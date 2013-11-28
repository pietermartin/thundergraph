package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Vertex;

import java.util.Iterator;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class GlmdbVertexForKeyValueIterable<T extends Vertex> implements Iterable<GlmdbVertex> {

    private final GlmdbGraph glmdbGraph;
    private final TransactionAndCursor tc;
    private String key;
    private Object value;

    public GlmdbVertexForKeyValueIterable(GlmdbGraph glmdbGraph, String key, Object value) {
        this.glmdbGraph = glmdbGraph;
        this.tc = this.glmdbGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<GlmdbVertex> iterator() {
        return new Iterator<GlmdbVertex>() {

            private GlmdbVertex next;
            private boolean goToFirst = true;

            @Override
            public boolean hasNext() {
                this.next = internalNext();
                return this.next != null;
            }

            @Override
            public GlmdbVertex next() {
                return this.next;
            }

            @Override
            public void remove() {
                //To change body of implemented methods use File | Settings | File Templates.
            }

            private GlmdbVertex internalNext() {
                long vertexIdArray[] = new long[1];
                if (this.goToFirst) {
                    this.goToFirst = false;
                    if (GlmdbVertexForKeyValueIterable.this.glmdbGraph.getGlmdb().getFirstVertexForKeyValue(tc.getVertexCursor(), vertexIdArray, GlmdbVertexForKeyValueIterable.this.key, GlmdbVertexForKeyValueIterable.this.value)) {
                        return new GlmdbVertex(GlmdbVertexForKeyValueIterable.this.glmdbGraph, vertexIdArray[0]);
                    } else {
                        return null;
                    }
                } else {
                    if (GlmdbVertexForKeyValueIterable.this.glmdbGraph.getGlmdb().getNextVertexForKeyValue(tc.getVertexCursor(), vertexIdArray, GlmdbVertexForKeyValueIterable.this.key, GlmdbVertexForKeyValueIterable.this.value)) {
                        return new GlmdbVertex(GlmdbVertexForKeyValueIterable.this.glmdbGraph, vertexIdArray[0]);
                    } else {
                        return null;
                    }
                }
            }

        };
    }
}
