#include <jni.h>
#include <stdio.h>
#include <string.h>
#include "lmdb.h"
#include "glmdb_jni.h"

#define	Z	"z"

static void prstat(MDB_stat *ms, char *name) {
	printf("%s\n", name);
	printf("  Tree depth: %u\n", ms->ms_depth);
	printf("  Branch pages: %"Z"u\n", ms->ms_branch_pages);
	printf("  Leaf pages: %"Z"u\n", ms->ms_leaf_pages);
	printf("  Overflow pages: %"Z"u\n", ms->ms_overflow_pages);
	printf("  Entries: %"Z"u\n", ms->ms_entries);
}

JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_init(JNIEnv *env,
		jclass that) {
	printf("called init\n");
}

JNIEXPORT jstring JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1strerror(
		JNIEnv *env, jclass that, jint error) {

	char *mdbError = mdb_strerror(error);
	jstring message = (*env)->NewStringUTF(env, mdbError);
	return message;

}

JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_glmdb_1env_1create(
		JNIEnv * env, jclass that, jstring path, jlongArray pointerArray) {

	const char *dbPath = NULL;
	jlong *mdbEnv = NULL;
	jint rc = 0;
	if (path) {
		if ((dbPath = (*env)->GetStringUTFChars(env, path, NULL)) == NULL) {
			goto fail;
		}
	}
	if (pointerArray) {
		if ((mdbEnv = (*env)->GetLongArrayElements(env, pointerArray, NULL))
				== NULL) {
			goto fail;
		}
	}
	rc = (jint) openGraph((GLMDB_env **) mdbEnv, dbPath);
	fail: if (pointerArray && mdbEnv) {
		(*env)->ReleaseLongArrayElements(env, pointerArray, mdbEnv, 0);
	}
	if (path && dbPath) {
		(*env)->ReleaseStringUTFChars(env, path, dbPath);
	}
	return rc;
}

JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_glmdb_1env_1close(
		JNIEnv *env, jclass that, jlong glmdbEnv) {

	closeGraph((GLMDB_env *) (long) glmdbEnv);

}

JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1begin(
		JNIEnv *env, jclass that, jlong glmdbEnv, jlong parent, jlong flags,
		jlongArray txnArray) {

	jint rc = 0;
	jlong *txn = NULL;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	if (txnArray) {
		if ((txn = (*env)->GetLongArrayElements(env, txnArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = mdb_txn_begin(glmdb_env->env, (MDB_txn *) (long) parent,
			(unsigned int) flags, (MDB_txn **) txn);
	fail: if (txnArray && txn) {
		(*env)->ReleaseLongArrayElements(env, txnArray, txn, 0);
	}
	return rc;

}

JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1renew(
		JNIEnv *env, jclass that, jlong txn) {

	jint rc = 0;
	rc = (jint) mdb_txn_renew((MDB_txn *) (long) txn);
	return rc;

}

JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1commit(
		JNIEnv *env, jclass that, jlong txn) {

	jint rc = 0;
	rc = (jint) mdb_txn_commit((MDB_txn *) (long) txn);
	return rc;

}

JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1reset(
		JNIEnv *env, jclass that, jlong txn) {

	mdb_txn_reset((MDB_txn *) (long) txn);

}

JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1abort(
		JNIEnv *env, jclass that, jlong txn) {

	mdb_txn_abort((MDB_txn *) (long) txn);

}

//JNIEnv *env, jclass that, jlong arg0, jlong arg1, jlongArray arg2
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1cursor_1open_1vertex_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv,
		jlongArray cursorArray) {

	jlong *cursor = NULL;
	jint rc = 0;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL))
				== NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexDb,
			(MDB_cursor **) cursor);
	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_cursor_close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1cursor_1close(
		JNIEnv *env, jclass that, jlong cursor) {
	mdb_cursor_close((MDB_cursor *) (long) cursor);
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_cursor_renew
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1cursor_1renew(
		JNIEnv *env, jclass that, jlong txn, jlong cursor) {

	jint rc = 0;
	rc = (jint) mdb_cursor_renew((MDB_txn *) (long) txn,
			(MDB_cursor *) (long) cursor);
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_add_vertex
 * Signature: (JJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1add_1vertex(
		JNIEnv *env, jclass that, jlong glmdbEnv, jlong cursor,
		jlongArray vertexIdArray) {

	jint rc = 0;
	jlong *vertexId = NULL;
	MDB_val vertexKey;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	glmdb_env->vertexIdSequence++;
	if (vertexIdArray) {
		if ((vertexId = (*env)->GetLongArrayElements(env, vertexIdArray, NULL))
				== NULL) {
			goto fail;
		}
	}
	rc = addVertex((MDB_cursor *) (long) cursor, glmdb_env->vertexDb,
			glmdb_env->vertexIdSequence, &vertexKey);
	*vertexId = (*((VertexDbId *) (vertexKey.mv_data))).vertexId;

	fail: if (vertexIdArray && vertexId) {
		(*env)->ReleaseLongArrayElements(env, vertexIdArray, vertexId, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_string
 * Signature: (JJILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1string(
		JNIEnv *env, jclass that, jlong cursor, jlong vertexId,
		jint propertyKeyId, jstring value) {

	jint rc = 0;
	jint strlen = (*env)->GetStringUTFLength(env, value);
	char *propertyValue = malloc(strlen);
	if (value) {
		(*env)->GetStringUTFRegion(env, value, 0, strlen, propertyValue);
		if (propertyValue == NULL) {
			goto fail;
		}
	}
	rc = setVertexPropertyString((MDB_cursor *) (long) cursor, (long)vertexId, (int)propertyKeyId, propertyValue);

	fail: if (value && propertyValue) {
		(*env)->ReleaseStringUTFChars(env, value, propertyValue);
	}
	return rc;
}

int openGraph(GLMDB_env **genv, const char *path) {
	int rc;

	GLMDB_env *e;
	e = calloc(sizeof(GLMDB_env), 1);

	MDB_txn *txn;
	MDB_env *env;
	MDB_dbi configDb;
	MDB_dbi vertexDb;
	MDB_dbi edgeDb;
	MDB_dbi propertyKeyDb;

	rc = mdb_env_create(&env);
	if (rc != 0) {
		return rc;
	}
	rc = mdb_env_set_mapsize(env, 107374182400); //100G
	if (rc != 0) {
		return rc;
	}
	rc = mdb_env_set_maxdbs(env, 4);
	if (rc != 0) {
		return rc;
	}
	rc = mdb_env_open(env, path, MDB_NOSYNC, 0664);
	if (rc != 0) {
		return rc;
	}

//Create the config db
	rc = mdb_txn_begin(env, NULL, 0, &txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_open(txn, "configDb", MDB_CREATE, &configDb);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_txn_commit(txn);
	if (rc != 0) {
		return rc;
	}

//Create the vertex db
	rc = mdb_txn_begin(env, NULL, 0, &txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_open(txn, "vertexDb", MDB_CREATE|MDB_INTEGERKEY, &vertexDb);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_set_compare(txn, vertexDb, compareVertexDbId);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_txn_commit(txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}

//Create the edge db
	rc = mdb_txn_begin(env, NULL, 0, &txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_open(txn, "edgeDb", MDB_CREATE|MDB_INTEGERKEY, &edgeDb);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_set_compare(txn, edgeDb, compareEdgeDbId);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_txn_commit(txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}

//Create the property key db
	rc = mdb_txn_begin(env, NULL, 0, &txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
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
	*genv = e;
	printf("created GLMDB_env\n");
	return rc;
}

void closeGraph(GLMDB_env *genv) {
	MDB_env *env = genv->env;
	MDB_dbi configDb = genv->configDb;
	MDB_dbi vertexDb = genv->vertexDb;
	MDB_dbi edgeDb = genv->edgeDb;
	MDB_dbi propertyKeyDb = genv->propertyKeyDb;

	printDbStats(env, configDb, "configDb");
	printDbStats(env, vertexDb, "vertexDb");
	printDbStats(env, edgeDb, "edgeDb");
	printDbStats(env, propertyKeyDb, "propertyKeyDb");

	mdb_close(env, configDb);
	mdb_close(env, vertexDb);
	mdb_close(env, edgeDb);
	mdb_close(env, propertyKeyDb);
	mdb_env_close(env);
	printf("closed GLMDB_env\n");
}

//MDB_val *vertexKey is out only
int addVertex(MDB_cursor *cursor, MDB_dbi vertexDb, long vertexId,
		MDB_val *vertexKey) {
	MDB_val data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VCORE;
	id.propertykeyId = -1;
	(*vertexKey).mv_size = (sizeof(VertexDbId));
	(*vertexKey).mv_data = &id;
//write a null of sorts
	data.mv_size = strlen("") + 1;
	data.mv_data = "";
	return mdb_cursor_put(cursor, vertexKey, &data, MDB_NOOVERWRITE);
}

int setVertexPropertyString(MDB_cursor *cursor, long vertexId,
		int propertyKeyId, char *propertyValue) {
	MDB_val key, data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VPROPERTY_KEY;
	id.propertykeyId = propertyKeyId;
	key.mv_size = (sizeof(VertexDbId));
	key.mv_data = &id;
	if (propertyValue != NULL) {
		data.mv_size = strlen(propertyValue) + 1;
		data.mv_data = propertyValue;
	} else {
		//write a null of sorts
		data.mv_size = strlen("") + 1;
		data.mv_data = "";
	}
	return mdb_cursor_put(cursor, &key, &data, MDB_NOOVERWRITE);
}

int getVertexPropertyString(MDB_cursor *cursor, long vertexId,
		int propertyKeyId, char *propertyValue) {
	MDB_val key, data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VPROPERTY_KEY;
	id.propertykeyId = propertyKeyId;
	key.mv_size = (sizeof(VertexDbId));
	key.mv_data = &id;
	if (propertyValue != NULL) {
		data.mv_size = strlen(propertyValue) + 1;
		data.mv_data = propertyValue;
	} else {
		//write a null of sorts
		data.mv_size = strlen("") + 1;
		data.mv_data = "";
	}
	return mdb_cursor_put(cursor, &key, &data, MDB_NOOVERWRITE);
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
				int propertyKey1 =
						(*(VertexDbId *) (key1->mv_data)).propertykeyId;
				int propertyKey2 =
						(*(VertexDbId *) (key2->mv_data)).propertykeyId;
				return (propertyKey1 > propertyKey2)
						- (propertyKey1 < propertyKey2);
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
					return (edgeId1 > edgeId2) - (edgeId1 < edgeId2);
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
					return (edgeId1 > edgeId2) - (edgeId1 < edgeId2);
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
				return (propertyKey1 > propertyKey2)
						- (propertyKey1 < propertyKey2);
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
