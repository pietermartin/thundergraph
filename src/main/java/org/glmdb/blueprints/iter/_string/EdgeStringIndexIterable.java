package org.glmdb.blueprints.iter._string;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderEdge;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.TransactionAndCursor;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class EdgeStringIndexIterable<T extends Vertex> implements Iterable<ThunderEdge> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private String value;

    public EdgeStringIndexIterable(ThunderGraph thunderGraph, String key, String value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeStringIndexIterator();
    }

    private final class EdgeStringIndexIterator implements Iterator<ThunderEdge> {

        private ThunderEdge next;
        private boolean goToFirst = true;
        private Cursor edgeStringIndexDbCursor;
        private Cursor edgeDbCursor;
        private boolean cursorIsReadOnly;

        public EdgeStringIndexIterator() {
            this.cursorIsReadOnly = EdgeStringIndexIterable.this.tc.isReadOnly();
            this.edgeStringIndexDbCursor = EdgeStringIndexIterable.this.thunderGraph.getThunder().openCursor(EdgeStringIndexIterable.this.tc.getTxn(), DbEnum.EDGE_STRING_INDEX);
            EdgeStringIndexIterable.this.tc.addIteratorCursor(this.edgeStringIndexDbCursor);
            this.edgeDbCursor = EdgeStringIndexIterable.this.thunderGraph.getThunder().openCursor(EdgeStringIndexIterable.this.tc.getTxn(), DbEnum.EDGE_DB);
            EdgeStringIndexIterable.this.tc.addIteratorCursor(this.edgeDbCursor);
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
                if (EdgeStringIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromStringIndex(this.edgeStringIndexDbCursor, this.edgeDbCursor, EdgeStringIndexIterable.this.key, EdgeStringIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeStringIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (EdgeStringIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromStringIndex(this.edgeStringIndexDbCursor, this.edgeDbCursor, EdgeStringIndexIterable.this.key, EdgeStringIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeStringIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
