package org.glmdb.blueprints.iter._short;

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
public class VertexForKeyShortValueIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private short value;

    public VertexForKeyShortValueIterable(ThunderGraph thunderGraph, String key, short value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexForKeyShortValueIterator();
    }

    private final class VertexForKeyShortValueIterator extends BaseVertexForKeyValueIterator implements Iterator {

        private VertexForKeyShortValueIterator() {
            super(VertexForKeyShortValueIterable.this.tc);
        }

        @Override
        protected VertexForKeyShortValueIterable getParentIterable() {
            return VertexForKeyShortValueIterable.this;
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
                this.tc = VertexForKeyShortValueIterable.this.thunderGraph.getWriteTx();
                refreshForFirst();
            }
            this.getParentIterable().thunderGraph.getThunder().removeVertex(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected boolean getFirst(long vertexIdArray[]) {
            return VertexForKeyShortValueIterable.this.thunderGraph.getThunder().getFirstVertexForKeyShortValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyShortValueIterable.this.key, VertexForKeyShortValueIterable.this.value);
        }

        @Override
        protected boolean getNext(long vertexIdArray[]) {
            return VertexForKeyShortValueIterable.this.thunderGraph.getThunder().getNextVertexForKeyShortValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyShortValueIterable.this.key, VertexForKeyShortValueIterable.this.value);
        }

    }
}
