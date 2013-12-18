package org.glmdb.blueprints.iter._string;

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
public class VertexStringIndexIterable<T extends Vertex> implements Iterable<ThunderVertex> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private String value;

    public VertexStringIndexIterable(ThunderGraph thunderGraph, String key, String value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexStringIndexIterator();
    }

    private final class VertexStringIndexIterator implements Iterator<ThunderVertex> {

        private ThunderVertex next;
        private boolean goToFirst = true;
        private Cursor cursor;
        private boolean cursorIsReadOnly;

        public VertexStringIndexIterator() {
            this.cursorIsReadOnly = VertexStringIndexIterable.this.tc.isReadOnly();
            this.cursor = VertexStringIndexIterable.this.thunderGraph.getThunder().openCursor(VertexStringIndexIterable.this.tc.getTxn(), DbEnum.VERTEX_STRING_INDEX);
            VertexStringIndexIterable.this.tc.addIteratorCursor(this.cursor);
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
                if (VertexStringIndexIterable.this.thunderGraph.getThunder().getFirstVertexForKeyValueFromStringIndex(this.cursor, elementIdArray, VertexStringIndexIterable.this.key, VertexStringIndexIterable.this.value)) {
                    return new ThunderVertex(VertexStringIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexStringIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromStringIndex(this.cursor, elementIdArray, VertexStringIndexIterable.this.key, VertexStringIndexIterable.this.value)) {
                    return new ThunderVertex(VertexStringIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
