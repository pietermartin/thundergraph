package org.glmdb.blueprints.iter._float;

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
public class VertexFloatIndexIterable<T extends Vertex> implements Iterable<ThunderVertex> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private float value;

    public VertexFloatIndexIterable(ThunderGraph thunderGraph, String key, float value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexFloatIndexIterator();
    }

    private final class VertexFloatIndexIterator implements Iterator<ThunderVertex> {

        private ThunderVertex next;
        private boolean goToFirst = true;
        private Cursor cursor;
        private boolean cursorIsReadOnly;

        public VertexFloatIndexIterator() {
            this.cursorIsReadOnly = VertexFloatIndexIterable.this.tc.isReadOnly();
            this.cursor = VertexFloatIndexIterable.this.thunderGraph.getThunder().openCursor(VertexFloatIndexIterable.this.tc.getTxn(), DbEnum.VERTEX_FLOAT_INDEX);
            VertexFloatIndexIterable.this.tc.addIteratorCursor(this.cursor);
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
                if (VertexFloatIndexIterable.this.thunderGraph.getThunder().getFirstVertexForKeyValueFromFloatIndex(this.cursor, elementIdArray, VertexFloatIndexIterable.this.key, VertexFloatIndexIterable.this.value)) {
                    return new ThunderVertex(VertexFloatIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexFloatIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromFloatIndex(this.cursor, elementIdArray, VertexFloatIndexIterable.this.key, VertexFloatIndexIterable.this.value)) {
                    return new ThunderVertex(VertexFloatIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
