#include <stdlib.h>
#include "thundergraph_boolean.h"

void printBooleanIndexDbRecord(MDB_val key, MDB_val data) {
	BooleanIndexKeyStruct *booleanIndexKeyStruct = (BooleanIndexKeyStruct *) (key.mv_data);
	int propertyKeyId = booleanIndexKeyStruct->propertyKeyId;
	unsigned char propertyKeyValue = booleanIndexKeyStruct->value;
	long long elementIdKey = booleanIndexKeyStruct->elementId;
	printf("propertyKeyId: %i, propertyKeyValue: %u, element id: %lld\n", propertyKeyId, propertyKeyValue, elementIdKey);
}

int setVertexPropertyBoolean(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jboolean *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		VertexDbId id;
		id.vertexId = vertexId;
		id.coreOrPropertyEnum = VPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		id.labelId = -1;
		id.edgeId = -1LL;
		key.mv_size = sizeof(VertexDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jboolean);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int compareBooleanIndexDbId(const MDB_val *key1, const MDB_val *key2) {
	BooleanIndexKeyStruct *booleanIndexKeyStruct1 = (BooleanIndexKeyStruct *) (key1->mv_data);
	BooleanIndexKeyStruct *booleanIndexKeyStruct2 = (BooleanIndexKeyStruct *) (key2->mv_data);
	int propertyKeyId1 = booleanIndexKeyStruct1->propertyKeyId;
	int propertyKeyId2 = booleanIndexKeyStruct2->propertyKeyId;
	if (propertyKeyId1 == propertyKeyId2) {
		unsigned char value1 = booleanIndexKeyStruct1->value;
		unsigned char value2 = booleanIndexKeyStruct2->value;
		if (value1 == value2) {
			long long elementId1 = booleanIndexKeyStruct1->elementId;
			long long elementId2 = booleanIndexKeyStruct2->elementId;
			return (elementId1 > elementId2) - (elementId1 < elementId2);
		} else {
			return (value1 > value2) - (value1 < value2);
		}
	} else {
		return (propertyKeyId1 > propertyKeyId2) - (propertyKeyId1 < propertyKeyId2);
	}
}

int getFirstElementForKeyValueFromBooleanIndex(MDB_cursor *cursor, int propertyKeyId, unsigned char value, long long int *vertexIdResultC) {

	printf("getFirstElementForKeyValueFromBooleanIndex propertyKeyId = %i", propertyKeyId);

	int rc;
	MDB_val key, data;
	BooleanIndexKeyStruct *booleanIndexKeyStruct = malloc(sizeof(BooleanIndexKeyStruct));
	booleanIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	booleanIndexKeyStruct->value = value;
	booleanIndexKeyStruct->elementId = -1LL;
	key.mv_size = sizeof(BooleanIndexKeyStruct);
	key.mv_data = booleanIndexKeyStruct;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {

		BooleanIndexKeyStruct *booleanIndexKeyStructTmp = (BooleanIndexKeyStruct *) (key.mv_data);
		unsigned char value1 = booleanIndexKeyStructTmp->value;

		printf("getFirstElementForKeyValueFromBooleanIndex value1 = %u", value1);
		printf("getFirstElementForKeyValueFromBooleanIndex value = %u", value);

		if (value == value1) {
			*vertexIdResultC = *((long long *) data.mv_data);
		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int getNextElementForKeyValueFromBooleanIndex(MDB_cursor *cursor, int propertyKeyId, unsigned char value, long long int *vertexIdResultC) {

	int rc;
	MDB_val key, data;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT);
	if (rc == 0) {

		BooleanIndexKeyStruct *booleanIndexKeyStructTmp = (BooleanIndexKeyStruct *) (key.mv_data);
		unsigned char value1 = booleanIndexKeyStructTmp->value;
		if (value1 == value) {
			*vertexIdResultC = *((long long *) data.mv_data);
		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int traverseBooleanIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi) {
	int rc = 0;
	MDB_cursor *cursor;
	MDB_val key, data;
	rc = mdb_cursor_open(txn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		printBooleanIndexDbRecord(key, data);
	}
	fail: mdb_cursor_close(cursor);
	return rc;
}

int setBooleanIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, unsigned char propertyValue) {
	int rc;
	MDB_val key, data;
	BooleanIndexKeyStruct *booleanIndexKeyStruct = malloc(sizeof(BooleanIndexKeyStruct));
	booleanIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	booleanIndexKeyStruct->elementId = (long long) elementId;
	booleanIndexKeyStruct->value = propertyValue;
	key.mv_size = sizeof(BooleanIndexKeyStruct);
	key.mv_data = booleanIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_put(indexCursor, &key, &data, 0);
	free(booleanIndexKeyStruct);
	return rc;
}

int removeBooleanIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, unsigned char propertyValue) {
	int rc;
	MDB_val key, data;
	BooleanIndexKeyStruct *booleanIndexKeyStruct = malloc(sizeof(BooleanIndexKeyStruct));
	booleanIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	booleanIndexKeyStruct->elementId = (long long) elementId;
	booleanIndexKeyStruct->value = propertyValue;
	key.mv_size = sizeof(BooleanIndexKeyStruct);
	key.mv_data = booleanIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_get(indexCursor, &key, &data, MDB_SET_KEY);
	if (rc == 0) {
		rc = mdb_cursor_del(indexCursor, 0);
	}
	free(booleanIndexKeyStruct);
	return rc;
}

int addOrUpdateBooleanIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId, int propertyKeyId,
		jboolean propertyValue, unsigned char vertex) {

	int rc;
	MDB_cursor *booleanIndexCursor;
	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexBooleanIndexDb, &booleanIndexCursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeBooleanIndexDb, &booleanIndexCursor);
	}
	if (rc != 0) {
		goto failIndexedVertex;
	}
	rc = deleteEntryFromBooleanIndex(glmdb_env, mdbTxn, vertexCursor, booleanIndexCursor, (long long) elementId, (int) propertyKeyId);
	if (rc != 0 && rc != MDB_NOTFOUND) {
		goto failIndexedVertex;
	}
	rc = setVertexPropertyBoolean(vertexCursor, (long) elementId, (int) propertyKeyId, &propertyValue);
	if (rc != 0) {
		goto failIndexedVertex;
	}

	rc = setBooleanIndex(booleanIndexCursor, elementId, propertyKeyId, propertyValue);

	failIndexedVertex: mdb_cursor_close(booleanIndexCursor);
	return rc;
}

int deleteEntryFromBooleanIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *booleanIndexCursor,
		long long elementId, int propertyKeyId) {

	int rc;

	//Get the old value first
	MDB_val oldData;
	MDB_val key, data;
	rc = getVertexProperty(vertexCursor, elementId, propertyKeyId, &oldData);
	if (rc == 0) {
		//Delete the current indexed element
		BooleanIndexKeyStruct *booleanIndexKeyStruct = malloc(sizeof(BooleanIndexKeyStruct));
		booleanIndexKeyStruct->propertyKeyId = propertyKeyId;
		booleanIndexKeyStruct->elementId = elementId;
		booleanIndexKeyStruct->value = *((unsigned char *) oldData.mv_data);
		key.mv_size = sizeof(BooleanIndexKeyStruct);
		key.mv_data = booleanIndexKeyStruct;
		rc = mdb_cursor_get(booleanIndexCursor, &key, &data, MDB_SET_KEY);
		if (rc != 0) {
			free(booleanIndexKeyStruct);
			goto fail;
		}
		free(booleanIndexKeyStruct);
		rc = mdb_cursor_del(booleanIndexCursor, 0);
	}

	fail: return rc;
}

int setEdgePropertyBoolean(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jboolean *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = EPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		key.mv_size = sizeof(EdgeDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jboolean);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int deleteBooleanIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex) {
	int rc;
	MDB_cursor *cursor;

	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexBooleanIndexDb, &cursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeBooleanIndexDb, &cursor);
	}
	if (rc == 0) {
		MDB_val key, data;
		BooleanIndexKeyStruct *booleanIndexKeyStruct = malloc(sizeof(BooleanIndexKeyStruct));
		booleanIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
		booleanIndexKeyStruct->elementId = -1LL;
		booleanIndexKeyStruct->value = 0;

		key.mv_size = sizeof(BooleanIndexKeyStruct);
		key.mv_data = booleanIndexKeyStruct;

		while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE) == 0)) {

			BooleanIndexKeyStruct *booleanIndexKeyStructToDelete = (BooleanIndexKeyStruct *) (key.mv_data);
			if (booleanIndexKeyStructToDelete->propertyKeyId == propertyKeyId) {
				rc = mdb_cursor_del(cursor, 0);
				if (rc != 0) {
					break;
				} else {
					//reset the key
					booleanIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
					booleanIndexKeyStruct->elementId = -1LL;
					booleanIndexKeyStruct->value = 0;
				}
			} else {
				break;
			}

		}
		free(booleanIndexKeyStruct);
	}
	return rc;

}

int placeCursorOnKeyValueBooleanIndex(MDB_cursor *cursor, long long vertexId, int propertyKeyId, jboolean value) {

	int rc;
	MDB_val key, data;
	BooleanIndexKeyStruct *booleanIndexKeyStruct = malloc(sizeof(BooleanIndexKeyStruct));
	booleanIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	booleanIndexKeyStruct->elementId = -1LL;
	booleanIndexKeyStruct->elementId = vertexId;
	booleanIndexKeyStruct->value = value;
	key.mv_size = sizeof(BooleanIndexKeyStruct);
	key.mv_data = booleanIndexKeyStruct;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {

		BooleanIndexKeyStruct *booleanIndexKeyStructTmp = (BooleanIndexKeyStruct *) (key.mv_data);
		unsigned char value1 = booleanIndexKeyStructTmp->value;
		if (value1 != value) {
			rc = MDB_NOTFOUND;
		}

	}

	free(booleanIndexKeyStruct);
	return rc;

}

int getCurrentVertexfromVertexBooleanIndexDb(MDB_cursor *cursor, jlong *vertexIdC, int propertyKeyId, jboolean value) {

	int rc = 0;
	MDB_val key, data;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_GET_CURRENT);

	if (rc == MDB_NOTFOUND) {
		rc = getNextElementForKeyValueFromBooleanIndex(cursor, propertyKeyId, value, (long long int *)vertexIdC);
	} else {
		*vertexIdC = *((long long *) data.mv_data);
	}

	return rc;
}
