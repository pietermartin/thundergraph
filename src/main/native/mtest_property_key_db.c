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

int addVertexAnd2Properties(GLMDB_env *genv, int propertyKeyLength, char *key1, char *value1);

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

	rc = addVertexAnd2Properties(genv, 4, "key1", "value1");
	if (rc != 0) {
		goto fail;
	}
	rc = addVertexAnd2Properties(genv, 4, "key2", "value2");
	if (rc != 0) {
		goto fail;
	}
	rc = addVertexAnd2Properties(genv, 4, "key3", "value3");
	if (rc != 0) {
		goto fail;
	}
	rc = addVertexAnd2Properties(genv, 4, "key4", "value3");
	rc = addVertexAnd2Properties(genv, 4, "key5", "value3");
	rc = addVertexAnd2Properties(genv, 4, "key6", "value3");
	rc = addVertexAnd2Properties(genv, 4, "key7", "value3");
	rc = addVertexAnd2Properties(genv, 4, "key8", "value3");
	rc = addVertexAnd2Properties(genv, 4, "key9", "value3");
	rc = addVertexAnd2Properties(genv, 4, "key10", "value3");
	rc = addVertexAnd2Properties(genv, 4, "key11", "value3");
	rc = addVertexAnd2Properties(genv, 4, "key12", "value3");
	rc = addVertexAnd2Properties(genv, 4, "key13", "value3");
	rc = addVertexAnd2Properties(genv, 4, "key14", "value3");

	MDB_txn *txn;
	rc = mdb_txn_begin(genv->env, NULL, 1, &txn);
	if (rc != 0) {
		printf("begin transaction failure  = %i!\n", rc);
		goto fail;
	}
	traverseVertexPropertyKeyDb(genv, txn);
	thundergraph_commit(genv, txn);

	fail:
	printf("closing graph!\n");
	closeGraph(genv);
	return 0;
}

int addVertexAnd2Properties(GLMDB_env *genv, int propertyKeyLength, char *key1, char *value1) {
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

	int propertyKeyId = 0;
	setPropertyKey(genv, txn, STRING, &propertyKeyId, propertyKeyLength, key1, 1, 0, 0);

	rc = setVertexPropertyString(cursor, 0, 0, propertyKeyLength, value1);
	if (rc != 0) {
		printf("setVertexPropertyChar failure  = %i!\n", rc);
		goto fail;
	}

	mdb_cursor_close(cursor);
	mdb_txn_commit(txn);
	fail:


	return rc;
}

