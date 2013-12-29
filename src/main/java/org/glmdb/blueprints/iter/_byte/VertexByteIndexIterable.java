package org.glmdb.blueprints.iter._byte;

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
public class VertexByteIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private byte value;

    public VertexByteIndexIterable(ThunderGraph thunderGraph, String key, byte value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexByteIndexIterator();
    }

    private final class VertexByteIndexIterator extends BaseThunderIterator<ThunderVertex> implements Iterator {

        private boolean goToFirst = true;

        public VertexByteIndexIterator() {
            super(VertexByteIndexIterable.this.tc);
        }

        @Override
        protected VertexByteIndexIterable getParentIterable() {
            return VertexByteIndexIterable.this;
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.VERTEX_BYTE_INDEX;
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
                if (VertexByteIndexIterable.this.thunderGraph.getThunder().getFirstVertexForKeyValueFromByteIndex(this.cursor, vertexIdArray, VertexByteIndexIterable.this.key, VertexByteIndexIterable.this.value)) {
                    return new ThunderVertex(VertexByteIndexIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexByteIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromByteIndex(this.cursor, vertexIdArray, VertexByteIndexIterable.this.key, VertexByteIndexIterable.this.value)) {
                    return new ThunderVertex(VertexByteIndexIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
