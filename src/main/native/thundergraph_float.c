#include <stdlib.h>
#include "thundergraph_float.h"

void printFloatIndexDbRecord(MDB_val key, MDB_val data) {
	FloatIndexKeyStruct *floatIndexKeyStruct = (FloatIndexKeyStruct *) (key.mv_data);
	int propertyKeyId = floatIndexKeyStruct->propertyKeyId;
	float propertyKeyValue = floatIndexKeyStruct->value;
	long long elementIdKey = floatIndexKeyStruct->elementId;
	printf("propertyKeyId: %i, propertyKeyValue: %f, element id: %lld\n", propertyKeyId, propertyKeyValue, elementIdKey);
}

int setVertexPropertyFloat(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jfloat *propertyValue) {
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
		data.mv_size = sizeof(jlong);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int compareFloatIndexDbId(const MDB_val *key1, const MDB_val *key2) {
	FloatIndexKeyStruct *floatIndexKeyStruct1 = (FloatIndexKeyStruct *) (key1->mv_data);
	FloatIndexKeyStruct *floatIndexKeyStruct2 = (FloatIndexKeyStruct *) (key2->mv_data);
	int propertyKeyId1 = floatIndexKeyStruct1->propertyKeyId;
	int propertyKeyId2 = floatIndexKeyStruct2->propertyKeyId;
	if (propertyKeyId1 == propertyKeyId2) {
		float value1 = floatIndexKeyStruct1->value;
		float value2 = floatIndexKeyStruct2->value;
		if (value1 == value2) {
			long long elementId1 = floatIndexKeyStruct1->elementId;
			long long elementId2 = floatIndexKeyStruct2->elementId;
			return (elementId1 > elementId2) - (elementId1 < elementId2);
		} else {
			return (value1 > value2) - (value1 < value2);
		}
	} else {
		return (propertyKeyId1 > propertyKeyId2) - (propertyKeyId1 < propertyKeyId2);
	}
}

int getFirstElementForKeyValueFromFloatIndex(MDB_cursor *cursor, int propertyKeyId, float value, long long int *vertexIdResultC) {

	printf("getFirstElementForKeyValueFromFloatIndex propertyKeyId = %i", propertyKeyId);

	int rc;
	MDB_val key, data;
	FloatIndexKeyStruct *floatIndexKeyStruct = malloc(sizeof(FloatIndexKeyStruct));
	floatIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	floatIndexKeyStruct->value = value;
	floatIndexKeyStruct->elementId = -1LL;
	key.mv_size = sizeof(FloatIndexKeyStruct);
	key.mv_data = floatIndexKeyStruct;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {

		FloatIndexKeyStruct *floatIndexKeyStructTmp = (FloatIndexKeyStruct *) (key.mv_data);
		float value1 = floatIndexKeyStructTmp->value;

		printf("getFirstElementForKeyValueFromFloatIndex value1 = %f", value1);
		printf("getFirstElementForKeyValueFromFloatIndex value = %f", value);

		if (value == value1) {
			*vertexIdResultC = *((long long *) data.mv_data);
		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int getNextElementForKeyValueFromFloatIndex(MDB_cursor *cursor, int propertyKeyId, float value, long long int *vertexIdResultC) {

	int rc;
	MDB_val key, data;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT);
	if (rc == 0) {

		FloatIndexKeyStruct *floatIndexKeyStructTmp = (FloatIndexKeyStruct *) (key.mv_data);
		float value1 = floatIndexKeyStructTmp->value;
		if (value1 == value) {
			*vertexIdResultC = *((long long *) data.mv_data);
		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int traverseFloatIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi) {
	int rc = 0;
	MDB_cursor *cursor;
	MDB_val key, data;
	rc = mdb_cursor_open(txn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		printFloatIndexDbRecord(key, data);
	}
	fail: mdb_cursor_close(cursor);
	return rc;
}

int setFloatIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, float propertyValue) {
	int rc;
	MDB_val key, data;
	FloatIndexKeyStruct *floatIndexKeyStruct = malloc(sizeof(FloatIndexKeyStruct));
	floatIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	floatIndexKeyStruct->elementId = (long long) elementId;
	floatIndexKeyStruct->value = propertyValue;
	key.mv_size = sizeof(FloatIndexKeyStruct);
	key.mv_data = floatIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_put(indexCursor, &key, &data, 0);
	free(floatIndexKeyStruct);
	return rc;
}

int removeFloatIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, float propertyValue) {
	int rc;
	MDB_val key, data;
	FloatIndexKeyStruct *floatIndexKeyStruct = malloc(sizeof(FloatIndexKeyStruct));
	floatIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	floatIndexKeyStruct->elementId = (long long) elementId;
	floatIndexKeyStruct->value = propertyValue;
	key.mv_size = sizeof(FloatIndexKeyStruct);
	key.mv_data = floatIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_get(indexCursor, &key, &data, MDB_SET_KEY);
	if (rc == 0) {
		rc = mdb_cursor_del(indexCursor, 0);
	}
	free(floatIndexKeyStruct);
	return rc;
}

int addOrUpdateFloatIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId, int propertyKeyId,
		jfloat propertyValue, unsigned char vertex) {

	int rc;
	MDB_cursor *floatIndexCursor;
	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexFloatIndexDb, &floatIndexCursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeFloatIndexDb, &floatIndexCursor);
	}
	if (rc != 0) {
		goto failIndexedVertex;
	}
	rc = deleteEntryFromFloatIndex(glmdb_env, mdbTxn, vertexCursor, floatIndexCursor, (long long) elementId, (int) propertyKeyId);
	if (rc != 0 && rc != MDB_NOTFOUND) {
		goto failIndexedVertex;
	}
	rc = setVertexPropertyFloat(vertexCursor, (long) elementId, (int) propertyKeyId, &propertyValue);
	if (rc != 0) {
		goto failIndexedVertex;
	}

	rc = setFloatIndex(floatIndexCursor, elementId, propertyKeyId, propertyValue);

	failIndexedVertex: mdb_cursor_close(floatIndexCursor);
	return rc;
}

int deleteEntryFromFloatIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *floatIndexCursor,
		long long elementId, int propertyKeyId) {

	int rc;

	//Get the old value first
	MDB_val oldData;
	MDB_val key, data;
	rc = getVertexProperty(vertexCursor, elementId, propertyKeyId, &oldData);
	if (rc == 0) {
		//Delete the current indexed element
		FloatIndexKeyStruct *floatIndexKeyStruct = malloc(sizeof(FloatIndexKeyStruct));
		floatIndexKeyStruct->propertyKeyId = propertyKeyId;
		floatIndexKeyStruct->elementId = elementId;
		floatIndexKeyStruct->value = *((float *) oldData.mv_data);
		key.mv_size = sizeof(FloatIndexKeyStruct);
		key.mv_data = floatIndexKeyStruct;
		rc = mdb_cursor_get(floatIndexCursor, &key, &data, MDB_SET_KEY);
		if (rc != 0) {
			free(floatIndexKeyStruct);
			goto fail;
		}
		free(floatIndexKeyStruct);
		rc = mdb_cursor_del(floatIndexCursor, 0);
	}

	fail: return rc;
}

int setEdgePropertyFloat(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jfloat *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = EPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		key.mv_size = sizeof(EdgeDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jfloat);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int deleteFloatIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex) {
	int rc;
	MDB_cursor *cursor;

	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexFloatIndexDb, &cursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeFloatIndexDb, &cursor);
	}
	if (rc == 0) {
		MDB_val key, data;
		FloatIndexKeyStruct *floatIndexKeyStruct = malloc(sizeof(FloatIndexKeyStruct));
		floatIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
		floatIndexKeyStruct->elementId = -1LL;
		floatIndexKeyStruct->value = -1;

		key.mv_size = sizeof(FloatIndexKeyStruct);
		key.mv_data = floatIndexKeyStruct;

		while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE) == 0)) {

			FloatIndexKeyStruct *floatIndexKeyStructToDelete = (FloatIndexKeyStruct *) (key.mv_data);
			if (floatIndexKeyStructToDelete->propertyKeyId == propertyKeyId) {
				rc = mdb_cursor_del(cursor, 0);
				if (rc != 0) {
					break;
				} else {
					//reset the key
					floatIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
					floatIndexKeyStruct->elementId = -1LL;
					floatIndexKeyStruct->value = -1;
				}
			} else {
				break;
			}

		}
		free(floatIndexKeyStruct);
	}
	return rc;

}
