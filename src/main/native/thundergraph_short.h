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

int setVertexPropertyShort(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jshort *propertyValue);
int compareShortIndexDbId(const MDB_val *key1, const MDB_val *key2);
int getFirstElementForKeyValueFromShortIndex(MDB_cursor *cursor, int propertyKeyId, short value, long long int *vertexIdResultC);
int getNextElementForKeyValueFromShortIndex(MDB_cursor *cursor, int propertyKeyId, short value, long long int *vertexIdResultC);
int traverseShortIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi);

int setShortIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, short propertyValue);
int removeShortIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, short propertyValue);
int addOrUpdateShortIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId, int propertyKeyId,
		jshort propertyValue, unsigned char vertex);
int deleteEntryFromShortIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *shortIndexCursor,
		long long elementId, int propertyKeyId);
int setEdgePropertyShort(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jshort *propertyValue);
int deleteShortIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex);

void printShortIndexDbRecord(MDB_val key, MDB_val data);
int placeCursorOnKeyValueShortIndex(MDB_cursor *cursor, long long vertexId, int propertyKeyId, jshort value);
int getCurrentVertexfromVertexShortIndexDb(MDB_cursor *cursor, jlong *vertexIdC, int propertyKeyId, jshort value);
