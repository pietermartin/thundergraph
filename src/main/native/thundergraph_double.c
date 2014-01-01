#include <stdlib.h>
#include "thundergraph_double.h"

void printDoubleIndexDbRecord(MDB_val key, MDB_val data) {
	DoubleIndexKeyStruct *doubleIndexKeyStruct = (DoubleIndexKeyStruct *) (key.mv_data);
	int propertyKeyId = doubleIndexKeyStruct->propertyKeyId;
	double propertyKeyValue = doubleIndexKeyStruct->value;
	long long elementIdKey = doubleIndexKeyStruct->elementId;
	printf("propertyKeyId: %i, propertyKeyValue: %e, element id: %lld\n", propertyKeyId, propertyKeyValue, elementIdKey);
}

int setVertexPropertyDouble(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jdouble *propertyValue) {
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
		data.mv_size = sizeof(jdouble);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int compareDoubleIndexDbId(const MDB_val *key1, const MDB_val *key2) {
	DoubleIndexKeyStruct *doubleIndexKeyStruct1 = (DoubleIndexKeyStruct *) (key1->mv_data);
	DoubleIndexKeyStruct *doubleIndexKeyStruct2 = (DoubleIndexKeyStruct *) (key2->mv_data);
	int propertyKeyId1 = doubleIndexKeyStruct1->propertyKeyId;
	int propertyKeyId2 = doubleIndexKeyStruct2->propertyKeyId;
	if (propertyKeyId1 == propertyKeyId2) {
		double value1 = doubleIndexKeyStruct1->value;
		double value2 = doubleIndexKeyStruct2->value;
		if (value1 == value2) {
			long long elementId1 = doubleIndexKeyStruct1->elementId;
			long long elementId2 = doubleIndexKeyStruct2->elementId;
			return (elementId1 > elementId2) - (elementId1 < elementId2);
		} else {
			return (value1 > value2) - (value1 < value2);
		}
	} else {
		return (propertyKeyId1 > propertyKeyId2) - (propertyKeyId1 < propertyKeyId2);
	}
}

int getFirstElementForKeyValueFromDoubleIndex(MDB_cursor *cursor, int propertyKeyId, double value, long long int *vertexIdResultC) {

	printf("getFirstElementForKeyValueFromDoubleIndex propertyKeyId = %i", propertyKeyId);

	int rc;
	MDB_val key, data;
	DoubleIndexKeyStruct *doubleIndexKeyStruct = malloc(sizeof(DoubleIndexKeyStruct));
	doubleIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	doubleIndexKeyStruct->value = value;
	doubleIndexKeyStruct->elementId = -1LL;
	key.mv_size = sizeof(DoubleIndexKeyStruct);
	key.mv_data = doubleIndexKeyStruct;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {

		DoubleIndexKeyStruct *doubleIndexKeyStructTmp = (DoubleIndexKeyStruct *) (key.mv_data);
		double value1 = doubleIndexKeyStructTmp->value;

		printf("getFirstElementForKeyValueFromDoubleIndex value1 = %f", value1);
		printf("getFirstElementForKeyValueFromDoubleIndex value = %f", value);

		if (value == value1) {
			*vertexIdResultC = *((long long *) data.mv_data);
		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int getNextElementForKeyValueFromDoubleIndex(MDB_cursor *cursor, int propertyKeyId, double value, long long int *vertexIdResultC) {

	int rc;
	MDB_val key, data;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT);
	if (rc == 0) {

		DoubleIndexKeyStruct *doubleIndexKeyStructTmp = (DoubleIndexKeyStruct *) (key.mv_data);
		double value1 = doubleIndexKeyStructTmp->value;
		if (value1 == value) {
			*vertexIdResultC = *((long long *) data.mv_data);
		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int traverseDoubleIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi) {
	int rc = 0;
	MDB_cursor *cursor;
	MDB_val key, data;
	rc = mdb_cursor_open(txn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		printDoubleIndexDbRecord(key, data);
	}
	fail: mdb_cursor_close(cursor);
	return rc;
}

int setDoubleIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, double propertyValue) {
	int rc;
	MDB_val key, data;
	DoubleIndexKeyStruct *doubleIndexKeyStruct = malloc(sizeof(DoubleIndexKeyStruct));
	doubleIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	doubleIndexKeyStruct->elementId = (long long) elementId;
	doubleIndexKeyStruct->value = propertyValue;
	key.mv_size = sizeof(DoubleIndexKeyStruct);
	key.mv_data = doubleIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_put(indexCursor, &key, &data, 0);
	free(doubleIndexKeyStruct);
	return rc;
}

int removeDoubleIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, double propertyValue) {
	int rc;
	MDB_val key, data;
	DoubleIndexKeyStruct *doubleIndexKeyStruct = malloc(sizeof(DoubleIndexKeyStruct));
	doubleIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	doubleIndexKeyStruct->elementId = (long long) elementId;
	doubleIndexKeyStruct->value = propertyValue;
	key.mv_size = sizeof(DoubleIndexKeyStruct);
	key.mv_data = doubleIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_get(indexCursor, &key, &data, MDB_SET_KEY);
	if (rc == 0) {
		rc = mdb_cursor_del(indexCursor, 0);
	}
	free(doubleIndexKeyStruct);
	return rc;
}

int addOrUpdateDoubleIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId, int propertyKeyId,
		jdouble propertyValue, unsigned char vertex) {

	int rc;
	MDB_cursor *doubleIndexCursor;
	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexDoubleIndexDb, &doubleIndexCursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeDoubleIndexDb, &doubleIndexCursor);
	}
	if (rc != 0) {
		goto failIndexedVertex;
	}
	rc = deleteEntryFromDoubleIndex(glmdb_env, mdbTxn, vertexCursor, doubleIndexCursor, (long long) elementId, (int) propertyKeyId);
	if (rc != 0 && rc != MDB_NOTFOUND) {
		goto failIndexedVertex;
	}
	rc = setVertexPropertyDouble(vertexCursor, (long) elementId, (int) propertyKeyId, &propertyValue);
	if (rc != 0) {
		goto failIndexedVertex;
	}

	rc = setDoubleIndex(doubleIndexCursor, elementId, propertyKeyId, propertyValue);

	failIndexedVertex: mdb_cursor_close(doubleIndexCursor);
	return rc;
}

int deleteEntryFromDoubleIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *doubleIndexCursor,
		long long elementId, int propertyKeyId) {

	int rc;

	//Get the old value first
	MDB_val oldData;
	MDB_val key, data;
	rc = getVertexProperty(vertexCursor, elementId, propertyKeyId, &oldData);
	if (rc == 0) {
		//Delete the current indexed element
		DoubleIndexKeyStruct *doubleIndexKeyStruct = malloc(sizeof(DoubleIndexKeyStruct));
		doubleIndexKeyStruct->propertyKeyId = propertyKeyId;
		doubleIndexKeyStruct->elementId = elementId;
		doubleIndexKeyStruct->value = *((double *) oldData.mv_data);
		key.mv_size = sizeof(DoubleIndexKeyStruct);
		key.mv_data = doubleIndexKeyStruct;
		rc = mdb_cursor_get(doubleIndexCursor, &key, &data, MDB_SET_KEY);
		if (rc != 0) {
			free(doubleIndexKeyStruct);
			goto fail;
		}
		free(doubleIndexKeyStruct);
		rc = mdb_cursor_del(doubleIndexCursor, 0);
	}

	fail: return rc;
}

int setEdgePropertyDouble(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jdouble *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = EPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		key.mv_size = sizeof(EdgeDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jdouble);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int deleteDoubleIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex) {
	int rc;
	MDB_cursor *cursor;

	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexDoubleIndexDb, &cursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeDoubleIndexDb, &cursor);
	}
	if (rc == 0) {
		MDB_val key, data;
		DoubleIndexKeyStruct *doubleIndexKeyStruct = malloc(sizeof(DoubleIndexKeyStruct));
		doubleIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
		doubleIndexKeyStruct->elementId = -1LL;
		doubleIndexKeyStruct->value = -1;

		key.mv_size = sizeof(DoubleIndexKeyStruct);
		key.mv_data = doubleIndexKeyStruct;

		while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE) == 0)) {

			DoubleIndexKeyStruct *doubleIndexKeyStructToDelete = (DoubleIndexKeyStruct *) (key.mv_data);
			if (doubleIndexKeyStructToDelete->propertyKeyId == propertyKeyId) {
				rc = mdb_cursor_del(cursor, 0);
				if (rc != 0) {
					break;
				} else {
					//reset the key
					doubleIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
					doubleIndexKeyStruct->elementId = -1LL;
					doubleIndexKeyStruct->value = -1;
				}
			} else {
				break;
			}

		}
		free(doubleIndexKeyStruct);
	}
	return rc;

}

int placeCursorOnKeyValueDoubleIndex(MDB_cursor *cursor, long long vertexId, int propertyKeyId, jdouble value) {

	int rc;
	MDB_val key, data;
	DoubleIndexKeyStruct *doubleIndexKeyStruct = malloc(sizeof(DoubleIndexKeyStruct));
	doubleIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	doubleIndexKeyStruct->elementId = -1LL;
	doubleIndexKeyStruct->elementId = vertexId;
	doubleIndexKeyStruct->value = value;
	key.mv_size = sizeof(DoubleIndexKeyStruct);
	key.mv_data = doubleIndexKeyStruct;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {

		DoubleIndexKeyStruct *doubleIndexKeyStructTmp = (DoubleIndexKeyStruct *) (key.mv_data);
		double value1 = doubleIndexKeyStructTmp->value;
		if (value1 != value) {
			rc = MDB_NOTFOUND;
		}

	}

	free(doubleIndexKeyStruct);
	return rc;

}

int getCurrentElementFromDoubleIndexDb(MDB_cursor *cursor, jlong *vertexIdC, int propertyKeyId, jdouble value) {

	int rc = 0;
	MDB_val key, data;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_GET_CURRENT);

	if (rc == MDB_NOTFOUND) {
		rc = getNextElementForKeyValueFromDoubleIndex(cursor, propertyKeyId, value, (long long int *)vertexIdC);
	} else {
		*vertexIdC = *((long long *) data.mv_data);
	}

	return rc;
}
