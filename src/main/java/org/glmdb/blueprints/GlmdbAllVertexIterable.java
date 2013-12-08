package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.jni.Cursor;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class GlmdbAllVertexIterable<T extends Vertex> implements Iterable<ThunderVertex> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;

    public GlmdbAllVertexIterable(ThunderGraph thunderGraph) {
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
            this.cursorIsReadOnly = GlmdbAllVertexIterable.this.tc.isReadOnly();
            this.cursor = GlmdbAllVertexIterable.this.thunderGraph.getGlmdb().openCursorToVertexDb(GlmdbAllVertexIterable.this.tc.getTxn());
            GlmdbAllVertexIterable.this.tc.addIteratorCursor(this.cursor);
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
                if (GlmdbAllVertexIterable.this.thunderGraph.getGlmdb().getFirstVertex(this.cursor, vertexIdArray)) {
                    this.previousId = vertexIdArray[0];
                    return new ThunderVertex(GlmdbAllVertexIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (GlmdbAllVertexIterable.this.thunderGraph.getGlmdb().getNextVertex(this.cursor, this.previousId, vertexIdArray)) {
                    this.previousId = vertexIdArray[0];
                    return new ThunderVertex(GlmdbAllVertexIterable.this.thunderGraph, vertexIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }
}
