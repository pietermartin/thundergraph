package org.glmdb.blueprints.iter._short;

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
public class EdgeShortIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private short value;

    public EdgeShortIndexIterable(ThunderGraph thunderGraph, String key, short value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeShortIndexIterator();
    }

    private final class EdgeShortIndexIterator implements Iterator<ThunderEdge> {

        private ThunderEdge next;
        private boolean goToFirst = true;
        private Cursor edgeStringIndexDbCursor;
        private Cursor edgeDbCursor;
        private boolean cursorIsReadOnly;

        public EdgeShortIndexIterator() {
            this.cursorIsReadOnly = EdgeShortIndexIterable.this.tc.isReadOnly();
            this.edgeStringIndexDbCursor = EdgeShortIndexIterable.this.thunderGraph.getThunder().openCursor(EdgeShortIndexIterable.this.tc.getTxn(), DbEnum.EDGE_SHORT_INDEX);
            EdgeShortIndexIterable.this.tc.addIteratorCursor(EdgeShortIndexIterable.this, this.edgeStringIndexDbCursor);
            this.edgeDbCursor = EdgeShortIndexIterable.this.thunderGraph.getThunder().openCursor(EdgeShortIndexIterable.this.tc.getTxn(), DbEnum.EDGE_DB);
            EdgeShortIndexIterable.this.tc.addIteratorCursor(EdgeShortIndexIterable.this, this.edgeDbCursor);
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
                if (EdgeShortIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromShortIndex(this.edgeStringIndexDbCursor, this.edgeDbCursor, EdgeShortIndexIterable.this.key, EdgeShortIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeShortIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (EdgeShortIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromShortIndex(this.edgeStringIndexDbCursor, this.edgeDbCursor, EdgeShortIndexIterable.this.key, EdgeShortIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeShortIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
