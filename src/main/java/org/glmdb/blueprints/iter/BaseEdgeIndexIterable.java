package org.glmdb.blueprints.iter;

import org.glmdb.blueprints.ThunderEdge;
import org.glmdb.blueprints.TransactionAndCursor;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;

/**
 * Date: 2013/12/30
 * Time: 9:31 PM
 */
public abstract class BaseEdgeIndexIterable extends BaseThunderIterator<ThunderEdge> implements Iterator {

    protected Cursor edgeDbCursor;

    protected BaseEdgeIndexIterable(TransactionAndCursor tc) {
        super(tc);
        this.edgeDbCursor = this.getParentIterable().thunderGraph.getThunder().openCursor(this.tc.getTxn(), DbEnum.EDGE_DB);
        this.tc.addOpenCursor(this.edgeDbCursor);
    }

    @Override
    public void remove() {
        if (this.cursorIsReadOnly) {
            //Upgrade transaction to a writable one.
            //Replace the current cursor with a new one from the writable transaction
            this.tc = this.getParentIterable().thunderGraph.getWriteTx();
            this.refreshForNext();

            //Check current has not changed, i.e. another thread may have removed the vertex already, throw StaleObjectException or something
            long edgeIdArray[] = new long[1];
            String labelArray[] = new String[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];

            if (this.cursor != null && this.getCurrentEdgeFromEdgeIndexDb(edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {

                //Check if the current is really the current.
                //If the current has been removed then current is in fact the next
                //if it is already next then do nothing, else get the next
                if (this.internalNext.getInternalId() != edgeIdArray[0]) {
                    throw new IllegalStateException("The index has been changed, remove is not possible!");
                }

            } else {
                throw new IllegalStateException("The index has been changed, remove is not possible!");
            }
        }
        this.getParentIterable().thunderGraph.getThunder().removeEdge(this.tc.getTxn(), this.internalNext.getInternalId());
    }

    @Override
    protected void refreshForFirst() {
        this.tc = this.getParentIterable().thunderGraph.getReadOnlyTx();
        //refresh the index cursor
        if (this.tc.hasAvailableCursors(this.getDbEnum())) {
            this.cursor = this.tc.getAndRemoveAvailableCursor(this.getDbEnum());
        } else {
            this.cursor = this.getParentIterable().thunderGraph.getThunder().openCursor(this.tc.getTxn(), this.getDbEnum());
        }
        if (this.cursor != null) {
            this.tc.addOpenCursor(this.cursor);
        }
        this.cursorIsReadOnly = this.tc.isReadOnly();
        refreshEdgeDbCursor();
    }

    @Override
    protected void refreshForNext() {
        this.tc = this.getParentIterable().thunderGraph.getReadOnlyTx();

        if (this.tc.hasAvailableCursors(this.getDbEnum())) {
            this.cursor = this.tc.getAndRemoveAvailableCursor(this.getDbEnum());
        } else {
            this.cursor = this.openAndPositionCursorOnKeyValueInEdgeTypeIndexDb();
        }
        if (this.cursor != null) {
            this.tc.addOpenCursor(this.cursor);
            this.cursorIsReadOnly = this.tc.isReadOnly();
        } else {
            this.cursorIsReadOnly = true;
        }

        this.refreshEdgeDbCursor();
        this.cursorIsReadOnly = this.tc.isReadOnly();
    }

    protected void refreshEdgeDbCursor() {
        //refresh the edgedb  cursor
        if (this.tc.hasAvailableCursors(DbEnum.EDGE_DB)) {
            this.edgeDbCursor = this.tc.getAndRemoveAvailableCursor(DbEnum.EDGE_DB);
        } else {
            this.edgeDbCursor = this.getParentIterable().thunderGraph.getThunder().openCursor(this.tc.getTxn(), DbEnum.EDGE_DB);
        }
        if (this.edgeDbCursor != null) {
            this.tc.addOpenCursor(this.edgeDbCursor);
        }
    }

    @Override
    protected ThunderEdge internalNext() {

        long edgeIdArray[] = new long[1];
        String labelArray[] = new String[1];
        long outVertexIdArray[] = new long[1];
        long inVertexIdArray[] = new long[1];

        if (this.goToFirst) {
            this.goToFirst = false;
            //Check if cursor needs reopening. This happens if a read only transaction is upgraded to a write transaction
            //after the iterator was instantiated.
            if (this.cursor == null || !this.cursor.isAllocated()) {
                refreshForFirst();
            }
            if (this.getFirstEdgeForKeyValueFromTypeIndex(edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                return new ThunderEdge(this.getParentIterable().thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
            } else {
                return null;
            }
        } else {

            //Check if cursor needs reopening. This happens if a read only transaction is upgraded to a write transaction
            //after the iterator was instantiated.
            if (this.cursor == null || !this.cursor.isAllocated()) {
                refreshForNext();

                if (this.cursor != null && getCurrentEdgeFromEdgeIndexDb(edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {

                    if (this.internalNext.getInternalId() == edgeIdArray[0]) {
                        if (this.getNextEdgeForKeyValueFromTypeIndex(edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {

                            return new ThunderEdge(this.getParentIterable().thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);

                        } else {
                            return null;
                        }
                    } else {
                        return new ThunderEdge(this.getParentIterable().thunderGraph, edgeIdArray[0], currentLabel, outVertexIdArray[0], inVertexIdArray[0]);
                    }
                } else {
                    return null;
                }
            } else {

                if (this.getNextEdgeForKeyValueFromTypeIndex(edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {

                    return new ThunderEdge(this.getParentIterable().thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);

                } else {
                    return null;
                }

            }
        }
    }

    protected abstract Cursor openAndPositionCursorOnKeyValueInEdgeTypeIndexDb();
    protected abstract boolean getCurrentEdgeFromEdgeIndexDb(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]);
    protected abstract boolean getFirstEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]);
    protected abstract boolean getNextEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]);

}
