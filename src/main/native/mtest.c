/* mtest.c - memory-mapped database tester/toy */
/*
 * Copyright 2011 Howard Chu, Symas Corp.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted only as authorized by the OpenLDAP
 * Public License.
 *
 * A copy of this license is available in the file LICENSE in the
 * top-level directory of the distribution or, alternatively, at
 * <http://www.OpenLDAP.org/license.html>.
 */
#define _XOPEN_SOURCE 500		/* srandom(), random() */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "glmdb_jni.c"

int main(int argc,char * argv[])
{
	int rc;
	GLMDB_env *genv;
	printf("opening graph!\n");
	rc = openGraph(&genv, "/home/pieter/Downloads/glmdb-blueprints/src/main/native/testdb");
	if (rc != 0) {
		printf("opening graph failure  = %i!\n", rc);
		goto fail;
	}

	MDB_txn *txn;
	MDB_cursor *cursor;
	rc = mdb_txn_begin(genv->env, NULL, 1, &txn);
	if (rc != 0) {
		printf("begin transaction failure  = %i!\n", rc);
		goto fail;
	}
	rc = mdb_cursor_open(txn, genv->vertexDb, &cursor);
	if (rc != 0) {
		printf("open cursor failure  = %i!\n", rc);
		goto fail;
	}
	MDB_val vertexKey;
	rc = addVertex(cursor, genv->vertexDb, genv->vertexIdSequence++, &vertexKey);
	if (rc != 0) {
		printf("add out vertex failure  = %i!\n", rc);
		goto fail;
	}
	VertexDbId outVertexDbId = (*((VertexDbId *) (vertexKey.mv_data)));
	signed long long outVertexId = outVertexDbId.vertexId;

	int i = 0;
	for (i = 0; i < 10; i = i + 1) {
		rc = addVertex(cursor, genv->vertexDb, genv->vertexIdSequence++, &vertexKey);
		if (rc != 0) {
			printf("add in vertex failure  = %i!\n", rc);
			goto fail;
		}
		VertexDbId inVertexDbId = (*((VertexDbId *) (vertexKey.mv_data)));
		signed long long inVertexId = inVertexDbId.vertexId;
		rc = addEdge(txn, genv->vertexDb, genv->edgeDb, genv->edgeIdSequence++, 0, outVertexId, inVertexId);
		if (rc != 0) {
			printf("add edge failure  = %i!\n", rc);
			goto fail;
		}
	}

	mdb_cursor_close(cursor);
	mdb_txn_commit(txn);

	rc = mdb_txn_begin(genv->env, NULL, 1, &txn);
	if (rc != 0) {
		printf("transaction begin = %i!\n", rc);
		goto fail;
	}
	rc = mdb_cursor_open(txn, genv->vertexDb, &cursor);
	if (rc != 0) {
		printf("open cursor failure  = %i!\n", rc);
		goto fail;
	}
	rc = getVertex(cursor, 0LL, &vertexKey);
	printKey(vertexKey);
	if (rc != 0) {
		printf("get vertex failure  = %i!\n", rc);
		goto fail;
	}

	jlong *edgeIdResultC = (jlong *)malloc(sizeof(signed long long));
	jlong *outVertexIdC = (jlong *)malloc(sizeof(signed long long));
	jlong *inVertexIdC = (jlong *)malloc(sizeof(signed long long));

	rc = getFirstEdgefromVertex(cursor, 0, 0LL, edgeIdResultC, outVertexIdC, inVertexIdC);
	if (rc != 0) {
		printf("getFirstEdgefromVertex failure  = %i!\n", rc);
		goto fail;
	}
	printf("edgeIdResultC = %ld, outVertexIdC = %ld, inVertexIdC = %ld\n", *edgeIdResultC, *outVertexIdC, *inVertexIdC);

	rc = getNextEdgefromVertex(cursor, 0, 0LL, edgeIdResultC, outVertexIdC, inVertexIdC);
	if (rc != 0) {
		printf("getNextEdgefromVertex failure  = %i!\n", rc);
		goto fail;
	}
	printf("edgeIdResultC = %ld, outVertexIdC = %ld, inVertexIdC = %ld\n", *edgeIdResultC, *outVertexIdC, *inVertexIdC);

	mdb_cursor_close(cursor);
	mdb_txn_commit(txn);

	traverseDb(genv->env, genv->vertexDb);

	fail:
	printf("closing graph!\n");
	closeGraph(genv);
	return 0;
}
