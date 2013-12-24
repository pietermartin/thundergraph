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
#include <string.h>
#include <time.h>

#include "glmdb_jni.c"

int main(int argc,char * argv[])
{
	int rc;
	GLMDB_env *genv;
	MDB_txn *txn;
	MDB_cursor *cursor;
	printf("opening graph!\n");
	rc = openGraph(&genv, "/home/pieter/Downloads/thundergraph/src/main/native/testdb");
	if (rc != 0) {
		printf("opening graph failure  = %i!\n", rc);
		goto fail;
	}
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

	//Add a vertex
	MDB_val vertexKey;
	long long vertexId1 = genv->vertexIdSequence++;
	rc = addVertex(cursor, genv->vertexDb, vertexId1, &vertexKey);
	if (rc != 0) {
		printf("addVertex failure  = %i!\n", rc);
		goto fail;
	}

//	int *vertexPropertyKeyIdSequence = malloc(sizeof(int));
//	char key1[5] = "";
//	sprintf(key1, "%.*s", 4, "key1");
//	rc = setPropertyKey(genv, (MDB_txn *) (long) txn, STRING, vertexPropertyKeyIdSequence, 5, key1, 1, 0, 0);
//	if (rc != 0) {
//		printf("setPropertyKey failure  = %i!\n", rc);
//		goto fail;
//	}
//
//	rc = addOrUpdateStringIndexedProperty(genv, txn, cursor, vertexId1, *vertexPropertyKeyIdSequence, 5, key1, 1);
//
//	//Add a vertex
//	long long vertexId2 = genv->vertexIdSequence++;
//	rc = addVertex(cursor, genv->vertexDb, vertexId2, &vertexKey);
//	if (rc != 0) {
//		printf("addVertex failure  = %i!\n", rc);
//		goto fail;
//	}
//
//	rc = addOrUpdateStringIndexedProperty(genv, txn, cursor, vertexId2, *vertexPropertyKeyIdSequence, 5, key1, 1);
//
//	mdb_cursor_close(cursor);
//	thundergraph_commit(genv, txn);
//
//	printf("traverseVertexPropertyKeyDb\n");
//
//	rc = mdb_txn_begin(genv->env, NULL, 1, &txn);
//	if (rc != 0) {
//		printf("begin transaction failure  = %i!\n", rc);
//		goto fail;
//	}
//
//	rc = traverseVertexPropertyKeyDb(genv, txn);
//
//	if (rc == MDB_NOTFOUND) {
//		printf("traverseVertexDb\n");
//		rc = traverseVertexDb(genv, txn);
//		if (rc == MDB_NOTFOUND) {
//			rc = traverseStringIndexDb(genv, txn, genv->vertexStringIndexDb);
//		}
//	}
//	thundergraph_commit(genv, txn);
//
//	rc = mdb_txn_begin(genv->env, NULL, 1, &txn);
//	if (rc != 0) {
//		printf("begin transaction failure  = %i!\n", rc);
//		goto fail;
//	}
//	rc = mdb_cursor_open(txn, genv->vertexStringIndexDb, &cursor);
//	if (rc != 0) {
//		printf("open cursor failure  = %i!\n", rc);
//		goto fail;
//	}
//
//	rc = deleteStringIndex(genv, txn, *vertexPropertyKeyIdSequence, 1);
//	if (rc != 0) {
//		printf("deleteStringIndex failure  = %i!\n", rc);
//		goto fail;
//	}
//
//	free(vertexPropertyKeyIdSequence);
//
//	//MDB_cursor *cursor, int propertyKeyId, int propertyValueLength, char *value, long long int *vertexIdResultC
//	long long int *vertexIdResultC = malloc(sizeof(long long int));
//	rc = getFirstElementForKeyValueFromStringIndex(cursor, 0, 5, "key1", vertexIdResultC);
//	if (rc == 0) {
//		printf("getFirstVertexForKeyValueFromStringIndex vertexid = %lld\n", *vertexIdResultC);
//
//		rc = getNextElementForKeyValueFromStringIndex(cursor, 0, 5, "key1", vertexIdResultC);
//		if (rc == 0) {
//			printf("getFirstVertexForKeyValueFromStringIndex vertexid = %lld\n", *vertexIdResultC);
//		} else {
//			printf("getNextVertexForKeyValueFromStringIndex %i\n", rc);
//		}
//
//	}


	mdb_cursor_close(cursor);
	thundergraph_commit(genv, txn);
//	free(vertexIdResultC);

	fail:


	printf("closing graph! %i\n", rc);
	closeGraph(genv);
	return 0;
}
