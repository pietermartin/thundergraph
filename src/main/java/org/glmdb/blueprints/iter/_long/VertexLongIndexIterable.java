package org.glmdb.blueprints.iter._long;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.ThunderVertex;
import org.glmdb.blueprints.TransactionAndCursor;
import org.glmdb.blueprints.iter.BaseThunderIterable;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class VertexLongIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private long value;

    public VertexLongIndexIterable(ThunderGraph thunderGraph, String key, long value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexLongIndexIterator();
    }

    private final class VertexLongIndexIterator implements Iterator<ThunderVertex> {

        private ThunderVertex next;
        private boolean goToFirst = true;
        private Cursor cursor;
        private boolean cursorIsReadOnly;

        public VertexLongIndexIterator() {
            this.cursorIsReadOnly = VertexLongIndexIterable.this.tc.isReadOnly();
            this.cursor = VertexLongIndexIterable.this.thunderGraph.getThunder().openCursor(VertexLongIndexIterable.this.tc.getTxn(), DbEnum.VERTEX_LONG_INDEX);
            VertexLongIndexIterable.this.tc.addIteratorCursor(VertexLongIndexIterable.this, this.cursor);
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
                if (VertexLongIndexIterable.this.thunderGraph.getThunder().getFirstVertexForKeyValueFromLongIndex(this.cursor, elementIdArray, VertexLongIndexIterable.this.key, VertexLongIndexIterable.this.value)) {
                    return new ThunderVertex(VertexLongIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexLongIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromLongIndex(this.cursor, elementIdArray, VertexLongIndexIterable.this.key, VertexLongIndexIterable.this.value)) {
                    return new ThunderVertex(VertexLongIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
