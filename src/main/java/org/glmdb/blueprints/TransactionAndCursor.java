package org.glmdb.blueprints;

import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.Transaction;

/**
 * Date: 2013/11/24
 * Time: 8:18 AM
 */
class TransactionAndCursor {

    private Transaction txn;
    private Cursor vertexCursor;
    private Cursor edgeCursor;
    private boolean readOnly;

    TransactionAndCursor(Transaction txn, Cursor vertexCursor, Cursor edgeCursor, boolean readOnly) {
        this.txn = txn;
        this.vertexCursor = vertexCursor;
        this.edgeCursor = edgeCursor;
        this.readOnly = readOnly;
    }

    Transaction getTxn() {
        return txn;
    }

    Cursor getVertexCursor() {
        return vertexCursor;
    }

    Cursor getEdgeCursor() {
        return edgeCursor;
    }

    boolean isReadOnly() {
        return readOnly;
    }

}
