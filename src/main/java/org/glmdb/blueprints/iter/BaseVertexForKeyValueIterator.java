package org.glmdb.blueprints.iter;

import org.glmdb.blueprints.ThunderVertex;
import org.glmdb.blueprints.TransactionAndCursor;

import java.util.Iterator;

/**
 * Date: 2013/12/25
 * Time: 8:35 PM
 */
public abstract class BaseVertexForKeyValueIterator extends BaseForKeyValueIterator<ThunderVertex> implements Iterator {

    public BaseVertexForKeyValueIterator(TransactionAndCursor tc) {
        super(tc);
    }

    @Override
    protected org.glmdb.blueprints.ThunderVertex internalNext() {
        long vertexIdArray[] = new long[1];
        if (this.goToFirst) {
            this.goToFirst = false;
            //Check if cursor needs reopening. This happens if a read only transaction is upgraded to a write transaction
            //after the iterator was instantiated.
            if (this.cursor == null || !this.cursor.isAllocated()) {
                refreshForFirst();
            }
            if (this.getFirst(vertexIdArray)) {
                return new org.glmdb.blueprints.ThunderVertex(this.getParentIterable().thunderGraph, vertexIdArray[0]);
            } else {
                return null;
            }
        } else {
            if (this.cursor == null || !this.cursor.isAllocated()) {
                refreshForNext();
            }
            if (this.cursor != null && getNext(vertexIdArray)) {
                return new org.glmdb.blueprints.ThunderVertex(this.getParentIterable().thunderGraph, vertexIdArray[0]);
            } else {
                return null;
            }
        }

    }

    @Override
    protected void refreshForNext() {
        this.tc = this.getParentIterable().thunderGraph.getReadOnlyTx();

        if (this.tc.hasAvailableCursors(this.getDbEnum())) {
            this.cursor = this.tc.getAndRemoveAvailableCursor(this.getDbEnum());
        } else {
            this.cursor = this.getParentIterable().thunderGraph.getThunder().openAndPositionCursorOnVertexInVertexDb(
                    this.tc.getTxn(),
                    this.getParentIterable().vertexId
            );
        }
        if (this.cursor != null) {
            this.cursorIsReadOnly = this.tc.isReadOnly();
            this.tc.addOpenCursor(this.cursor);
        } else {
            this.cursorIsReadOnly = true;
        }
    }

    protected abstract boolean getFirst(long vertexIdArray[]);
    protected abstract boolean getNext(long vertexIdArray[]);
}
