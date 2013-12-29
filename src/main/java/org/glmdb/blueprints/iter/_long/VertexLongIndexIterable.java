package org.glmdb.blueprints.iter._long;

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
public class VertexLongIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private long value;

    public VertexLongIndexIterable(ThunderGraph thunderGraph, String key, long value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexLongIndexIterator();
    }

    private final class VertexLongIndexIterator extends BaseThunderIterator<ThunderVertex> implements Iterator {

        private boolean goToFirst = true;

        public VertexLongIndexIterator() {
            super(VertexLongIndexIterable.this.tc);
        }

        @Override
        protected VertexLongIndexIterable getParentIterable() {
            return VertexLongIndexIterable.this;
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.VERTEX_LONG_INDEX;
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
                if (VertexLongIndexIterable.this.thunderGraph.getThunder().getFirstVertexForKeyValueFromLongIndex(this.cursor, elementIdArray, VertexLongIndexIterable.this.key, VertexLongIndexIterable.this.value)) {
                    return new ThunderVertex(VertexLongIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexLongIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromLongIndex(this.cursor, elementIdArray, VertexLongIndexIterable.this.key, VertexLongIndexIterable.this.value)) {
                    return new ThunderVertex(VertexLongIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
