package org.glmdb.blueprints.jni;

import java.nio.ByteBuffer;

/**
 * Date: 2013/11/17
 * Time: 4:28 PM
 */
public class ThunderJni {

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

    //Thunder error codes
    static public int GLMDB_WRITE_NULL = -30599;
    static public int GLMDB_END_OF_EDGES = -30598;

    public static final native int mdb_env_get_path(long glmdb_env, byte[][] path);

    public static final native String mdb_strerror(int err);

    public static final native int print_db(long glmdb_env, long txn, int dbEnum);

    public static final native int mdb_stat(long glmdb_env, long txn, int dbEnum, int ms_psize[], int ms_depth[], int ms_branch_pages[], int ms_leaf_pages[], int ms_overflow_pages[], int ms_entries[]);

    public static final native int glmdb_env_create(String path, long[] env);

    public static final native void glmdb_env_close(long glmdb_env);

    public static final native int mdb_txn_begin(long glmdb_env, long parent, long flags, long[] txn);

    public static final native int mdb_txn_renew(long txn);

    public static final native int mdb_txn_commit(long glmdb_env, long txn, boolean readOnly);

    public static final native void mdb_txn_reset(long txn);

    public static final native void mdb_txn_abort(long glmdb_env, long txn);

    public static final native void mdb_cursor_close(long cursor);

    public static final native int mdb_cursor_renew(long txn, long cursor);

    public static final native int mdb_cursor_open(long txn, long glmdb_env, int dbEnum, long[] cursor);

    //Direction here must be OUT or IN, not both as it represent the direction of the current edge
    public static final native int mdb_cursor_open_and_position_on_edge_vertex_db(long txn, long glmdb_env, long vertexId, int direction, int labelId, long edgeId, long[] cursor);

    public static final native int mdb_cursor_open_and_position_on_vertex_vertex_db(long txn, long glmdb_env, long vertexId, long[] cursor);

    public static final native int mdb_cursor_open_and_position_on_edge_edge_db(long txn, long glmdb_env, long edgeId, int propertyKeyId, long[] cursor);

    public static final native int mdb_add_vertex(long glmdb_env, long cursor, long vertexId[]);

    public static final native int mdb_add_edge(long glmdb_env, long txn, long outVertexId, long inVertexId, int labelId, long edgeId[]);




    //setters
    public static final native int mdb_set_property_string(long glmdb_env, long txn, long cursor, long elementId, int propertykeyId, String value, boolean vertexProperty, boolean indexed);

    public static final native int mdb_set_property_boolean(long glmdb_env, long txn, long cursor, long elementId, int propertykeyId, boolean value, boolean vertexProperty, boolean indexed);

    public static final native int mdb_set_property_byte(long glmdb_env, long txn, long cursor, long elementId, int propertykeyId, byte value, boolean vertexProperty, boolean indexed);

    public static final native int mdb_set_property_short(long glmdb_env, long txn, long cursor, long elementId, int propertykeyId, short value, boolean vertexProperty, boolean indexed);

    public static final native int mdb_set_property_int(long glmdb_env, long txn, long cursor, long elementId, int propertykeyId, int value, boolean vertexProperty, boolean indexed);

    public static final native int mdb_set_property_long(long glmdb_env, long txn, long cursor, long elementId, int propertykeyId, long value, boolean vertexProperty, boolean indexed);

    public static final native int mdb_set_property_float(long glmdb_env, long txn, long cursor, long elementId, int propertykeyId, float value, boolean vertexProperty, boolean indexed);

    public static final native int mdb_set_property_double(long glmdb_env, long txn, long cursor, long elementId, int propertykeyId, double value, boolean vertexProperty, boolean indexed);

    public static final native int mdb_set_property_char(long glmdb_env, long txn, long cursor, long elementId, int propertykeyId, char value, boolean vertexProperty, boolean indexed);


    public static final native int mdb_get_property_array(long cursor, long elementId, int propertyKeyId, byte[][] value, boolean vertexProperty);

    public static final native int mdb_del_property(long cursor, long elementId, int propertyKeyId, byte[][] value, boolean vertexProperty);

    public static final native int mdb_get_property_keys(long cursor, long elementId, int[][] propertyKeyIds, boolean vertexProperty);

    public static final native int mdb_set_propertykey(long glmdb_env, long txn, String propertyKey, int propertyTypeEnum, int[] propertyKeyId, boolean vertex, boolean indexed, boolean overwrite);

