package org.glmdb.blueprints.iter._string;

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
public class EdgeStringIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private String key;
    private String value;

    public EdgeStringIndexIterable(ThunderGraph thunderGraph, String key, String value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeStringIndexIterator();
    }

    private final class EdgeStringIndexIterator extends BaseEdgeIndexIterable implements Iterator {

        public EdgeStringIndexIterator() {
            super(EdgeStringIndexIterable.this.tc);
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.EDGE_STRING_INDEX;
        }

        @Override
        protected EdgeStringIndexIterable getParentIterable() {
            return EdgeStringIndexIterable.this;
        }

        @Override
        protected boolean getCurrentEdgeFromEdgeIndexDb(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeStringIndexIterable.this.thunderGraph.getThunder().getCurrentEdgeFromEdgeStringIndexDb(this.cursor, this.edgeDbCursor, EdgeStringIndexIterable.this.key, EdgeStringIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected boolean getFirstEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeStringIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromStringIndex(this.cursor, this.edgeDbCursor, EdgeStringIndexIterable.this.key, EdgeStringIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);

        }

        @Override
        protected boolean getNextEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeStringIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromStringIndex(this.cursor, this.edgeDbCursor, EdgeStringIndexIterable.this.key, EdgeStringIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected Cursor openAndPositionCursorOnKeyValueInEdgeTypeIndexDb() {
            return EdgeStringIndexIterable.this.thunderGraph.getThunder().openAndPositionCursorOnKeyValueInEdgeStringIndexDb(
                    this.tc.getTxn(),
                    this.internalNext.getInternalId(),
                    EdgeStringIndexIterable.this.key,
                    EdgeStringIndexIterable.this.value
            );
        }

    }


}
