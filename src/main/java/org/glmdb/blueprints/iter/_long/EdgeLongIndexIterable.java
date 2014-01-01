package org.glmdb.blueprints.iter._long;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderEdge;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.TransactionAndCursor;
import org.glmdb.blueprints.iter.BaseEdgeIndexIterable;
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
public class EdgeLongIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private String key;
    private long value;

    public EdgeLongIndexIterable(ThunderGraph thunderGraph, String key, long value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeLongIndexIterator();
    }

    private final class EdgeLongIndexIterator extends BaseEdgeIndexIterable implements Iterator {

        public EdgeLongIndexIterator() {
            super(EdgeLongIndexIterable.this.tc);
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.EDGE_LONG_INDEX;
        }

        @Override
        protected EdgeLongIndexIterable getParentIterable() {
            return EdgeLongIndexIterable.this;
        }

        @Override
        protected boolean getCurrentEdgeFromEdgeIndexDb(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeLongIndexIterable.this.thunderGraph.getThunder().getCurrentEdgeFromEdgeLongIndexDb(this.cursor, this.edgeDbCursor, EdgeLongIndexIterable.this.key, EdgeLongIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected boolean getFirstEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeLongIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromLongIndex(this.cursor, this.edgeDbCursor, EdgeLongIndexIterable.this.key, EdgeLongIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);

        }

        @Override
        protected boolean getNextEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeLongIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromLongIndex(this.cursor, this.edgeDbCursor, EdgeLongIndexIterable.this.key, EdgeLongIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected Cursor openAndPositionCursorOnKeyValueInEdgeTypeIndexDb() {
            return EdgeLongIndexIterable.this.thunderGraph.getThunder().openAndPositionCursorOnKeyValueInEdgeLongIndexDb(
                    this.tc.getTxn(),
                    this.internalNext.getInternalId(),
                    EdgeLongIndexIterable.this.key,
                    EdgeLongIndexIterable.this.value
            );
        }

    }

}
