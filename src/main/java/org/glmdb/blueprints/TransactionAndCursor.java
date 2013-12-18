package org.glmdb.blueprints;

import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.Transaction;

import java.util.HashSet;
import java.util.Set;

/**
 * Date: 2013/11/24
 * Time: 8:18 AM
 */
public class TransactionAndCursor {

    private Transaction txn;
    private Cursor vertexCursor;
    private Cursor edgeCursor;
    private boolean readOnly;
    private Set<Cursor> iteratorCursors = new HashSet<Cursor>();

    TransactionAndCursor(Transaction txn, Cursor vertexCursor, Cursor edgeCursor, boolean readOnly) {
        this.txn = txn;
        this.vertexCursor = vertexCursor;
        this.edgeCursor = edgeCursor;
        this.readOnly = readOnly;
    }

    public Transaction getTxn() {
        return txn;
    }

    public Cursor getVertexCursor() {
        return vertexCursor;
    }

    public Cursor getEdgeCursor() {
        return edgeCursor;
    }

    public boolean isReadOnly() {
        return readOnly;
    }

    public void addIteratorCursor(Cursor cursor) {
        this.iteratorCursors.add(cursor);
    }

    public void closeCursors() {
        this.vertexCursor.close();
        this.edgeCursor.close();
        for (Cursor c : this.iteratorCursors) {
            c.close();
        }
        this.iteratorCursors.clear();
    }


}
