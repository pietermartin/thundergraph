package org.glmdb.blueprints.iter._int;

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
public class VertexIntIndexIterable<T extends Vertex> implements Iterable<ThunderVertex> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private int value;

    public VertexIntIndexIterable(ThunderGraph thunderGraph, String key, int value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexIntIndexIterator();
    }

    private final class VertexIntIndexIterator implements Iterator<ThunderVertex> {

        private ThunderVertex next;
        private boolean goToFirst = true;
        private Cursor cursor;
        private boolean cursorIsReadOnly;

        public VertexIntIndexIterator() {
            this.cursorIsReadOnly = VertexIntIndexIterable.this.tc.isReadOnly();
            this.cursor = VertexIntIndexIterable.this.thunderGraph.getThunder().openCursor(VertexIntIndexIterable.this.tc.getTxn(), DbEnum.VERTEX_INT_INDEX);
            VertexIntIndexIterable.this.tc.addIteratorCursor(this.cursor);
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
            long elementIdArray[] = new long[1];
            if (this.goToFirst) {
                this.goToFirst = false;
                if (VertexIntIndexIterable.this.thunderGraph.getThunder().getFirstVertexForKeyValueFromIntIndex(this.cursor, elementIdArray, VertexIntIndexIterable.this.key, VertexIntIndexIterable.this.value)) {
                    return new ThunderVertex(VertexIntIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexIntIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromIntIndex(this.cursor, elementIdArray, VertexIntIndexIterable.this.key, VertexIntIndexIterable.this.value)) {
                    return new ThunderVertex(VertexIntIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
