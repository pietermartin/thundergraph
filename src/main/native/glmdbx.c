#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include "lmdb.h"
//#include "uthash.h"

#define	Z	"z"

static void prstat(MDB_stat *ms, char *name) {
	printf("%s\n", name);
	printf("  Tree depth: %u\n", ms->ms_depth);
	printf("  Branch pages: %"Z"u\n", ms->ms_branch_pages);
	printf("  Leaf pages: %"Z"u\n", ms->ms_leaf_pages);
	printf("  Overflow pages: %"Z"u\n", ms->ms_overflow_pages);
	printf("  Entries: %"Z"u\n", ms->ms_entries);
}

//typedef struct PropertyKeyStruct {
//	char *propertyKey;
//	int propertyKeyId;
//	UT_hash_handle hh;
//} PropertyKeyStruct;

typedef struct GLMDB_env {
	MDB_env *env;
	MDB_dbi configDb;
	MDB_dbi vertexDb;
	MDB_dbi edgeDb;
	MDB_dbi propertyKeyDb;
//	PropertyKeyStruct *propertyKeys;
	char *path;
} GLMDB_env;

//Core represent just the vertex's existence.
//If it exist but has no properties then this will be the only entry in the tree.
enum VertexCoreOrPropertyEnum {
	VCORE, VPROPERTY_KEY, OUTLABEL, INLABEL
};

enum EdgeCoreOrPropertyEnum {
	ECORE, EPROPERTY_KEY
};

typedef struct VertexDbId {
	int vertexId;
	enum VertexCoreOrPropertyEnum coreOrPropertyEnum;
	int propertykeyId;
	char *label;
	int edgeId;
} VertexDbId;

typedef struct EdgeDbId {
	int edgeId;
	enum EdgeCoreOrPropertyEnum coreOrPropertyEnum;
	int propertykeyId;
} EdgeDbId;

typedef struct EdgeData {
	int vertexInId;
	int vertexOutId;
	char *label;
} EdgeData;

int openGraph(GLMDB_env **genv, char *path);
int closeGraph(GLMDB_env *genv);
//int loadPropertyKeysIntoHashTable(GLMDB_env *genv);
//int loadPropertyKeyIdHigh(GLMDB_env *genv);
//PropertyKeyStruct *savePropertyKeyId(GLMDB_env *genv, MDB_txn *txn, char *propertyKey, PropertyKeyStruct *propertyKeyIdStruct);
//void addPropertyKey(PropertyKeyStruct **propertyKeys, char *propertyKey,
//		int propertyKeyId);
//void print_usersX(GLMDB_env genv);

void printDbStats(MDB_env *env, MDB_dbi vertexDb, char *name);
int addVertex(MDB_cursor *cursor, MDB_dbi vertexDb, int vertexId, MDB_val *vertexKey);
int addVertexBatch(MDB_cursor *cursor, MDB_dbi vertexDb, int vertexId,
		MDB_val *vertexKey);
int addEdge(MDB_txn *txn, MDB_dbi vertexDb, MDB_dbi edgeDb, int edgeId, char * label, int vertexInId, int vertexOutId, MDB_val *edgeKey);
int addEdgeToEdgeDb(MDB_txn *txn, MDB_dbi edgeDb, int edgeId, char *label, int vertexInId, int vertexOutId, MDB_val *edgeKey);
int addEdgeToVertexDb(MDB_txn *txn, MDB_dbi vertexDb, int edgeId, char *label, int vertexInId, int vertexOutId, MDB_val *edgeKey);
int getVertex(MDB_txn *txn, MDB_dbi vertexDb, int vertexId, MDB_val *vertex);
int setVertexProperty(MDB_txn *txn, MDB_cursor *cursor, GLMDB_env *genv, int vertexId,
		int propertyKeyId,
		char *propertyValue);
int setEdgeProperty(MDB_txn *txn, MDB_cursor *cursor, GLMDB_env *genv, int edgeId,
		int propertyKeyId,
		char *propertyValue);
