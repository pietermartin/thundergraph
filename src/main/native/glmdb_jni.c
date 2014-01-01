#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glmdb_jni.h"

#ifndef THUNDERGRAPH_STRING
#define THUNDERGRAPH_STRING
#include "thundergraph_string.h"
#endif
#ifndef THUNDERGRAPH_INT
#define THUNDERGRAPH_INT
#include "thundergraph_int.h"
#endif
#ifndef THUNDERGRAPH_LONG
#define THUNDERGRAPH_LONG
#include "thundergraph_long.h"
#endif
#ifndef THUNDERGRAPH_FLOAT
#define THUNDERGRAPH_FLOAT
#include "thundergraph_float.h"
#endif
#ifndef THUNDERGRAPH_DOUBLE
#define THUNDERGRAPH_DOUBLE
#include "thundergraph_double.h"
#endif
#ifndef THUNDERGRAPH_BOOLLEAN
#define THUNDERGRAPH_BOOLEAN
#include "thundergraph_boolean.h"
#endif
#ifndef THUNDERGRAPH_SHORT
#define THUNDERGRAPH_SHORT
#include "thundergraph_short.h"
#endif
#ifndef THUNDERGRAPH_CHAR
#define THUNDERGRAPH_CHAR
#include "thundergraph_char.h"
#endif
#ifndef THUNDERGRAPH_BYTE
#define THUNDERGRAPH_BYTE
#include "thundergraph_byte.h"
#endif

#define	Z	"z"

static void prstat(MDB_stat *ms, char *name) {
	printf("%s\n", name);
	printf("  Tree depth: %u\n", ms->ms_depth);
	printf("  Branch pages: %"Z"u\n", ms->ms_branch_pages);
	printf("  Leaf pages: %"Z"u\n", ms->ms_leaf_pages);
	printf("  Overflow pages: %"Z"u\n", ms->ms_overflow_pages);
	printf("  Entries: %"Z"u\n", ms->ms_entries);
}

JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_init(JNIEnv *env, jclass that) {

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_byte_value
 * Signature: (J[JIB)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1byte_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jbyte value) {

	int rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((signed char *) data.mv_data)) {
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
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_byte_value
 * Signature: (J[JIB)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1byte_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jbyte value) {

	jint rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((signed char *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_value_from_byte_index
 * Signature: (J[JIB)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1byte_1index(JNIEnv *env,
		jclass that, jlong vertexByteIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jbyte value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getFirstElementForKeyValueFromByteIndex((MDB_cursor *) (long) vertexByteIndexDbCursor, propertyKeyId, value,
			(long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_value_for_byte_index
 * Signature: (J[JIB)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1byte_1index(JNIEnv *env,
		jclass that, jlong vertexByteIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jbyte value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;
	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getNextElementForKeyValueFromByteIndex((MDB_cursor *) (long) vertexByteIndexDbCursor, propertyKeyId, value,
			(long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_value_from_byte_index
 * Signature: (JJIB[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1byte_1index(JNIEnv *env,
		jclass that, jlong edgeByteIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jbyte value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

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

	rc = getFirstElementForKeyValueFromByteIndex((MDB_cursor *) (long) edgeByteIndexDbCursor, propertyKeyId, value,
			(long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_value_for_byte_index
 * Signature: (JJIB[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1byte_1index(JNIEnv *env,
		jclass that, jlong edgeByteIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jbyte value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

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

	rc = getNextElementForKeyValueFromByteIndex((MDB_cursor *) (long) edgeByteIndexDbCursor, propertyKeyId, value,
			(long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_byte_value
 * Signature: (J[J[I[J[JIB)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1byte_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jbyte value) {

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

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((signed char *) data.mv_data)) {
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
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_byte_value
 * Signature: (J[J[I[J[JIB)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1byte_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jbyte value) {

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

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((signed char *) data.mv_data)) {
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
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_char_value
 * Signature: (J[JIC)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1char_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jchar value) {

	jint rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((unsigned short *) data.mv_data)) {
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
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_char_value
 * Signature: (J[JIC)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1char_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jchar value) {

	jint rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((unsigned short *) data.mv_data)) {
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
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_value_from_char_index
 * Signature: (J[JIC)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1char_1index(JNIEnv *env,
		jclass that, jlong vertexCharIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jchar value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getFirstElementForKeyValueFromCharIndex((MDB_cursor *) (long) vertexCharIndexDbCursor, propertyKeyId, value,
			(long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_value_for_char_index
 * Signature: (J[JIC)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1char_1index(JNIEnv *env,
		jclass that, jlong vertexCharIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jchar value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;
	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getNextElementForKeyValueFromCharIndex((MDB_cursor *) (long) vertexCharIndexDbCursor, propertyKeyId, value,
			(long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_value_from_char_index
 * Signature: (JJIC[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1char_1index(JNIEnv *env,
		jclass that, jlong edgeCharIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jchar value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

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

	rc = getFirstElementForKeyValueFromCharIndex((MDB_cursor *) (long) edgeCharIndexDbCursor, propertyKeyId, value,
			(long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_value_for_char_index
 * Signature: (JJIC[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1char_1index(JNIEnv *env,
		jclass that, jlong edgeCharIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jchar value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

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

	rc = getNextElementForKeyValueFromCharIndex((MDB_cursor *) (long) edgeCharIndexDbCursor, propertyKeyId, value,
			(long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_char_value
 * Signature: (J[J[I[J[JIC)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1char_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jchar value) {

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

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((unsigned short *) data.mv_data)) {
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
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_char_value
 * Signature: (J[J[I[J[JIC)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1char_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jchar value) {

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

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((unsigned short *) data.mv_data)) {
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
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_short_value
 * Signature: (J[JIS)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1short_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jshort value) {

	jint rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((short *) data.mv_data)) {
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
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_short_value
 * Signature: (J[JIS)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1short_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jshort value) {

	jint rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((short *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_value_from_short_index
 * Signature: (J[JIS)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1short_1index(JNIEnv *env,
		jclass that, jlong vertexShortIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jshort value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getFirstElementForKeyValueFromShortIndex((MDB_cursor *) (long) vertexShortIndexDbCursor, propertyKeyId, value,
			(long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_value_for_short_index
 * Signature: (J[JIS)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1short_1index(JNIEnv *env,
		jclass that, jlong vertexShortIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jshort value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;
	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getNextElementForKeyValueFromShortIndex((MDB_cursor *) (long) vertexShortIndexDbCursor, propertyKeyId, value,
			(long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_value_from_short_index
 * Signature: (JJIS[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1short_1index(JNIEnv *env,
		jclass that, jlong edgeShortIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jshort value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

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

	rc = getFirstElementForKeyValueFromShortIndex((MDB_cursor *) (long) edgeShortIndexDbCursor, propertyKeyId, value,
			(long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_value_for_short_index
 * Signature: (JJIS[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1short_1index(JNIEnv *env,
		jclass that, jlong edgeShortIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jshort value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

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

	rc = getNextElementForKeyValueFromShortIndex((MDB_cursor *) (long) edgeShortIndexDbCursor, propertyKeyId, value,
			(long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_short_value
 * Signature: (J[J[I[J[JIS)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1short_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jshort value) {

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

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((short *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_short_value
 * Signature: (J[J[I[J[JIS)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1short_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jshort value) {

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

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((short *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_boolean_value
 * Signature: (J[JIZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1boolean_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jboolean value) {

	jint rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((unsigned char *) data.mv_data)) {
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
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_boolean_value
 * Signature: (J[JIZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1boolean_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jboolean value) {

	jint rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((unsigned char *) data.mv_data)) {
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
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_value_from_boolean_index
 * Signature: (J[JIZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1boolean_1index(JNIEnv *env,
		jclass that, jlong vertexBooleanIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jboolean value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getFirstElementForKeyValueFromBooleanIndex((MDB_cursor *) (long) vertexBooleanIndexDbCursor, propertyKeyId, value,
			(long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_value_for_boolean_index
 * Signature: (J[JIZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1boolean_1index(JNIEnv *env,
		jclass that, jlong vertexBooleanIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jboolean value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;
	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getNextElementForKeyValueFromBooleanIndex((MDB_cursor *) (long) vertexBooleanIndexDbCursor, propertyKeyId, value,
			(long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_value_from_boolean_index
 * Signature: (JJIZ[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1boolean_1index(JNIEnv *env,
		jclass that, jlong edgeBooleanIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jboolean value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

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

	rc = getFirstElementForKeyValueFromBooleanIndex((MDB_cursor *) (long) edgeBooleanIndexDbCursor, propertyKeyId, value,
			(long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_value_for_boolean_index
 * Signature: (JJIZ[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1boolean_1index(JNIEnv *env,
		jclass that, jlong edgeBooleanIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jboolean value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

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

	rc = getNextElementForKeyValueFromBooleanIndex((MDB_cursor *) (long) edgeBooleanIndexDbCursor, propertyKeyId, value,
			(long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_boolean_value
 * Signature: (J[J[I[J[JIZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1boolean_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jboolean value) {

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

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((unsigned char *) data.mv_data)) {
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
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_boolean_value
 * Signature: (J[J[I[J[JIZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1boolean_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jboolean value) {

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

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((unsigned char *) data.mv_data)) {
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
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_double_value
 * Signature: (J[JID)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1double_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jdouble value) {

	jint rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((double *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_double_value
 * Signature: (J[JID)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1double_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jdouble value) {

	jint rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((double *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_value_from_double_index
 * Signature: (J[JID)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1double_1index(JNIEnv *env,
		jclass that, jlong vertexDoubleIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jdouble value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getFirstElementForKeyValueFromDoubleIndex((MDB_cursor *) (long) vertexDoubleIndexDbCursor, propertyKeyId, value,
			(long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_value_for_double_index
 * Signature: (J[JID)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1double_1index(JNIEnv *env,
		jclass that, jlong vertexDoubleIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jdouble value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;
	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getNextElementForKeyValueFromDoubleIndex((MDB_cursor *) (long) vertexDoubleIndexDbCursor, propertyKeyId, value,
			(long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_value_from_double_index
 * Signature: (JJID[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1double_1index(JNIEnv *env,
		jclass that, jlong edgeDoubleIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jdouble value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

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

	rc = getFirstElementForKeyValueFromDoubleIndex((MDB_cursor *) (long) edgeDoubleIndexDbCursor, propertyKeyId, value,
			(long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_value_for_double_index
 * Signature: (JJID[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1double_1index(JNIEnv *env,
		jclass that, jlong edgeDoubleIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jdouble value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

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

	rc = getNextElementForKeyValueFromDoubleIndex((MDB_cursor *) (long) edgeDoubleIndexDbCursor, propertyKeyId, value,
			(long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_double_value
 * Signature: (J[J[I[J[JID)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1double_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jdouble value) {

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

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((double *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_double_value
 * Signature: (J[J[I[J[JID)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1double_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jdouble value) {

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

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((double *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_float_value
 * Signature: (J[JIF)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1float_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jfloat value) {

	jint rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((float *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_float_value
 * Signature: (J[JIF)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1float_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jfloat value) {

	jint rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((float *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_value_from_float_index
 * Signature: (J[JIF)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1float_1index(JNIEnv *env,
		jclass that, jlong vertexFloatIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jfloat value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getFirstElementForKeyValueFromFloatIndex((MDB_cursor *) (long) vertexFloatIndexDbCursor, propertyKeyId, value,
			(long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_value_for_float_index
 * Signature: (J[JIF)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1float_1index(JNIEnv *env,
		jclass that, jlong vertexFloatIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jfloat value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;
	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getNextElementForKeyValueFromFloatIndex((MDB_cursor *) (long) vertexFloatIndexDbCursor, propertyKeyId, value,
			(long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_value_from_float_index
 * Signature: (JJIF[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1float_1index(JNIEnv *env,
		jclass that, jlong edgeFloatIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jfloat value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

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

	rc = getFirstElementForKeyValueFromFloatIndex((MDB_cursor *) (long) edgeFloatIndexDbCursor, propertyKeyId, value,
			(long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_value_for_float_index
 * Signature: (JJIF[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1float_1index(JNIEnv *env,
		jclass that, jlong edgeFloatIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jfloat value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

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

	rc = getNextElementForKeyValueFromFloatIndex((MDB_cursor *) (long) edgeFloatIndexDbCursor, propertyKeyId, value,
			(long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_float_value
 * Signature: (J[J[I[J[JIF)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1float_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jfloat value) {

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

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((float *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_float_value
 * Signature: (J[J[I[J[JIF)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1float_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jfloat value) {

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

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((float *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_long_value
 * Signature: (J[JIJ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1long_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jlong value) {

	jint rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((long long *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_long_value
 * Signature: (J[JIJ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1long_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jlong value) {

	jint rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((long long *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_value_from_long_index
 * Signature: (J[JIJ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1long_1index(JNIEnv *env,
		jclass that, jlong vertexLongIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jlong value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getFirstElementForKeyValueFromLongIndex((MDB_cursor *) (long) vertexLongIndexDbCursor, propertyKeyId, value,
			(long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_value_for_long_index
 * Signature: (J[JIJ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1long_1index(JNIEnv *env,
		jclass that, jlong vertexLongIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jlong value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;
	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getNextElementForKeyValueFromLongIndex((MDB_cursor *) (long) vertexLongIndexDbCursor, propertyKeyId, value,
			(long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_value_from_long_index
 * Signature: (JJIJ[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1long_1index(JNIEnv *env,
		jclass that, jlong edgeLongIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jlong value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

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

	rc = getFirstElementForKeyValueFromLongIndex((MDB_cursor *) (long) edgeLongIndexDbCursor, propertyKeyId, value,
			(long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_value_for_long_index
 * Signature: (JJIJ[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1long_1index(JNIEnv *env,
		jclass that, jlong edgeLongIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jlong value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

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

	rc = getNextElementForKeyValueFromLongIndex((MDB_cursor *) (long) edgeLongIndexDbCursor, propertyKeyId, value,
			(long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_long_value
 * Signature: (J[J[I[J[JIJ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1long_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jlong value) {

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

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((long long *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_long_value
 * Signature: (J[J[I[J[JIJ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1long_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jlong value) {

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

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((long long *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_stat
 * Signature: (JJI[I[I[I[I[I[I)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1stat(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn, jint dbEnum,
		jintArray ms_psize, jintArray ms_depth, jintArray ms_branch_pages, jintArray ms_leaf_pages, jintArray ms_overflow_pages,
		jintArray ms_entries) {

	int rc = 0;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	MDB_txn *mdbTxn = (MDB_txn *) (long) txn;
	MDB_stat stat;

	jint *ms_psizeC = NULL;
	jint *ms_depthC = NULL;
	jint *ms_branch_pagesC = NULL;
	jint *ms_leaf_pagesC = NULL;
	jint *ms_overflow_pagesC = NULL;
	jint *ms_entriesC = NULL;

	if (ms_psize) {
		if ((ms_psizeC = (*env)->GetIntArrayElements(env, ms_psize, NULL)) == NULL) {
			goto fail;
		}
	}
	if (ms_depth) {
		if ((ms_depthC = (*env)->GetIntArrayElements(env, ms_depth, NULL)) == NULL) {
			goto fail;
		}
	}
	if (ms_branch_pages) {
		if ((ms_branch_pagesC = (*env)->GetIntArrayElements(env, ms_branch_pages, NULL)) == NULL) {
			goto fail;
		}
	}
	if (ms_leaf_pages) {
		if ((ms_leaf_pagesC = (*env)->GetIntArrayElements(env, ms_leaf_pages, NULL)) == NULL) {
			goto fail;
		}
	}
	if (ms_overflow_pages) {
		if ((ms_overflow_pagesC = (*env)->GetIntArrayElements(env, ms_overflow_pages, NULL)) == NULL) {
			goto fail;
		}
	}
	if (ms_entries) {
		if ((ms_entriesC = (*env)->GetIntArrayElements(env, ms_entries, NULL)) == NULL) {
			goto fail;
		}
	}

	switch (dbEnum) {
	case VERTEX_DB:
		mdb_stat(mdbTxn, glmdb_env->vertexDb, &stat);
		break;
	case EDGE_DB:
		mdb_stat(mdbTxn, glmdb_env->edgeDb, &stat);
		break;
	case VERTEX_PROPERTY_DB:
		mdb_stat(mdbTxn, glmdb_env->vertexPropertyKeyDb, &stat);
		break;
	case VERTEX_PROPERTY_INVERSE_DB:
		mdb_stat(mdbTxn, glmdb_env->vertexPropertyKeyInverseDb, &stat);
		break;
	case EDGE_PROPERTY_DB:
		mdb_stat(mdbTxn, glmdb_env->edgePropertyKeyDb, &stat);
		break;
	case EDGE_PROPERTY_INVERSE_DB:
		mdb_stat(mdbTxn, glmdb_env->edgePropertyKeyInverseDb, &stat);
		break;
	case LABEL_DB:
		mdb_stat(mdbTxn, glmdb_env->labelDb, &stat);
		break;
	case CONFIG_DB:
		mdb_stat(mdbTxn, glmdb_env->configDb, &stat);
		break;
	case VERTEX_BOOLEAN_INDEX:
		mdb_stat(mdbTxn, glmdb_env->vertexBooleanIndexDb, &stat);
		break;
	case VERTEX_BYTE_INDEX:
		mdb_stat(mdbTxn, glmdb_env->vertexByteIndexDb, &stat);
		break;
	case VERTEX_SHORT_INDEX:
		mdb_stat(mdbTxn, glmdb_env->vertexShortIndexDb, &stat);
		break;
	case VERTEX_INT_INDEX:
		mdb_stat(mdbTxn, glmdb_env->vertexIntIndexDb, &stat);
		break;
	case VERTEX_LONG_INDEX:
		mdb_stat(mdbTxn, glmdb_env->vertexLongIndexDb, &stat);
		break;
	case VERTEX_FLOAT_INDEX:
		mdb_stat(mdbTxn, glmdb_env->vertexFloatIndexDb, &stat);
		break;
	case VERTEX_DOUBLE_INDEX:
		mdb_stat(mdbTxn, glmdb_env->vertexDoubleIndexDb, &stat);
		break;
	case VERTEX_CHAR_INDEX:
		mdb_stat(mdbTxn, glmdb_env->vertexCharIndexDb, &stat);
		break;
	case VERTEX_STRING_INDEX:
		mdb_stat(mdbTxn, glmdb_env->vertexStringIndexDb, &stat);
		break;
	case EDGE_BOOLEAN_INDEX:
		mdb_stat(mdbTxn, glmdb_env->edgeBooleanIndexDb, &stat);
		break;
	case EDGE_BYTE_INDEX:
		mdb_stat(mdbTxn, glmdb_env->edgeByteIndexDb, &stat);
		break;
	case EDGE_SHORT_INDEX:
		mdb_stat(mdbTxn, glmdb_env->edgeShortIndexDb, &stat);
		break;
	case EDGE_INT_INDEX:
		mdb_stat(mdbTxn, glmdb_env->edgeIntIndexDb, &stat);
		break;
	case EDGE_LONG_INDEX:
		mdb_stat(mdbTxn, glmdb_env->edgeLongIndexDb, &stat);
		break;
	case EDGE_FLOAT_INDEX:
		mdb_stat(mdbTxn, glmdb_env->edgeFloatIndexDb, &stat);
		break;
	case EDGE_DOUBLE_INDEX:
		mdb_stat(mdbTxn, glmdb_env->edgeDoubleIndexDb, &stat);
		break;
	case EDGE_CHAR_INDEX:
		mdb_stat(mdbTxn, glmdb_env->edgeCharIndexDb, &stat);
		break;
	case EDGE_STRING_INDEX:
		mdb_stat(mdbTxn, glmdb_env->edgeStringIndexDb, &stat);
		break;
	default:
		rc = GLMDB_INVALID_DB;
	}

	*ms_psizeC = stat.ms_psize;
	*ms_depthC = stat.ms_depth;
	*ms_branch_pagesC = stat.ms_branch_pages;
	*ms_leaf_pagesC = stat.ms_leaf_pages;
	*ms_overflow_pagesC = stat.ms_overflow_pages;
	*ms_entriesC = stat.ms_entries;

	fail:

	if (ms_psize && ms_psizeC) {
		(*env)->ReleaseIntArrayElements(env, ms_psize, ms_psizeC, 0);
	}
	if (ms_depth && ms_depthC) {
		(*env)->ReleaseIntArrayElements(env, ms_depth, ms_depthC, 0);
	}
	if (ms_branch_pages && ms_branch_pagesC) {
		(*env)->ReleaseIntArrayElements(env, ms_branch_pages, ms_branch_pagesC, 0);
	}
	if (ms_leaf_pages && ms_leaf_pagesC) {
		(*env)->ReleaseIntArrayElements(env, ms_leaf_pages, ms_leaf_pagesC, 0);
	}
	if (ms_overflow_pages && ms_overflow_pagesC) {
		(*env)->ReleaseIntArrayElements(env, ms_overflow_pages, ms_overflow_pagesC, 0);
	}
	if (ms_entries && ms_entriesC) {
		(*env)->ReleaseIntArrayElements(env, ms_entries, ms_entriesC, 0);
	}

	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_env_get_path
 * Signature: (J[[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1env_1get_1path(JNIEnv *env, jclass that, jlong glmdbEnv,
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

JNIEXPORT jstring JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1strerror(JNIEnv *env, jclass that, jint error) {

	char *mdbError = mdb_strerror(error);
	jstring message = (*env)->NewStringUTF(env, mdbError);
	return message;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    print_db
 * Signature: (JJI)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_print_1db(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn, jint dbEnum) {

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
	case VERTEX_PROPERTY_INVERSE_DB:
		printf("VERTEX_PROPERTY_INVERSE_DB...\n");
		traverseVertexPropertyKeyInverseDb(glmdb_env, (MDB_txn *) (long) txn);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->vertexPropertyKeyInverseDb, "vertexPropertyKeyInverseDb");
		break;
	case EDGE_PROPERTY_DB:
		printf("EDGE_PROPERTY_DB...\n");
		traverseEdgePropertyKeyDb(glmdb_env, (MDB_txn *) (long) txn);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->edgePropertyKeyDb, "edgePropertyKeyDb");
		break;
	case EDGE_PROPERTY_INVERSE_DB:
		printf("EDGE_PROPERTY_INVERSE_DB...\n");
		traverseEdgePropertyKeyInverseDb(glmdb_env, (MDB_txn *) (long) txn);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->edgePropertyKeyInverseDb, "edgePropertyKeyInverseDb");
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
		printf("VERTEX_BOOLEAN_INDEX...\n");
		traverseBooleanIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->vertexBooleanIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->vertexBooleanIndexDb, "vertexBooleanIndexDb");
		break;
	case VERTEX_BYTE_INDEX:
		printf("VERTEX_BYTE_INDEX...\n");
		traverseByteIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->vertexByteIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->vertexByteIndexDb, "vertexByteIndexDb");
		break;
	case VERTEX_SHORT_INDEX:
		printf("VERTEX_SHORT_INDEX...\n");
		traverseShortIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->vertexShortIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->vertexShortIndexDb, "vertexShortIndexDb");
		break;
	case VERTEX_INT_INDEX:
		printf("VERTEX_INT_INDEX...\n");
		traverseIntIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->vertexIntIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->vertexIntIndexDb, "vertexIntIndexDb");
		break;
	case VERTEX_LONG_INDEX:
		printf("VERTEX_LONG_INDEX...\n");
		traverseLongIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->vertexLongIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->vertexLongIndexDb, "vertexLongIndexDb");
		break;
	case VERTEX_FLOAT_INDEX:
		printf("VERTEX_FLOAT_INDEX...\n");
		traverseFloatIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->vertexFloatIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->vertexFloatIndexDb, "vertexFloatIndexDb");
		break;
	case VERTEX_DOUBLE_INDEX:
		printf("VERTEX_DOUBLE_INDEX...\n");
		traverseDoubleIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->vertexDoubleIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->vertexDoubleIndexDb, "vertexDoubleIndexDb");
		break;
	case VERTEX_CHAR_INDEX:
		printf("VERTEX_CHAR_INDEX...\n");
		traverseCharIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->vertexCharIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->vertexCharIndexDb, "vertexCharIndexDb");
		break;
	case VERTEX_STRING_INDEX:
		printf("VERTEX_STRING_INDEX...\n");
		traverseStringIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->vertexStringIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->vertexStringIndexDb, "vertexStringIndexDb");
		break;
	case EDGE_BOOLEAN_INDEX:
		printf("EDGE_BOOLEAN_INDEX...\n");
		traverseBooleanIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->edgeBooleanIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->edgeBooleanIndexDb, "edgeBooleanIndexDb");
		break;
	case EDGE_BYTE_INDEX:
		printf("EDGE_BYTE_INDEX...\n");
		traverseByteIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->edgeByteIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->edgeByteIndexDb, "edgeByteIndexDb");
		break;
	case EDGE_SHORT_INDEX:
		printf("EDGE_SHORT_INDEX...\n");
		traverseShortIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->edgeShortIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->edgeShortIndexDb, "edgeShortIndexDb");
		break;
	case EDGE_INT_INDEX:
		printf("EDGE_INT_INDEX...\n");
		traverseIntIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->edgeIntIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->edgeIntIndexDb, "edgeIntIndexDb");
		break;
	case EDGE_LONG_INDEX:
		printf("EDGE_LONG_INDEX...\n");
		traverseLongIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->edgeLongIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->edgeLongIndexDb, "edgeLongIndexDb");
		break;
	case EDGE_FLOAT_INDEX:
		printf("EDGE_FLOAT_INDEX...\n");
		traverseFloatIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->edgeFloatIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->edgeFloatIndexDb, "edgeFloatIndexDb");
		break;
	case EDGE_DOUBLE_INDEX:
		printf("EDGE_DOUBLE_INDEX...\n");
		traverseDoubleIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->edgeDoubleIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->edgeDoubleIndexDb, "edgeDoubleIndexDb");
		break;
	case EDGE_CHAR_INDEX:
		printf("EDGE_CHAR_INDEX...\n");
		traverseCharIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->edgeCharIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->edgeCharIndexDb, "edgeCharIndexDb");
		break;
	case EDGE_STRING_INDEX:
		printf("EDGE_STRING_INDEX...\n");
		traverseStringIndexDb(glmdb_env, (MDB_txn *) (long) txn, glmdb_env->edgeStringIndexDb);
		printDbStats(glmdb_env->env, (MDB_txn *) (long) txn, glmdb_env->edgeStringIndexDb, "edgeStringIndexDb");
		break;
	default:
		rc = GLMDB_INVALID_DB;
	}
	return rc;

}

JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_glmdb_1env_1create(JNIEnv * env, jclass that, jstring path,
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
JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_glmdb_1env_1close(JNIEnv *env, jclass that, jlong glmdbEnv) {

	closeGraph((GLMDB_env *) (long) glmdbEnv);

}

JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1txn_1begin(JNIEnv *env, jclass that, jlong glmdbEnv, jlong parent,
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

JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1txn_1renew(JNIEnv *env, jclass that, jlong txn) {

	jint rc = 0;
	rc = (jint) mdb_txn_renew((MDB_txn *) (long) txn);
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_txn_commit
 * Signature: (JJZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1txn_1commit(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn,
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

JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1txn_1reset(JNIEnv *env, jclass that, jlong txn) {

	mdb_txn_reset((MDB_txn *) (long) txn);

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_txn_abort
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1txn_1abort(JNIEnv *env, jclass that, jlong glmdb_env, jlong txn) {

	mdb_txn_abort((MDB_txn *) (long) txn);

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_cursor_open_and_position_on_edge_vertex_db
 * Signature: (JJJIIJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1edge_1vertex_1db(JNIEnv *env,
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
	rc = mdb_cursor_get((MDB_cursor *) mdbCursor, &key, &data, MDB_SET_RANGE);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}

	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_vertex_vertex_db
 * Signature: (JJJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1vertex_1vertex_1db(JNIEnv *env,
		jclass that, jlong txn, jlong glmdbEnv, jlong vertexId, jlongArray cursorArray) {

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
	vertexDbId.coreOrPropertyEnum = VCORE;
	vertexDbId.propertykeyId = -1;
	vertexDbId.labelId = -1;
	vertexDbId.edgeId = -1LL;

	key.mv_size = sizeof(VertexDbId);
	key.mv_data = &vertexDbId;
	rc = mdb_cursor_get((MDB_cursor *) mdbCursor, &key, &data, MDB_SET_RANGE);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}

	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_edge_edge_db
 * Signature: (JJJI[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1edge_1edge_1db(JNIEnv *env,
		jclass that, jlong txn, jlong glmdbEnv, jlong edgeId, jint propertykeyId, jlongArray cursorArray) {

	MDB_cursor *mdbCursor;
	jlong *cursor = NULL;
	jint rc = 0;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}
	MDB_val key, data;
	EdgeDbId edgeDbId;
	edgeDbId.coreOrPropertyEnum = EPROPERTY_KEY;
	edgeDbId.edgeId = edgeId;
	edgeDbId.propertykeyId = propertykeyId;

	key.mv_size = sizeof(EdgeDbId);
	key.mv_data = &edgeDbId;
	rc = mdb_cursor_get((MDB_cursor *) mdbCursor, &key, &data, MDB_SET);

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
JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1close(JNIEnv *env, jclass that, jlong cursor) {

	mdb_cursor_close((MDB_cursor *) (long) cursor);
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_cursor_renew
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1renew(JNIEnv *env, jclass that, jlong txn, jlong cursor) {

	jint rc = 0;
	rc = (jint) mdb_cursor_renew((MDB_txn *) (long) txn, (MDB_cursor *) (long) cursor);
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open
 * Signature: (JJI[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open(JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv,
		jint dbEnum, jlongArray cursorArray) {

	jlong *cursor = NULL;
	jint rc = 0;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}

	switch (dbEnum) {
	case VERTEX_DB:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexDb, (MDB_cursor **) cursor);
		break;
	case EDGE_DB:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeDb, (MDB_cursor **) cursor);
		break;
	case VERTEX_PROPERTY_DB:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexPropertyKeyDb, (MDB_cursor **) cursor);
		break;
	case EDGE_PROPERTY_DB:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgePropertyKeyDb, (MDB_cursor **) cursor);
		break;
	case LABEL_DB:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->labelDb, (MDB_cursor **) cursor);
		break;
	case CONFIG_DB:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->configDb, (MDB_cursor **) cursor);
		break;
	case VERTEX_BOOLEAN_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexBooleanIndexDb, (MDB_cursor **) cursor);
		break;
	case VERTEX_BYTE_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexByteIndexDb, (MDB_cursor **) cursor);
		break;
	case VERTEX_SHORT_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexShortIndexDb, (MDB_cursor **) cursor);
		break;
	case VERTEX_INT_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexIntIndexDb, (MDB_cursor **) cursor);
		break;
	case VERTEX_LONG_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexLongIndexDb, (MDB_cursor **) cursor);
		break;
	case VERTEX_FLOAT_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexFloatIndexDb, (MDB_cursor **) cursor);
		break;
	case VERTEX_DOUBLE_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexDoubleIndexDb, (MDB_cursor **) cursor);
		break;
	case VERTEX_CHAR_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexCharIndexDb, (MDB_cursor **) cursor);
		break;
	case VERTEX_STRING_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexStringIndexDb, (MDB_cursor **) cursor);
		break;
	case EDGE_BOOLEAN_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeBooleanIndexDb, (MDB_cursor **) cursor);
		break;
	case EDGE_BYTE_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeByteIndexDb, (MDB_cursor **) cursor);
		break;
	case EDGE_SHORT_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeShortIndexDb, (MDB_cursor **) cursor);
		break;
	case EDGE_INT_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeIntIndexDb, (MDB_cursor **) cursor);
		break;
	case EDGE_LONG_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeLongIndexDb, (MDB_cursor **) cursor);
		break;
	case EDGE_FLOAT_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeFloatIndexDb, (MDB_cursor **) cursor);
		break;
	case EDGE_DOUBLE_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeDoubleIndexDb, (MDB_cursor **) cursor);
		break;
	case EDGE_CHAR_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeCharIndexDb, (MDB_cursor **) cursor);
		break;
	case EDGE_STRING_INDEX:
		rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeStringIndexDb, (MDB_cursor **) cursor);
		break;
	default:
		rc = GLMDB_INVALID_DB;
	}

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_add_vertex
 * Signature: (JJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1add_1vertex(JNIEnv *env, jclass that, jlong glmdbEnv, jlong cursor,
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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1add_1edge(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn,
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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_set_property_boolean
 * Signature: (JJJJIZZZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1boolean(JNIEnv *env, jclass that, jlong glmdbEnv,
		jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jboolean value, jboolean vertex, jboolean indexed) {

	jint rc = 0;
	GLMDB_env *glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	MDB_txn *mdbTxn = (MDB_txn *) (long) txn;

	if (vertex) {

		if (indexed) {
			rc = addOrUpdateBooleanIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId, value, 1);
		} else {
			rc = setVertexPropertyBoolean((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
		}
	} else {
		if (indexed) {
			rc = addOrUpdateBooleanIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId, value, 0);
		} else {
			rc = setEdgePropertyBoolean((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
		}
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_set_property_byte
 * Signature: (JJJJIBZZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1byte(JNIEnv *env, jclass that, jlong glmdbEnv,
		jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jbyte value, jboolean vertex, jboolean indexed) {

	jint rc = 0;
	GLMDB_env *glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	MDB_txn *mdbTxn = (MDB_txn *) (long) txn;

	if (vertex) {

		if (indexed) {
			rc = addOrUpdateByteIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId, value, 1);
		} else {
			rc = setVertexPropertyByte((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
		}
	} else {
		if (indexed) {
			rc = addOrUpdateByteIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId, value, 0);
		} else {
			rc = setEdgePropertyByte((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
		}
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_set_property_short
 * Signature: (JJJJISZZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1short(JNIEnv *env, jclass that, jlong glmdbEnv,
		jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jshort value, jboolean vertex, jboolean indexed) {

	jint rc = 0;
	GLMDB_env *glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	MDB_txn *mdbTxn = (MDB_txn *) (long) txn;

	if (vertex) {

		if (indexed) {
			rc = addOrUpdateShortIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId, value, 1);
		} else {
			rc = setVertexPropertyShort((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
		}
	} else {
		if (indexed) {
			rc = addOrUpdateShortIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId, value, 0);
		} else {
			rc = setEdgePropertyShort((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
		}
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_set_property_int
 * Signature: (JJJJIIZZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1int(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn,
		jlong cursor, jlong elementId, jint propertyKeyId, jint value, jboolean vertex, jboolean indexed) {

	jint rc = 0;
	GLMDB_env *glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	MDB_txn *mdbTxn = (MDB_txn *) (long) txn;

	if (vertex) {

		if (indexed) {
			rc = addOrUpdateIntIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId, value, 1);
		} else {
			rc = setVertexPropertyInt((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
		}
	} else {
		if (indexed) {
			rc = addOrUpdateIntIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId, value, 0);
		} else {
			rc = setEdgePropertyInt((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
		}
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_set_property_long
 * Signature: (JJJJIJZZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1long(JNIEnv *env, jclass that, jlong glmdbEnv,
		jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jlong value, jboolean vertex, jboolean indexed) {

	jint rc = 0;
	GLMDB_env *glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	MDB_txn *mdbTxn = (MDB_txn *) (long) txn;

	if (vertex) {

		if (indexed) {
			rc = addOrUpdateLongIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId, value, 1);
		} else {
			rc = setVertexPropertyLong((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
		}
	} else {
		if (indexed) {
			rc = addOrUpdateLongIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId, value, 0);
		} else {
			rc = setEdgePropertyLong((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
		}
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_set_property_float
 * Signature: (JJJJIFZZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1float(JNIEnv *env, jclass that, jlong glmdbEnv,
		jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jfloat value, jboolean vertex, jboolean indexed) {

	jint rc = 0;
	GLMDB_env *glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	MDB_txn *mdbTxn = (MDB_txn *) (long) txn;

	if (vertex) {

		if (indexed) {
			rc = addOrUpdateFloatIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId, value, 1);
		} else {
			rc = setVertexPropertyFloat((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
		}
	} else {
		if (indexed) {
			rc = addOrUpdateFloatIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId, value, 0);
		} else {
			rc = setEdgePropertyFloat((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
		}
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_set_property_double
 * Signature: (JJJJIDZZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1double(JNIEnv *env, jclass that, jlong glmdbEnv,
		jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jdouble value, jboolean vertex, jboolean indexed) {

	jint rc = 0;
	GLMDB_env *glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	MDB_txn *mdbTxn = (MDB_txn *) (long) txn;

	if (vertex) {

		if (indexed) {
			rc = addOrUpdateDoubleIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId, value, 1);
		} else {
			rc = setVertexPropertyDouble((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
		}
	} else {
		if (indexed) {
			rc = addOrUpdateDoubleIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId, value, 0);
		} else {
			rc = setEdgePropertyDouble((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
		}
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_set_property_char
 * Signature: (JJJJICZZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1char(JNIEnv *env, jclass that, jlong glmdbEnv,
		jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jchar value, jboolean vertex, jboolean indexed) {

	jint rc = 0;
	GLMDB_env *glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	MDB_txn *mdbTxn = (MDB_txn *) (long) txn;

	if (vertex) {

		if (indexed) {
			rc = addOrUpdateCharIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId, value, 1);
		} else {
			rc = setVertexPropertyChar((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
		}
	} else {
		if (indexed) {
			rc = addOrUpdateCharIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId, value, 0);
		} else {
			rc = setEdgePropertyChar((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, &value);
		}
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_string
 * Signature: (JJJJILjava/lang/String;ZZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1string(JNIEnv *env, jclass that, jlong glmdbEnv,
		jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jstring value, jboolean vertex, jboolean indexed) {

	jint rc = 0;
	GLMDB_env *glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	MDB_txn *mdbTxn = (MDB_txn *) (long) txn;
	jint propertyValueLength = (*env)->GetStringUTFLength(env, value);
//	printf("propertyValueLength = %i\n", propertyValueLength);
	char propertyValue[propertyValueLength];
	//GetStringUTFRegion breaks on values with a length bigger than 80
//	if (value) {
//		(*env)->GetStringUTFRegion(env, value, 0, propertyValueLength, propertyValue);
//		if (propertyValue == NULL) {
//			goto fail;
//		}
//	}
//	printf("propertyValue = %.*s\n", propertyValueLength, propertyValue);

	const char *inCStr = (*env)->GetStringUTFChars(env, value, NULL);
	if (NULL == inCStr) {
		return GLMDB_INVALID_STRING;
	}
	memcpy(propertyValue, inCStr, propertyValueLength);
//	printf("propertyValue = %.*s\n", propertyValueLength, propertyValue);

	if (vertex) {
		if (indexed) {
			rc = addOrUpdateStringIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId,
					propertyValueLength, propertyValue, 1);
		} else {
			rc = setVertexPropertyString((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, propertyValueLength,
					propertyValue);
		}
	} else {

		if (indexed) {
			rc = addOrUpdateStringIndexedProperty(glmdb_env, mdbTxn, (MDB_cursor *) (long) cursor, elementId, propertyKeyId,
					propertyValueLength, propertyValue, 0);
		} else {
			rc = setEdgePropertyString((MDB_cursor *) (long) cursor, (long) elementId, (int) propertyKeyId, propertyValueLength,
					propertyValue);
		}

	}

	(*env)->ReleaseStringUTFChars(env, value, inCStr);
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_property_array
 * Signature: (JJI[[BZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1property_1array(JNIEnv *env, jclass that, jlong cursor,
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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1del_1property(JNIEnv *env, jclass that, jlong cursor, jlong elementId,
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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1property(JNIEnv *env, jclass that, jlong cursor, jlong vertexId,
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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1property_1keys(JNIEnv *env, jclass that, jlong cursor,
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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1propertykey(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn,
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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_reindex_property
 * Signature: (JJIIZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1reindex_1property(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn,
		jint propertyKeyId, jint propertyKeyEnum, jboolean vertex) {

	int rc;
	GLMDB_env *glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	MDB_txn *mdbTxn = (MDB_txn *) (long) txn;

	rc = reindexProperty(glmdb_env, mdbTxn, propertyKeyId, propertyKeyEnum, vertex);

	return rc;

}

int reindexProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, int propertyKeyId, int propertyKeyEnum, unsigned char vertex) {

	int rc;
	MDB_dbi dbi;
	MDB_cursor *cursor;
	MDB_cursor *indexCursor;
	MDB_val key, data;
	if (vertex) {
		dbi = glmdb_env->vertexDb;
	} else {
		dbi = glmdb_env->edgeDb;
	}

	rc = mdb_cursor_open(mdbTxn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	MDB_dbi indexDbi;
	switch (propertyKeyEnum) {
	case BOOLEAN:
		indexDbi = vertex ? glmdb_env->vertexBooleanIndexDb : glmdb_env->edgeBooleanIndexDb;
		break;
	case BYTE:
		indexDbi = vertex ? glmdb_env->vertexByteIndexDb : glmdb_env->edgeByteIndexDb;
		break;
	case SHORT:
		indexDbi = vertex ? glmdb_env->vertexShortIndexDb : glmdb_env->edgeShortIndexDb;
		break;
	case INT:
		indexDbi = vertex ? glmdb_env->vertexIntIndexDb : glmdb_env->edgeIntIndexDb;
		break;
	case LONG:
		indexDbi = vertex ? glmdb_env->vertexLongIndexDb : glmdb_env->edgeLongIndexDb;
		break;
	case FLOAT:
		indexDbi = vertex ? glmdb_env->vertexFloatIndexDb : glmdb_env->edgeFloatIndexDb;
		break;
	case DOUBLE:
		indexDbi = vertex ? glmdb_env->vertexDoubleIndexDb : glmdb_env->edgeDoubleIndexDb;
		break;
	case CHAR:
		indexDbi = vertex ? glmdb_env->vertexCharIndexDb : glmdb_env->edgeCharIndexDb;
		break;
	case STRING:
		indexDbi = vertex ? glmdb_env->vertexStringIndexDb : glmdb_env->edgeStringIndexDb;
		break;
	default:
		rc = GLMDB_INVALID_SEQUENCE;
		break;
	}
	if (rc != 0) {
		goto fail;
	}

	rc = mdb_cursor_open(mdbTxn, indexDbi, &indexCursor);
	if (rc != 0) {
		goto fail;
	}

	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = (*((VertexDbId *) (key.mv_data)));
		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == propertyKeyId) {

			int propertyValueLength = data.mv_size;
			char propertyValue[propertyValueLength];
			switch (propertyKeyEnum) {
			case BOOLEAN:
				rc = setBooleanIndex(indexCursor, vertexDbId.vertexId, propertyKeyId, *((unsigned char *) data.mv_data));
				break;
			case BYTE:
				rc = setByteIndex(indexCursor, vertexDbId.vertexId, propertyKeyId, *((signed char *) data.mv_data));
				break;
			case SHORT:
				rc = setShortIndex(indexCursor, vertexDbId.vertexId, propertyKeyId, *((short *) data.mv_data));
				break;
			case INT:
				rc = setIntIndex(indexCursor, vertexDbId.vertexId, propertyKeyId, *((int *) data.mv_data));
				break;
			case LONG:
				rc = setLongIndex(indexCursor, vertexDbId.vertexId, propertyKeyId, *((long long *) data.mv_data));
				break;
			case FLOAT:
				rc = setFloatIndex(indexCursor, vertexDbId.vertexId, propertyKeyId, *((float *) data.mv_data));
				break;
			case DOUBLE:
				rc = setDoubleIndex(indexCursor, vertexDbId.vertexId, propertyKeyId, *((double *) data.mv_data));
				break;
			case CHAR:
				rc = setCharIndex(indexCursor, vertexDbId.vertexId, propertyKeyId, *((unsigned short *) data.mv_data));
				break;
			case STRING:
				;
				memcpy(propertyValue, data.mv_data, propertyValueLength);
				rc = setStringIndex(indexCursor, vertexDbId.vertexId, propertyKeyId, propertyValueLength, propertyValue);
				break;
			default:
				rc = GLMDB_INVALID_SEQUENCE;
				break;
			}
			if (rc != 0) {
				goto fail;
			}
		}

	}

	if (rc == MDB_NOTFOUND) {
		rc = 0;
	}

	fail: mdb_cursor_close(cursor);
	mdb_cursor_close(indexCursor);
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_first_property_key
 * Signature: (J[I[I[Z[[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1property_1key(JNIEnv *env, jclass that, jlong cursor,
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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1property_1key(JNIEnv *env, jclass that, jlong cursor,
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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1label(JNIEnv *env, jclass that, jlong cursor,
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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1label(JNIEnv *env, jclass that, jlong cursor,
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
	MDB_cursor *inverseCursor;
	MDB_dbi propertyKeyDb;
	MDB_dbi propertyKeyInverseDb;
	PropertyKeyInverseDataStruct *propertyKeyInverseDataStruct = NULL;
	if (vertex == 0) {
		propertyKeyDb = glmdb_env->edgePropertyKeyDb;
		propertyKeyInverseDb = glmdb_env->edgePropertyKeyInverseDb;
	} else {
		propertyKeyDb = glmdb_env->vertexPropertyKeyDb;
		propertyKeyInverseDb = glmdb_env->vertexPropertyKeyInverseDb;
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

	if (rc != 0) {
		goto fail;
	}

	//Do the inverse property key db
	MDB_val inverseKey, inverseData;
	inverseKey.mv_size = sizeof(int);
	inverseKey.mv_data = &(propertyKeyDataStruct.propertyKeyId);
	propertyKeyInverseDataStruct = malloc(sizeof(PropertyKeyInverseDataStruct) + propertyKeyLength);
	propertyKeyInverseDataStruct->type = propertyKeyDataStruct.type;
	propertyKeyInverseDataStruct->indexed = propertyKeyDataStruct.indexed;
	memcpy(propertyKeyInverseDataStruct->propertyKey, propertyKeyC, propertyKeyLength);
	inverseData.mv_size = sizeof(PropertyKeyInverseDataStruct) + propertyKeyLength;
	inverseData.mv_data = propertyKeyInverseDataStruct;
	rc = mdb_cursor_open(txn, propertyKeyInverseDb, &inverseCursor);
	if (rc != 0)
		goto fail;

	if (overwrite) {
		rc = mdb_cursor_put(inverseCursor, &inverseKey, &inverseData, 0/*Allow overwrites*/);
	} else {
		rc = mdb_cursor_put(inverseCursor, &inverseKey, &inverseData, MDB_NOOVERWRITE);
	}

	if (rc != 0) {
		goto fail;
	}

	*propertyKeyId = (*((PropertyKeyDataStruct *) (data.mv_data))).propertyKeyId;

	fail: free(propertyKeyInverseDataStruct);
	mdb_cursor_close(cursor);
	mdb_cursor_close(inverseCursor);
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_label
 * Signature: (JJLjava/lang/String;[I)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1label(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn,
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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1vertex(JNIEnv *env, jclass that, jlong cursor, jlong vertexId,
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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1remove_1vertex(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn,
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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex(JNIEnv *env, jclass that, jlong cursor,
		jlongArray vertexIdResult) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getFirstVertex((MDB_cursor *) (long) cursor, (long long *) vertexIdResultC);

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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex(JNIEnv *env, jclass that, jlong cursor,
		jlong previousVertexId, jlongArray vertexIdResult) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getNextVertex((MDB_cursor *) (long) cursor, previousVertexId, (long long *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_value_from_string_index
 * Signature: (J[JILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1string_1index(JNIEnv *env,
		jclass that, jlong cursor, jlongArray vertexIdResult, jint propertyKey, jstring value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;
	jint propertyValueLength = (*env)->GetStringUTFLength(env, value);
	char propertyValue[propertyValueLength];
	if (value) {
		(*env)->GetStringUTFRegion(env, value, 0, propertyValueLength, propertyValue);
		if (propertyValue == NULL) {
			goto fail;
		}
	}

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getFirstElementForKeyValueFromStringIndex((MDB_cursor *) (long) cursor, propertyKey, propertyValueLength, propertyValue,
			(long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_value_for_string_index
 * Signature: (J[JILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1string_1index(JNIEnv *env,
		jclass that, jlong cursor, jlongArray vertexIdResult, jint propertyKey, jstring value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;
	jint propertyValueLength = (*env)->GetStringUTFLength(env, value);
	char propertyValue[propertyValueLength];
	if (value) {
		(*env)->GetStringUTFRegion(env, value, 0, propertyValueLength, propertyValue);
		if (propertyValue == NULL) {
			goto fail;
		}
	}

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getNextElementForKeyValueFromStringIndex((MDB_cursor *) (long) cursor, propertyKey, propertyValueLength, propertyValue,
			(long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;
}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_value_from_string_index
 * Signature: (JJILjava/lang/String;[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1string_1index(JNIEnv *env,
		jclass that, jlong edgeStringIndexDbCursor, jlong edgeDbCursor, jint propertyKey, jstring value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

	jint rc = 0;

	jlong *edgeIdResultC = NULL;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;
	jint propertyValueLength = (*env)->GetStringUTFLength(env, value);
	char propertyValue[propertyValueLength];

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
		(*env)->GetStringUTFRegion(env, value, 0, propertyValueLength, propertyValue);
		if (propertyValue == NULL) {
			goto fail;
		}
	}

	rc = getFirstElementForKeyValueFromStringIndex((MDB_cursor *) (long) edgeStringIndexDbCursor, propertyKey, propertyValueLength,
			propertyValue, (long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_edge_from_edge_string_index_db
 * Signature: (JJILjava/lang/String;[J[Ljava/lang/String;[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1edge_1from_1edge_1string_1index_1db(JNIEnv *env,
		jclass that, jlong edgeStringIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jstring value, jlongArray edgeIdArray,
		jobjectArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

	jint rc = 0;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;
	jlong *edgeIdC = NULL;

	jint propertyValueLength = (*env)->GetStringUTFLength(env, value);
	char propertyValue[propertyValueLength];
	if (value) {
		(*env)->GetStringUTFRegion(env, value, 0, propertyValueLength, propertyValue);
		if (propertyValue == NULL) {
			goto fail;
		}
	}

	if (edgeIdArray) {
		if ((edgeIdC = (*env)->GetLongArrayElements(env, edgeIdArray, NULL)) == NULL) {
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

	rc = getCurrentElementFromStringIndexDb((MDB_cursor *) (long) edgeStringIndexDbCursor, edgeIdC, propertyKeyId, propertyValueLength,
			propertyValue);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		*edgeIdC = edgeDbId.edgeId;
		EdgeData edgeData = *((EdgeData *) (data.mv_data));
		*outVertexIdC = edgeData.vertexOutId;
		*inVertexIdC = edgeData.vertexInId;
		*labelIdC = edgeData.labelId;
	}

	fail: if (edgeIdArray && edgeIdC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdArray, edgeIdC, 0);
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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_value_for_string_index
 * Signature: (JJILjava/lang/String;[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1string_1index(JNIEnv *env,
		jclass that, jlong edgeStringIndexDbCursor, jlong edgeDbCursor, jint propertyKey, jstring value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

	jint rc = 0;

	jlong *edgeIdResultC = NULL;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;
	jint propertyValueLength = (*env)->GetStringUTFLength(env, value);
	char propertyValue[propertyValueLength];

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
		(*env)->GetStringUTFRegion(env, value, 0, propertyValueLength, propertyValue);
		if (propertyValue == NULL) {
			goto fail;
		}
	}

	rc = getNextElementForKeyValueFromStringIndex((MDB_cursor *) (long) edgeStringIndexDbCursor, propertyKey, propertyValueLength,
			propertyValue, (long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_value_from_int_index
 * Signature: (J[JII)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1int_1index(JNIEnv *env,
		jclass that, jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jint value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getFirstElementForKeyValueFromIntIndex((MDB_cursor *) (long) cursor, propertyKeyId, value, (long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_value_for_int_index
 * Signature: (J[JII)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1int_1index(JNIEnv *env,
		jclass that, jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jint value) {

	jint rc = 0;
	jlong *vertexIdResultC = NULL;
	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getNextElementForKeyValueFromIntIndex((MDB_cursor *) (long) cursor, propertyKeyId, value, (long long int *) vertexIdResultC);

	fail: if (vertexIdResult && vertexIdResultC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdResult, vertexIdResultC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_value_from_int_index
 * Signature: (JJII[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1int_1index(JNIEnv *env,
		jclass that, jlong edgeIntIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jint value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

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

	rc = getFirstElementForKeyValueFromIntIndex((MDB_cursor *) (long) edgeIntIndexDbCursor, propertyKeyId, value,
			(long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_value_for_int_index
 * Signature: (JJII[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1int_1index(JNIEnv *env,
		jclass that, jlong edgeIntIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jint value, jlongArray edgeIdResult,
		jintArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

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

	rc = getNextElementForKeyValueFromIntIndex((MDB_cursor *) (long) edgeIntIndexDbCursor, propertyKeyId, value,
			(long long int *) edgeIdResultC);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdResultC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

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
 * Method:    mdb_get_edge
 * Signature: (JJ[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1edge(JNIEnv *env, jclass that, jlong cursor, jlong edgeId,
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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1remove_1edge(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn,
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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge(JNIEnv * env, jclass that, jlong cursor,
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
			printEdgeRecord(key, data);
			printf("mdb_get_first_edge edgeDbId.coreOrPropertyEnum = %i\n", edgeDbId.coreOrPropertyEnum);
			printf("mdb_get_first_edge = %i\n", rc);
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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge(JNIEnv *env, jclass that, jlong cursor,
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
 * Method:    mdb_get_first_edge_from_vertex
 * Signature: (JIIJ[J[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1from_1vertex(JNIEnv *env, jclass that, jlong cursor,
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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1from_1vertex(JNIEnv *env, jclass that, jlong cursor,
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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_edge_from_vertex
 * Signature: (JIIJ[J[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1edge_1from_1vertex(JNIEnv *env, jclass that,
		jlong cursor, jint direction, jint labelId, jlong fromVertexId, jlongArray edgeIdResult, jlongArray outVertexId,
		jlongArray inVertexId) {

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

	rc = getCurrentEdgefromVertex((MDB_cursor *) (long) cursor, direction, labelId, fromVertexId, edgeIdResultC, outVertexIdC, inVertexIdC);

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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1from_1vertex_1all_1labels(JNIEnv *env, jclass that,
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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1from_1vertex_1all_1labels(JNIEnv *env, jclass that,
		jlong cursor, jint direction, jlong fromVertexId, jintArray labelIdResult, jlongArray edgeIdResult, jlongArray outVertexId,
		jlongArray inVertexId) {

	jint rc = 0;
	jint *labelIdResultC = NULL;
	jlong *edgeIdResultC = NULL;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;

//	(*env)->GetPrimitiveArrayCritical(env, labelIdResult, NULL)
	if (labelIdResult) {
		if ((labelIdResultC = (*env)->GetPrimitiveArrayCritical(env, labelIdResult, NULL)) == NULL) {
			goto fail;
		}
	}
	if (edgeIdResult) {
		if ((edgeIdResultC = (*env)->GetPrimitiveArrayCritical(env, edgeIdResult, NULL)) == NULL) {
			goto fail;
		}
	}
	if (outVertexId) {
		if ((outVertexIdC = (*env)->GetPrimitiveArrayCritical(env, outVertexId, NULL)) == NULL) {
			goto fail;
		}
	}
	if (inVertexId) {
		if ((inVertexIdC = (*env)->GetPrimitiveArrayCritical(env, inVertexId, NULL)) == NULL) {
			goto fail;
		}
	}

//	if (labelIdResult) {
//		if ((labelIdResultC = (*env)->GetIntArrayElements(env, labelIdResult, NULL)) == NULL) {
//			goto fail;
//		}
//	}
//	if (edgeIdResult) {
//		if ((edgeIdResultC = (*env)->GetLongArrayElements(env, edgeIdResult, NULL)) == NULL) {
//			goto fail;
//		}
//	}
//	if (outVertexId) {
//		if ((outVertexIdC = (*env)->GetLongArrayElements(env, outVertexId, NULL)) == NULL) {
//			goto fail;
//		}
//	}
//	if (inVertexId) {
//		if ((inVertexIdC = (*env)->GetLongArrayElements(env, inVertexId, NULL)) == NULL) {
//			goto fail;
//		}
//	}

	rc = getNextEdgefromVertexAllLabels((MDB_cursor *) (long) cursor, direction, fromVertexId, labelIdResultC, edgeIdResultC, outVertexIdC,
			inVertexIdC);

	fail: if (labelIdResult && labelIdResultC) {
		(*env)->ReleasePrimitiveArrayCritical(env, labelIdResult, labelIdResultC, 0);
	}
	if (edgeIdResult && edgeIdResultC) {
		(*env)->ReleasePrimitiveArrayCritical(env, edgeIdResult, edgeIdResultC, 0);
	}
	if (outVertexId && outVertexIdC) {
		(*env)->ReleasePrimitiveArrayCritical(env, outVertexId, outVertexIdC, 0);
	}
	if (inVertexId && inVertexIdC) {
		(*env)->ReleasePrimitiveArrayCritical(env, inVertexId, inVertexIdC, 0);
	}

//	if (labelIdResult && labelIdResultC) {
//		(*env)->ReleaseIntArrayElements(env, labelIdResult, labelIdResultC, 0);
//	}
//	if (edgeIdResult && edgeIdResultC) {
//		(*env)->ReleaseLongArrayElements(env, edgeIdResult, edgeIdResultC, 0);
//	}
//	if (outVertexId && outVertexIdC) {
//		(*env)->ReleaseLongArrayElements(env, outVertexId, outVertexIdC, 0);
//	}
//	if (inVertexId && inVertexIdC) {
//		(*env)->ReleaseLongArrayElements(env, inVertexId, inVertexIdC, 0);
//	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_edge_from_vertex_all_labels
 * Signature: (JIJ[I[J[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1edge_1from_1vertex_1all_1labels(JNIEnv *env, jclass that,
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

	rc = getCurrentEdgefromVertexAllLabels((MDB_cursor *) (long) cursor, direction, fromVertexId, labelIdResultC, edgeIdResultC,
			outVertexIdC, inVertexIdC);

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

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_delete_index
 * Signature: (JJIZI)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1delete_1index(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn,
		jint propertyKeyId, jboolean vertex, jint propertyKeyEnum) {

	jint rc = 0;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	MDB_txn * mdbTxn = (MDB_txn *) (long) txn;
	switch (propertyKeyEnum) {
	case BOOLEAN:
		rc = deleteBooleanIndex(glmdb_env, mdbTxn, propertyKeyId, vertex);
		break;
	case BYTE:
		rc = deleteByteIndex(glmdb_env, mdbTxn, propertyKeyId, vertex);
		break;
	case SHORT:
		rc = deleteShortIndex(glmdb_env, mdbTxn, propertyKeyId, vertex);
		break;
	case INT:
		rc = deleteIntIndex(glmdb_env, mdbTxn, propertyKeyId, vertex);
		break;
	case LONG:
		rc = deleteLongIndex(glmdb_env, mdbTxn, propertyKeyId, vertex);
		break;
	case FLOAT:
		rc = deleteFloatIndex(glmdb_env, mdbTxn, propertyKeyId, vertex);
		break;
	case DOUBLE:
		rc = deleteDoubleIndex(glmdb_env, mdbTxn, propertyKeyId, vertex);
		break;
	case CHAR:
		rc = deleteCharIndex(glmdb_env, mdbTxn, propertyKeyId, vertex);
		break;
	case STRING:
		rc = deleteStringIndex(glmdb_env, mdbTxn, propertyKeyId, vertex);
		break;
	default:
		rc = GLMDB_INVALID_SEQUENCE;
		break;
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_string_value
 * Signature: (J[JILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1string_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jstring value) {

	jint rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;
	jint propertyValueLength = (*env)->GetStringUTFLength(env, value);
	char propertyValue[propertyValueLength];
	if (value) {
		(*env)->GetStringUTFRegion(env, value, 0, propertyValueLength, propertyValue);
		if (propertyValue == NULL) {
			goto fail;
		}
	}

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (propertyValueLength == (int) data.mv_size) {

				int compare = strncmp(propertyValue, data.mv_data, propertyValueLength);
				if (compare == 0) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_string_value
 * Signature: (J[JILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1string_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jstring value) {

	jint rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;
	jint propertyValueLength = (*env)->GetStringUTFLength(env, value);
	char propertyValue[propertyValueLength];
	if (value) {
		(*env)->GetStringUTFRegion(env, value, 0, propertyValueLength, propertyValue);
		if (propertyValue == NULL) {
			goto fail;
		}
	}

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (propertyValueLength == (int) data.mv_size) {

				int compare = strncmp(propertyValue, data.mv_data, propertyValueLength);
				if (compare == 0) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_int_value
 * Signature: (J[JII)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1int_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jint value) {

	jint rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((int *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_int_value
 * Signature: (J[JII)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1int_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jint value) {

	jint rc = 0;
	MDB_val key, data;
	jlong *vertexIdResultC = NULL;

	if (vertexIdResult) {
		if ((vertexIdResultC = (*env)->GetLongArrayElements(env, vertexIdResult, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY && vertexDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((int *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_string_value
 * Signature: (J[J[I[J[JILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1string_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jstring value) {

	jint rc = 0;
	jlong *edgeIdResultC = NULL;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;
	jint propertyValueLength = (*env)->GetStringUTFLength(env, value);
	char propertyValue[propertyValueLength];
	if (value) {
		(*env)->GetStringUTFRegion(env, value, 0, propertyValueLength, propertyValue);
		if (propertyValue == NULL) {
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
	if (labelId) {
		if ((labelIdC = (*env)->GetIntArrayElements(env, labelId, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (propertyValueLength == (int) data.mv_size) {
				if (strncmp(propertyValue, data.mv_data, propertyValueLength) == 0) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_string_value
 * Signature: (J[J[I[J[JILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1string_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jstring value) {

	jint rc = 0;
	jlong *edgeIdResultC = NULL;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;
	jint propertyValueLength = (*env)->GetStringUTFLength(env, value);
	char propertyValue[propertyValueLength];
	if (value) {
		(*env)->GetStringUTFRegion(env, value, 0, propertyValueLength, propertyValue);
		if (propertyValue == NULL) {
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
	if (labelId) {
		if ((labelIdC = (*env)->GetIntArrayElements(env, labelId, NULL)) == NULL) {
			goto fail;
		}
	}

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (propertyValueLength == (int) data.mv_size) {
				if (strncmp(propertyValue, data.mv_data, propertyValueLength) == 0) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_edge_for_key_int_value
 * Signature: (J[J[I[J[JII)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1int_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jint value) {

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

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {
			rc = GLMDB_DB_CORRUPT;
		}

	}
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((int *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_edge_for_key_int_value
 * Signature: (J[J[I[J[JII)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1int_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
		jint value) {

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

	unsigned char foundPropertyKeyAndValue = 1;
	MDB_val key, data;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));

		if (edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY && edgeDbId.propertykeyId == (int) propertyKeyId) {

			if (value == *((int *) data.mv_data)) {
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
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_string_index_db
 * Signature: (JJJILjava/lang/String;[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1string_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong vertexId, jint propertyKey, jstring value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;
	jint propertyValueLength = (*env)->GetStringUTFLength(env, value);
	char propertyValue[propertyValueLength];
	if (value) {
		(*env)->GetStringUTFRegion(env, value, 0, propertyValueLength, propertyValue);
		if (propertyValue == NULL) {
			goto fail;
		}
	}

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexStringIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueStringIndex(mdbCursor, vertexId, propertyKey, propertyValueLength, propertyValue);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_int_index_db
 * Signature: (JJJII[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1int_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong vertexId, jint propertyKey, jint value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexIntIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueIntIndex(mdbCursor, vertexId, propertyKey, value);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_long_index_db
 * Signature: (JJJIJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1long_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong vertexId, jint propertyKey, jlong value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexLongIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueLongIndex(mdbCursor, vertexId, propertyKey, value);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_float_index_db
 * Signature: (JJJIF[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1float_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong vertexId, jint propertyKey, jfloat value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexFloatIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueFloatIndex(mdbCursor, vertexId, propertyKey, value);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_double_index_db
 * Signature: (JJJID[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1double_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong vertexId, jint propertyKey, jdouble value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexDoubleIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueDoubleIndex(mdbCursor, vertexId, propertyKey, value);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_boolean_index_db
 * Signature: (JJJIZ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1boolean_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong vertexId, jint propertyKey, jboolean value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexBooleanIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueBooleanIndex(mdbCursor, vertexId, propertyKey, value);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_short_index_db
 * Signature: (JJJIS[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1short_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong vertexId, jint propertyKey, jshort value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexShortIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueShortIndex(mdbCursor, vertexId, propertyKey, value);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_char_index_db
 * Signature: (JJJIC[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1char_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong vertexId, jint propertyKey, jchar value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexCharIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueCharIndex(mdbCursor, vertexId, propertyKey, value);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_byte_index_db
 * Signature: (JJJIB[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1byte_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong vertexId, jint propertyKey, jbyte value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->vertexByteIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueByteIndex(mdbCursor, vertexId, propertyKey, value);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_vertex_from_vertex_string_index_db
 * Signature: (J[JILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1string_1index_1db(JNIEnv *env,
		jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId, jstring value) {

	jint rc = 0;
	jlong *vertexIdC = NULL;

	jint propertyValueLength = (*env)->GetStringUTFLength(env, value);
	char propertyValue[propertyValueLength];
	if (value) {
		(*env)->GetStringUTFRegion(env, value, 0, propertyValueLength, propertyValue);
		if (propertyValue == NULL) {
			goto fail;
		}
	}

	if (vertexIdArray) {
		if ((vertexIdC = (*env)->GetLongArrayElements(env, vertexIdArray, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getCurrentElementFromStringIndexDb((MDB_cursor *) (long) cursor, vertexIdC, propertyKeyId, propertyValueLength, propertyValue);

	fail: if (vertexIdArray && vertexIdC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdArray, vertexIdC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_edge_string_index_db
 * Signature: (JJJILjava/lang/String;[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1edge_1string_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong edgeId, jint propertyKey, jstring value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;
	jint propertyValueLength = (*env)->GetStringUTFLength(env, value);
	char propertyValue[propertyValueLength];
	if (value) {
		(*env)->GetStringUTFRegion(env, value, 0, propertyValueLength, propertyValue);
		if (propertyValue == NULL) {
			goto fail;
		}
	}

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeStringIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueStringIndex(mdbCursor, edgeId, propertyKey, propertyValueLength, propertyValue);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_vertex_from_vertex_int_index_db
 * Signature: (J[JII)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1int_1index_1db(JNIEnv *env,
		jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId, jint value) {

	jint rc = 0;
	jlong *vertexIdC = NULL;

	if (vertexIdArray) {
		if ((vertexIdC = (*env)->GetLongArrayElements(env, vertexIdArray, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getCurrentElementFromIntIndexDb((MDB_cursor *) (long) cursor, vertexIdC, propertyKeyId, value);

	fail: if (vertexIdArray && vertexIdC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdArray, vertexIdC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_vertex_from_vertex_long_index_db
 * Signature: (J[JIJ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1long_1index_1db(JNIEnv *env,
		jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId, jlong value) {

	jint rc = 0;
	jlong *vertexIdC = NULL;

	if (vertexIdArray) {
		if ((vertexIdC = (*env)->GetLongArrayElements(env, vertexIdArray, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getCurrentElementFromLongIndexDb((MDB_cursor *) (long) cursor, vertexIdC, propertyKeyId, value);

	fail: if (vertexIdArray && vertexIdC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdArray, vertexIdC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_vertex_from_vertex_float_index_db
 * Signature: (J[JIF)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1float_1index_1db(JNIEnv *env,
		jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId, jfloat value) {

	jint rc = 0;
	jlong *vertexIdC = NULL;

	if (vertexIdArray) {
		if ((vertexIdC = (*env)->GetLongArrayElements(env, vertexIdArray, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getCurrentElementFromFloatIndexDb((MDB_cursor *) (long) cursor, vertexIdC, propertyKeyId, value);

	fail: if (vertexIdArray && vertexIdC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdArray, vertexIdC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_vertex_from_vertex_double_index_db
 * Signature: (J[JID)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1double_1index_1db(JNIEnv *env,
		jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId, jdouble value) {

	jint rc = 0;
	jlong *vertexIdC = NULL;

	if (vertexIdArray) {
		if ((vertexIdC = (*env)->GetLongArrayElements(env, vertexIdArray, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getCurrentElementFromDoubleIndexDb((MDB_cursor *) (long) cursor, vertexIdC, propertyKeyId, value);

	fail: if (vertexIdArray && vertexIdC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdArray, vertexIdC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_vertex_from_vertex_boolean_index_db
 * Signature: (J[JIZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1boolean_1index_1db(JNIEnv *env,
		jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId, jboolean value) {

	jint rc = 0;
	jlong *vertexIdC = NULL;

	if (vertexIdArray) {
		if ((vertexIdC = (*env)->GetLongArrayElements(env, vertexIdArray, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getCurrentElementFromBooleanIndexDb((MDB_cursor *) (long) cursor, vertexIdC, propertyKeyId, value);

	fail: if (vertexIdArray && vertexIdC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdArray, vertexIdC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_vertex_from_vertex_short_index_db
 * Signature: (J[JIS)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1short_1index_1db(JNIEnv *env,
		jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId, jshort value) {

	jint rc = 0;
	jlong *vertexIdC = NULL;

	if (vertexIdArray) {
		if ((vertexIdC = (*env)->GetLongArrayElements(env, vertexIdArray, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getCurrentElementFromShortIndexDb((MDB_cursor *) (long) cursor, vertexIdC, propertyKeyId, value);

	fail: if (vertexIdArray && vertexIdC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdArray, vertexIdC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_vertex_from_vertex_char_index_db
 * Signature: (J[JIC)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1char_1index_1db(JNIEnv *env,
		jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId, jchar value) {

	jint rc = 0;
	jlong *vertexIdC = NULL;

	if (vertexIdArray) {
		if ((vertexIdC = (*env)->GetLongArrayElements(env, vertexIdArray, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getCurrentElementFromCharIndexDb((MDB_cursor *) (long) cursor, vertexIdC, propertyKeyId, value);

	fail: if (vertexIdArray && vertexIdC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdArray, vertexIdC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_vertex_from_vertex_byte_index_db
 * Signature: (J[JIB)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1byte_1index_1db(JNIEnv *env,
		jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId, jbyte value) {

	jint rc = 0;
	jlong *vertexIdC = NULL;

	if (vertexIdArray) {
		if ((vertexIdC = (*env)->GetLongArrayElements(env, vertexIdArray, NULL)) == NULL) {
			goto fail;
		}
	}

	rc = getCurrentElementFromByteIndexDb((MDB_cursor *) (long) cursor, vertexIdC, propertyKeyId, value);

	fail: if (vertexIdArray && vertexIdC) {
		(*env)->ReleaseLongArrayElements(env, vertexIdArray, vertexIdC, 0);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_edge_int_index_db
 * Signature: (JJJII[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1edge_1int_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong edgeId, jint key, jint value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeIntIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueIntIndex(mdbCursor, edgeId, key, value);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_edge_from_edge_int_index_db
 * Signature: (JJII[J[Ljava/lang/String;[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1edge_1from_1edge_1int_1index_1db(JNIEnv *env,
		jclass that, jlong edgeIntIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jint value, jlongArray edgeIdArray,
		jobjectArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

	jint rc = 0;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;
	jlong *edgeIdC = NULL;

	if (edgeIdArray) {
		if ((edgeIdC = (*env)->GetLongArrayElements(env, edgeIdArray, NULL)) == NULL) {
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

	rc = getCurrentElementFromIntIndexDb((MDB_cursor *) (long) edgeIntIndexDbCursor, edgeIdC, propertyKeyId, value);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		*edgeIdC = edgeDbId.edgeId;
		EdgeData edgeData = *((EdgeData *) (data.mv_data));
		*outVertexIdC = edgeData.vertexOutId;
		*inVertexIdC = edgeData.vertexInId;
		*labelIdC = edgeData.labelId;
	}

	fail: if (edgeIdArray && edgeIdC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdArray, edgeIdC, 0);
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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_edge_long_index_db
 * Signature: (JJJIJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1edge_1long_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong edgeId, jint key, jlong value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeLongIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueLongIndex(mdbCursor, edgeId, key, value);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_edge_from_edge_long_index_db
 * Signature: (JJIJ[J[Ljava/lang/String;[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1edge_1from_1edge_1long_1index_1db(JNIEnv *env,
		jclass that, jlong edgeLongIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jlong value, jlongArray edgeIdArray,
		jobjectArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

	jint rc = 0;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;
	jlong *edgeIdC = NULL;

	if (edgeIdArray) {
		if ((edgeIdC = (*env)->GetLongArrayElements(env, edgeIdArray, NULL)) == NULL) {
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

	rc = getCurrentElementFromLongIndexDb((MDB_cursor *) (long) edgeLongIndexDbCursor, edgeIdC, propertyKeyId, value);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		*edgeIdC = edgeDbId.edgeId;
		EdgeData edgeData = *((EdgeData *) (data.mv_data));
		*outVertexIdC = edgeData.vertexOutId;
		*inVertexIdC = edgeData.vertexInId;
		*labelIdC = edgeData.labelId;
	}

	fail: if (edgeIdArray && edgeIdC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdArray, edgeIdC, 0);
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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_edge_float_index_db
 * Signature: (JJJIF[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1edge_1float_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong edgeId, jint key, jfloat value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeFloatIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueFloatIndex(mdbCursor, edgeId, key, value);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_edge_from_edge_float_index_db
 * Signature: (JJIF[J[Ljava/lang/String;[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1edge_1from_1edge_1float_1index_1db(JNIEnv *env,
		jclass that, jlong edgeFloatIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jfloat value, jlongArray edgeIdArray,
		jobjectArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

	jint rc = 0;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;
	jlong *edgeIdC = NULL;

	if (edgeIdArray) {
		if ((edgeIdC = (*env)->GetLongArrayElements(env, edgeIdArray, NULL)) == NULL) {
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

	rc = getCurrentElementFromFloatIndexDb((MDB_cursor *) (long) edgeFloatIndexDbCursor, edgeIdC, propertyKeyId, value);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		*edgeIdC = edgeDbId.edgeId;
		EdgeData edgeData = *((EdgeData *) (data.mv_data));
		*outVertexIdC = edgeData.vertexOutId;
		*inVertexIdC = edgeData.vertexInId;
		*labelIdC = edgeData.labelId;
	}

	fail: if (edgeIdArray && edgeIdC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdArray, edgeIdC, 0);
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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_edge_double_index_db
 * Signature: (JJJID[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1edge_1double_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong edgeId, jint key, jdouble value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeDoubleIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueDoubleIndex(mdbCursor, edgeId, key, value);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_edge_from_edge_double_index_db
 * Signature: (JJID[J[Ljava/lang/String;[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1edge_1from_1edge_1double_1index_1db(JNIEnv *env,
		jclass that, jlong edgeDoubleIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jdouble value, jlongArray edgeIdArray,
		jobjectArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

	jint rc = 0;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;
	jlong *edgeIdC = NULL;

	if (edgeIdArray) {
		if ((edgeIdC = (*env)->GetLongArrayElements(env, edgeIdArray, NULL)) == NULL) {
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

	rc = getCurrentElementFromDoubleIndexDb((MDB_cursor *) (long) edgeDoubleIndexDbCursor, edgeIdC, propertyKeyId, value);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		*edgeIdC = edgeDbId.edgeId;
		EdgeData edgeData = *((EdgeData *) (data.mv_data));
		*outVertexIdC = edgeData.vertexOutId;
		*inVertexIdC = edgeData.vertexInId;
		*labelIdC = edgeData.labelId;
	}

	fail: if (edgeIdArray && edgeIdC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdArray, edgeIdC, 0);
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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_edge_boolean_index_db
 * Signature: (JJJIZ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1edge_1boolean_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong edgeId, jint key, jboolean value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeBooleanIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueBooleanIndex(mdbCursor, edgeId, key, value);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_edge_from_edge_boolean_index_db
 * Signature: (JJIZ[J[Ljava/lang/String;[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1edge_1from_1edge_1boolean_1index_1db(JNIEnv *env,
		jclass that, jlong edgeBooleanIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jboolean value, jlongArray edgeIdArray,
		jobjectArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

	jint rc = 0;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;
	jlong *edgeIdC = NULL;

	if (edgeIdArray) {
		if ((edgeIdC = (*env)->GetLongArrayElements(env, edgeIdArray, NULL)) == NULL) {
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

	rc = getCurrentElementFromBooleanIndexDb((MDB_cursor *) (long) edgeBooleanIndexDbCursor, edgeIdC, propertyKeyId, value);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		*edgeIdC = edgeDbId.edgeId;
		EdgeData edgeData = *((EdgeData *) (data.mv_data));
		*outVertexIdC = edgeData.vertexOutId;
		*inVertexIdC = edgeData.vertexInId;
		*labelIdC = edgeData.labelId;
	}

	fail: if (edgeIdArray && edgeIdC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdArray, edgeIdC, 0);
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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_edge_short_index_db
 * Signature: (JJJIS[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1edge_1short_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong edgeId, jint key, jshort value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeShortIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueShortIndex(mdbCursor, edgeId, key, value);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_edge_from_edge_short_index_db
 * Signature: (JJIS[J[Ljava/lang/String;[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1edge_1from_1edge_1short_1index_1db(JNIEnv *env,
		jclass that, jlong edgeShortIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jshort value, jlongArray edgeIdArray,
		jobjectArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

	jint rc = 0;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;
	jlong *edgeIdC = NULL;

	if (edgeIdArray) {
		if ((edgeIdC = (*env)->GetLongArrayElements(env, edgeIdArray, NULL)) == NULL) {
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

	rc = getCurrentElementFromShortIndexDb((MDB_cursor *) (long) edgeShortIndexDbCursor, edgeIdC, propertyKeyId, value);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		*edgeIdC = edgeDbId.edgeId;
		EdgeData edgeData = *((EdgeData *) (data.mv_data));
		*outVertexIdC = edgeData.vertexOutId;
		*inVertexIdC = edgeData.vertexInId;
		*labelIdC = edgeData.labelId;
	}

	fail: if (edgeIdArray && edgeIdC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdArray, edgeIdC, 0);
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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_edge_char_index_db
 * Signature: (JJJIC[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1edge_1char_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong edgeId, jint key, jchar value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeCharIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueCharIndex(mdbCursor, edgeId, key, value);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_edge_from_edge_char_index_db
 * Signature: (JJIC[J[Ljava/lang/String;[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1edge_1from_1edge_1char_1index_1db(JNIEnv *env,
		jclass that, jlong edgeCharIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jchar value, jlongArray edgeIdArray,
		jobjectArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

	jint rc = 0;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;
	jlong *edgeIdC = NULL;

	if (edgeIdArray) {
		if ((edgeIdC = (*env)->GetLongArrayElements(env, edgeIdArray, NULL)) == NULL) {
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

	rc = getCurrentElementFromCharIndexDb((MDB_cursor *) (long) edgeCharIndexDbCursor, edgeIdC, propertyKeyId, value);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		*edgeIdC = edgeDbId.edgeId;
		EdgeData edgeData = *((EdgeData *) (data.mv_data));
		*outVertexIdC = edgeData.vertexOutId;
		*inVertexIdC = edgeData.vertexInId;
		*labelIdC = edgeData.labelId;
	}

	fail: if (edgeIdArray && edgeIdC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdArray, edgeIdC, 0);
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
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_cursor_open_and_position_on_key_value_edge_byte_index_db
 * Signature: (JJJIB[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1edge_1byte_1index_1db(
		JNIEnv *env, jclass that, jlong txn, jlong glmdbEnv, jlong edgeId, jint key, jbyte value, jlongArray cursorArray) {

	jint rc = 0;
	MDB_cursor *mdbCursor;
	GLMDB_env * glmdb_env = (GLMDB_env *) (long) glmdbEnv;
	jlong *cursor = NULL;

	if (cursorArray) {
		if ((cursor = (*env)->GetLongArrayElements(env, cursorArray, NULL)) == NULL) {
			goto fail;
		}
	}
	rc = (jint) mdb_cursor_open((MDB_txn *) (long) txn, glmdb_env->edgeByteIndexDb, (MDB_cursor **) cursor);

	mdbCursor = (MDB_cursor *) *cursor;

	if (rc != 0) {
		goto fail;
	}

	rc = placeCursorOnKeyValueByteIndex(mdbCursor, edgeId, key, value);

	fail: if (cursorArray && cursor) {
		(*env)->ReleaseLongArrayElements(env, cursorArray, cursor, 0);
	}
	if (rc == MDB_NOTFOUND) {
		mdb_cursor_close(mdbCursor);
	}
	return rc;

}

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_current_edge_from_edge_byte_index_db
 * Signature: (JJIB[J[Ljava/lang/String;[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1edge_1from_1edge_1byte_1index_1db(JNIEnv *env,
		jclass that, jlong edgeByteIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jbyte value, jlongArray edgeIdArray,
		jobjectArray labelId, jlongArray outVertexId, jlongArray inVertexId) {

	jint rc = 0;
	jlong *outVertexIdC = NULL;
	jlong *inVertexIdC = NULL;
	jint *labelIdC = NULL;
	jlong *edgeIdC = NULL;

	if (edgeIdArray) {
		if ((edgeIdC = (*env)->GetLongArrayElements(env, edgeIdArray, NULL)) == NULL) {
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

	rc = getCurrentElementFromByteIndexDb((MDB_cursor *) (long) edgeByteIndexDbCursor, edgeIdC, propertyKeyId, value);

	if (rc == 0) {
		MDB_val key, data;
		rc = getEdge((MDB_cursor *) (long) edgeDbCursor, *edgeIdC, &key, &data);
		if (rc != 0) {
			goto fail;
		}

		EdgeDbId edgeDbId = *((EdgeDbId *) (key.mv_data));
		*edgeIdC = edgeDbId.edgeId;
		EdgeData edgeData = *((EdgeData *) (data.mv_data));
		*outVertexIdC = edgeData.vertexOutId;
		*inVertexIdC = edgeData.vertexInId;
		*labelIdC = edgeData.labelId;
	}

	fail: if (edgeIdArray && edgeIdC) {
		(*env)->ReleaseLongArrayElements(env, edgeIdArray, edgeIdC, 0);
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

	GLMDB_env *glmdbEnv;
	glmdbEnv = calloc(sizeof(GLMDB_env), 1);

	MDB_env *env;
	MDB_dbi configDb;
	MDB_dbi vertexDb;
	MDB_dbi edgeDb;
	MDB_dbi vertexPropertyKeyDb;
	MDB_dbi vertexPropertyKeyInverseDb;
	MDB_dbi vertexBooleanIndexDb;
	MDB_dbi vertexByteIndexDb;
	MDB_dbi vertexShortIndexDb;
	MDB_dbi vertexIntIndexDb;
	MDB_dbi vertexLongIndexDb;
	MDB_dbi vertexFloatIndexDb;
	MDB_dbi vertexDoubleIndexDb;
	MDB_dbi vertexCharIndexDb;
	MDB_dbi vertexStringIndexDb;

	MDB_dbi edgePropertyKeyDb;
	MDB_dbi edgePropertyKeyInverseDb;
	MDB_dbi edgeBooleanIndexDb;
	MDB_dbi edgeByteIndexDb;
	MDB_dbi edgeShortIndexDb;
	MDB_dbi edgeIntIndexDb;
	MDB_dbi edgeLongIndexDb;
	MDB_dbi edgeFloatIndexDb;
	MDB_dbi edgeDoubleIndexDb;
	MDB_dbi edgeCharIndexDb;
	MDB_dbi edgeStringIndexDb;

	MDB_dbi labelDb;

	rc = mdb_env_create(&env);
	if (rc != 0) {
		return rc;
	}

	rc = mdb_env_set_maxreaders(env, 1100);
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
	rc = mdb_env_open(env, path, MDB_NOSYNC, 0664);
//	rc = mdb_env_open(env, path, 0, 0664);
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

	//Create the vertex property key inverse db
	rc = createDb(env, "vertexPropertyKeyInverseDb", MDB_CREATE | MDB_INTEGERKEY, &vertexPropertyKeyInverseDb, NULL);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->vertexPropertyKeyInverseDb = vertexPropertyKeyInverseDb;

	//Create the edge property key db
	rc = createDb(env, "edgePropertyKeyDb", MDB_CREATE, &edgePropertyKeyDb, comparePropertyKeyDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->edgePropertyKeyDb = edgePropertyKeyDb;

	//Create the edge property key inverse db
	rc = createDb(env, "edgePropertyKeyInverseDb", MDB_CREATE | MDB_INTEGERKEY, &edgePropertyKeyInverseDb, NULL);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->edgePropertyKeyInverseDb = edgePropertyKeyInverseDb;

	//Create the label db
	rc = createDb(env, "labelDb", MDB_CREATE, &labelDb, NULL);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->labelDb = labelDb;

	//Create the Boolean index db
	rc = createDb(env, "vertexBooleanIndexDb", MDB_CREATE, &vertexBooleanIndexDb, compareBooleanIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->vertexBooleanIndexDb = vertexBooleanIndexDb;

	//Create the Byte index db
	rc = createDb(env, "vertexByteIndexDb", MDB_CREATE, &vertexByteIndexDb, compareByteIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->vertexByteIndexDb = vertexByteIndexDb;

	//Create the Short index db
	rc = createDb(env, "vertexShortIndexDb", MDB_CREATE, &vertexShortIndexDb, compareShortIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->vertexShortIndexDb = vertexShortIndexDb;

	//Create the Int index db
	rc = createDb(env, "vertexIntIndexDb", MDB_CREATE, &vertexIntIndexDb, compareIntIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->vertexIntIndexDb = vertexIntIndexDb;

	//Create the Long index db
	rc = createDb(env, "vertexLongIndexDb", MDB_CREATE, &vertexLongIndexDb, compareLongIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->vertexLongIndexDb = vertexLongIndexDb;

	//Create the Float index db
	rc = createDb(env, "vertexFloatIndexDb", MDB_CREATE, &vertexFloatIndexDb, compareFloatIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->vertexFloatIndexDb = vertexFloatIndexDb;

	//Create the Double index db
	rc = createDb(env, "vertexDoubleIndexDb", MDB_CREATE, &vertexDoubleIndexDb, compareDoubleIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->vertexDoubleIndexDb = vertexDoubleIndexDb;

	//Create the Char index db
	rc = createDb(env, "vertexCharIndexDb", MDB_CREATE, &vertexCharIndexDb, compareCharIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->vertexCharIndexDb = vertexCharIndexDb;

	//Create the String index db
	rc = createDb(env, "vertexStringIndexDb", MDB_CREATE, &vertexStringIndexDb, compareStringIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->vertexStringIndexDb = vertexStringIndexDb;

	//Create the Boolean index db
	rc = createDb(env, "edgeBooleanIndexDb", MDB_CREATE, &edgeBooleanIndexDb, compareBooleanIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->edgeBooleanIndexDb = edgeBooleanIndexDb;

	//Create the Byte index db
	rc = createDb(env, "edgeByteIndexDb", MDB_CREATE, &edgeByteIndexDb, compareByteIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->edgeByteIndexDb = edgeByteIndexDb;

	//Create the Short index db
	rc = createDb(env, "edgeShortIndexDb", MDB_CREATE, &edgeShortIndexDb, compareShortIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->edgeShortIndexDb = edgeShortIndexDb;

	//Create the Int index db
	rc = createDb(env, "edgeIntIndexDb", MDB_CREATE, &edgeIntIndexDb, compareIntIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->edgeIntIndexDb = edgeIntIndexDb;

	//Create the Long index db
	rc = createDb(env, "edgeLongIndexDb", MDB_CREATE, &edgeLongIndexDb, compareLongIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->edgeLongIndexDb = edgeLongIndexDb;

	//Create the Float index db
	rc = createDb(env, "edgeFloatIndexDb", MDB_CREATE, &edgeFloatIndexDb, compareFloatIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->edgeFloatIndexDb = edgeFloatIndexDb;

	//Create the Double index db
	rc = createDb(env, "edgeDoubleIndexDb", MDB_CREATE, &edgeDoubleIndexDb, compareDoubleIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->edgeDoubleIndexDb = edgeDoubleIndexDb;

	//Create the Char index db
	rc = createDb(env, "edgeCharIndexDb", MDB_CREATE, &edgeCharIndexDb, compareCharIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->edgeCharIndexDb = edgeCharIndexDb;

	//Create the String index db
	rc = createDb(env, "edgeStringIndexDb", MDB_CREATE, &edgeStringIndexDb, compareStringIndexDbId);
	if (rc != 0) {
		return rc;
	}
	glmdbEnv->edgeStringIndexDb = edgeStringIndexDb;

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
	MDB_dbi vertexPropertyKeyInverseDb = genv->vertexPropertyKeyInverseDb;
	MDB_dbi edgePropertyKeyDb = genv->edgePropertyKeyDb;
	MDB_dbi edgePropertyKeyInverseDb = genv->edgePropertyKeyInverseDb;
	MDB_dbi labelDb = genv->labelDb;

	MDB_dbi vertexBooleanIndexDb = genv->vertexBooleanIndexDb;
	MDB_dbi vertexByteIndexDb = genv->vertexByteIndexDb;
	MDB_dbi vertexShortIndexDb = genv->vertexShortIndexDb;
	MDB_dbi vertexIntIndexDb = genv->vertexIntIndexDb;
	MDB_dbi vertexLongIndexDb = genv->vertexLongIndexDb;
	MDB_dbi vertexFloatIndexDb = genv->vertexFloatIndexDb;
	MDB_dbi vertexDoubleIndexDb = genv->vertexDoubleIndexDb;
	MDB_dbi vertexCharIndexDb = genv->vertexCharIndexDb;
	MDB_dbi vertexStringIndexDb = genv->vertexStringIndexDb;

	MDB_dbi edgeBooleanIndexDb = genv->edgeBooleanIndexDb;
	MDB_dbi edgeByteIndexDb = genv->edgeByteIndexDb;
	MDB_dbi edgeShortIndexDb = genv->edgeShortIndexDb;
	MDB_dbi edgeIntIndexDb = genv->edgeIntIndexDb;
	MDB_dbi edgeLongIndexDb = genv->edgeLongIndexDb;
	MDB_dbi edgeFloatIndexDb = genv->edgeFloatIndexDb;
	MDB_dbi edgeDoubleIndexDb = genv->edgeDoubleIndexDb;
	MDB_dbi edgeCharIndexDb = genv->edgeCharIndexDb;
	MDB_dbi edgeStringIndexDb = genv->edgeStringIndexDb;

	mdb_close(env, configDb);
	mdb_close(env, vertexDb);
	mdb_close(env, edgeDb);
	mdb_close(env, vertexPropertyKeyDb);
	mdb_close(env, vertexPropertyKeyInverseDb);
	mdb_close(env, edgePropertyKeyDb);
	mdb_close(env, edgePropertyKeyInverseDb);
	mdb_close(env, labelDb);

	mdb_close(env, vertexBooleanIndexDb);
	mdb_close(env, vertexByteIndexDb);
	mdb_close(env, vertexShortIndexDb);
	mdb_close(env, vertexIntIndexDb);
	mdb_close(env, vertexLongIndexDb);
	mdb_close(env, vertexFloatIndexDb);
	mdb_close(env, vertexDoubleIndexDb);
	mdb_close(env, vertexCharIndexDb);
	mdb_close(env, vertexStringIndexDb);

	mdb_close(env, edgeBooleanIndexDb);
	mdb_close(env, edgeByteIndexDb);
	mdb_close(env, edgeShortIndexDb);
	mdb_close(env, edgeIntIndexDb);
	mdb_close(env, edgeLongIndexDb);
	mdb_close(env, edgeFloatIndexDb);
	mdb_close(env, edgeDoubleIndexDb);
	mdb_close(env, edgeCharIndexDb);
	mdb_close(env, edgeStringIndexDb);

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

int getCurrentEdgefromVertex(MDB_cursor *cursor, jint direction, jint labelId, jlong fromVertexId, jlong *edgeIdResultC,
		jlong *outVertexIdC, jlong *inVertexIdC) {

	int rc = 0;
	VertexDbId id;
	initVertexDbId(&id);
	MDB_val key, data;
	key.mv_size = sizeof(VertexDbId);
	key.mv_data = &id;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_GET_CURRENT);
	if (rc != 0) {
		goto fail;
	}
	unsigned char foundEdge = 0;
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
			foundEdge = 1;
			break;
		case 1:
			if (vertexDbId.coreOrPropertyEnum != INLABEL) {
				rc = GLMDB_END_OF_EDGES;
				goto fail;
			}
			*outVertexIdC = *((jlong *) (data.mv_data));
			*inVertexIdC = vertexDbId.vertexId;
			foundEdge = 1;
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
			foundEdge = 1;
			break;
		default:
			rc = GLMDB_UNDEFINED_DIRECTION;
			goto fail;
		}
		*edgeIdResultC = vertexDbId.edgeId;
	} else {
		rc = GLMDB_END_OF_EDGES;
	}

	if (foundEdge == 0) {
		rc = getNextEdgefromVertex(cursor, direction, labelId, fromVertexId, edgeIdResultC, outVertexIdC, inVertexIdC);
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

//	printf("getNextEdgefromVertexAllLabels start\n");
	int rc = 0;
	VertexDbId id;
	initVertexDbId(&id);
	MDB_val key, data;
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

//		printVertexRecord(key, data);

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
			goto fail;
		}
	}
	fail:
//	printf("getNextEdgefromVertexAllLabels end\n");
	return rc;
}

int getCurrentEdgefromVertexAllLabels(MDB_cursor *cursor, jint direction, jlong fromVertexId, jint *labelIdResultC, jlong *edgeIdResultC,
		jlong *outVertexIdC, jlong *inVertexIdC) {

	int rc = 0;
	VertexDbId id;
	initVertexDbId(&id);
	MDB_val key, data;

	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_GET_CURRENT);

	unsigned char foundEdge = 0;
	VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
	if (fromVertexId == vertexDbId.vertexId) {

		if (direction == 0) {
			if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
				*outVertexIdC = vertexDbId.vertexId;
				*inVertexIdC = *((jlong *) (data.mv_data));
				*labelIdResultC = vertexDbId.labelId;
				*edgeIdResultC = vertexDbId.edgeId;
				foundEdge = 1;
			}
		} else if (direction == 1) {
			if (vertexDbId.coreOrPropertyEnum == INLABEL) {
				*outVertexIdC = *((jlong *) (data.mv_data));
				*inVertexIdC = vertexDbId.vertexId;
				*labelIdResultC = vertexDbId.labelId;
				*edgeIdResultC = vertexDbId.edgeId;
				foundEdge = 1;
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
			foundEdge = 1;
		}
	} else {
		rc = GLMDB_END_OF_EDGES;
		goto fail;
	}

	if (foundEdge == 0) {
		rc = getNextEdgefromVertexAllLabels(cursor, direction, fromVertexId, labelIdResultC, edgeIdResultC, outVertexIdC, inVertexIdC);
	}

	fail: return rc;
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

int comparePropertyKeyDbId(const MDB_val *key1, const MDB_val *key2) {
	int propertyKey1Size = (size_t) key1->mv_size;
	int propertyKey2Size = (size_t) key2->mv_size;

	if (propertyKey1Size == propertyKey2Size) {
		char * propertyKeyId1 = (char *) (key1->mv_data);
		char * propertyKeyId2 = (char *) (key2->mv_data);
		int compare = strncmp(propertyKeyId1, propertyKeyId2, propertyKey1Size);
		return compare;
	} else {
		return (propertyKey1Size > propertyKey2Size) - (propertyKey1Size < propertyKey2Size);
	}

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
	char *propertyKey = (char *) (key.mv_data);
	int propertyKeySize = ((size_t) key.mv_size);
	PropertyKeyDataStruct propertyKeyDataStruct = (*((PropertyKeyDataStruct *) (data.mv_data)));
	printf("propertyKey: %.*s propertyKeyIdType %s, propertyKeyId: %i , indexed = %s\n", propertyKeySize, propertyKey,
			propertyTypeEnumToString(propertyKeyDataStruct.type), propertyKeyDataStruct.propertyKeyId,
			(propertyKeyDataStruct.indexed == 1 ? "true" : "false"));
}

void printPropertyKeyInverseDbRecord(MDB_val key, MDB_val data) {
	int propertyKeyId = *((int *) (key.mv_data));
	int propertyKeySize = data.mv_size - sizeof(PropertyKeyInverseDataStruct);
	PropertyKeyInverseDataStruct *propertyKeyInverseDataStruct = (PropertyKeyInverseDataStruct *) (data.mv_data);
	enum PropertyTypeEnum type = propertyKeyInverseDataStruct->type;
	unsigned char indexed = propertyKeyInverseDataStruct->indexed;
	char *propertyKey = propertyKeyInverseDataStruct->propertyKey;
	printf("propertyKeyId: %i propertyKeyIdType %s, indexed = %s, propertyKey = %.*s \n", propertyKeyId, propertyTypeEnumToString(type),
			(indexed == 1 ? "true" : "false"), propertyKeySize, propertyKey);
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
	fail: mdb_cursor_close(cursor);
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
	fail: mdb_cursor_close(cursor);
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

int traverseVertexPropertyKeyInverseDb(GLMDB_env * glmdb_env, MDB_txn *txn) {

	int rc = 0;
	MDB_dbi dbi = glmdb_env->vertexPropertyKeyInverseDb;
	MDB_cursor *cursor;
	MDB_val key, data;
	rc = mdb_cursor_open(txn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		printPropertyKeyInverseDbRecord(key, data);
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

int traverseEdgePropertyKeyInverseDb(GLMDB_env * glmdb_env, MDB_txn *txn) {
	int rc;
	MDB_dbi dbi = glmdb_env->edgePropertyKeyInverseDb;
	MDB_cursor *cursor;
	MDB_val key, data;
	rc = mdb_cursor_open(txn, dbi, &cursor);
	if (rc != 0) {
		goto fail;
	}
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		printPropertyKeyInverseDbRecord(key, data);
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

