package org.glmdb.blueprints.iter._boolean;

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
public class EdgeBooleanIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private boolean value;

    public EdgeBooleanIndexIterable(ThunderGraph thunderGraph, String key, boolean value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeBooleanIndexIterator();
    }

    private final class EdgeBooleanIndexIterator implements Iterator<ThunderEdge> {

        private ThunderEdge next;
        private boolean goToFirst = true;
        private Cursor edgeStringIndexDbCursor;
        private Cursor edgeDbCursor;
        private boolean cursorIsReadOnly;

        public EdgeBooleanIndexIterator() {
            this.cursorIsReadOnly = EdgeBooleanIndexIterable.this.tc.isReadOnly();
            this.edgeStringIndexDbCursor = EdgeBooleanIndexIterable.this.thunderGraph.getThunder().openCursor(EdgeBooleanIndexIterable.this.tc.getTxn(), DbEnum.EDGE_BOOLEAN_INDEX);
            EdgeBooleanIndexIterable.this.tc.addIteratorCursor(EdgeBooleanIndexIterable.this, this.edgeStringIndexDbCursor);
            this.edgeDbCursor = EdgeBooleanIndexIterable.this.thunderGraph.getThunder().openCursor(EdgeBooleanIndexIterable.this.tc.getTxn(), DbEnum.EDGE_DB);
            EdgeBooleanIndexIterable.this.tc.addIteratorCursor(EdgeBooleanIndexIterable.this, this.edgeDbCursor);
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
                if (EdgeBooleanIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromBooleanIndex(this.edgeStringIndexDbCursor, this.edgeDbCursor, EdgeBooleanIndexIterable.this.key, EdgeBooleanIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeBooleanIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (EdgeBooleanIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromBooleanIndex(this.edgeStringIndexDbCursor, this.edgeDbCursor, EdgeBooleanIndexIterable.this.key, EdgeBooleanIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeBooleanIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
