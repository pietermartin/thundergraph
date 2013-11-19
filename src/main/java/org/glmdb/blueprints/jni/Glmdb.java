package org.glmdb.blueprints.jni;

import java.io.Closeable;

import static  org.glmdb.blueprints.jni.GlmdbJni.*;
import static org.glmdb.blueprints.jni.Util.*;

/**
 * Date: 2013/11/18
 * Time: 8:07 PM
 */
public class Glmdb extends NativeObject implements Closeable {

    public Glmdb(String path) {
        super(create(path));
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
        checkErrorCode(mdb_txn_begin(pointer(), parent==null ? 0 : parent.pointer(), readOnly ? MDB_RDONLY : 0, txpointer));
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
}
