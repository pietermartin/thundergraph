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

typedef struct TestDbId {
	long long testId;
	int coreOrPropertyEnum;
	int propertykeyId;
	int labelId;
	long long edgeId;
} TestDbId;

int compareTestDbId(const MDB_val *key1, const MDB_val *key2);

int main(int argc,char * argv[])
{
	int rc;
	MDB_env *env;
	MDB_txn *txn;
	MDB_dbi db;
	rc = mdb_env_create(&env);
	if (rc != 0) {
		return rc;
	}
	rc = mdb_env_set_mapsize(env, 107374182400); //100G
	if (rc != 0) {
		return rc;
	}
	rc = mdb_env_set_maxdbs(env, 27);
	if (rc != 0) {
		return rc;
	}
	rc = mdb_env_open(env, "/home/pieter/Downloads/thundergraph/src/main/native/testdb", MDB_NOSYNC, 0664);
	if (rc != 0) {
		return rc;
	}

	rc = mdb_txn_begin(env, NULL, 0, &txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_open(txn, "testdb", MDB_CREATE | MDB_INTEGERKEY, &db);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}

	rc = mdb_set_compare(txn, db, compareTestDbId);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}

	rc = mdb_txn_commit(txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}

	rc = mdb_txn_begin(env, NULL, 0, &txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	int i= 0;
	for (i = 0; i < 1000; i++) {

		MDB_cursor *cursor;
		rc = mdb_cursor_open(txn, db, &cursor);
		if (rc != 0) {
			printf("open cursor failure  = %i!\n", rc);
			goto fail;
		}

		//Create a core vertex
		MDB_val key, data;
		TestDbId testDbId;
		testDbId.testId = i;
		testDbId.coreOrPropertyEnum = 0;
		testDbId.labelId = -1;
		testDbId.propertykeyId = -1;
		testDbId.edgeId = -1LL;
		key.mv_size = sizeof(TestDbId);
		key.mv_data = &testDbId;
		data.mv_size = 50;
		char *value = malloc(5);
		char v[] = "12345";
		memcpy(value, v, 5);
		data.mv_data = &v;
		mdb_cursor_put(cursor, &key, &data, MDB_NOOVERWRITE);
		free(value);

		//Create a vertex property
		MDB_val propertyKey, propertyData;
		TestDbId propertyTestDbId;
		propertyTestDbId.testId = i;
		propertyTestDbId.coreOrPropertyEnum = 1;
		propertyTestDbId.labelId = -1;
		propertyTestDbId.propertykeyId = -1;
		propertyTestDbId.edgeId = -1LL;
		propertyKey.mv_size = sizeof(TestDbId);
		propertyKey.mv_data = &propertyTestDbId;
		data.mv_size = 50;
		char *propertyValue = malloc(5);
		char propertyV[] = "12345";
		memcpy(propertyValue, propertyV, 5);
		data.mv_data = &propertyV;
		mdb_cursor_put(cursor, &propertyKey, &propertyData, MDB_NOOVERWRITE);
		free(propertyValue);

		//Create a vertex in edge
		MDB_val inEdgeKey, inEdgeData;
		TestDbId inEdgeTestDbId;
		inEdgeTestDbId.testId = i;
		inEdgeTestDbId.coreOrPropertyEnum = 2;
		inEdgeTestDbId.labelId = -1;
		inEdgeTestDbId.propertykeyId = -1;
		inEdgeTestDbId.edgeId = -1LL;
		inEdgeKey.mv_size = sizeof(TestDbId);
		inEdgeKey.mv_data = &inEdgeTestDbId;
		data.mv_size = 50;
		char *inEdgeValue = malloc(5);
		char inEdgeV[] = "12345";
		memcpy(inEdgeValue, inEdgeV, 5);
		data.mv_data = &inEdgeV;
		mdb_cursor_put(cursor, &inEdgeKey, &inEdgeData, MDB_NOOVERWRITE);
		mdb_cursor_close(cursor);
		free(inEdgeValue);

	}

	MDB_cursor *cursor;
	mdb_cursor_close(cursor);

	rc = mdb_cursor_open(txn, db, &cursor);
	if (rc != 0) {
		printf("open cursor failure  = %i!\n", rc);
		goto fail;
	}

	MDB_val key, data;
	for (i = 0; i < 1000; i++) {

		TestDbId testDbId;
		testDbId.testId = i;
		testDbId.coreOrPropertyEnum = 0;
		testDbId.labelId = -1;
		testDbId.propertykeyId = -1;
		testDbId.edgeId = -1LL;
		key.mv_size = sizeof(TestDbId);
		key.mv_data = &testDbId;

		rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_KEY);
		printf("mdb_cursor_get index = %i result = %i\n", i, rc);

		MDB_val keyDelete, dataDelete;
		TestDbId deleteTestDbId;
		deleteTestDbId.testId = i;
		deleteTestDbId.coreOrPropertyEnum = 0;
		deleteTestDbId.labelId = -1;
		deleteTestDbId.propertykeyId = -1;
		deleteTestDbId.edgeId = -1LL;
		keyDelete.mv_size = sizeof(TestDbId);
		keyDelete.mv_data = &deleteTestDbId;

		rc = mdb_del(txn, db, &keyDelete, &dataDelete);
		printf("mdb_del = %i\n", rc);

		MDB_val propertyKeyDelete, propertyDataDelete;
		TestDbId propertyDeleteTestDbId;
		propertyDeleteTestDbId.testId = i;
		propertyDeleteTestDbId.coreOrPropertyEnum = 1;
		propertyDeleteTestDbId.labelId = -1;
		propertyDeleteTestDbId.propertykeyId = -1;
		propertyDeleteTestDbId.edgeId = -1LL;
		propertyKeyDelete.mv_size = sizeof(TestDbId);
		propertyKeyDelete.mv_data = &propertyDeleteTestDbId;

		rc = mdb_del(txn, db, &propertyKeyDelete, &propertyDataDelete);
		printf("mdb_del = %i\n", rc);

		MDB_val inEdgeKeyDelete, inEdgeDataDelete;
		TestDbId inEdgeDeleteTestDbId;
		inEdgeDeleteTestDbId.testId = i;
		inEdgeDeleteTestDbId.coreOrPropertyEnum = 2;
		inEdgeDeleteTestDbId.labelId = -1;
		inEdgeDeleteTestDbId.propertykeyId = -1;
		inEdgeDeleteTestDbId.edgeId = -1LL;
		inEdgeKeyDelete.mv_size = sizeof(TestDbId);
		inEdgeKeyDelete.mv_data = &inEdgeDeleteTestDbId;

		rc = mdb_del(txn, db, &inEdgeKeyDelete, &inEdgeDataDelete);
		printf("mdb_del = %i\n", rc);


	}
	mdb_cursor_close(cursor);


	rc = mdb_cursor_open(txn, db, &cursor);
	if (rc != 0) {
		printf("open cursor failure  = %i!\n", rc);
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		TestDbId testDbId = *((TestDbId *) (key.mv_data));
		printf("keyId = %llu\n", testDbId.testId);
	}
	mdb_cursor_close(cursor);

	fail:
	mdb_close(env, db);
	mdb_env_close(env);
	printf("closing graph!\n");
	return 0;
}

