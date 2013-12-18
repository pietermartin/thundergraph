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

int setVertexPropertyBoolean(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jboolean *propertyValue);
int compareBooleanIndexDbId(const MDB_val *key1, const MDB_val *key2);
int getFirstElementForKeyValueFromBooleanIndex(MDB_cursor *cursor, int propertyKeyId, unsigned char value, long long int *vertexIdResultC);
int getNextElementForKeyValueFromBooleanIndex(MDB_cursor *cursor, int propertyKeyId, unsigned char value, long long int *vertexIdResultC);
int traverseBooleanIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi);

int setBooleanIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, unsigned char propertyValue);
int removeBooleanIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, unsigned char propertyValue);
int addOrUpdateBooleanIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId, int propertyKeyId,
		jboolean propertyValue, unsigned char vertex);
int deleteEntryFromBooleanIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *booleanIndexCursor,
		long long elementId, int propertyKeyId);
int setEdgePropertyBoolean(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jboolean *propertyValue);
int deleteBooleanIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex);

void printBooleanIndexDbRecord(MDB_val key, MDB_val data);
