package org.glmdb.blueprints.iter._byte;

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
public class EdgeByteIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private String key;
    private byte value;

    public EdgeByteIndexIterable(ThunderGraph thunderGraph, String key, byte value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeByteIndexIterator();
    }

    private final class EdgeByteIndexIterator extends BaseEdgeIndexIterable implements Iterator {

        public EdgeByteIndexIterator() {
            super(EdgeByteIndexIterable.this.tc);
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.EDGE_BYTE_INDEX;
        }

        @Override
        protected EdgeByteIndexIterable getParentIterable() {
            return EdgeByteIndexIterable.this;
        }

        @Override
        protected boolean getCurrentEdgeFromEdgeIndexDb(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeByteIndexIterable.this.thunderGraph.getThunder().getCurrentEdgeFromEdgeByteIndexDb(this.cursor, this.edgeDbCursor, EdgeByteIndexIterable.this.key, EdgeByteIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected boolean getFirstEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeByteIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromByteIndex(this.cursor, this.edgeDbCursor, EdgeByteIndexIterable.this.key, EdgeByteIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);

        }

        @Override
        protected boolean getNextEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeByteIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromByteIndex(this.cursor, this.edgeDbCursor, EdgeByteIndexIterable.this.key, EdgeByteIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected Cursor openAndPositionCursorOnKeyValueInEdgeTypeIndexDb() {
            return EdgeByteIndexIterable.this.thunderGraph.getThunder().openAndPositionCursorOnKeyValueInEdgeByteIndexDb(
                    this.tc.getTxn(),
                    this.internalNext.getInternalId(),
                    EdgeByteIndexIterable.this.key,
                    EdgeByteIndexIterable.this.value
            );
        }

    }

}
