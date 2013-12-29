package org.glmdb.blueprints.iter._float;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.ThunderVertex;
import org.glmdb.blueprints.TransactionAndCursor;
import org.glmdb.blueprints.iter.BaseThunderIterable;
import org.glmdb.blueprints.iter.BaseThunderIterator;
import org.glmdb.blueprints.iter.BaseVertexForKeyValueIterator;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class VertexForKeyFloatValueIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private float value;

    public VertexForKeyFloatValueIterable(ThunderGraph thunderGraph, String key, float value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexForKeyFloatValueIterator();
    }

    private final class VertexForKeyFloatValueIterator extends BaseVertexForKeyValueIterator implements Iterator {

        private VertexForKeyFloatValueIterator() {
            super(VertexForKeyFloatValueIterable.this.tc);
        }

        @Override
        protected VertexForKeyFloatValueIterable getParentIterable() {
            return VertexForKeyFloatValueIterable.this;
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
                this.tc = VertexForKeyFloatValueIterable.this.thunderGraph.getWriteTx();
                refreshForFirst();
            }
            this.getParentIterable().thunderGraph.getThunder().removeVertex(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected boolean getFirst(long vertexIdArray[]) {
            return VertexForKeyFloatValueIterable.this.thunderGraph.getThunder().getFirstVertexForKeyFloatValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyFloatValueIterable.this.key, VertexForKeyFloatValueIterable.this.value);
        }

        @Override
        protected boolean getNext(long vertexIdArray[]) {
            return VertexForKeyFloatValueIterable.this.thunderGraph.getThunder().getNextVertexForKeyFloatValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyFloatValueIterable.this.key, VertexForKeyFloatValueIterable.this.value);
        }

    }
}
