package org.glmdb.blueprints.iter._byte;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.ThunderVertex;
import org.glmdb.blueprints.TransactionAndCursor;
import org.glmdb.blueprints.iter.BaseThunderIterable;
import org.glmdb.blueprints.iter.BaseVertexForKeyValueIterator;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class VertexForKeyByteValueIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private byte value;

    public VertexForKeyByteValueIterable(ThunderGraph thunderGraph, String key, byte value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexForKeyByteValueIterator();
    }

    private final class VertexForKeyByteValueIterator extends BaseVertexForKeyValueIterator implements Iterator {

        private VertexForKeyByteValueIterator() {
            super(VertexForKeyByteValueIterable.this.tc);
        }

        @Override
        protected VertexForKeyByteValueIterable getParentIterable() {
            return VertexForKeyByteValueIterable.this;
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.VERTEX_DB;
        }

        @Override
        protected void internalRemove() {
            //remove is overridden so this is not called
        }

        @Override
        public void remove() {
            if (this.cursorIsReadOnly) {
                //Upgrade transaction to a writable one.
                //Replace the current cursor with a new one from the writable transaction
                this.tc = VertexForKeyByteValueIterable.this.thunderGraph.getWriteTx();
                refreshForFirst();
            }
            this.getParentIterable().thunderGraph.getThunder().removeVertex(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected boolean getFirst(long vertexIdArray[]) {
            return VertexForKeyByteValueIterable.this.thunderGraph.getThunder().getFirstVertexForKeyByteValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyByteValueIterable.this.key, VertexForKeyByteValueIterable.this.value);
        }

        @Override
        protected boolean getNext(long vertexIdArray[]) {
            return VertexForKeyByteValueIterable.this.thunderGraph.getThunder().getNextVertexForKeyByteValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyByteValueIterable.this.key, VertexForKeyByteValueIterable.this.value);
        }

    }
}
