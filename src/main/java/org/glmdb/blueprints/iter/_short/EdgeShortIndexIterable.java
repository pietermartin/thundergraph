package org.glmdb.blueprints.iter._short;

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

    private final class EdgeShortIndexIterator extends BaseThunderIterator<ThunderEdge>  implements Iterator {

        private boolean goToFirst = true;
        private Cursor edgeDbCursor;

        public EdgeShortIndexIterator() {
            super(EdgeShortIndexIterable.this.tc);
            this.edgeDbCursor = EdgeShortIndexIterable.this.thunderGraph.getThunder().openCursor(this.tc.getTxn(), DbEnum.EDGE_DB);
            this.tc.addOpenCursor(this.edgeDbCursor);
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
                if (EdgeShortIndexIterable.this.thunderGraph.getThunder().getFirstEdgeForKeyValueFromShortIndex(this.cursor, this.edgeDbCursor, EdgeShortIndexIterable.this.key, EdgeShortIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeShortIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (EdgeShortIndexIterable.this.thunderGraph.getThunder().getNextEdgeForKeyValueFromShortIndex(this.cursor, this.edgeDbCursor, EdgeShortIndexIterable.this.key, EdgeShortIndexIterable.this.value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray)) {
                    return new ThunderEdge(EdgeShortIndexIterable.this.thunderGraph, edgeIdArray[0], labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
