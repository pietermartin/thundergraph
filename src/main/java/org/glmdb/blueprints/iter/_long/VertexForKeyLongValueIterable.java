package org.glmdb.blueprints.iter._long;

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
public class VertexForKeyLongValueIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private long value;

    public VertexForKeyLongValueIterable(ThunderGraph thunderGraph, String key, long value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexForKeyLongValueIterator();
    }

    private final class VertexForKeyLongValueIterator extends BaseVertexForKeyValueIterator implements Iterator {

        private VertexForKeyLongValueIterator() {
            super(VertexForKeyLongValueIterable.this.tc);
        }

        @Override
        protected VertexForKeyLongValueIterable getParentIterable() {
            return VertexForKeyLongValueIterable.this;
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
                this.tc = VertexForKeyLongValueIterable.this.thunderGraph.getWriteTx();
                refreshForFirst();
            }
            this.getParentIterable().thunderGraph.getThunder().removeVertex(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected boolean getFirst(long vertexIdArray[]) {
            return VertexForKeyLongValueIterable.this.thunderGraph.getThunder().getFirstVertexForKeyLongValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyLongValueIterable.this.key, VertexForKeyLongValueIterable.this.value);
        }

        @Override
        protected boolean getNext(long vertexIdArray[]) {
            return VertexForKeyLongValueIterable.this.thunderGraph.getThunder().getNextVertexForKeyLongValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyLongValueIterable.this.key, VertexForKeyLongValueIterable.this.value);
        }

    }
}
