package org.glmdb.blueprints;

import org.glmdb.blueprints.iter.BaseThunderIterable;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.Transaction;
import org.glmdb.blueprints.util.Pair;

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
    private Set<Pair<BaseThunderIterable, Cursor>> iteratorCursors = new HashSet<Pair<BaseThunderIterable, Cursor>>();

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

    public void addIteratorCursor(BaseThunderIterable iter, Cursor cursor) {
        Pair<BaseThunderIterable, Cursor> pair = new Pair<BaseThunderIterable, Cursor>(iter, cursor);
        this.iteratorCursors.add(pair);
    }

    public void closeCursors() {
        this.vertexCursor.close();
        this.edgeCursor.close();
        for (Pair<BaseThunderIterable, Cursor> pair : this.iteratorCursors) {
            pair.getFirst().setRefresh(true);
            pair.getSecond().close();
        }
        this.iteratorCursors.clear();
    }

    Set<Pair<BaseThunderIterable, Cursor>> getCopyOfIteratorCursorsCopy() {
        Set<Pair<BaseThunderIterable, Cursor>> copy = new HashSet<Pair<BaseThunderIterable, Cursor>>(this.iteratorCursors.size());
        for (Pair<BaseThunderIterable, Cursor> pair : this.iteratorCursors) {
            copy.add(pair);
        }
        return copy;
    }

    void setIteratorCursors(Set<Pair<BaseThunderIterable, Cursor>> iteratorCursors) {
        this.iteratorCursors = iteratorCursors;
    }

}