int setVertexPropertyBatch(MDB_cursor *cursor, MDB_dbi vertexDb, int vertexId, int propertyKey,
		char *propertyValue);
int compareVertexDbId(const MDB_val *key1, const MDB_val *key2);
int compareEdgeDbId(const MDB_val *key1, const MDB_val *key2);

int openGraph(GLMDB_env **genv, char *path) {
	int rc;

	GLMDB_env *e;
	e = calloc(1, sizeof(GLMDB_env));

	MDB_txn *txn;
	MDB_env *env;
	MDB_dbi configDb;
	MDB_dbi vertexDb;
	MDB_dbi edgeDb;
	MDB_dbi propertyKeyDb;
	//The hashtable for property keys to integers
//	PropertyKeyStruct *propertyKeys = NULL;

	mdb_env_create(&env);
	mdb_env_set_mapsize(env, 107374182400); //100G
	mdb_env_set_maxdbs(env, 4);
	mdb_env_open(env, path, MDB_NOSYNC, 0664);

	//Create the config db
	mdb_txn_begin(env, NULL, 0, &txn);
	rc = mdb_open(txn, "configDb", MDB_CREATE, &configDb);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	mdb_txn_commit(txn);

	//Create the vertex db
	mdb_txn_begin(env, NULL, 0, &txn);
	rc = mdb_open(txn, "vertexDb", MDB_CREATE|MDB_INTEGERKEY, &vertexDb);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	mdb_set_compare(txn, vertexDb, compareVertexDbId);
	mdb_set_compare(txn, edgeDb, compareEdgeDbId);
	mdb_txn_commit(txn);

	//Create the edge db
	mdb_txn_begin(env, NULL, 0, &txn);
	rc = mdb_open(txn, "edgeDb", MDB_CREATE|MDB_INTEGERKEY, &edgeDb);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	mdb_txn_commit(txn);

	//Create the property key db
	mdb_txn_begin(env, NULL, 0, &txn);
	rc = mdb_open(txn, "propertyKeyDb", MDB_CREATE, &propertyKeyDb);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_txn_commit(txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}

	e->env = env;
	e->configDb = configDb;
	e->vertexDb = vertexDb;
	e->edgeDb = edgeDb;
	e->propertyKeyDb = propertyKeyDb;
	//The hashtable for property keys to integers
//	e->propertyKeys = propertyKeys;

	*genv = e;

//	rc = loadPropertyKeyIdHigh(*genv);
//	if (rc != 0) {
//		return rc;
//	}
//
//	rc = loadPropertyKeysIntoHashTable(*genv);
	return rc;
}

int closeGraph(GLMDB_env *genv) {
	MDB_env *env = genv->env;
	MDB_dbi configDb = genv->configDb;
	MDB_dbi vertexDb = genv->vertexDb;
	MDB_dbi edgeDb = genv->edgeDb;
	MDB_dbi propertyKeyDb = genv->propertyKeyDb;

//	HASH_CLEAR(hh,genv->propertyKeys);

	printDbStats(env, configDb, "configDb");
	printDbStats(env, vertexDb, "vertexDb");
	printDbStats(env, edgeDb, "edgeDb");
	printDbStats(env, propertyKeyDb, "propertyKeyDb");

	mdb_close(env, configDb);
	mdb_close(env, vertexDb);
	mdb_close(env, edgeDb);
	mdb_close(env, propertyKeyDb);
	mdb_env_close(env);
	return 0;
}

//MDB_val *vertexKey is out only
int addVertex(MDB_cursor *cursor, MDB_dbi vertexDb, int vertexId, MDB_val *vertexKey) {
	MDB_val data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VCORE;
	id.propertykeyId = -1;
	(*vertexKey).mv_size = (sizeof(VertexDbId));
	(*vertexKey).mv_data = &id;
	//write a null of sorts
	data.mv_size = strlen("\0");
	data.mv_data = "\0";
	return mdb_cursor_put(cursor, vertexKey, &data, MDB_NOOVERWRITE);
}

