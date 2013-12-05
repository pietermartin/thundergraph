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

int addVertexAnd2Properties(GLMDB_env *genv);

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

	rc = addVertexAnd2Properties(genv);
	if (rc != 0) {
		goto fail;
	}

	printf("before traverseEdgeDb\n");
	traverseEdgeDb(genv->env, genv->edgeDb);

	fail:
	printf("closing graph!\n");
	closeGraph(genv);
	return 0;
}

int addVertexAnd2Properties(GLMDB_env *genv) {
	int rc;
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

	int *propertyKeyId = malloc(sizeof(int));
	*propertyKeyId = 0;
	char *propertyKey = malloc(5);
	char propertyKeyName[] = "name1";
	memcpy(propertyKey, propertyKeyName, 5);
	setPropertyKey(genv, txn, GLMDB_STRING, propertyKeyId, propertyKey);
	free(propertyKeyId);
	free(propertyKey);

	int *propertyKeyId2 = malloc(sizeof(int));
	*propertyKeyId2 = 0;
	char *propertyKey2 = malloc(5);
	char propertyKeyName2[] = "name2";
	memcpy(propertyKey2, propertyKeyName2, 5);
	setPropertyKey(genv, txn, GLMDB_STRING, propertyKeyId2, propertyKey2);
	free(propertyKeyId2);
	free(propertyKey2);


	char *propertyValue1 = malloc(5);
	char v1[] = "12345";
	memcpy(propertyValue1, v1, 5);
	rc = setVertexPropertyString(cursor, 0, 0, propertyValue1);
	if (rc != 0) {
		printf("setVertexPropertyChar failure  = %i!\n", rc);
		goto fail;
	}

	char *propertyValue2 = malloc(5);
	char v2[] = "12345";
	memcpy(propertyValue2, v2, 5);
	rc = setVertexPropertyString(cursor, 0, 1, propertyValue2);
	if (rc != 0) {
		printf("setVertexPropertyChar failure  = %i!\n", rc);
		goto fail;
	}
	fail:
	mdb_cursor_close(cursor);
	mdb_txn_commit(txn);
	return rc;
}
