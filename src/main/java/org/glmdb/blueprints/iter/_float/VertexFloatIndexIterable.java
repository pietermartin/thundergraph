package org.glmdb.blueprints.iter._float;

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
public class VertexFloatIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private float value;

    public VertexFloatIndexIterable(ThunderGraph thunderGraph, String key, float value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexFloatIndexIterator();
    }

    private final class VertexFloatIndexIterator extends BaseThunderIterator<ThunderVertex> implements Iterator {

        private boolean goToFirst = true;

        public VertexFloatIndexIterator() {
            super(VertexFloatIndexIterable.this.tc);
        }

        @Override
        protected VertexFloatIndexIterable getParentIterable() {
            return VertexFloatIndexIterable.this;
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.VERTEX_FLOAT_INDEX;
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
                if (VertexFloatIndexIterable.this.thunderGraph.getThunder().getFirstVertexForKeyValueFromFloatIndex(this.cursor, vertexIdArray, VertexFloatIndexIterable.this.key, VertexFloatIndexIterable.this.value)) {
                    return new ThunderVertex(VertexFloatIndexIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexFloatIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromFloatIndex(this.cursor, vertexIdArray, VertexFloatIndexIterable.this.key, VertexFloatIndexIterable.this.value)) {
                    return new ThunderVertex(VertexFloatIndexIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