int addVertexBatch(MDB_cursor *cursor, MDB_dbi vertexDb, int vertexId,
		MDB_val *vertexKey) {
	MDB_val data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VCORE;
	id.propertykeyId = -1;
	(*vertexKey).mv_size = (sizeof(VertexDbId));
	(*vertexKey).mv_data = &id;
	//write a null of sorts
	data.mv_size = strlen("\0");
	data.mv_data = "\0";
	return mdb_cursor_put(cursor, vertexKey, &data, MDB_APPEND);
}

//MDB_val *edgeKey is out only
int addEdge(MDB_txn *txn, MDB_dbi vertexDb, MDB_dbi edgeDb, int edgeId, char *label, int vertexInId, int vertexOutId, MDB_val *edgeKey) {
	int rc = addEdgeToEdgeDb(txn, edgeDb, edgeId, label, vertexInId, vertexOutId, edgeKey);
	if (rc == 0) {
		MDB_val edgeVertexDbKey;
		rc = addEdgeToVertexDb(txn, vertexDb, edgeId, label, vertexInId, vertexOutId, &edgeVertexDbKey);
	}
	return rc;
}

int addEdgeToEdgeDb(MDB_txn *txn, MDB_dbi edgeDb, int edgeId, char *label, int vertexInId, int vertexOutId, MDB_val *edgeKey) {
	MDB_val data;
	EdgeDbId id;
	id.edgeId = edgeId;
	id.coreOrPropertyEnum = ECORE;
	id.propertykeyId = -1;
	(*edgeKey).mv_size = (sizeof(EdgeDbId));
	(*edgeKey).mv_data = &id;

	EdgeData edgeData;
	edgeData.vertexInId = vertexInId;
	edgeData.vertexOutId = vertexOutId;
	int strLength = strlen(label) + 1;
	edgeData.label = malloc(strLength);
	strncpy(edgeData.label, label, strLength);

	data.mv_size = sizeof(EdgeData);
	data.mv_data = &edgeData;
	return mdb_put(txn, edgeDb, edgeKey, &data, MDB_NOOVERWRITE);
}

int addEdgeToVertexDb(MDB_txn *txn, MDB_dbi vertexDb, int edgeId, char *label, int vertexInId, int vertexOutId, MDB_val *edgeVertexDbKey) {
	MDB_val data;
	VertexDbId id;
	id.vertexId = vertexInId;
	id.coreOrPropertyEnum = OUTLABEL;
	id.propertykeyId = -1;
	id.edgeId = edgeId;
	int strLength = strlen(label) + 1;
	id.label = malloc(strLength);
	strncpy(id.label, label, strLength);

	(*edgeVertexDbKey).mv_size = sizeof(VertexDbId) + strLength;
	(*edgeVertexDbKey).mv_data = &id;
	data.mv_size = sizeof(int);
	data.mv_data = &vertexOutId;
	return mdb_put(txn, vertexDb, edgeVertexDbKey, &data, MDB_NOOVERWRITE);
}

int getVertex(MDB_txn *txn, MDB_dbi vertexDb, int vertexId, MDB_val *vertexKey) {
	MDB_val data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VCORE;
	id.propertykeyId = -1;
	(*vertexKey).mv_size = (sizeof(int) + sizeof(enum VertexCoreOrPropertyEnum)
			+ sizeof(int));
	(*vertexKey).mv_data = &id;
	MDB_cursor *cursor;
	mdb_cursor_open(txn, vertexDb, &cursor);
	return mdb_cursor_get(cursor, vertexKey, &data, MDB_SET_KEY);
}

int setVertexProperty(MDB_txn *txn, MDB_cursor *cursor, GLMDB_env *genv, int vertexId,
		int propertyKeyId,
		char *propertyValue) {
	MDB_val key, data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VPROPERTY_KEY;
	id.propertykeyId = propertyKeyId;
	key.mv_size = (sizeof(VertexDbId));
	key.mv_data = &id;
	if (propertyValue != NULL) {
		data.mv_size = strlen(propertyValue);
		data.mv_data = propertyValue;
	} else {
		//write a null of sorts
		data.mv_size = strlen("\0");
		data.mv_data = "\0";
	}
	return mdb_cursor_put(cursor, &key, &data, MDB_NOOVERWRITE);
}

