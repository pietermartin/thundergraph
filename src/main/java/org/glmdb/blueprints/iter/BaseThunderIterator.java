package org.glmdb.blueprints.iter;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderElement;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/12/24
 * Time: 7:03 PM
 */
abstract class BaseThunderIterator<E extends ThunderElement> implements Iterator  {

    protected Cursor cursor;
    protected boolean cursorIsReadOnly;
    protected long edgeId;
    protected boolean goToFirst = true;
    protected String currentLabel;
    protected long currentEdgeOutVertexId;

    private E next;
    //This is needed as a cache for the remove method.
    //Remove is called after a call to next however next sets next to null for the hasNext logic;
    protected E internalNext;

    BaseThunderIterator() {
        this.cursorIsReadOnly = this.getParentIterable().tc.isReadOnly();
        this.cursor = this.getParentIterable().thunderGraph.getThunder().openCursor(this.getParentIterable().tc.getTxn(), DbEnum.VERTEX_DB);
        this.getParentIterable().tc.addIteratorCursor(this.getParentIterable(), this.cursor);
    }

    @Override
    public void remove() {
        if (this.cursorIsReadOnly) {
            //Upgrade transaction to a writable one.
            //Replace the current cursor with a new one from the writable transaction
            this.getParentIterable().tc = this.getParentIterable().thunderGraph.getWriteTx();
            this.cursorIsReadOnly = false;
            this.cursor = this.getParentIterable().thunderGraph.getThunder().openAndPositionCursorOnEdgeInVertexDb(
                    this.getParentIterable().tc.getTxn(),
                    this.getParentIterable().vertexId,
                    (this.currentEdgeOutVertexId == this.getParentIterable().vertexId ? Direction.OUT : Direction.IN),
                    this.currentLabel,
                    this.edgeId
            );
        }
        this.internalRemove();
    }

    protected abstract void internalRemove();

    @Override
    public boolean hasNext() {
        if (this.next == null) {
            this.next = internalNext();
            this.internalNext = this.next;
        }
        return this.next != null;
    }

    @Override
    public E next() {
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

    protected void refreshFirst() {
        this.getParentIterable().tc = this.getParentIterable().thunderGraph.getReadOnlyTx();
        this.cursor = this.getParentIterable().thunderGraph.getThunder().openCursor(this.getParentIterable().tc.getTxn(), DbEnum.VERTEX_DB);
        this.cursorIsReadOnly = this.getParentIterable().tc.isReadOnly();
        this.getParentIterable().setRefresh(false);
    }

    protected void refreshNext() {
        this.getParentIterable().tc = this.getParentIterable().thunderGraph.getReadOnlyTx();
        this.cursor = this.getParentIterable().thunderGraph.getThunder().openAndPositionCursorOnEdgeInVertexDb(
                this.getParentIterable().tc.getTxn(),
                this.getParentIterable().vertexId,
                (this.currentEdgeOutVertexId == this.getParentIterable().vertexId ? Direction.OUT : Direction.IN),
                this.currentLabel,
                this.edgeId
        );
        if (this.cursor != null) {
            this.cursorIsReadOnly = this.getParentIterable().tc.isReadOnly();
        } else {
            this.cursorIsReadOnly = true;
        }
        this.getParentIterable().setRefresh(false);
    }

    protected abstract E internalNext();
    abstract BaseThunderIterable getParentIterable();

}
