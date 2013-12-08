package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Vertex;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class GlmdbVertexForKeyValueIterable<T extends Vertex> implements Iterable<ThunderVertex> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private Object value;

    public GlmdbVertexForKeyValueIterable(ThunderGraph thunderGraph, String key, Object value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexForKeyValueIterable();
    }

    private final class VertexForKeyValueIterable implements Iterator<ThunderVertex> {

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
            //To change body of implemented methods use File | Settings | File Templates.
        }

        private ThunderVertex internalNext() {
            long vertexIdArray[] = new long[1];
            if (this.goToFirst) {
                this.goToFirst = false;
                if (GlmdbVertexForKeyValueIterable.this.thunderGraph.getGlmdb().getFirstVertexForKeyValue(tc.getVertexCursor(), vertexIdArray, GlmdbVertexForKeyValueIterable.this.key, GlmdbVertexForKeyValueIterable.this.value)) {
                    return new ThunderVertex(GlmdbVertexForKeyValueIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (GlmdbVertexForKeyValueIterable.this.thunderGraph.getGlmdb().getNextVertexForKeyValue(tc.getVertexCursor(), vertexIdArray, GlmdbVertexForKeyValueIterable.this.key, GlmdbVertexForKeyValueIterable.this.value)) {
                    return new ThunderVertex(GlmdbVertexForKeyValueIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }
}
