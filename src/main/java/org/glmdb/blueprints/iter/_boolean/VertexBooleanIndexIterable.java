package org.glmdb.blueprints.iter._boolean;

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
public class VertexBooleanIndexIterable<T extends Vertex> implements Iterable<ThunderVertex> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private boolean value;

    public VertexBooleanIndexIterable(ThunderGraph thunderGraph, String key, boolean value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexBooleanIndexIterator();
    }

    private final class VertexBooleanIndexIterator implements Iterator<ThunderVertex> {

        private ThunderVertex next;
        private boolean goToFirst = true;
        private Cursor cursor;
        private boolean cursorIsReadOnly;

        public VertexBooleanIndexIterator() {
            this.cursorIsReadOnly = VertexBooleanIndexIterable.this.tc.isReadOnly();
            this.cursor = VertexBooleanIndexIterable.this.thunderGraph.getThunder().openCursor(VertexBooleanIndexIterable.this.tc.getTxn(), DbEnum.VERTEX_BOOLEAN_INDEX);
            VertexBooleanIndexIterable.this.tc.addIteratorCursor(this.cursor);
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
                if (VertexBooleanIndexIterable.this.thunderGraph.getThunder().getFirstVertexForKeyValueFromBooleanIndex(this.cursor, elementIdArray, VertexBooleanIndexIterable.this.key, VertexBooleanIndexIterable.this.value)) {
                    return new ThunderVertex(VertexBooleanIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexBooleanIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromBooleanIndex(this.cursor, elementIdArray, VertexBooleanIndexIterable.this.key, VertexBooleanIndexIterable.this.value)) {
                    return new ThunderVertex(VertexBooleanIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
