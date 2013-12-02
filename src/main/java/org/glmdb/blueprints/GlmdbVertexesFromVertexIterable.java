package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.jni.Cursor;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class GlmdbVertexesFromVertexIterable<T extends Vertex> implements Iterable<GlmdbVertex> {

    private final GlmdbGraph glmdbGraph;
    private final TransactionAndCursor tc;
    private final long vertexId;
    private final Direction direction;
    private final List<String> labels;

    public GlmdbVertexesFromVertexIterable(GlmdbGraph glmdbGraph, long vertexId, Direction direction, String[] labels) {
        this.glmdbGraph = glmdbGraph;
        this.tc = this.glmdbGraph.getReadOnlyTx();
        this.vertexId = vertexId;
        this.direction = direction;
        this.labels = new ArrayList<String>(Arrays.asList(labels));
    }

    @Override
    public Iterator<GlmdbVertex> iterator() {
        if (this.labels.isEmpty()) {
            return new VertexesIterator();
        } else {
            return new VertexesIteratorForLabel();
        }
    }

    private class VertexesIteratorForLabel implements Iterator<GlmdbVertex> {

        private Cursor cursor;
        private GlmdbVertex next;
        private boolean goToFirst = true;
        private String currentLabel;
        private Iterator<String> labelIterator;

        private VertexesIteratorForLabel() {
            this.labelIterator = GlmdbVertexesFromVertexIterable.this.labels.iterator();
            //No need to check hasNext as Iterator<GlmdbEdge> iterator() ensures there is at least one label.
            this.currentLabel = this.labelIterator.next();
            this.cursor = GlmdbVertexesFromVertexIterable.this.glmdbGraph.getGlmdb().openCursorToVertexDb(GlmdbVertexesFromVertexIterable.this.tc.getTxn());
            GlmdbVertexesFromVertexIterable.this.tc.addIteratorCursor(this.cursor);
        }

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
            //TODO
        }

        private GlmdbVertex internalNext() {

            long edgeIdArray[] = new long[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];

            while (this.currentLabel != null) {
                if (this.goToFirst) {
                    this.goToFirst = false;
                    if (GlmdbVertexesFromVertexIterable.this.glmdbGraph.getGlmdb().getFirstEdgeFromVertex(
                            this.cursor, GlmdbVertexesFromVertexIterable.this.direction, currentLabel, GlmdbVertexesFromVertexIterable.this.vertexId, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                        return new GlmdbVertex(GlmdbVertexesFromVertexIterable.this.glmdbGraph, inVertexIdArray[0]);
                    } else {
                         if (this.labelIterator.hasNext()) {
                             this.currentLabel = this.labelIterator.next();
                             this.goToFirst = true;
                         } else {
                             this.currentLabel = null;
                         }
                    }
                } else {
                    if (GlmdbVertexesFromVertexIterable.this.glmdbGraph.getGlmdb().getNextEdgeFromVertex(
                            this.cursor, GlmdbVertexesFromVertexIterable.this.direction, currentLabel, GlmdbVertexesFromVertexIterable.this.vertexId, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                        return new GlmdbVertex(GlmdbVertexesFromVertexIterable.this.glmdbGraph, inVertexIdArray[0]);
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

    private class VertexesIterator implements Iterator<GlmdbVertex> {

        private Cursor cursor;
        private GlmdbVertex next;
        private boolean goToFirst = true;

        private VertexesIterator() {
            this.cursor = GlmdbVertexesFromVertexIterable.this.glmdbGraph.getGlmdb().openCursorToVertexDb(GlmdbVertexesFromVertexIterable.this.tc.getTxn());
            GlmdbVertexesFromVertexIterable.this.tc.addIteratorCursor(this.cursor);
        }

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
            //TODO
        }

        private GlmdbVertex internalNext() {

            String labelArray[] = new String[1];
            long edgeIdArray[] = new long[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];

            if (this.goToFirst) {
                this.goToFirst = false;
                if (GlmdbVertexesFromVertexIterable.this.glmdbGraph.getGlmdb().getFirstEdgeFromVertex(
                        this.cursor, GlmdbVertexesFromVertexIterable.this.direction, GlmdbVertexesFromVertexIterable.this.vertexId, labelArray, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                    return new GlmdbVertex(GlmdbVertexesFromVertexIterable.this.glmdbGraph, inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (GlmdbVertexesFromVertexIterable.this.glmdbGraph.getGlmdb().getNextEdgeFromVertex(
                        this.cursor, GlmdbVertexesFromVertexIterable.this.direction, GlmdbVertexesFromVertexIterable.this.vertexId, labelArray, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                    return new GlmdbVertex(GlmdbVertexesFromVertexIterable.this.glmdbGraph, inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }
    }

}
