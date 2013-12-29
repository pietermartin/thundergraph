package org.glmdb.blueprints.iter._boolean;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.ThunderVertex;
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
public class VertexBooleanIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private boolean value;

    public VertexBooleanIndexIterable(ThunderGraph thunderGraph, String key, boolean value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexBooleanIndexIterator();
    }

    private final class VertexBooleanIndexIterator extends BaseThunderIterator<ThunderVertex> implements Iterator {

        private boolean goToFirst = true;

        public VertexBooleanIndexIterator() {
            super(VertexBooleanIndexIterable.this.tc);
        }

        @Override
        protected VertexBooleanIndexIterable getParentIterable() {
            return VertexBooleanIndexIterable.this;
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.VERTEX_BOOLEAN_INDEX;
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
                if (VertexBooleanIndexIterable.this.thunderGraph.getThunder().getFirstVertexForKeyValueFromBooleanIndex(this.cursor, vertexIdArray, VertexBooleanIndexIterable.this.key, VertexBooleanIndexIterable.this.value)) {
                    return new ThunderVertex(VertexBooleanIndexIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexBooleanIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromBooleanIndex(this.cursor, vertexIdArray, VertexBooleanIndexIterable.this.key, VertexBooleanIndexIterable.this.value)) {
                    return new ThunderVertex(VertexBooleanIndexIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
