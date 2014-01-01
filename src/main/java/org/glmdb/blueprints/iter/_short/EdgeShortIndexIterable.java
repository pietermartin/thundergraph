package org.glmdb.blueprints.iter._short;

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
public class EdgeShortIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private String key;
    private short value;

    public EdgeShortIndexIterable(ThunderGraph thunderGraph, String key, short value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeShortIndexIterator();
    }

    private final class EdgeShortIndexIterator extends BaseEdgeIndexIterable implements Iterator {


        public EdgeShortIndexIterator() {
            super(EdgeShortIndexIterable.this.tc);
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.EDGE_SHORT_INDEX;
        }

        @Override
        protected EdgeShortIndexIterable getParentIterable() {
            return EdgeShortIndexIterable.this;
        }

        @Override
        protected boolean getCurrentEdgeFromEdgeIndexDb(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeShortIndexIterable.this.thunderGraph.getThunder().getCurrentEdgeFromEdgeShortIndexDb(this.cursor, this.edgeDbCursor, EdgeShortIndexIterable.this.key, EdgeShortIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected boolean getFirstEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeShortIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromShortIndex(this.cursor, this.edgeDbCursor, EdgeShortIndexIterable.this.key, EdgeShortIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);

        }

        @Override
        protected boolean getNextEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeShortIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromShortIndex(this.cursor, this.edgeDbCursor, EdgeShortIndexIterable.this.key, EdgeShortIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected Cursor openAndPositionCursorOnKeyValueInEdgeTypeIndexDb() {
            return EdgeShortIndexIterable.this.thunderGraph.getThunder().openAndPositionCursorOnKeyValueInEdgeShortIndexDb(
                    this.tc.getTxn(),
                    this.internalNext.getInternalId(),
                    EdgeShortIndexIterable.this.key,
                    EdgeShortIndexIterable.this.value
            );
        }

    }

}
