#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lmdb.h"
#include "glmdb_jni.h"

#define	Z	"z"

static void prstat(MDB_stat *ms, char *name) {
	printf("%s\n", name);
	printf("  Tree depth: %u\n", ms->ms_depth);
	printf("  Branch pages: %"Z"u\n", ms->ms_branch_pages);
	printf("  Leaf pages: %"Z"u\n", ms->ms_leaf_pages);
	printf("  Overflow pages: %"Z"u\n", ms->ms_overflow_pages);
	printf("  Entries: %"Z"u\n", ms->ms_entries);
}

JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_init(JNIEnv *env, jclass that) {

	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_VERSION_MAJOR", "I"), (jint) MDB_VERSION_MAJOR);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_VERSION_MINOR", "I"), (jint) MDB_VERSION_MINOR);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_VERSION_PATCH", "I"), (jint) MDB_VERSION_PATCH);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_VERSION_FULL", "I"), (jint) MDB_VERSION_FULL);
//	(*env)->SetStaticLongField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_VERSION_DATE", "J"), (jlong) (intptr_t) MDB_VERSION_DATE);
//	(*env)->SetStaticLongField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_VERSION_STRING", "J"), (jlong) (intptr_t) MDB_VERSION_STRING);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_FIXEDMAP", "I"), (jint) MDB_FIXEDMAP);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_NOSUBDIR", "I"), (jint) MDB_NOSUBDIR);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_NOSYNC", "I"), (jint) MDB_NOSYNC);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_RDONLY", "I"), (jint) MDB_RDONLY);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_NOMETASYNC", "I"), (jint) MDB_NOMETASYNC);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_WRITEMAP", "I"), (jint) MDB_WRITEMAP);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_MAPASYNC", "I"), (jint) MDB_MAPASYNC);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_NOTLS", "I"), (jint) MDB_NOTLS);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_REVERSEKEY", "I"), (jint) MDB_REVERSEKEY);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_DUPSORT", "I"), (jint) MDB_DUPSORT);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_INTEGERKEY", "I"), (jint) MDB_INTEGERKEY);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_DUPFIXED", "I"), (jint) MDB_DUPFIXED);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_INTEGERDUP", "I"), (jint) MDB_INTEGERDUP);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_REVERSEDUP", "I"), (jint) MDB_REVERSEDUP);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_CREATE", "I"), (jint) MDB_CREATE);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_NOOVERWRITE", "I"), (jint) MDB_NOOVERWRITE);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_NODUPDATA", "I"), (jint) MDB_NODUPDATA);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_CURRENT", "I"), (jint) MDB_CURRENT);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_RESERVE", "I"), (jint) MDB_RESERVE);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_APPEND", "I"), (jint) MDB_APPEND);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_APPENDDUP", "I"), (jint) MDB_APPENDDUP);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_MULTIPLE", "I"), (jint) MDB_MULTIPLE);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_FIRST", "I"), (jint) MDB_FIRST);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_FIRST_DUP", "I"), (jint) MDB_FIRST_DUP);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_GET_BOTH", "I"), (jint) MDB_GET_BOTH);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_GET_BOTH_RANGE", "I"), (jint) MDB_GET_BOTH_RANGE);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_GET_CURRENT", "I"), (jint) MDB_GET_CURRENT);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_GET_MULTIPLE", "I"), (jint) MDB_GET_MULTIPLE);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_LAST", "I"), (jint) MDB_LAST);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_LAST_DUP", "I"), (jint) MDB_LAST_DUP);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_NEXT", "I"), (jint) MDB_NEXT);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_NEXT_DUP", "I"), (jint) MDB_NEXT_DUP);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_NEXT_MULTIPLE", "I"), (jint) MDB_NEXT_MULTIPLE);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_NEXT_NODUP", "I"), (jint) MDB_NEXT_NODUP);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_PREV", "I"), (jint) MDB_PREV);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_PREV_DUP", "I"), (jint) MDB_PREV_DUP);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_PREV_NODUP", "I"), (jint) MDB_PREV_NODUP);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_SET", "I"), (jint) MDB_SET);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_SET_KEY", "I"), (jint) MDB_SET_KEY);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_SET_RANGE", "I"), (jint) MDB_SET_RANGE);
//	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "EINVAL", "I"), (jint) EINVAL);
//	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "EACCES", "I"), (jint) EACCES);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_SUCCESS", "I"), (jint) MDB_SUCCESS);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_KEYEXIST", "I"), (jint) MDB_KEYEXIST);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_NOTFOUND", "I"), (jint) MDB_NOTFOUND);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_PAGE_NOTFOUND", "I"), (jint) MDB_PAGE_NOTFOUND);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_CORRUPTED", "I"), (jint) MDB_CORRUPTED);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_PANIC", "I"), (jint) MDB_PANIC);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_VERSION_MISMATCH", "I"), (jint) MDB_VERSION_MISMATCH);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_INVALID", "I"), (jint) MDB_INVALID);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_MAP_FULL", "I"), (jint) MDB_MAP_FULL);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_DBS_FULL", "I"), (jint) MDB_DBS_FULL);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_READERS_FULL", "I"), (jint) MDB_READERS_FULL);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_TLS_FULL", "I"), (jint) MDB_TLS_FULL);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_TXN_FULL", "I"), (jint) MDB_TXN_FULL);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_CURSOR_FULL", "I"), (jint) MDB_CURSOR_FULL);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_PAGE_FULL", "I"), (jint) MDB_PAGE_FULL);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_MAP_RESIZED", "I"), (jint) MDB_MAP_RESIZED);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_INCOMPATIBLE", "I"), (jint) MDB_INCOMPATIBLE);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_BAD_RSLOT", "I"), (jint) MDB_BAD_RSLOT);
	(*env)->SetStaticIntField(env, that, (*env)->GetStaticFieldID(env, that, "MDB_LAST_ERRCODE", "I"), (jint) MDB_LAST_ERRCODE);
	return;
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_env_get_path
 * Signature: (J[[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1env_1get_1path(JNIEnv *env, jclass that, jlong glmdbEnv,
		jobjectArray path) {

	jint rc;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	const char **pathPointer = malloc(sizeof(void *));
	rc = mdb_env_get_path(glmdb_env->env, pathPointer);
	if (rc == 0) {
		int pathLength = strlen(pathPointer[0]);
		jbyteArray byteArray = (*env)->NewByteArray(env, pathLength);
		jbyte *cbytes = (*env)->GetByteArrayElements(env, byteArray, NULL);
		memcpy(cbytes, pathPointer[0], pathLength);
		(*env)->SetObjectArrayElement(env, path, 0, byteArray);
		(*env)->ReleaseByteArrayElements(env, byteArray, cbytes, 0);
	}
	free(pathPointer);
	return rc;

}

JNIEXPORT jstring JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1strerror(JNIEnv *env, jclass that, jint error) {

	char *mdbError = mdb_strerror(error);
	jstring message = (*env)->NewStringUTF(env, mdbError);
	return message;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    print_db
 * Signature: (JJI)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_print_1db(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn, jint dbEnum) {

	int rc = 0;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	switch (dbEnum) {
	case VERTEX_DB:
		printf("VERTEX_DB...\n");
		traverseVertexDb(glmdb_env, (MDB_txn *) (long) txn);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->vertexDb, "vertexDb");
		break;
	case EDGE_DB:
		printf("EDGE_DB...\n");
		traverseEdgeDb(glmdb_env, (MDB_txn *) (long) txn);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->edgeDb, "edgeDb");
		break;
	case VERTEX_PROPERTY_DB:
		printf("VERTEX_PROPERTY_DB...\n");
		traverseVertexPropertyKeyDb(glmdb_env, (MDB_txn *) (long) txn);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->vertexPropertyKeyDb, "vertexPropertyKeyDb");
		break;
	case EDGE_PROPERTY_DB:
		printf("EDGE_PROPERTY_DB...\n");
		traverseEdgePropertyKeyDb(glmdb_env, (MDB_txn *) (long) txn);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->edgePropertyKeyDb, "edgePropertyKeyDb");
		break;
	case LABEL_DB:
		printf("LABEL_DB...\n");
		traverseLabelDb(glmdb_env, (MDB_txn *) (long) txn);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->labelDb, "labelDb");
		break;
	case CONFIG_DB:
		printf("CONFIG_DB...\n");
		traverseConfigDb(glmdb_env, (MDB_txn *) (long) txn);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->configDb, "configDb");
		break;
	case VERTEX_BOOLEAN_INDEX:
		break;
	case VERTEX_BYTE_INDEX:
		break;
	case VERTEX_SHORT_INDEX:
		break;
	case VERTEX_INT_INDEX:
		break;
	case VERTEX_LONG_INDEX:
		break;
	case VERTEX_FLOAT_INDEX:
		break;
	case VERTEX_DOUBLE_INDEX:
		break;
	case VERTEX_CHAR_INDEX:
		break;
	case VERTEX_STRING_INDEX:
		break;
	case EDGE_BOOLEAN_INDEX:
		break;
	case EDGE_BYTE_INDEX:
		break;
	case EDGE_SHORT_INDEX:
		break;
	case EDGE_INT_INDEX:
		break;
	case EDGE_LONG_INDEX:
		break;
	case EDGE_FLOAT_INDEX:
		break;
	case EDGE_DOUBLE_INDEX:
		break;
	case EDGE_CHAR_INDEX:
		break;
	case EDGE_STRING_INDEX:
		break;
	default:
		rc = GLMDB_INVALID_DB;
	}
	return rc;

}


JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_glmdb_1env_1create(JNIEnv * env, jclass that, jstring path,
		jlongArray pointerArray) {

	const char *dbPath = NULL;
	jlong *mdbEnv = NULL;
	jint rc = 0;
	if (path) {
		if ((dbPath = (*env)->GetStringUTFChars(env, path, NULL)) == NULL) {
			goto fail;
		}
	}
	if (pointerArray) {
		if ((mdbEnv = (*env)->GetLongArrayElements(env, pointerArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) openGraph((GLMDB_env **) mdbEnv, dbPath);
	fail: if (pointerArray && mdbEnv) {
		(*env)->ReleaseLongArrayElements(env, pointerArray, mdbEnv, 0);
	}
	if (path && dbPath) {
		(*env)->ReleaseStringUTFChars(env, path, dbPath);
	}
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    glmdb_env_close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_glmdb_1env_1close(JNIEnv *env, jclass that, jlong glmdbEnv) {

	closeGraph((GLMDB_env *) (long) glmdbEnv);

}

JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1begin(JNIEnv *env, jclass that, jlong glmdbEnv, jlong parent,
		jlong flags, jlongArray txnArray) {

	jint rc = 0;
	jlong *txn = NULL;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	if (txnArray) {
		if ((txn = (*env)->GetLongArrayElements(env, txnArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = mdb_txn_begin(glmdb_env->env, (MDB_txn *) (long) parent, (unsigned int) flags, (MDB_txn **) txn);

	fail: if (txnArray && txn) {
		(*env)->ReleaseLongArrayElements(env, txnArray, txn, 0);
	}
	return rc;

}

JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1renew(JNIEnv *env, jclass that, jlong txn) {

	jint rc = 0;
	rc = (jint) mdb_txn_renew((MDB_txn *) (long) txn);
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_txn_commit
 * Signature: (JJZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1commit(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn,
		jboolean readOnly) {

	int rc = 0;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	MDB_txn *mdbtxn = (MDB_txn *) (long) txn;
	if (readOnly == 0) {
		rc = thundergraph_commit(glmdb_env, mdbtxn);
	} else {
		rc = mdb_txn_commit(mdbtxn);
	}
	return rc;
}

int thundergraph_commit(GLMDB_env * glmdb_env, MDB_txn *txn) {

	jint rc = 0;
	//save all the sequences
	rc = saveSequenceHigh(glmdb_env, txn, VERTEX_ID_SEQUENCE);
	if (rc == 0) {
		rc = saveSequenceHigh(glmdb_env, txn, EDGE_ID_SEQUENCE);
	}
	if (rc == 0) {
		rc = saveSequenceHigh(glmdb_env, txn, VERTEX_PROPERTY_KEY_ID_SEQUENCE);
	}
	if (rc == 0) {
		rc = saveSequenceHigh(glmdb_env, txn, EDGE_PROPERTY_KEY_ID_SEQUENCE);
	}
	if (rc == 0) {
		rc = saveSequenceHigh(glmdb_env, txn, LABEL_ID_SEQUENCE);
	}
	if (rc == 0) {
		rc = (jint) mdb_txn_commit(txn);
	}
	return rc;

}

int saveSequenceHigh(GLMDB_env * glmdb_env, MDB_txn *txn, enum SequenceEnum sequenceEnum) {
	int rc = 0;
	int sequenceKey;
	long long longSequenceId;
	int intSequenceId;
	MDB_val key, data;
	switch (sequenceEnum) {
	case VERTEX_ID_SEQUENCE:
		key.mv_size = sizeof(VERTEX_ID_SEQUENCE);
		sequenceKey = VERTEX_ID_SEQUENCE;
		key.mv_data = &sequenceKey;
		data.mv_size = sizeof(long long);
		longSequenceId = glmdb_env->vertexIdSequence;
		data.mv_data = &longSequenceId;
		rc = mdb_put(txn, glmdb_env->configDb, &key, &data, 0);
		break;
	case EDGE_ID_SEQUENCE:
		key.mv_size = sizeof(EDGE_ID_SEQUENCE);
		sequenceKey = EDGE_ID_SEQUENCE;
		key.mv_data = &sequenceKey;
		data.mv_size = sizeof(long long);
		longSequenceId = glmdb_env->edgeIdSequence;
		data.mv_data = &longSequenceId;
		rc = mdb_put(txn, glmdb_env->configDb, &key, &data, 0);
		break;
	case VERTEX_PROPERTY_KEY_ID_SEQUENCE:
		key.mv_size = sizeof(VERTEX_PROPERTY_KEY_ID_SEQUENCE);
		sequenceKey = VERTEX_PROPERTY_KEY_ID_SEQUENCE;
		key.mv_data = &sequenceKey;
		data.mv_size = sizeof(long long);
		intSequenceId = glmdb_env->vertexPropertyKeyIdSequence;
		data.mv_data = &intSequenceId;
		rc = mdb_put(txn, glmdb_env->configDb, &key, &data, 0);
		break;
	case EDGE_PROPERTY_KEY_ID_SEQUENCE:
		key.mv_size = sizeof(EDGE_PROPERTY_KEY_ID_SEQUENCE);
		sequenceKey = EDGE_PROPERTY_KEY_ID_SEQUENCE;
		key.mv_data = &sequenceKey;
		data.mv_size = sizeof(long long);
		intSequenceId = glmdb_env->edgePropertyKeyIdSequence;
		data.mv_data = &intSequenceId;
		rc = mdb_put(txn, glmdb_env->configDb, &key, &data, 0);
		break;
	case LABEL_ID_SEQUENCE:
		key.mv_size = sizeof(LABEL_ID_SEQUENCE);
		sequenceKey = LABEL_ID_SEQUENCE;
		key.mv_data = &sequenceKey;
		data.mv_size = sizeof(long long);
		intSequenceId = glmdb_env->labelIdSequence;
		data.mv_data = &intSequenceId;
		rc = mdb_put(txn, glmdb_env->configDb, &key, &data, 0);
		break;
	default:
		rc = GLMDB_INVALID_SEQUENCE;
	}
	return rc;
}

JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1reset(JNIEnv *env, jclass that, jlong txn) {

	mdb_txn_reset((MDB_txn *) (long) txn);

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_txn_abort
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1abort(JNIEnv *env, jclass that, jlong glmdb_env, jlong txn) {

	mdb_txn_abort((MDB_txn *) (long) txn);

}

//JNIEnv *env, jclass that, jlong arg0, jlong arg1, jlongArray arg2
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1cursor_1open_1vertex_1db(JNIEnv *env, jclass that, jlong txn,
		jlong glmdbEnv, jlongArray cursorArray) {

	jlong *cursor = NULL;
	jint rc = 0;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexDb, (MDB_cursor **) cursor);
	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_cursor_open_property_key_db
 * Signature: (JJ[JZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1cursor_1open_1property_1key_1db(JNIEnv *env, jclass that, jlong txn,
		jlong glmdbEnv, jlongArray cursorArray, jboolean vertex) {

	jlong *cursor = NULL;
	jint rc = 0;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	if (vertex == 1) {
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexPropertyKeyDb, (MDB_cursor **) cursor);
	} else {
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgePropertyKeyDb, (MDB_cursor **) cursor);
	}
	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_cursor_open_label_db
 * Signature: (JJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1cursor_1open_1label_1db(JNIEnv *env, jclass that, jlong txn,
		jlong glmdbEnv, jlongArray cursorArray) {

	jlong *cursor = NULL;
	jint rc = 0;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->labelDb, (MDB_cursor **) cursor);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_cursor_open_and_position_on_edge_vertex_db
 * Signature: (JJJIIJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1cursor_1open_1and_1position_1on_1edge_1vertex_1db(JNIEnv *env,
		jclass that, jlong txn, jlong glmdbEnv, jlong vertexId, jint direction, jint labelId, jlong edgeId, jlongArray cursorArray) {

	MDB_cursor *mdbCursor;
	jlong *cursor = NULL;
	jint rc = 0;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}
	MDB_val key, data;
	VertexDbId vertexDbId;
	vertexDbId.vertexId = vertexId;
	if (direction == 0) {
		vertexDbId.coreOrPropertyEnum = OUTLABEL;
	} else if (direction == 1) {
		vertexDbId.coreOrPropertyEnum = INLABEL;
	} else {
		rc = GLMDB_DB_INVALID_DIRECTION;
		goto fail;
	}
	vertexDbId.propertykeyId = -1;
	vertexDbId.labelId = labelId;
	vertexDbId.edgeId = edgeId;

	key.mv_size = sizeof(VertexDbId);
	key.mv_data = &vertexDbId;
	rc = mdb_cursor_get((MDB_cursor *) mdbCursor, &key, &data, MDB_SET);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}

	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_cursor_open_edge_db
 * Signature: (JJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1cursor_1open_1edge_1db(JNIEnv *env, jclass that, jlong txn,
		jlong glmdbEnv, jlongArray cursorArray) {

	jlong *cursor = NULL;
	jint rc = 0;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeDb, (MDB_cursor **) cursor);
	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_cursor_close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1cursor_1close(JNIEnv *env, jclass that, jlong cursor) {

	mdb_cursor_close((MDB_cursor *) (long) cursor);
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_cursor_renew
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1cursor_1renew(JNIEnv *env, jclass that, jlong txn, jlong cursor) {

	jint rc = 0;
	rc = (jint) mdb_cursor_renew((MDB_txn *) (long) txn, (MDB_cursor *) (long) cursor);
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_add_vertex
 * Signature: (JJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1add_1vertex(JNIEnv *env, jclass that, jlong glmdbEnv, jlong cursor,
		jlongArray vertexIdArray) {

	jint rc = 0;
	jlong *vertexId = NULL;
	MDB_val vertexKey;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	if (vertexIdArray) {
		if ((vertexId = (*env)->GetLongArrayElements(env, vertexIdArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = addVertex((MDB_cursor *) (long) cursor, glmdb_env->vertexDb, glmdb_env->vertexIdSequence, &vertexKey);
	glmdb_env->vertexIdSequence++;
	*vertexId = (*((VertexDbId *) (vertexKey.mv_data))).vertexId;

	fail: if (vertexIdArray && vertexId) {
		(*env)->ReleaseLongArrayElements(env, vertexIdArray, vertexId, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_add_edge
 * Signature: (JJJJI[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1add_1edge(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn,
		jlong outVertexId, jlong inVertexId, jint labelId, jlongArray edgeId) {

	jint rc = 0;
	jlong *edgeIdC = NULL;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;

	if (edgeId) {
		if ((edgeIdC = (*env)->GetLongArrayElements(env, edgeId, NULL)) == NULL) {
			goto fail;
		}
	}

	*edgeIdC = glmdb_env->edgeIdSequence++;

	rc = addEdge((MDB_txn *) (long) txn, glmdb_env->vertexDb, glmdb_env->edgeDb, *edgeIdC, (long) labelId, (long) outVertexId,
			(long) inVertexId);

	fail: if (edgeId && edgeIdC) {
		(*env)->ReleaseLongArrayElements(env, edgeId, edgeIdC, 0);
	}
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_boolean
 * Signature: (JJIZZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1boolean(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jboolean value, jboolean vertexKey) {

	jint rc = 0;
	if (vertexKey) {
		rc = setVertexPropertyBoolean((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
	} else {
		rc = setEdgePropertyBoolean((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_byte
 * Signature: (JJIBZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1byte(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jbyte value, jboolean vertexKey) {

	jint rc = 0;
	if (vertexKey) {
		rc = setVertexPropertyByte((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
	} else {
		rc = setEdgePropertyByte((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_short
 * Signature: (JJISZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1short(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jshort value, jboolean vertexKey) {

	jint rc = 0;
	if (vertexKey) {
		rc = setVertexPropertyShort((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
	} else {
		rc = setEdgePropertyShort((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_int
 * Signature: (JJIIZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1int(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jint value, jboolean vertexKey) {

	jint rc = 0;
	if (vertexKey) {
		rc = setVertexPropertyInt((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
	} else {
		rc = setEdgePropertyInt((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_long
 * Signature: (JJIJZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1long(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jlong value, jboolean vertexKey) {

	jint rc = 0;
	if (vertexKey) {
		rc = setVertexPropertyLong((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
	} else {
		rc = setEdgePropertyLong((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_float
 * Signature: (JJIFZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1float(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jfloat value, jboolean vertexKey) {

	jint rc = 0;
	if (vertexKey) {
		rc = setVertexPropertyFloat((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
	} else {
		rc = setEdgePropertyFloat((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_double
 * Signature: (JJIDZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1double(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jdouble value, jboolean vertexKey) {

	jint rc = 0;
	if (vertexKey) {
		rc = setVertexPropertyDouble((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
	} else {
		rc = setEdgePropertyDouble((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_char
 * Signature: (JJICZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1char(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jchar value, jboolean vertexKey) {

	jint rc = 0;
	if (vertexKey) {
		rc = setVertexPropertyChar((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
	} else {
		rc = setEdgePropertyChar((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_string
 * Signature: (JJJJILjava/lang/String;ZZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1string(JNIEnv *env, jclass that, jlong glmdbEnv,
		jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jstring value, jboolean vertex, jboolean indexed) {

	jint rc = 0;
	jint propertyValueLength = (*env)->GetStringUTFLength(env, value);
	char propertyValue[propertyValueLength];
	if (value) {
		(*env)->GetStringUTFRegion(env, value, 0, propertyValueLength, propertyValue);
		if (propertyValue == NULL) {
			goto fail;
		}
	}
	if (vertex) {
		rc = setVertexPropertyString((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, propertyValueLength,
				propertyValue);
	} else {
		rc = setEdgePropertyString((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, propertyValueLength, propertyValue);
	}

	if (rc == 0 && indexed) {
		GLMDB_env *glmdb_env = (GLMDB_env *) (long) glmdbEnv;
		MDB_cursor *indexCursor;
		rc = mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexStringIndexDb, &indexCursor);

//		MDB_val key, data;
//		StringIndexKeyStruct stringIndexKeyStruct;
//		stringIndexKeyStruct.propertyKeyId = (int) propertyKeyId;
//		stringIndexKeyStruct.value = propertyValue;
//		key.mv_size = strlen + sizeof(StringIndexKeyStruct);
//		key.mv_data = &stringIndexKeyStruct;
//		data.mv_size = sizeof(long long);
//		data.mv_data = (long) elementId;
//		rc = mdb_cursor_put(cursor, &key, &data, 0);
		mdb_cursor_close(indexCursor);
	}

	fail: return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_property_array
 * Signature: (JJI[[BZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1property_1array(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jobjectArray value, jboolean vertexKey) {

	jint rc = 0;
	MDB_val data;
	if (vertexKey) {
		rc = getVertexProperty((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &data);
	} else {
		rc = getEdgeProperty((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &data);
	}
	if (rc == 0) {
		jbyteArray byteArray = (*env)->NewByteArray(env, (size_t) data.mv_size);
		jbyte *cbytes = (*env)->GetByteArrayElements(env, byteArray, NULL);
		memcpy(cbytes, data.mv_data, data.mv_size);
		(*env)->SetObjectArrayElement(env, value, 0, byteArray);
		(*env)->ReleaseByteArrayElements(env, byteArray, cbytes, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_del_property
 * Signature: (JJI[[BZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1del_1property(JNIEnv *env, jclass that, jlong cursor, jlong elementId,
		jint propertyKeyId, jobjectArray value, jboolean vertexOrEdge) {

	jint rc = 0;
	MDB_val data;
	if (vertexOrEdge) {
		rc = getVertexProperty((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &data);
	} else {
		rc = getEdgeProperty((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &data);
	}
	if (rc == 0) {
		jbyteArray byteArray = (*env)->NewByteArray(env, (size_t) data.mv_size);
		jbyte *cbytes = (*env)->GetByteArrayElements(env, byteArray, NULL);
		memcpy(cbytes, data.mv_data, data.mv_size);
		(*env)->SetObjectArrayElement(env, value, 0, byteArray);
		(*env)->ReleaseByteArrayElements(env, byteArray, cbytes, 0);

		rc = mdb_cursor_del((MDB_cursor *) (long) cursor, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_property
 * Signature: (JJILorg/glmdb/blueprints/jni/Value;)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1property(JNIEnv *env, jclass that, jlong cursor, jlong vertexId,
		jint propertyKeyId, jobject value) {

	jint rc = 0;
	//TODO cache this
	jclass valueClass = (*env)->GetObjectClass(env, value);
	jfieldID mvDataFieldId = (*env)->GetFieldID(env, valueClass, "mv_data", "[B");

	MDB_val data;
	rc = getVertexProperty((MDB_cursor *) (long) cursor, (long) vertexId, (int) propertyKeyId, &data);

	jbyteArray byteArray = (*env)->NewByteArray(env, (size_t) data.mv_size);
	jbyte *cbytes = (*env)->GetByteArrayElements(env, byteArray, NULL);

	if (rc == 0) {
		memcpy(cbytes, data.mv_data, data.mv_size);
	}
	(*env)->SetObjectField(env, value, mvDataFieldId, byteArray);
	(*env)->ReleaseByteArrayElements(env, byteArray, cbytes, 0);

	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_property_keys
 * Signature: (JJ[[IZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1property_1keys(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jobjectArray values, jboolean vertexOrEdge) {

	jint rc = 0;
	jint *propertyKeyIdSize = (jint *) malloc(sizeof(int));
	jint **propertyKeyIdHolder = malloc(sizeof(void *));
	if (vertexOrEdge) {

		rc = getVertexPropertyKeys((MDB_cursor *) (long) cursor, elementId, propertyKeyIdSize, propertyKeyIdHolder);
		if (rc != 0) {
			goto fail;
		}

	} else {

		rc = getEdgePropertyKeys((MDB_cursor *) (long) cursor, elementId, propertyKeyIdSize, propertyKeyIdHolder);
		if (rc != 0) {
			goto fail;
		}

	}

	if (rc == 0) {
		jintArray intArray = (*env)->NewIntArray(env, *propertyKeyIdSize);
		jint *intArrayC = (*env)->GetIntArrayElements(env, intArray, NULL);
		memcpy(intArrayC, propertyKeyIdHolder[0], *propertyKeyIdSize * sizeof(jint));
		(*env)->SetObjectArrayElement(env, values, 0, intArray);
		(*env)->ReleaseIntArrayElements(env, intArray, intArrayC, 0);
	}

	fail: if (rc != MDB_NOTFOUND) {
		free(propertyKeyIdHolder[0]);
	}
	free(propertyKeyIdHolder);
	free(propertyKeyIdSize);
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_propertykey
 * Signature: (JJLjava/lang/String;I[IZZZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1propertykey(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn,
		jstring propertyKey, jint propertyKeyEnum, jintArray propertyKeyIdArray, jboolean vertex, jboolean indexed, jboolean overwrite) {

	jint rc = 0;
	jint *propertyKeyId = NULL;
	GLMDB_env *glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jsize strLength = (*env)->GetStringUTFLength(env, propertyKey);

	char propertyKeyCC[strLength];
	(*env)->GetStringUTFRegion(env, propertyKey, 0, strLength, propertyKeyCC);

	if (propertyKeyIdArray) {
		if ((propertyKeyId = (*env)->GetIntArrayElements(env, propertyKeyIdArray, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = setPropertyKey(glmdb_env, (MDB_txn *) (long) txn, propertyKeyEnum, propertyKeyId, strLength, propertyKeyCC, vertex, indexed,
			overwrite);

	fail: if (propertyKeyIdArray && propertyKeyId) {
		(*env)->ReleaseIntArrayElements(env, propertyKeyIdArray, propertyKeyId, 0);
	}
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_first_property_key
 * Signature: (J[I[I[Z[[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1first_1property_1key(JNIEnv *env, jclass that, jlong cursor,
		jintArray propertyKeyIdArray, jintArray propertyTypeEnumArray, jbooleanArray propertyIndexedArray, jobjectArray propertyKeyArray) {

	jint rc = 0;
	jint *propertyKeyIdArrayC = NULL;
	jint *propertyTypeEnumArrayC = NULL;
	jboolean *propertyIndexedArrayC = NULL;

	if (propertyKeyIdArray) {
		if ((propertyKeyIdArrayC = (*env)->GetIntArrayElements(env, propertyKeyIdArray, NULL)) == NULL) {
			goto fail;
		}
	}
	if (propertyTypeEnumArray) {
		if ((propertyTypeEnumArrayC = (*env)->GetIntArrayElements(env, propertyTypeEnumArray, NULL)) == NULL) {
			goto fail;
		}
	}
	if (propertyIndexedArray) {
		if ((propertyIndexedArrayC = (*env)->GetBooleanArrayElements(env, propertyIndexedArray, NULL)) == NULL) {
			goto fail;
		}
	}

	MDB_val key, data;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {
		char * propertyKeyId = (char *) (key.mv_data);
		PropertyKeyDataStruct propertyKeyDataStruct = (*((PropertyKeyDataStruct *) (data.mv_data)));
		*propertyKeyIdArrayC = propertyKeyDataStruct.propertyKeyId;
		*propertyIndexedArrayC = propertyKeyDataStruct.indexed;
		*propertyTypeEnumArrayC = propertyKeyDataStruct.type;

		jbyteArray byteArray = (*env)->NewByteArray(env, (size_t) key.mv_size);
		jbyte *byteArrayC = (*env)->GetByteArrayElements(env, byteArray, NULL);
		memcpy(byteArrayC, propertyKeyId, (size_t) key.mv_size);
		(*env)->SetObjectArrayElement(env, propertyKeyArray, 0, byteArray);
		(*env)->ReleaseByteArrayElements(env, byteArray, byteArrayC, 0);
	}

	fail: if (propertyKeyIdArray && propertyKeyIdArrayC) {
		(*env)->ReleaseIntArrayElements(env, propertyKeyIdArray, propertyKeyIdArrayC, 0);
	}
	if (propertyTypeEnumArray && propertyTypeEnumArrayC) {
		(*env)->ReleaseIntArrayElements(env, propertyTypeEnumArray, propertyTypeEnumArrayC, 0);
	}
	if (propertyIndexedArray && propertyIndexedArrayC) {
		(*env)->ReleaseBooleanArrayElements(env, propertyIndexedArray, propertyIndexedArrayC, 0);
	}
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_next_property_key
 * Signature: (J[I[I[Z[[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1next_1property_1key(JNIEnv *env, jclass that, jlong cursor,
		jintArray propertyKeyIdArray, jintArray propertyTypeEnumArray, jbooleanArray propertyIndexedArray, jobjectArray propertyKeyArray) {

	jint rc = 0;
	jint *propertyKeyIdArrayC = NULL;
	jint *propertyTypeEnumArrayC = NULL;
	jboolean *propertyIndexedArrayC = NULL;

	if (propertyKeyIdArray) {
		if ((propertyKeyIdArrayC = (*env)->GetIntArrayElements(env, propertyKeyIdArray, NULL)) == NULL) {
			goto fail;
		}
	}
	if (propertyTypeEnumArray) {
		if ((propertyTypeEnumArrayC = (*env)->GetIntArrayElements(env, propertyTypeEnumArray, NULL)) == NULL) {
			goto fail;
		}
	}
	if (propertyIndexedArray) {
		if ((propertyIndexedArrayC = (*env)->GetBooleanArrayElements(env, propertyIndexedArray, NULL)) == NULL) {
			goto fail;
		}
	}

	MDB_val key, data;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT);
	if (rc == 0) {
		char *propertyKeyId = (char *) (key.mv_data);
		PropertyKeyDataStruct propertyKeyDataStruct = (*((PropertyKeyDataStruct *) (data.mv_data)));
		*propertyKeyIdArrayC = propertyKeyDataStruct.propertyKeyId;
		*propertyIndexedArrayC = propertyKeyDataStruct.indexed;
		*propertyTypeEnumArrayC = propertyKeyDataStruct.type;

		jbyteArray byteArray = (*env)->NewByteArray(env, (size_t) key.mv_size);
		jbyte *byteArrayC = (*env)->GetByteArrayElements(env, byteArray, NULL);
		memcpy(byteArrayC, propertyKeyId, key.mv_size);
		(*env)->SetObjectArrayElement(env, propertyKeyArray, 0, byteArray);
		(*env)->ReleaseByteArrayElements(env, byteArray, byteArrayC, 0);
	}

	fail: if (propertyKeyIdArray && propertyKeyIdArrayC) {
		(*env)->ReleaseIntArrayElements(env, propertyKeyIdArray, propertyKeyIdArrayC, 0);
	}
	if (propertyTypeEnumArray && propertyTypeEnumArrayC) {
		(*env)->ReleaseIntArrayElements(env, propertyTypeEnumArray, propertyTypeEnumArrayC, 0);
	}
	if (propertyIndexedArray && propertyIndexedArrayC) {
		(*env)->ReleaseBooleanArrayElements(env, propertyIndexedArray, propertyIndexedArrayC, 0);
	}
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_first_label
 * Signature: (J[I[[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1first_1label(JNIEnv *env, jclass that, jlong cursor,
		jintArray labelIdArray, jobjectArray labelArray) {

	jint rc = 0;
	jint *labelIdArrayC = NULL;

	if (labelIdArray) {
		if ((labelIdArrayC = (*env)->GetIntArrayElements(env, labelIdArray, NULL)) == NULL) {
			goto fail;
		}
	}

	MDB_val key, data;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {
		char *label = (char *) (key.mv_data);
		*labelIdArrayC = *((jint *) (data.mv_data));

		jbyteArray labelByteArray = (*env)->NewByteArray(env, (size_t) key.mv_size);
		jbyte *labelByteArrayC = (*env)->GetByteArrayElements(env, labelByteArray, NULL);
		memcpy(labelByteArrayC, label, (size_t) key.mv_size);
		(*env)->SetObjectArrayElement(env, labelArray, 0, labelByteArray);
		(*env)->ReleaseByteArrayElements(env, labelByteArray, labelByteArrayC, 0);

	}

	fail: if (labelIdArray && labelIdArrayC) {
		(*env)->ReleaseIntArrayElements(env, labelIdArray, labelIdArrayC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_next_label
 * Signature: (J[I[[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1next_1label(JNIEnv *env, jclass that, jlong cursor,
		jintArray labelIdArray, jobjectArray labelArray) {

	jint rc = 0;
	jint *labelIdArrayC = NULL;

	if (labelIdArray) {
		if ((labelIdArrayC = (*env)->GetIntArrayElements(env, labelIdArray, NULL)) == NULL) {
			goto fail;
		}
	}

	MDB_val key, data;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT);
	if (rc == 0) {
		char *label = (char *) (key.mv_data);
		labelIdArrayC = (int *) (data.mv_data);

		jbyteArray byteArray = (*env)->NewByteArray(env, (size_t) key.mv_size);
		jbyte *byteArrayC = (*env)->GetByteArrayElements(env, byteArray, NULL);
		memcpy(byteArrayC, label, key.mv_size);
		(*env)->SetObjectArrayElement(env, labelArray, 0, byteArray);
		(*env)->ReleaseByteArrayElements(env, byteArray, byteArrayC, 0);
	}

	fail: if (labelIdArray && labelIdArrayC) {
		(*env)->ReleaseIntArrayElements(env, labelIdArray, labelIdArrayC, 0);
	}
	return rc;

}

int setPropertyKey(GLMDB_env *glmdb_env, MDB_txn * txn, int propertyKeyEnum, int *propertyKeyId, int propertyKeyLength, char propertyKeyC[],
		unsigned char vertex, unsigned char indexed, unsigned char overwrite) {

	int rc = 0;
	MDB_cursor *cursor;
	MDB_dbi propertyKeyDb;
	if (vertex == 0) {
		propertyKeyDb = glmdb_env->edgePropertyKeyDb;
	} else {
		propertyKeyDb = glmdb_env->vertexPropertyKeyDb;
	}

	PropertyKeyDataStruct propertyKeyDataStruct;
	if (!overwrite) {
		//new entry so give it an new id
		if (vertex) {
			propertyKeyDataStruct.propertyKeyId = glmdb_env->vertexPropertyKeyIdSequence++;
		} else {
			propertyKeyDataStruct.propertyKeyId = glmdb_env->edgePropertyKeyIdSequence++;
		}
	} else {
		propertyKeyDataStruct.propertyKeyId = *propertyKeyId;
	}
	propertyKeyDataStruct.indexed = indexed;
	switch ((int) propertyKeyEnum) {
	case BOOLEAN:
		propertyKeyDataStruct.type = BOOLEAN;
		break;
	case BYTE:
		propertyKeyDataStruct.type = BYTE;
		break;
	case SHORT:
		propertyKeyDataStruct.type = SHORT;
		break;
	case INT:
		propertyKeyDataStruct.type = INT;
		break;
	case LONG:
		propertyKeyDataStruct.type = LONG;
		break;
	case FLOAT:
		propertyKeyDataStruct.type = FLOAT;
		break;
	case DOUBLE:
		propertyKeyDataStruct.type = DOUBLE;
		break;
	case CHAR:
		propertyKeyDataStruct.type = CHAR;
		break;
	case STRING:
		propertyKeyDataStruct.type = STRING;
		break;
	case ARRAY_BOOLEAN:
		propertyKeyDataStruct.type = ARRAY_BOOLEAN;
		break;
	case ARRAY_BYTE:
		propertyKeyDataStruct.type = ARRAY_BYTE;
		break;
	case ARRAY_SHORT:
		propertyKeyDataStruct.type = ARRAY_SHORT;
		break;
	case ARRAY_INT:
		propertyKeyDataStruct.type = ARRAY_INT;
		break;
	case ARRAY_LONG:
		propertyKeyDataStruct.type = ARRAY_LONG;
		break;
	case ARRAY_FLOAT:
		propertyKeyDataStruct.type = ARRAY_FLOAT;
		break;
	case ARRAY_DOUBLE:
		propertyKeyDataStruct.type = ARRAY_DOUBLE;
		break;
	case ARRAY_CHAR:
		propertyKeyDataStruct.type = ARRAY_CHAR;
		break;
	case ARRAY_STRING:
		propertyKeyDataStruct.type = ARRAY_STRING;
		break;
	case UNSET:
		propertyKeyDataStruct.type = UNSET;
		break;
	}

	MDB_val key, data;
	key.mv_size = propertyKeyLength;
	key.mv_data = propertyKeyC;
	data.mv_size = sizeof(PropertyKeyDataStruct);
	data.mv_data = &propertyKeyDataStruct;
	rc = mdb_cursor_open(txn, propertyKeyDb, &cursor);
	if (rc != 0)
		goto fail;

	if (overwrite) {
		rc = mdb_cursor_put(cursor, &key, &data, 0/*Allow overwrites*/);
	} else {
		rc = mdb_cursor_put(cursor, &key, &data, MDB_NOOVERWRITE);
	}

	if (rc != 0)
		goto fail;

	*propertyKeyId = (*((PropertyKeyDataStruct *) (data.mv_data))).propertyKeyId;

	fail: mdb_cursor_close(cursor);
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_label
 * Signature: (JJLjava/lang/String;[I)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1label(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn,
		jstring label, jintArray labelIdArray) {

	jint rc = 0;
	jint *labelId = NULL;
	MDB_cursor *cursor;
	GLMDB_env *glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	MDB_dbi labelDb = glmdb_env->labelDb;

	jint labelLength = (*env)->GetStringUTFLength(env, label);
	char labelC[labelLength];
	if (label) {
		(*env)->GetStringUTFRegion(env, label, 0, labelLength, labelC);
		if (labelC == NULL) {
			goto fail;
		}
	}

	if (labelIdArray) {
		if ((labelId = (*env)->GetIntArrayElements(env, labelIdArray, NULL)) == NULL) {
			goto fail;
		}
	}

	*labelId = glmdb_env->labelIdSequence++;

	MDB_val key, data;
	key.mv_size = labelLength;
	key.mv_data = labelC;
	data.mv_size = sizeof(jint);
	data.mv_data = labelId;
	rc = mdb_cursor_open((MDB_txn *) (long) txn, labelDb, &cursor);
	if (rc != 0) {
		goto fail;
	}
	rc = mdb_cursor_put(cursor, &key, &data, MDB_NOOVERWRITE);
	if (rc != 0) {
		goto fail;
	}

	*labelId = *((jint *) (data.mv_data));

	fail: mdb_cursor_close(cursor);

	if (labelIdArray && labelId) {
		(*env)->ReleaseIntArrayElements(env, labelIdArray, labelId, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_vertex
 * Signature: (JJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1vertex(JNIEnv *env, jclass that, jlong cursor, jlong vertexId,
		jlongArray vertexIdResult) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	MDB_val key;
	rc = getVertex((MDB_cursor *) (long) cursor, vertexId, &key);
	if (rc != 0) {
		goto fail;
	}

	VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
	*vertexIdResultC = vertexDbId.vertexId;

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_remove_vertex
 * Signature: (JJJ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1remove_1vertex(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn,
		jlong vertexId) {

	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	MDB_txn * tx = (MDB_txn *) (long) txn;
	return removeVertex(tx, glmdb_env, vertexId);

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_first_vertex
 * Signature: (J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1first_1vertex(JNIEnv *env, jclass that, jlong cursor,
		jlongArray vertexIdResult) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundVertex = 1;
	MDB_val key, data;

	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {
		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (vertexDbId.coreOrPropertyEnum == VCORE) {
			foundVertex = 0;
		} else {
			rc = GLMDB_DB_CORRUPT;
		}
	}

	if (rc == 0 && foundVertex == 0) {
		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		*vertexIdResultC = vertexDbId.vertexId;
	}

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_next_vertex
 * Signature: (JJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1next_1vertex(JNIEnv *env, jclass that, jlong cursor,
		jlong previousVertexId, jlongArray vertexIdResult) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundVertex = 1;
	MDB_val vertexKey, data;
	VertexDbId id;
	initVertexDbId(&id);
	id.vertexId = (long) previousVertexId + 1L;
	id.coreOrPropertyEnum = VCORE;
	vertexKey.mv_size = sizeof(VertexDbId);
	vertexKey.mv_data = &id;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &vertexKey, &data, MDB_SET_RANGE);
	if (rc == 0) {
		VertexDbId vertexDbId = *((VertexDbId *) (vertexKey.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VCORE) {
			foundVertex = 0;
		}
	}

	if (rc == 0 && foundVertex == 0) {
		VertexDbId vertexDbId = *((VertexDbId *) (vertexKey.mv_data));
		*vertexIdResultC = vertexDbId.vertexId;
	}

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_first_vertex_for_key_value
 * Signature: (J[JI[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1first_1vertex_1for_1key_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKey, jbyteArray value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;
	jbyte *valueC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}
	if (value) {
		if ((valueC = (*env)->GetByteArrayElements(env, value, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKey) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	if (foundPropertyKeyAndValue != 0) {
		while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
			VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

			if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKey) {

				if (memcmp(valueC, data.mv_data, data.mv_size) == 0) {
					foundPropertyKeyAndValue = 0;
					break;
				}

			}
		}
	}
	if (rc == 0 && foundPropertyKeyAndValue == 0) {
		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		*vertexIdResultC = vertexDbId.vertexId;
	}

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	if (value && valueC) {
		(*env)->ReleaseByteArrayElements(env, value, valueC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_next_vertex_for_key_value
 * Signature: (J[JI[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1next_1vertex_1for_1key_1value(JNIEnv * env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKey, jbyteArray value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;
	jbyte *valueC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}
	if (value) {
		if ((valueC = (*env)->GetByteArrayElements(env, value, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKey) {

			if (memcmp(valueC, data.mv_data, data.mv_size) == 0) {
				foundPropertyKeyAndValue = 0;
				break;
			}
		}
	}

	if (rc == 0 && foundPropertyKeyAndValue == 0) {
		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		*vertexIdResultC = vertexDbId.vertexId;
	}

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	if (value && valueC) {
		(*env)->ReleaseByteArrayElements(env, value, valueC, 0);
	}

	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_edge
 * Signature: (JJ[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1edge(JNIEnv *env, jclass that, jlong cursor, jlong edgeId,
		jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

	jint rc = 0;
	jlong *edgeIdResultC = NULL;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;

	if (edgeIdResult) {
		if ((edgeIdResultC = (*env)->GetLongArrayElements(env, edgeIdResult, NULL)) == NULL) {
			goto fail;
		}
	}
	if (outVertexId) {
		if ((outVertexIdC = (*env)->GetLongArrayElements(env, outVertexId, NULL)) == NULL) {
			goto fail;
		}
	}
	if (inVertexId) {
		if ((inVertexIdC = (*env)->GetLongArrayElements(env, inVertexId, NULL)) == NULL) {
			goto fail;
		}
	}
	if (labelId) {
		if ((labelIdC = (*env)->GetIntArrayElements(env, labelId, NULL)) == NULL) {
			goto fail;
		}
	}

	MDB_val key, data;
	rc = getEdge((MDB_cursor *) (long) cursor, edgeId, &key, &data);
	if (rc != 0) {
		goto fail;
	}

	EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
	*edgeIdResultC = edgeDbId.edgeId;
	EdgeData edgeData = *((EdgeData *) (data.mv_data));
	*outVertexIdC = edgeData.vertexOutId;
	*inVertexIdC = edgeData.vertexInId;
	*labelIdC = edgeData.labelId;

	fail: if (edgeIdResult && edgeIdResultC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdResult, edgeIdResultC, 0);
	}
	if (outVertexId && outVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, outVertexId, outVertexIdC, 0);
	}
	if (inVertexId && inVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, inVertexId, inVertexIdC, 0);
	}
	if (labelId && labelIdC) {
		(*env)->ReleaseIntArrayElements(env, labelId, labelIdC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_remove_edge
 * Signature: (JJJ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1remove_1edge(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn,
		jlong edgeId) {

	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	MDB_txn * tx = (MDB_txn *) (long) txn;
	return removeEdge(tx, glmdb_env, edgeId);

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_first_edge
 * Signature: (J[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1first_1edge(JNIEnv * env, jclass that, jlong cursor,
		jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

	jint rc = 0;
	jlong *edgeIdResultC = NULL;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;

	if (edgeIdResult) {
		if ((edgeIdResultC = (*env)->GetLongArrayElements(env, edgeIdResult, NULL)) == NULL) {
			goto fail;
		}
	}
	if (outVertexId) {
		if ((outVertexIdC = (*env)->GetLongArrayElements(env, outVertexId, NULL)) == NULL) {
			goto fail;
		}
	}
	if (inVertexId) {
		if ((inVertexIdC = (*env)->GetLongArrayElements(env, inVertexId, NULL)) == NULL) {
			goto fail;
		}
	}
	if (labelId) {
		if ((labelIdC = (*env)->GetIntArrayElements(env, labelId, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundEdge = 1;
	MDB_val key, data;
	EdgeDbId id;
	id.edgeId = -1;
	id.coreOrPropertyEnum = ECORE;
	id.propertykeyId = -1;
	key.mv_size = sizeof(EdgeDbId);
	key.mv_data = &id;

	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		switch (edgeDbId.coreOrPropertyEnum) {
		case ECORE:
			foundEdge = 0;
			break;
		default:
			rc = GLMDB_DB_CORRUPT;
			break;
		}
	}

	if (rc == 0 && foundEdge == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		*edgeIdResultC = edgeDbId.edgeId;
		EdgeData edgeData = *((EdgeData *) (data.mv_data));
		*outVertexIdC = edgeData.vertexOutId;
		*inVertexIdC = edgeData.vertexInId;
		*labelIdC = edgeData.labelId;
	}

	fail: if (edgeIdResult && edgeIdResultC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdResult, edgeIdResultC, 0);
	}
	if (outVertexId && outVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, outVertexId, outVertexIdC, 0);
	}
	if (inVertexId && inVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, inVertexId, inVertexIdC, 0);
	}
	if (labelId && labelIdC) {
		(*env)->ReleaseIntArrayElements(env, labelId, labelIdC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_next_edge
 * Signature: (JJ[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1next_1edge(JNIEnv *env, jclass that, jlong cursor,
		jlong previousEdgeId, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

	jint rc = 0;
	jlong *edgeIdResultC = NULL;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;

	if (edgeIdResult) {
		if ((edgeIdResultC = (*env)->GetLongArrayElements(env, edgeIdResult, NULL)) == NULL) {
			goto fail;
		}
	}
	if (outVertexId) {
		if ((outVertexIdC = (*env)->GetLongArrayElements(env, outVertexId, NULL)) == NULL) {
			goto fail;
		}
	}
	if (inVertexId) {
		if ((inVertexIdC = (*env)->GetLongArrayElements(env, inVertexId, NULL)) == NULL) {
			goto fail;
		}
	}
	if (labelId) {
		if ((labelIdC = (*env)->GetIntArrayElements(env, labelId, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundEdge = 1;
	MDB_val key, data;
	EdgeDbId id;
	id.edgeId = (long) previousEdgeId + 1L;
	id.coreOrPropertyEnum = ECORE;
	id.propertykeyId = -1;
	key.mv_size = sizeof(EdgeDbId);
	key.mv_data = &id;

	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == ECORE) {
			foundEdge = 0;
		}
	}

	if (rc == 0 && foundEdge == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		*edgeIdResultC = edgeDbId.edgeId;
		EdgeData edgeData = *((EdgeData *) (data.mv_data));
		*outVertexIdC = edgeData.vertexOutId;
		*inVertexIdC = edgeData.vertexInId;
		*labelIdC = edgeData.labelId;
	}

	fail: if (edgeIdResult && edgeIdResultC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdResult, edgeIdResultC, 0);
	}
	if (outVertexId && outVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, outVertexId, outVertexIdC, 0);
	}
	if (inVertexId && inVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, inVertexId, inVertexIdC, 0);
	}
	if (labelId && labelIdC) {
		(*env)->ReleaseIntArrayElements(env, labelId, labelIdC, 0);
	}
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_first_edge_for_key_value
 * Signature: (J[J[I[J[JI[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1first_1edge_1for_1key_1value(JNIEnv *env, jclass that, jlong cursor,
		jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKey, jbyteArray value) {

	jint rc = 0;
	jlong *edgeIdResultC = NULL;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;
	jbyte *valueC = NULL;

	if (edgeIdResult) {
		if ((edgeIdResultC = (*env)->GetLongArrayElements(env, edgeIdResult, NULL)) == NULL) {
			goto fail;
		}
	}
	if (outVertexId) {
		if ((outVertexIdC = (*env)->GetLongArrayElements(env, outVertexId, NULL)) == NULL) {
			goto fail;
		}
	}
	if (inVertexId) {
		if ((inVertexIdC = (*env)->GetLongArrayElements(env, inVertexId, NULL)) == NULL) {
			goto fail;
		}
	}
	if (labelId) {
		if ((labelIdC = (*env)->GetIntArrayElements(env, labelId, NULL)) == NULL) {
			goto fail;
		}
	}
	if (value) {
		if ((valueC = (*env)->GetByteArrayElements(env, value, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKey) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	if (foundPropertyKeyAndValue != 0) {
		while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
			EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

			if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKey) {

				if (memcmp(valueC, data.mv_data, data.mv_size) == 0) {
					foundPropertyKeyAndValue = 0;
					break;
				}

			}
		}
	}

	if (rc == 0 && foundPropertyKeyAndValue == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		*edgeIdResultC = edgeDbId.edgeId;
		EdgeData edgeData = *((EdgeData *) (data.mv_data));
		*outVertexIdC = edgeData.vertexOutId;
		*inVertexIdC = edgeData.vertexInId;
		*labelIdC = edgeData.labelId;
	}

	fail: if (edgeIdResult && edgeIdResultC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdResult, edgeIdResultC, 0);
	}
	if (outVertexId && outVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, outVertexId, outVertexIdC, 0);
	}
	if (inVertexId && inVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, inVertexId, inVertexIdC, 0);
	}
	if (labelId && labelIdC) {
		(*env)->ReleaseIntArrayElements(env, labelId, labelIdC, 0);
	}
	if (value && valueC) {
		(*env)->ReleaseByteArrayElements(env, value, valueC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_next_edge_for_key_value
 * Signature: (J[J[I[J[JI[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1next_1edge_1for_1key_1value(JNIEnv *env, jclass that, jlong cursor,
		jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKey, jbyteArray value) {

	jint rc = 0;
	jlong *edgeIdResultC = NULL;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;
	jbyte *valueC = NULL;

	if (edgeIdResult) {
		if ((edgeIdResultC = (*env)->GetLongArrayElements(env, edgeIdResult, NULL)) == NULL) {
			goto fail;
		}
	}
	if (outVertexId) {
		if ((outVertexIdC = (*env)->GetLongArrayElements(env, outVertexId, NULL)) == NULL) {
			goto fail;
		}
	}
	if (inVertexId) {
		if ((inVertexIdC = (*env)->GetLongArrayElements(env, inVertexId, NULL)) == NULL) {
			goto fail;
		}
	}
	if (labelId) {
		if ((labelIdC = (*env)->GetIntArrayElements(env, labelId, NULL)) == NULL) {
			goto fail;
		}
	}
	if (value) {
		if ((valueC = (*env)->GetByteArrayElements(env, value, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKey) {

			if (memcmp(valueC, data.mv_data, data.mv_size) == 0) {
				foundPropertyKeyAndValue = 0;
				break;
			}
		}
	}

	if (rc == 0 && foundPropertyKeyAndValue == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		*edgeIdResultC = edgeDbId.edgeId;
		EdgeData edgeData = *((EdgeData *) (data.mv_data));
		*outVertexIdC = edgeData.vertexOutId;
		*inVertexIdC = edgeData.vertexInId;
		*labelIdC = edgeData.labelId;
	}

	fail: if (edgeIdResult && edgeIdResultC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdResult, edgeIdResultC, 0);
	}
	if (outVertexId && outVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, outVertexId, outVertexIdC, 0);
	}
	if (inVertexId && inVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, inVertexId, inVertexIdC, 0);
	}
	if (labelId && labelIdC) {
		(*env)->ReleaseIntArrayElements(env, labelId, labelIdC, 0);
	}
	if (value && valueC) {
		(*env)->ReleaseByteArrayElements(env, value, valueC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_first_edge_from_vertex
 * Signature: (JIIJ[J[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1first_1edge_1from_1vertex(JNIEnv *env, jclass that, jlong cursor,
		jint direction, jint labelId, jlong fromVertexId, jlongArray edgeIdResult, jlongArray outVertexId, jlongArray inVertexId) {

	jint rc = 0;
	jlong *edgeIdResultC = NULL;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;

	if (edgeIdResult) {
		if ((edgeIdResultC = (*env)->GetLongArrayElements(env, edgeIdResult, NULL)) == NULL) {
			goto fail;
		}
	}
	if (outVertexId) {
		if ((outVertexIdC = (*env)->GetLongArrayElements(env, outVertexId, NULL)) == NULL) {
			goto fail;
		}
	}
	if (inVertexId) {
		if ((inVertexIdC = (*env)->GetLongArrayElements(env, inVertexId, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getFirstEdgefromVertex((MDB_cursor *) (long) cursor, direction, labelId, fromVertexId, edgeIdResultC, outVertexIdC, inVertexIdC);

	fail: if (edgeIdResult && edgeIdResultC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdResult, edgeIdResultC, 0);
	}
	if (outVertexId && outVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, outVertexId, outVertexIdC, 0);
	}
	if (inVertexId && inVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, inVertexId, inVertexIdC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_next_edge_from_vertex
 * Signature: (JIIJ[J[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1next_1edge_1from_1vertex(JNIEnv *env, jclass that, jlong cursor,
		jint direction, jint labelId, jlong fromVertexId, jlongArray edgeIdResult, jlongArray outVertexId, jlongArray inVertexId) {

	jint rc = 0;
	jlong *edgeIdResultC = NULL;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;

	if (edgeIdResult) {
		if ((edgeIdResultC = (*env)->GetLongArrayElements(env, edgeIdResult, NULL)) == NULL) {
			goto fail;
		}
	}
	if (outVertexId) {
		if ((outVertexIdC = (*env)->GetLongArrayElements(env, outVertexId, NULL)) == NULL) {
			goto fail;
		}
	}
	if (inVertexId) {
		if ((inVertexIdC = (*env)->GetLongArrayElements(env, inVertexId, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getNextEdgefromVertex((MDB_cursor *) (long) cursor, direction, labelId, fromVertexId, edgeIdResultC, outVertexIdC, inVertexIdC);

	fail: if (edgeIdResult && edgeIdResultC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdResult, edgeIdResultC, 0);
	}
	if (outVertexId && outVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, outVertexId, outVertexIdC, 0);
	}
	if (inVertexId && inVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, inVertexId, inVertexIdC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_first_edge_from_vertex_all_labels
 * Signature: (JIJ[I[J[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1first_1edge_1from_1vertex_1all_1labels(JNIEnv *env, jclass that,
		jlong cursor, jint direction, jlong fromVertexId, jintArray labelIdResult, jlongArray edgeIdResult, jlongArray outVertexId,
		jlongArray inVertexId) {

	jint rc = 0;
	jint *labelIdResultC = NULL;
	jlong *edgeIdResultC = NULL;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;

	if (labelIdResult) {
		if ((labelIdResultC = (*env)->GetIntArrayElements(env, labelIdResult, NULL)) == NULL) {
			goto fail;
		}
	}
	if (edgeIdResult) {
		if ((edgeIdResultC = (*env)->GetLongArrayElements(env, edgeIdResult, NULL)) == NULL) {
			goto fail;
		}
	}
	if (outVertexId) {
		if ((outVertexIdC = (*env)->GetLongArrayElements(env, outVertexId, NULL)) == NULL) {
			goto fail;
		}
	}
	if (inVertexId) {
		if ((inVertexIdC = (*env)->GetLongArrayElements(env, inVertexId, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getFirstEdgefromVertexAllLabels((MDB_cursor *) (long) cursor, direction, fromVertexId, labelIdResultC, edgeIdResultC, outVertexIdC,
			inVertexIdC);

	fail: if (labelIdResultC && labelIdResultC) {
		(*env)->ReleaseIntArrayElements(env, labelIdResult, labelIdResultC, 0);
	}
	if (edgeIdResult && edgeIdResultC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdResult, edgeIdResultC, 0);
	}
	if (outVertexId && outVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, outVertexId, outVertexIdC, 0);
	}
	if (inVertexId && inVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, inVertexId, inVertexIdC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_next_edge_from_vertex_all_labels
 * Signature: (JIJ[I[J[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1next_1edge_1from_1vertex_1all_1labels(JNIEnv *env, jclass that,
		jlong cursor, jint direction, jlong fromVertexId, jintArray labelIdResult, jlongArray edgeIdResult, jlongArray outVertexId,
		jlongArray inVertexId) {

	jint rc = 0;
	jint *labelIdResultC = NULL;
	jlong *edgeIdResultC = NULL;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;

	if (labelIdResult) {
		if ((labelIdResultC = (*env)->GetIntArrayElements(env, labelIdResult, NULL)) == NULL) {
			goto fail;
		}
	}
	if (edgeIdResult) {
		if ((edgeIdResultC = (*env)->GetLongArrayElements(env, edgeIdResult, NULL)) == NULL) {
			goto fail;
		}
	}
	if (outVertexId) {
		if ((outVertexIdC = (*env)->GetLongArrayElements(env, outVertexId, NULL)) == NULL) {
			goto fail;
		}
	}
	if (inVertexId) {
		if ((inVertexIdC = (*env)->GetLongArrayElements(env, inVertexId, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getNextEdgefromVertexAllLabels((MDB_cursor *) (long) cursor, direction, fromVertexId, labelIdResultC, edgeIdResultC, outVertexIdC,
			inVertexIdC);

	fail: if (labelIdResult && labelIdResultC) {
		(*env)->ReleaseIntArrayElements(env, labelIdResult, labelIdResultC, 0);
	}
	if (edgeIdResult && edgeIdResultC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdResult, edgeIdResultC, 0);
	}
	if (outVertexId && outVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, outVertexId, outVertexIdC, 0);
	}
	if (inVertexId && inVertexIdC) {
		(*env)->ReleaseLongArrayElements(env, inVertexId, inVertexIdC, 0);
	}
	return rc;

}

void buffer_copy(const void *source, size_t source_pos, void *dest, size_t dest_pos, size_t length) {
	memmove(((char *) dest) + dest_pos, ((const char *) source) + source_pos, length);
}

int openGraph(GLMDB_env **genv, const char *path) {
	int rc;

	GLMDB_env *glmdbEnv;
	glmdbEnv = calloc(sizeof(GLMDB_env), 1);

	MDB_env *env;
	MDB_dbi configDb;
	MDB_dbi vertexDb;
	MDB_dbi edgeDb;
	MDB_dbi vertexPropertyKeyDb;
//	MDB_dbi vertexBooleanIndexDb;
//	MDB_dbi vertexByteIndexDb;
//	MDB_dbi vertexShortIndexDb;
//	MDB_dbi vertexIntIndexDb;
//	MDB_dbi vertexLongIndexDb;
//	MDB_dbi vertexFloatIndexDb;
//	MDB_dbi vertexDoubleIndexDb;
//	MDB_dbi vertexCharIndexDb;
//	MDB_dbi vertexStringIndexDb;

	MDB_dbi edgePropertyKeyDb;
//	MDB_dbi edgeBooleanIndexDb;
//	MDB_dbi edgeByteIndexDb;
//	MDB_dbi edgeShortIndexDb;
//	MDB_dbi edgeIntIndexDb;
//	MDB_dbi edgeLongIndexDb;
//	MDB_dbi edgeFloatIndexDb;
//	MDB_dbi edgeDoubleIndexDb;
//	MDB_dbi edgeCharIndexDb;
//	MDB_dbi edgeStringIndexDb;

	MDB_dbi labelDb;

	rc = mdb_env_create(&env);
	if (rc != 0) {
		return rc;
	}
	rc = mdb_env_set_mapsize(env, 107374182400); //100G
	if (rc != 0) {
		return rc;
	}
	rc = mdb_env_set_maxdbs(env, 7);
	if (rc != 0) {
		return rc;
	}
	rc = mdb_env_open(env, path, MDB_NOSYNC, 0664);
	if (rc != 0) {
		return rc;
	}

	//Create the config db
	rc = createDb(env, "configDb", MDB_CREATE | MDB_INTEGERKEY, &configDb, NULL);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->configDb = configDb;

	//Create the vertex db
	rc = createDb(env, "vertexDb", MDB_CREATE, &vertexDb, compareVertexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->vertexDb = vertexDb;

	//Create the edge db
	rc = createDb(env, "edgeDb", MDB_CREATE | MDB_INTEGERKEY, &edgeDb, compareEdgeDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->edgeDb = edgeDb;

	//Create the vertex property key db
	rc = createDb(env, "vertexPropertyKeyDb", MDB_CREATE, &vertexPropertyKeyDb, comparePropertyKeyDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->vertexPropertyKeyDb = vertexPropertyKeyDb;

	//Create the edge property key db
	rc = createDb(env, "edgePropertyKeyDb", MDB_CREATE, &edgePropertyKeyDb, comparePropertyKeyDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->edgePropertyKeyDb = edgePropertyKeyDb;

	//Create the label db
	rc = createDb(env, "labelDb", MDB_CREATE, &labelDb, NULL);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->labelDb = labelDb;

//	//Create the String index db
//	rc = createDb(env, "vertexStringIndexDb", MDB_CREATE, &vertexStringIndexDb, NULL);
//	if (rc != 0) {
//		return rc;
//	}
//	glmdbEnv->vertexStringIndexDb = vertexStringIndexDb;

	glmdbEnv->env = env;
	*genv = glmdbEnv;

	rc = loadSequences(glmdbEnv, VERTEX_ID_SEQUENCE);
	if (rc != 0) {
		return rc;
	}

	return rc;
}

int loadSequences(GLMDB_env *glmdbEnv, enum SequenceEnum sequenceEnum) {
	int rc;
	MDB_txn *txn;
	rc = mdb_txn_begin(glmdbEnv->env, NULL, 0, &txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	MDB_val key, data;
	int sequenceKey;
	switch (sequenceEnum) {
	case VERTEX_ID_SEQUENCE:
		key.mv_size = sizeof(VERTEX_ID_SEQUENCE);
		sequenceKey = VERTEX_ID_SEQUENCE;
		key.mv_data = &sequenceKey;
		rc = mdb_get(txn, glmdbEnv->configDb, &key, &data);
		if (rc == 0) {
			long long *sequenceId = ((long long *) (data.mv_data));
			glmdbEnv->vertexIdSequence = *sequenceId;
		} else if (rc == MDB_NOTFOUND) {
			rc = 0;
			glmdbEnv->vertexIdSequence = 0LL;
		}
		break;
	case EDGE_ID_SEQUENCE:
		key.mv_size = sizeof(EDGE_ID_SEQUENCE);
		sequenceKey = EDGE_ID_SEQUENCE;
		key.mv_data = &sequenceKey;
		rc = mdb_get(txn, glmdbEnv->configDb, &key, &data);
		if (rc == 0) {
			long long *sequenceId = ((long long *) (data.mv_data));
			glmdbEnv->edgeIdSequence = *sequenceId;
		} else if (rc == MDB_NOTFOUND) {
			rc = 0;
			glmdbEnv->edgeIdSequence = 0LL;
		}
		break;
	case VERTEX_PROPERTY_KEY_ID_SEQUENCE:
		key.mv_size = sizeof(VERTEX_PROPERTY_KEY_ID_SEQUENCE);
		sequenceKey = VERTEX_PROPERTY_KEY_ID_SEQUENCE;
		key.mv_data = &sequenceKey;
		rc = mdb_get(txn, glmdbEnv->configDb, &key, &data);
		if (rc == 0) {
			int *sequenceId = ((int *) (data.mv_data));
			glmdbEnv->vertexPropertyKeyIdSequence = *sequenceId;
		} else if (rc == MDB_NOTFOUND) {
			rc = 0;
			glmdbEnv->vertexPropertyKeyIdSequence = 0;
		}
		break;
	case EDGE_PROPERTY_KEY_ID_SEQUENCE:
		key.mv_size = sizeof(EDGE_PROPERTY_KEY_ID_SEQUENCE);
		sequenceKey = EDGE_PROPERTY_KEY_ID_SEQUENCE;
		key.mv_data = &sequenceKey;
		rc = mdb_get(txn, glmdbEnv->configDb, &key, &data);
		if (rc == 0) {
			int *sequenceId = ((int *) (data.mv_data));
			glmdbEnv->edgePropertyKeyIdSequence = *sequenceId;
		} else if (rc == MDB_NOTFOUND) {
			rc = 0;
			glmdbEnv->edgePropertyKeyIdSequence = 0;
		}
		break;
	case LABEL_ID_SEQUENCE:
		key.mv_size = sizeof(LABEL_ID_SEQUENCE);
		sequenceKey = LABEL_ID_SEQUENCE;
		key.mv_data = &sequenceKey;
		rc = mdb_get(txn, glmdbEnv->configDb, &key, &data);
		if (rc == 0) {
			int *sequenceId = ((int *) (data.mv_data));
			glmdbEnv->labelIdSequence = *sequenceId;
		} else if (rc == MDB_NOTFOUND) {
			rc = 0;
			glmdbEnv->labelIdSequence = 0;
		}
		break;
	default:
		rc = GLMDB_INVALID_SEQUENCE;
	}

	rc = mdb_txn_commit(txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	return rc;
}

int createDb(MDB_env *env, char *name, unsigned int flags, MDB_dbi *db, MDB_cmp_func *cmp) {
	int rc;
	MDB_txn *txn;

	rc = mdb_txn_begin(env, NULL, 0, &txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_open(txn, name, flags, db);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}

	if (cmp != NULL) {
		rc = mdb_set_compare(txn, *db, cmp);
		if (rc != 0) {
			mdb_txn_abort(txn);
			return rc;
		}
	}

	rc = mdb_txn_commit(txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	return rc;
}

void closeGraph(GLMDB_env *genv) {
	MDB_env *env = genv->env;
	MDB_dbi configDb = genv->configDb;
	MDB_dbi vertexDb = genv->vertexDb;
	MDB_dbi edgeDb = genv->edgeDb;
	MDB_dbi vertexPropertyKeyDb = genv->vertexPropertyKeyDb;
	MDB_dbi edgePropertyKeyDb = genv->edgePropertyKeyDb;
	MDB_dbi labelDb = genv->labelDb;
//	MDB_dbi vertexStringIndexDb = genv->vertexStringIndexDb;

//	printDbStats(env, configDb, "configDb");
//	printDbStats(env, vertexDb, "vertexDb");
//	printDbStats(env, edgeDb, "edgeDb");
//	printDbStats(env, vertexPropertyKeyDb, "vertexPropertyKeyDb");
//	printDbStats(env, edgePropertyKeyDb, "edgePropertyKeyDb");
//	printDbStats(env, labelDb, "labelDb");
//	printDbStats(env, vertexStringIndexDb, "vertexStringIndexDb");

	mdb_close(env, configDb);
	mdb_close(env, vertexDb);
	mdb_close(env, edgeDb);
	mdb_close(env, vertexPropertyKeyDb);
	mdb_close(env, edgePropertyKeyDb);
	mdb_close(env, labelDb);
//	mdb_close(env, vertexStringIndexDb);

	mdb_env_close(env);
}

//MDB_val *vertexKey is out only
int addVertex(MDB_cursor *cursor, MDB_dbi vertexDb, jlong vertexId, MDB_val *vertexKey) {
	MDB_val data;
	VertexDbId id;
	initVertexDbId(&id);
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VCORE;
	(*vertexKey).mv_size = sizeof(VertexDbId);
	(*vertexKey).mv_data = &id;
	char myNull = '\0';
	data.mv_size = sizeof(char);
	data.mv_data = &myNull;
	return mdb_cursor_put(cursor, vertexKey, &data, MDB_NOOVERWRITE);
}

int removeVertex(MDB_txn *txn, GLMDB_env *genv, jlong vertexId) {
	//Remove all out and in edges
	int rc;
	MDB_val key, data;
	MDB_val inverseKey, inverseData;
	VertexDbId inverseId;
	initVertexDbId(&inverseId);
	MDB_cursor *vertexCursor;
	MDB_cursor *inverseCursor;
	MDB_cursor *edgeCursor;
	rc = mdb_cursor_open(txn, genv->vertexDb, &vertexCursor);
	if (rc != 0) {
		goto fail;
	}
	rc = mdb_cursor_open(txn, genv->vertexDb, &inverseCursor);
	if (rc != 0) {
		goto fail;
	}
	rc = mdb_cursor_open(txn, genv->edgeDb, &edgeCursor);
	if (rc != 0) {
		goto fail;
	}
	VertexDbId id;
	initVertexDbId(&id);
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VCORE;
	key.mv_size = sizeof(VertexDbId);
	key.mv_data = &id;
	rc = mdb_cursor_get(vertexCursor, &key, &data, MDB_SET);
	if (rc != 0) {
		goto fail;
	}
	rc = mdb_cursor_del(vertexCursor, 0);
	if (rc != 0) {
		goto fail;
	}

	initVertexDbId(&id);
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VCORE;
	key.mv_size = sizeof(VertexDbId);
	key.mv_data = &id;

	//First delete all in edges
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) vertexCursor, &key, &data, MDB_SET_RANGE)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (vertexId == vertexDbId.vertexId) {
			if (vertexDbId.coreOrPropertyEnum == INLABEL || vertexDbId.coreOrPropertyEnum == OUTLABEL) {

				rc = internalRemoveEdge(edgeCursor, vertexDbId.edgeId);
				if (rc != 0) {
					rc = GLMDB_DB_CORRUPT;
					goto fail;
				}
				//get the inverse side
				inverseId.vertexId = *(long long *) data.mv_data;
				inverseId.coreOrPropertyEnum = (vertexDbId.coreOrPropertyEnum == OUTLABEL ? INLABEL : OUTLABEL);
				inverseId.labelId = vertexDbId.labelId;
				inverseId.edgeId = vertexDbId.edgeId;
				inverseKey.mv_size = sizeof(VertexDbId);
				inverseKey.mv_data = &inverseId;

				//delete inverse
				rc = mdb_cursor_get(inverseCursor, &inverseKey, &inverseData, MDB_SET);
				if (rc != 0) {
					rc = GLMDB_DB_CORRUPT;
					goto fail;
				}
				rc = mdb_cursor_del(inverseCursor, 0);
				if (rc != 0) {
					rc = GLMDB_DB_CORRUPT;
					goto fail;
				}

				//delete current
				rc = mdb_cursor_del(vertexCursor, 0);
				if (rc != 0) {
					rc = GLMDB_DB_CORRUPT;
					goto fail;
				}

				if (rc != 0) {
					rc = GLMDB_DB_CORRUPT;
					goto fail;
				}
				if (rc != 0) {
					goto fail;
				}

			} else if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY) {

				rc = mdb_cursor_del(vertexCursor, 0);
				if (rc != 0) {
					rc = GLMDB_DB_CORRUPT;
					goto fail;
				}
				if (rc != 0) {
					goto fail;
				}
			} else if (vertexDbId.coreOrPropertyEnum == VCORE) {
				rc = GLMDB_DB_CORRUPT;
				goto fail;
			} else {
				rc = GLMDB_DB_CORRUPT;
				goto fail;
			}

			initVertexDbId(&id);
			id.vertexId = vertexId;
			id.coreOrPropertyEnum = VCORE;
			key.mv_size = sizeof(VertexDbId);
			key.mv_data = &id;
		} else {
			break;
		}

	}

	fail: if (rc == MDB_NOTFOUND) {
		//This means MDB_NEXT returned nada, i.e. there were no more edges to delete
		rc = 0;
	}
	mdb_cursor_close(vertexCursor);
	mdb_cursor_close(inverseCursor);
	mdb_cursor_close(edgeCursor);
	return rc;
}

int internalDeleteVertex(MDB_cursor *vertexCursor, MDB_cursor *inverseCursor, MDB_cursor *edgeCursor, VertexDbId vertexDbId,
		VertexDbId inverseId, MDB_val inverseKey, MDB_val data, MDB_val inverseData) {

//	MDB_val key, data;
//	MDB_val inverseKey, inverseData;
//	VertexDbId inverseId;
//	initVertexDbId(&inverseId);
//	MDB_cursor *vertexCursor;
//	MDB_cursor *inverseCursor;
//	MDB_cursor *edgeCursor;

	int rc;
	rc = internalRemoveEdge(edgeCursor, vertexDbId.edgeId);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}
	//get the inverse side
	inverseId.vertexId = *(long long *) data.mv_data;
	inverseId.coreOrPropertyEnum = (vertexDbId.coreOrPropertyEnum == OUTLABEL ? INLABEL : OUTLABEL);
	inverseId.labelId = vertexDbId.labelId;
	inverseId.edgeId = vertexDbId.edgeId;
	inverseKey.mv_size = sizeof(VertexDbId);
	inverseKey.mv_data = &inverseId;

	//delete inverse
	rc = mdb_cursor_get(inverseCursor, &inverseKey, &inverseData, MDB_SET);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}
	rc = mdb_cursor_del(inverseCursor, 0);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}

	//delete current
	rc = mdb_cursor_del(vertexCursor, 0);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}
	fail: return rc;

}

int getVertex(MDB_cursor *cursor, jlong vertexId, MDB_val *vertexKey) {
	MDB_val data;
	VertexDbId id;
	initVertexDbId(&id);
	id.vertexId = (long) vertexId;
	id.coreOrPropertyEnum = VCORE;
	(*vertexKey).mv_size = sizeof(VertexDbId);
	(*vertexKey).mv_data = &id;
	return mdb_cursor_get((MDB_cursor *) (long) cursor, vertexKey, &data, MDB_SET_KEY);
}

int getFirstEdgefromVertex(MDB_cursor *cursor, jint direction, jint labelId, jlong fromVertexId, jlong *edgeIdResultC, jlong *outVertexIdC,
		jlong *inVertexIdC) {

	int rc;
	MDB_val key, data;
	VertexDbId id;
	initVertexDbId(&id);
	id.vertexId = fromVertexId;
	switch (direction) {
	case 0:
		id.coreOrPropertyEnum = OUTLABEL;
		break;
	case 1:
		id.coreOrPropertyEnum = INLABEL;
		break;
	case 2:
		//for direction both place the cursor at the first out label
		id.coreOrPropertyEnum = OUTLABEL;
		break;
	default:
		rc = GLMDB_UNDEFINED_DIRECTION;
		goto fail;
	}
	id.labelId = labelId;
	key.mv_size = sizeof(VertexDbId);
	key.mv_data = &id;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {
		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (fromVertexId == vertexDbId.vertexId && labelId == vertexDbId.labelId) {

			switch (direction) {
			case 0:
				if (vertexDbId.coreOrPropertyEnum != OUTLABEL) {
					rc = GLMDB_END_OF_EDGES;
					goto fail;
				}
				*outVertexIdC = vertexDbId.vertexId;
				*inVertexIdC = *((jlong *) (data.mv_data));
				break;
			case 1:
				if (vertexDbId.coreOrPropertyEnum != INLABEL) {
					rc = GLMDB_END_OF_EDGES;
					goto fail;
				}
				*outVertexIdC = *((jlong *) (data.mv_data));
				*inVertexIdC = vertexDbId.vertexId;
				break;
			case 2:
				if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
					*outVertexIdC = vertexDbId.vertexId;
					*inVertexIdC = *((jlong *) (data.mv_data));
				} else if (vertexDbId.coreOrPropertyEnum == INLABEL) {
					*outVertexIdC = *((jlong *) (data.mv_data));
					*inVertexIdC = vertexDbId.vertexId;
				} else {
					rc = GLMDB_END_OF_EDGES;
					goto fail;
				}
				break;
			default:
				rc = GLMDB_UNDEFINED_DIRECTION;
				goto fail;
			}

			*edgeIdResultC = vertexDbId.edgeId;
		} else {
			rc = GLMDB_END_OF_EDGES;
		}
	}
	fail: return rc;
}

int getNextEdgefromVertex(MDB_cursor *cursor, jint direction, jint labelId, jlong fromVertexId, jlong *edgeIdResultC, jlong *outVertexIdC,
		jlong *inVertexIdC) {

	int rc = 0;
	VertexDbId id;
	initVertexDbId(&id);
	MDB_val key, data;
	key.mv_size = sizeof(VertexDbId);
	key.mv_data = &id;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT);
	if (rc != 0) {
		goto fail;
	}
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_GET_CURRENT);
	if (rc != 0) {
		goto fail;
	}
	VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
	if (fromVertexId == vertexDbId.vertexId && labelId == vertexDbId.labelId) {
		switch (direction) {
		case 0:
			if (vertexDbId.coreOrPropertyEnum != OUTLABEL) {
				rc = GLMDB_END_OF_EDGES;
				goto fail;
			}
			*outVertexIdC = vertexDbId.vertexId;
			*inVertexIdC = *((jlong *) (data.mv_data));
			break;
		case 1:
			if (vertexDbId.coreOrPropertyEnum != INLABEL) {
				rc = GLMDB_END_OF_EDGES;
				goto fail;
			}
			*outVertexIdC = *((jlong *) (data.mv_data));
			*inVertexIdC = vertexDbId.vertexId;
			break;
		case 2:
			if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
				*outVertexIdC = vertexDbId.vertexId;
				*inVertexIdC = *((jlong *) (data.mv_data));
			} else if (vertexDbId.coreOrPropertyEnum == INLABEL) {
				*outVertexIdC = *((jlong *) (data.mv_data));
				*inVertexIdC = vertexDbId.vertexId;
			} else {
				rc = GLMDB_END_OF_EDGES;
				goto fail;
			}
			break;
		default:
			rc = GLMDB_UNDEFINED_DIRECTION;
			goto fail;
		}
		*edgeIdResultC = vertexDbId.edgeId;
	} else {
		rc = GLMDB_END_OF_EDGES;
	}
	fail: return rc;
}

int getFirstEdgefromVertexAllLabels(MDB_cursor *cursor, jint direction, jlong fromVertexId, jint *labelIdResultC, jlong *edgeIdResultC,
		jlong *outVertexIdC, jlong *inVertexIdC) {

	int rc;
	MDB_val key, data;
	VertexDbId id;
	initVertexDbId(&id);
	id.vertexId = fromVertexId;
	id.coreOrPropertyEnum = VCORE;
	key.mv_size = sizeof(VertexDbId);
	key.mv_data = &id;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_SET_RANGE);
	VertexDbId sanityCheckVertexDbId = *((VertexDbId *) (key.mv_data));
	if (sanityCheckVertexDbId.coreOrPropertyEnum != VCORE) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}

	if (rc == 0) {

		while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

			VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
			if (fromVertexId == vertexDbId.vertexId) {
				if (direction == 0) {
					if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
						*outVertexIdC = vertexDbId.vertexId;
						*inVertexIdC = *((jlong *) (data.mv_data));
						*labelIdResultC = vertexDbId.labelId;
						*edgeIdResultC = vertexDbId.edgeId;
						break;
					}
				} else if (direction == 1) {
					if (vertexDbId.coreOrPropertyEnum == INLABEL) {
						*outVertexIdC = *((jlong *) (data.mv_data));
						*inVertexIdC = vertexDbId.vertexId;
						*labelIdResultC = vertexDbId.labelId;
						*edgeIdResultC = vertexDbId.edgeId;
						break;
					}
				} else {
					if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
						*outVertexIdC = vertexDbId.vertexId;
						*inVertexIdC = *((jlong *) (data.mv_data));
						*labelIdResultC = vertexDbId.labelId;
						*edgeIdResultC = vertexDbId.edgeId;
						break;
					} else if (vertexDbId.coreOrPropertyEnum == INLABEL) {
						*outVertexIdC = *((jlong *) (data.mv_data));
						*inVertexIdC = vertexDbId.vertexId;
						*labelIdResultC = vertexDbId.labelId;
						*edgeIdResultC = vertexDbId.edgeId;
						break;
					}
				}
			} else {
				rc = GLMDB_END_OF_EDGES;
			}
		}
	}
	fail: return rc;
}

int getNextEdgefromVertexAllLabels(MDB_cursor *cursor, jint direction, jlong fromVertexId, jint *labelIdResultC, jlong *edgeIdResultC,
		jlong *outVertexIdC, jlong *inVertexIdC) {

	int rc = 0;
	VertexDbId id;
	initVertexDbId(&id);
	MDB_val key, data;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (fromVertexId == vertexDbId.vertexId) {

			if (direction == 0) {
				if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
					*outVertexIdC = vertexDbId.vertexId;
					*inVertexIdC = *((jlong *) (data.mv_data));
					*labelIdResultC = vertexDbId.labelId;
					*edgeIdResultC = vertexDbId.edgeId;
					break;
				}
			} else if (direction == 1) {
				if (vertexDbId.coreOrPropertyEnum == INLABEL) {
					*outVertexIdC = *((jlong *) (data.mv_data));
					*inVertexIdC = vertexDbId.vertexId;
					*labelIdResultC = vertexDbId.labelId;
					*edgeIdResultC = vertexDbId.edgeId;
					break;
				}
			} else {
				if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
					*outVertexIdC = vertexDbId.vertexId;
					*inVertexIdC = *((jlong *) (data.mv_data));
				} else if (vertexDbId.coreOrPropertyEnum == INLABEL) {
					*outVertexIdC = *((jlong *) (data.mv_data));
					*inVertexIdC = vertexDbId.vertexId;
				} else {
					rc = GLMDB_END_OF_EDGES;
					goto fail;
				}
				*labelIdResultC = vertexDbId.labelId;
				*edgeIdResultC = vertexDbId.edgeId;
				break;
			}
		} else {
			rc = GLMDB_END_OF_EDGES;
		}
	}
	fail: return rc;
}

int setVertexPropertyString(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jint propertyValueLength, char *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		VertexDbId id;
		id.vertexId = vertexId;
		id.coreOrPropertyEnum = VPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		id.labelId = -1;
		id.edgeId = -1LL;
		key.mv_size = sizeof(VertexDbId);
		key.mv_data = &id;
		data.mv_size = propertyValueLength;
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int setEdgePropertyString(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jint propertyValueLength, char *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = ECORE;
		id.propertykeyId = propertyKeyId;
		key.mv_size = sizeof(EdgeDbId);
		key.mv_data = &id;
		data.mv_size = propertyValueLength;
		data.mv_data = propertyValue;

		int rc = mdb_cursor_get(cursor, &key, &data, MDB_SET);
		if (rc == 0) {
			id.coreOrPropertyEnum = EPROPERTY_KEY;
			key.mv_size = sizeof(EdgeDbId);
			key.mv_data = &id;
			data.mv_size = propertyValueLength;
			data.mv_data = propertyValue;
			return mdb_cursor_put(cursor, &key, &data, 0);
		} else {
			return GLMDB_DB_INVALID_EDGE;
		}
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int setVertexPropertyBoolean(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jboolean *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		VertexDbId id;
		id.vertexId = vertexId;
		id.coreOrPropertyEnum = VPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		id.labelId = -1;
		id.edgeId = -1LL;
		key.mv_size = sizeof(VertexDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jboolean);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int setEdgePropertyBoolean(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jboolean *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = EPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		key.mv_size = sizeof(EdgeDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jboolean);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int setVertexPropertyByte(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jbyte *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		VertexDbId id;
		id.vertexId = vertexId;
		id.coreOrPropertyEnum = VPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		id.labelId = -1;
		id.edgeId = -1LL;
		key.mv_size = sizeof(VertexDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jbyte);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int setEdgePropertyByte(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jbyte *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = EPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		key.mv_size = sizeof(EdgeDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jbyte);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int setVertexPropertyShort(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jshort *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		VertexDbId id;
		id.vertexId = vertexId;
		id.coreOrPropertyEnum = VPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		id.labelId = -1;
		id.edgeId = -1LL;
		key.mv_size = sizeof(VertexDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jshort);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int setEdgePropertyShort(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jshort *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = EPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		key.mv_size = sizeof(EdgeDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jshort);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int setVertexPropertyInt(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jint *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		VertexDbId id;
		id.vertexId = vertexId;
		id.coreOrPropertyEnum = VPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		id.labelId = -1;
		id.edgeId = -1LL;
		key.mv_size = sizeof(VertexDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jint);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int setEdgePropertyInt(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jint *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = EPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		key.mv_size = sizeof(EdgeDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jint);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int setVertexPropertyLong(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jlong *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		VertexDbId id;
		id.vertexId = vertexId;
		id.coreOrPropertyEnum = VPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		id.labelId = -1;
		id.edgeId = -1LL;
		key.mv_size = sizeof(VertexDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jlong);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int setEdgePropertyLong(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jlong *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = EPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		key.mv_size = sizeof(EdgeDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jlong);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int setVertexPropertyFloat(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jfloat *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		VertexDbId id;
		id.vertexId = vertexId;
		id.coreOrPropertyEnum = VPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		id.labelId = -1;
		id.edgeId = -1LL;
		key.mv_size = sizeof(VertexDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jfloat);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int setEdgePropertyFloat(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jfloat *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = EPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		key.mv_size = sizeof(EdgeDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jfloat);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int setVertexPropertyDouble(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jdouble *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		VertexDbId id;
		id.vertexId = vertexId;
		id.coreOrPropertyEnum = VPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		id.labelId = -1;
		id.edgeId = -1LL;
		key.mv_size = sizeof(VertexDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jdouble);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int setEdgePropertyDouble(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jdouble *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = EPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		key.mv_size = (sizeof(EdgeDbId));
		key.mv_data = &id;
		data.mv_size = sizeof(jdouble);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int setVertexPropertyChar(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jchar *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		VertexDbId id;
		id.vertexId = vertexId;
		id.coreOrPropertyEnum = VPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		id.labelId = -1;
		id.edgeId = -1LL;
		key.mv_size = sizeof(VertexDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jchar);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int setEdgePropertyChar(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jchar *propertyValue) {
	if (propertyValue != NULL) {
		MDB_val key, data;
		EdgeDbId id;
		id.edgeId = edgeId;
		id.coreOrPropertyEnum = EPROPERTY_KEY;
		id.propertykeyId = propertyKeyId;
		key.mv_size = sizeof(EdgeDbId);
		key.mv_data = &id;
		data.mv_size = sizeof(jchar);
		data.mv_data = propertyValue;
		return mdb_cursor_put(cursor, &key, &data, 0);
	} else {
		return GLMDB_WRITE_NULL;
	}
}

int getVertexProperty(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, MDB_val *data) {
	MDB_val key;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VPROPERTY_KEY;
	id.propertykeyId = propertyKeyId;
	id.labelId = -1;
	id.edgeId = -1LL;
	key.mv_size = sizeof(VertexDbId);
	key.mv_data = &id;
	return mdb_cursor_get(cursor, &key, data, MDB_SET_KEY);
}

int getVertexPropertyKeys(MDB_cursor *cursor, jlong vertexId, jint *propertyKeyArraySizeC, jint **propertyKeyArrayC) {

	jint rc = 0;
	int *propertyKeyId = malloc(sizeof(int));

	MDB_val key, data;
	VertexDbId vertexDbId;
	initVertexDbId(&vertexDbId);
	vertexDbId.vertexId = vertexId;
	vertexDbId.coreOrPropertyEnum = VPROPERTY_KEY;
	key.mv_size = sizeof(VertexDbId);
	key.mv_data = &vertexDbId;

	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE);
	if (rc != 0) {
		goto fail;
	}
	vertexDbId = *((VertexDbId *) (key.mv_data));
	if (vertexDbId.vertexId != vertexId || vertexDbId.coreOrPropertyEnum != VPROPERTY_KEY) {
		rc = MDB_NOTFOUND;
		goto fail;
	}
	*propertyKeyArraySizeC = 1;
	propertyKeyId[0] = vertexDbId.propertykeyId;

	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (vertexDbId.vertexId != vertexId || vertexDbId.coreOrPropertyEnum != VPROPERTY_KEY) {
			break;
		}
		*propertyKeyArraySizeC = *propertyKeyArraySizeC + 1;
		propertyKeyId = (jint *) realloc((jint *) propertyKeyId, *propertyKeyArraySizeC * sizeof(jint));
		propertyKeyId[*propertyKeyArraySizeC - 1] = vertexDbId.propertykeyId;
	}

	propertyKeyArrayC[0] = propertyKeyId;

	if (rc == MDB_NOTFOUND) {
		rc = 0;
	}
	fail: return rc;

}

int getEdgePropertyKeys(MDB_cursor *cursor, jlong edgeId, jint *propertyKeyArraySizeC, jint **propertyKeyArrayC) {

	jint rc = 0;
	int *propertyKeyId = malloc(sizeof(int));

	MDB_val key, data;
	EdgeDbId edgeDbId;
	initEdgeDbId(&edgeDbId);
	edgeDbId.edgeId = edgeId;
	edgeDbId.coreOrPropertyEnum = EPROPERTY_KEY;
	key.mv_size = sizeof(EdgeDbId);
	key.mv_data = &edgeDbId;

	rc = mdb_cursor_get(cursor, &key, &data, MDB_SET_RANGE);
	if (rc != 0) {
		goto fail;
	}
	edgeDbId = *((EdgeDbId *) (key.mv_data));
	if (edgeDbId.edgeId != edgeId || edgeDbId.coreOrPropertyEnum != EPROPERTY_KEY) {
		rc = MDB_NOTFOUND;
		goto fail;
	}
	*propertyKeyArraySizeC = 1;
	propertyKeyId[0] = edgeDbId.propertykeyId;

	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		if (edgeDbId.edgeId != edgeId || edgeDbId.coreOrPropertyEnum != EPROPERTY_KEY) {
			break;
		}
		*propertyKeyArraySizeC = *propertyKeyArraySizeC + 1;
		propertyKeyId = (jint *) realloc((jint *) propertyKeyId, *propertyKeyArraySizeC * sizeof(jint));
		propertyKeyId[*propertyKeyArraySizeC - 1] = edgeDbId.propertykeyId;
	}

	propertyKeyArrayC[0] = propertyKeyId;

	if (rc == MDB_NOTFOUND) {
		rc = 0;
	}
	fail: return rc;

}

int removeVertexProperty(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId) {
	MDB_val data;
	int rc = getVertexProperty(cursor, vertexId, propertyKeyId, &data);
	if (rc == 0) {
		rc = mdb_cursor_del(cursor, 0);
	}
	return rc;
}

int getEdgeProperty(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, MDB_val *data) {
	MDB_val key;
	EdgeDbId id;
	id.edgeId = edgeId;
	id.coreOrPropertyEnum = EPROPERTY_KEY;
	id.propertykeyId = propertyKeyId;
	key.mv_size = sizeof(EdgeDbId);
	key.mv_data = &id;
	return mdb_cursor_get(cursor, &key, data, MDB_SET_KEY);
}

int removeEdgeProperty(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId) {
	MDB_val data;
	int rc = getEdgeProperty(cursor, edgeId, propertyKeyId, &data);
	if (rc == 0) {
		rc = mdb_cursor_del(cursor, 0);
	}
	return rc;
}

//MDB_val *edgeKey is out only
int addEdge(MDB_txn *txn, MDB_dbi vertexDb, MDB_dbi edgeDb, jlong edgeId, jint labelId, jlong vertexOutId, jlong vertexInId) {

	int rc = addEdgeToEdgeDb(txn, edgeDb, edgeId, labelId, vertexOutId, vertexInId);
	if (rc == 0) {
		rc = addEdgeToVertexDb(txn, vertexDb, edgeId, labelId, vertexOutId, vertexInId);
	}
	return rc;
}

int addEdgeToEdgeDb(MDB_txn *txn, MDB_dbi edgeDb, jlong edgeId, jint labelId, jlong vertexOutId, jlong vertexInId) {
	MDB_val edgeKey, data;
	EdgeDbId id;
	id.edgeId = edgeId;
	id.coreOrPropertyEnum = ECORE;
	id.propertykeyId = -1;
	edgeKey.mv_size = (sizeof(EdgeDbId));
	edgeKey.mv_data = &id;

	EdgeData edgeData;
	edgeData.vertexInId = vertexInId;
	edgeData.vertexOutId = vertexOutId;
	edgeData.labelId = labelId;

	data.mv_size = sizeof(EdgeData);
	data.mv_data = &edgeData;

	return mdb_put(txn, edgeDb, &edgeKey, &data, MDB_NOOVERWRITE);
}

int addEdgeToVertexDb(MDB_txn *txn, MDB_dbi vertexDb, jlong edgeId, jint labelId, jlong vertexOutId, jlong vertexInId) {
	MDB_val edgeVertexDbKeyOut, dataOut;
	VertexDbId idOut;
	idOut.vertexId = vertexOutId;
	idOut.coreOrPropertyEnum = OUTLABEL;
	idOut.propertykeyId = -1;
	idOut.edgeId = edgeId;
	idOut.labelId = labelId;

	edgeVertexDbKeyOut.mv_size = sizeof(VertexDbId);
	edgeVertexDbKeyOut.mv_data = &idOut;
	dataOut.mv_size = sizeof(jlong);
	dataOut.mv_data = &vertexInId;
	int rc = mdb_put(txn, vertexDb, &edgeVertexDbKeyOut, &dataOut, MDB_NOOVERWRITE);
	if (rc == 0) {
		MDB_val edgeVertexDbKeyIn, dataIn;
		VertexDbId idIn;
		idIn.vertexId = vertexInId;
		idIn.coreOrPropertyEnum = INLABEL;
		idIn.propertykeyId = -1;
		idIn.edgeId = edgeId;
		idIn.labelId = labelId;

		edgeVertexDbKeyIn.mv_size = sizeof(VertexDbId);
		edgeVertexDbKeyIn.mv_data = &idIn;
		dataIn.mv_size = sizeof(jlong);
		dataIn.mv_data = &vertexOutId;
		rc = mdb_put(txn, vertexDb, &edgeVertexDbKeyIn, &dataIn, MDB_NOOVERWRITE);
	}
	return rc;
}

/**
 * This only removes the edge from the edge db, not the related edges in the vertexDb
 */
int internalRemoveEdge(MDB_cursor *cursor, jlong edgeId) {
	MDB_val edgeKey, edgeData;
	int rc = getEdge(cursor, edgeId, &edgeKey, &edgeData);
	if (rc == 0) {
		rc = mdb_cursor_del(cursor, 0);
	}

	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &edgeKey, &edgeData, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (edgeKey.mv_data));
		if (edgeDbId.edgeId == edgeId) {
			rc = mdb_cursor_del((MDB_cursor *) (long) cursor, 0);
			if (rc == MDB_NOTFOUND) {
				//This happens at the end of the keys when it iterates forever on the last record.
				//When we delete what is already deleted it returns MDB_NOTFOUND
				break;
			}
			if (rc != 0) {
				rc = GLMDB_DB_CORRUPT;
				goto fail;
			}
		} else {
			break;
		}
	}
	if (rc == MDB_NOTFOUND) {
		rc = 0;
	}
	fail: return rc;
}

int removeEdge(MDB_txn *txn, GLMDB_env *genv, jlong edgeId) {

	int rc = 0;
	MDB_val edgeKey, vertexKey, data, vertexData;
	MDB_cursor *edgeCursor;
	MDB_cursor *vertexCursor;

	rc = mdb_cursor_open(txn, genv->vertexDb, &vertexCursor);
	if (rc != 0) {
		goto fail;
	}
	rc = mdb_cursor_open(txn, genv->edgeDb, &edgeCursor);
	if (rc != 0) {
		goto fail;
	}

	rc = getEdge(edgeCursor, edgeId, &edgeKey, &data);
	if (rc != 0) {
		goto fail;
	}

	EdgeData edgeData = *((EdgeData *) (data.mv_data));

	VertexDbId vertexDbId;

//Delete the out edge
	vertexDbId.vertexId = edgeData.vertexOutId;
	vertexDbId.coreOrPropertyEnum = OUTLABEL;
	vertexDbId.labelId = edgeData.labelId;
	vertexDbId.edgeId = edgeId;
	vertexKey.mv_size = sizeof(VertexDbId);
	vertexKey.mv_data = &vertexDbId;

	rc = mdb_cursor_get(vertexCursor, &vertexKey, &vertexData, MDB_SET);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}
	rc = mdb_cursor_del((MDB_cursor *) (long) vertexCursor, 0);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}

//Delete the in edge
	vertexDbId.vertexId = edgeData.vertexInId;
	vertexDbId.coreOrPropertyEnum = INLABEL;
	vertexDbId.labelId = edgeData.labelId;
	vertexDbId.edgeId = edgeId;
	vertexKey.mv_size = sizeof(VertexDbId);
	vertexKey.mv_data = &vertexDbId;

	rc = mdb_cursor_get(vertexCursor, &vertexKey, &vertexData, MDB_SET);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}
	rc = mdb_cursor_del((MDB_cursor *) (long) vertexCursor, 0);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}

//delete the edge
	rc = mdb_cursor_del((MDB_cursor *) (long) edgeCursor, 0);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}

	while ((rc = mdb_cursor_get((MDB_cursor *) (long) edgeCursor, &edgeKey, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (edgeKey.mv_data));
		if (edgeDbId.edgeId == edgeId) {
			rc = mdb_cursor_del((MDB_cursor *) (long) edgeCursor, 0);
			if (rc == MDB_NOTFOUND) {
				//This happens at the end of the keys when it iterates forever on the last record.
				//When we delete what is already deleted it returns MDB_NOTFOUND
				break;
			}
			if (rc != 0) {
				rc = GLMDB_DB_CORRUPT;
				goto fail;
			}
		} else {
			break;
		}
	}
	if (rc == MDB_NOTFOUND) {
		rc = 0;
	}
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}

	fail: mdb_cursor_close(vertexCursor);
	mdb_cursor_close(edgeCursor);

	return rc;
}

int getEdge(MDB_cursor *cursor, jlong edgeId, MDB_val *edgeKey, MDB_val *edgeData) {
	EdgeDbId id;
	id.edgeId = (long) edgeId;
	id.coreOrPropertyEnum = ECORE;
	id.propertykeyId = -1;
	(*edgeKey).mv_size = sizeof(EdgeDbId);
	(*edgeKey).mv_data = &id;
	return mdb_cursor_get((MDB_cursor *) (long) cursor, edgeKey, edgeData, MDB_SET_KEY);
}

int comparePropertyKeyDbId(const MDB_val *key1, const MDB_val *key2) {
	int propertyKey1Size = (size_t) key1->mv_size;
	char * propertyKeyId1 = (char *) (key1->mv_data);
	char * propertyKeyId2 = (char *) (key2->mv_data);
	int compare = strncmp(propertyKeyId1, propertyKeyId2, propertyKey1Size);
	return compare;
}

int compareVertexDbId(const MDB_val *key1, const MDB_val *key2) {

	VertexDbId vertexDbId1 = (*(VertexDbId *) (key1->mv_data));
	VertexDbId vertexDbId2 = (*(VertexDbId *) (key2->mv_data));

	jlong vertex1Id = vertexDbId1.vertexId;
	jlong vertex2Id = vertexDbId2.vertexId;
	if (vertex1Id == vertex2Id) {

		//Compare on label next
		jint labelId1 = vertexDbId1.labelId;
		jint labelId2 = vertexDbId2.labelId;
		if (labelId1 == labelId2) {

			//Compare coreOrPropertyEnum
			enum VertexCoreOrPropertyEnum coreOrProperty1 = vertexDbId1.coreOrPropertyEnum;
			enum VertexCoreOrPropertyEnum coreOrProperty2 = vertexDbId2.coreOrPropertyEnum;
			if (coreOrProperty1 == coreOrProperty2) {

				switch (coreOrProperty1) {
				case VCORE:
					return 0;
					break;
				case VPROPERTY_KEY:
					;
					jint propertyKey1 = vertexDbId1.propertykeyId;
					jint propertyKey2 = vertexDbId2.propertykeyId;
					return (propertyKey1 > propertyKey2) - (propertyKey1 < propertyKey2);
					break;
				case OUTLABEL:
					;
					jlong edgeId1 = vertexDbId1.edgeId;
					jlong edgeId2 = vertexDbId2.edgeId;
					return (edgeId1 > edgeId2) - (edgeId1 < edgeId2);
					break;
				case INLABEL:
					;
					jlong edgeId11 = vertexDbId1.edgeId;
					jlong edgeId22 = vertexDbId2.edgeId;
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

int compareEdgeDbId(const MDB_val *key1, const MDB_val *key2) {
	jlong edge1Id = (*(EdgeDbId *) (key1->mv_data)).edgeId;
	jlong edge2Id = (*(EdgeDbId *) (key2->mv_data)).edgeId;
	if (edge1Id == edge2Id) {
		//Need to compare further on core or property. core comes first
		enum EdgeCoreOrPropertyEnum coreOrProperty1 = (*(EdgeDbId *) (key1->mv_data)).coreOrPropertyEnum;
		enum EdgeCoreOrPropertyEnum coreOrProperty2 = (*(EdgeDbId *) (key2->mv_data)).coreOrPropertyEnum;
		if (coreOrProperty1 == coreOrProperty2) {
			switch (coreOrProperty1) {
			case ECORE:
				return 0;
				break;
			case EPROPERTY_KEY:
				;
				jint propertyKey1 = (*(EdgeDbId *) (key1->mv_data)).propertykeyId;
				jint propertyKey2 = (*(EdgeDbId *) (key2->mv_data)).propertykeyId;
				return (propertyKey1 > propertyKey2) - (propertyKey1 < propertyKey2);
				break;
			}
		} else {
			return (coreOrProperty1 > coreOrProperty2) - (coreOrProperty1 < coreOrProperty2);
		}
	} else {
		return (edge1Id > edge2Id) - (edge1Id < edge2Id);
	}
	return 0;
}

void printDbStats(MDB_env *env, MDB_txn *txn, MDB_dbi vertexDb, char *name) {
	MDB_stat stat;
	mdb_stat(txn, vertexDb, &stat);
	prstat(&stat, name);
}

void printVertexRecord(MDB_val key, MDB_val data) {

	VertexDbId vertexDbId = (*((VertexDbId *) (key.mv_data)));
	switch (vertexDbId.coreOrPropertyEnum) {
	case VCORE:
		printf("key: %lld, labelId = %i, type = VCORE, propertyKey: %i,  edgeId = %lld,  data: %s\n", (long long) vertexDbId.vertexId,
				vertexDbId.labelId, vertexDbId.propertykeyId, (long long) vertexDbId.edgeId,
				*((char *) data.mv_data) == '\0' ? "NULL" : "????");
		break;
	case VPROPERTY_KEY:
		printf("key: %lld, labelId = %i, type = VPROPERTY_KEY, propertyKey: %i, edgeId = %lld,  data: %.*s\n",
				(long long) vertexDbId.vertexId, vertexDbId.labelId, vertexDbId.propertykeyId, (long long) vertexDbId.edgeId,
				(int) data.mv_size, (char *) data.mv_data);
		break;
	case OUTLABEL:
		printf("key: %lld, labelId = %i, type = OUTLABEL, propertyKey: %i, edgeId = %lld,  data: %lld\n", (long long) vertexDbId.vertexId,
				vertexDbId.labelId, vertexDbId.propertykeyId, (long long) vertexDbId.edgeId, *(long long *) data.mv_data);
		break;
	case INLABEL:
		printf("key: %lld, labelId = %i, type = INLABEL, propertyKey: %i, edgeId = %lld,  data: %lld\n", (long long) vertexDbId.vertexId,
				vertexDbId.labelId, vertexDbId.propertykeyId, (long long) vertexDbId.edgeId, *(long long *) data.mv_data);
		break;
	}
}

void printEdgeRecord(MDB_val key, MDB_val data) {

	EdgeDbId edgeDbId = (*((EdgeDbId *) (key.mv_data)));
	EdgeData edgeData = (*((EdgeData *) (data.mv_data)));
	switch (edgeDbId.coreOrPropertyEnum) {
	case ECORE:
		printf("key: %lld, type = ECORE, propertyKey: %i, labelId = %i, vertexOutId = %lld,  vertexInId = %lld\n",
				(long long) edgeDbId.edgeId, edgeDbId.propertykeyId, edgeData.labelId, (long long) edgeData.vertexOutId,
				(long long) edgeData.vertexInId);
		break;
	case EPROPERTY_KEY:
		printf("key: %lld, type = EPROPERTY_KEY, propertyKey: %i, data: %.*s\n", (long long) edgeDbId.edgeId, edgeDbId.propertykeyId,
				(int) data.mv_size, (char *) data.mv_data);
		break;
	}
}

void printPropertyKeyDbRecord(MDB_val key, MDB_val data) {
	char *propertyKeyId = (char *) (key.mv_data);
	int propertyKeySize = ((size_t) key.mv_size);
	PropertyKeyDataStruct propertyKeyDataStruct = (*((PropertyKeyDataStruct *) (data.mv_data)));
	printf("propertyKey: %.*s propertyKeyIdType %s, propertyKeyId: %i , indexed = %s\n", propertyKeySize, propertyKeyId,
			propertyTypeEnumToString(propertyKeyDataStruct.type), propertyKeyDataStruct.propertyKeyId,
			(propertyKeyDataStruct.indexed == 1 ? "true" : "false"));
}

void printLabelDbRecord(MDB_val key, MDB_val data) {
	char *label = (char *) (key.mv_data);
	int labelSize = ((size_t) key.mv_size);
	int labelId = *((int *) (data.mv_data));
	printf("label: %.*s, labelId: %i\n", labelSize, label, labelId);
}

int printConfigDbRecord(MDB_val key, MDB_val data) {
	int rc = 0;
	int sequenceEnum = *((int *) (key.mv_data));
	switch (sequenceEnum) {
	case VERTEX_ID_SEQUENCE:
		;
		long long *vertexIdHigh = (long long *) (data.mv_data);
		printf("VERTEX_ID_SEQUENCE high: %lld\n", *vertexIdHigh);
		break;
	case EDGE_ID_SEQUENCE:
		;
		long long *edgeIdHigh = (long long *) (data.mv_data);
		printf("EDGE_ID_SEQUENCE high: %lld\n", *edgeIdHigh);
		break;
	case VERTEX_PROPERTY_KEY_ID_SEQUENCE:
		;
		int vertexPropertyKeyIdHigh = *((int *) (data.mv_data));
		printf("VERTEX_PROPERTY_KEY_ID_SEQUENCE high: %i\n", vertexPropertyKeyIdHigh);
		break;
	case EDGE_PROPERTY_KEY_ID_SEQUENCE:
		;
		int edgePropertyKeyIdHigh = *((int *) (data.mv_data));
		printf("EDGE_PROPERTY_KEY_ID_SEQUENCE high: %i\n", edgePropertyKeyIdHigh);
		break;
	case LABEL_ID_SEQUENCE:
		;
		int labelIdHigh = *((int *) (data.mv_data));
		printf("LABEL_ID_SEQUENCE high: %i\n", labelIdHigh);
		break;
	default:
		rc = GLMDB_INVALID_SEQUENCE;
	}
	return rc;
}

char * propertyTypeEnumToString(int propertyTypeEnum) {
	switch ((int) propertyTypeEnum) {
	case BOOLEAN:
		return "BOOLEAN";
	case BYTE:
		return "BYTE";
	case SHORT:
		return "SHORT";
	case INT:
		return "INT";
	case LONG:
		return "LONG";
	case FLOAT:
		return "FLOAT";
	case DOUBLE:
		return "DOUBLE";
	case CHAR:
		return "CHAR";
	case STRING:
		return "STRING";
	case ARRAY_BOOLEAN:
		return "ARRAY_BOOLEAN";
	case ARRAY_BYTE:
		return "ARRAY_BYTE";
	case ARRAY_SHORT:
		return "ARRAY_SHORT";
	case ARRAY_INT:
		return "ARRAY_INT";
	case ARRAY_LONG:
		return "ARRAY_LONG";
	case ARRAY_FLOAT:
		return "ARRAY_FLOAT";
	case ARRAY_DOUBLE:
		return "ARRAY_DOUBLE";
	case ARRAY_CHAR:
		return "ARRAY_CHAR";
	case ARRAY_STRING:
		return "ARRAY_STRING";
	case UNSET:
		return "UNSET";
	default:
		return "ERROR";
	}

}

void printKey(MDB_val key) {

	VertexDbId vertexDbId = (*((VertexDbId *) (key.mv_data)));
	switch (vertexDbId.coreOrPropertyEnum) {
	case VCORE:
		printf("key: %lld, type = VCORE, propertyKey: %i, labelId = %i, edgeId = %lld\n", (long long) vertexDbId.vertexId,
				vertexDbId.propertykeyId, vertexDbId.labelId, (long long) vertexDbId.edgeId);
		break;
	case VPROPERTY_KEY:
		printf("key: %lld, type = VPROPERTY_KEY, propertyKey: %i, labelId = %i, edgeId = %lld\n", (long long) vertexDbId.vertexId,
				vertexDbId.propertykeyId, vertexDbId.labelId, (long long) vertexDbId.edgeId);
		break;
	case OUTLABEL:
		printf("key: %lld, type = OUTLABEL, propertyKey: %i, labelId = %i, edgeId = %lld\n", (long long) vertexDbId.vertexId,
				vertexDbId.propertykeyId, vertexDbId.labelId, (long long) vertexDbId.edgeId);
		break;
	case INLABEL:
		printf("key: %lld, type = INLABEL, propertyKey: %i, labelId = %i, edgeId = %lld\n", (long long) vertexDbId.vertexId,
				vertexDbId.propertykeyId, vertexDbId.labelId, (long long) vertexDbId.edgeId);
		break;
	default:
		printf("bust\n");
		break;
	}
}

int traverseVertexDb(GLMDB_env * glmdb_env, MDB_txn *txn) {
	int rc, i = 0;
	MDB_dbi dbi = glmdb_env->vertexDb;
	MDB_cursor *cursor;
	MDB_val key, data;
	rc = mdb_cursor_open(txn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
//		if (i % 10000 == 0) {
		printVertexRecord(key, data);
		i = i + 1;
//		}
	}
	fail:
	mdb_cursor_close(cursor);
	return rc;
}

int traverseEdgeDb(GLMDB_env * glmdb_env, MDB_txn *txn) {
	int rc, i = 0;
	MDB_dbi dbi = glmdb_env->edgeDb;
	MDB_cursor *cursor;
	MDB_val key, data;
	rc = mdb_cursor_open(txn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
//		if (i % 10000 == 0) {
		printEdgeRecord(key, data);
		i = i + 1;
//		}
	}
	fail:
	mdb_cursor_close(cursor);
	return 0;
}

int traverseVertexPropertyKeyDb(GLMDB_env * glmdb_env, MDB_txn *txn) {

	int rc = 0;
	MDB_dbi dbi = glmdb_env->vertexPropertyKeyDb;
	MDB_cursor *cursor;
	MDB_val key, data;
	rc = mdb_cursor_open(txn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		printPropertyKeyDbRecord(key, data);
	}
	fail: mdb_cursor_close(cursor);
	return rc;
}

int traverseEdgePropertyKeyDb(GLMDB_env * glmdb_env, MDB_txn *txn) {
	int rc;
	MDB_dbi dbi = glmdb_env->edgePropertyKeyDb;
	MDB_cursor *cursor;
	MDB_val key, data;
	rc = mdb_cursor_open(txn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		printPropertyKeyDbRecord(key, data);
	}
	fail: mdb_cursor_close(cursor);
	return 0;
}

int traverseLabelDb(GLMDB_env * glmdb_env, MDB_txn *txn) {
	int rc = 0;
	MDB_dbi dbi = glmdb_env->labelDb;
	MDB_cursor *cursor;
	MDB_val key, data;
	rc = mdb_cursor_open(txn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		printLabelDbRecord(key, data);
	}
	fail: mdb_cursor_close(cursor);
	return rc;
}

int traverseConfigDb(GLMDB_env * glmdb_env, MDB_txn *txn) {
	int rc = 0;
	MDB_dbi dbi = glmdb_env->configDb;
	MDB_cursor *cursor;
	MDB_val key, data;
	rc = mdb_cursor_open(txn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		rc = printConfigDbRecord(key, data);
		if (rc != 0) {
			goto fail;
		}
	}
	fail: mdb_cursor_close(cursor);
	return rc;
}

void initVertexDbId(VertexDbId *vertexDbId) {
	vertexDbId->vertexId = -1LL;
	vertexDbId->coreOrPropertyEnum = VCORE;
	vertexDbId->propertykeyId = -1;
	vertexDbId->labelId = -1;
	vertexDbId->edgeId = -1LL;
}

void initEdgeDbId(EdgeDbId *edgeDbId) {
	edgeDbId->edgeId = -1LL;
	edgeDbId->coreOrPropertyEnum = ECORE;
	edgeDbId->propertykeyId = -1;
}

void initEdgeData(EdgeData *edgeData) {
	edgeData->vertexInId = -1LL;
	edgeData->vertexOutId = -1LL;
	edgeData->labelId = -1;
}
