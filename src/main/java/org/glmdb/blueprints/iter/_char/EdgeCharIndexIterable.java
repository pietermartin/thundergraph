package org.glmdb.blueprints.iter._char;

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
public class EdgeCharIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderEdge> {

    private String key;
    private char value;

    public EdgeCharIndexIterable(ThunderGraph thunderGraph, String key, char value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderEdge> iterator() {
        return new EdgeCharIndexIterator();
    }

    private final class EdgeCharIndexIterator extends BaseEdgeIndexIterable implements Iterator {

        public EdgeCharIndexIterator() {
            super(EdgeCharIndexIterable.this.tc);
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.EDGE_CHAR_INDEX;
        }

        @Override
        protected EdgeCharIndexIterable getParentIterable() {
            return EdgeCharIndexIterable.this;
        }

        @Override
        protected boolean getCurrentEdgeFromEdgeIndexDb(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeCharIndexIterable.this.thunderGraph.getThunder().getCurrentEdgeFromEdgeCharIndexDb(this.cursor, this.edgeDbCursor, EdgeCharIndexIterable.this.key, EdgeCharIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected boolean getFirstEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeCharIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromCharIndex(this.cursor, this.edgeDbCursor, EdgeCharIndexIterable.this.key, EdgeCharIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);

        }

        @Override
        protected boolean getNextEdgeForKeyValueFromTypeIndex(long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
            return EdgeCharIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromCharIndex(this.cursor, this.edgeDbCursor, EdgeCharIndexIterable.this.key, EdgeCharIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
        }

        @Override
        protected Cursor openAndPositionCursorOnKeyValueInEdgeTypeIndexDb() {
            return EdgeCharIndexIterable.this.thunderGraph.getThunder().openAndPositionCursorOnKeyValueInEdgeCharIndexDb(
                    this.tc.getTxn(),
                    this.internalNext.getInternalId(),
                    EdgeCharIndexIterable.this.key,
                    EdgeCharIndexIterable.this.value
            );
        }

    }

}
