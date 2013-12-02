package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Edge;
import org.glmdb.blueprints.jni.Cursor;

import java.util.*;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class GlmdbEdgesFromVertexIterable<T extends Edge> implements Iterable<GlmdbEdge> {

    private final GlmdbGraph glmdbGraph;
    private TransactionAndCursor tc;
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
            return new EdgesIterator();
        } else {
            return new EdgesIteratorForLabel();
        }
    }

    private class EdgesIteratorForLabel implements Iterator<GlmdbEdge> {

        private Cursor cursor;
        private boolean cursorIsReadOnly;
        private GlmdbEdge internalNext;
        private GlmdbEdge next;
        private boolean goToFirst = true;
        private String currentLabel;
        private Iterator<String> labelIterator;

        private EdgesIteratorForLabel() {
            this.labelIterator = GlmdbEdgesFromVertexIterable.this.labels.iterator();
            //No need to check hasNext as Iterator<GlmdbEdge> iterator() ensures there is at least one label.
            this.currentLabel = this.labelIterator.next();
            this.cursorIsReadOnly = GlmdbEdgesFromVertexIterable.this.tc.isReadOnly();
            this.cursor = GlmdbEdgesFromVertexIterable.this.glmdbGraph.getGlmdb().openCursorToVertexDb(GlmdbEdgesFromVertexIterable.this.tc.getTxn());
            GlmdbEdgesFromVertexIterable.this.tc.addIteratorCursor(this.cursor);
        }

        @Override
        public boolean hasNext() {
            if (this.next == null) {
                this.next = internalNext();
                this.internalNext = this.next;
            }
            return this.next != null;
        }

        @Override
        public GlmdbEdge next() {
            if (this.next == null) {
                this.next = internalNext();
                if (this.next == null) {
                    throw new NoSuchElementException();
                }
                this.internalNext = this.next;
            }
            GlmdbEdge result = this.next;
            this.next = null;
            return result;
        }

        @Override
        public void remove() {
            if (this.cursorIsReadOnly) {
                //Upgrade transaction to a writable one.
                //Replace the current cursor with a new one from the writable transaction
                GlmdbEdgesFromVertexIterable.this.tc = GlmdbEdgesFromVertexIterable.this.glmdbGraph.getWriteTx();
                this.cursorIsReadOnly = false;
                this.cursor = GlmdbEdgesFromVertexIterable.this.glmdbGraph.getGlmdb().openAndPositionCursorOnEdgeInVertexDb(
                        GlmdbEdgesFromVertexIterable.this.tc.getTxn(),
                        GlmdbEdgesFromVertexIterable.this.vertexId,
                        (this.internalNext.getOutVertexId() == GlmdbEdgesFromVertexIterable.this.vertexId ? Direction.OUT : Direction.IN),
                        this.internalNext.getLabel(),
                        this.internalNext.id
                );
            }
            GlmdbEdgesFromVertexIterable.this.glmdbGraph.getGlmdb().removeEdge(GlmdbEdgesFromVertexIterable.this.tc.getTxn(), this.internalNext.id);
        }

        private GlmdbEdge internalNext() {

            long edgeIdArray[] = new long[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];

            while (this.currentLabel != null) {
                if (this.goToFirst) {
                    this.goToFirst = false;
                    if (GlmdbEdgesFromVertexIterable.this.glmdbGraph.getGlmdb().getFirstEdgeFromVertex(
                            this.cursor, GlmdbEdgesFromVertexIterable.this.direction, currentLabel, GlmdbEdgesFromVertexIterable.this.vertexId, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
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
                            this.cursor, GlmdbEdgesFromVertexIterable.this.direction, currentLabel, GlmdbEdgesFromVertexIterable.this.vertexId, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
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

    private class EdgesIterator implements Iterator<GlmdbEdge> {

        private Cursor cursor;
        private boolean cursorIsReadOnly;
        private GlmdbEdge next;
        private GlmdbEdge internalNext;
        private boolean goToFirst = true;

        private EdgesIterator() {
            this.cursorIsReadOnly = GlmdbEdgesFromVertexIterable.this.tc.isReadOnly();
            this.cursor = GlmdbEdgesFromVertexIterable.this.glmdbGraph.getGlmdb().openCursorToVertexDb(GlmdbEdgesFromVertexIterable.this.tc.getTxn());
            GlmdbEdgesFromVertexIterable.this.tc.addIteratorCursor(this.cursor);
        }

        @Override
        public boolean hasNext() {
            if (this.next == null) {
                this.next = internalNext();
                this.internalNext = this.next;
            }
            return this.next != null;
        }

        @Override
        public GlmdbEdge next() {
            if (this.next == null) {
                this.next = internalNext();
                if (this.next == null) {
                    throw new NoSuchElementException();
                }
                this.internalNext = this.next;
            }
            GlmdbEdge result = this.next;
            this.next = null;
            return result;
        }

        @Override
        public void remove() {
            if (this.cursorIsReadOnly) {
                //Upgrade transaction to a writable one.
                //Replace the current cursor with a new one from the writable transaction
                GlmdbEdgesFromVertexIterable.this.tc = GlmdbEdgesFromVertexIterable.this.glmdbGraph.getWriteTx();
                this.cursorIsReadOnly = false;
                this.cursor = GlmdbEdgesFromVertexIterable.this.glmdbGraph.getGlmdb().openAndPositionCursorOnEdgeInVertexDb(
                        GlmdbEdgesFromVertexIterable.this.tc.getTxn(),
                        GlmdbEdgesFromVertexIterable.this.vertexId,
                        (this.internalNext.getOutVertexId() == GlmdbEdgesFromVertexIterable.this.vertexId ? Direction.OUT : Direction.IN),
                        this.internalNext.getLabel(),
                        this.internalNext.id
                );
            }
            GlmdbEdgesFromVertexIterable.this.glmdbGraph.getGlmdb().removeEdge(GlmdbEdgesFromVertexIterable.this.tc.getTxn(), this.internalNext.id);
        }

        private GlmdbEdge internalNext() {

            String labelArray[] = new String[1];
            long edgeIdArray[] = new long[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];

            if (this.goToFirst) {
                this.goToFirst = false;
                if (GlmdbEdgesFromVertexIterable.this.glmdbGraph.getGlmdb().getFirstEdgeFromVertex(
                        this.cursor, GlmdbEdgesFromVertexIterable.this.direction, GlmdbEdgesFromVertexIterable.this.vertexId, labelArray, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                    return new GlmdbEdge(GlmdbEdgesFromVertexIterable.this.glmdbGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (GlmdbEdgesFromVertexIterable.this.glmdbGraph.getGlmdb().getNextEdgeFromVertex(
                        this.cursor, GlmdbEdgesFromVertexIterable.this.direction, GlmdbEdgesFromVertexIterable.this.vertexId, labelArray, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                    return new GlmdbEdge(GlmdbEdgesFromVertexIterable.this.glmdbGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }
    }

}
