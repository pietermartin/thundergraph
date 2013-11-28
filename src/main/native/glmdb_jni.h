#include <jni.h>
#include "lmdb.h"

#ifndef _Included_org_glmdb_blueprints_jni_Glmdb
#define _Included_org_glmdb_blueprints_jni_Glmdb
#ifdef __cplusplus
extern "C" {
#endif

//Data types
#define GLMDB_BOOLEAN	0
#define GLMDB_BYTE 1
#define GLMDB_SHORT 2
#define GLMDB_INT 3
#define GLMDB_LONG 4
#define GLMDB_DOUBLE 5
#define GLMDB_CHAR 6
#define GLMDB_STRING 7
#define GLMDB_ARRAY_BOOLEAN 8
#define GLMDB_ARRAY_BYTE 9
#define GLMDB_ARRAY_SHORT 10
#define GLMDB_ARRAY_INT 11
#define GLMDB_ARRAY_LONG 12
#define GLMDB_ARRAY_DOUBLE 13
#define GLMDB_ARRAY_CHAR 14
#define GLMDB_ARRAY_STRING 15

/** @defgroup  errors	Return Codes
 *
 *	lmdb uses -30600 to -30800, we'll go under them
 *	@{
 */
/** key/data pair already exists */
#define GLMDB_WRITE_NULL	(-30599)
#define GLMDB_END_OF_EDGES	(-30598)

typedef struct GLMDB_env {
	MDB_env *env;
	MDB_dbi configDb;
	MDB_dbi vertexDb;
	MDB_dbi edgeDb;
	MDB_dbi propertyKeyDb;
	MDB_dbi labelDb;
	jlong vertexIdSequence;
	jlong edgeIdSequence;
	jint propertyKeyIdSequence;
	jint labelIdSequence;
	char *path;
} GLMDB_env;

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
	DOUBLE,
	CHAR,
	STRING,
	ARRAY_BOOLEAN,
	ARRAY_BYTE,
	ARRAY_SHORT,
	ARRAY_INT,
	ARRAY_LONG,
	ARRAY_DOUBLE,
	ARRAY_CHAR,
	ARRAY_STRING
};

