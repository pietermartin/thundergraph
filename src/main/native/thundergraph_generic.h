#include <jni.h>
#include "lmdb.h"

#ifndef THUNDERGRAPH_STRUCT
#define THUNDERGRAPH_STRUCT
#include "thundergraph_structs.h"
#endif

void initVertexDbId(VertexDbId *vertexDbId);
void initEdgeDbId(EdgeDbId *edgeDbId);
void initEdgeData(EdgeData *edgeData);

int getVertexProperty(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, MDB_val *data);
int getFirstVertex(MDB_cursor *cursor, long long *vertexIdResultC);
int getNextVertex(MDB_cursor *cursor, long long previousVertexId, long long *vertexIdResultC);
int removeVertex(MDB_txn *txn, GLMDB_env *genv, jlong vertexId);
int internalDeleteVertex(MDB_cursor *vertexCursor, MDB_cursor *inverseCursor, MDB_cursor *edgeCursor, VertexDbId vertexDbId,
		VertexDbId inverseId, MDB_val inverseKey, MDB_val data, MDB_val inverseData);
int removeEdge(MDB_txn *txn, GLMDB_env *genv, jlong edgeId);
/**
 * This only removes the edge from the edge db, not the related edges in the vertexDb
 */
int internalRemoveEdge(GLMDB_env *genv, MDB_txn *txn, MDB_cursor *edgeCursor, jlong edgeId);
int deleteEdgeProperties(GLMDB_env *genv, MDB_txn *txn, MDB_cursor *edgeCursor, MDB_val edgeKey, MDB_val data, jlong edgeId);

int getEdge(MDB_cursor *cursor, jlong edgeId, MDB_val *edgeKey, MDB_val *edgeData);

void printVertexRecord(MDB_val key, MDB_val data);

int getFirstEdgefromVertex(MDB_cursor *cursor, jint direction, jint labelId, jlong fromVertexId, jlong *edgeIdResultC,
		jlong *outVertexIdC, jlong *inVertexIdC);
int getNextEdgefromVertex(MDB_cursor *cursor, jint direction, jint labelId, jlong fromVertexId, jlong *edgeIdResultC,
		jlong *outVertexIdC, jlong *inVertexIdC);
int getCurrentEdgefromVertex(MDB_cursor *cursor, jint direction, jint labelId, jlong fromVertexId, jlong *edgeIdResultC,
		jlong *outVertexIdC, jlong *inVertexIdC);
int getFirstEdgefromVertexAllLabels(MDB_cursor *cursor, jint direction, jlong fromVertexId, jint *labelIdResultC, jlong *edgeIdResultC,
		jlong *outVertexIdC, jlong *inVertexIdC);
int getNextEdgefromVertexAllLabels(MDB_cursor *cursor, jint direction, jlong fromVertexId, jint *labelIdResultC, jlong *edgeIdResultC,
		jlong *outVertexIdC, jlong *inVertexIdC);
int getCurrentEdgefromVertexAllLabels(MDB_cursor *cursor, jint direction, jlong fromVertexId, jint *labelIdResultC,
		jlong *edgeIdResultC, jlong *outVertexIdC, jlong *inVertexIdC);

