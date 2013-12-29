package org.glmdb.blueprints.iter._boolean;

import com.tinkerpop.blueprints.Vertex;
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

    private final class EdgeBooleanIndexIterator extends BaseThunderIterator<ThunderEdge> implements Iterator {

        private boolean goToFirst = true;
        private Cursor edgeDbCursor;

        public EdgeBooleanIndexIterator() {
            super(EdgeBooleanIndexIterable.this.tc);
            this.edgeDbCursor = EdgeBooleanIndexIterable.this.thunderGraph.getThunder().openCursor(this.tc.getTxn(), DbEnum.EDGE_DB);
            this.tc.addOpenCursor(this.edgeDbCursor);
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
        public void remove() {
            throw new RuntimeException("Not yet implemented!");
        }

        @Override
        protected ThunderEdge internalNext() {
            long edgeIdArray[] = new long[1];
            String labelArray[] = new String[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];

            if (this.goToFirst) {
                this.goToFirst = false;
                if (EdgeBooleanIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromBooleanIndex(this.cursor, this.edgeDbCursor, EdgeBooleanIndexIterable.this.key, EdgeBooleanIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeBooleanIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (EdgeBooleanIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromBooleanIndex(this.cursor, this.edgeDbCursor, EdgeBooleanIndexIterable.this.key, EdgeBooleanIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeBooleanIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
