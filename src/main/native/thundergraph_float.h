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

int setVertexPropertyFloat(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jfloat *propertyValue);
int compareFloatIndexDbId(const MDB_val *key1, const MDB_val *key2);
int getFirstElementForKeyValueFromFloatIndex(MDB_cursor *cursor, int propertyKeyId, float value, long long int *vertexIdResultC);
int getNextElementForKeyValueFromFloatIndex(MDB_cursor *cursor, int propertyKeyId, float value, long long int *vertexIdResultC);
int traverseFloatIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi);

int setFloatIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, float propertyValue);
int removeFloatIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, float propertyValue);
int addOrUpdateFloatIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId, int propertyKeyId,
		jfloat propertyValue, unsigned char vertex);
int deleteEntryFromFloatIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *floatIndexCursor,
		long long elementId, int propertyKeyId);
int setEdgePropertyFloat(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jfloat *propertyValue);
int deleteFloatIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex);

void printFloatIndexDbRecord(MDB_val key, MDB_val data);
int placeCursorOnKeyValueFloatIndex(MDB_cursor *cursor, long long vertexId, int propertyKeyId, jfloat value);
int getCurrentVertexfromVertexFloatIndexDb(MDB_cursor *cursor, jlong *vertexIdC, int propertyKeyId, jfloat value);
