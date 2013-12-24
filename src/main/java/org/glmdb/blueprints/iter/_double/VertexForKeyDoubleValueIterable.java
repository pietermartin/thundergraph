package org.glmdb.blueprints.iter._double;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.ThunderVertex;
import org.glmdb.blueprints.TransactionAndCursor;
import org.glmdb.blueprints.iter.BaseThunderIterable;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class VertexForKeyDoubleValueIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private double value;

    public VertexForKeyDoubleValueIterable(ThunderGraph thunderGraph, String key, double value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexForKeyDoubleValueIterator();
    }

    private final class VertexForKeyDoubleValueIterator implements Iterator<ThunderVertex> {

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
                if (VertexForKeyDoubleValueIterable.this.thunderGraph.getThunder().getFirstVertexForKeyDoubleValue(tc.getVertexCursor(), vertexIdArray, VertexForKeyDoubleValueIterable.this.key, VertexForKeyDoubleValueIterable.this.value)) {
                    return new ThunderVertex(VertexForKeyDoubleValueIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexForKeyDoubleValueIterable.this.thunderGraph.getThunder().getNextVertexForKeyDoubleValue(tc.getVertexCursor(), vertexIdArray, VertexForKeyDoubleValueIterable.this.key, VertexForKeyDoubleValueIterable.this.value)) {
                    return new ThunderVertex(VertexForKeyDoubleValueIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }
}
