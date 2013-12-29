package org.glmdb.blueprints.iter._string;

import com.tinkerpop.blueprints.Edge;
import org.glmdb.blueprints.ThunderEdge;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.TransactionAndCursor;
import org.glmdb.blueprints.iter.BaseThunderIterable;
import org.glmdb.blueprints.iter.BaseThunderIterator;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class EdgeForKeyStringValueIterable<T extends Edge> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private String key;
    private String value;

    public EdgeForKeyStringValueIterable(ThunderGraph thunderGraph, String key, String value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeForKeyStringValueIterator();
    }

    private final class EdgeForKeyStringValueIterator extends BaseThunderIterator<ThunderEdge>  implements Iterator  {

        private boolean goToFirst = true;

        private EdgeForKeyStringValueIterator() {
            super(EdgeForKeyStringValueIterable.this.tc);
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.EDGE_DB;
        }

        @Override
        protected EdgeForKeyStringValueIterable getParentIterable() {
            return EdgeForKeyStringValueIterable.this;
        }

        @Override
        public void remove() {
            if (this.cursorIsReadOnly) {
                //Upgrade transaction to a writable one.
                //Replace the current cursor with a new one from the writable transaction
                this.tc = EdgeForKeyStringValueIterable.this.thunderGraph.getWriteTx();
                this.cursorIsReadOnly = false;
                this.cursor = EdgeForKeyStringValueIterable.this.thunderGraph.getThunder().openAndPositionCursorOnEdgePropertyInEdgeDb(
                        this.tc.getTxn(),
                        this.next.getInternalId(),
                        EdgeForKeyStringValueIterable.this.key
                );
            }
            EdgeForKeyStringValueIterable.this.thunderGraph.getThunder().removeEdge(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected ThunderEdge internalNext() {
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
