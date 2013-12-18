package org.glmdb.blueprints.iter;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Edge;
import org.glmdb.blueprints.ThunderEdge;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.TransactionAndCursor;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.*;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class EdgesFromVertexIterable<T extends Edge> implements Iterable<ThunderEdge> {

    private final ThunderGraph thunderGraph;
    private TransactionAndCursor tc;
    private final long vertexId;
    private final Direction direction;
    private final List<String> labels;

    public EdgesFromVertexIterable(ThunderGraph thunderGraph, long vertexId, Direction direction, String[] labels) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.vertexId = vertexId;
        this.direction = direction;
        this.labels = new ArrayList<String>(Arrays.asList(labels));
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        if (this.labels.isEmpty()) {
            return new EdgesIterator();
        } else {
            return new EdgesIteratorForLabel();
        }
    }

    private class EdgesIteratorForLabel implements Iterator<ThunderEdge> {

        private Cursor cursor;
        private boolean cursorIsReadOnly;
        private ThunderEdge internalNext;
        private ThunderEdge next;
        private boolean goToFirst = true;
        private String currentLabel;
        private Iterator<String> labelIterator;

        private EdgesIteratorForLabel() {
            this.labelIterator = EdgesFromVertexIterable.this.labels.iterator();
            //No need to check hasNext as Iterator<ThunderEdge> iterator() ensures there is at least one label.
            this.currentLabel = this.labelIterator.next();
            this.cursorIsReadOnly = EdgesFromVertexIterable.this.tc.isReadOnly();
            this.cursor = EdgesFromVertexIterable.this.thunderGraph.getThunder().openCursor(EdgesFromVertexIterable.this.tc.getTxn(), DbEnum.VERTEX_DB);
            EdgesFromVertexIterable.this.tc.addIteratorCursor(this.cursor);
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
        public ThunderEdge next() {
            if (this.next == null) {
                this.next = internalNext();
                if (this.next == null) {
                    throw new NoSuchElementException();
                }
                this.internalNext = this.next;
            }
            ThunderEdge result = this.next;
            this.next = null;
            return result;
        }

        @Override
        public void remove() {
            if (this.cursorIsReadOnly) {
                //Upgrade transaction to a writable one.
                //Replace the current cursor with a new one from the writable transaction
                EdgesFromVertexIterable.this.tc = EdgesFromVertexIterable.this.thunderGraph.getWriteTx();
                this.cursorIsReadOnly = false;
                this.cursor = EdgesFromVertexIterable.this.thunderGraph.getThunder().openAndPositionCursorOnEdgeInVertexDb(
                        EdgesFromVertexIterable.this.tc.getTxn(),
                        EdgesFromVertexIterable.this.vertexId,
                        (this.internalNext.getOutVertexId() == EdgesFromVertexIterable.this.vertexId ? Direction.OUT : Direction.IN),
                        this.internalNext.getLabel(),
                        this.internalNext.getInternalId()
                );
            }
            EdgesFromVertexIterable.this.thunderGraph.getThunder().removeEdge(EdgesFromVertexIterable.this.tc.getTxn(), this.internalNext.getInternalId());
        }

        private ThunderEdge internalNext() {

            long edgeIdArray[] = new long[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];

            while (this.currentLabel != null) {
                if (this.goToFirst) {
                    this.goToFirst = false;
                    if (EdgesFromVertexIterable.this.thunderGraph.getThunder().getFirstEdgeFromVertex(
                            this.cursor, EdgesFromVertexIterable.this.direction, currentLabel, EdgesFromVertexIterable.this.vertexId, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                        return new ThunderEdge(EdgesFromVertexIterable.this.thunderGraph, edgeIdArray[0], currentLabel, outVertexIdArray[0], inVertexIdArray[0]);
                    } else {
                        if (this.labelIterator.hasNext()) {
                            this.currentLabel = this.labelIterator.next();
                            this.goToFirst = true;
                        } else {
                            this.currentLabel = null;
                        }
                    }
                } else {
                    if (EdgesFromVertexIterable.this.thunderGraph.getThunder().getNextEdgeFromVertex(
                            this.cursor, EdgesFromVertexIterable.this.direction, currentLabel, EdgesFromVertexIterable.this.vertexId, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                        return new ThunderEdge(EdgesFromVertexIterable.this.thunderGraph, edgeIdArray[0], currentLabel, outVertexIdArray[0], inVertexIdArray[0]);
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

    private class EdgesIterator implements Iterator<ThunderEdge> {

        private Cursor cursor;
        private boolean cursorIsReadOnly;
        private ThunderEdge next;
        private ThunderEdge internalNext;
        private boolean goToFirst = true;

        private EdgesIterator() {
            this.cursorIsReadOnly = EdgesFromVertexIterable.this.tc.isReadOnly();
            this.cursor = EdgesFromVertexIterable.this.thunderGraph.getThunder().openCursor(EdgesFromVertexIterable.this.tc.getTxn(), DbEnum.VERTEX_DB);
            EdgesFromVertexIterable.this.tc.addIteratorCursor(this.cursor);
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
        public ThunderEdge next() {
            if (this.next == null) {
                this.next = internalNext();
                if (this.next == null) {
                    throw new NoSuchElementException();
                }
                this.internalNext = this.next;
            }
            ThunderEdge result = this.next;
            this.next = null;
            return result;
        }

        @Override
        public void remove() {
            if (this.cursorIsReadOnly) {
                //Upgrade transaction to a writable one.
                //Replace the current cursor with a new one from the writable transaction
                EdgesFromVertexIterable.this.tc = EdgesFromVertexIterable.this.thunderGraph.getWriteTx();
                this.cursorIsReadOnly = false;
                this.cursor = EdgesFromVertexIterable.this.thunderGraph.getThunder().openAndPositionCursorOnEdgeInVertexDb(
                        EdgesFromVertexIterable.this.tc.getTxn(),
                        EdgesFromVertexIterable.this.vertexId,
                        (this.internalNext.getOutVertexId() == EdgesFromVertexIterable.this.vertexId ? Direction.OUT : Direction.IN),
                        this.internalNext.getLabel(),
                        this.internalNext.getInternalId()
                );
            }
            EdgesFromVertexIterable.this.thunderGraph.getThunder().removeEdge(EdgesFromVertexIterable.this.tc.getTxn(), this.internalNext.getInternalId());
        }

        private ThunderEdge internalNext() {

            String labelArray[] = new String[1];
            long edgeIdArray[] = new long[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];

            if (this.goToFirst) {
                this.goToFirst = false;
                if (EdgesFromVertexIterable.this.thunderGraph.getThunder().getFirstEdgeFromVertex(
                        this.cursor, EdgesFromVertexIterable.this.direction, EdgesFromVertexIterable.this.vertexId, labelArray, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgesFromVertexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (EdgesFromVertexIterable.this.thunderGraph.getThunder().getNextEdgeFromVertex(
                        this.cursor, EdgesFromVertexIterable.this.direction, EdgesFromVertexIterable.this.vertexId, labelArray, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgesFromVertexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }
    }

}
