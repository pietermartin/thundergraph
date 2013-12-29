package org.glmdb.blueprints.iter._long;

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
public class EdgeForKeyLongValueIterable<T extends Edge> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private String key;
    private long value;

    public EdgeForKeyLongValueIterable(ThunderGraph thunderGraph, String key, long value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeForKeyLongValueIterator();
    }

    private final class EdgeForKeyLongValueIterator extends BaseThunderIterator<ThunderEdge> implements Iterator {

        private boolean goToFirst = true;

        private EdgeForKeyLongValueIterator() {
            super(EdgeForKeyLongValueIterable.this.tc);
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.EDGE_DB;
        }

        @Override
        protected EdgeForKeyLongValueIterable getParentIterable() {
            return EdgeForKeyLongValueIterable.this;
        }

        @Override
        public void remove() {
            if (this.cursorIsReadOnly) {
                //Upgrade transaction to a writable one.
                //Replace the current cursor with a new one from the writable transaction
                this.tc = EdgeForKeyLongValueIterable.this.thunderGraph.getWriteTx();
                this.cursorIsReadOnly = false;
                this.cursor = EdgeForKeyLongValueIterable.this.thunderGraph.getThunder().openAndPositionCursorOnEdgePropertyInEdgeDb(
                        this.tc.getTxn(),
                        this.next.getInternalId(),
                        EdgeForKeyLongValueIterable.this.key
                );
            }
            EdgeForKeyLongValueIterable.this.thunderGraph.getThunder().removeEdge(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected ThunderEdge internalNext() {
            long edgeIdArray[] = new long[1];
            String labelArray[] = new String[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];
            if (this.goToFirst) {
                this.goToFirst = false;
                if (EdgeForKeyLongValueIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyLongValue(this.tc.getEdgeCursor(), edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray, EdgeForKeyLongValueIterable.this.key, EdgeForKeyLongValueIterable.this.value)) {
                    return new ThunderEdge(EdgeForKeyLongValueIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (EdgeForKeyLongValueIterable.this.thunderGraph.getThunder().getNextEdgeForKeyLongValue(this.tc.getEdgeCursor(), edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray, EdgeForKeyLongValueIterable.this.key, EdgeForKeyLongValueIterable.this.value)) {
                    return new ThunderEdge(EdgeForKeyLongValueIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }
}
