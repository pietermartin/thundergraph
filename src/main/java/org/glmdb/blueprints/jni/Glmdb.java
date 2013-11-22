package org.glmdb.blueprints.jni;

import java.io.Closeable;
import java.util.HashMap;
import java.util.Map;

import static org.glmdb.blueprints.jni.GlmdbJni.*;
import static org.glmdb.blueprints.jni.Util.*;

/**
 * Date: 2013/11/18
 * Time: 8:07 PM
 */
public class Glmdb extends NativeObject implements Closeable {

    private Map<String, Integer> propertyKeyToIdMap = new HashMap<String, Integer>();

    public Glmdb(String path) {
        super(create(path));
        this.propertyKeyToIdMap.put("name0", 0);
        this.propertyKeyToIdMap.put("name1", 1);
        this.propertyKeyToIdMap.put("name2", 2);
        this.propertyKeyToIdMap.put("name3", 3);
    }

    private static long create(String path) {
        long env_ptr[] = new long[1];
        checkErrorCode(glmdb_env_create(path, env_ptr));
        return env_ptr[0];
    }

    public void close() {
        if( self!=0 ) {
            glmdb_env_close(self);
            self=0;
        }
    }

    public Transaction createTransaction() {
        return createTransaction(null, false);
    }
    public Transaction createTransaction(boolean readOnly) {
        return createTransaction(null, readOnly);
    }
    public Transaction createTransaction(Transaction parent) {
        return createTransaction(parent, false);
    }

    public Transaction createTransaction(Transaction parent, boolean readOnly) {
        long txpointer [] = new long[1];
        checkErrorCode(mdb_txn_begin(pointer(), parent == null ? 0 : parent.pointer(), readOnly ? GlmdbJni.MDB_RDONLY : 0, txpointer));
        return new Transaction(this, txpointer[0]);
    }

    public Cursor openCursorToVertexDb(Transaction tx) {
        long cursor[] = new long[1];
        checkErrorCode(mdb_cursor_open_vertex_db(tx.pointer(), pointer(), cursor));
        return new Cursor(this, cursor[0]);
    }

    public long addVertex(Cursor cursor) {
        long vertexId[] = new long[1];
        checkErrorCode(mdb_add_vertex(pointer(), cursor.pointer(), vertexId));
        return vertexId[0];
    }

    public void setProperty(Cursor cursor, long vertexId, String key, String value) {
        Integer propertyKeyId = this.propertyKeyToIdMap.get(key);
        if (propertyKeyId == null) {

        }
        checkErrorCode(mdb_set_property_string(cursor.pointer(), vertexId, propertyKeyId, value));
    }

    public String getProperty(Cursor cursor, long vertexId, String key) {
        Integer propertyKeyId = this.propertyKeyToIdMap.get(key);
        if (propertyKeyId == null) {

        }
//        Value value = new Value();
//        checkErrorCode(mdb_get_property(cursor.pointer(), vertexId, propertyKeyId, value));
//        return string(value.mv_data);

        byte[][] value = new byte[1][];
        checkErrorCode(mdb_get_property_array(cursor.pointer(), vertexId, propertyKeyId, value));
        return string(value[0]);

    }

}
