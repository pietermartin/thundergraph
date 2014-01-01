package org.glmdb.blueprints.iter._int;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderEdge;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.iter.BaseEdgeIndexIterable;
import org.glmdb.blueprints.iter.BaseThunderIterable;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class EdgeIntIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private String key;
    private int value;

    public EdgeIntIndexIterable(ThunderGraph thunderGraph, String key, int value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeIntIndexIterator();
    }

    private final class EdgeIntIndexIterator extends BaseEdgeIndexIterable implements Iterator {

        public EdgeIntIndexIterator() {
            super(EdgeIntIndexIterable.this.tc);
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.EDGE_INT_INDEX;
        }

        @Override
        protected EdgeIntIndexIterable getParentIterable() {
            return EdgeIntIndexIterable.this;
        }

        @Override
        protected boolean getCurrentEdgeFromEdgeIndexDb(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeIntIndexIterable.this.thunderGraph.getThunder().getCurrentEdgeFromEdgeIntIndexDb(this.cursor, this.edgeDbCursor, EdgeIntIndexIterable.this.key, EdgeIntIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected boolean getFirstEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeIntIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromIntIndex(this.cursor, this.edgeDbCursor, EdgeIntIndexIterable.this.key, EdgeIntIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);

        }

        @Override
        protected boolean getNextEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeIntIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromIntIndex(this.cursor, this.edgeDbCursor, EdgeIntIndexIterable.this.key, EdgeIntIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected Cursor openAndPositionCursorOnKeyValueInEdgeTypeIndexDb() {
            return EdgeIntIndexIterable.this.thunderGraph.getThunder().openAndPositionCursorOnKeyValueInEdgeIntIndexDb(
                    this.tc.getTxn(),
                    this.internalNext.getInternalId(),
                    EdgeIntIndexIterable.this.key,
                    EdgeIntIndexIterable.this.value
            );
        }

    }

}
