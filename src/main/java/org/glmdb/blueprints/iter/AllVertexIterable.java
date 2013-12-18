package org.glmdb.blueprints.iter;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.ThunderVertex;
import org.glmdb.blueprints.TransactionAndCursor;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class AllVertexIterable<T extends Vertex> implements Iterable<ThunderVertex> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;

    public AllVertexIterable(ThunderGraph thunderGraph) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new AllVertexIterator();
    }

    private final class AllVertexIterator implements Iterator<ThunderVertex> {

        private ThunderVertex next;
        private boolean goToFirst = true;
        private Cursor cursor;
        private boolean cursorIsReadOnly;
        private long previousId;

        private AllVertexIterator() {
            this.cursorIsReadOnly = AllVertexIterable.this.tc.isReadOnly();
            this.cursor = AllVertexIterable.this.thunderGraph.getThunder().openCursor(AllVertexIterable.this.tc.getTxn(), DbEnum.VERTEX_DB);
            AllVertexIterable.this.tc.addIteratorCursor(this.cursor);
        }

        @Override
        public boolean hasNext() {
            if (this.next == null) {
                this.next = internalNext();
            }
            return this.next != null;
        }

        @Override
        public ThunderVertex next() {
            if (this.next == null) {
                this.next = internalNext();
                if (this.next == null) {
                    throw new NoSuchElementException();
                }
            }
            ThunderVertex result = this.next;
            this.next = null;
            return result;
        }

        @Override
        public void remove() {
            throw new RuntimeException("Not yet implemented!");
        }

        private ThunderVertex internalNext() {
            long vertexIdArray[] = new long[1];
            if (this.goToFirst) {
                this.goToFirst = false;
                if (AllVertexIterable.this.thunderGraph.getThunder().getFirstVertex(this.cursor, vertexIdArray)) {
                    this.previousId = vertexIdArray[0];
                    return new ThunderVertex(AllVertexIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
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