int setEdgeProperty(MDB_txn *txn, MDB_cursor *cursor, GLMDB_env *genv, int edgeId,
		int propertyKeyId,
		char *propertyValue) {

	MDB_val key, data;
	EdgeDbId id;
	id.edgeId = edgeId;
	id.coreOrPropertyEnum = EPROPERTY_KEY;
	id.propertykeyId = propertyKeyId;
	key.mv_size = (sizeof(EdgeDbId));
	key.mv_data = &id;
	if (propertyValue != NULL) {
		data.mv_size = strlen(propertyValue) + 1;
		data.mv_data = propertyValue;
	} else {
		//write a null of sorts
		data.mv_size = strlen("\0");
		data.mv_data = "\0";
	}
	return mdb_cursor_put(cursor, &key, &data, MDB_NOOVERWRITE);
}

int setVertexPropertyBatch(MDB_cursor *cursor, MDB_dbi vertexDb, int vertexId, int propertyKey,
		char *propertyValue) {
	MDB_val key, data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VPROPERTY_KEY;
	id.propertykeyId = propertyKey;
	key.mv_size = (sizeof(VertexDbId));
	key.mv_data = &id;
	if (propertyValue != NULL) {
		data.mv_size = strlen(propertyValue);
		data.mv_data = propertyValue;
	} else {
		//write a null of sorts
		data.mv_size = strlen("\0");
		data.mv_data = "\0";
	}
	return mdb_cursor_put(cursor, &key, &data, MDB_APPEND);
}

int compareVertexDbId(const MDB_val *key1, const MDB_val *key2) {
	int vertex1Id = (*(VertexDbId *) (key1->mv_data)).vertexId;
	int vertex2Id = (*(VertexDbId *) (key2->mv_data)).vertexId;
	if (vertex1Id == vertex2Id) {
		//Need to compare further on core or property. core comes first
		enum VertexCoreOrPropertyEnum coreOrProperty1 =
				(*(VertexDbId *) (key1->mv_data)).coreOrPropertyEnum;
		enum VertexCoreOrPropertyEnum coreOrProperty2 =
				(*(VertexDbId *) (key2->mv_data)).coreOrPropertyEnum;
		if (coreOrProperty1 == coreOrProperty2) {
			switch (coreOrProperty1) {
				case VCORE:
					return 0;
					break;
				case VPROPERTY_KEY:
					;
					int propertyKey1 = (*(VertexDbId *) (key1->mv_data)).propertykeyId;
					int propertyKey2 = (*(VertexDbId *) (key2->mv_data)).propertykeyId;
					return (propertyKey1 > propertyKey2) - (propertyKey1 < propertyKey2);
					break;
				case OUTLABEL:
					;
					char *label1 = (*(VertexDbId *) (key1->mv_data)).label;
					char *label2 = (*(VertexDbId *) (key2->mv_data)).label;
					int labelCmp1 = strcmp(label1, label2);
					if (labelCmp1 == 0) {
						//Compare the edge id
						int edgeId1 = (*(VertexDbId *) (key1->mv_data)).edgeId;
						int edgeId2 = (*(VertexDbId *) (key2->mv_data)).edgeId;
						return (edgeId1 > edgeId2)
								- (edgeId1 < edgeId2);
					} else {
						return labelCmp1;
					}
					break;
				case INLABEL:
					;
					char *label11 = (*(VertexDbId *) (key1->mv_data)).label;
					char *label22 = (*(VertexDbId *) (key2->mv_data)).label;
					int labelCmp2 = strcmp(label11, label22);
					if (labelCmp2 == 0) {
						//Compare the edge id
						int edgeId1 = (*(VertexDbId *) (key1->mv_data)).edgeId;
						int edgeId2 = (*(VertexDbId *) (key2->mv_data)).edgeId;
						return (edgeId1 > edgeId2)
								- (edgeId1 < edgeId2);
					} else {
						return labelCmp2;
					}
					break;
			}

		} else {
			return (coreOrProperty1 > coreOrProperty2)
					- (coreOrProperty1 < coreOrProperty2);
		}
	} else {
		return (vertex1Id > vertex2Id) - (vertex1Id < vertex2Id);
	}
	return 0;
}

