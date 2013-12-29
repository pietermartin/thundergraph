package org.glmdb.blueprints.iter._string;

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
public class VertexStringIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private String value;

    public VertexStringIndexIterable(ThunderGraph thunderGraph, String key, String value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexStringIndexIterator();
    }

    private final class VertexStringIndexIterator extends BaseThunderIterator<ThunderVertex> implements Iterator {

        private boolean goToFirst = true;

        public VertexStringIndexIterator() {
            super(VertexStringIndexIterable.this.tc);
        }

        @Override
        protected VertexStringIndexIterable getParentIterable() {
            return VertexStringIndexIterable.this;
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.VERTEX_STRING_INDEX;
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
                if (VertexStringIndexIterable.this.thunderGraph.getThunder().getFirstVertexForKeyValueFromStringIndex(this.cursor, elementIdArray, VertexStringIndexIterable.this.key, VertexStringIndexIterable.this.value)) {
                    return new ThunderVertex(VertexStringIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexStringIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromStringIndex(this.cursor, elementIdArray, VertexStringIndexIterable.this.key, VertexStringIndexIterable.this.value)) {
                    return new ThunderVertex(VertexStringIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
