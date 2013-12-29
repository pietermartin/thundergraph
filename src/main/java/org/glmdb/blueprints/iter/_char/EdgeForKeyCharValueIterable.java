package org.glmdb.blueprints.iter._char;

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
public class EdgeForKeyCharValueIterable<T extends Edge> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private String key;
    private char value;

    public EdgeForKeyCharValueIterable(ThunderGraph thunderGraph, String key, char value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeForKeyCharValueIterator();
    }

    private final class EdgeForKeyCharValueIterator extends BaseThunderIterator<ThunderEdge> implements Iterator  {

        private boolean goToFirst = true;

        private EdgeForKeyCharValueIterator() {
            super(EdgeForKeyCharValueIterable.this.tc);
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.EDGE_DB;
        }

        @Override
        protected EdgeForKeyCharValueIterable getParentIterable() {
            return EdgeForKeyCharValueIterable.this;
        }

        @Override
        public void remove() {
            if (this.cursorIsReadOnly) {
                //Upgrade transaction to a writable one.
                //Replace the current cursor with a new one from the writable transaction
                this.tc = EdgeForKeyCharValueIterable.this.thunderGraph.getWriteTx();
                this.cursorIsReadOnly = false;
                this.cursor = EdgeForKeyCharValueIterable.this.thunderGraph.getThunder().openAndPositionCursorOnEdgePropertyInEdgeDb(
                        this.tc.getTxn(),
                        this.next.getInternalId(),
                        EdgeForKeyCharValueIterable.this.key
                );
            }
            EdgeForKeyCharValueIterable.this.thunderGraph.getThunder().removeEdge(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected ThunderEdge internalNext() {
            long edgeIdArray[] = new long[1];
            String labelArray[] = new String[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];
            if (this.goToFirst) {
                this.goToFirst = false;
                if (EdgeForKeyCharValueIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyCharValue(this.tc.getEdgeCursor(), edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray, EdgeForKeyCharValueIterable.this.key, EdgeForKeyCharValueIterable.this.value)) {
                    return new ThunderEdge(EdgeForKeyCharValueIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (EdgeForKeyCharValueIterable.this.thunderGraph.getThunder().getNextEdgeForKeyCharValue(this.tc.getEdgeCursor(), edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray, EdgeForKeyCharValueIterable.this.key, EdgeForKeyCharValueIterable.this.value)) {
                    return new ThunderEdge(EdgeForKeyCharValueIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }
}
