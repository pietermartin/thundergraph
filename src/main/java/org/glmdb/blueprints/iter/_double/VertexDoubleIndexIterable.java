package org.glmdb.blueprints.iter._double;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.ThunderVertex;
import org.glmdb.blueprints.TransactionAndCursor;
import org.glmdb.blueprints.iter.BaseThunderIterable;
import org.glmdb.blueprints.iter.BaseThunderIterator;
import org.glmdb.blueprints.iter.BaseVertexForKeyValueIterator;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class VertexDoubleIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private double value;

    public VertexDoubleIndexIterable(ThunderGraph thunderGraph, String key, double value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexDoubleIndexIterator();
    }

    private final class VertexDoubleIndexIterator extends BaseThunderIterator<ThunderVertex> implements Iterator {

        private boolean goToFirst = true;

        public VertexDoubleIndexIterator() {
            super(VertexDoubleIndexIterable.this.tc);
        }

        @Override
        protected VertexDoubleIndexIterable getParentIterable() {
            return VertexDoubleIndexIterable.this;
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.VERTEX_DOUBLE_INDEX;
        }

        @Override
        public void remove() {
            throw new RuntimeException("Not yet implemented!");
        }

        @Override
        protected ThunderVertex internalNext() {
            long vertexIdArray[] = new long[1];
            if (this.goToFirst) {
                this.goToFirst = false;
                if (VertexDoubleIndexIterable.this.thunderGraph.getThunder().getFirstVertexForKeyValueFromDoubleIndex(this.cursor, vertexIdArray, VertexDoubleIndexIterable.this.key, VertexDoubleIndexIterable.this.value)) {
                    return new ThunderVertex(VertexDoubleIndexIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexDoubleIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromDoubleIndex(this.cursor, vertexIdArray, VertexDoubleIndexIterable.this.key, VertexDoubleIndexIterable.this.value)) {
                    return new ThunderVertex(VertexDoubleIndexIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
