#include <stdlib.h>
#include "thundergraph_long.h"

void printLongIndexDbRecord(MDB_val key, MDB_val data) {
	LongIndexKeyStruct *longIndexKeyStruct = (LongIndexKeyStruct *) (key.mv_data);
	int propertyKeyId = longIndexKeyStruct->propertyKeyId;
	long long propertyKeyValue = longIndexKeyStruct->value;
	long long elementIdKey = longIndexKeyStruct->elementId;
	printf("propertyKeyId: %i, propertyKeyValue: %lld, element id: %lld\n", propertyKeyId, propertyKeyValue, elementIdKey);
}

int setVertexPropertyLong(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jlong *propertyValue) {
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

int compareLongIndexDbId(const MDB_val *key1, const MDB_val *key2) {
	LongIndexKeyStruct *longIndexKeyStruct1 = (LongIndexKeyStruct *) (key1->mv_data);
	LongIndexKeyStruct *longIndexKeyStruct2 = (LongIndexKeyStruct *) (key2->mv_data);
	int propertyKeyId1 = longIndexKeyStruct1->propertyKeyId;
	int propertyKeyId2 = longIndexKeyStruct2->propertyKeyId;
	if (propertyKeyId1 == propertyKeyId2) {
		long long value1 = longIndexKeyStruct1->value;
		long long value2 = longIndexKeyStruct2->value;
		if (value1 == value2) {
			long long elementId1 = longIndexKeyStruct1->elementId;
			long long elementId2 = longIndexKeyStruct2->elementId;
			return (elementId1 > elementId2) - (elementId1 < elementId2);
		} else {
			return (value1 > value2) - (value1 < value2);
		}
	} else {
		return (propertyKeyId1 > propertyKeyId2) - (propertyKeyId1 < propertyKeyId2);
	}
}

int getFirstElementForKeyValueFromLongIndex(MDB_cursor *cursor, int propertyKeyId, long long value, long long int *vertexIdResultC) {

	int rc;
	MDB_val key, data;
	LongIndexKeyStruct *longIndexKeyStruct = malloc(sizeof(LongIndexKeyStruct));
	longIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	longIndexKeyStruct->value = value;
	longIndexKeyStruct->elementId = -1LL;
	key.mv_size = sizeof(LongIndexKeyStruct);
	key.mv_data = longIndexKeyStruct;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {

		LongIndexKeyStruct *longIndexKeyStructTmp = (LongIndexKeyStruct *) (key.mv_data);
		long long value1 = longIndexKeyStructTmp->value;

		if (value == value1) {
			*vertexIdResultC = *((long long *) data.mv_data);
		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int getNextElementForKeyValueFromLongIndex(MDB_cursor *cursor, int propertyKeyId, long long value, long long int *vertexIdResultC) {

	int rc;
	MDB_val key, data;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT);
	if (rc == 0) {

		LongIndexKeyStruct *longIndexKeyStructTmp = (LongIndexKeyStruct *) (key.mv_data);
		long long value1 = longIndexKeyStructTmp->value;
		if (value1 == value) {
			*vertexIdResultC = *((long long *) data.mv_data);
		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int traverseLongIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi) {
	int rc = 0;
	MDB_cursor *cursor;
	MDB_val key, data;
	rc = mdb_cursor_open(txn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		printLongIndexDbRecord(key, data);
	}
	fail: mdb_cursor_close(cursor);
	return rc;
}

int setLongIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, long long propertyValue) {
	int rc;
	MDB_val key, data;
	LongIndexKeyStruct *longIndexKeyStruct = malloc(sizeof(LongIndexKeyStruct));
	longIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	longIndexKeyStruct->elementId = (long long) elementId;
	longIndexKeyStruct->value = propertyValue;
	key.mv_size = sizeof(LongIndexKeyStruct);
	key.mv_data = longIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_put(indexCursor, &key, &data, 0);
	free(longIndexKeyStruct);
	return rc;
}

int removeLongIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, long long propertyValue) {
	int rc;
	MDB_val key, data;
	LongIndexKeyStruct *longIndexKeyStruct = malloc(sizeof(LongIndexKeyStruct));
	longIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	longIndexKeyStruct->elementId = (long long) elementId;
	longIndexKeyStruct->value = propertyValue;
	key.mv_size = sizeof(LongIndexKeyStruct);
	key.mv_data = longIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_get(indexCursor, &key, &data, MDB_SET_KEY);
	if (rc == 0) {
		rc = mdb_cursor_del(indexCursor, 0);
	}
	free(longIndexKeyStruct);
	return rc;
}

int addOrUpdateLongIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId, int propertyKeyId,
		jlong propertyValue, unsigned char vertex) {

	int rc;
	MDB_cursor *longIndexCursor;
	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexLongIndexDb, &longIndexCursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeLongIndexDb, &longIndexCursor);
	}
	if (rc != 0) {
		goto failIndexedVertex;
	}
	rc = deleteEntryFromLongIndex(glmdb_env, mdbTxn, vertexCursor, longIndexCursor, (long long) elementId, (int) propertyKeyId);
	if (rc != 0 && rc != MDB_NOTFOUND) {
		goto failIndexedVertex;
	}
	rc = setVertexPropertyLong(vertexCursor, (long) elementId, (int) propertyKeyId, &propertyValue);
	if (rc != 0) {
		goto failIndexedVertex;
	}

	rc = setLongIndex(longIndexCursor, elementId, propertyKeyId, propertyValue);

	failIndexedVertex: mdb_cursor_close(longIndexCursor);
	return rc;
}

int deleteEntryFromLongIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *longIndexCursor,
		long long elementId, int propertyKeyId) {

	int rc;

	//Get the old value first
	MDB_val oldData;
	MDB_val key, data;
	rc = getVertexProperty(vertexCursor, elementId, propertyKeyId, &oldData);
	if (rc == 0) {
		//Delete the current indexed element
		LongIndexKeyStruct *longIndexKeyStruct = malloc(sizeof(LongIndexKeyStruct));
		longIndexKeyStruct->propertyKeyId = propertyKeyId;
		longIndexKeyStruct->elementId = elementId;
		longIndexKeyStruct->value = *((int *) oldData.mv_data);
		key.mv_size = sizeof(LongIndexKeyStruct);
		key.mv_data = longIndexKeyStruct;
		rc = mdb_cursor_get(longIndexCursor, &key, &data, MDB_SET_KEY);
		if (rc != 0) {
			free(longIndexKeyStruct);
			goto fail;
		}
		free(longIndexKeyStruct);
		rc = mdb_cursor_del(longIndexCursor, 0);
	}

	fail: return rc;
}

int setEdgePropertyLong(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jlong *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = EPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		key.mv_size = sizeof(EdgeDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jlong);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int deleteLongIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex) {
	int rc;
	MDB_cursor *cursor;

	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexLongIndexDb, &cursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeLongIndexDb, &cursor);
	}
	if (rc == 0) {
		MDB_val key, data;
		LongIndexKeyStruct *longIndexKeyStruct = malloc(sizeof(LongIndexKeyStruct));
		longIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
		longIndexKeyStruct->elementId = -1LL;
		longIndexKeyStruct->value = -1LL;

		key.mv_size = sizeof(LongIndexKeyStruct);
		key.mv_data = longIndexKeyStruct;

		while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE) == 0)) {

			LongIndexKeyStruct *longIndexKeyStructToDelete = (LongIndexKeyStruct *) (key.mv_data);
			if (longIndexKeyStructToDelete->propertyKeyId == propertyKeyId) {
				rc = mdb_cursor_del(cursor, 0);
				if (rc != 0) {
					break;
				} else {
					//reset the key
					longIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
					longIndexKeyStruct->elementId = -1LL;
					longIndexKeyStruct->value = -1LL;
				}
			} else {
				break;
			}

		}
		free(longIndexKeyStruct);
	}
	return rc;

}

int placeCursorOnKeyValueLongIndex(MDB_cursor *cursor, long long vertexId, int propertyKeyId, jlong value) {

	int rc;
	MDB_val key, data;
	LongIndexKeyStruct *longIndexKeyStruct = malloc(sizeof(LongIndexKeyStruct));
	longIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	longIndexKeyStruct->elementId = -1LL;
	longIndexKeyStruct->elementId = vertexId;
	longIndexKeyStruct->value = value;
	key.mv_size = sizeof(LongIndexKeyStruct);
	key.mv_data = longIndexKeyStruct;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {

		LongIndexKeyStruct *longIndexKeyStructTmp = (LongIndexKeyStruct *) (key.mv_data);
		long long value1 = longIndexKeyStructTmp->value;
		if (value1 != value) {
			rc = MDB_NOTFOUND;
		}

	}

	free(longIndexKeyStruct);
	return rc;

}

int getCurrentElementFromLongIndexDb(MDB_cursor *cursor, jlong *vertexIdC, int propertyKeyId, jlong value) {

	int rc = 0;
	MDB_val key, data;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_GET_CURRENT);

	if (rc == MDB_NOTFOUND) {
		rc = getNextElementForKeyValueFromLongIndex(cursor, propertyKeyId, value, (long long int *)vertexIdC);
	} else {
		*vertexIdC = *((long long *) data.mv_data);
	}

	return rc;
}
