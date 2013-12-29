package org.glmdb.blueprints.iter._boolean;

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
public class VertexForKeyBooleanValueIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private boolean value;

    public VertexForKeyBooleanValueIterable(ThunderGraph thunderGraph, String key, boolean value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexForKeyBooleanValueIterator();
    }

    private final class VertexForKeyBooleanValueIterator extends BaseVertexForKeyValueIterator implements Iterator {

        private VertexForKeyBooleanValueIterator() {
            super(VertexForKeyBooleanValueIterable.this.tc);
        }

        @Override
        protected VertexForKeyBooleanValueIterable getParentIterable() {
            return VertexForKeyBooleanValueIterable.this;
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
                this.tc = VertexForKeyBooleanValueIterable.this.thunderGraph.getWriteTx();
                refreshForFirst();
            }
            this.getParentIterable().thunderGraph.getThunder().removeVertex(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected boolean getFirst(long vertexIdArray[]) {
            return VertexForKeyBooleanValueIterable.this.thunderGraph.getThunder().getFirstVertexForKeyBooleanValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyBooleanValueIterable.this.key, VertexForKeyBooleanValueIterable.this.value);
        }

        @Override
        protected boolean getNext(long vertexIdArray[]) {
            return VertexForKeyBooleanValueIterable.this.thunderGraph.getThunder().getNextVertexForKeyBooleanValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyBooleanValueIterable.this.key, VertexForKeyBooleanValueIterable.this.value);
        }

    }
}
