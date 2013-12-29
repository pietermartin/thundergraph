package org.glmdb.blueprints.iter._char;

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
public class VertexCharIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private char value;

    public VertexCharIndexIterable(ThunderGraph thunderGraph, String key, char value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexCharIndexIterator();
    }

    private final class VertexCharIndexIterator extends BaseThunderIterator<ThunderVertex> implements Iterator {

        private boolean goToFirst = true;

        public VertexCharIndexIterator() {
            super(VertexCharIndexIterable.this.tc);
        }

        @Override
        protected VertexCharIndexIterable getParentIterable() {
            return VertexCharIndexIterable.this;
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.VERTEX_CHAR_INDEX;
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
                if (VertexCharIndexIterable.this.thunderGraph.getThunder().getFirstVertexForKeyValueFromCharIndex(this.cursor, vertexIdArray, VertexCharIndexIterable.this.key, VertexCharIndexIterable.this.value)) {
                    return new ThunderVertex(VertexCharIndexIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexCharIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromCharIndex(this.cursor, vertexIdArray, VertexCharIndexIterable.this.key, VertexCharIndexIterable.this.value)) {
                    return new ThunderVertex(VertexCharIndexIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
