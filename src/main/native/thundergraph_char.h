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

int setVertexPropertyChar(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jchar *propertyValue);
int compareCharIndexDbId(const MDB_val *key1, const MDB_val *key2);
int getFirstElementForKeyValueFromCharIndex(MDB_cursor *cursor, int propertyKeyId, unsigned short value, long long int *vertexIdResultC);
int getNextElementForKeyValueFromCharIndex(MDB_cursor *cursor, int propertyKeyId, unsigned short value, long long int *vertexIdResultC);
int traverseCharIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi);

int setCharIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, unsigned short propertyValue);
int removeCharIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, unsigned short propertyValue);
int addOrUpdateCharIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId, int propertyKeyId,
		jchar propertyValue, unsigned char vertex);
int deleteEntryFromCharIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *charIndexCursor,
		long long elementId, int propertyKeyId);
int setEdgePropertyChar(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jchar *propertyValue);
int deleteCharIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex);

void printCharIndexDbRecord(MDB_val key, MDB_val data);
int placeCursorOnKeyValueCharIndex(MDB_cursor *cursor, long long vertexId, int propertyKeyId, jchar value);
int getCurrentElementFromCharIndexDb(MDB_cursor *cursor, jlong *vertexIdC, int propertyKeyId, jchar value);
