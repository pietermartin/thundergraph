package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Vertex;

import java.util.Iterator;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class GlmdbAllVertexIterable<T extends Vertex> implements Iterable<ThunderVertex> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;

    public GlmdbAllVertexIterable(ThunderGraph thunderGraph) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new Iterator<ThunderVertex>() {

            private ThunderVertex next;
            private boolean goToFirst = true;

            @Override
            public boolean hasNext() {
                this.next = internalNext();
                return this.next != null;
            }

            @Override
            public ThunderVertex next() {
                return this.next;
            }

            @Override
            public void remove() {
                //To change body of implemented methods use File | Settings | File Templates.
            }

            private ThunderVertex internalNext() {
                long vertexIdArray[] = new long[1];
                if (this.goToFirst) {
                    this.goToFirst = false;
                    if (GlmdbAllVertexIterable.this.thunderGraph.getGlmdb().getFirstVertex(tc.getVertexCursor(), vertexIdArray)) {
                        return new ThunderVertex(GlmdbAllVertexIterable.this.thunderGraph, vertexIdArray[0]);
                    } else {
                        return null;
                    }
                } else {
                    if (GlmdbAllVertexIterable.this.thunderGraph.getGlmdb().getNextVertex(tc.getVertexCursor(), vertexIdArray)) {
                        return new ThunderVertex(GlmdbAllVertexIterable.this.thunderGraph, vertexIdArray[0]);
                    } else {
                        return null;
                    }
                }
            }

        };
    }
}
