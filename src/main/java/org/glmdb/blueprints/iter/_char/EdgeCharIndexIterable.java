package org.glmdb.blueprints.iter._char;

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
public class EdgeCharIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private char value;

    public EdgeCharIndexIterable(ThunderGraph thunderGraph, String key, char value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeCharIndexIterator();
    }

    private final class EdgeCharIndexIterator implements Iterator<ThunderEdge> {

        private ThunderEdge next;
        private boolean goToFirst = true;
        private Cursor edgeStringIndexDbCursor;
        private Cursor edgeDbCursor;
        private boolean cursorIsReadOnly;

        public EdgeCharIndexIterator() {
            this.cursorIsReadOnly = EdgeCharIndexIterable.this.tc.isReadOnly();
            this.edgeStringIndexDbCursor = EdgeCharIndexIterable.this.thunderGraph.getThunder().openCursor(EdgeCharIndexIterable.this.tc.getTxn(), DbEnum.EDGE_CHAR_INDEX);
            EdgeCharIndexIterable.this.tc.addIteratorCursor(EdgeCharIndexIterable.this, this.edgeStringIndexDbCursor);
            this.edgeDbCursor = EdgeCharIndexIterable.this.thunderGraph.getThunder().openCursor(EdgeCharIndexIterable.this.tc.getTxn(), DbEnum.EDGE_DB);
            EdgeCharIndexIterable.this.tc.addIteratorCursor(EdgeCharIndexIterable.this, this.edgeDbCursor);
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
                if (EdgeCharIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromCharIndex(this.edgeStringIndexDbCursor, this.edgeDbCursor, EdgeCharIndexIterable.this.key, EdgeCharIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeCharIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (EdgeCharIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromCharIndex(this.edgeStringIndexDbCursor, this.edgeDbCursor, EdgeCharIndexIterable.this.key, EdgeCharIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeCharIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
