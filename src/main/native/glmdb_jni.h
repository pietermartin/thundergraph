#include <jni.h>
#include "lmdb.h"

#ifndef _Included_org_glmdb_blueprints_jni_Glmdb
#define _Included_org_glmdb_blueprints_jni_Glmdb
#ifdef __cplusplus
extern "C" {
#endif

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

typedef struct GLMDB_env {
	MDB_env *env;
	MDB_dbi configDb;
	MDB_dbi vertexDb;
	MDB_dbi edgeDb;
	MDB_dbi propertyKeyDb;
	MDB_dbi labelDb;
	long vertexIdSequence;
	long edgeIdSequence;
	long propertyKeyIdSequence;
	long labelIdSequence;
	char *path;
} GLMDB_env;

enum VertexCoreOrPropertyEnum {
	VCORE, VPROPERTY_KEY, OUTLABEL, INLABEL
};

enum EdgeCoreOrPropertyEnum {
	ECORE, EPROPERTY_KEY
};

typedef struct VertexDbId {
	long vertexId;
	enum VertexCoreOrPropertyEnum coreOrPropertyEnum;
	int propertykeyId;
	int labelId;
	long edgeId;
} VertexDbId;

typedef struct EdgeDbId {
	long edgeId;
	enum EdgeCoreOrPropertyEnum coreOrPropertyEnum;
	long propertykeyId;
} EdgeDbId;

typedef struct EdgeData {
	long vertexInId;
	long vertexOutId;
	int labelId;
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
	int propertyKeyId;
	enum PropertyTypeEnum type;
} PropertyKeyStruct;

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
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
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
 * Signature: (JJIZ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1boolean(JNIEnv *env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jboolean value);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_byte
 * Signature: (JJIB)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1byte(JNIEnv *env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jbyte value);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_short
 * Signature: (JJIS)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1short(JNIEnv *env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jshort value);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_int
 * Signature: (JJII)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1int(JNIEnv * env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jint value);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_long
 * Signature: (JJIJ)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1long(JNIEnv * env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jlong value);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_float
 * Signature: (JJIF)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1float(JNIEnv *env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jfloat value);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_double
 * Signature: (JJID)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1double(JNIEnv *env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jdouble value);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_char
 * Signature: (JJIC)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1char(JNIEnv *env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jchar value);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_set_property_string
 * Signature: (JJILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1set_1property_1string(JNIEnv *env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jstring value);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_get_property_array
 * Signature: (JJI[[B)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1property_1array(JNIEnv *env, jclass that, jlong cursor,
		jlong vertexId, jint propertyKeyId, jobjectArray value);

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
 * Method:    mdb_get_edge
 * Signature: (JJ[J[I[J[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1get_1edge(JNIEnv *env, jclass that, jlong cursor, jlong edgeId,
		jlongArray edgeIdResult, jintArray labelId, jlongArray outVertexId, jlongArray inVertexId);

int openGraph(GLMDB_env **genv, const char *path);
void closeGraph(GLMDB_env *genv);
int addVertex(MDB_cursor *cursor, MDB_dbi vertexDb, long vertexId, MDB_val *vertexKey);

int addEdge(MDB_txn *txn, MDB_dbi vertexDb, MDB_dbi edgeDb, int edgeId, int labelId, int vertexOutId, int vertexInId, MDB_val *edgeKey);
int addEdgeToEdgeDb(MDB_txn *txn, MDB_dbi edgeDb, int edgeId, int labelId, int vertexInId, int vertexOutId, MDB_val *edgeKey);
int addEdgeToVertexDb(MDB_txn *txn, MDB_dbi vertexDb, int edgeId, int labelId, int vertexInId, int vertexOutId, MDB_val *edgeVertexDbKey);

int compareVertexDbId(const MDB_val *key1, const MDB_val *key2);
int compareEdgeDbId(const MDB_val *key1, const MDB_val *key2);
void printDbStats(MDB_env *env, MDB_dbi vertexDb, char *name);
int setVertexPropertyBoolean(MDB_cursor *cursor, long vertexId, int propertyKeyId, jboolean *propertyValue);
int setVertexPropertyByte(MDB_cursor *cursor, long vertexId, int propertyKeyId, jbyte *propertyValue);

int setVertexPropertyShort(MDB_cursor *cursor, long vertexId, int propertyKeyId, jshort *propertyValue);
int setVertexPropertyInt(MDB_cursor *cursor, long vertexId, int propertyKeyId, jint *propertyValue);

int setVertexPropertyLong(MDB_cursor *cursor, long vertexId, int propertyKeyId, jlong *propertyValue);
int setVertexPropertyFloat(MDB_cursor *cursor, long vertexId, int propertyKeyId, jfloat *propertyValue);
int setVertexPropertyDouble(MDB_cursor *cursor, long vertexId, int propertyKeyId, jdouble *propertyValue);
int setVertexPropertyChar(MDB_cursor *cursor, long vertexId, int propertyKeyId, jchar *propertyValue);

int setVertexPropertyString(MDB_cursor *cursor, long vertexId, int propertyKeyId, char *propertyValue);
int getVertexProperty(MDB_cursor *cursor, long vertexId, int propertyKeyId, MDB_val *data);

void buffer_copy(const void *source, size_t source_pos, void *dest, size_t dest_pos, size_t length);
#ifdef __cplusplus
}
#endif
#endif
