package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Edge;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class GlmdbEdgeForKeyValueIterable<T extends Edge> implements Iterable<ThunderEdge> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private Object value;

    public GlmdbEdgeForKeyValueIterable(ThunderGraph thunderGraph, String key, Object value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeForKeyValueIterator();
    }

    private final class EdgeForKeyValueIterator implements Iterator<ThunderEdge>  {

        private ThunderEdge next;
        private boolean goToFirst = true;

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
            //To change body of implemented methods use File | Settings | File Templates.
        }

        private ThunderEdge internalNext() {
            long edgeIdArray[] = new long[1];
            String labelArray[] = new String[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];
            if (this.goToFirst) {
                this.goToFirst = false;
                if (GlmdbEdgeForKeyValueIterable.this.thunderGraph.getGlmdb().getFirstEdgeForKeyValue(tc.getEdgeCursor(), edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray, GlmdbEdgeForKeyValueIterable.this.key, GlmdbEdgeForKeyValueIterable.this.value)) {
                    return new ThunderEdge(GlmdbEdgeForKeyValueIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (GlmdbEdgeForKeyValueIterable.this.thunderGraph.getGlmdb().getNextEdgeForKeyValue(tc.getEdgeCursor(), edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray, GlmdbEdgeForKeyValueIterable.this.key, GlmdbEdgeForKeyValueIterable.this.value)) {
                    return new ThunderEdge(GlmdbEdgeForKeyValueIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }
}
