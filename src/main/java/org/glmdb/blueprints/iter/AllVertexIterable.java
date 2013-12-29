package org.glmdb.blueprints.iter;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.ThunderVertex;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class AllVertexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    public AllVertexIterable(ThunderGraph thunderGraph) {
        super(thunderGraph);
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new AllVertexIterator();
    }

    private final class AllVertexIterator extends BaseThunderIterator<ThunderVertex> implements Iterator {

        private boolean goToFirst = true;
        private long previousId;

        private AllVertexIterator() {
            super(AllVertexIterable.this.tc);
        }

        @Override
        protected AllVertexIterable getParentIterable() {
            return AllVertexIterable.this;
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.VERTEX_DB;
        }

        @Override
        public void remove() {
            if (this.cursorIsReadOnly) {
                //Upgrade transaction to a writable one.
                //Replace the current cursor with a new one from the writable transaction
                AllVertexIterable.this.tc = AllVertexIterable.this.thunderGraph.getWriteTx();
                refreshForFirst();
            }
            this.getParentIterable().thunderGraph.getThunder().removeVertex(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected ThunderVertex internalNext() {
            long vertexIdArray[] = new long[1];
            if (this.goToFirst) {
                this.goToFirst = false;
                if (this.cursor == null || !this.cursor.isAllocated()) {
                    refreshForFirst();
                }
                if (AllVertexIterable.this.thunderGraph.getThunder().getFirstVertex(this.cursor, vertexIdArray)) {
                    this.previousId = vertexIdArray[0];
                    return new ThunderVertex(AllVertexIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                //Check if cursor needs reopening. This happens if a read only transaction is upgraded to a write transaction
                //after the iterator was instantiated.
                if (this.cursor == null || !this.cursor.isAllocated()) {
                    //This can be a refreshForFirst as getNextVertex does a range query
                    refreshForFirst();
                }
                if (AllVertexIterable.this.thunderGraph.getThunder().getNextVertex(this.cursor, this.previousId, vertexIdArray)) {
                    this.previousId = vertexIdArray[0];
                    return new ThunderVertex(AllVertexIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }
}
