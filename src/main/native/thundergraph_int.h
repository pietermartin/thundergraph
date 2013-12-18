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

int setVertexPropertyInt(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jint *propertyValue);
int compareIntIndexDbId(const MDB_val *key1, const MDB_val *key2);
int getFirstElementForKeyValueFromIntIndex(MDB_cursor *cursor, int propertyKeyId, int value, long long int *vertexIdResultC);
int getNextElementForKeyValueFromIntIndex(MDB_cursor *cursor, int propertyKeyId, int value, long long int *vertexIdResultC);
int traverseIntIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi);

int setIntIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, int propertyValue);
int removeIntIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, int propertyValue);
int addOrUpdateIntIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId, int propertyKeyId,
		int propertyValue, unsigned char vertex);
int deleteEntryFromIntIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *intIndexCursor,
		long long elementId, int propertyKeyId);
int setEdgePropertyInt(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jint *propertyValue);
int deleteIntIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex);

void printIntIndexDbRecord(MDB_val key, MDB_val data);
