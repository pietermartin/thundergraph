package org.glmdb.blueprints.jni;

/**
 * Date: 2013/11/19
 * Time: 7:20 PM
 */
public class GLMDBException extends RuntimeException {

    public static final int EINVAL = GlmdbJni.EINVAL;
    public static final int EACCES = GlmdbJni.EACCES;
    public static final int KEYEXIST = GlmdbJni.MDB_KEYEXIST;
    public static final int NOTFOUND = GlmdbJni.MDB_NOTFOUND;
    public static final int PAGE_NOTFOUND = GlmdbJni.MDB_PAGE_NOTFOUND;
    public static final int CORRUPTED = GlmdbJni.MDB_CORRUPTED;
    public static final int PANIC = GlmdbJni.MDB_PANIC;
    public static final int VERSION_MISMATCH = GlmdbJni.MDB_VERSION_MISMATCH;
    public static final int INVALID = GlmdbJni.MDB_INVALID;
    public static final int MAP_FULL = GlmdbJni.MDB_MAP_FULL;
    public static final int DBS_FULL = GlmdbJni.MDB_DBS_FULL;
    public static final int READERS_FULL = GlmdbJni.MDB_READERS_FULL;
    public static final int TLS_FULL = GlmdbJni.MDB_TLS_FULL;
    public static final int TXN_FULL = GlmdbJni.MDB_TXN_FULL;
    public static final int CURSOR_FULL = GlmdbJni.MDB_CURSOR_FULL;
    public static final int PAGE_FULL = GlmdbJni.MDB_PAGE_FULL;
    public static final int MAP_RESIZED = GlmdbJni.MDB_MAP_RESIZED;
    public static final int INCOMPATIBLE = GlmdbJni.MDB_INCOMPATIBLE;
    public static final int BAD_RSLOT = GlmdbJni.MDB_BAD_RSLOT;

    int errorCode;

    public GLMDBException() {
    }

    public GLMDBException(String message) {
        super(message);
    }

    public GLMDBException(String message, int errorCode) {
        super(message);
        this.errorCode = errorCode;
    }

    public int getErrorCode() {
        return errorCode;
    }

    public void setErrorCode(int errorCode) {
        this.errorCode = errorCode;
    }

}
