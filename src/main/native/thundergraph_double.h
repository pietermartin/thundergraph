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

int setVertexPropertyDouble(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jdouble *propertyValue);
int compareDoubleIndexDbId(const MDB_val *key1, const MDB_val *key2);
int getFirstElementForKeyValueFromDoubleIndex(MDB_cursor *cursor, int propertyKeyId, double value, long long int *vertexIdResultC);
int getNextElementForKeyValueFromDoubleIndex(MDB_cursor *cursor, int propertyKeyId, double value, long long int *vertexIdResultC);
int traverseDoubleIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi);

int setDoubleIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, double propertyValue);
int removeDoubleIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, double propertyValue);
int addOrUpdateDoubleIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId, int propertyKeyId,
		jdouble propertyValue, unsigned char vertex);
int deleteEntryFromDoubleIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *doubleIndexCursor,
		long long elementId, int propertyKeyId);
int setEdgePropertyDouble(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jdouble *propertyValue);
int deleteDoubleIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex);

void printDoubleIndexDbRecord(MDB_val key, MDB_val data);
int placeCursorOnKeyValueDoubleIndex(MDB_cursor *cursor, long long vertexId, int propertyKeyId, jdouble value);
int getCurrentElementFromDoubleIndexDb(MDB_cursor *cursor, jlong *vertexIdC, int propertyKeyId, jdouble value);
