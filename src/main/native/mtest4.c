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
	int i = 0;
	for (i = 0; i < 50; i = i + 1) {
		rc = addVertex(cursor, genv->vertexDb, genv->vertexIdSequence++, &vertexKey);
		if (rc != 0) {
			printf("add in vertex failure  = %i!\n", rc);
			goto fail;
		}
	}

	printf("ddddd %i!\n", rc);

	int j = 0;
	for (j = 0; j < 40; j = j + 2) {
		long vertexOutId = (long)j;
		long vertexInId = (long) (j + 1);
		long edgeId = (long) (j);
		rc = addEdge(txn, genv->vertexDb, genv->edgeDb, edgeId, 0, vertexOutId, vertexInId);
		if (rc != 0) {
			printf("add edge failure  = %i!\n", rc);
			goto fail;
		}
	}
	mdb_cursor_close(cursor);
	mdb_txn_commit(txn);
	traverseVertexDb(genv->env, genv->vertexDb);

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

	for (i = 0; i < 50; i = i + 1) {
		printf("deleting record %i\n", i);
		rc = removeVertex(txn, genv, (long)i);
		if (rc != 0) {
			printf("removeVertex failure  = %i!\n", rc);
			goto fail;
		}
	}

	mdb_cursor_close(cursor);
	mdb_txn_commit(txn);

	traverseVertexDb(genv->env, genv->vertexDb);

	fail:
	printf("closing graph!\n");
	closeGraph(genv);
	return 0;
}
