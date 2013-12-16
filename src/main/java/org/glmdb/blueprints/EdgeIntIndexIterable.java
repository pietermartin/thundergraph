package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class EdgeIntIndexIterable<T extends Vertex> implements Iterable<ThunderEdge> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private int value;

    public EdgeIntIndexIterable(ThunderGraph thunderGraph, String key, int value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeIntIndexIterator();
    }

    private final class EdgeIntIndexIterator implements Iterator<ThunderEdge> {

        private ThunderEdge next;
        private boolean goToFirst = true;
        private Cursor edgeStringIndexDbCursor;
        private Cursor edgeDbCursor;
        private boolean cursorIsReadOnly;

        public EdgeIntIndexIterator() {
            this.cursorIsReadOnly = EdgeIntIndexIterable.this.tc.isReadOnly();
            this.edgeStringIndexDbCursor = EdgeIntIndexIterable.this.thunderGraph.getThunder().openCursor(EdgeIntIndexIterable.this.tc.getTxn(), DbEnum.EDGE_INT_INDEX);
            EdgeIntIndexIterable.this.tc.addIteratorCursor(this.edgeStringIndexDbCursor);
            this.edgeDbCursor = EdgeIntIndexIterable.this.thunderGraph.getThunder().openCursor(EdgeIntIndexIterable.this.tc.getTxn(), DbEnum.EDGE_DB);
            EdgeIntIndexIterable.this.tc.addIteratorCursor(this.edgeDbCursor);
        }

        @Override
        public boolean hasNext() {
            if (this.next == null) {
                this.next = internalNext();
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
            }
            ThunderEdge result = this.next;
            this.next = null;
            return result;
        }

        @Override
        public void remove() {
            throw new RuntimeException("Not yet implemented!");
        }

        private ThunderEdge internalNext() {
            long edgeIdArray[] = new long[1];
            String labelArray[] = new String[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];

            if (this.goToFirst) {
                this.goToFirst = false;
                if (EdgeIntIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromIntIndex(this.edgeStringIndexDbCursor, this.edgeDbCursor, EdgeIntIndexIterable.this.key, EdgeIntIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeIntIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (EdgeIntIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromIntIndex(this.edgeStringIndexDbCursor, this.edgeDbCursor, EdgeIntIndexIterable.this.key, EdgeIntIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeIntIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
