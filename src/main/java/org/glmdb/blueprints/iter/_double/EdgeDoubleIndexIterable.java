package org.glmdb.blueprints.iter._double;

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
public class EdgeDoubleIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private String key;
    private double value;

    public EdgeDoubleIndexIterable(ThunderGraph thunderGraph, String key, double value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeDoubleIndexIterator();
    }

    private final class EdgeDoubleIndexIterator extends BaseEdgeIndexIterable implements Iterator {

        public EdgeDoubleIndexIterator() {
            super(EdgeDoubleIndexIterable.this.tc);
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.EDGE_DOUBLE_INDEX;
        }

        @Override
        protected EdgeDoubleIndexIterable getParentIterable() {
            return EdgeDoubleIndexIterable.this;
        }

        @Override
        protected boolean getCurrentEdgeFromEdgeIndexDb(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeDoubleIndexIterable.this.thunderGraph.getThunder().getCurrentEdgeFromEdgeDoubleIndexDb(this.cursor, this.edgeDbCursor, EdgeDoubleIndexIterable.this.key, EdgeDoubleIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected boolean getFirstEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeDoubleIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromDoubleIndex(this.cursor, this.edgeDbCursor, EdgeDoubleIndexIterable.this.key, EdgeDoubleIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);

        }

        @Override
        protected boolean getNextEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeDoubleIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromDoubleIndex(this.cursor, this.edgeDbCursor, EdgeDoubleIndexIterable.this.key, EdgeDoubleIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected Cursor openAndPositionCursorOnKeyValueInEdgeTypeIndexDb() {
            return EdgeDoubleIndexIterable.this.thunderGraph.getThunder().openAndPositionCursorOnKeyValueInEdgeDoubleIndexDb(
                    this.tc.getTxn(),
                    this.internalNext.getInternalId(),
                    EdgeDoubleIndexIterable.this.key,
                    EdgeDoubleIndexIterable.this.value
            );
        }

    }

}
