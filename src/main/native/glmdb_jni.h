#include <jni.h>
#include "lmdb.h"

#ifndef _Included_org_glmdb_blueprints_jni_Glmdb
#define _Included_org_glmdb_blueprints_jni_Glmdb
#ifdef __cplusplus
extern "C" {
#endif

typedef struct GLMDB_env {
	MDB_env *env;
	MDB_dbi configDb;
	MDB_dbi vertexDb;
	MDB_dbi edgeDb;
	MDB_dbi propertyKeyDb;
	long idSequence;
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
	char *label;
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
	char *label;
} EdgeData;

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
JNIEXPORT jstring JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1strerror
  (JNIEnv *env, jclass that, jint error);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    glmdb_env_create
 * Signature: (Ljava/lang/String;[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_glmdb_1env_1create(
		JNIEnv * env, jclass that, jstring path, jlongArray pointerArray);

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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1begin
  (JNIEnv *env, jclass that, jlong glmdb_env, jlong parent, jlong flags, jlongArray txn);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_txn_renew
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1renew
  (JNIEnv *env, jclass that, jlong txn);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_txn_commit
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1txn_1commit
  (JNIEnv *env, jclass that, jlong txn);

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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1cursor_1open_1vertex_1db
  (JNIEnv *env, jclass that, jlong txn, jlong glmdb_env, jlongArray cursorArray);

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
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1cursor_1renew
  (JNIEnv *env, jclass that, jlong txn, jlong cursor);

/*
 * Class:     org_glmdb_blueprints_jni_GlmdbJni
 * Method:    mdb_add_vertex
 * Signature: (JJ[J)I
 */
JNIEXPORT jint JNICALL Java_org_glmdb_blueprints_jni_GlmdbJni_mdb_1add_1vertex
  (JNIEnv *env, jclass that, jlong glmdb_env, jlong cursor, jlongArray vertexId);

int openGraph(GLMDB_env **genv, const char *path);
void closeGraph(GLMDB_env *genv);
int addVertex(MDB_cursor *cursor, MDB_dbi vertexDb, long vertexId, MDB_val *vertexKey);
int compareVertexDbId(const MDB_val *key1, const MDB_val *key2);
int compareEdgeDbId(const MDB_val *key1, const MDB_val *key2);
void printDbStats(MDB_env *env, MDB_dbi vertexDb, char *name);

#ifdef __cplusplus
}
#endif
#endif
