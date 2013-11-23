package org.glmdb.blueprints.jni;

/**
 * Date: 2013/11/17
 * Time: 4:28 PM
 */
public class GlmdbJni {

    static {
        try {
            LibraryLoader.loadLibrary("glmdb_jni");
        } catch (Exception e) {
            System.err.println(e);
            System.exit(1);
        }
        init();
    }

    /**
     * This loads all lmdb's constants
     */
    private static final native void init();

    ///////////////////////////////////////////////////////////////////////
    //
    // The lmdb API
    //
    ///////////////////////////////////////////////////////////////////////

    //====================================================//
    // Version Info
    //====================================================//
    static public int MDB_VERSION_MAJOR;
    static public int MDB_VERSION_MINOR;
    static public int MDB_VERSION_PATCH;
    static public int MDB_VERSION_FULL;

    static long MDB_VERSION_DATE;
    static long MDB_VERSION_STRING;

    //====================================================//
    // Environment Flags
    //====================================================//
    static public int MDB_FIXEDMAP;
    static public int MDB_NOSUBDIR;
    static public int MDB_NOSYNC;
    static public int MDB_RDONLY;
    static public int MDB_NOMETASYNC;
    static public int MDB_WRITEMAP;
    static public int MDB_MAPASYNC;
    static public int MDB_NOTLS;

    //====================================================//
    // Database Flags
    //====================================================//
    static public int MDB_REVERSEKEY;
    static public int MDB_DUPSORT;
    static public int MDB_INTEGERKEY;
    static public int MDB_DUPFIXED;
    static public int MDB_INTEGERDUP;
    static public int MDB_REVERSEDUP;
    static public int MDB_CREATE;

    //====================================================//
    // Write Flags
    //====================================================//
    static public int MDB_NOOVERWRITE;
    static public int MDB_NODUPDATA;
    static public int MDB_CURRENT;
    static public int MDB_RESERVE;
    static public int MDB_APPEND;
    static public int MDB_APPENDDUP;
    static public int MDB_MULTIPLE;

    //====================================================//
    // enum MDB_cursor_op:
    //====================================================//
    static public int MDB_FIRST;
    static public int MDB_FIRST_DUP;
    static public int MDB_GET_BOTH;
    static public int MDB_GET_BOTH_RANGE;
    static public int MDB_GET_CURRENT;
    static public int MDB_GET_MULTIPLE;
    static public int MDB_LAST;
    static public int MDB_LAST_DUP;
    static public int MDB_NEXT;
    static public int MDB_NEXT_DUP;
    static public int MDB_NEXT_MULTIPLE;
    static public int MDB_NEXT_NODUP;
    static public int MDB_PREV;
    static public int MDB_PREV_DUP;
    static public int MDB_PREV_NODUP;
    static public int MDB_SET;
    static public int MDB_SET_KEY;
    static public int MDB_SET_RANGE;

    //====================================================//
    // Return Codes
    //====================================================//
    static public int EINVAL;
    static public int EACCES;
    static public int MDB_SUCCESS;
    static public int MDB_KEYEXIST;
    static public int MDB_NOTFOUND;
    static public int MDB_PAGE_NOTFOUND;
    static public int MDB_CORRUPTED;
    static public int MDB_PANIC;
    static public int MDB_VERSION_MISMATCH;
    static public int MDB_INVALID;
    static public int MDB_MAP_FULL;
    static public int MDB_DBS_FULL;
    static public int MDB_READERS_FULL;
    static public int MDB_TLS_FULL;
    static public int MDB_TXN_FULL;
    static public int MDB_CURSOR_FULL;
    static public int MDB_PAGE_FULL;
    static public int MDB_MAP_RESIZED;
    static public int MDB_INCOMPATIBLE;
    static public int MDB_BAD_RSLOT;
    static public int MDB_LAST_ERRCODE;

    public static final native String mdb_strerror(int err);

    public static final native int glmdb_env_create(String path, long[] env);

    public static final native void glmdb_env_close(long glmdb_env);

    public static final native int mdb_txn_begin(long glmdb_env, long parent, long flags, long[] txn);

    public static final native int mdb_txn_renew(long txn);

    public static final native int mdb_txn_commit(long txn);

    public static final native void mdb_txn_reset(long txn);

    public static final native void mdb_txn_abort(long txn);

    public static final native void mdb_cursor_close(long cursor);

    public static final native int mdb_cursor_renew(long txn, long cursor);

    public static final native int mdb_cursor_open_vertex_db(long txn, long glmdb_env, long[] cursor);

    public static final native int mdb_cursor_open_edge_db(long txn, long glmdb_env, long[] cursor);

//    public static final native int mdb_cursor_open_propertykey_db(long txn, long glmdb_env, long[] cursor);

    public static final native int mdb_add_vertex(long glmdb_env, long cursor, long vertexId[]);

    public static final native int mdb_add_edge(long glmdb_env, long txn, long outVertexId, long inVertexId, int labelId, long edgeId[]);

    //BOOLEAN, BYTE, SHORT, INT, LONG, DOUBLE, CHAR, STRING,
    public static final native int mdb_set_property_boolean(long cursor, long vertexId, int propertykeyId, boolean value);

    public static final native int mdb_set_property_byte(long cursor, long vertexId, int propertykeyId, byte value);

    public static final native int mdb_set_property_short(long cursor, long vertexId, int propertykeyId, short value);

    public static final native int mdb_set_property_int(long cursor, long vertexId, int propertykeyId, int value);

    public static final native int mdb_set_property_long(long cursor, long vertexId, int propertykeyId, long value);

    public static final native int mdb_set_property_float(long cursor, long vertexId, int propertykeyId, float value);

    public static final native int mdb_set_property_double(long cursor, long vertexId, int propertykeyId, double value);

    public static final native int mdb_set_property_char(long cursor, long vertexId, int propertykeyId, char value);

    public static final native int mdb_set_property_string(long cursor, long vertexId, int propertykeyId, String value);

    public static final native int mdb_get_property_array(long cursor, long vertexId, int propertyKeyId, byte[][] value);

    public static final native int mdb_set_propertykey(long glmdb_env, long txn, String propertyKey, int propertyTypeEnum, int[] propertyKeyId);

    public static final native int mdb_set_label(long glmdb_env, long txn, String label, int[] labelId);

    public static final native int mdb_get_vertex(long cursor, long vertexId, long vertexIdResult[]);

    public static final native int mdb_get_edge(long cursor, long edgeId, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

}
