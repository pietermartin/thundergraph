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

int main(int argc, char * argv[]) {
	int rc;
	GLMDB_env *genv;
	printf("opening graph!\n");
	rc = openGraph(&genv, "/home/pieter/Downloads/thundergraph/src/main/native/testdb");
	if (rc != 0) {
		printf("opening graph failure  = %i!\n", rc);
		goto fail;
	}

	MDB_txn *txn;
	MDB_cursor *cursor;
	rc = mdb_txn_begin(genv->env, NULL, 0, &txn);
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

	char *propertyValue1 = malloc(1);
	char v1[] = "1";
	memcpy(propertyValue1, v1, 1);
	rc = setVertexPropertyString(cursor, 0, 0, 1, propertyValue1);
	if (rc != 0) {
		printf("setVertexPropertyChar failure  = %i!\n", rc);
		goto fail;
	}
	free(propertyValue1);

	clock_t start = clock();
	int i = 0;
	for (i = 0; i < 10000000; i = i + 1) {
		rc = addVertex(cursor, genv->vertexDb, genv->vertexIdSequence, &vertexKey);
		if (rc != 0) {
			printf("add in vertex failure  = %i!\n", rc);
			goto fail;
		}

		char *propertyValue1 = malloc(1);
		char v1[] = "2";
		memcpy(propertyValue1, v1, 1);
		rc = setVertexPropertyString(cursor, 0, 0, 1, propertyValue1);
		if (rc != 0) {
			printf("setVertexPropertyChar failure  = %i!\n", rc);
			goto fail;
		}
		free(propertyValue1);

		rc = addEdge(txn, genv->vertexDb, genv->edgeDb, genv->edgeIdSequence++, 0, outVertexId, genv->vertexIdSequence++);
		if (rc != 0) {
			printf("add edge failure  = %i!\n", rc);
			goto fail;
		}
		MDB_cursor *edgeCursor;
		rc = mdb_cursor_open(txn, genv->edgeDb, &edgeCursor);
		if (rc != 0) {
			printf("open cursor failure  = %i!\n", rc);
			goto fail;
		}

		mdb_cursor_close(edgeCursor);

	}
	mdb_cursor_close(cursor);
	mdb_txn_commit(txn);

	clock_t end = clock();
	float seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("write 10000000 = %g\n", seconds);
	start = clock();

	txn = NULL;
	rc = mdb_txn_begin(genv->env, NULL, 0, &txn);
	if (rc != 0) {
		printf("begin transaction failure  = %i!\n", rc);
		goto fail;
	}
	rc = mdb_cursor_open(txn, genv->vertexDb, &cursor);
	if (rc != 0) {
		printf("open cursor failure  = %i!\n", rc);
		goto fail;
	}

	jint *labelIdResultC = malloc(sizeof(jint));
	jlong *edgeIdResultC = malloc(sizeof(jlong));
	jlong *outVertexIdC = malloc(sizeof(jlong));
	jlong *inVertexIdC = malloc(sizeof(jlong));

	rc = getFirstEdgefromVertexAllLabels(cursor, 0, 0LL, labelIdResultC, edgeIdResultC, outVertexIdC, inVertexIdC);

	if (rc != 0) {
		printf("getFirstEdgefromVertexAllLabels failure %i\n", rc);
	}
	printf("getFirstEdgefromVertexAllLabels inVertexIdC %lld\n", (long long)(*inVertexIdC));

	MDB_val data;
	MDB_cursor *vertexPropertyCursor;
	rc = mdb_cursor_open(txn, genv->vertexDb, &vertexPropertyCursor);
	if (rc != 0) {
		printf("open cursor failure  = %i!\n", rc);
		goto fail;
	}

	while ((rc = getNextEdgefromVertexAllLabels(cursor, 0, 0LL, labelIdResultC, edgeIdResultC, outVertexIdC, inVertexIdC)) == 0) {

		getVertexProperty(vertexPropertyCursor, *inVertexIdC, 0, &data);

		if ((long long)(*inVertexIdC) % 1000000 == 0) {
			printf("getNextEdgefromVertexAllLabels inVertexIdC %lld\n", (long long)*inVertexIdC);
		}

	}

	mdb_cursor_close(vertexPropertyCursor);

	free(labelIdResultC);
	free(edgeIdResultC);
	free(outVertexIdC);
	free(inVertexIdC);

	mdb_cursor_close(cursor);
//	traverseVertexDb(genv, txn);
	mdb_txn_commit(txn);

	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("read 10000000 = %g\n", seconds);
	fail: printf("closing graph!\n");
	closeGraph(genv);
	return 0;
}
