package org.glmdb.blueprints.iter._double;

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
public class VertexForKeyDoubleValueIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private double value;

    public VertexForKeyDoubleValueIterable(ThunderGraph thunderGraph, String key, double value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexForKeyDoubleValueIterator();
    }

    private final class VertexForKeyDoubleValueIterator extends BaseVertexForKeyValueIterator implements Iterator {

        private VertexForKeyDoubleValueIterator() {
            super(VertexForKeyDoubleValueIterable.this.tc);
        }

        @Override
        protected VertexForKeyDoubleValueIterable getParentIterable() {
            return VertexForKeyDoubleValueIterable.this;
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
                this.tc = VertexForKeyDoubleValueIterable.this.thunderGraph.getWriteTx();
                refreshForFirst();
            }
            this.getParentIterable().thunderGraph.getThunder().removeVertex(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected boolean getFirst(long vertexIdArray[]) {
            return VertexForKeyDoubleValueIterable.this.thunderGraph.getThunder().getFirstVertexForKeyDoubleValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyDoubleValueIterable.this.key, VertexForKeyDoubleValueIterable.this.value);
        }

        @Override
        protected boolean getNext(long vertexIdArray[]) {
            return VertexForKeyDoubleValueIterable.this.thunderGraph.getThunder().getNextVertexForKeyDoubleValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyDoubleValueIterable.this.key, VertexForKeyDoubleValueIterable.this.value);
        }

    }
}
