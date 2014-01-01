#include <jni.h>
#include "lmdb.h"

#ifndef THUNDERGRAPH_STRUCT
#define THUNDERGRAPH_STRUCT
#include "thundergraph_structs.h"
#endif

#ifndef THUNDERGRAPH_GENERIC
#define THUNDERGRAPH_GENERIC
#include "thundergraph_generic.h"
#endif


int setVertexPropertyString(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jint propertyValueLength, char *propertyValue);
int compareStringIndexDbId(const MDB_val *key1, const MDB_val *key2);
int getFirstElementForKeyValueFromStringIndex(MDB_cursor *cursor, int propertyKeyId, int propertyValueLength, char *value,
		long long int *vertexIdResultC);
int getNextElementForKeyValueFromStringIndex(MDB_cursor *cursor, int propertyKeyId, int propertyValueLength, char *value,
		long long int *vertexIdResultC);
int placeCursorOnKeyValueStringIndex(MDB_cursor *cursor, long long vertexId, int propertyKeyId, int propertyValueLength, char *value);
int getCurrentElementFromStringIndexDb(MDB_cursor *cursor, jlong *elementIdC, int propertyKeyId, int propertyValueLength, char *value);
int traverseStringIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi);
int setStringIndex(MDB_cursor *indexCursor, long long vertexId, int propertyKeyId, int propertyValueLength, char propertyValue[]);
int removeStringIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, int propertyValueLength, char propertyValue[]);
void printStringIndexDbRecord(MDB_val key, MDB_val data);
int setEdgePropertyString(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jint propertyValueLength, char *propertyValue);
int addOrUpdateStringIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId,
		int propertyKeyId, int propertyValueLength, char *propertyValue, unsigned char vertex);
int deleteStringIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex);
int deleteEntryFromStringIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *stringIndexCursor,
		long long elementId, int propertyKeyId);
