package org.glmdb.blueprints.iter._string;

import com.tinkerpop.blueprints.Vertex;
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
public class VertexForKeyStringValueIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private String value;

    public VertexForKeyStringValueIterable(ThunderGraph thunderGraph, String key, String value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexForKeyStringValueIterator();
    }

    private final class VertexForKeyStringValueIterator extends BaseVertexForKeyValueIterator implements Iterator {

        private VertexForKeyStringValueIterator() {
            super(VertexForKeyStringValueIterable.this.tc);
        }

        @Override
        protected VertexForKeyStringValueIterable getParentIterable() {
            return VertexForKeyStringValueIterable.this;
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
                this.tc = VertexForKeyStringValueIterable.this.thunderGraph.getWriteTx();
                refreshForFirst();
            }
            this.getParentIterable().thunderGraph.getThunder().removeVertex(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected boolean getFirst(long vertexIdArray[]) {
            return VertexForKeyStringValueIterable.this.thunderGraph.getThunder().getFirstVertexForKeyStringValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyStringValueIterable.this.key, VertexForKeyStringValueIterable.this.value);
        }

        @Override
        protected boolean getNext(long vertexIdArray[]) {
            return VertexForKeyStringValueIterable.this.thunderGraph.getThunder().getNextVertexForKeyStringValue(this.tc.getVertexCursor(), vertexIdArray, VertexForKeyStringValueIterable.this.key, VertexForKeyStringValueIterable.this.value);
        }

    }
}