int compareTestDbId(const MDB_val *key1, const MDB_val *key2) {

	TestDbId testDbId1 = (*(TestDbId *) (key1->mv_data));
	TestDbId testDbId2 = (*(TestDbId *) (key2->mv_data));

	long long vertex1Id = testDbId1.testId;
	long long vertex2Id = testDbId2.testId;
	if (vertex1Id == vertex2Id) {

		//Compare on label next
		int labelId1 = testDbId1.labelId;
		int labelId2 = testDbId2.labelId;
		if (labelId1 == labelId2) {

			//Compare coreOrPropertyEnum
			int coreOrProperty1 = testDbId1.coreOrPropertyEnum;
			int coreOrProperty2 = testDbId2.coreOrPropertyEnum;
			if (coreOrProperty1 == coreOrProperty2) {

				switch (coreOrProperty1) {
				case VCORE:
					return 0;
					break;
				case VPROPERTY_KEY:
					;
					int propertyKey1 = testDbId1.propertykeyId;
					int propertyKey2 = testDbId2.propertykeyId;
					return (propertyKey1 > propertyKey2) - (propertyKey1 < propertyKey2);
					break;
				case OUTLABEL:
					;
					long long edgeId1 = testDbId1.edgeId;
					long long edgeId2 = testDbId2.edgeId;
					return (edgeId1 > edgeId2) - (edgeId1 < edgeId2);
					break;
				case INLABEL:
					;
					long long edgeId11 = testDbId1.edgeId;
					long long edgeId22 = testDbId2.edgeId;
					return (edgeId11 > edgeId22) - (edgeId11 < edgeId22);
					break;
				}
			} else {
				return (coreOrProperty1 > coreOrProperty2) - (coreOrProperty1 < coreOrProperty2);
			}

		} else {
			return (labelId1 > labelId2) - (labelId1 < labelId2);
		}

	} else {
		return (vertex1Id > vertex2Id) - (vertex1Id < vertex2Id);
	}
	return 0;
}
