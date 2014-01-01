#include <stdlib.h>
#include "thundergraph_short.h"

void printShortIndexDbRecord(MDB_val key, MDB_val data) {
	ShortIndexKeyStruct *shortIndexKeyStruct = (ShortIndexKeyStruct *) (key.mv_data);
	int propertyKeyId = shortIndexKeyStruct->propertyKeyId;
	short propertyKeyValue = shortIndexKeyStruct->value;
	long long elementIdKey = shortIndexKeyStruct->elementId;
	printf("propertyKeyId: %i, propertyKeyValue: %hu, element id: %lld\n", propertyKeyId, propertyKeyValue, elementIdKey);
}

int setVertexPropertyShort(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jshort *propertyValue) {
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
		data.mv_size = sizeof(jshort);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int compareShortIndexDbId(const MDB_val *key1, const MDB_val *key2) {
	ShortIndexKeyStruct *shortIndexKeyStruct1 = (ShortIndexKeyStruct *) (key1->mv_data);
	ShortIndexKeyStruct *shortIndexKeyStruct2 = (ShortIndexKeyStruct *) (key2->mv_data);
	int propertyKeyId1 = shortIndexKeyStruct1->propertyKeyId;
	int propertyKeyId2 = shortIndexKeyStruct2->propertyKeyId;
	if (propertyKeyId1 == propertyKeyId2) {
		short value1 = shortIndexKeyStruct1->value;
		short value2 = shortIndexKeyStruct2->value;
		if (value1 == value2) {
			long long elementId1 = shortIndexKeyStruct1->elementId;
			long long elementId2 = shortIndexKeyStruct2->elementId;
			return (elementId1 > elementId2) - (elementId1 < elementId2);
		} else {
			return (value1 > value2) - (value1 < value2);
		}
	} else {
		return (propertyKeyId1 > propertyKeyId2) - (propertyKeyId1 < propertyKeyId2);
	}
}

int getFirstElementForKeyValueFromShortIndex(MDB_cursor *cursor, int propertyKeyId, short value, long long int *vertexIdResultC) {

	int rc;
	MDB_val key, data;
	ShortIndexKeyStruct *shortIndexKeyStruct = malloc(sizeof(ShortIndexKeyStruct));
	shortIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	shortIndexKeyStruct->value = value;
	shortIndexKeyStruct->elementId = -1LL;
	key.mv_size = sizeof(ShortIndexKeyStruct);
	key.mv_data = shortIndexKeyStruct;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {

		ShortIndexKeyStruct *shortIndexKeyStructTmp = (ShortIndexKeyStruct *) (key.mv_data);
		short value1 = shortIndexKeyStructTmp->value;

		if (value == value1) {
			*vertexIdResultC = *((long long *) data.mv_data);
		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int getNextElementForKeyValueFromShortIndex(MDB_cursor *cursor, int propertyKeyId, short value, long long int *vertexIdResultC) {

	int rc;
	MDB_val key, data;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT);
	if (rc == 0) {

		ShortIndexKeyStruct *shortIndexKeyStructTmp = (ShortIndexKeyStruct *) (key.mv_data);
		short value1 = shortIndexKeyStructTmp->value;
		if (value1 == value) {
			*vertexIdResultC = *((long long *) data.mv_data);
		} else {
			rc = MDB_NOTFOUND;
		}

	}
	return rc;
}

int traverseShortIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi) {
	int rc = 0;
	MDB_cursor *cursor;
	MDB_val key, data;
	rc = mdb_cursor_open(txn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		printShortIndexDbRecord(key, data);
	}
	fail: mdb_cursor_close(cursor);
	return rc;
}

int setShortIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, short propertyValue) {
	int rc;
	MDB_val key, data;
	ShortIndexKeyStruct *shortIndexKeyStruct = malloc(sizeof(ShortIndexKeyStruct));
	shortIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	shortIndexKeyStruct->elementId = (long long) elementId;
	shortIndexKeyStruct->value = propertyValue;
	key.mv_size = sizeof(ShortIndexKeyStruct);
	key.mv_data = shortIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_put(indexCursor, &key, &data, 0);
	free(shortIndexKeyStruct);
	return rc;
}

int removeShortIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, short propertyValue) {
	int rc;
	MDB_val key, data;
	ShortIndexKeyStruct *shortIndexKeyStruct = malloc(sizeof(ShortIndexKeyStruct));
	shortIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	shortIndexKeyStruct->elementId = (long long) elementId;
	shortIndexKeyStruct->value = propertyValue;
	key.mv_size = sizeof(ShortIndexKeyStruct);
	key.mv_data = shortIndexKeyStruct;
	data.mv_size = sizeof(long long);
	data.mv_data = &elementId;
	rc = mdb_cursor_get(indexCursor, &key, &data, MDB_SET_KEY);
	if (rc == 0) {
		rc = mdb_cursor_del(indexCursor, 0);
	}
	free(shortIndexKeyStruct);
	return rc;
}

int addOrUpdateShortIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId, int propertyKeyId,
		jshort propertyValue, unsigned char vertex) {

	int rc;
	MDB_cursor *shortIndexCursor;
	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexShortIndexDb, &shortIndexCursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeShortIndexDb, &shortIndexCursor);
	}
	if (rc != 0) {
		goto failIndexedVertex;
	}
	rc = deleteEntryFromShortIndex(glmdb_env, mdbTxn, vertexCursor, shortIndexCursor, (long long) elementId, (int) propertyKeyId);
	if (rc != 0 && rc != MDB_NOTFOUND) {
		goto failIndexedVertex;
	}
	rc = setVertexPropertyShort(vertexCursor, (long) elementId, (int) propertyKeyId, &propertyValue);
	if (rc != 0) {
		goto failIndexedVertex;
	}

	rc = setShortIndex(shortIndexCursor, elementId, propertyKeyId, propertyValue);

	failIndexedVertex: mdb_cursor_close(shortIndexCursor);
	return rc;
}

int deleteEntryFromShortIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *shortIndexCursor,
		long long elementId, int propertyKeyId) {

	int rc;

	//Get the old value first
	MDB_val oldData;
	MDB_val key, data;
	rc = getVertexProperty(vertexCursor, elementId, propertyKeyId, &oldData);
	if (rc == 0) {
		//Delete the current indexed element
		ShortIndexKeyStruct *shortIndexKeyStruct = malloc(sizeof(ShortIndexKeyStruct));
		shortIndexKeyStruct->propertyKeyId = propertyKeyId;
		shortIndexKeyStruct->elementId = elementId;
		shortIndexKeyStruct->value = *((short *) oldData.mv_data);
		key.mv_size = sizeof(ShortIndexKeyStruct);
		key.mv_data = shortIndexKeyStruct;
		rc = mdb_cursor_get(shortIndexCursor, &key, &data, MDB_SET_KEY);
		if (rc != 0) {
			free(shortIndexKeyStruct);
			goto fail;
		}
		free(shortIndexKeyStruct);
		rc = mdb_cursor_del(shortIndexCursor, 0);
	}

	fail: return rc;
}

int setEdgePropertyShort(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jshort *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = EPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		key.mv_size = sizeof(EdgeDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jshort);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int deleteShortIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex) {
	int rc;
	MDB_cursor *cursor;

	if (vertex) {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->vertexShortIndexDb, &cursor);
	} else {
		rc = mdb_cursor_open(mdbTxn, glmdb_env->edgeShortIndexDb, &cursor);
	}
	if (rc == 0) {
		MDB_val key, data;
		ShortIndexKeyStruct *shortIndexKeyStruct = malloc(sizeof(ShortIndexKeyStruct));
		shortIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
		shortIndexKeyStruct->elementId = -1LL;
		shortIndexKeyStruct->value = -1;

		key.mv_size = sizeof(ShortIndexKeyStruct);
		key.mv_data = shortIndexKeyStruct;

		while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE) == 0)) {

			ShortIndexKeyStruct *shortIndexKeyStructToDelete = (ShortIndexKeyStruct *) (key.mv_data);
			if (shortIndexKeyStructToDelete->propertyKeyId == propertyKeyId) {
				rc = mdb_cursor_del(cursor, 0);
				if (rc != 0) {
					break;
				} else {
					//reset the key
					shortIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
					shortIndexKeyStruct->elementId = -1LL;
					shortIndexKeyStruct->value = -1;
				}
			} else {
				break;
			}

		}
		free(shortIndexKeyStruct);
	}
	return rc;

}

int placeCursorOnKeyValueShortIndex(MDB_cursor *cursor, long long vertexId, int propertyKeyId, jshort value) {

	int rc;
	MDB_val key, data;
	ShortIndexKeyStruct *shortIndexKeyStruct = malloc(sizeof(ShortIndexKeyStruct));
	shortIndexKeyStruct->propertyKeyId = (int) propertyKeyId;
	shortIndexKeyStruct->elementId = -1LL;
	shortIndexKeyStruct->elementId = vertexId;
	shortIndexKeyStruct->value = value;
	key.mv_size = sizeof(ShortIndexKeyStruct);
	key.mv_data = shortIndexKeyStruct;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {

		ShortIndexKeyStruct *shortIndexKeyStructTmp = (ShortIndexKeyStruct *) (key.mv_data);
		short value1 = shortIndexKeyStructTmp->value;
		if (value1 != value) {
			rc = MDB_NOTFOUND;
		}

	}

	free(shortIndexKeyStruct);
	return rc;

}

int getCurrentElementFromShortIndexDb(MDB_cursor *cursor, jlong *vertexIdC, int propertyKeyId, jshort value) {

	int rc = 0;
	MDB_val key, data;
	rc = mdb_cursor_get(cursor, &key, &data, MDB_GET_CURRENT);

	if (rc == MDB_NOTFOUND) {
		rc = getNextElementForKeyValueFromShortIndex(cursor, propertyKeyId, value, (long long int *)vertexIdC);
	} else {
		*vertexIdC = *((long long *) data.mv_data);
	}

	return rc;
}
