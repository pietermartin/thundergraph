#include <stdlib.h>
#include "thundergraph_string.h"

int setVertexPropertyString(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jint propertyValueLength, char *propertyValue) {
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

		data.mv_size = propertyValueLength;
		data.mv_data = propertyValue;

		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int compareStringIndexDbId(const MDB_val *key1, const MDB_val *key2) {
	int propertyKey1Size = (size_t) key1->mv_size;
	int propertyKey2Size = (size_t) key2->mv_size;
	int propertyKey1ValueSize = propertyKey1Size - sizeof(StringIndexKeyStruct);
	int propertyKey2ValueSize = propertyKey2Size - sizeof(StringIndexKeyStruct);
	StringIndexKeyStruct *stringIndexKeyStruct1 = (StringIndexKeyStruct *) (key1->mv_data);
	StringIndexKeyStruct *stringIndexKeyStruct2 = (StringIndexKeyStruct *) (key2->mv_data);
	int propertyKeyId1 = stringIndexKeyStruct1->propertyKeyId;
	int propertyKeyId2 = stringIndexKeyStruct2->propertyKeyId;
	if (propertyKeyId1 == propertyKeyId2) {

		if (propertyKey1ValueSize == propertyKey2ValueSize) {

			char *value1 = stringIndexKeyStruct1->value;
			char *value2 = stringIndexKeyStruct2->value;

			int compare = strncmp(value1, value2, propertyKey1ValueSize);
			if (compare == 0) {
				long long elementId1 = stringIndexKeyStruct1->elementId;
				long long elementId2 = stringIndexKeyStruct2->elementId;
				return (elementId1 > elementId2) - (elementId1 < elementId2);
			} else {
				return compare;
			}
		} else {
			int compare = (propertyKey1ValueSize > propertyKey2ValueSize) - (propertyKey1ValueSize < propertyKey2ValueSize);
			return compare;
		}

	} else {
		return (propertyKeyId1 > propertyKeyId2) - (propertyKeyId1 < propertyKeyId2);
	}
}

int getFirstElementForKeyValueFromStringIndex(MDB_cursor *cursor, int propertyKeyId, int propertyValueLength, char *value,
		long long int *vertexIdResultC) {

	int rc;
	MDB_val key, data;
	StringIndexKeyStruct *stringIndexKeyStruct = malloc(sizeof(StringIndexKeyStruct) + propertyValueLength);
	stringIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	stringIndexKeyStruct->elementId = -1LL;
	memcpy(stringIndexKeyStruct->value, value, propertyValueLength);
	key.mv_size = propertyValueLength + sizeof(StringIndexKeyStruct);
	key.mv_data = stringIndexKeyStruct;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {

		int propertyKeySize = (size_t) key.mv_size;
		int propertyKeyInIndexValueSize = propertyKeySize - sizeof(StringIndexKeyStruct);

		if (propertyKeyInIndexValueSize == propertyValueLength) {

			StringIndexKeyStruct *stringIndexKeyStructTmp = (StringIndexKeyStruct *) (key.mv_data);
			char *value1 = stringIndexKeyStructTmp->value;
			int compare = strncmp(value1, value, propertyValueLength);
			if (compare == 0) {
				*vertexIdResultC = *((long long *) data.mv_data);
			} else {
				rc = MDB_NOTFOUND;
			}

		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int getNextElementForKeyValueFromStringIndex(MDB_cursor *cursor, int propertyKeyId, int propertyValueLength, char *value,
		long long int *vertexIdResultC) {

	int rc;
	MDB_val key, data;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT);
	if (rc == 0) {

		int propertyKeySize = (size_t) key.mv_size;
		int propertyKeyInIndexValueSize = propertyKeySize - sizeof(StringIndexKeyStruct);

		if (propertyKeyInIndexValueSize == propertyValueLength) {

			StringIndexKeyStruct *stringIndexKeyStructTmp = (StringIndexKeyStruct *) (key.mv_data);
			char *value1 = stringIndexKeyStructTmp->value;
			int compare = strncmp(value1, value, propertyValueLength);
			if (compare == 0) {
				*vertexIdResultC = *((long long *) data.mv_data);
			} else {
				rc = MDB_NOTFOUND;
			}

		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int traverseStringIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi) {
	int rc = 0;
	MDB_cursor *cursor;
	MDB_val key, data;
	rc = mdb_cursor_open(txn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		printStringIndexDbRecord(key, data);
	}
	fail: mdb_cursor_close(cursor);
	return rc;
}

int setStringIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, int propertyValueLength, char propertyValue[]) {
	int rc;
	MDB_val key, data;
	StringIndexKeyStruct *stringIndexKeyStruct = malloc(sizeof(StringIndexKeyStruct) + propertyValueLength);
	stringIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	stringIndexKeyStruct->elementId = (long long) elementId;
	memcpy(stringIndexKeyStruct->value, propertyValue, propertyValueLength);
	key.mv_size = propertyValueLength + sizeof(StringIndexKeyStruct);
	key.mv_data = stringIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_put(indexCursor, &key, &data, 0);
	free(stringIndexKeyStruct);
	return rc;
}

int removeStringIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, int propertyValueLength, char propertyValue[]) {
	int rc;
	MDB_val key, data;
	StringIndexKeyStruct *stringIndexKeyStruct = malloc(sizeof(StringIndexKeyStruct) + propertyValueLength);
	stringIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	stringIndexKeyStruct->elementId = (long long) elementId;
	memcpy(stringIndexKeyStruct->value, propertyValue, propertyValueLength);
	key.mv_size = propertyValueLength + sizeof(StringIndexKeyStruct);
	key.mv_data = stringIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_get(indexCursor, &key, &data, MDB_SET_KEY);
	if (rc == 0) {
		rc = mdb_cursor_del(indexCursor, 0);
	}
	free(stringIndexKeyStruct);
	return rc;
}

void printStringIndexDbRecord(MDB_val key, MDB_val data) {
	int keySize = ((size_t) key.mv_size);
	StringIndexKeyStruct *stringIndexKeyStruct = (StringIndexKeyStruct *) (key.mv_data);
	int propertyKeyValueSize = keySize - sizeof(StringIndexKeyStruct);
	int propertyKeyId = stringIndexKeyStruct->propertyKeyId;
	char *propertyKeyValue = stringIndexKeyStruct->value;
	long long elementIdKey = stringIndexKeyStruct->elementId;
	printf("propertyKeyId: %i, propertyKeyValue: %.*s, element id: %lld\n", propertyKeyId, propertyKeyValueSize, propertyKeyValue,
			elementIdKey);
}

int setEdgePropertyString(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jint propertyValueLength, char *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = ECORE;
		id.propertykeyId = propertyKeyId;
		key.mv_size = sizeof(EdgeDbId);
		key.mv_data = &id;
		data.mv_size = propertyValueLength;
		data.mv_data = propertyValue;

		int rc = mdb_cursor_get(cursor, &key, &data, MDB_SET);
		if (rc == 0) {
			id.coreOrPropertyEnum = EPROPERTY_KEY;
			key.mv_size = sizeof(EdgeDbId);
			key.mv_data = &id;
			data.mv_size = propertyValueLength;
			data.mv_data = propertyValue;
			return mdb_cursor_put(cursor, &key, &data, 0);
		} else {
			return GLMDB_DB_INVALID_EDGE;
		}
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int addOrUpdateStringIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId,
		int propertyKeyId, int propertyValueLength, char *propertyValue, unsigned char vertex) {

	int rc;
	MDB_cursor *stringIndexCursor;
	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexStringIndexDb, &stringIndexCursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeStringIndexDb, &stringIndexCursor);
	}
	if (rc != 0) {
		goto failIndexedVertex;
	}
	rc = deleteEntryFromStringIndex(glmdb_env, mdbTxn, vertexCursor, stringIndexCursor, (long long) elementId, (int) propertyKeyId);
	if (rc != 0 && rc != MDB_NOTFOUND) {
		goto failIndexedVertex;
	}
	rc = setVertexPropertyString(vertexCursor, (long) elementId, (int) propertyKeyId, propertyValueLength, propertyValue);
	if (rc != 0) {
		goto failIndexedVertex;
	}
	rc = setStringIndex(stringIndexCursor, elementId, propertyKeyId, propertyValueLength, propertyValue);

	failIndexedVertex: mdb_cursor_close(stringIndexCursor);
	return rc;
}

int deleteStringIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex) {
	int rc;
	MDB_cursor *cursor;

	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexStringIndexDb, &cursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeStringIndexDb, &cursor);
	}
	if (rc == 0) {
		MDB_val key, data;
		StringIndexKeyStruct *stringIndexKeyStruct = malloc(sizeof(StringIndexKeyStruct));
		stringIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
		stringIndexKeyStruct->elementId = -1LL;
		stringIndexKeyStruct->value[0] = '\0';

		key.mv_size = sizeof(StringIndexKeyStruct);
		key.mv_data = stringIndexKeyStruct;

		while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE) == 0)) {

			StringIndexKeyStruct *stringIndexKeyStructToDelete = (StringIndexKeyStruct *) (key.mv_data);
			if (stringIndexKeyStructToDelete->propertyKeyId == propertyKeyId) {
				rc = mdb_cursor_del(cursor, 0);
				if (rc != 0) {
					break;
				} else {
					//reset the key
					stringIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
					stringIndexKeyStruct->elementId = -1LL;
					stringIndexKeyStruct->value[0] = '\0';
				}
			} else {
				break;
			}

		}
		free(stringIndexKeyStruct);
	}
	return rc;

}

int deleteEntryFromStringIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *stringIndexCursor,
		long long elementId, int propertyKeyId) {

	int rc;

	//Get the old value first
	MDB_val oldData;
	MDB_val key, data;
	rc = getVertexProperty(vertexCursor, elementId, propertyKeyId, &oldData);
	if (rc == 0) {
		int oldPropertyValueLength = oldData.mv_size;
		char oldPropertyValue[oldPropertyValueLength];
		memcpy(oldPropertyValue, oldData.mv_data, oldPropertyValueLength);

		//Delete the current indexed element
		StringIndexKeyStruct *stringIndexKeyStruct = malloc(sizeof(StringIndexKeyStruct) + oldPropertyValueLength);
		stringIndexKeyStruct->propertyKeyId = propertyKeyId;
		stringIndexKeyStruct->elementId = elementId;
		memcpy(stringIndexKeyStruct->value, oldPropertyValue, oldPropertyValueLength);
		key.mv_size = oldPropertyValueLength + sizeof(StringIndexKeyStruct);
		key.mv_data = stringIndexKeyStruct;
		rc = mdb_cursor_get(stringIndexCursor, &key, &data, MDB_SET_KEY);
		if (rc != 0) {
			free(stringIndexKeyStruct);
			goto fail;
		}
		free(stringIndexKeyStruct);
		rc = mdb_cursor_del(stringIndexCursor, 0);
	}

	fail: return rc;
}