    public static final native int mdb_reindex_property(long glmdb_env, long txn, int propertyKey, int propertyTypeEnum, boolean vertex);

    public static final native int mdb_get_first_property_key(long cursor, int propertyKeyIdArray[], int propertyTypeEnumArray[], boolean propertyIndexedArray[], byte[][] propertyKeyArray);

    public static final native int mdb_get_next_property_key(long cursor, int propertyKeyIdArray[], int propertyTypeEnumArray[], boolean propertyIndexedArray[], byte[][] propertyKeyArray);

    public static final native int mdb_get_first_label(long cursor, int labelIdArray[], byte[][] labelArray);

    public static final native int mdb_get_next_label(long cursor, int labelIdArray[], byte[][] labelArray);

    public static final native int mdb_set_label(long glmdb_env, long txn, String label, int[] labelId);

    public static final native int mdb_get_vertex(long cursor, long vertexId, long vertexIdResult[]);

    public static final native int mdb_remove_vertex(long glmdb_env, long txn, long vertexId);

    public static final native int mdb_get_first_vertex(long cursor, long vertexIdResult[]);

    public static final native int mdb_get_next_vertex(long cursor, long previousId, long vertexIdResult[]);


    //string
    public static final native int mdb_get_first_vertex_for_key_string_value(long cursor, long vertexIdResult[], int key, String value);

    public static final native int mdb_get_next_vertex_for_key_string_value(long cursor, long vertexIdResult[], int key, String value);

    public static final native int mdb_get_first_vertex_for_key_value_from_string_index(long vertexStringIndexDbCursor, long vertexIdResult[], int key, String value);

    public static final native int mdb_get_next_vertex_for_key_value_for_string_index(long vertexStringIndexDbCursor, long vertexIdResult[], int key, String value);

    public static final native int mdb_get_first_edge_for_key_value_from_string_index(long edgeStringIndexDbCursor, long edgeDbCursor, int key, String value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_next_edge_for_key_value_for_string_index(long edgeStringIndexDbCursor, long edgeDbCursor, int key, String value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_cursor_open_and_position_on_key_value_vertex_string_index_db(long txn, long glmdb_env, long vertexId, int key, String value, long[] cursor);

    public static final native int mdb_get_current_vertex_from_vertex_string_index_db(long cursor, long[] vertexId, int propertyKeyId, String value);

    public static final native int mdb_get_first_edge_for_key_string_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, String value);

    public static final native int mdb_get_next_edge_for_key_string_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, String value);

    public static final native int mdb_cursor_open_and_position_on_key_value_edge_string_index_db(long txn, long glmdb_env, long edgeId, int key, String value, long[] cursor);

