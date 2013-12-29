package org.glmdb.blueprints.iter._int;

import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.ThunderVertex;
import org.glmdb.blueprints.iter.BaseThunderIterable;
import org.glmdb.blueprints.iter.BaseVertexForKeyValueIterator;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class VertexForKeyIntValueIterable<Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private int value;

    public VertexForKeyIntValueIterable(ThunderGraph thunderGraph, String key, int value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexForKeyIntValueIterator();
    }

    private final class VertexForKeyIntValueIterator extends BaseVertexForKeyValueIterator implements Iterator {

        private VertexForKeyIntValueIterator() {
            super(VertexForKeyIntValueIterable.this.tc);
        }

        @Override
        protected VertexForKeyIntValueIterable getParentIterable() {
            return VertexForKeyIntValueIterable.this;
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
                this.tc = VertexForKeyIntValueIterable.this.thunderGraph.getWriteTx();
                refreshForFirst();
            }
            this.getParentIterable().thunderGraph.getThunder().removeVertex(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected boolean getFirst(long vertexIdArray[]) {
            return VertexForKeyIntValueIterable.this.thunderGraph.getThunder().getFirstVertexForKeyIntValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyIntValueIterable.this.key, VertexForKeyIntValueIterable.this.value);
        }

        @Override
        protected boolean getNext(long vertexIdArray[]) {
            return VertexForKeyIntValueIterable.this.thunderGraph.getThunder().getNextVertexForKeyIntValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyIntValueIterable.this.key, VertexForKeyIntValueIterable.this.value);
        }

    }
}
