package org.glmdb.blueprints.iter;

import com.tinkerpop.blueprints.Edge;
import org.glmdb.blueprints.ThunderEdge;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.ThunderVertex;
import org.glmdb.blueprints.TransactionAndCursor;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class AllEdgeIterable<T extends Edge> extends BaseThunderIterable implements Iterable<ThunderEdge> {


    public AllEdgeIterable(ThunderGraph thunderGraph) {
        super(thunderGraph);
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgesIterator();
    }

    private final class EdgesIterator extends BaseThunderIterator<ThunderEdge> implements Iterator {

        private boolean goToFirst = true;
        private long previousEdgeId;

        private EdgesIterator() {
            super(AllEdgeIterable.this.tc);
        }

        @Override
        protected AllEdgeIterable getParentIterable() {
            return AllEdgeIterable.this;
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.EDGE_DB;
        }

        @Override
        public void remove() {
            if (this.cursorIsReadOnly) {
                //Upgrade transaction to a writable one.
                //Replace the current cursor with a new one from the writable transaction
                AllEdgeIterable.this.tc = this.getParentIterable().thunderGraph.getWriteTx();
                refreshForFirst();
            }
            AllEdgeIterable.this.thunderGraph.getThunder().removeEdge(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected ThunderEdge internalNext() {
            long edgeIdArray[] = new long[1];
            String labelArray[] = new String[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];
            if (this.goToFirst) {
                this.goToFirst = false;
                if (this.cursor == null || !this.cursor.isAllocated()) {
                    refreshForFirst();
                }
                if (AllEdgeIterable.this.thunderGraph.getThunder().getFirstEdge(this.cursor, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    this.previousEdgeId = edgeIdArray[0];
                    return new ThunderEdge(AllEdgeIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                //Check if cursor needs reopening. This happens if a read only transaction is upgraded to a write transaction
                //after the iterator was instantiated.
                if (this.cursor == null || !this.cursor.isAllocated()) {
                    //This can be a refreshForFirst as getNextVertex does a range query
                    refreshForFirst();
                }
                if (AllEdgeIterable.this.thunderGraph.getThunder().getNextEdge(this.cursor, this.previousEdgeId, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    this.previousEdgeId = edgeIdArray[0];
                    return new ThunderEdge(AllEdgeIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }
}
