package org.glmdb.blueprints.iter._byte;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.ThunderVertex;
import org.glmdb.blueprints.TransactionAndCursor;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class VertexForKeyByteValueIterable<T extends Vertex> implements Iterable<ThunderVertex> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private byte value;

    public VertexForKeyByteValueIterable(ThunderGraph thunderGraph, String key, byte value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexForKeyByteValueIterator();
    }

    private final class VertexForKeyByteValueIterator implements Iterator<ThunderVertex> {

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
                if (VertexForKeyByteValueIterable.this.thunderGraph.getThunder().getFirstVertexForKeyByteValue(tc.getVertexCursor(), vertexIdArray, VertexForKeyByteValueIterable.this.key, VertexForKeyByteValueIterable.this.value)) {
                    return new ThunderVertex(VertexForKeyByteValueIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexForKeyByteValueIterable.this.thunderGraph.getThunder().getNextVertexForKeyByteValue(tc.getVertexCursor(), vertexIdArray, VertexForKeyByteValueIterable.this.key, VertexForKeyByteValueIterable.this.value)) {
                    return new ThunderVertex(VertexForKeyByteValueIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }
}
