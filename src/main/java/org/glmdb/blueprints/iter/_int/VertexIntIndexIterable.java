package org.glmdb.blueprints.iter._int;

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
public class VertexIntIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private int value;

    public VertexIntIndexIterable(ThunderGraph thunderGraph, String key, int value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexIntIndexIterator();
    }

    private final class VertexIntIndexIterator extends BaseThunderIterator<ThunderVertex> implements Iterator {

        private boolean goToFirst = true;

        public VertexIntIndexIterator() {
            super(VertexIntIndexIterable.this.tc);
        }

        @Override
        protected VertexIntIndexIterable getParentIterable() {
            return VertexIntIndexIterable.this;
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.VERTEX_INT_INDEX;
        }

        @Override
        public void remove() {
            throw new RuntimeException("Not yet implemented!");
        }

        @Override
        protected ThunderVertex internalNext() {
            long elementIdArray[] = new long[1];
            if (this.goToFirst) {
                this.goToFirst = false;
                if (VertexIntIndexIterable.this.thunderGraph.getThunder().getFirstVertexForKeyValueFromIntIndex(this.cursor, elementIdArray, VertexIntIndexIterable.this.key, VertexIntIndexIterable.this.value)) {
                    return new ThunderVertex(VertexIntIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexIntIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromIntIndex(this.cursor, elementIdArray, VertexIntIndexIterable.this.key, VertexIntIndexIterable.this.value)) {
                    return new ThunderVertex(VertexIntIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
