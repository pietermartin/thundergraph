#include <jni.h>
#include "lmdb.h"

#ifndef _Included_org_glmdb_blueprints_jni_ThunderJni
#define _Included_org_glmdb_blueprints_jni_ThunderJni
#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup  errors	Return Codes
 *
 *	lmdb uses -30600 to -30800, we'll go under them
 *	@{
 */
/** key/data pair already exists */
#define GLMDB_WRITE_NULL	(-30599)
#define GLMDB_END_OF_EDGES	(-30598)
#define GLMDB_UNDEFINED_DIRECTION	(-30597)
#define GLMDB_DB_CORRUPT	(-30596)
#define GLMDB_DB_INVALID_DIRECTION	(-30595)
#define GLMDB_DB_INVALID_EDGE	(-30594)
#define GLMDB_INVALID_SEQUENCE	(-30593)
#define GLMDB_INVALID_DB	(-30592)

typedef struct GLMDB_env {
	MDB_env *env;
	MDB_dbi configDb;
	MDB_dbi vertexDb;
	MDB_dbi edgeDb;
	MDB_dbi vertexPropertyKeyDb;
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

	long long vertexIdSequence;
	long long edgeIdSequence;
	int vertexPropertyKeyIdSequence;
	int edgePropertyKeyIdSequence;
	int labelIdSequence;
	char *path;
} GLMDB_env;

enum DbEnum {
	VERTEX_DB,
	EDGE_DB,
	VERTEX_PROPERTY_DB,
	EDGE_PROPERTY_DB,
	LABEL_DB,
	CONFIG_DB,
	VERTEX_BOOLEAN_INDEX,
	VERTEX_BYTE_INDEX,
	VERTEX_SHORT_INDEX,
	VERTEX_INT_INDEX,
	VERTEX_LONG_INDEX,
	VERTEX_FLOAT_INDEX,
	VERTEX_DOUBLE_INDEX,
	VERTEX_CHAR_INDEX,
	VERTEX_STRING_INDEX,
	EDGE_BOOLEAN_INDEX,
	EDGE_BYTE_INDEX,
	EDGE_SHORT_INDEX,
	EDGE_INT_INDEX,
	EDGE_LONG_INDEX,
	EDGE_FLOAT_INDEX,
	EDGE_DOUBLE_INDEX,
	EDGE_CHAR_INDEX,
	EDGE_STRING_INDEX
};

enum SequenceEnum {
	VERTEX_ID_SEQUENCE, EDGE_ID_SEQUENCE, VERTEX_PROPERTY_KEY_ID_SEQUENCE, EDGE_PROPERTY_KEY_ID_SEQUENCE, LABEL_ID_SEQUENCE
};

enum VertexCoreOrPropertyEnum {
	VCORE, VPROPERTY_KEY, OUTLABEL, INLABEL
};

enum EdgeCoreOrPropertyEnum {
	ECORE, EPROPERTY_KEY
};

typedef struct VertexDbId {
	jlong vertexId;
	enum VertexCoreOrPropertyEnum coreOrPropertyEnum;
	jint propertykeyId;
	jint labelId;
	jlong edgeId;
} VertexDbId;

typedef struct EdgeDbId {
	jlong edgeId;
	enum EdgeCoreOrPropertyEnum coreOrPropertyEnum;
	jint propertykeyId;
} EdgeDbId;

typedef struct EdgeData {
	jlong vertexInId;
	jlong vertexOutId;
	jint labelId;
} EdgeData;

enum PropertyTypeEnum {
	BOOLEAN,
	BYTE,
	SHORT,
	INT,
	LONG,
	FLOAT,
	DOUBLE,
	CHAR,
	STRING,
	ARRAY_BOOLEAN,
	ARRAY_BYTE,
	ARRAY_SHORT,
	ARRAY_INT,
	ARRAY_LONG,
	ARRAY_FLOAT,
	ARRAY_DOUBLE,
	ARRAY_CHAR,
	ARRAY_STRING,
	UNSET
};

typedef struct PropertyKeyDataStruct {
	jint propertyKeyId;
	enum PropertyTypeEnum type;
	jboolean indexed;
} PropertyKeyDataStruct;

typedef struct StringIndexKeyStruct {
	jint propertyKeyId;
	long long elementId;
	char value[0];
} StringIndexKeyStruct;

typedef struct IntIndexKeyStruct {
	jint propertyKeyId;
	long long elementId;
	int value;
} IntIndexKeyStruct;

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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_print_1db(JNIEnv *env, jclass that, jlong glmdbEnv, jlong txn, jint dbEnum);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_init
(JNIEnv *env, jclass that);

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
JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_glmdb_1env_1close
(JNIEnv *env, jclass that, jlong glmdbEnv);

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
JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1txn_1reset
(JNIEnv *env, jclass that, jlong txn);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_txn_abort
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1txn_1abort
(JNIEnv *env, jclass that, jlong glmdb_env, jlong txn);

///*
// * Class:     org_glmdb_blueprints_jni_GlmdbJni
// * Method:    mdb_cursor_open_vertex_db
// * Signature: (JJ[J)I
// */
//JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1vertex_1db(JNIEnv *env, jclass that, jlong txn,
//		jlong glmdb_env, jlongArray cursorArray);
//
///*
// * Class:     org_glmdb_blueprints_jni_GlmdbJni
// * Method:    mdb_cursor_open_property_key_db
// * Signature: (JJ[JZ)I
// */
//JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1property_1key_1db(JNIEnv *env, jclass that, jlong txn,
//		jlong glmdb_env, jlongArray cursorArray, jboolean vertex);
//
///*
// * Class:     org_glmdb_blueprints_jni_GlmdbJni
// * Method:    mdb_cursor_open_label_db
// * Signature: (JJ[J)I
// */
//JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1label_1db(JNIEnv *env, jclass that, jlong txn,
//		jlong glmdb_env, jlongArray cursorArray);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_cursor_open_and_position_on_edge_vertex_db
 * Signature: (JJJIIJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1and_1position_1on_1edge_1vertex_1db(JNIEnv *env,
		jclass that, jlong txn, jlong glmdb_env, jlong vertexId, jint direction, jint labelId, jlong edgeId, jlongArray cursorArray);

///*
// * Class:     org_glmdb_blueprints_jni_GlmdbJni
// * Method:    mdb_cursor_open_edge_db
// * Signature: (JJ[J)I
// */
//JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1open_1edge_1db(JNIEnv *env, jclass that, jlong txn,
//		jlong glmdb_env, jlongArray cursorArray);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJniint
 * Method:    mdb_cursor_close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1cursor_1close
(JNIEnv *env, jclass that, jlong cursor);

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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1add_1vertex(JNIEnv *env, jclass that, jlong glmdb_env, jlong cursor,
		jlongArray vertexId);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_add_edge
 * Signature: (JJJJI[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1add_1edge(JNIEnv *env, jclass that, jlong glmdb_env, jlong txn,
		jlong outVertexId, jlong inVertexId, jint labelId, jlongArray edgeId);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_boolean
 * Signature: (JJIZZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1boolean(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jboolean value, jboolean vertexKey);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_byte
 * Signature: (JJIBZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1byte(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jbyte value, jboolean vertexKey);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_short
 * Signature: (JJISZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1short(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jshort value, jboolean vertexKey);

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_set_property_int
 * Signature: (JJJJIIZZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1int(JNIEnv *env, jclass that, jlong glmdb_env,
		jlong txn, jlong cursor, jlong elementId, jint propertyKeyId, jint value, jboolean vertex, jboolean indexed);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_long
 * Signature: (JJIJZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1long(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jlong value, jboolean vertexKey);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_float
 * Signature: (JJIFZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1float(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jfloat value, jboolean vertexKey);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_double
 * Signature: (JJIDZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1double(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jdouble value, jboolean vertexKey);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_char
 * Signature: (JJICZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1property_1char(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jchar value, jboolean vertexKey);

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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1del_1property(JNIEnv *env, jclass that, jlong cursor, jlong elementId,
		jint propertyKeyId, jobjectArray value, jboolean vertexOrEdge);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_property
 * Signature: (JJILorg/glmdb/blueprints/jni/Value;)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1property(JNIEnv *env, jclass that, jlong cursor, jlong vertexId,
		jint propertyKeyId, jobject value);

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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1set_1propertykey(JNIEnv *env, jclass that, jlong glmdb_env, jlong txn,
		jstring propertyKey, jint propertyKeyEnum, jintArray propertyKeyIdArray, jboolean vertex, jboolean indexed, jboolean overwrite);

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_reindex_property
 * Signature: (JJIIZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1reindex_1property(JNIEnv *env, jclass that, jlong glmdb_env, jlong txn,
		jint propertyKeyId, jint propertyKeyEnum, jboolean vertex);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_first_property_key
 * Signature: (J[I[I[Z[[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1property_1key(JNIEnv *env, jclass that, jlong cursor,
		jintArray propertyKeyIdArray, jintArray propertyTypeEnumArray, jbooleanArray propertyIndexedArray, jobjectArray propertyKeyArray);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_next_property_key
 * Signature: (J[I[I[Z[[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1property_1key(JNIEnv *env, jclass that, jlong cursor,
		jintArray propertyKeyIdArray, jintArray propertyTypeEnumArray, jbooleanArray propertyIndexedArray, jobjectArray propertyKeyArray);

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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1remove_1vertex(JNIEnv *env, jclass that, jlong glmdb_env, jlong txn,
		jlong vertexId);

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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1value_1from_1string_1index(JNIEnv *env,
		jclass that, jlong cursor, jlongArray vertexIdResult, jint propertyKey, jstring value);

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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1from_1vertex(JNIEnv *env, jclass that, jlong cursor,
		jint direction, jint labelId, jlong fromVertexId, jlongArray edgeIdResult, jlongArray outVertexId, jlongArray inVertexId);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_next_edge_from_vertex
 * Signature: (JIIJ[J[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1from_1vertex(JNIEnv *env, jclass that, jlong cursor,
		jint direction, jint labelId, jlong fromVertexId, jlongArray edgeIdResult, jlongArray outVertexId, jlongArray inVertexId);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_first_edge_from_vertex_all_labels
 * Signature: (JIJ[I[J[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1edge_1from_1vertex_1all_1labels(JNIEnv *env, jclass that,
		jlong cursor, jint direction, jlong fromVertexId, jintArray labelIdResult, jlongArray edgeIdResult, jlongArray outVertexId,
		jlongArray inVertexId);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_next_edge_from_vertex_all_labels
 * Signature: (JIJ[I[J[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1edge_1from_1vertex_1all_1labels(JNIEnv *env, jclass that,
		jlong cursor, jint direction, jlong fromVertexId, jintArray labelIdResult, jlongArray edgeIdResult, jlongArray outVertexId,
		jlongArray inVertexId);

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_delete_string_index
 * Signature: (JJIZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1delete_1string_1index(JNIEnv *env, jclass that, jlong glmdb_env,
		jlong txn, jint propertyKeyId, jboolean vertex);

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_first_vertex_for_key_string_value
 * Signature: (J[JILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1first_1vertex_1for_1key_1string_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint key, jstring value);

/*
 * Class:     org_glmdb_blueprints_jni_ThunderJni
 * Method:    mdb_get_next_vertex_for_key_string_value
 * Signature: (J[JILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_ThunderJni_mdb_1get_1next_1vertex_1for_1key_1string_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint key, jstring value);

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

void printVertexRecord(MDB_val key, MDB_val data);
void printEdgeRecord(MDB_val key, MDB_val data);
void printKey(MDB_val key);
void printPropertyKeyDbRecord(MDB_val key, MDB_val data);
void printLabelDbRecord(MDB_val key, MDB_val data);
int printConfigDbRecord(MDB_val key, MDB_val data);
void printStringIndexDbRecord(MDB_val key, MDB_val data);
void printIntIndexDbRecord(MDB_val key, MDB_val data);

void initVertexDbId(VertexDbId *vertexDbId);
void initEdgeDbId(EdgeDbId *edgeDbId);
void initEdgeData(EdgeData *edgeData);

int openGraph(GLMDB_env **genv, const char *path);
int thundergraph_commit(GLMDB_env * glmdb_env, MDB_txn *txn);
int saveSequenceHigh(GLMDB_env * glmdb_env, MDB_txn *txn, enum SequenceEnum sequenceEnum);
int loadSequences(GLMDB_env *glmdbEnv, enum SequenceEnum sequenceEnum);
int createDb(MDB_env *env, char *name, unsigned int flags, MDB_dbi *db, MDB_cmp_func *cmp);
void closeGraph(GLMDB_env *genv);
int addVertex(MDB_cursor *cursor, MDB_dbi vertexDb, jlong vertexId, MDB_val *vertexKey);
int removeVertex(MDB_txn *txn, GLMDB_env *genv, jlong vertexId);
int internalDeleteVertex(MDB_cursor *vertexCursor, MDB_cursor *inverseCursor, MDB_cursor *edgeCursor, VertexDbId vertexDbId,
		VertexDbId inverseId, MDB_val inverseKey, MDB_val data, MDB_val inverseData);
int getVertex(MDB_cursor *cursor, jlong vertexId, MDB_val *vertexKey);
int getFirstEdgefromVertex(MDB_cursor *cursor, jint direction, jint labelId, jlong fromVertexId, jlong *edgeIdResultC, jlong *outVertexIdC,
		jlong *inVertexIdC);
int getNextEdgefromVertex(MDB_cursor *cursor, jint direction, jint labelId, jlong fromVertexId, jlong *edgeIdResultC, jlong *outVertexIdC,
		jlong *inVertexIdC);
int getFirstEdgefromVertexAllLabels(MDB_cursor *cursor, jint direction, jlong fromVertexId, jint *labelIdResultC, jlong *edgeIdResultC,
		jlong *outVertexIdC, jlong *inVertexIdC);
int getNextEdgefromVertexAllLabels(MDB_cursor *cursor, jint direction, jlong fromVertexId, jint *labelIdResultC, jlong *edgeIdResultC,
		jlong *outVertexIdC, jlong *inVertexIdC);

int addEdge(MDB_txn *txn, MDB_dbi vertexDb, MDB_dbi edgeDb, jlong edgeId, jint labelId, jlong vertexOutId, jlong vertexInId);
int removeEdge(MDB_txn *txn, GLMDB_env *genv, jlong edgeId);
/**
 * This only removes the edge from the edge db, not the related edges in the vertexDb
 */
int internalRemoveEdge(MDB_cursor *cursor, jlong edgeId);
int getEdge(MDB_cursor *cursor, jlong edgeId, MDB_val *edgeKey, MDB_val *edgeData);
int addEdgeToEdgeDb(MDB_txn *txn, MDB_dbi edgeDb, jlong edgeId, jint labelId, jlong vertexOutId, jlong vertexInId);
int addEdgeToVertexDb(MDB_txn *txn, MDB_dbi vertexDb, jlong edgeId, jint labelId, jlong vertexOutId, jlong vertexInId);

int compareVertexDbId(const MDB_val *key1, const MDB_val *key2);
int compareEdgeDbId(const MDB_val *key1, const MDB_val *key2);
int comparePropertyKeyDbId(const MDB_val *key1, const MDB_val *key2);
int compareStringIndexDbId(const MDB_val *key1, const MDB_val *key2);
int compareIntIndexDbId(const MDB_val *key1, const MDB_val *key2);

void printDbStats(MDB_env *env, MDB_txn *txn, MDB_dbi vertexDb, char *name);

int setVertexPropertyBoolean(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jboolean *propertyValue);
int setVertexPropertyByte(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jbyte *propertyValue);
int setVertexPropertyShort(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jshort *propertyValue);
int setVertexPropertyInt(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jint *propertyValue);
int setVertexPropertyLong(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jlong *propertyValue);
int setVertexPropertyFloat(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jfloat *propertyValue);
int setVertexPropertyDouble(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jdouble *propertyValue);
int setVertexPropertyChar(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jchar *propertyValue);
int setVertexPropertyString(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jint propertyValueLength, char *propertyValue);

int setEdgePropertyBoolean(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jboolean *propertyValue);
int setEdgePropertyByte(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jbyte *propertyValue);
int setEdgePropertyShort(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jshort *propertyValue);
int setEdgePropertyInt(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jint *propertyValue);
int setEdgePropertyLong(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jlong *propertyValue);
int setEdgePropertyFloat(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jfloat *propertyValue);
int setEdgePropertyDouble(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jdouble *propertyValue);
int setEdgePropertyChar(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jchar *propertyValue);
int setEdgePropertyString(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jint propertyValueLength, char *propertyValue);

int setStringIndex(MDB_cursor *indexCursor, long long vertexId, int propertyKeyId, int propertyValueLength, char propertyValue[]);
int setIntIndex(MDB_cursor *indexCursor, long long elementId, int propertyKeyId, int propertyValue);
int addOrUpdateStringIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId,
		int propertyKeyId, int propertyValueLength, char *propertyValue, unsigned char vertex);
int addOrUpdateIntIndexedProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor * vertexCursor, long long elementId, int propertyKeyId,
		int propertyValue, unsigned char vertex);
int deleteStringIndex(GLMDB_env * glmdb_env, MDB_txn * mdbTxn, int propertyKeyId, unsigned char vertex);
int deleteEntryFromStringIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *stringIndexCursor,
		long long elementId, int propertyKeyId);
int deleteEntryFromIntIndex(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, MDB_cursor *vertexCursor, MDB_cursor *intIndexCursor,
		long long elementId, int propertyKeyId);
int reindexProperty(GLMDB_env *glmdb_env, MDB_txn *mdbTxn, int propertyKeyId, int propertyKeyEnum, unsigned char vertex);

int getVertexProperty(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, MDB_val *data);
int removeVertexProperty(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId);
int getEdgeProperty(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, MDB_val *data);
int removeEdgeProperty(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId);
int getVertexPropertyKeys(MDB_cursor *cursor, jlong vertexId, jint *propertyKeyArraySizeC, jint **propertyKeyArrayC);
int getEdgePropertyKeys(MDB_cursor *cursor, jlong edgeId, jint *propertyKeyArraySizeC, jint **propertyKeyArrayC);

int setPropertyKey(GLMDB_env *glmdb_env, MDB_txn * txn, int propertyKeyEnum, int *propertyKeyId, int propertyKeyLength, char propertyKeyC[],
		unsigned char vertex, unsigned char indexed, unsigned char overwrite);
char * propertyTypeEnumToString(int propertyTypeEnum);

int traverseVertexDb(GLMDB_env * glmdb_env, MDB_txn *txn);
int traverseEdgeDb(GLMDB_env * glmdb_env, MDB_txn *txn);
int traverseVertexPropertyKeyDb(GLMDB_env * glmdb_env, MDB_txn *txn);
int traverseEdgePropertyKeyDb(GLMDB_env * glmdb_env, MDB_txn *txn);
int traverseLabelDb(GLMDB_env * glmdb_env, MDB_txn *txn);
int traverseConfigDb(GLMDB_env * glmdb_env, MDB_txn *txn);
int traverseStringIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi);
int traverseIntIndexDb(GLMDB_env * glmdb_env, MDB_txn *txn, MDB_dbi dbi);

int getFirstElementForKeyValueFromStringIndex(MDB_cursor *cursor, int propertyKeyId, int propertyValueLength, char *value,
		long long int *vertexIdResultC);
int getNextElementForKeyValueFromStringIndex(MDB_cursor *cursor, int propertyKeyId, int propertyValueLength, char *value,
		long long int *vertexIdResultC);
int getFirstElementForKeyValueFromIntIndex(MDB_cursor *cursor, int propertyKeyId, int value, long long int *vertexIdResultC);
int getNextElementForKeyValueFromIntIndex(MDB_cursor *cursor, int propertyKeyId, int value, long long int *vertexIdResultC);

void buffer_copy(const void *source, size_t source_pos, void *dest, size_t dest_pos, size_t length);
#ifdef __cplusplus
}
#endif
#endif