typedef struct PropertyKeyStruct {
	jint propertyKeyId;
	enum PropertyTypeEnum type;
} PropertyKeyStruct;

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    printVertexDb
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_printVertexDb(JNIEnv *env, jclass that, jlong glmdbEnv);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_init
(JNIEnv *env, jclass that);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_strerror
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1strerror(JNIEnv *env, jclass that, jint error);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    glmdb_env_create
 * Signature: (Ljava/lang/String;[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_glmdb_1env_1create(JNIEnv * env, jclass that, jstring path,
		jlongArray pointerArray);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    glmdb_env_close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_glmdb_1env_1close
(JNIEnv *env, jclass that, jlong glmdbEnv);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_txn_begin
 * Signature: (JJJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1begin(JNIEnv *env, jclass that, jlong glmdb_env, jlong parent,
		jlong flags, jlongArray txn);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_txn_renew
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1renew(JNIEnv *env, jclass that, jlong txn);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_txn_commit
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1commit(JNIEnv *env, jclass that, jlong txn);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_txn_reset
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1reset
(JNIEnv *env, jclass that, jlong txn);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_txn_abort
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1abort
(JNIEnv *env, jclass that, jlong txn);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_cursor_open_vertex_db
 * Signature: (JJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1cursor_1open_1vertex_1db(JNIEnv *env, jclass that, jlong txn,
		jlong glmdb_env, jlongArray cursorArray);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_cursor_open_edge_db
 * Signature: (JJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1cursor_1open_1edge_1db(JNIEnv *env, jclass that, jlong txn,
		jlong glmdb_env, jlongArray cursorArray);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJniint
 * Method:    mdb_cursor_close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1cursor_1close
(JNIEnv *env, jclass that, jlong cursor);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_cursor_renew
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1cursor_1renew(JNIEnv *env, jclass that, jlong txn, jlong cursor);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_add_vertex
 * Signature: (JJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1add_1vertex(JNIEnv *env, jclass that, jlong glmdb_env, jlong cursor,
		jlongArray vertexId);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_add_edge
 * Signature: (JJJJI[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1add_1edge(JNIEnv *env, jclass that, jlong glmdb_env, jlong txn,
		jlong outVertexId, jlong inVertexId, jint labelId, jlongArray edgeId);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_boolean
 * Signature: (JJIZZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1boolean(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jboolean value, jboolean vertexKey);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_byte
 * Signature: (JJIBZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1byte(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jbyte value, jboolean vertexKey);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_short
 * Signature: (JJISZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1short(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jshort value, jboolean vertexKey);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_int
 * Signature: (JJIIZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1int(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jint value, jboolean vertexKey);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_long
 * Signature: (JJIJZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1long(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jlong value, jboolean vertexKey);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_float
 * Signature: (JJIFZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1float(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jfloat value, jboolean vertexKey);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_double
 * Signature: (JJIDZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1double(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jdouble value, jboolean vertexKey);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_char
 * Signature: (JJICZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1char(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jchar value, jboolean vertexKey);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_string
 * Signature: (JJILjava/lang/String;Z)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1string(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jstring value, jboolean vertexKey);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_property_array
 * Signature: (JJI[[BZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1property_1array(JNIEnv *env, jclass that, jlong cursor,
		jlong elementId, jint propertyKeyId, jobjectArray value, jboolean vertexKey);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_property
 * Signature: (JJILorg/glmdb/blueprints/jni/Value;)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1property(JNIEnv *env, jclass that, jlong cursor, jlong vertexId,
		jint propertyKeyId, jobject value);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_propertykey
 * Signature: (JJLjava/lang/String;I[I)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1propertykey(JNIEnv *env, jclass that, jlong glmdb_env, jlong txn,
		jstring propertyKey, jint propertyKeyEnum, jintArray propertyKeyIdArray);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_label
 * Signature: (JJLjava/lang/String;[I)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1label(JNIEnv *env, jclass that, jlong glmdb_env, jlong txn,
		jstring label, jintArray labelIdArray);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_vertex
 * Signature: (JJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1vertex(JNIEnv *env, jclass that, jlong cursor, jlong vertexId,
		jlongArray vertexIdResult);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_first_vertex
 * Signature: (J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1first_1vertex(JNIEnv *env, jclass that, jlong cursor,
		jlongArray vertexIdResult);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_next_vertex
 * Signature: (J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1next_1vertex(JNIEnv *env, jclass that, jlong cursor,
		jlongArray vertexIdResult);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_first_vertex_for_key_value
 * Signature: (J[JILjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1first_1vertex_1for_1key_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKey, jobject value);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_first_vertex_for_key_value
 * Signature: (J[JI[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1first_1vertex_1for_1key_1value(JNIEnv *env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKey, jbyteArray value);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_next_vertex_for_key_value
 * Signature: (J[JI[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1next_1vertex_1for_1key_1value(JNIEnv * env, jclass that,
		jlong cursor, jlongArray vertexIdResult, jint propertyKey, jbyteArray value);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_edge
 * Signature: (JJ[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1edge(JNIEnv *env, jclass that, jlong cursor, jlong edgeId,
		jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_first_edge
 * Signature: (J[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1first_1edge(JNIEnv * env, jclass that, jlong cursor,
		jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_next_edge
 * Signature: (J[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1next_1edge(JNIEnv *env, jclass that, jlong cursor,
		jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_first_edge_for_key_value
 * Signature: (J[J[I[J[JI[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1first_1edge_1for_1key_1value(JNIEnv *env, jclass that, jlong cursor,
		jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint propertyKey, jbyteArray value);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_next_edge_for_key_value
 * Signature: (J[J[I[J[JI[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1next_1edge_1for_1key_1value(JNIEnv *env, jclass that, jlong cursor,
		jlongArray edgeIdResult, jintArray label, jlongArray outVertexId, jlongArray inVertexId, jint propertyKey, jbyteArray value);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_first_edge_from_vertex
 * Signature: (JIJ[J[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1first_1edge_1from_1vertex(JNIEnv * env, jclass that, jlong cursor,
		jint labelId, jlong fromVertexId, jlongArray edgeIdResult, jlongArray outVertexId, jlongArray inVertexId);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_next_edge_from_vertex
 * Signature: (JIJ[J[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1next_1edge_1from_1vertex(JNIEnv *env, jclass that, jlong cursor,
		jint labelId, jlong fromVertexId, jlongArray edgeIdResult, jlongArray outVertexId, jlongArray inVertexId);

void printRecord(MDB_val key, MDB_val data);
void printKey(MDB_val key);

void initVertexDbId(VertexDbId *vertexDbId);
void initEdgeDbId(EdgeDbId *edgeDbId);
void initEdgeData(EdgeData *edgeData);

int openGraph(GLMDB_env **genv, const char *path);
void closeGraph(GLMDB_env *genv);
int addVertex(MDB_cursor *cursor, MDB_dbi vertexDb, jlong vertexId, MDB_val *vertexKey);
int getVertex(MDB_cursor *cursor, jlong vertexId, MDB_val *vertexKey);
int getFirstEdgefromVertex(MDB_cursor *cursor, jint labelId, jlong fromVertexId, jlong *edgeIdResultC, jlong *outVertexIdC,
		jlong *inVertexIdC);
int getNextEdgefromVertex(MDB_cursor *cursor, jint labelId, jlong fromVertexId, jlong *edgeIdResultC, jlong *outVertexIdC,
		jlong *inVertexIdC);

int addEdge(MDB_txn *txn, MDB_dbi vertexDb, MDB_dbi edgeDb, jlong edgeId, jint labelId, jlong vertexOutId, jlong vertexInId);
int addEdgeToEdgeDb(MDB_txn *txn, MDB_dbi edgeDb, jlong edgeId, jint labelId, jlong vertexOutId, jlong vertexInId);
int addEdgeToVertexDb(MDB_txn *txn, MDB_dbi vertexDb, jlong edgeId, jint labelId, jlong vertexOutId, jlong vertexInId);

int compareVertexDbId(const MDB_val *key1, const MDB_val *key2);
int compareEdgeDbId(const MDB_val *key1, const MDB_val *key2);
void printDbStats(MDB_env *env, MDB_dbi vertexDb, char *name);
int setVertexPropertyBoolean(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jboolean *propertyValue);
int setVertexPropertyByte(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jbyte *propertyValue);
int setVertexPropertyShort(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jshort *propertyValue);
int setVertexPropertyInt(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jint *propertyValue);
int setVertexPropertyLong(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jlong *propertyValue);
int setVertexPropertyFloat(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jfloat *propertyValue);
int setVertexPropertyDouble(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jdouble *propertyValue);
int setVertexPropertyChar(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, jchar *propertyValue);
int setVertexPropertyString(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, char *propertyValue);

int setEdgePropertyBoolean(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jboolean *propertyValue);
int setEdgePropertyByte(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jbyte *propertyValue);
int setEdgePropertyShort(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jshort *propertyValue);
int setEdgePropertyInt(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jint *propertyValue);
int setEdgePropertyLong(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jlong *propertyValue);
int setEdgePropertyFloat(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jfloat *propertyValue);
int setEdgePropertyDouble(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jdouble *propertyValue);
int setEdgePropertyChar(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, jchar *propertyValue);
int setEdgePropertyString(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, char *propertyValue);

int getVertexProperty(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, MDB_val *data);
int getEdgeProperty(MDB_cursor *cursor, jlong edgeId, jint propertyKeyId, MDB_val *data);

int traverseDb(MDB_env *env, MDB_dbi dbi);

void buffer_copy(const void *source, size_t source_pos, void *dest, size_t dest_pos, size_t length);
#ifdef __cplusplus
}
#endif
#endif
