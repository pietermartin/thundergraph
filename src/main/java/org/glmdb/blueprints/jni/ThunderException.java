package org.glmdb.blueprints.jni;

/**
 * Date: 2013/11/19
 * Time: 7:20 PM
 */
public class ThunderException extends RuntimeException {

    public static final int EINVAL = ThunderJni.EINVAL;
    public static final int EACCES = ThunderJni.EACCES;
    public static final int KEYEXIST = ThunderJni.MDB_KEYEXIST;
    public static final int NOTFOUND = ThunderJni.MDB_NOTFOUND;
    public static final int PAGE_NOTFOUND = ThunderJni.MDB_PAGE_NOTFOUND;
    public static final int CORRUPTED = ThunderJni.MDB_CORRUPTED;
    public static final int PANIC = ThunderJni.MDB_PANIC;
    public static final int VERSION_MISMATCH = ThunderJni.MDB_VERSION_MISMATCH;
    public static final int INVALID = ThunderJni.MDB_INVALID;
    public static final int MAP_FULL = ThunderJni.MDB_MAP_FULL;
    public static final int DBS_FULL = ThunderJni.MDB_DBS_FULL;
    public static final int READERS_FULL = ThunderJni.MDB_READERS_FULL;
    public static final int TLS_FULL = ThunderJni.MDB_TLS_FULL;
    public static final int TXN_FULL = ThunderJni.MDB_TXN_FULL;
    public static final int CURSOR_FULL = ThunderJni.MDB_CURSOR_FULL;
    public static final int PAGE_FULL = ThunderJni.MDB_PAGE_FULL;
    public static final int MAP_RESIZED = ThunderJni.MDB_MAP_RESIZED;
    public static final int INCOMPATIBLE = ThunderJni.MDB_INCOMPATIBLE;
    public static final int BAD_RSLOT = ThunderJni.MDB_BAD_RSLOT;

    int errorCode;

    public ThunderException() {
    }

    public ThunderException(String message) {
        super(message);
    }

    public ThunderException(String message, int errorCode) {
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
