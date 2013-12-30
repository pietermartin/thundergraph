package org.glmdb.blueprints.iter;

import com.tinkerpop.blueprints.Direction;
import org.glmdb.blueprints.ThunderElement;
import org.glmdb.blueprints.TransactionAndCursor;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/12/24
 * Time: 7:03 PM
 */
public abstract class BaseThunderIterator<E extends ThunderElement> implements Iterator  {

    protected TransactionAndCursor tc;
    protected Cursor cursor;
    protected boolean cursorIsReadOnly;
    protected long edgeId;
    protected boolean goToFirst = true;
    protected String currentLabel;
    protected long currentEdgeOutVertexId;
    protected E next;
    //This is needed as a cache for the remove method.
    //Remove is called after a call to next however next sets next to null for the hasNext logic;
    protected E internalNext;
    protected boolean closed = false;

    protected BaseThunderIterator(TransactionAndCursor tc) {
        this.tc = tc;
        this.cursorIsReadOnly = this.tc.isReadOnly();
        if (this.tc.hasAvailableCursors(this.getDbEnum())) {
            this.cursor = this.tc.getAndRemoveAvailableCursor(this.getDbEnum());
        } else {
            this.cursor = this.getParentIterable().thunderGraph.getThunder().openCursor(this.tc.getTxn(), this.getDbEnum());
        }
        if (this.cursor != null) {
            this.tc.addOpenCursor(this.cursor);
        }
    }

    @Override
    public boolean hasNext() {
        if (this.next == null) {
            this.next = internalNext();
            this.internalNext = this.next;
        }
        boolean result = this.next != null;
        if (!result) {
            this.closed = true;
            this.tc.closeAndRemoveCursor(this.getDbEnum(), this.cursor);
        }
        return result;
    }

    @Override
    public E next() {
        if (this.closed) {
            throw new NoSuchElementException();
        }
        if (this.next == null) {
            this.next = internalNext();
            if (this.next == null) {
                throw new NoSuchElementException();
            }
        }
        E result = this.next;
        this.internalNext = this.next;
        this.next = null;
        return result;
    }

    protected void refreshForFirst() {
        this.tc = this.getParentIterable().thunderGraph.getReadOnlyTx();
        if (this.tc.hasAvailableCursors(this.getDbEnum())) {
            this.cursor = this.tc.getAndRemoveAvailableCursor(this.getDbEnum());
        } else {
            this.cursor = this.getParentIterable().thunderGraph.getThunder().openCursor(this.tc.getTxn(), this.getDbEnum());
        }
        if (this.cursor != null) {
            this.tc.addOpenCursor(this.cursor);
        }
        this.cursorIsReadOnly = this.tc.isReadOnly();
    }

    protected void refreshForNext() {
        this.tc = this.getParentIterable().thunderGraph.getReadOnlyTx();

        if (this.tc.hasAvailableCursors(this.getDbEnum())) {
            this.cursor = this.tc.getAndRemoveAvailableCursor(this.getDbEnum());
        } else {
            this.cursor = this.getParentIterable().thunderGraph.getThunder().openAndPositionCursorOnEdgeInVertexDb(
                    this.tc.getTxn(),
                    this.getParentIterable().vertexId,
                    (this.currentEdgeOutVertexId == this.getParentIterable().vertexId ? Direction.OUT : Direction.IN),
                    this.currentLabel,
                    this.edgeId
            );
        }
        if (this.cursor != null) {
            this.tc.addOpenCursor(this.cursor);
            this.cursorIsReadOnly = this.tc.isReadOnly();
        } else {
            this.cursorIsReadOnly = true;
        }
    }

    protected abstract DbEnum getDbEnum();
    protected abstract E internalNext();
    protected abstract BaseThunderIterable getParentIterable();

}
