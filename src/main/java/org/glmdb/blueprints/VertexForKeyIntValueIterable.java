package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Vertex;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class VertexForKeyIntValueIterable<T extends Vertex> implements Iterable<ThunderVertex> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private int value;

    public VertexForKeyIntValueIterable(ThunderGraph thunderGraph, String key, int value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexForKeyIntValueIterator();
    }

    private final class VertexForKeyIntValueIterator implements Iterator<ThunderVertex> {

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
                if (VertexForKeyIntValueIterable.this.thunderGraph.getThunder().getFirstVertexForKeyIntValue(tc.getVertexCursor(), vertexIdArray, VertexForKeyIntValueIterable.this.key, VertexForKeyIntValueIterable.this.value)) {
                    return new ThunderVertex(VertexForKeyIntValueIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexForKeyIntValueIterable.this.thunderGraph.getThunder().getNextVertexForKeyIntValue(tc.getVertexCursor(), vertexIdArray, VertexForKeyIntValueIterable.this.key, VertexForKeyIntValueIterable.this.value)) {
                    return new ThunderVertex(VertexForKeyIntValueIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }
}