    public static final native int mdb_get_current_edge_from_edge_string_index_db(long edgeStringIndexDbCursor, long edgeDbCursor, int propertyKeyId, String value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]);


    //int
    public static final native int mdb_get_first_vertex_for_key_int_value(long cursor, long vertexIdResult[], int key, int value);

    public static final native int mdb_get_next_vertex_for_key_int_value(long cursor, long vertexIdResult[], int key, int value);

    public static final native int mdb_get_first_vertex_for_key_value_from_int_index(long vertexStringIndexDbCursor, long vertexIdResult[], int key, int value);

    public static final native int mdb_get_next_vertex_for_key_value_for_int_index(long vertexStringIndexDbCursor, long vertexIdResult[], int key, int value);

    public static final native int mdb_get_first_edge_for_key_value_from_int_index(long edgeStringIndexDbCursor, long edgeDbCursor, int key, int value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_next_edge_for_key_value_for_int_index(long edgeStringIndexDbCursor, long edgeDbCursor, int key, int value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_first_edge_for_key_int_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, int value);

    public static final native int mdb_get_next_edge_for_key_int_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, int value);

    public static final native int mdb_cursor_open_and_position_on_key_value_vertex_int_index_db(long txn, long glmdb_env, long vertexId, int key, int value, long[] cursor);

    public static final native int mdb_get_current_vertex_from_vertex_int_index_db(long cursor, long[] vertexId, int propertyKeyId, int value);

    public static final native int mdb_cursor_open_and_position_on_key_value_edge_int_index_db(long txn, long glmdb_env, long edgeId, int key, int value, long[] cursor);

    public static final native int mdb_get_current_edge_from_edge_int_index_db(long edgeIntIndexDbCursor, long edgeDbCursor, int propertyKeyId, int value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]);


    //long
    public static final native int mdb_get_first_vertex_for_key_long_value(long cursor, long vertexIdResult[], int key, long value);

    public static final native int mdb_get_next_vertex_for_key_long_value(long cursor, long vertexIdResult[], int key, long value);

    public static final native int mdb_get_first_vertex_for_key_value_from_long_index(long vertexLongIndexDbCursor, long vertexIdResult[], int key, long value);

    public static final native int mdb_get_next_vertex_for_key_value_for_long_index(long vertexLongIndexDbCursor, long vertexIdResult[], int key, long value);

    public static final native int mdb_get_first_edge_for_key_value_from_long_index(long edgeLongIndexDbCursor, long edgeDbCursor, int key, long value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_next_edge_for_key_value_for_long_index(long edgeLongIndexDbCursor, long edgeDbCursor, int key, long value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_first_edge_for_key_long_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, long value);

    public static final native int mdb_get_next_edge_for_key_long_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, long value);

    public static final native int mdb_cursor_open_and_position_on_key_value_vertex_long_index_db(long txn, long glmdb_env, long vertexId, int key, long value, long[] cursor);

    public static final native int mdb_get_current_vertex_from_vertex_long_index_db(long cursor, long[] vertexId, int propertyKeyId, long value);

    public static final native int mdb_cursor_open_and_position_on_key_value_edge_long_index_db(long txn, long glmdb_env, long edgeId, int key, long value, long[] cursor);

    public static final native int mdb_get_current_edge_from_edge_long_index_db(long edgeLongIndexDbCursor, long edgeDbCursor, int propertyKeyId, long value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]);


    //float
    public static final native int mdb_get_first_vertex_for_key_float_value(long cursor, long vertexIdResult[], int key, float value);

    public static final native int mdb_get_next_vertex_for_key_float_value(long cursor, long vertexIdResult[], int key, float value);

    public static final native int mdb_get_first_vertex_for_key_value_from_float_index(long vertexFloatIndexDbCursor, long vertexIdResult[], int key, float value);

    public static final native int mdb_get_next_vertex_for_key_value_for_float_index(long vertexFloatIndexDbCursor, long vertexIdResult[], int key, float value);

    public static final native int mdb_get_first_edge_for_key_value_from_float_index(long edgeFloatIndexDbCursor, long edgeDbCursor, int key, float value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_next_edge_for_key_value_for_float_index(long edgeFloatIndexDbCursor, long edgeDbCursor, int key, float value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_first_edge_for_key_float_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, float value);

    public static final native int mdb_get_next_edge_for_key_float_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, float value);

    public static final native int mdb_cursor_open_and_position_on_key_value_vertex_float_index_db(long txn, long glmdb_env, long vertexId, int key, float value, long[] cursor);

    public static final native int mdb_get_current_vertex_from_vertex_float_index_db(long cursor, long[] vertexId, int propertyKeyId, float value);

    public static final native int mdb_cursor_open_and_position_on_key_value_edge_float_index_db(long txn, long glmdb_env, long edgeId, int key, float value, long[] cursor);

    public static final native int mdb_get_current_edge_from_edge_float_index_db(long edgeFloatIndexDbCursor, long edgeDbCursor, int propertyKeyId, float value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]);


    //double
    public static final native int mdb_get_first_vertex_for_key_double_value(long cursor, long vertexIdResult[], int key, double value);

    public static final native int mdb_get_next_vertex_for_key_double_value(long cursor, long vertexIdResult[], int key, double value);

    public static final native int mdb_get_first_vertex_for_key_value_from_double_index(long vertexDoubleIndexDbCursor, long vertexIdResult[], int key, double value);

    public static final native int mdb_get_next_vertex_for_key_value_for_double_index(long vertexDoubleIndexDbCursor, long vertexIdResult[], int key, double value);

    public static final native int mdb_get_first_edge_for_key_value_from_double_index(long edgeDoubleIndexDbCursor, long edgeDbCursor, int key, double value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_next_edge_for_key_value_for_double_index(long edgeDoubleIndexDbCursor, long edgeDbCursor, int key, double value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_first_edge_for_key_double_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, double value);

    public static final native int mdb_get_next_edge_for_key_double_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, double value);

    public static final native int mdb_cursor_open_and_position_on_key_value_vertex_double_index_db(long txn, long glmdb_env, long vertexId, int key, double value, long[] cursor);

    public static final native int mdb_get_current_vertex_from_vertex_double_index_db(long cursor, long[] vertexId, int propertyKeyId, double value);

    public static final native int mdb_cursor_open_and_position_on_key_value_edge_double_index_db(long txn, long glmdb_env, long edgeId, int key, double value, long[] cursor);

    public static final native int mdb_get_current_edge_from_edge_double_index_db(long edgeDoubleIndexDbCursor, long edgeDbCursor, int propertyKeyId, double value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]);



    //boolean
    public static final native int mdb_get_first_vertex_for_key_boolean_value(long cursor, long vertexIdResult[], int key, boolean value);

    public static final native int mdb_get_next_vertex_for_key_boolean_value(long cursor, long vertexIdResult[], int key, boolean value);

    public static final native int mdb_get_first_vertex_for_key_value_from_boolean_index(long vertexBooleanIndexDbCursor, long vertexIdResult[], int key, boolean value);

    public static final native int mdb_get_next_vertex_for_key_value_for_boolean_index(long vertexBooleanIndexDbCursor, long vertexIdResult[], int key, boolean value);

    public static final native int mdb_get_first_edge_for_key_value_from_boolean_index(long edgeBooleanIndexDbCursor, long edgeDbCursor, int key, boolean value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_next_edge_for_key_value_for_boolean_index(long edgeBooleanIndexDbCursor, long edgeDbCursor, int key, boolean value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_first_edge_for_key_boolean_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, boolean value);

    public static final native int mdb_get_next_edge_for_key_boolean_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, boolean value);

    public static final native int mdb_cursor_open_and_position_on_key_value_vertex_boolean_index_db(long txn, long glmdb_env, long vertexId, int key, boolean value, long[] cursor);

    public static final native int mdb_get_current_vertex_from_vertex_boolean_index_db(long cursor, long[] vertexId, int propertyKeyId, boolean value);

    public static final native int mdb_cursor_open_and_position_on_key_value_edge_boolean_index_db(long txn, long glmdb_env, long edgeId, int key, boolean value, long[] cursor);

    public static final native int mdb_get_current_edge_from_edge_boolean_index_db(long edgeBooleanIndexDbCursor, long edgeDbCursor, int propertyKeyId, boolean value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]);




    //short
    public static final native int mdb_get_first_vertex_for_key_short_value(long cursor, long vertexIdResult[], int key, short value);

    public static final native int mdb_get_next_vertex_for_key_short_value(long cursor, long vertexIdResult[], int key, short value);

    public static final native int mdb_get_first_vertex_for_key_value_from_short_index(long vertexShortIndexDbCursor, long vertexIdResult[], int key, short value);

    public static final native int mdb_get_next_vertex_for_key_value_for_short_index(long vertexShortIndexDbCursor, long vertexIdResult[], int key, short value);

    public static final native int mdb_get_first_edge_for_key_value_from_short_index(long edgeShortIndexDbCursor, long edgeDbCursor, int key, short value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_next_edge_for_key_value_for_short_index(long edgeShortIndexDbCursor, long edgeDbCursor, int key, short value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_first_edge_for_key_short_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, short value);

    public static final native int mdb_get_next_edge_for_key_short_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, short value);

    public static final native int mdb_cursor_open_and_position_on_key_value_vertex_short_index_db(long txn, long glmdb_env, long vertexId, int key, short value, long[] cursor);

    public static final native int mdb_get_current_vertex_from_vertex_short_index_db(long cursor, long[] vertexId, int propertyKeyId, short value);

    public static final native int mdb_cursor_open_and_position_on_key_value_edge_short_index_db(long txn, long glmdb_env, long edgeId, int key, short value, long[] cursor);

    public static final native int mdb_get_current_edge_from_edge_short_index_db(long edgeShortIndexDbCursor, long edgeDbCursor, int propertyKeyId, short value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]);



    //char
    public static final native int mdb_get_first_vertex_for_key_char_value(long cursor, long vertexIdResult[], int key, char value);

    public static final native int mdb_get_next_vertex_for_key_char_value(long cursor, long vertexIdResult[], int key, char value);

    public static final native int mdb_get_first_vertex_for_key_value_from_char_index(long vertexCharIndexDbCursor, long vertexIdResult[], int key, char value);

    public static final native int mdb_get_next_vertex_for_key_value_for_char_index(long vertexCharIndexDbCursor, long vertexIdResult[], int key, char value);

    public static final native int mdb_get_first_edge_for_key_value_from_char_index(long edgeCharIndexDbCursor, long edgeDbCursor, int key, char value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_next_edge_for_key_value_for_char_index(long edgeCharIndexDbCursor, long edgeDbCursor, int key, char value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_first_edge_for_key_char_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, char value);

    public static final native int mdb_get_next_edge_for_key_char_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, char value);

    public static final native int mdb_cursor_open_and_position_on_key_value_vertex_char_index_db(long txn, long glmdb_env, long vertexId, int key, char value, long[] cursor);

    public static final native int mdb_get_current_vertex_from_vertex_char_index_db(long cursor, long[] vertexId, int propertyKeyId, char value);

    public static final native int mdb_cursor_open_and_position_on_key_value_edge_char_index_db(long txn, long glmdb_env, long edgeId, int key, char value, long[] cursor);

    public static final native int mdb_get_current_edge_from_edge_char_index_db(long edgeCharIndexDbCursor, long edgeDbCursor, int propertyKeyId, char value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]);



    //byte
    public static final native int mdb_get_first_vertex_for_key_byte_value(long cursor, long vertexIdResult[], int key, byte value);

    public static final native int mdb_get_next_vertex_for_key_byte_value(long cursor, long vertexIdResult[], int key, byte value);

    public static final native int mdb_get_first_vertex_for_key_value_from_byte_index(long vertexByteIndexDbCursor, long vertexIdResult[], int key, byte value);

    public static final native int mdb_get_next_vertex_for_key_value_for_byte_index(long vertexByteIndexDbCursor, long vertexIdResult[], int key, byte value);

    public static final native int mdb_get_first_edge_for_key_value_from_byte_index(long edgeByteIndexDbCursor, long edgeDbCursor, int key, byte value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_next_edge_for_key_value_for_byte_index(long edgeByteIndexDbCursor, long edgeDbCursor, int key, byte value, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_first_edge_for_key_byte_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, byte value);

    public static final native int mdb_get_next_edge_for_key_byte_value(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId, int key, byte value);

    public static final native int mdb_cursor_open_and_position_on_key_value_vertex_byte_index_db(long txn, long glmdb_env, long vertexId, int key, byte value, long[] cursor);

    public static final native int mdb_get_current_vertex_from_vertex_byte_index_db(long cursor, long[] vertexId, int propertyKeyId, byte value);

    public static final native int mdb_cursor_open_and_position_on_key_value_edge_byte_index_db(long txn, long glmdb_env, long edgeId, int key, byte value, long[] cursor);

    public static final native int mdb_get_current_edge_from_edge_byte_index_db(long edgeByteIndexDbCursor, long edgeDbCursor, int propertyKeyId, byte value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]);





    public static final native int mdb_get_edge(long cursor, long edgeId, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_remove_edge(long glmdb_env, long txn, long edgeId);

    public static final native int mdb_get_first_edge(long cursor, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_next_edge(long cursor, long previousEdgeId, long edgeIdResult[], int[] label, long[] outVertexId, long[] inVertexId);



    public static final native int mdb_get_first_edge_from_vertex(long cursor, int direction, int labelId, long fromVertexId, long edgeIdResult[], long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_next_edge_from_vertex(long cursor, int direction, int labelId, long fromVertexId, long edgeIdResult[], long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_current_edge_from_vertex(long cursor, int direction, int labelId, long fromVertexId, long edgeIdResult[], long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_first_edge_from_vertex_all_labels(long cursor, int direction, long fromVertexId, int labelId[], long edgeIdResult[], long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_next_edge_from_vertex_all_labels(long cursor, int direction, long fromVertexId, int labelId[], long edgeIdResult[], long[] outVertexId, long[] inVertexId);

    public static final native int mdb_get_current_edge_from_vertex_all_labels(long cursor, int direction, long fromVertexId, int labelId[], long edgeIdResult[], long[] outVertexId, long[] inVertexId);

    public static final native int mdb_delete_index(long glmdb_env, long txn, int propertyKeyId, boolean vertex, int propertyTypeEnum);


}
