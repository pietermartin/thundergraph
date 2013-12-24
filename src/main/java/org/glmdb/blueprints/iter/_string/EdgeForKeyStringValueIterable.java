package org.glmdb.blueprints.iter._string;

import com.tinkerpop.blueprints.Edge;
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
public class EdgeForKeyStringValueIterable<T extends Edge> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private final ThunderGraph thunderGraph;
    private TransactionAndCursor tc;
    private String key;
    private String value;

    public EdgeForKeyStringValueIterable(ThunderGraph thunderGraph, String key, String value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeForKeyStringValueIterator();
    }

    private final class EdgeForKeyStringValueIterator implements Iterator<ThunderEdge>  {

        private ThunderEdge next;
        private ThunderEdge internalNext;
        private boolean goToFirst = true;
        private Cursor cursor;
        private boolean cursorIsReadOnly;

        private EdgeForKeyStringValueIterator() {
            this.cursorIsReadOnly = EdgeForKeyStringValueIterable.this.tc.isReadOnly();
            this.cursor = EdgeForKeyStringValueIterable.this.thunderGraph.getThunder().openCursor(EdgeForKeyStringValueIterable.this.tc.getTxn(), DbEnum.EDGE_DB);
            EdgeForKeyStringValueIterable.this.tc.addIteratorCursor(EdgeForKeyStringValueIterable.this, this.cursor);

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
                EdgeForKeyStringValueIterable.this.tc = EdgeForKeyStringValueIterable.this.thunderGraph.getWriteTx();
                this.cursorIsReadOnly = false;
                this.cursor = EdgeForKeyStringValueIterable.this.thunderGraph.getThunder().openAndPositionCursorOnEdgePropertyInEdgeDb(
                        EdgeForKeyStringValueIterable.this.tc.getTxn(),
                        this.next.getInternalId(),
                        EdgeForKeyStringValueIterable.this.key
                );
            }
            EdgeForKeyStringValueIterable.this.thunderGraph.getThunder().removeEdge(EdgeForKeyStringValueIterable.this.tc.getTxn(), this.internalNext.getInternalId());
        }

        private ThunderEdge internalNext() {
            long edgeIdArray[] = new long[1];
            String labelArray[] = new String[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];
            if (this.goToFirst) {
                this.goToFirst = false;
                if (EdgeForKeyStringValueIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyStringValue(this.cursor, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray, EdgeForKeyStringValueIterable.this.key, EdgeForKeyStringValueIterable.this.value)) {
                    return new ThunderEdge(EdgeForKeyStringValueIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (EdgeForKeyStringValueIterable.this.thunderGraph.getThunder().getNextEdgeForKeyStringValue(this.cursor, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray, EdgeForKeyStringValueIterable.this.key, EdgeForKeyStringValueIterable.this.value)) {
                    return new ThunderEdge(EdgeForKeyStringValueIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }
}
