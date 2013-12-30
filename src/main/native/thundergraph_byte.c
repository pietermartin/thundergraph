#include <stdlib.h>
#include "thundergraph_byte.h"

void printByteIndexDbRecord(MDB_val key, MDB_val data) {
	ByteIndexKeyStruct *byteIndexKeyStruct = (ByteIndexKeyStruct *) (key.mv_data);
	int propertyKeyId = byteIndexKeyStruct->propertyKeyId;
	signed char propertyKeyValue = byteIndexKeyStruct->value;
	long long elementIdKey = byteIndexKeyStruct->elementId;
	printf("propertyKeyId: %i, propertyKeyValue: %hu, element id: %lld\n", propertyKeyId, propertyKeyValue, elementIdKey);
}

int setVertexPropertyByte(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jbyte *propertyValue) {
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
		data.mv_size = sizeof(jbyte);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int compareByteIndexDbId(const MDB_val *key1, const MDB_val *key2) {
	ByteIndexKeyStruct *byteIndexKeyStruct1 = (ByteIndexKeyStruct *) (key1->mv_data);
	ByteIndexKeyStruct *byteIndexKeyStruct2 = (ByteIndexKeyStruct *) (key2->mv_data);
	int propertyKeyId1 = byteIndexKeyStruct1->propertyKeyId;
	int propertyKeyId2 = byteIndexKeyStruct2->propertyKeyId;
	if (propertyKeyId1 == propertyKeyId2) {
		signed char value1 = byteIndexKeyStruct1->value;
		signed char value2 = byteIndexKeyStruct2->value;
		if (value1 == value2) {
			long long elementId1 = byteIndexKeyStruct1->elementId;
			long long elementId2 = byteIndexKeyStruct2->elementId;
			return (elementId1 > elementId2) - (elementId1 < elementId2);
		} else {
			return (value1 > value2) - (value1 < value2);
		}
	} else {
		return (propertyKeyId1 > propertyKeyId2) - (propertyKeyId1 < propertyKeyId2);
	}
}

int getFirstElementForKeyValueFromByteIndex(MDB_cursor *cursor, int propertyKeyId, signed char value, long long int *vertexIdResultC) {

	int rc;
	MDB_val key, data;
	ByteIndexKeyStruct *byteIndexKeyStruct = malloc(sizeof(ByteIndexKeyStruct));
	byteIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	byteIndexKeyStruct->value = value;
	byteIndexKeyStruct->elementId = -1LL;
	key.mv_size = sizeof(ByteIndexKeyStruct);
	key.mv_data = byteIndexKeyStruct;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {

		ByteIndexKeyStruct *byteIndexKeyStructTmp = (ByteIndexKeyStruct *) (key.mv_data);
		signed char value1 = byteIndexKeyStructTmp->value;

		if (value == value1) {
			*vertexIdResultC = *((long long *) data.mv_data);
		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int getNextElementForKeyValueFromByteIndex(MDB_cursor *cursor, int propertyKeyId, signed char value, long long int *vertexIdResultC) {

	int rc;
	MDB_val key, data;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT);
	if (rc == 0) {

		ByteIndexKeyStruct *byteIndexKeyStructTmp = (ByteIndexKeyStruct *) (key.mv_data);
		signed char value1 = byteIndexKeyStructTmp->value;
		if (value1 == value) {
			*vertexIdResultC = *((long long *) data.mv_data);
		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int traverseByteIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi) {
	int rc = 0;
	MDB_cursor *cursor;
	MDB_val key, data;
	rc = mdb_cursor_open(txn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		printByteIndexDbRecord(key, data);
	}
	fail: mdb_cursor_close(cursor);
	return rc;
}

int setByteIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, signed char propertyValue) {
	int rc;
	MDB_val key, data;
	ByteIndexKeyStruct *byteIndexKeyStruct = malloc(sizeof(ByteIndexKeyStruct));
	byteIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	byteIndexKeyStruct->elementId = (long long) elementId;
	byteIndexKeyStruct->value = propertyValue;
	key.mv_size = sizeof(ByteIndexKeyStruct);
	key.mv_data = byteIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_put(indexCursor, &key, &data, 0);
	free(byteIndexKeyStruct);
	return rc;
}

int removeByteIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, signed char propertyValue) {
	int rc;
	MDB_val key, data;
	ByteIndexKeyStruct *byteIndexKeyStruct = malloc(sizeof(ByteIndexKeyStruct));
	byteIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	byteIndexKeyStruct->elementId = (long long) elementId;
	byteIndexKeyStruct->value = propertyValue;
	key.mv_size = sizeof(ByteIndexKeyStruct);
	key.mv_data = byteIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_get(indexCursor, &key, &data, MDB_SET_KEY);
	if (rc == 0) {
		rc = mdb_cursor_del(indexCursor, 0);
	}
	free(byteIndexKeyStruct);
	return rc;
}

int addOrUpdateByteIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId, int propertyKeyId,
		jbyte propertyValue, unsigned char vertex) {

	int rc;
	MDB_cursor *byteIndexCursor;
	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexByteIndexDb, &byteIndexCursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeByteIndexDb, &byteIndexCursor);
	}
	if (rc != 0) {
		goto failIndexedVertex;
	}
	rc = deleteEntryFromByteIndex(glmdb_env, mdbTxn, vertexCursor, byteIndexCursor, (long long) elementId, (int) propertyKeyId);
	if (rc != 0 && rc != MDB_NOTFOUND) {
		goto failIndexedVertex;
	}
	rc = setVertexPropertyByte(vertexCursor, (long) elementId, (int) propertyKeyId, &propertyValue);
	if (rc != 0) {
		goto failIndexedVertex;
	}

	rc = setByteIndex(byteIndexCursor, elementId, propertyKeyId, propertyValue);

	failIndexedVertex: mdb_cursor_close(byteIndexCursor);
	return rc;
}

int deleteEntryFromByteIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *byteIndexCursor,
		long long elementId, int propertyKeyId) {

	int rc;

	//Get the old value first
	MDB_val oldData;
	MDB_val key, data;
	rc = getVertexProperty(vertexCursor, elementId, propertyKeyId, &oldData);
	if (rc == 0) {
		//Delete the current indexed element
		ByteIndexKeyStruct *byteIndexKeyStruct = malloc(sizeof(ByteIndexKeyStruct));
		byteIndexKeyStruct->propertyKeyId = propertyKeyId;
		byteIndexKeyStruct->elementId = elementId;
		byteIndexKeyStruct->value = *((signed char *) oldData.mv_data);
		key.mv_size = sizeof(ByteIndexKeyStruct);
		key.mv_data = byteIndexKeyStruct;
		rc = mdb_cursor_get(byteIndexCursor, &key, &data, MDB_SET_KEY);
		if (rc != 0) {
			free(byteIndexKeyStruct);
			goto fail;
		}
		free(byteIndexKeyStruct);
		rc = mdb_cursor_del(byteIndexCursor, 0);
	}

	fail: return rc;
}

int setEdgePropertyByte(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jbyte *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = EPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		key.mv_size = sizeof(EdgeDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jbyte);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int deleteByteIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex) {
	int rc;
	MDB_cursor *cursor;

	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexByteIndexDb, &cursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeByteIndexDb, &cursor);
	}
	if (rc == 0) {
		MDB_val key, data;
		ByteIndexKeyStruct *byteIndexKeyStruct = malloc(sizeof(ByteIndexKeyStruct));
		byteIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
		byteIndexKeyStruct->elementId = -1LL;
		byteIndexKeyStruct->value = -1;

		key.mv_size = sizeof(ByteIndexKeyStruct);
		key.mv_data = byteIndexKeyStruct;

		while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE) == 0)) {

			ByteIndexKeyStruct *byteIndexKeyStructToDelete = (ByteIndexKeyStruct *) (key.mv_data);
			if (byteIndexKeyStructToDelete->propertyKeyId == propertyKeyId) {
				rc = mdb_cursor_del(cursor, 0);
				if (rc != 0) {
					break;
				} else {
					//reset the key
					byteIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
					byteIndexKeyStruct->elementId = -1LL;
					byteIndexKeyStruct->value = -1;
				}
			} else {
				break;
			}

		}
		free(byteIndexKeyStruct);
	}
	return rc;

}

int placeCursorOnKeyValueByteIndex(MDB_cursor *cursor, long long vertexId, int propertyKeyId, jbyte value) {

	int rc;
	MDB_val key, data;
	ByteIndexKeyStruct *byteIndexKeyStruct = malloc(sizeof(ByteIndexKeyStruct));
	byteIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	byteIndexKeyStruct->elementId = -1LL;
	byteIndexKeyStruct->elementId = vertexId;
	byteIndexKeyStruct->value = value;
	key.mv_size = sizeof(ByteIndexKeyStruct);
	key.mv_data = byteIndexKeyStruct;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {

		ByteIndexKeyStruct *byteIndexKeyStructTmp = (ByteIndexKeyStruct *) (key.mv_data);
		signed char value1 = byteIndexKeyStructTmp->value;
		if (value1 != value) {
			rc = MDB_NOTFOUND;
		}

	}

	free(byteIndexKeyStruct);
	return rc;

}

int getCurrentVertexfromVertexByteIndexDb(MDB_cursor *cursor, jlong *vertexIdC, int propertyKeyId, jbyte value) {

	int rc = 0;
	MDB_val key, data;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_GET_CURRENT);

	if (rc == MDB_NOTFOUND) {
		rc = getNextElementForKeyValueFromByteIndex(cursor, propertyKeyId, value, (long long int *)vertexIdC);
	} else {
		*vertexIdC = *((long long *) data.mv_data);
	}

	return rc;
}
