#include <jni.h>
#include <stdio.h>
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

JNIEXPORT jstring JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1strerror(JNIEnv *env, jclass that, jint error) {

	char *mdbError = mdb_strerror(error);
	jstring message = (*env)->NewStringUTF(env, mdbError);
	return message;

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

JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1commit(JNIEnv *env, jclass that, jlong txn) {

	jint rc = 0;
	rc = (jint) mdb_txn_commit((MDB_txn *) (long) txn);
	return rc;

}

JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1reset(JNIEnv *env, jclass that, jlong txn) {

	mdb_txn_reset((MDB_txn *) (long) txn);

}

JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1abort(JNIEnv *env, jclass that, jlong txn) {

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
	MDB_val edgeKey;
	jlong *edgeIdC = NULL;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;

	if (edgeId) {
		if ((edgeIdC = (*env)->GetLongArrayElements(env, edgeId, NULL)) == NULL) {
			goto fail;
		}
	}

	*edgeIdC = glmdb_env->edgeIdSequence++;

	addEdge((MDB_txn *) (long) txn, glmdb_env->vertexDb, glmdb_env->edgeDb, *edgeIdC, (long) labelId, (long) outVertexId, (long) inVertexId,
			&edgeKey);

	fail: if (edgeId && edgeIdC) {
		(*env)->ReleaseLongArrayElements(env, edgeId, edgeIdC, 0);
	}
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_boolean
 * Signature: (JJIZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1boolean(JNIEnv *env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jboolean value) {

	jint rc = 0;
	rc = setVertexPropertyBoolean((MDB_cursor *) (long) cursor, (long) vertexId, (int) propertyKeyId, &value);
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_byte
 * Signature: (JJIB)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1byte(JNIEnv *env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jbyte value) {

	jint rc = 0;
	rc = setVertexPropertyByte((MDB_cursor *) (long) cursor, (long) vertexId, (int) propertyKeyId, &value);
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_short
 * Signature: (JJIS)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1short(JNIEnv *env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jshort value) {

	jint rc = 0;
	rc = setVertexPropertyShort((MDB_cursor *) (long) cursor, (long) vertexId, (int) propertyKeyId, &value);
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_int
 * Signature: (JJII)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1int(JNIEnv * env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jint value) {

	jint rc = 0;
	rc = setVertexPropertyInt((MDB_cursor *) (long) cursor, (long) vertexId, (int) propertyKeyId, &value);
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_long
 * Signature: (JJIJ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1long(JNIEnv * env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jlong value) {

	jint rc = 0;
	rc = setVertexPropertyLong((MDB_cursor *) (long) cursor, (long) vertexId, (int) propertyKeyId, &value);
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_float
 * Signature: (JJIF)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1float(JNIEnv *env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jfloat value) {

	jint rc = 0;
	rc = setVertexPropertyFloat((MDB_cursor *) (long) cursor, (long) vertexId, (int) propertyKeyId, &value);
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_double
 * Signature: (JJID)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1double(JNIEnv *env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jdouble value) {

	jint rc = 0;
	rc = setVertexPropertyDouble((MDB_cursor *) (long) cursor, (long) vertexId, (int) propertyKeyId, &value);
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_char
 * Signature: (JJIC)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1char(JNIEnv *env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jchar value) {

	jint rc = 0;
	rc = setVertexPropertyChar((MDB_cursor *) (long) cursor, (long) vertexId, (int) propertyKeyId, &value);
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_string
 * Signature: (JJILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1string(JNIEnv *env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jstring value) {

	jint rc = 0;
	jint strlen = (*env)->GetStringUTFLength(env, value);
	char *propertyValue = malloc(strlen);
	if (value) {
		(*env)->GetStringUTFRegion(env, value, 0, strlen, propertyValue);
		if (propertyValue == NULL) {
			goto fail;
		}
	}
	rc = setVertexPropertyString((MDB_cursor *) (long) cursor, (long) vertexId, (int) propertyKeyId, propertyValue);

	fail: if (value && propertyValue) {
		(*env)->ReleaseStringUTFChars(env, value, propertyValue);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_property_array
 * Signature: (JJI[[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1property_1array(JNIEnv *env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jobjectArray value) {

	jint rc = 0;
	MDB_val data;
	rc = getVertexProperty((MDB_cursor *) (long) cursor, (long) vertexId, (int) propertyKeyId, &data);
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
 * Method:    mdb_set_propertykey
 * Signature: (JJLjava/lang/String;I[I)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1propertykey(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn,
		jstring propertyKey, jint propertyKeyEnum, jintArray propertyKeyIdArray) {

	jint rc = 0;
	jint *propertyKeyId = NULL;
	MDB_cursor *cursor;
	GLMDB_env *glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	MDB_dbi propertyKeyDb = glmdb_env->propertyKeyDb;

	jint strlen = (*env)->GetStringUTFLength(env, propertyKey);
	char *propertyKeyC = malloc(strlen);
	if (propertyKey) {
		(*env)->GetStringUTFRegion(env, propertyKey, 0, strlen, propertyKeyC);
		if (propertyKeyC == NULL) {
			goto fail;
		}
	}

	if (propertyKeyIdArray) {
		if ((propertyKeyId = (*env)->GetIntArrayElements(env, propertyKeyIdArray, NULL)) == NULL) {
			goto fail;
		}
	}

	PropertyKeyStruct *propertyKeyIdStruct = (PropertyKeyStruct*) malloc(sizeof(PropertyKeyStruct));
	propertyKeyIdStruct->propertyKeyId = glmdb_env->propertyKeyIdSequence++;
	switch ((int) propertyKeyEnum) {
	case GLMDB_BOOLEAN:
		propertyKeyIdStruct->type = BOOLEAN;
		break;
	case GLMDB_BYTE:
		propertyKeyIdStruct->type = BYTE;
		break;
	case GLMDB_SHORT:
		propertyKeyIdStruct->type = SHORT;
		break;
	case GLMDB_INT:
		propertyKeyIdStruct->type = INT;
		break;
	case GLMDB_LONG:
		propertyKeyIdStruct->type = LONG;
		break;
	case GLMDB_DOUBLE:
		propertyKeyIdStruct->type = DOUBLE;
		break;
	case GLMDB_CHAR:
		propertyKeyIdStruct->type = CHAR;
		break;
	case GLMDB_STRING:
		propertyKeyIdStruct->type = STRING;
		break;
	case GLMDB_ARRAY_BOOLEAN:
		propertyKeyIdStruct->type = ARRAY_BOOLEAN;
		break;
	case GLMDB_ARRAY_BYTE:
		propertyKeyIdStruct->type = ARRAY_BYTE;
		break;
	case GLMDB_ARRAY_SHORT:
		propertyKeyIdStruct->type = ARRAY_SHORT;
		break;
	case GLMDB_ARRAY_INT:
		propertyKeyIdStruct->type = ARRAY_INT;
		break;
	case GLMDB_ARRAY_LONG:
		propertyKeyIdStruct->type = ARRAY_LONG;
		break;
	case GLMDB_ARRAY_DOUBLE:
		propertyKeyIdStruct->type = ARRAY_DOUBLE;
		break;
	case GLMDB_ARRAY_CHAR:
		propertyKeyIdStruct->type = ARRAY_CHAR;
		break;
	case GLMDB_ARRAY_STRING:
		propertyKeyIdStruct->type = ARRAY_STRING;
		break;
	}

	MDB_val key, data;
	key.mv_size = (size_t) strlen;
	key.mv_data = propertyKeyC;
	data.mv_size = sizeof(PropertyKeyStruct);
	data.mv_data = propertyKeyIdStruct;
	rc = mdb_cursor_open((MDB_txn *) (long) txn, propertyKeyDb, &cursor);
	if (rc != 0)
		goto fail;
	rc = mdb_cursor_put(cursor, &key, &data, MDB_NOOVERWRITE);
	if (rc != 0)
		goto fail;

	*propertyKeyId = (*((PropertyKeyStruct *) (data.mv_data))).propertyKeyId;

	fail: mdb_cursor_close(cursor);
	if (propertyKey && propertyKeyC) {
		(*env)->ReleaseStringUTFChars(env, propertyKey, propertyKeyC);
	}
	if (propertyKeyIdArray && propertyKeyId) {
		(*env)->ReleaseIntArrayElements(env, propertyKeyIdArray, propertyKeyId, 0);
	}
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

	jint strlen = (*env)->GetStringUTFLength(env, label);
	char *labelC = malloc(strlen);
	if (label) {
		(*env)->GetStringUTFRegion(env, label, 0, strlen, labelC);
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
	key.mv_size = (size_t) strlen;
	key.mv_data = labelC;
	data.mv_size = sizeof(int);
	data.mv_data = labelId;
	rc = mdb_cursor_open((MDB_txn *) (long) txn, labelDb, &cursor);
	if (rc != 0) {
		goto fail;
	}
	rc = mdb_cursor_put(cursor, &key, &data, MDB_NOOVERWRITE);
	if (rc != 0) {
		goto fail;
	}

	*labelId = *((int *) (data.mv_data));

	fail: mdb_cursor_close(cursor);
	if (label && labelC) {
		(*env)->ReleaseStringUTFChars(env, label, labelC);
	}
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

	MDB_val key, data;
	VertexDbId id;
	id.vertexId = (long) vertexId;
	id.coreOrPropertyEnum = VCORE;
	id.propertykeyId = -1;
	key.mv_size = (sizeof(int) + sizeof(enum VertexCoreOrPropertyEnum) + sizeof(int));
	key.mv_data = &id;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_SET_KEY);

	VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
	*vertexIdResultC = vertexDbId.vertexId;

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
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
	EdgeDbId id;
	id.edgeId = (long) edgeId;
	id.coreOrPropertyEnum = ECORE;
	id.propertykeyId = -1;
	key.mv_size = (sizeof(int) + sizeof(enum EdgeCoreOrPropertyEnum) + sizeof(int));
	key.mv_data = &id;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_SET_KEY);

	if (rc == 0) {
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

void buffer_copy(const void *source, size_t source_pos, void *dest, size_t dest_pos, size_t length) {
	memmove(((char *) dest) + dest_pos, ((const char *) source) + source_pos, length);
}

int openGraph(GLMDB_env **genv, const char *path) {
	int rc;

	GLMDB_env *e;
	e = calloc(sizeof(GLMDB_env), 1);

	MDB_txn *txn;
	MDB_env *env;
	MDB_dbi configDb;
	MDB_dbi vertexDb;
	MDB_dbi edgeDb;
	MDB_dbi propertyKeyDb;
	MDB_dbi labelDb;

	rc = mdb_env_create(&env);
	if (rc != 0) {
		return rc;
	}
	rc = mdb_env_set_mapsize(env, 107374182400); //100G
	if (rc != 0) {
		return rc;
	}
	rc = mdb_env_set_maxdbs(env, 5);
	if (rc != 0) {
		return rc;
	}
	rc = mdb_env_open(env, path, MDB_NOSYNC, 0664);
	if (rc != 0) {
		return rc;
	}

//Create the config db
	rc = mdb_txn_begin(env, NULL, 0, &txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_open(txn, "configDb", MDB_CREATE, &configDb);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_txn_commit(txn);
	if (rc != 0) {
		return rc;
	}

//Create the vertex db
	rc = mdb_txn_begin(env, NULL, 0, &txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_open(txn, "vertexDb", MDB_CREATE|MDB_INTEGERKEY, &vertexDb);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_set_compare(txn, vertexDb, compareVertexDbId);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_txn_commit(txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}

//Create the edge db
	rc = mdb_txn_begin(env, NULL, 0, &txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_open(txn, "edgeDb", MDB_CREATE|MDB_INTEGERKEY, &edgeDb);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_set_compare(txn, edgeDb, compareEdgeDbId);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_txn_commit(txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}

//Create the property key db
	rc = mdb_txn_begin(env, NULL, 0, &txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_open(txn, "propertyKeyDb", MDB_CREATE, &propertyKeyDb);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_txn_commit(txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}

	//Create the label db
	rc = mdb_txn_begin(env, NULL, 0, &txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_open(txn, "labelDb", MDB_CREATE, &labelDb);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}
	rc = mdb_txn_commit(txn);
	if (rc != 0) {
		mdb_txn_abort(txn);
		return rc;
	}

	e->env = env;
	e->configDb = configDb;
	e->vertexDb = vertexDb;
	e->edgeDb = edgeDb;
	e->propertyKeyDb = propertyKeyDb;
	e->labelDb = labelDb;
	*genv = e;
	return rc;
}

void closeGraph(GLMDB_env *genv) {
	MDB_env *env = genv->env;
	MDB_dbi configDb = genv->configDb;
	MDB_dbi vertexDb = genv->vertexDb;
	MDB_dbi edgeDb = genv->edgeDb;
	MDB_dbi propertyKeyDb = genv->propertyKeyDb;
	MDB_dbi labelDb = genv->labelDb;

	printDbStats(env, configDb, "configDb");
	printDbStats(env, vertexDb, "vertexDb");
	printDbStats(env, edgeDb, "edgeDb");
	printDbStats(env, propertyKeyDb, "propertyKeyDb");
	printDbStats(env, labelDb, "labelDb");

	mdb_close(env, configDb);
	mdb_close(env, vertexDb);
	mdb_close(env, edgeDb);
	mdb_close(env, propertyKeyDb);
	mdb_close(env, labelDb);
	mdb_env_close(env);
}

//MDB_val *vertexKey is out only
int addVertex(MDB_cursor *cursor, MDB_dbi vertexDb, long vertexId, MDB_val *vertexKey) {
	MDB_val data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VCORE;
	id.propertykeyId = -1;
	(*vertexKey).mv_size = (sizeof(VertexDbId));
	(*vertexKey).mv_data = &id;
//write a null of sorts
	data.mv_size = strlen("");
	data.mv_data = "";
	return mdb_cursor_put(cursor, vertexKey, &data, MDB_NOOVERWRITE);
}

int setVertexPropertyString(MDB_cursor *cursor, long vertexId, int propertyKeyId, char *propertyValue) {
	MDB_val key, data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VPROPERTY_KEY;
	id.propertykeyId = propertyKeyId;
	key.mv_size = (sizeof(VertexDbId));
	key.mv_data = &id;
	if (propertyValue != NULL) {
		data.mv_size = strlen(propertyValue);
		data.mv_data = propertyValue;
	} else {
		//write a null of sorts
		data.mv_size = strlen("");
		data.mv_data = "";
	}
	return mdb_cursor_put(cursor, &key, &data, 0);
}

int setVertexPropertyBoolean(MDB_cursor *cursor, long vertexId, int propertyKeyId, jboolean *propertyValue) {
	MDB_val key, data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VPROPERTY_KEY;
	id.propertykeyId = propertyKeyId;
	key.mv_size = (sizeof(VertexDbId));
	key.mv_data = &id;
	if (propertyValue != NULL) {
		data.mv_size = sizeof(jboolean);
		data.mv_data = propertyValue;
	} else {
		//write a null of sorts
		data.mv_size = strlen("");
		data.mv_data = "";
	}
	return mdb_cursor_put(cursor, &key, &data, 0);
}

int setVertexPropertyByte(MDB_cursor *cursor, long vertexId, int propertyKeyId, jbyte *propertyValue) {
	MDB_val key, data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VPROPERTY_KEY;
	id.propertykeyId = propertyKeyId;
	key.mv_size = (sizeof(VertexDbId));
	key.mv_data = &id;
	if (propertyValue != NULL) {
		data.mv_size = sizeof(jbyte);
		data.mv_data = propertyValue;
	} else {
		//write a null of sorts
		data.mv_size = strlen("");
		data.mv_data = "";
	}
	return mdb_cursor_put(cursor, &key, &data, 0);
}

int setVertexPropertyShort(MDB_cursor *cursor, long vertexId, int propertyKeyId, jshort *propertyValue) {
	MDB_val key, data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VPROPERTY_KEY;
	id.propertykeyId = propertyKeyId;
	key.mv_size = (sizeof(VertexDbId));
	key.mv_data = &id;
	if (propertyValue != NULL) {
		data.mv_size = sizeof(jshort);
		data.mv_data = propertyValue;
	} else {
		//write a null of sorts
		data.mv_size = strlen("");
		data.mv_data = "";
	}
	return mdb_cursor_put(cursor, &key, &data, 0);
}

int setVertexPropertyInt(MDB_cursor *cursor, long vertexId, int propertyKeyId, jint *propertyValue) {
	MDB_val key, data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VPROPERTY_KEY;
	id.propertykeyId = propertyKeyId;
	key.mv_size = (sizeof(VertexDbId));
	key.mv_data = &id;
	if (propertyValue != NULL) {
		data.mv_size = sizeof(jint);
		data.mv_data = propertyValue;
	} else {
		//write a null of sorts
		data.mv_size = strlen("");
		data.mv_data = "";
	}
	return mdb_cursor_put(cursor, &key, &data, 0);
}

int setVertexPropertyLong(MDB_cursor *cursor, long vertexId, int propertyKeyId, jlong *propertyValue) {
	MDB_val key, data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VPROPERTY_KEY;
	id.propertykeyId = propertyKeyId;
	key.mv_size = (sizeof(VertexDbId));
	key.mv_data = &id;
	if (propertyValue != NULL) {
		data.mv_size = sizeof(jlong);
		data.mv_data = propertyValue;
	} else {
		//write a null of sorts
		data.mv_size = strlen("");
		data.mv_data = "";
	}
	return mdb_cursor_put(cursor, &key, &data, 0);
}

int setVertexPropertyFloat(MDB_cursor *cursor, long vertexId, int propertyKeyId, jfloat *propertyValue) {
	MDB_val key, data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VPROPERTY_KEY;
	id.propertykeyId = propertyKeyId;
	key.mv_size = (sizeof(VertexDbId));
	key.mv_data = &id;
	if (propertyValue != NULL) {
		data.mv_size = sizeof(jfloat);
		data.mv_data = propertyValue;
	} else {
		//write a null of sorts
		data.mv_size = strlen("");
		data.mv_data = "";
	}
	return mdb_cursor_put(cursor, &key, &data, 0);
}

int setVertexPropertyDouble(MDB_cursor *cursor, long vertexId, int propertyKeyId, jdouble *propertyValue) {
	MDB_val key, data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VPROPERTY_KEY;
	id.propertykeyId = propertyKeyId;
	key.mv_size = (sizeof(VertexDbId));
	key.mv_data = &id;
	if (propertyValue != NULL) {
		data.mv_size = sizeof(jdouble);
		data.mv_data = propertyValue;
	} else {
		//write a null of sorts
		data.mv_size = strlen("");
		data.mv_data = "";
	}
	return mdb_cursor_put(cursor, &key, &data, 0);
}

int setVertexPropertyChar(MDB_cursor *cursor, long vertexId, int propertyKeyId, jchar *propertyValue) {
	MDB_val key, data;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VPROPERTY_KEY;
	id.propertykeyId = propertyKeyId;
	key.mv_size = (sizeof(VertexDbId));
	key.mv_data = &id;
	if (propertyValue != NULL) {
		data.mv_size = sizeof(jchar);
		data.mv_data = propertyValue;
	} else {
		//write a null of sorts
		data.mv_size = strlen("");
		data.mv_data = "";
	}
	return mdb_cursor_put(cursor, &key, &data, 0);
}

int getVertexProperty(MDB_cursor *cursor, long vertexId, int propertyKeyId, MDB_val *data) {
	MDB_val key;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VPROPERTY_KEY;
	id.propertykeyId = propertyKeyId;
	key.mv_size = (sizeof(VertexDbId));
	key.mv_data = &id;
	return mdb_cursor_get(cursor, &key, data, MDB_SET_KEY);
}

//MDB_val *edgeKey is out only
int addEdge(MDB_txn *txn, MDB_dbi vertexDb, MDB_dbi edgeDb, int edgeId, int labelId, int vertexOutId, int vertexInId, MDB_val *edgeKey) {
	int rc = addEdgeToEdgeDb(txn, edgeDb, edgeId, labelId, vertexInId, vertexOutId, edgeKey);
	if (rc == 0) {
		MDB_val edgeVertexDbKey;
		rc = addEdgeToVertexDb(txn, vertexDb, edgeId, labelId, vertexInId, vertexOutId, &edgeVertexDbKey);
	}
	return rc;
}

int addEdgeToEdgeDb(MDB_txn *txn, MDB_dbi edgeDb, int edgeId, int labelId, int vertexInId, int vertexOutId, MDB_val *edgeKey) {
	MDB_val data;
	EdgeDbId id;
	id.edgeId = edgeId;
	id.coreOrPropertyEnum = ECORE;
	id.propertykeyId = -1;
	(*edgeKey).mv_size = (sizeof(EdgeDbId));
	(*edgeKey).mv_data = &id;

	EdgeData edgeData;
	edgeData.vertexInId = vertexInId;
	edgeData.vertexOutId = vertexOutId;
	edgeData.labelId = labelId;

	data.mv_size = sizeof(EdgeData);
	data.mv_data = &edgeData;
	return mdb_put(txn, edgeDb, edgeKey, &data, MDB_NOOVERWRITE);
}

int addEdgeToVertexDb(MDB_txn *txn, MDB_dbi vertexDb, int edgeId, int labelId, int vertexInId, int vertexOutId, MDB_val *edgeVertexDbKey) {
	MDB_val data;
	VertexDbId id;
	id.vertexId = vertexInId;
	id.coreOrPropertyEnum = OUTLABEL;
	id.propertykeyId = -1;
	id.edgeId = edgeId;
	id.labelId = labelId;

	(*edgeVertexDbKey).mv_size = sizeof(VertexDbId);
	(*edgeVertexDbKey).mv_data = &id;
	data.mv_size = sizeof(int);
	data.mv_data = &vertexOutId;
	return mdb_put(txn, vertexDb, edgeVertexDbKey, &data, MDB_NOOVERWRITE);
}

int compareVertexDbId(const MDB_val *key1, const MDB_val *key2) {
	int vertex1Id = (*(VertexDbId *) (key1->mv_data)).vertexId;
	int vertex2Id = (*(VertexDbId *) (key2->mv_data)).vertexId;
	if (vertex1Id == vertex2Id) {
		//Need to compare further on core or property. core comes first
		enum VertexCoreOrPropertyEnum coreOrProperty1 = (*(VertexDbId *) (key1->mv_data)).coreOrPropertyEnum;
		enum VertexCoreOrPropertyEnum coreOrProperty2 = (*(VertexDbId *) (key2->mv_data)).coreOrPropertyEnum;
		if (coreOrProperty1 == coreOrProperty2) {
			switch (coreOrProperty1) {
			case VCORE:
				return 0;
				break;
			case VPROPERTY_KEY:
				;
				int propertyKey1 = (*(VertexDbId *) (key1->mv_data)).propertykeyId;
				int propertyKey2 = (*(VertexDbId *) (key2->mv_data)).propertykeyId;
				return (propertyKey1 > propertyKey2) - (propertyKey1 < propertyKey2);
				break;
			case OUTLABEL:
				;
				int labelId1 = (*(VertexDbId *) (key1->mv_data)).labelId;
				int labelId2 = (*(VertexDbId *) (key2->mv_data)).labelId;
				return (labelId1 > labelId2) - (labelId1 < labelId2);
				break;
			case INLABEL:
				;
				int labelId11 = (*(VertexDbId *) (key1->mv_data)).labelId;
				int labelId22 = (*(VertexDbId *) (key2->mv_data)).labelId;
				return (labelId11 > labelId22) - (labelId11 < labelId22);
				break;
			}

		} else {
			return (coreOrProperty1 > coreOrProperty2) - (coreOrProperty1 < coreOrProperty2);
		}
	} else {
		return (vertex1Id > vertex2Id) - (vertex1Id < vertex2Id);
	}
	return 0;
}

int compareEdgeDbId(const MDB_val *key1, const MDB_val *key2) {
	int edge1Id = (*(EdgeDbId *) (key1->mv_data)).edgeId;
	int edge2Id = (*(EdgeDbId *) (key2->mv_data)).edgeId;
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
				int propertyKey1 = (*(EdgeDbId *) (key1->mv_data)).propertykeyId;
				int propertyKey2 = (*(EdgeDbId *) (key2->mv_data)).propertykeyId;
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

void printDbStats(MDB_env *env, MDB_dbi vertexDb, char *name) {
	MDB_txn *txn;
	MDB_stat stat;
	mdb_txn_begin(env, NULL, 1, &txn);
	mdb_stat(txn, vertexDb, &stat);
	prstat(&stat, name);
	mdb_txn_commit(txn);
}
