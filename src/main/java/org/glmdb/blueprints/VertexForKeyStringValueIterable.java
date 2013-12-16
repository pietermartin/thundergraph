package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Vertex;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class VertexForKeyStringValueIterable<T extends Vertex> implements Iterable<ThunderVertex> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private String value;

    public VertexForKeyStringValueIterable(ThunderGraph thunderGraph, String key, String value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexForKeyStringValueIterator();
    }

    private final class VertexForKeyStringValueIterator implements Iterator<ThunderVertex> {

        private ThunderVertex next;
        private boolean goToFirst = true;

        @Override
        public boolean hasNext() {
            if (this.next == null) {
                this.next = internalNext();
            }
            return this.next != null;
        }

        @Override
        public ThunderVertex next() {
            if (this.next == null) {
                this.next = internalNext();
                if (this.next == null) {
                    throw new NoSuchElementException();
                }
            }
            ThunderVertex result = this.next;
            this.next = null;
            return result;
        }

        @Override
        public void remove() {
            throw new RuntimeException("Not yet implemented!");
        }

        private ThunderVertex internalNext() {
            long vertexIdArray[] = new long[1];
            if (this.goToFirst) {
                this.goToFirst = false;
                if (VertexForKeyStringValueIterable.this.thunderGraph.getThunder().getFirstVertexForKeyStringValue(tc.getVertexCursor(), vertexIdArray, VertexForKeyStringValueIterable.this.key, VertexForKeyStringValueIterable.this.value)) {
                    return new ThunderVertex(VertexForKeyStringValueIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexForKeyStringValueIterable.this.thunderGraph.getThunder().getNextVertexForKeyStringValue(tc.getVertexCursor(), vertexIdArray, VertexForKeyStringValueIterable.this.key, VertexForKeyStringValueIterable.this.value)) {
                    return new ThunderVertex(VertexForKeyStringValueIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }
}
