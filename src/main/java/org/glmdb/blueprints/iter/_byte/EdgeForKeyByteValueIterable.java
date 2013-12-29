package org.glmdb.blueprints.iter._byte;

import com.tinkerpop.blueprints.Edge;
import org.glmdb.blueprints.ThunderEdge;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.TransactionAndCursor;
import org.glmdb.blueprints.iter.BaseThunderIterable;
import org.glmdb.blueprints.iter.BaseThunderIterator;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class EdgeForKeyByteValueIterable<T extends Edge> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private String key;
    private byte value;

    public EdgeForKeyByteValueIterable(ThunderGraph thunderGraph, String key, byte value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeForKeyByteValueIterator();
    }

    private final class EdgeForKeyByteValueIterator extends BaseThunderIterator<ThunderEdge> implements Iterator  {

        private boolean goToFirst = true;

        private EdgeForKeyByteValueIterator() {
            super(EdgeForKeyByteValueIterable.this.tc);
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.EDGE_DB;
        }

        @Override
        protected EdgeForKeyByteValueIterable getParentIterable() {
            return EdgeForKeyByteValueIterable.this;
        }

        @Override
        public void remove() {
            if (this.cursorIsReadOnly) {
                //Upgrade transaction to a writable one.
                //Replace the current cursor with a new one from the writable transaction
                this.tc = EdgeForKeyByteValueIterable.this.thunderGraph.getWriteTx();
                this.cursorIsReadOnly = false;
                this.cursor = EdgeForKeyByteValueIterable.this.thunderGraph.getThunder().openAndPositionCursorOnEdgePropertyInEdgeDb(
                        this.tc.getTxn(),
                        this.next.getInternalId(),
                        EdgeForKeyByteValueIterable.this.key
                );
            }
            EdgeForKeyByteValueIterable.this.thunderGraph.getThunder().removeEdge(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected ThunderEdge internalNext() {
            long edgeIdArray[] = new long[1];
            String labelArray[] = new String[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];
            if (this.goToFirst) {
                this.goToFirst = false;
                if (EdgeForKeyByteValueIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyByteValue(this.tc.getEdgeCursor(), edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray, EdgeForKeyByteValueIterable.this.key, EdgeForKeyByteValueIterable.this.value)) {
                    return new ThunderEdge(EdgeForKeyByteValueIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (EdgeForKeyByteValueIterable.this.thunderGraph.getThunder().getNextEdgeForKeyByteValue(this.tc.getEdgeCursor(), edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray, EdgeForKeyByteValueIterable.this.key, EdgeForKeyByteValueIterable.this.value)) {
                    return new ThunderEdge(EdgeForKeyByteValueIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }
    }
}