int compareEdgeDbId(const MDB_val *key1, const MDB_val *key2) {
	int edge1Id = (*(EdgeDbId *) (key1->mv_data)).edgeId;
	int edge2Id = (*(EdgeDbId *) (key2->mv_data)).edgeId;
	if (edge1Id == edge2Id) {
		//Need to compare further on core or property. core comes first
		enum EdgeCoreOrPropertyEnum coreOrProperty1 =
				(*(EdgeDbId *) (key1->mv_data)).coreOrPropertyEnum;
		enum EdgeCoreOrPropertyEnum coreOrProperty2 =
				(*(EdgeDbId *) (key2->mv_data)).coreOrPropertyEnum;
		if (coreOrProperty1 == coreOrProperty2) {
			switch (coreOrProperty1) {
				case ECORE:
					return 0;
					break;
				case EPROPERTY_KEY:
					;
					int propertyKey1 = (*(EdgeDbId *) (key1->mv_data)).propertykeyId;
					int propertyKey2 = (*(EdgeDbId *) (key2->mv_data)).propertykeyId;
					return (propertyKey1 > propertyKey2) - (propertyKey1 < propertyKey2);
					break;
			}
		} else {
			return (coreOrProperty1 > coreOrProperty2)
					- (coreOrProperty1 < coreOrProperty2);
		}
	} else {
		return (edge1Id > edge2Id) - (edge1Id < edge2Id);
	}
	return 0;
}

void printDbStats(MDB_env *env, MDB_dbi vertexDb, char *name) {
	MDB_txn *txn;
	MDB_stat stat;
	mdb_txn_begin(env, NULL, 1, &txn);
	mdb_stat(txn, vertexDb, &stat);
	prstat(&stat, name);
	mdb_txn_commit(txn);
}

//void addPropertyKey(PropertyKeyStruct **propertyKeys, char *propertyKey,
//		int propertyKeyId) {
//	PropertyKeyStruct *s = (PropertyKeyStruct*) malloc(sizeof(PropertyKeyStruct));
//	s->propertyKeyId = propertyKeyId;
//
//	char *propertyKeyCopy;
//	propertyKeyCopy = malloc(strlen(propertyKey) + 1);
//	strcpy(propertyKeyCopy, propertyKey);
//	s->propertyKey = propertyKeyCopy;
//	HASH_ADD_KEYPTR(hh, *propertyKeys, s->propertyKey, strlen(s->propertyKey),
//			s);
//}
//
//void print_usersX(GLMDB_env genv) {
//	PropertyKeyStruct *s;
//	for (s = genv.propertyKeys; s != NULL; s = (PropertyKeyStruct*) (s->hh.next)) {
//		printf("propertyKey %s: propertyKeyId %d\n", s->propertyKey,
//				s->propertyKeyId);
//	}
//}

