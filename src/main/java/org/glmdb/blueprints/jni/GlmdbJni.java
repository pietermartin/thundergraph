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

//    /**
//     * <a href="http://symas.com/mdb/doc/group__mdb.html#structMDB__envinfo">details</a>
//     */
//    static public class MDB_envinfo {
//        public long me_mapaddr;
//        public long me_mapsize;
//        public long me_last_pgno;
//        public long me_last_txnid;
//        public long me_maxreaders;
//        public long me_numreaders;
//
//        @Override
//        public String toString() {
//            return "{" +
//                    "me_last_pgno=" + me_last_pgno +
//                    ", me_mapaddr=" + me_mapaddr +
//                    ", me_mapsize=" + me_mapsize +
//                    ", me_last_txnid=" + me_last_txnid +
//                    ", me_maxreaders=" + me_maxreaders +
//                    ", me_numreaders=" + me_numreaders +
//                    '}';
//        }
//    }
//
//    /**
//     * <a href="http://symas.com/mdb/doc/group__mdb.html#structMDB_stat">details</a>
//     */
//    public static class MDB_stat {
//        public long ms_psize;
//        public long ms_depth;
//        public long ms_branch_pages;
//        public long ms_leaf_pages;
//        public long ms_overflow_pages;
//        public long ms_entries;
//
//        @Override
//        public String toString() {
//            return "{" +
//                    "ms_branch_pages=" + ms_branch_pages +
//                    ", ms_psize=" + ms_psize +
//                    ", ms_depth=" + ms_depth +
//                    ", ms_leaf_pages=" + ms_leaf_pages +
//                    ", ms_overflow_pages=" + ms_overflow_pages +
//                    ", ms_entries=" + ms_entries +
//                    '}';
//        }
//    }

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

    //Glmdb error codes
    static public int GLMDB_WRITE_NULL = -30599;
    static public int GLMDB_END_OF_EDGES = -30598;

    public static final native int mdb_env_get_path(long glmdb_env, byte[][] path);

    public static final native String mdb_strerror(int err);

    public static final native int print_db(long glmdb_env, long txn, int dbEnum);

    public static final native int glmdb_env_create(String path, long[] env);

    public static final native void glmdb_env_close(long glmdb_env);

    public static final native int mdb_txn_begin(long glmdb_env, long parent, long flags, long[] txn);

    public static final native int mdb_txn_renew(long txn);

    public static final native int mdb_txn_commit(long glmdb_env, long txn, boolean readOnly);

    public static final native void mdb_txn_reset(long txn);

    public static final native void mdb_txn_abort(long glmdb_env, long txn);

    public static final native void mdb_cursor_close(long cursor);

    public static final native int mdb_cursor_renew(long txn, long cursor);

    public static final native int mdb_cursor_open_vertex_db(long txn, long glmdb_env, long[] cursor);

    public static final native int mdb_cursor_open_property_key_db(long txn, long glmdb_env, long[] cursor, boolean vertex);

    public static final native int mdb_cursor_open_label_db(long txn, long glmdb_env, long[] cursor);

    //Direction here must be OUT or IN, not both as it represent the direction of the current edge
    public static final native int mdb_cursor_open_and_position_on_edge_vertex_db(long txn, long glmdb_env, long vertexId, int direction, int labelId, long edgeId, long[] cursor);

    public static final native int mdb_cursor_open_edge_db(long txn, long glmdb_env, long[] cursor);

    public static final native int mdb_add_vertex(long glmdb_env, long cursor, long vertexId[]);

    public static final native int mdb_add_edge(long glmdb_env, long txn, long outVertexId, long inVertexId, int labelId, long edgeId[]);

    public static final native int mdb_set_property_boolean(long cursor, long elementId, int propertykeyId, boolean value, boolean vertexProperty);

    public static final native int mdb_set_property_byte(long cursor, long elementId, int propertykeyId, byte value, boolean vertexProperty);

    public static final native int mdb_set_property_short(long cursor, long elementId, int propertykeyId, short value, boolean vertexProperty);

    public static final native int mdb_set_property_int(long cursor, long elementId, int propertykeyId, int value, boolean vertexProperty);

    public static final native int mdb_set_property_long(long cursor, long elementId, int propertykeyId, long value, boolean vertexProperty);

    public static final native int mdb_set_property_float(long cursor, long elementId, int propertykeyId, float value, boolean vertexProperty);

    public static final native int mdb_set_property_double(long cursor, long elementId, int propertykeyId, double value, boolean vertexProperty);

    public static final native int mdb_set_property_char(long cursor, long elementId, int propertykeyId, char value, boolean vertexProperty);

    public static final native int mdb_set_property_string(long glmdb_env, long txn, long cursor, long elementId, int propertykeyId, String value, boolean vertexProperty, boolean indexed);

    public static final native int mdb_get_property_array(long cursor, long elementId, int propertyKeyId, byte[][] value, boolean vertexProperty);

    public static final native int mdb_del_property(long cursor, long elementId, int propertyKeyId, byte[][] value, boolean vertexProperty);

    public static final native int mdb_get_property_keys(long cursor, long elementId, int[][] propertyKeyIds, boolean vertexProperty);

    public static final native int mdb_set_propertykey(long glmdb_env, long txn, String propertyKey, int propertyTypeEnum, int[] propertyKeyId, boolean vertex, boolean indexed, boolean overwrite);

    public static final native int mdb_get_first_property_key(long cursor, int propertyKeyIdArray[], int propertyTypeEnumArray[], boolean propertyIndexedArray[], byte[][] propertyKeyArray);

    public static final native int mdb_get_next_property_key(long cursor, int propertyKeyIdArray[], int propertyTypeEnumArray[], boolean propertyIndexedArray[], byte[][] propertyKeyArray);

    public static final native int mdb_get_first_label(long cursor, int labelIdArray[], byte[][] labelArray);

    public static final native int mdb_get_next_label(long cursor, int labelIdArray[], byte[][] labelArray);

    public static final native int mdb_set_label(long glmdb_env, long txn, String label, int[] labelId);

    public static final native int mdb_get_vertex(long cursor, long vertexId, long vertexIdResult[]);

    public static final native int mdb_remove_vertex(long glmdb_env, long txn, long vertexId);

    public static final native int mdb_get_first_vertex(long cursor, long vertexIdResult[]);

    public static final native int mdb_get_next_vertex(long cursor, long previousId, long vertexIdResult[]);

    public static final native int mdb_get_first_vertex_for_key_value(long cursor, long vertexIdResult[], int key, byte[] value);

    public static final native int mdb_get_next_vertex_for_key_value(long cursor, long vertexIdResult[], int key, byte[] value);

    public static final native int mdb_get_edge(long cursor, long edgeId, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_remove_edge(long glmdb_env, long txn, long edgeId);

    public static final native int mdb_get_first_edge(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_next_edge(long cursor, long previousEdgeId, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_first_edge_for_key_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, byte[] value);

    public static final native int mdb_get_next_edge_for_key_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, byte[] value);

    public static final native int mdb_get_first_edge_from_vertex(long cursor, int direction, int labelId, long fromVertexId, long edgeIdResult[], long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_next_edge_from_vertex(long cursor, int direction, int labelId, long fromVertexId, long edgeIdResult[], long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_first_edge_from_vertex_all_labels(long cursor, int direction, long fromVertexId, int labelId[], long edgeIdResult[], long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_next_edge_from_vertex_all_labels(long cursor, int direction, long fromVertexId, int labelId[], long edgeIdResult[], long[] outVertexId, long[] inVertexId);

}
