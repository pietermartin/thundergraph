package org.glmdb.blueprints.iter;

import com.tinkerpop.blueprints.Edge;
import org.glmdb.blueprints.ThunderEdge;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.TransactionAndCursor;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class AllEdgeIterable<T extends Edge> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;

    public AllEdgeIterable(ThunderGraph thunderGraph) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgesIterator();
    }

    private class EdgesIterator implements Iterator<ThunderEdge> {

        private ThunderEdge next;
        private boolean goToFirst = true;
        private long previousEdgeId;

        @Override
        public boolean hasNext() {
            if (this.next == null) {
                this.next = internalNext();
            }
            return this.next != null;
        }

        @Override
        public ThunderEdge next() {
            if (this.next == null) {
                this.next = internalNext();
                if (this.next == null) {
                    throw new NoSuchElementException();
                }
            }
            ThunderEdge result = this.next;
            this.next = null;
            return result;
        }

        @Override
        public void remove() {
            throw new RuntimeException("Not yet implemented!");
        }

        private ThunderEdge internalNext() {
            long edgeIdArray[] = new long[1];
            String labelArray[] = new String[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];
            if (this.goToFirst) {
                this.goToFirst = false;
                if (AllEdgeIterable.this.thunderGraph.getThunder().getFirstEdge(tc.getEdgeCursor(), edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    this.previousEdgeId = edgeIdArray[0];
                    return new ThunderEdge(AllEdgeIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (AllEdgeIterable.this.thunderGraph.getThunder().getNextEdge(tc.getEdgeCursor(), this.previousEdgeId, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    this.previousEdgeId = edgeIdArray[0];
                    return new ThunderEdge(AllEdgeIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }
}
