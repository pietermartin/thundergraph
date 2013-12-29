package org.glmdb.blueprints.iter._int;

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
public class EdgeForKeyIntValueIterable<T extends Edge> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private String key;
    private int value;

    public EdgeForKeyIntValueIterable(ThunderGraph thunderGraph, String key, int value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeForKeyIntValueIterator();
    }

    private final class EdgeForKeyIntValueIterator extends BaseThunderIterator<ThunderEdge> implements Iterator  {

        private boolean goToFirst = true;

        private EdgeForKeyIntValueIterator() {
            super(EdgeForKeyIntValueIterable.this.tc);
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.EDGE_DB;
        }

        @Override
        protected EdgeForKeyIntValueIterable getParentIterable() {
            return EdgeForKeyIntValueIterable.this;
        }

        @Override
        public void remove() {
            if (this.cursorIsReadOnly) {
                //Upgrade transaction to a writable one.
                //Replace the current cursor with a new one from the writable transaction
                this.tc = EdgeForKeyIntValueIterable.this.thunderGraph.getWriteTx();
                this.cursorIsReadOnly = false;
                this.cursor = EdgeForKeyIntValueIterable.this.thunderGraph.getThunder().openAndPositionCursorOnEdgePropertyInEdgeDb(
                        this.tc.getTxn(),
                        this.next.getInternalId(),
                        EdgeForKeyIntValueIterable.this.key
                );
            }
            EdgeForKeyIntValueIterable.this.thunderGraph.getThunder().removeEdge(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected ThunderEdge internalNext() {
            long edgeIdArray[] = new long[1];
            String labelArray[] = new String[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];
            if (this.goToFirst) {
                this.goToFirst = false;
                if (EdgeForKeyIntValueIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyIntValue(this.tc.getEdgeCursor(), edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray, EdgeForKeyIntValueIterable.this.key, EdgeForKeyIntValueIterable.this.value)) {
                    return new ThunderEdge(EdgeForKeyIntValueIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (EdgeForKeyIntValueIterable.this.thunderGraph.getThunder().getNextEdgeForKeyIntValue(this.tc.getEdgeCursor(), edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray, EdgeForKeyIntValueIterable.this.key, EdgeForKeyIntValueIterable.this.value)) {
                    return new ThunderEdge(EdgeForKeyIntValueIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }
}
