package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.*;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class VertexesFromVertexIterable<T extends Vertex> implements Iterable<ThunderVertex> {

    private final ThunderGraph thunderGraph;
    private TransactionAndCursor tc;
    private final long vertexId;
    private final Direction direction;
    private final List<String> labels;

    public VertexesFromVertexIterable(ThunderGraph thunderGraph, long vertexId, Direction direction, String[] labels) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.vertexId = vertexId;
        this.direction = direction;
        this.labels = new ArrayList<String>(Arrays.asList(labels));
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        if (this.labels.isEmpty()) {
            return new VertexesIterator();
        } else {
            return new VertexesIteratorForLabel();
        }
    }

    private class VertexesIteratorForLabel implements Iterator<ThunderVertex> {

        private Cursor cursor;
        private boolean cursorIsReadOnly;
        private ThunderVertex internalNext;
        private ThunderVertex next;
        private boolean goToFirst = true;
        private String currentLabel;
        private long currentEdgeOutVertexId;
        private Iterator<String> labelIterator;

        private VertexesIteratorForLabel() {
            this.labelIterator = VertexesFromVertexIterable.this.labels.iterator();
            //No need to check hasNext as Iterator<ThunderEdge> iterator() ensures there is at least one label.
            this.currentLabel = this.labelIterator.next();
            this.cursorIsReadOnly = VertexesFromVertexIterable.this.tc.isReadOnly();
            this.cursor = VertexesFromVertexIterable.this.thunderGraph.getThunder().openCursor(VertexesFromVertexIterable.this.tc.getTxn(), DbEnum.VERTEX_DB);
            VertexesFromVertexIterable.this.tc.addIteratorCursor(this.cursor);
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
        public ThunderVertex next() {
            if (this.next == null) {
                this.next = internalNext();
                if (this.next == null) {
                    throw new NoSuchElementException();
                }
                this.internalNext = this.next;
            }
            ThunderVertex result = this.next;
            this.next = null;
            return result;
        }

        @Override
        public void remove() {
            if (this.cursorIsReadOnly) {
                //Upgrade transaction to a writable one.
                //Replace the current cursor with a new one from the writable transaction
                VertexesFromVertexIterable.this.tc = VertexesFromVertexIterable.this.thunderGraph.getWriteTx();
                this.cursorIsReadOnly = false;
                this.cursor = VertexesFromVertexIterable.this.thunderGraph.getThunder().openAndPositionCursorOnEdgeInVertexDb(
                        VertexesFromVertexIterable.this.tc.getTxn(),
                        VertexesFromVertexIterable.this.vertexId,
                        (this.currentEdgeOutVertexId == VertexesFromVertexIterable.this.vertexId ? Direction.OUT : Direction.IN),
                        this.currentLabel,
                        this.internalNext.id
                );
            }
            VertexesFromVertexIterable.this.thunderGraph.getThunder().removeVertex(VertexesFromVertexIterable.this.tc.getTxn(), this.internalNext.id);
        }

        private ThunderVertex internalNext() {

            long edgeIdArray[] = new long[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];

            while (this.currentLabel != null) {
                if (this.goToFirst) {
                    this.goToFirst = false;
                    if (VertexesFromVertexIterable.this.thunderGraph.getThunder().getFirstEdgeFromVertex(
                            this.cursor, VertexesFromVertexIterable.this.direction, currentLabel, VertexesFromVertexIterable.this.vertexId, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                        this.currentEdgeOutVertexId = outVertexIdArray[0];
                        //Return the vertex that is not the from vertex.
                        if (outVertexIdArray[0] == VertexesFromVertexIterable.this.vertexId) {
                            return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, inVertexIdArray[0]);
                        } else {
                            return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, outVertexIdArray[0]);
                        }
                    } else {
                         if (this.labelIterator.hasNext()) {
                             this.currentLabel = this.labelIterator.next();
                             this.goToFirst = true;
                         } else {
                             this.currentLabel = null;
                         }
                    }
                } else {
                    if (VertexesFromVertexIterable.this.thunderGraph.getThunder().getNextEdgeFromVertex(
                            this.cursor, VertexesFromVertexIterable.this.direction, currentLabel, VertexesFromVertexIterable.this.vertexId, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                        this.currentEdgeOutVertexId = outVertexIdArray[0];
                        //Return the vertex that is not the from vertex.
                        if (outVertexIdArray[0] == VertexesFromVertexIterable.this.vertexId) {
                            return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, inVertexIdArray[0]);
                        } else {
                            return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, outVertexIdArray[0]);
                        }
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

    private class VertexesIterator implements Iterator<ThunderVertex> {

        private Cursor cursor;
        private boolean cursorIsReadOnly;
        private ThunderVertex next;
        private ThunderVertex internalNext;
        private boolean goToFirst = true;
        private String currentLabel;
        private long currentEdgeOutVertexId;

        private VertexesIterator() {
            this.cursorIsReadOnly = VertexesFromVertexIterable.this.tc.isReadOnly();
            this.cursor = VertexesFromVertexIterable.this.thunderGraph.getThunder().openCursor(VertexesFromVertexIterable.this.tc.getTxn(), DbEnum.VERTEX_DB);
            VertexesFromVertexIterable.this.tc.addIteratorCursor(this.cursor);
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
        public ThunderVertex next() {
            if (this.next == null) {
                this.next = internalNext();
                if (this.next == null) {
                    throw new NoSuchElementException();
                }
                this.internalNext = this.next;
            }
            ThunderVertex result = this.next;
            this.next = null;
            return result;
        }

        @Override
        public void remove() {
            if (this.cursorIsReadOnly) {
                //Upgrade transaction to a writable one.
                //Replace the current cursor with a new one from the writable transaction
                VertexesFromVertexIterable.this.tc = VertexesFromVertexIterable.this.thunderGraph.getWriteTx();
                this.cursorIsReadOnly = false;
                this.cursor = VertexesFromVertexIterable.this.thunderGraph.getThunder().openAndPositionCursorOnEdgeInVertexDb(
                        VertexesFromVertexIterable.this.tc.getTxn(),
                        VertexesFromVertexIterable.this.vertexId,
                        (this.currentEdgeOutVertexId == VertexesFromVertexIterable.this.vertexId ? Direction.OUT : Direction.IN),
                        this.currentLabel,
                        this.internalNext.id
                );
            }
            VertexesFromVertexIterable.this.thunderGraph.getThunder().removeVertex(VertexesFromVertexIterable.this.tc.getTxn(), this.internalNext.id);
        }

        private ThunderVertex internalNext() {

            String labelArray[] = new String[1];
            long edgeIdArray[] = new long[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];

            if (this.goToFirst) {
                this.goToFirst = false;
                if (VertexesFromVertexIterable.this.thunderGraph.getThunder().getFirstEdgeFromVertex(
                        this.cursor, VertexesFromVertexIterable.this.direction, VertexesFromVertexIterable.this.vertexId, labelArray, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                    this.currentLabel = labelArray[0];
                    this.currentEdgeOutVertexId = outVertexIdArray[0];
                    return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexesFromVertexIterable.this.thunderGraph.getThunder().getNextEdgeFromVertex(
                        this.cursor, VertexesFromVertexIterable.this.direction, VertexesFromVertexIterable.this.vertexId, labelArray, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                    this.currentLabel = labelArray[0];
                    this.currentEdgeOutVertexId = outVertexIdArray[0];
                    return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }
    }

}
