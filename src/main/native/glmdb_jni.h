#ifndef THUNDERGRAPH_STRUCT
#define THUNDERGRAPH_STRUCT
#include "thundergraph_structs.h"
#endif

#ifndef _Included_org_glmdb_blueprints_jni_ThunderJni
#define _Included_org_glmdb_blueprints_jni_ThunderJni
#ifdef __cplusplus
extern "C" {
#endif

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_byte_value
	 * Signature: (J[JIB)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1byte_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jbyte value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_byte_value
	 * Signature: (J[JIB)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1byte_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jbyte value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_value_from_byte_index
	 * Signature: (J[JIB)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1byte_1index(JNIEnv *env,
			jclass that, jlong vertexByteIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jbyte value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_value_for_byte_index
	 * Signature: (J[JIB)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1byte_1index(JNIEnv *env,
			jclass that, jlong vertexByteIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jbyte value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_value_from_byte_index
	 * Signature: (JJIB[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1byte_1index(JNIEnv *env,
			jclass that, jlong edgeByteIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jbyte value, jlongArray edgeIdResult,
			jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_value_for_byte_index
	 * Signature: (JJIB[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1byte_1index(JNIEnv *env,
			jclass that, jlong edgeByteIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jbyte value, jlongArray edgeIdResult,
			jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_byte_value
	 * Signature: (J[J[I[J[JIB)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1byte_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
			jbyte value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_byte_value
	 * Signature: (J[J[I[J[JIB)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1byte_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
			jbyte value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_char_value
	 * Signature: (J[JIC)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1char_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jchar value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_char_value
	 * Signature: (J[JIC)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1char_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jchar value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_value_from_char_index
	 * Signature: (J[JIC)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1char_1index(JNIEnv *env,
			jclass that, jlong vertexCharIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jchar value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_value_for_char_index
	 * Signature: (J[JIC)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1char_1index(JNIEnv *env,
			jclass that, jlong vertexCharIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jchar value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_value_from_char_index
	 * Signature: (JJIC[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1char_1index(JNIEnv *env,
			jclass that, jlong edgeCharIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jchar value, jlongArray edgeIdResult,
			jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_value_for_char_index
	 * Signature: (JJIC[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1char_1index(JNIEnv *env,
			jclass that, jlong edgeCharIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jchar value, jlongArray edgeIdResult,
			jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_char_value
	 * Signature: (J[J[I[J[JIC)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1char_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
			jchar value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_char_value
	 * Signature: (J[J[I[J[JIC)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1char_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
			jchar value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_short_value
	 * Signature: (J[JIS)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1short_1value(JNIEnv *env,
			jclass that, jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jshort value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_short_value
	 * Signature: (J[JIS)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1short_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jshort value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_value_from_short_index
	 * Signature: (J[JIS)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1short_1index(
			JNIEnv *env, jclass that, jlong vertexShortIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jshort value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_value_for_short_index
	 * Signature: (J[JIS)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1short_1index(JNIEnv *env,
			jclass that, jlong vertexShortIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jshort value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_value_from_short_index
	 * Signature: (JJIS[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1short_1index(JNIEnv *env,
			jclass that, jlong edgeShortIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jshort value, jlongArray edgeIdResult,
			jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_value_for_short_index
	 * Signature: (JJIS[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1short_1index(JNIEnv *env,
			jclass that, jlong edgeShortIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jshort value, jlongArray edgeIdResult,
			jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_short_value
	 * Signature: (J[J[I[J[JIS)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1short_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
			jshort value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_short_value
	 * Signature: (J[J[I[J[JIS)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1short_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
			jshort value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_boolean_value
	 * Signature: (J[JIZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1boolean_1value(JNIEnv *env,
			jclass that, jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jboolean value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_boolean_value
	 * Signature: (J[JIZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1boolean_1value(JNIEnv *env,
			jclass that, jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jboolean value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_value_from_boolean_index
	 * Signature: (J[JIZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1boolean_1index(
			JNIEnv *env, jclass that, jlong vertexBooleanIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jboolean value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_value_for_boolean_index
	 * Signature: (J[JIZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1boolean_1index(
			JNIEnv *env, jclass that, jlong vertexBooleanIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jboolean value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_value_from_boolean_index
	 * Signature: (JJIZ[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1boolean_1index(
			JNIEnv *env, jclass that, jlong edgeBooleanIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jboolean value,
			jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_value_for_boolean_index
	 * Signature: (JJIZ[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1boolean_1index(JNIEnv *env,
			jclass that, jlong edgeBooleanIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jboolean value, jlongArray edgeIdResult,
			jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_boolean_value
	 * Signature: (J[J[I[J[JIZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1boolean_1value(JNIEnv *env,
			jclass that, jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId,
			jint propertyKeyId, jboolean value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_boolean_value
	 * Signature: (J[J[I[J[JIZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1boolean_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
			jboolean value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_double_value
	 * Signature: (J[JID)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1double_1value(JNIEnv *env,
			jclass that, jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jdouble value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_double_value
	 * Signature: (J[JID)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1double_1value(JNIEnv *env,
			jclass that, jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jdouble value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_value_from_double_index
	 * Signature: (J[JID)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1double_1index(
			JNIEnv *env, jclass that, jlong vertexDoubleIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jdouble value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_value_for_double_index
	 * Signature: (J[JID)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1double_1index(JNIEnv *env,
			jclass that, jlong vertexDoubleIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jdouble value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_value_from_double_index
	 * Signature: (JJID[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1double_1index(JNIEnv *env,
			jclass that, jlong edgeDoubleIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jdouble value, jlongArray edgeIdResult,
			jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_value_for_double_index
	 * Signature: (JJID[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1double_1index(JNIEnv *env,
			jclass that, jlong edgeDoubleIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jdouble value, jlongArray edgeIdResult,
			jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_double_value
	 * Signature: (J[J[I[J[JID)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1double_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
			jdouble value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_double_value
	 * Signature: (J[J[I[J[JID)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1double_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
			jdouble value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_float_value
	 * Signature: (J[JIF)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1float_1value(JNIEnv *env,
			jclass that, jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jfloat value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_float_value
	 * Signature: (J[JIF)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1float_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jfloat value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_value_from_float_index
	 * Signature: (J[JIF)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1float_1index(
			JNIEnv *env, jclass that, jlong vertexFloatIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jfloat value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_value_for_float_index
	 * Signature: (J[JIF)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1float_1index(JNIEnv *env,
			jclass that, jlong vertexFloatIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jfloat value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_value_from_float_index
	 * Signature: (JJIF[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1float_1index(JNIEnv *env,
			jclass that, jlong edgeFloatIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jfloat value, jlongArray edgeIdResult,
			jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_value_for_float_index
	 * Signature: (JJIF[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1float_1index(JNIEnv *env,
			jclass that, jlong edgeFloatIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jfloat value, jlongArray edgeIdResult,
			jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_float_value
	 * Signature: (J[J[I[J[JIF)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1float_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
			jfloat value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_float_value
	 * Signature: (J[J[I[J[JIF)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1float_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
			jfloat value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_long_value
	 * Signature: (J[JIJ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1long_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jlong value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_long_value
	 * Signature: (J[JIJ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1long_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jlong value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_value_from_long_index
	 * Signature: (J[JIJ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1long_1index(JNIEnv *env,
			jclass that, jlong vertexLongIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jlong value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_value_for_long_index
	 * Signature: (J[JIJ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1long_1index(JNIEnv *env,
			jclass that, jlong vertexLongIndexDbCursor, jlongArray vertexIdResult, jint propertyKeyId, jlong value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_value_from_long_index
	 * Signature: (JJIJ[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1long_1index(JNIEnv *env,
			jclass that, jlong edgeLongIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jlong value, jlongArray edgeIdResult,
			jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_value_for_long_index
	 * Signature: (JJIJ[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1long_1index(JNIEnv *env,
			jclass that, jlong edgeLongIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jlong value, jlongArray edgeIdResult,
			jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_long_value
	 * Signature: (J[J[I[J[JIJ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1long_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
			jlong value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_long_value
	 * Signature: (J[J[I[J[JIJ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1long_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint propertyKeyId,
			jlong value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_db_entries
	 * Signature: (JJI[I)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1db_1entries(JNIEnv *env, jclass that, jlong glmdb_env, jlong txn,
			jint dbEnum, jintArray entries);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_env_get_path
	 * Signature: (J[[B)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1env_1get_1path(JNIEnv *env, jclass that, jlong glmdbEnv,
			jobjectArray path);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    print_db
	 * Signature: (JJI)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_print_1db(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn,
			jint dbEnum);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    init
	 * Signature: ()V
	 */
	JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_init(JNIEnv *env, jclass that);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_strerror
	 * Signature: (I)Ljava/lang/String;
	 */
	JNIEXPORT jstring JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1strerror(JNIEnv *env, jclass that, jint error);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    glmdb_env_create
	 * Signature: (Ljava/lang/String;[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_glmdb_1env_1create(JNIEnv * env, jclass that, jstring path,
			jlongArray pointerArray);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    glmdb_env_close
	 * Signature: (J)V
	 */
	JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_glmdb_1env_1close(JNIEnv *env, jclass that, jlong glmdbEnv);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_txn_begin
	 * Signature: (JJJ[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1txn_1begin(JNIEnv *env, jclass that, jlong glmdb_env, jlong parent,
			jlong flags, jlongArray txn);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_txn_renew
	 * Signature: (J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1txn_1renew(JNIEnv *env, jclass that, jlong txn);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_txn_commit
	 * Signature: (JJZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1txn_1commit(JNIEnv *env, jclass that, jlong glmdb_env, jlong txn,
			jboolean readOnly);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_txn_reset
	 * Signature: (J)V
	 */
	JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1txn_1reset(JNIEnv *env, jclass that, jlong txn);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_txn_abort
	 * Signature: (JJ)V
	 */
	JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1txn_1abort(JNIEnv *env, jclass that, jlong glmdb_env, jlong txn);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_cursor_open_and_position_on_edge_vertex_db
	 * Signature: (JJJIIJ[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1edge_1vertex_1db(JNIEnv *env,
			jclass that, jlong txn, jlong glmdb_env, jlong vertexId, jint direction, jint labelId, jlong edgeId, jlongArray cursorArray);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_cursor_open_and_position_on_vertex_vertex_db
	 * Signature: (JJJ[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1vertex_1vertex_1db
	  (JNIEnv *env, jclass that, jlong txn, jlong glmdb_env, jlong vertexId, jlongArray cursorArray);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_cursor_open_and_position_on_edge_edge_db
	 * Signature: (JJJI[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1edge_1edge_1db(JNIEnv *env,
			jclass that, jlong txn, jlong glmdb_env, jlong edgeId, jint propertykeyId, jlongArray cursor);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJniint
	 * Method:    mdb_cursor_close
	 * Signature: (J)V
	 */
	JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1close(JNIEnv *env, jclass that, jlong cursor);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_cursor_renew
	 * Signature: (JJ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1renew(JNIEnv *env, jclass that, jlong txn, jlong cursor);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_cursor_open
	 * Signature: (JJI[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open(JNIEnv *env, jclass that, jlong txn, jlong glmdb_env,
			jint dbEnum, jlongArray cursorArray);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_add_vertex
	 * Signature: (JJ[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1add_1vertex(JNIEnv *env, jclass that, jlong glmdb_env,
			jlong cursor, jlongArray vertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_add_edge
	 * Signature: (JJJJI[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1add_1edge(JNIEnv *env, jclass that, jlong glmdb_env, jlong txn,
			jlong outVertexId, jlong inVertexId, jint labelId, jlongArray edgeId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_set_property_boolean
	 * Signature: (JJJJIZZZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1boolean(JNIEnv *env, jclass that, jlong glmdb_env,
			jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jboolean value, jboolean vertex, jboolean indexed);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_set_property_byte
	 * Signature: (JJJJIBZZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1byte(JNIEnv *env, jclass that, jlong glmdb_env,
			jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jbyte value, jboolean vertex, jboolean indexed);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_set_property_short
	 * Signature: (JJJJISZZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1short(JNIEnv *env, jclass that, jlong glmdb_env,
			jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jshort value, jboolean vertex, jboolean indexed);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_set_property_int
	 * Signature: (JJJJIIZZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1int(JNIEnv *env, jclass that, jlong glmdb_env,
			jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jint value, jboolean vertex, jboolean indexed);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_set_property_long
	 * Signature: (JJJJIJZZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1long(JNIEnv *env, jclass that, jlong glmdb_env,
			jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jlong value, jboolean vertex, jboolean indexed);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_set_property_float
	 * Signature: (JJJJIFZZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1float(JNIEnv *env, jclass that, jlong glmdb_env,
			jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jfloat value, jboolean vertex, jboolean indexed);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_set_property_double
	 * Signature: (JJJJIDZZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1double(JNIEnv *env, jclass that, jlong glmdb_env,
			jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jdouble value, jboolean vertex, jboolean indexed);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_set_property_char
	 * Signature: (JJJJICZZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1char(JNIEnv *env, jclass that, jlong glmdb_env,
			jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jchar value, jboolean vertex, jboolean indexed);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_set_property_string
	 * Signature: (JJJJILjava/lang/String;ZZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1string(JNIEnv *env, jclass that, jlong glmdb_env,
			jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jstring value, jboolean vertex, jboolean indexed);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_property_array
	 * Signature: (JJI[[BZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1property_1array(JNIEnv *env, jclass that, jlong cursor,
			jlong elementId, jint propertyKeyId, jobjectArray value, jboolean vertexKey);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_del_property
	 * Signature: (JJI[[BZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1del_1property(JNIEnv *env, jclass that, jlong cursor,
			jlong elementId, jint propertyKeyId, jobjectArray value, jboolean vertexOrEdge);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_property
	 * Signature: (JJILorg/glmdb/blueprints/jni/Value;)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1property(JNIEnv *env, jclass that, jlong cursor,
			jlong vertexId, jint propertyKeyId, jobject value);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_property_keys
	 * Signature: (JJ[[IZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1property_1keys(JNIEnv *env, jclass that, jlong cursor,
			jlong elementId, jobjectArray values, jboolean vertexOrEdge);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_set_propertykey
	 * Signature: (JJLjava/lang/String;I[IZZZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1propertykey(JNIEnv *env, jclass that, jlong glmdb_env,
			jlong txn, jstring propertyKey, jint propertyKeyEnum, jintArray propertyKeyIdArray, jboolean vertex, jboolean indexed,
			jboolean overwrite);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_reindex_property
	 * Signature: (JJIIZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1reindex_1property(JNIEnv *env, jclass that, jlong glmdb_env,
			jlong txn, jint propertyKeyId, jint propertyKeyEnum, jboolean vertex);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_first_property_key
	 * Signature: (J[I[I[Z[[B)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1property_1key(JNIEnv *env, jclass that, jlong cursor,
			jintArray propertyKeyIdArray, jintArray propertyTypeEnumArray, jbooleanArray propertyIndexedArray,
			jobjectArray propertyKeyArray);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_next_property_key
	 * Signature: (J[I[I[Z[[B)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1property_1key(JNIEnv *env, jclass that, jlong cursor,
			jintArray propertyKeyIdArray, jintArray propertyTypeEnumArray, jbooleanArray propertyIndexedArray,
			jobjectArray propertyKeyArray);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_first_label
	 * Signature: (J[I[[B)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1label(JNIEnv *env, jclass that, jlong cursor,
			jintArray labelIdArray, jobjectArray labelArray);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_next_label
	 * Signature: (J[I[[B)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1label(JNIEnv *env, jclass that, jlong cursor,
			jintArray labelIdArray, jobjectArray labelArray);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_set_label
	 * Signature: (JJLjava/lang/String;[I)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1label(JNIEnv *env, jclass that, jlong glmdb_env, jlong txn,
			jstring label, jintArray labelIdArray);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_vertex
	 * Signature: (JJ[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1vertex(JNIEnv *env, jclass that, jlong cursor, jlong vertexId,
			jlongArray vertexIdResult);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_remove_vertex
	 * Signature: (JJJ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1remove_1vertex(JNIEnv *env, jclass that, jlong glmdb_env,
			jlong txn, jlong vertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_first_vertex
	 * Signature: (J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex(JNIEnv *env, jclass that, jlong cursor,
			jlongArray vertexIdResult);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_next_vertex
	 * Signature: (JJ[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex(JNIEnv *env, jclass that, jlong cursor,
			jlong previousVertexId, jlongArray vertexIdResult);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_first_vertex_for_key_value
	 * Signature: (J[JILjava/lang/Object;)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray vertexIdResult, jint propertyKey, jobject value);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_first_vertex_for_key_value
	 * Signature: (J[JI[B)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray vertexIdResult, jint propertyKey, jbyteArray value);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_next_vertex_for_key_value
	 * Signature: (J[JI[B)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value(JNIEnv * env, jclass that,
			jlong cursor, jlongArray vertexIdResult, jint propertyKey, jbyteArray value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_value_from_string_index
	 * Signature: (J[JILjava/lang/String;)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1string_1index(
			JNIEnv *env, jclass that, jlong cursor, jlongArray vertexIdResult, jint propertyKey, jstring value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_value_for_string_index
	 * Signature: (J[JILjava/lang/String;)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1string_1index(JNIEnv *env,
			jclass that, jlong cursor, jlongArray vertexIdResult, jint propertyKey, jstring value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_value_from_string_index
	 * Signature: (JJILjava/lang/String;[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1string_1index(JNIEnv *env,
			jclass that, jlong edgeStringIndexDbCursor, jlong edgeDbCursor, jint propertyKey, jstring value, jlongArray edgeIdResult,
			jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_value_for_string_index
	 * Signature: (JJILjava/lang/String;[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1string_1index(JNIEnv *env,
			jclass that, jlong edgeStringIndexDbCursor, jlong edgeDbCursor, jint propertyKey, jstring value, jlongArray edgeIdResult,
			jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_value_from_int_index
	 * Signature: (J[JII)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1int_1index(JNIEnv *env,
			jclass that, jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jint value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_value_for_int_index
	 * Signature: (J[JII)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1value_1for_1int_1index(JNIEnv *env,
			jclass that, jlong cursor, jlongArray vertexIdResult, jint propertyKeyId, jint value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_value_from_int_index
	 * Signature: (JJII[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value_1from_1int_1index(JNIEnv *env,
			jclass that, jlong edgeIntIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jint value, jlongArray edgeIdResult,
			jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_value_for_int_index
	 * Signature: (JJII[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value_1for_1int_1index(JNIEnv *env,
			jclass that, jlong edgeIntIndexDbCursor, jlong edgeDbCursor, jint propertyKeyId, jint value, jlongArray edgeIdResult,
			jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_edge
	 * Signature: (JJ[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1edge(JNIEnv *env, jclass that, jlong cursor, jlong edgeId,
			jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_remove_edge
	 * Signature: (JJJ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1remove_1edge(JNIEnv *env, jclass that, jlong glmdb_env, jlong txn,
			jlong edgeId);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_first_edge
	 * Signature: (J[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge(JNIEnv * env, jclass that, jlong cursor,
			jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_next_edge
	 * Signature: (JJ[J[I[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge(JNIEnv *env, jclass that, jlong cursor,
			jlong previousEdgeId, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_first_edge_for_key_value
	 * Signature: (J[J[I[J[JI[B)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint propertyKey,
			jbyteArray value);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_next_edge_for_key_value
	 * Signature: (J[J[I[J[JI[B)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint propertyKey,
			jbyteArray value);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_first_edge_from_vertex
	 * Signature: (JIIJ[J[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1from_1vertex(JNIEnv *env, jclass that,
			jlong cursor, jint direction, jint labelId, jlong fromVertexId, jlongArray edgeIdResult, jlongArray outVertexId,
			jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_next_edge_from_vertex
	 * Signature: (JIIJ[J[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1from_1vertex(JNIEnv *env, jclass that,
			jlong cursor, jint direction, jint labelId, jlong fromVertexId, jlongArray edgeIdResult, jlongArray outVertexId,
			jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_current_edge_from_vertex
	 * Signature: (JIIJ[J[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1edge_1from_1vertex(JNIEnv *env, jclass that,
			jlong cursor, jint direction, jint labelId, jlong fromVertexId, jlongArray edgeIdResult, jlongArray outVertexId,
			jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_first_edge_from_vertex_all_labels
	 * Signature: (JIJ[I[J[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1from_1vertex_1all_1labels(JNIEnv *env,
			jclass that, jlong cursor, jint direction, jlong fromVertexId, jintArray labelIdResult, jlongArray edgeIdResult,
			jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_GlmdbJni
	 * Method:    mdb_get_next_edge_from_vertex_all_labels
	 * Signature: (JIJ[I[J[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1from_1vertex_1all_1labels(JNIEnv *env,
			jclass that, jlong cursor, jint direction, jlong fromVertexId, jintArray labelIdResult, jlongArray edgeIdResult,
			jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_current_edge_from_vertex_all_labels
	 * Signature: (JIJ[I[J[J[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1edge_1from_1vertex_1all_1labels(JNIEnv *env,
			jclass that, jlong cursor, jint direction, jlong fromVertexId, jintArray labelIdResult, jlongArray edgeIdResult,
			jlongArray outVertexId, jlongArray inVertexId);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_delete_index
	 * Signature: (JJIZI)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1delete_1index(JNIEnv *env, jclass that, jlong glmdb_env, jlong txn,
			jint propertyKeyId, jboolean vertex, jint propertyKeyEnum);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_string_value
	 * Signature: (J[JILjava/lang/String;)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1string_1value(JNIEnv *env,
			jclass that, jlong cursor, jlongArray vertexIdResult, jint key, jstring value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_string_value
	 * Signature: (J[JILjava/lang/String;)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1string_1value(JNIEnv *env,
			jclass that, jlong cursor, jlongArray vertexIdResult, jint key, jstring value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_vertex_for_key_int_value
	 * Signature: (J[JII)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1int_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray vertexIdResult, jint key, jint value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_vertex_for_key_int_value
	 * Signature: (J[JII)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1int_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray vertexIdResult, jint key, jint value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_string_value
	 * Signature: (J[J[I[J[JILjava/lang/String;)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1string_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint key, jstring value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_string_value
	 * Signature: (J[J[I[J[JILjava/lang/String;)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1string_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint key, jstring value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_first_edge_for_key_int_value
	 * Signature: (J[J[I[J[JII)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1for_1key_1int_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint key, jint value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_next_edge_for_key_int_value
	 * Signature: (J[J[I[J[JII)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1for_1key_1int_1value(JNIEnv *env, jclass that,
			jlong cursor, jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint key, jint value);



	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_string_index_db
	 * Signature: (JJJILjava/lang/String;[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1string_1index_1db
	  (JNIEnv *env, jclass that, jlong txn , jlong glmdb_env, jlong vertexId, jint propertyKey, jstring value, jlongArray cursor);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_int_index_db
	 * Signature: (JJJII[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1int_1index_1db
	  (JNIEnv *env, jclass that, jlong txn, jlong glmdb_env, jlong vertexId, jint propertyKey, jint value, jlongArray cursor);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_long_index_db
	 * Signature: (JJJIJ[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1long_1index_1db
	  (JNIEnv *env, jclass that, jlong txn, jlong glmdb_env, jlong vertexId, jint propertyKey, jlong value, jlongArray cursor);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_float_index_db
	 * Signature: (JJJIF[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1float_1index_1db
	  (JNIEnv *env, jclass that, jlong txn, jlong glmdb_env, jlong vertexId, jint propertyKey, jfloat value, jlongArray cursor);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_double_index_db
	 * Signature: (JJJID[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1double_1index_1db
	  (JNIEnv *env, jclass that, jlong txn, jlong glmdb_env, jlong vertexId, jint propertyKey, jdouble value, jlongArray cursor);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_boolean_index_db
	 * Signature: (JJJIZ[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1boolean_1index_1db
	  (JNIEnv *env, jclass that, jlong txn, jlong glmdb_env, jlong vertexId, jint propertyKey, jboolean value, jlongArray cursor);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_short_index_db
	 * Signature: (JJJIS[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1short_1index_1db
	  (JNIEnv *env, jclass that, jlong txn, jlong glmdb_env, jlong vertexId, jint propertyKey, jshort value, jlongArray cursor);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_char_index_db
	 * Signature: (JJJIC[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1char_1index_1db
	  (JNIEnv *env, jclass that, jlong txn, jlong glmdb_env, jlong vertexId, jint propertyKey, jchar value, jlongArray cursor);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_cursor_open_and_position_on_key_value_vertex_byte_index_db
	 * Signature: (JJJIB[J)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1key_1value_1vertex_1byte_1index_1db
	  (JNIEnv *env, jclass that, jlong txn, jlong glmdb_env, jlong vertexId, jint propertyKey, jbyte value, jlongArray cursor);


	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_current_vertex_from_vertex_string_index_db
	 * Signature: (J[JILjava/lang/String;)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1string_1index_1db
	  (JNIEnv *env, jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId, jstring value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_current_vertex_from_vertex_int_index_db
	 * Signature: (J[JII)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1int_1index_1db
	  (JNIEnv *env, jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId, jint value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_current_vertex_from_vertex_long_index_db
	 * Signature: (J[JIJ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1long_1index_1db
	  (JNIEnv *env, jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId, jlong value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_current_vertex_from_vertex_float_index_db
	 * Signature: (J[JIF)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1float_1index_1db
	  (JNIEnv *env, jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId, jfloat value);


	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_current_vertex_from_vertex_double_index_db
	 * Signature: (J[JID)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1double_1index_1db
	  (JNIEnv *env, jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId,  jdouble value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_current_vertex_from_vertex_boolean_index_db
	 * Signature: (J[JIZ)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1boolean_1index_1db
	  (JNIEnv *env, jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId,  jboolean value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_current_vertex_from_vertex_short_index_db
	 * Signature: (J[JIS)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1short_1index_1db
	  (JNIEnv *env, jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId,  jshort value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_current_vertex_from_vertex_char_index_db
	 * Signature: (J[JIC)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1char_1index_1db
	  (JNIEnv *env, jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId,  jchar value);

	/*
	 * Class:     org_glmdb_blueprints_jni_ThunderJni
	 * Method:    mdb_get_current_vertex_from_vertex_byte_index_db
	 * Signature: (J[JIB)I
	 */
	JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1current_1vertex_1from_1vertex_1byte_1index_1db
	  (JNIEnv *env, jclass that, jlong cursor, jlongArray vertexIdArray, jint propertyKeyId,  jbyte value);


	void printEdgeRecord(MDB_val key, MDB_val data);
	void printKey(MDB_val key);
	void printPropertyKeyDbRecord(MDB_val key, MDB_val data);
	void printPropertyKeyInverseDbRecord(MDB_val key, MDB_val data);
	void printLabelDbRecord(MDB_val key, MDB_val data);
	int printConfigDbRecord(MDB_val key, MDB_val data);

	int openGraph(GLMDB_env **genv, const char *path);
	int thundergraph_commit(GLMDB_env * glmdb_env, MDB_txn *txn);
	int saveSequenceHigh(GLMDB_env * glmdb_env, MDB_txn *txn, enum SequenceEnum sequenceEnum);
	int loadSequences(GLMDB_env *glmdbEnv, enum SequenceEnum sequenceEnum);
	int createDb(MDB_env *env, char *name, unsigned int flags, MDB_dbi *db, MDB_cmp_func *cmp);
	void closeGraph(GLMDB_env *genv);
	int addVertex(MDB_cursor *cursor, MDB_dbi vertexDb, jlong vertexId, MDB_val *vertexKey);
	int getVertex(MDB_cursor *cursor, jlong vertexId, MDB_val *vertexKey);
	int getFirstEdgefromVertex(MDB_cursor *cursor, jint direction, jint labelId, jlong fromVertexId, jlong *edgeIdResultC,
			jlong *outVertexIdC, jlong *inVertexIdC);
	int getNextEdgefromVertex(MDB_cursor *cursor, jint direction, jint labelId, jlong fromVertexId, jlong *edgeIdResultC,
			jlong *outVertexIdC, jlong *inVertexIdC);
	int getCurrentEdgefromVertex(MDB_cursor *cursor, jint direction, jint labelId, jlong fromVertexId, jlong *edgeIdResultC, jlong *outVertexIdC,
			jlong *inVertexIdC);
	int getFirstEdgefromVertexAllLabels(MDB_cursor *cursor, jint direction, jlong fromVertexId, jint *labelIdResultC, jlong *edgeIdResultC,
			jlong *outVertexIdC, jlong *inVertexIdC);
	int getNextEdgefromVertexAllLabels(MDB_cursor *cursor, jint direction, jlong fromVertexId, jint *labelIdResultC, jlong *edgeIdResultC,
			jlong *outVertexIdC, jlong *inVertexIdC);
	int getCurrentEdgefromVertexAllLabels(MDB_cursor *cursor, jint direction, jlong fromVertexId, jint *labelIdResultC,
			jlong *edgeIdResultC, jlong *outVertexIdC, jlong *inVertexIdC);

	int addEdge(MDB_txn *txn, MDB_dbi vertexDb, MDB_dbi edgeDb, jlong edgeId, jint labelId, jlong vertexOutId, jlong vertexInId);
	int addEdgeToEdgeDb(MDB_txn *txn, MDB_dbi edgeDb, jlong edgeId, jint labelId, jlong vertexOutId, jlong vertexInId);
	int addEdgeToVertexDb(MDB_txn *txn, MDB_dbi vertexDb, jlong edgeId, jint labelId, jlong vertexOutId, jlong vertexInId);

	int compareVertexDbId(const MDB_val *key1, const MDB_val *key2);
	int compareEdgeDbId(const MDB_val *key1, const MDB_val *key2);
	int comparePropertyKeyDbId(const MDB_val *key1, const MDB_val *key2);

	void printDbStats(MDB_env *env, MDB_txn *txn, MDB_dbi vertexDb, char *name);

	int setVertexPropertyBoolean(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jboolean *propertyValue);
	int setVertexPropertyByte(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jbyte *propertyValue);
	int setVertexPropertyShort(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jshort *propertyValue);
	int setVertexPropertyFloat(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jfloat *propertyValue);
	int setVertexPropertyDouble(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jdouble *propertyValue);
	int setVertexPropertyChar(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jchar *propertyValue);

	int setEdgePropertyBoolean(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jboolean *propertyValue);
	int setEdgePropertyByte(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jbyte *propertyValue);
	int setEdgePropertyShort(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jshort *propertyValue);
	int setEdgePropertyFloat(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jfloat *propertyValue);
	int setEdgePropertyDouble(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jdouble *propertyValue);
	int setEdgePropertyChar(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jchar *propertyValue);

	int reindexProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, int propertyKeyId, int propertyKeyEnum, unsigned char vertex);

	int removeVertexProperty(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId);
	int getEdgeProperty(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, MDB_val *data);
	int removeEdgeProperty(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId);
	int getVertexPropertyKeys(MDB_cursor *cursor, jlong vertexId, jint *propertyKeyArraySizeC, jint **propertyKeyArrayC);
	int getEdgePropertyKeys(MDB_cursor *cursor, jlong edgeId, jint *propertyKeyArraySizeC, jint **propertyKeyArrayC);

	int setPropertyKey(GLMDB_env *glmdb_env, MDB_txn * txn, int propertyKeyEnum, int *propertyKeyId, int propertyKeyLength,
			char propertyKeyC[], unsigned char vertex, unsigned char indexed, unsigned char overwrite);
	char * propertyTypeEnumToString(int propertyTypeEnum);

	int traverseVertexDb(GLMDB_env * glmdb_env, MDB_txn *txn);
	int traverseEdgeDb(GLMDB_env * glmdb_env, MDB_txn *txn);
	int traverseVertexPropertyKeyDb(GLMDB_env * glmdb_env, MDB_txn *txn);
	int traverseVertexPropertyKeyInverseDb(GLMDB_env * glmdb_env, MDB_txn *txn);
	int traverseEdgePropertyKeyDb(GLMDB_env * glmdb_env, MDB_txn *txn);
	int traverseEdgePropertyKeyInverseDb(GLMDB_env * glmdb_env, MDB_txn *txn);
	int traverseLabelDb(GLMDB_env * glmdb_env, MDB_txn *txn);
	int traverseConfigDb(GLMDB_env * glmdb_env, MDB_txn *txn);

	void buffer_copy(const void *source, size_t source_pos, void *dest, size_t dest_pos, size_t length);

#ifdef __cplusplus
}
#endif
#endif
