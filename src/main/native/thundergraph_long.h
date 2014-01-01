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

int setVertexPropertyLong(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jlong *propertyValue);
int compareLongIndexDbId(const MDB_val *key1, const MDB_val *key2);
int getFirstElementForKeyValueFromLongIndex(MDB_cursor *cursor, int propertyKeyId, long long value, long long int *vertexIdResultC);
int getNextElementForKeyValueFromLongIndex(MDB_cursor *cursor, int propertyKeyId, long long value, long long int *vertexIdResultC);
int traverseLongIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi);

int setLongIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, long long propertyValue);
int removeLongIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, long long propertyValue);
int addOrUpdateLongIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId, int propertyKeyId,
		jlong propertyValue, unsigned char vertex);
int deleteEntryFromLongIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *longIndexCursor,
		long long elementId, int propertyKeyId);
int setEdgePropertyLong(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jlong *propertyValue);
int deleteLongIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex);

void printLongIndexDbRecord(MDB_val key, MDB_val data);
int placeCursorOnKeyValueLongIndex(MDB_cursor *cursor, long long vertexId, int propertyKeyId, jlong value);
int getCurrentElementFromLongIndexDb(MDB_cursor *cursor, jlong *vertexIdC, int propertyKeyId, jlong value);
