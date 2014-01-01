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

int setVertexPropertyByte(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jbyte *propertyValue);
int compareByteIndexDbId(const MDB_val *key1, const MDB_val *key2);
int getFirstElementForKeyValueFromByteIndex(MDB_cursor *cursor, int propertyKeyId, signed char value, long long int *vertexIdResultC);
int getNextElementForKeyValueFromByteIndex(MDB_cursor *cursor, int propertyKeyId, signed char value, long long int *vertexIdResultC);
int traverseByteIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi);

int setByteIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, signed char propertyValue);
int removeByteIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, signed char propertyValue);
int addOrUpdateByteIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId, int propertyKeyId,
		jbyte propertyValue, unsigned char vertex);
int deleteEntryFromByteIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *byteIndexCursor,
		long long elementId, int propertyKeyId);
int setEdgePropertyByte(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jbyte *propertyValue);
int deleteByteIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex);

void printByteIndexDbRecord(MDB_val key, MDB_val data);
int placeCursorOnKeyValueByteIndex(MDB_cursor *cursor, long long vertexId, int propertyKeyId, jbyte value);
int getCurrentElementFromByteIndexDb(MDB_cursor *cursor, jlong *vertexIdC, int propertyKeyId, jbyte value);
