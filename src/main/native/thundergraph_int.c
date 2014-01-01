#include <stdlib.h>
#include "thundergraph_int.h"

void printIntIndexDbRecord(MDB_val key, MDB_val data) {
	IntIndexKeyStruct *intIndexKeyStruct = (IntIndexKeyStruct *) (key.mv_data);
	int propertyKeyId = intIndexKeyStruct->propertyKeyId;
	int propertyKeyValue = intIndexKeyStruct->value;
	long long elementIdKey = intIndexKeyStruct->elementId;
	printf("propertyKeyId: %i, propertyKeyValue: %i, element id: %lld\n", propertyKeyId, propertyKeyValue, elementIdKey);
}

int setVertexPropertyInt(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jint *propertyValue) {
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
		data.mv_size = sizeof(jint);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int compareIntIndexDbId(const MDB_val *key1, const MDB_val *key2) {
	IntIndexKeyStruct *intIndexKeyStruct1 = (IntIndexKeyStruct *) (key1->mv_data);
	IntIndexKeyStruct *intIndexKeyStruct2 = (IntIndexKeyStruct *) (key2->mv_data);
	int propertyKeyId1 = intIndexKeyStruct1->propertyKeyId;
	int propertyKeyId2 = intIndexKeyStruct2->propertyKeyId;
	if (propertyKeyId1 == propertyKeyId2) {
		int value1 = intIndexKeyStruct1->value;
		int value2 = intIndexKeyStruct2->value;
		if (value1 == value2) {
			long long elementId1 = intIndexKeyStruct1->elementId;
			long long elementId2 = intIndexKeyStruct2->elementId;
			return (elementId1 > elementId2) - (elementId1 < elementId2);
		} else {
			return (value1 > value2) - (value1 < value2);
		}
	} else {
		return (propertyKeyId1 > propertyKeyId2) - (propertyKeyId1 < propertyKeyId2);
	}
}

int getFirstElementForKeyValueFromIntIndex(MDB_cursor *cursor, int propertyKeyId, int value, long long int *vertexIdResultC) {

	int rc;
	MDB_val key, data;
	IntIndexKeyStruct *intIndexKeyStruct = malloc(sizeof(IntIndexKeyStruct));
	intIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	intIndexKeyStruct->value = value;
	intIndexKeyStruct->elementId = -1LL;
	key.mv_size = sizeof(IntIndexKeyStruct);
	key.mv_data = intIndexKeyStruct;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {

		IntIndexKeyStruct *intIndexKeyStructTmp = (IntIndexKeyStruct *) (key.mv_data);
		int value1 = intIndexKeyStructTmp->value;
		if (value == value1) {
			*vertexIdResultC = *((long long *) data.mv_data);
		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int getNextElementForKeyValueFromIntIndex(MDB_cursor *cursor, int propertyKeyId, int value, long long int *vertexIdResultC) {

	int rc;
	MDB_val key, data;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT);
	if (rc == 0) {

		IntIndexKeyStruct *intIndexKeyStructTmp = (IntIndexKeyStruct *) (key.mv_data);
		int value1 = intIndexKeyStructTmp->value;
		if (value1 == value) {
			*vertexIdResultC = *((long long *) data.mv_data);
		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int traverseIntIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi) {
	int rc = 0;
	MDB_cursor *cursor;
	MDB_val key, data;
	rc = mdb_cursor_open(txn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		printIntIndexDbRecord(key, data);
	}
	fail: mdb_cursor_close(cursor);
	return rc;
}

int setIntIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, int propertyValue) {
	int rc;
	MDB_val key, data;
	IntIndexKeyStruct *intIndexKeyStruct = malloc(sizeof(IntIndexKeyStruct));
	intIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	intIndexKeyStruct->elementId = (long long) elementId;
	intIndexKeyStruct->value = propertyValue;
	key.mv_size = sizeof(IntIndexKeyStruct);
	key.mv_data = intIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_put(indexCursor, &key, &data, 0);
	free(intIndexKeyStruct);
	return rc;
}

int removeIntIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, int propertyValue) {
	int rc;
	MDB_val key, data;
	IntIndexKeyStruct *intIndexKeyStruct = malloc(sizeof(IntIndexKeyStruct));
	intIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	intIndexKeyStruct->elementId = (long long) elementId;
	intIndexKeyStruct->value = propertyValue;
	key.mv_size = sizeof(IntIndexKeyStruct);
	key.mv_data = intIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_get(indexCursor, &key, &data, MDB_SET_KEY);
	if (rc == 0) {
		rc = mdb_cursor_del(indexCursor, 0);
	}
	free(intIndexKeyStruct);
	return rc;
}

int addOrUpdateIntIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId, int propertyKeyId,
		int propertyValue, unsigned char vertex) {

	int rc;
	MDB_cursor *intIndexCursor;
	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexIntIndexDb, &intIndexCursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeIntIndexDb, &intIndexCursor);
	}
	if (rc != 0) {
		goto failIndexedVertex;
	}
	rc = deleteEntryFromIntIndex(glmdb_env, mdbTxn, vertexCursor, intIndexCursor, (long long) elementId, (int) propertyKeyId);
	if (rc != 0 && rc != MDB_NOTFOUND) {
		goto failIndexedVertex;
	}
	rc = setVertexPropertyInt(vertexCursor, (long) elementId, (int) propertyKeyId, &propertyValue);
	if (rc != 0) {
		goto failIndexedVertex;
	}

	rc = setIntIndex(intIndexCursor, elementId, propertyKeyId, propertyValue);

	failIndexedVertex: mdb_cursor_close(intIndexCursor);
	return rc;
}

int deleteEntryFromIntIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *intIndexCursor,
		long long elementId, int propertyKeyId) {

	int rc;

	//Get the old value first
	MDB_val oldData;
	MDB_val key, data;
	rc = getVertexProperty(vertexCursor, elementId, propertyKeyId, &oldData);
	if (rc == 0) {
		//Delete the current indexed element
		IntIndexKeyStruct *intIndexKeyStruct = malloc(sizeof(IntIndexKeyStruct));
		intIndexKeyStruct->propertyKeyId = propertyKeyId;
		intIndexKeyStruct->elementId = elementId;
		intIndexKeyStruct->value = *((int *) oldData.mv_data);
		key.mv_size = sizeof(IntIndexKeyStruct);
		key.mv_data = intIndexKeyStruct;
		rc = mdb_cursor_get(intIndexCursor, &key, &data, MDB_SET_KEY);
		if (rc != 0) {
			free(intIndexKeyStruct);
			goto fail;
		}
		free(intIndexKeyStruct);
		rc = mdb_cursor_del(intIndexCursor, 0);
	}

	fail: return rc;
}

int setEdgePropertyInt(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jint *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = EPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		key.mv_size = sizeof(EdgeDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jint);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int deleteIntIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex) {
	int rc;
	MDB_cursor *cursor;

	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexIntIndexDb, &cursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeIntIndexDb, &cursor);
	}
	if (rc == 0) {
		MDB_val key, data;
		IntIndexKeyStruct *intIndexKeyStruct = malloc(sizeof(IntIndexKeyStruct));
		intIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
		intIndexKeyStruct->elementId = -1LL;
		intIndexKeyStruct->value = -1;

		key.mv_size = sizeof(IntIndexKeyStruct);
		key.mv_data = intIndexKeyStruct;

		while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE) == 0)) {

			IntIndexKeyStruct *intIndexKeyStructToDelete = (IntIndexKeyStruct *) (key.mv_data);
			if (intIndexKeyStructToDelete->propertyKeyId == propertyKeyId) {
				rc = mdb_cursor_del(cursor, 0);
				if (rc != 0) {
					break;
				} else {
					//reset the key
					intIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
					intIndexKeyStruct->elementId = -1LL;
					intIndexKeyStruct->value = -1;
				}
			} else {
				break;
			}

		}
		free(intIndexKeyStruct);
	}
	return rc;

}

int placeCursorOnKeyValueIntIndex(MDB_cursor *cursor, long long vertexId, int propertyKeyId, jint value) {

	int rc;
	MDB_val key, data;
	IntIndexKeyStruct *intIndexKeyStruct = malloc(sizeof(IntIndexKeyStruct));
	intIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	intIndexKeyStruct->elementId = -1LL;
	intIndexKeyStruct->elementId = vertexId;
	intIndexKeyStruct->value = value;
	key.mv_size = sizeof(IntIndexKeyStruct);
	key.mv_data = intIndexKeyStruct;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {

		IntIndexKeyStruct *intIndexKeyStructTmp = (IntIndexKeyStruct *) (key.mv_data);
		int value1 = intIndexKeyStructTmp->value;
		if (value1 != value) {
			rc = MDB_NOTFOUND;
		}

	}

	free(intIndexKeyStruct);
	return rc;

}

int getCurrentElementFromIntIndexDb(MDB_cursor *cursor, jlong *vertexIdC, int propertyKeyId, jint value) {

	int rc = 0;
	MDB_val key, data;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_GET_CURRENT);

	if (rc == MDB_NOTFOUND) {
		rc = getNextElementForKeyValueFromIntIndex(cursor, propertyKeyId, value, (long long int *)vertexIdC);
	} else {
		*vertexIdC = *((long long *) data.mv_data);
	}

	return rc;
}
