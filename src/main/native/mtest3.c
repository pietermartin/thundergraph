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

	char *propertyValue1 = malloc(5);
	char v1[] = "12345";
	memcpy(propertyValue1, v1, 5);
	rc = setVertexPropertyString(cursor, 0, 0, 5, propertyValue1);
	if (rc != 0) {
		printf("setVertexPropertyChar failure  = %i!\n", rc);
		goto fail;
	}

	char *propertyValue2 = malloc(5);
	char v2[] = "12345";
	memcpy(propertyValue2, v2, 5);
	rc = setVertexPropertyString(cursor, 0, 1, 5, propertyValue2);
	if (rc != 0) {
		printf("setVertexPropertyChar failure  = %i!\n", rc);
		goto fail;
	}

	int i = 0;
	for (i = 0; i < 1100; i = i + 1) {
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
		MDB_cursor *edgeCursor;
		rc = mdb_cursor_open(txn, genv->edgeDb, &edgeCursor);
		if (rc != 0) {
			printf("open cursor failure  = %i!\n", rc);
			goto fail;
		}

		char *edgePropertyValue2 = malloc(5);
		char v2[] = "12345";
		memcpy(edgePropertyValue2, v2, 5);

		rc = setEdgePropertyString(edgeCursor, genv->edgeIdSequence - 1, 0, 5, edgePropertyValue2);

		mdb_cursor_close(edgeCursor);

	}
	mdb_cursor_close(cursor);
//	traverseVertexDb(genv, txn);
	mdb_txn_commit(txn);

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

	long long *vertexIdResultC = malloc(sizeof(long long));
	rc = getFirstVertex(cursor, vertexIdResultC);
	if (rc != 0) {
		printf("getFirstVertex failure %i\n", rc);
	}
	printf("getFirstVertex vertexIdResultC %llu\n", *vertexIdResultC);
	long long previousVertexId = *vertexIdResultC;
	while ((rc = getNextVertex(cursor, previousVertexId, vertexIdResultC)) ==0) {

		printf("getNextVertex vertexIdResultC %llu\n", *vertexIdResultC);
		previousVertexId = *vertexIdResultC;

		rc = removeVertex(txn, genv, previousVertexId);
		if (rc != 0) {
			printf("removeVertex failure %i\n", rc);
			goto fail;
		}
	}

//	long long j;
//	for (j = 1; j < 1101; j++) {
//
//		MDB_val vertexKeyT, dataT;
//		VertexDbId id;
//		id.vertexId = j;
//		id.coreOrPropertyEnum = VCORE;
//		id.labelId = -1;
//		id.edgeId = -1LL;
//		id.propertykeyId = -1;
//		vertexKeyT.mv_size = sizeof(VertexDbId);
//		vertexKeyT.mv_data = &id;
//
//		rc = mdb_cursor_get(cursor, &vertexKeyT, &dataT, MDB_SET_KEY);
//		printf("mdb_cursor_get index = %llu, result = %i\n", j, rc);
//
//		rc = removeVertex(txn, genv, j);
//		if (rc != 0) {
//			printf("removeVertex failure %i\n", rc);
//			goto fail;
//		}
//		rc = mdb_cursor_get(cursor, &vertexKeyT, &dataT, MDB_FIRST);
//		if (rc != 0) {
//			printf("mdb_cursor_get MDB_CURRENT failure %i\n", rc);
//			goto fail;
//		}
//
//	}

	mdb_cursor_close(cursor);
	traverseVertexDb(genv, txn);
	mdb_txn_commit(txn);

	fail: printf("closing graph!\n");
	closeGraph(genv);
	return 0;
}
