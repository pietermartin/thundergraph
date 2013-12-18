#include <stdlib.h>
#include "thundergraph_char.h"

void printCharIndexDbRecord(MDB_val key, MDB_val data) {
	CharIndexKeyStruct *charIndexKeyStruct = (CharIndexKeyStruct *) (key.mv_data);
	int propertyKeyId = charIndexKeyStruct->propertyKeyId;
	unsigned short propertyKeyValue = charIndexKeyStruct->value;
	long long elementIdKey = charIndexKeyStruct->elementId;
	printf("propertyKeyId: %i, propertyKeyValue: %hu, element id: %lld\n", propertyKeyId, propertyKeyValue, elementIdKey);
}

int setVertexPropertyChar(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jchar *propertyValue) {
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
		data.mv_size = sizeof(jchar);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int compareCharIndexDbId(const MDB_val *key1, const MDB_val *key2) {
	CharIndexKeyStruct *charIndexKeyStruct1 = (CharIndexKeyStruct *) (key1->mv_data);
	CharIndexKeyStruct *charIndexKeyStruct2 = (CharIndexKeyStruct *) (key2->mv_data);
	int propertyKeyId1 = charIndexKeyStruct1->propertyKeyId;
	int propertyKeyId2 = charIndexKeyStruct2->propertyKeyId;
	if (propertyKeyId1 == propertyKeyId2) {
		unsigned short value1 = charIndexKeyStruct1->value;
		unsigned short value2 = charIndexKeyStruct2->value;
		if (value1 == value2) {
			long long elementId1 = charIndexKeyStruct1->elementId;
			long long elementId2 = charIndexKeyStruct2->elementId;
			return (elementId1 > elementId2) - (elementId1 < elementId2);
		} else {
			return (value1 > value2) - (value1 < value2);
		}
	} else {
		return (propertyKeyId1 > propertyKeyId2) - (propertyKeyId1 < propertyKeyId2);
	}
}

int getFirstElementForKeyValueFromCharIndex(MDB_cursor *cursor, int propertyKeyId, unsigned short value, long long int *vertexIdResultC) {

	printf("getFirstElementForKeyValueFromCharIndex propertyKeyId = %i\n", propertyKeyId);

	int rc;
	MDB_val key, data;
	CharIndexKeyStruct *charIndexKeyStruct = malloc(sizeof(CharIndexKeyStruct));
	charIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	charIndexKeyStruct->value = value;
	charIndexKeyStruct->elementId = -1LL;
	key.mv_size = sizeof(CharIndexKeyStruct);
	key.mv_data = charIndexKeyStruct;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {

		CharIndexKeyStruct *charIndexKeyStructTmp = (CharIndexKeyStruct *) (key.mv_data);
		unsigned short value1 = charIndexKeyStructTmp->value;

		printf("getFirstElementForKeyValueFromCharIndex value1 = %hu\n", value1);
		printf("getFirstElementForKeyValueFromCharIndex value = %hu\n", value);

		if (value == value1) {
			*vertexIdResultC = *((long long *) data.mv_data);
		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int getNextElementForKeyValueFromCharIndex(MDB_cursor *cursor, int propertyKeyId, unsigned short value, long long int *vertexIdResultC) {

	int rc;
	MDB_val key, data;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT);
	if (rc == 0) {

		CharIndexKeyStruct *charIndexKeyStructTmp = (CharIndexKeyStruct *) (key.mv_data);
		unsigned short value1 = charIndexKeyStructTmp->value;
		if (value1 == value) {
			*vertexIdResultC = *((long long *) data.mv_data);
		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int traverseCharIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi) {
	int rc = 0;
	MDB_cursor *cursor;
	MDB_val key, data;
	rc = mdb_cursor_open(txn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		printCharIndexDbRecord(key, data);
	}
	fail: mdb_cursor_close(cursor);
	return rc;
}

int setCharIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, unsigned short propertyValue) {
	int rc;
	MDB_val key, data;
	CharIndexKeyStruct *charIndexKeyStruct = malloc(sizeof(CharIndexKeyStruct));
	charIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	charIndexKeyStruct->elementId = (long long) elementId;
	charIndexKeyStruct->value = propertyValue;
	key.mv_size = sizeof(CharIndexKeyStruct);
	key.mv_data = charIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_put(indexCursor, &key, &data, 0);
	free(charIndexKeyStruct);
	return rc;
}

int removeCharIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, unsigned short propertyValue) {
	int rc;
	MDB_val key, data;
	CharIndexKeyStruct *charIndexKeyStruct = malloc(sizeof(CharIndexKeyStruct));
	charIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	charIndexKeyStruct->elementId = (long long) elementId;
	charIndexKeyStruct->value = propertyValue;
	key.mv_size = sizeof(CharIndexKeyStruct);
	key.mv_data = charIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_get(indexCursor, &key, &data, MDB_SET_KEY);
	if (rc == 0) {
		rc = mdb_cursor_del(indexCursor, 0);
	}
	free(charIndexKeyStruct);
	return rc;
}

int addOrUpdateCharIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId, int propertyKeyId,
		jchar propertyValue, unsigned char vertex) {

	int rc;
	MDB_cursor *charIndexCursor;
	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexCharIndexDb, &charIndexCursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeCharIndexDb, &charIndexCursor);
	}
	if (rc != 0) {
		goto failIndexedVertex;
	}
	rc = deleteEntryFromCharIndex(glmdb_env, mdbTxn, vertexCursor, charIndexCursor, (long long) elementId, (int) propertyKeyId);
	if (rc != 0 && rc != MDB_NOTFOUND) {
		goto failIndexedVertex;
	}
	rc = setVertexPropertyChar(vertexCursor, (long) elementId, (int) propertyKeyId, &propertyValue);
	if (rc != 0) {
		goto failIndexedVertex;
	}

	rc = setCharIndex(charIndexCursor, elementId, propertyKeyId, propertyValue);

	failIndexedVertex: mdb_cursor_close(charIndexCursor);
	return rc;
}

int deleteEntryFromCharIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *charIndexCursor,
		long long elementId, int propertyKeyId) {

	int rc;

	//Get the old value first
	MDB_val oldData;
	MDB_val key, data;
	rc = getVertexProperty(vertexCursor, elementId, propertyKeyId, &oldData);
	if (rc == 0) {
		//Delete the current indexed element
		CharIndexKeyStruct *charIndexKeyStruct = malloc(sizeof(CharIndexKeyStruct));
		charIndexKeyStruct->propertyKeyId = propertyKeyId;
		charIndexKeyStruct->elementId = elementId;
		charIndexKeyStruct->value = *((double *) oldData.mv_data);
		key.mv_size = sizeof(CharIndexKeyStruct);
		key.mv_data = charIndexKeyStruct;
		rc = mdb_cursor_get(charIndexCursor, &key, &data, MDB_SET_KEY);
		if (rc != 0) {
			free(charIndexKeyStruct);
			goto fail;
		}
		free(charIndexKeyStruct);
		rc = mdb_cursor_del(charIndexCursor, 0);
	}

	fail: return rc;
}

int setEdgePropertyChar(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jchar *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = EPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		key.mv_size = sizeof(EdgeDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jchar);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int deleteCharIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex) {
	int rc;
	MDB_cursor *cursor;

	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexCharIndexDb, &cursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeCharIndexDb, &cursor);
	}
	if (rc == 0) {
		MDB_val key, data;
		CharIndexKeyStruct *charIndexKeyStruct = malloc(sizeof(CharIndexKeyStruct));
		charIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
		charIndexKeyStruct->elementId = -1LL;
		charIndexKeyStruct->value = 0;

		key.mv_size = sizeof(CharIndexKeyStruct);
		key.mv_data = charIndexKeyStruct;

		while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE) == 0)) {

			CharIndexKeyStruct *charIndexKeyStructToDelete = (CharIndexKeyStruct *) (key.mv_data);
			if (charIndexKeyStructToDelete->propertyKeyId == propertyKeyId) {
				rc = mdb_cursor_del(cursor, 0);
				if (rc != 0) {
					break;
				} else {
					//reset the key
					charIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
					charIndexKeyStruct->elementId = -1LL;
					charIndexKeyStruct->value = 0;
				}
			} else {
				break;
			}

		}
		free(charIndexKeyStruct);
	}
	return rc;

}
