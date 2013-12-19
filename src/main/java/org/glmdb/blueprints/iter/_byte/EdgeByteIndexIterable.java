package org.glmdb.blueprints.iter._byte;

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
public class EdgeByteIndexIterable<T extends Vertex> implements Iterable<ThunderEdge> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private byte value;

    public EdgeByteIndexIterable(ThunderGraph thunderGraph, String key, byte value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeByteIndexIterator();
    }

    private final class EdgeByteIndexIterator implements Iterator<ThunderEdge> {

        private ThunderEdge next;
        private boolean goToFirst = true;
        private Cursor edgeStringIndexDbCursor;
        private Cursor edgeDbCursor;
        private boolean cursorIsReadOnly;

        public EdgeByteIndexIterator() {
            this.cursorIsReadOnly = EdgeByteIndexIterable.this.tc.isReadOnly();
            this.edgeStringIndexDbCursor = EdgeByteIndexIterable.this.thunderGraph.getThunder().openCursor(EdgeByteIndexIterable.this.tc.getTxn(), DbEnum.EDGE_BYTE_INDEX);
            EdgeByteIndexIterable.this.tc.addIteratorCursor(this.edgeStringIndexDbCursor);
            this.edgeDbCursor = EdgeByteIndexIterable.this.thunderGraph.getThunder().openCursor(EdgeByteIndexIterable.this.tc.getTxn(), DbEnum.EDGE_DB);
            EdgeByteIndexIterable.this.tc.addIteratorCursor(this.edgeDbCursor);
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
                if (EdgeByteIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromByteIndex(this.edgeStringIndexDbCursor, this.edgeDbCursor, EdgeByteIndexIterable.this.key, EdgeByteIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeByteIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (EdgeByteIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromByteIndex(this.edgeStringIndexDbCursor, this.edgeDbCursor, EdgeByteIndexIterable.this.key, EdgeByteIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeByteIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
