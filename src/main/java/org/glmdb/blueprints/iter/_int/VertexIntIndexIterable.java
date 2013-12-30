package org.glmdb.blueprints.iter._int;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.ThunderVertex;
import org.glmdb.blueprints.iter.BaseThunderIterable;
import org.glmdb.blueprints.iter.BaseThunderIterator;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class VertexIntIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private int value;

    public VertexIntIndexIterable(ThunderGraph thunderGraph, String key, int value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexIntIndexIterator();
    }

    private final class VertexIntIndexIterator extends BaseThunderIterator<ThunderVertex> implements Iterator {

        private boolean goToFirst = true;

        public VertexIntIndexIterator() {
            super(VertexIntIndexIterable.this.tc);
        }

        @Override
        protected VertexIntIndexIterable getParentIterable() {
            return VertexIntIndexIterable.this;
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.VERTEX_INT_INDEX;
        }

        @Override
        public void remove() {
            if (this.cursorIsReadOnly) {
                //Upgrade transaction to a writable one.
                //Replace the current cursor with a new one from the writable transaction
                this.tc = this.getParentIterable().thunderGraph.getWriteTx();
                this.refreshForNext();

                //Check current has not changed, i.e. another thread may have removed the vertex already, throw StaleObjectException or something
                long elementIdArray[] = new long[1];
                if (this.cursor != null && VertexIntIndexIterable.this.thunderGraph.getThunder().getCurrentVertexFromVertexIntIndexDb(
                        this.cursor, elementIdArray, VertexIntIndexIterable.this.key, VertexIntIndexIterable.this.value)) {

                    //Check if the current is really the current.
                    //If the current has been removed then current is in fact the next
                    //if it is already next then do nothing, else get the next
                    if (this.internalNext.getInternalId() != elementIdArray[0]) {
                        throw new IllegalStateException("The index has been changed, remove is not possible!");
                    }

                } else {
                    throw new IllegalStateException("The index has been changed, remove is not possible!");
                }
            }
            VertexIntIndexIterable.this.thunderGraph.getThunder().removeVertex(this.tc.getTxn(), this.internalNext.getInternalId());

        }

        @Override
        protected ThunderVertex internalNext() {
            long elementIdArray[] = new long[1];
            if (this.goToFirst) {
                this.goToFirst = false;
                //Check if cursor needs reopening. This happens if a read only transaction is upgraded to a write transaction
                //after the iterator was instantiated.
                if (this.cursor == null || !this.cursor.isAllocated()) {
                    refreshForFirst();
                }
                if (this.cursor != null && VertexIntIndexIterable.this.thunderGraph.getThunder().getFirstVertexForKeyValueFromIntIndex(this.cursor, elementIdArray, VertexIntIndexIterable.this.key, VertexIntIndexIterable.this.value)) {
                    return new ThunderVertex(VertexIntIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (this.cursor == null || !this.cursor.isAllocated()) {
                    refreshForNext();

                    if (this.cursor != null && VertexIntIndexIterable.this.thunderGraph.getThunder().getCurrentVertexFromVertexIntIndexDb(
                            this.cursor, elementIdArray, VertexIntIndexIterable.this.key, VertexIntIndexIterable.this.value)) {

                        //Check if the current is really the current.
                        //If the current has been removed then current is in fact the next
                        //if it is already next then do nothing, else get the next
                        if (this.internalNext.getInternalId() == elementIdArray[0]) {

                            if (this.cursor != null && VertexIntIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromIntIndex(this.cursor, elementIdArray, VertexIntIndexIterable.this.key, VertexIntIndexIterable.this.value)) {
                                return new ThunderVertex(VertexIntIndexIterable.this.thunderGraph, elementIdArray[0]);
                            } else {
                                return null;
                            }

                        } else {

                            return new ThunderVertex(VertexIntIndexIterable.this.thunderGraph, elementIdArray[0]);
                        }

                    } else {
                        return null;
                    }
                } else {
                    if (VertexIntIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromIntIndex(this.cursor, elementIdArray, VertexIntIndexIterable.this.key, VertexIntIndexIterable.this.value)) {
                        return new ThunderVertex(VertexIntIndexIterable.this.thunderGraph, elementIdArray[0]);
                    } else {
                        return null;
                    }
                }
            }
        }

        @Override
        protected void refreshForNext() {
            this.tc = VertexIntIndexIterable.this.thunderGraph.getReadOnlyTx();

            if (this.tc.hasAvailableCursors(this.getDbEnum())) {
                this.cursor = this.tc.getAndRemoveAvailableCursor(this.getDbEnum());
            } else {
                this.cursor = VertexIntIndexIterable.this.thunderGraph.getThunder().openAndPositionCursorOnKeyValueInVertexIntIndexDb(
                        this.tc.getTxn(),
                        this.internalNext.getInternalId(),
                        VertexIntIndexIterable.this.key,
                        VertexIntIndexIterable.this.value
                );
            }
            if (this.cursor != null) {
                this.tc.addOpenCursor(this.cursor);
                this.cursorIsReadOnly = this.tc.isReadOnly();
            } else {
                this.cursorIsReadOnly = true;
            }
        }

    }

}
