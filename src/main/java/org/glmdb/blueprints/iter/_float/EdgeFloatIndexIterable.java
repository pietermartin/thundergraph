package org.glmdb.blueprints.iter._float;

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
public class EdgeFloatIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private String key;
    private float value;

    public EdgeFloatIndexIterable(ThunderGraph thunderGraph, String key, float value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeFloatIndexIterator();
    }

    private final class EdgeFloatIndexIterator extends BaseEdgeIndexIterable implements Iterator {

        public EdgeFloatIndexIterator() {
            super(EdgeFloatIndexIterable.this.tc);
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.EDGE_FLOAT_INDEX;
        }

        @Override
        protected EdgeFloatIndexIterable getParentIterable() {
            return EdgeFloatIndexIterable.this;
        }

        @Override
        protected boolean getCurrentEdgeFromEdgeIndexDb(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeFloatIndexIterable.this.thunderGraph.getThunder().getCurrentEdgeFromEdgeFloatIndexDb(this.cursor, this.edgeDbCursor, EdgeFloatIndexIterable.this.key, EdgeFloatIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected boolean getFirstEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeFloatIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromFloatIndex(this.cursor, this.edgeDbCursor, EdgeFloatIndexIterable.this.key, EdgeFloatIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);

        }

        @Override
        protected boolean getNextEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeFloatIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromFloatIndex(this.cursor, this.edgeDbCursor, EdgeFloatIndexIterable.this.key, EdgeFloatIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected Cursor openAndPositionCursorOnKeyValueInEdgeTypeIndexDb() {
            return EdgeFloatIndexIterable.this.thunderGraph.getThunder().openAndPositionCursorOnKeyValueInEdgeFloatIndexDb(
                    this.tc.getTxn(),
                    this.internalNext.getInternalId(),
                    EdgeFloatIndexIterable.this.key,
                    EdgeFloatIndexIterable.this.value
            );
        }

    }

}
