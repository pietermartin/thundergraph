package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Edge;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class GlmdbEdgesFromVertexIterable<T extends Edge> implements Iterable<GlmdbEdge> {

    private final GlmdbGraph glmdbGraph;
    private final TransactionAndCursor tc;
    private final long vertexId;
    private final Direction direction;
    private final List<String> labels;

    public GlmdbEdgesFromVertexIterable(GlmdbGraph glmdbGraph, long vertexId, Direction direction, String[] labels) {
        this.glmdbGraph = glmdbGraph;
        this.tc = this.glmdbGraph.getReadOnlyTx();
        this.vertexId = vertexId;
        this.direction = direction;
        this.labels = new ArrayList<String>(Arrays.asList(labels));
    }

    @Override
    public Iterator<GlmdbEdge> iterator() {
        if (this.labels.isEmpty()) {
            return null;
        } else {
            return new EdgesIteratorForLabel();
        }
    }

    private class EdgesIteratorForLabel implements Iterator<GlmdbEdge> {

        private GlmdbEdge next;
        private boolean goToFirst = true;
        private String currentLabel;
        private Iterator<String> labelIterator;

        public EdgesIteratorForLabel() {
            this.labelIterator = GlmdbEdgesFromVertexIterable.this.labels.iterator();
            //No need to check hasNext as Iterator<GlmdbEdge> iterator() ensures there is at least one label.
            this.currentLabel = this.labelIterator.next();
        }

        @Override
        public boolean hasNext() {
            this.next = internalNext();
            return this.next != null;
        }

        @Override
        public GlmdbEdge next() {
            return this.next;
        }

        @Override
        public void remove() {
            //To change body of implemented methods use File | Settings | File Templates.
        }

        private GlmdbEdge internalNext() {

            long edgeIdArray[] = new long[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];

            while (this.currentLabel != null) {
                if (this.goToFirst) {
                    this.goToFirst = false;
                    if (GlmdbEdgesFromVertexIterable.this.glmdbGraph.getGlmdb().getFirstEdgeFromVertex(
                            tc.getVertexCursor(), currentLabel, GlmdbEdgesFromVertexIterable.this.vertexId, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                        return new GlmdbEdge(GlmdbEdgesFromVertexIterable.this.glmdbGraph, edgeIdArray[0], currentLabel, outVertexIdArray[0], inVertexIdArray[0]);
                    } else {
                         if (this.labelIterator.hasNext()) {
                             this.currentLabel = this.labelIterator.next();
                             this.goToFirst = true;
                         } else {
                             this.currentLabel = null;
                         }
                    }
                } else {
                    if (GlmdbEdgesFromVertexIterable.this.glmdbGraph.getGlmdb().getNextEdgeFromVertex(
                            tc.getVertexCursor(), currentLabel, GlmdbEdgesFromVertexIterable.this.vertexId, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                        return new GlmdbEdge(GlmdbEdgesFromVertexIterable.this.glmdbGraph, edgeIdArray[0], currentLabel, outVertexIdArray[0], inVertexIdArray[0]);
                    } else {
                        if (this.labelIterator.hasNext()) {
                            this.currentLabel = this.labelIterator.next();
                            this.goToFirst = true;
                        } else {
                            this.currentLabel = null;
                        }
                    }
                }
            }
            return null;

        }

    }


}
