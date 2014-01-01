package org.glmdb.blueprints.iter._boolean;

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
public class EdgeBooleanIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private String key;
    private boolean value;

    public EdgeBooleanIndexIterable(ThunderGraph thunderGraph, String key, boolean value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeBooleanIndexIterator();
    }

    private final class EdgeBooleanIndexIterator extends BaseEdgeIndexIterable implements Iterator {

        public EdgeBooleanIndexIterator() {
            super(EdgeBooleanIndexIterable.this.tc);
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.EDGE_BOOLEAN_INDEX;
        }

        @Override
        protected EdgeBooleanIndexIterable getParentIterable() {
            return EdgeBooleanIndexIterable.this;
        }

        @Override
        protected boolean getCurrentEdgeFromEdgeIndexDb(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeBooleanIndexIterable.this.thunderGraph.getThunder().getCurrentEdgeFromEdgeBooleanIndexDb(this.cursor, this.edgeDbCursor, EdgeBooleanIndexIterable.this.key, EdgeBooleanIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected boolean getFirstEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeBooleanIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromBooleanIndex(this.cursor, this.edgeDbCursor, EdgeBooleanIndexIterable.this.key, EdgeBooleanIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);

        }

        @Override
        protected boolean getNextEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeBooleanIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromBooleanIndex(this.cursor, this.edgeDbCursor, EdgeBooleanIndexIterable.this.key, EdgeBooleanIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected Cursor openAndPositionCursorOnKeyValueInEdgeTypeIndexDb() {
            return EdgeBooleanIndexIterable.this.thunderGraph.getThunder().openAndPositionCursorOnKeyValueInEdgeBooleanIndexDb(
                    this.tc.getTxn(),
                    this.internalNext.getInternalId(),
                    EdgeBooleanIndexIterable.this.key,
                    EdgeBooleanIndexIterable.this.value
            );
        }

    }

}
