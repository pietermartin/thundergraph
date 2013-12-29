package org.glmdb.blueprints.iter._char;

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
public class VertexForKeyCharValueIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private char value;

    public VertexForKeyCharValueIterable(ThunderGraph thunderGraph, String key, char value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexForKeyCharValueIterator();
    }

    private final class VertexForKeyCharValueIterator extends BaseVertexForKeyValueIterator implements Iterator {

        private VertexForKeyCharValueIterator() {
            super(VertexForKeyCharValueIterable.this.tc);
        }

        @Override
        protected VertexForKeyCharValueIterable getParentIterable() {
            return VertexForKeyCharValueIterable.this;
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
                this.tc = VertexForKeyCharValueIterable.this.thunderGraph.getWriteTx();
                refreshForFirst();
            }
            this.getParentIterable().thunderGraph.getThunder().removeVertex(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected boolean getFirst(long vertexIdArray[]) {
            return VertexForKeyCharValueIterable.this.thunderGraph.getThunder().getFirstVertexForKeyCharValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyCharValueIterable.this.key, VertexForKeyCharValueIterable.this.value);
        }

        @Override
        protected boolean getNext(long vertexIdArray[]) {
            return VertexForKeyCharValueIterable.this.thunderGraph.getThunder().getNextVertexForKeyCharValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyCharValueIterable.this.key, VertexForKeyCharValueIterable.this.value);
        }

    }
}