//int loadPropertyKeysIntoHashTable(GLMDB_env *genv) {
//	int rc = 0;
//
//	MDB_env *env = genv->env;
//	MDB_dbi propertyKeyDb = genv->propertyKeyDb;
//	PropertyKeyStruct **propertyKeys = &(genv->propertyKeys);
//
//	MDB_txn *txn;
//	MDB_cursor *cursor;
//	MDB_val key, data;
//	rc = mdb_txn_begin(env, NULL, 1, &txn);
//	if (rc != 0) {
//		mdb_txn_abort(txn);
//		return rc;
//	}
//	rc = mdb_cursor_open(txn, propertyKeyDb, &cursor);
//	if (rc != 0) {
//		mdb_txn_abort(txn);
//		return rc;
//	}
//	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
//		char *propertyKey = (char *) (key.mv_data);
//		int propertyKeyId = *((int *) (data.mv_data));
//		addPropertyKey(propertyKeys, propertyKey, propertyKeyId);
//	}
//	mdb_cursor_close(cursor);
//	mdb_txn_abort(txn);
//	return 0;
//}
//
//int loadPropertyKeyIdHigh(GLMDB_env *genv) {
//	int rc = 0;
//	MDB_txn *txn;
//	MDB_dbi configDb = genv->configDb;
//	MDB_cursor *cursor;
//	MDB_val key, data;
//
//	int propertyKeyHighIdKey = 0;
//	key.mv_size = sizeof(int);
//	key.mv_data = &propertyKeyHighIdKey;
//
//	rc = mdb_txn_begin(genv->env, NULL, 1, &txn);
//	if (rc != 0) {
//		mdb_txn_abort(txn);
//		return rc;
//	}
//	rc = mdb_cursor_open(txn, configDb, &cursor);
//	if (rc != 0) {
//		mdb_txn_abort(txn);
//		return rc;
//	}
//	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_KEY);
//	if (rc == MDB_NOTFOUND) {
//		//Must be the first time. Insert the first propertyKeyHighId
//		data.mv_size = sizeof(int);
//		data.mv_data = &propertyKeyHighIdKey;
//		rc = mdb_cursor_put(cursor, &key, &data, MDB_NOOVERWRITE);
//		mdb_cursor_close(cursor);
//		if (rc != 0) {
//			mdb_txn_abort(txn);
//			return rc;
//		} else {
//			rc = mdb_txn_commit(txn);
//			if (rc != 0) {
//				mdb_txn_abort(txn);
//			}
////			genv->propertyKeyIdHigh = *((char *) data.mv_data);
//			return rc;
//		}
//	} else {
//		mdb_cursor_close(cursor);
//		mdb_txn_abort(txn);
//		return rc;
//	}
//}

//PropertyKeyStruct *savePropertyKeyId(GLMDB_env *genv, MDB_txn *txn, char *propertyKey, PropertyKeyStruct *propertyKeyIdStruct) {
//	int rc = 0;
//	MDB_cursor *cursor;
//	MDB_val key, data;
//
//	//do some locking
//
//	//after lock check if it has not in the mean time arrived
//	HASH_FIND_STR(genv->propertyKeys, propertyKey, propertyKeyIdStruct);
//	if (propertyKeyIdStruct == NULL) {
//
//		propertyKeyIdStruct = (PropertyKeyStruct*) malloc(sizeof(PropertyKeyStruct));
//
//		//get the current propertyKeyHighId
//		MDB_dbi configDb = genv->configDb;
//		rc = mdb_cursor_open(txn, configDb, &cursor);
//		if (rc != 0) {
//			printf("could not open nested cursor %i\n", rc);
//		}
//		int propertyKeyHighIdKey = 0;
//		key.mv_size = sizeof(int);
//		key.mv_data = &propertyKeyHighIdKey;
//		rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_KEY);
//		propertyKeyIdStruct->propertyKeyId = *((int *) data.mv_data);
//		//update the current propertyKeyHighId
//		data.mv_size = sizeof(int);
//		int nextPropertyKeyHighId = propertyKeyIdStruct->propertyKeyId + 1;
//		data.mv_data = &nextPropertyKeyHighId;
//		rc = mdb_cursor_put(cursor, &key, &data, 0);
//		mdb_cursor_close(cursor);
//
//		//add the key with its property key id
//		MDB_dbi propertyKeyDb = genv->propertyKeyDb;
//		rc = mdb_cursor_open(txn, propertyKeyDb, &cursor);
//		key.mv_size = strlen(propertyKey) + 1;
//		key.mv_data = propertyKey;
//		data.mv_size = sizeof(int);
//		data.mv_data = &(propertyKeyIdStruct->propertyKeyId);
//		rc = mdb_cursor_put(cursor, &key, &data, MDB_NOOVERWRITE);
//		addPropertyKey(&(genv->propertyKeys), propertyKey, propertyKeyIdStruct->propertyKeyId);
//		mdb_cursor_close(cursor);
//	}
//
//	//unlock
//	return propertyKeyIdStruct;
//}
