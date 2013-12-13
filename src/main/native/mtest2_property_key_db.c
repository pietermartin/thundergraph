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

int addPropertyKey(GLMDB_env *genv, MDB_txn *txn, MDB_cursor *cursor, int propertyKeyLength, char *key1, char *value1);
int callAddProperty(GLMDB_env *genv,MDB_txn *txn, MDB_cursor *cursor, int propertyKeyLength, char *key1, char *value1);

int main(int argc,char * argv[])
{
	int rc;
	GLMDB_env *genv;
	MDB_txn *txn;
	MDB_cursor *cursor;
	printf("opening graph!\n");
	rc = openGraph(&genv, "/home/pieter/Downloads/glmdb-blueprints/src/main/native/testdb");
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

	int vertexPropertyKeyIdSequence = genv->vertexPropertyKeyIdSequence;
	char key1[5] = "";

	sprintf(key1, "%.*s", 4, "key1");
	rc = setPropertyKey(genv, (MDB_txn *) (long) txn, STRING, &vertexPropertyKeyIdSequence, 5, key1, 1, 0, 0);

	sprintf(key1, "%.*s", 4, "key2");
	rc = setPropertyKey(genv, (MDB_txn *) (long) txn, STRING, &vertexPropertyKeyIdSequence, 5, key1, 1, 0, 0);

	sprintf(key1, "%.*s", 4, "key3");
	rc = setPropertyKey(genv, (MDB_txn *) (long) txn, STRING, &vertexPropertyKeyIdSequence, 5, key1, 1, 0, 0);

	sprintf(key1, "%.*s", 4, "key4");
	rc = setPropertyKey(genv, (MDB_txn *) (long) txn, STRING, &vertexPropertyKeyIdSequence, 5, key1, 1, 0, 0);

	sprintf(key1, "%.*s", 4, "key5");
	rc = setPropertyKey(genv, (MDB_txn *) (long) txn, STRING, &vertexPropertyKeyIdSequence, 5, key1, 1, 0, 0);

	sprintf(key1, "%.*s", 4, "key6");
	rc = setPropertyKey(genv, (MDB_txn *) (long) txn, STRING, &vertexPropertyKeyIdSequence, 5, key1, 1, 0, 0);

	sprintf(key1, "%.*s", 4, "key7");
	rc = setPropertyKey(genv, (MDB_txn *) (long) txn, STRING, &vertexPropertyKeyIdSequence, 5, key1, 1, 0, 0);

	sprintf(key1, "%.*s", 4, "key8");
	rc = setPropertyKey(genv, (MDB_txn *) (long) txn, STRING, &vertexPropertyKeyIdSequence, 5, key1, 1, 0, 0);

	sprintf(key1, "%.*s", 4, "key9");
	rc = setPropertyKey(genv, (MDB_txn *) (long) txn, STRING, &vertexPropertyKeyIdSequence, 5, key1, 1, 0, 0);

	sprintf(key1, "%.*s", 4, "key0");
	rc = setPropertyKey(genv, (MDB_txn *) (long) txn, STRING, &vertexPropertyKeyIdSequence, 5, key1, 1, 0, 0);

	mdb_cursor_close(cursor);
	thundergraph_commit(genv, txn);

	printf("traverseVertexPropertyKeyDb\n");

	rc = traverseVertexPropertyKeyDb(genv->env, genv->vertexPropertyKeyDb);

	if (rc == MDB_NOTFOUND) {
		printf("traverseVertexDb\n");
		rc = traverseVertexDb(genv->env, genv->vertexDb);
	}

	fail:
	printf("closing graph! %i\n", rc);
	closeGraph(genv);
	return 0;
}

int callAddProperty(GLMDB_env *genv,MDB_txn *txn, MDB_cursor *vertexCursor, int propertyKeyLength, char *key, char *value) {
	int rc;
	rc = addPropertyKey(genv, txn, vertexCursor, propertyKeyLength, key, value);
	return rc;
}


int addPropertyKey(GLMDB_env *genv, MDB_txn *txn, MDB_cursor *vertexCursor, int propertyKeyLength, char *key1, char *value1) {
	int rc;
	MDB_val vertexKey;
	rc = addVertex(vertexCursor, genv->vertexDb, genv->vertexIdSequence++, &vertexKey);
	if (rc != 0) {
		printf("add out vertex failure  = %i!\n", rc);
		goto fail;
	}

	int propertyKeyId = 0;
	rc = setPropertyKey(genv, txn, STRING, &propertyKeyId, propertyKeyLength, key1, 1, 0, 0);
	if (rc != 0) {
		printf("setPropertyKey failure  = %i!\n", rc);
		goto fail;
	}

	rc = setVertexPropertyString(vertexCursor, 0, 0, value1);
	if (rc != 0) {
		printf("setVertexPropertyString failure  = %i!\n", rc);
		goto fail;
	}
	fail:
	return rc;
}

