package org.glmdb.blueprints.iter._long;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderEdge;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.TransactionAndCursor;
import org.glmdb.blueprints.iter.BaseThunderIterable;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class EdgeLongIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private long value;

    public EdgeLongIndexIterable(ThunderGraph thunderGraph, String key, long value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeLongIndexIterator();
    }

    private final class EdgeLongIndexIterator implements Iterator<ThunderEdge> {

        private ThunderEdge next;
        private boolean goToFirst = true;
        private Cursor edgeStringIndexDbCursor;
        private Cursor edgeDbCursor;
        private boolean cursorIsReadOnly;

        public EdgeLongIndexIterator() {
            this.cursorIsReadOnly = EdgeLongIndexIterable.this.tc.isReadOnly();
            this.edgeStringIndexDbCursor = EdgeLongIndexIterable.this.thunderGraph.getThunder().openCursor(EdgeLongIndexIterable.this.tc.getTxn(), DbEnum.EDGE_LONG_INDEX);
            EdgeLongIndexIterable.this.tc.addIteratorCursor(EdgeLongIndexIterable.this, this.edgeStringIndexDbCursor);
            this.edgeDbCursor = EdgeLongIndexIterable.this.thunderGraph.getThunder().openCursor(EdgeLongIndexIterable.this.tc.getTxn(), DbEnum.EDGE_DB);
            EdgeLongIndexIterable.this.tc.addIteratorCursor(EdgeLongIndexIterable.this, this.edgeDbCursor);
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
                if (EdgeLongIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromLongIndex(this.edgeStringIndexDbCursor, this.edgeDbCursor, EdgeLongIndexIterable.this.key, EdgeLongIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeLongIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (EdgeLongIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromLongIndex(this.edgeStringIndexDbCursor, this.edgeDbCursor, EdgeLongIndexIterable.this.key, EdgeLongIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeLongIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
