package org.glmdb.blueprints.iter._double;

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
public class VertexDoubleIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private double value;

    public VertexDoubleIndexIterable(ThunderGraph thunderGraph, String key, double value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexDoubleIndexIterator();
    }

    private final class VertexDoubleIndexIterator implements Iterator<ThunderVertex> {

        private ThunderVertex next;
        private boolean goToFirst = true;
        private Cursor cursor;
        private boolean cursorIsReadOnly;

        public VertexDoubleIndexIterator() {
            this.cursorIsReadOnly = VertexDoubleIndexIterable.this.tc.isReadOnly();
            this.cursor = VertexDoubleIndexIterable.this.thunderGraph.getThunder().openCursor(VertexDoubleIndexIterable.this.tc.getTxn(), DbEnum.VERTEX_DOUBLE_INDEX);
            VertexDoubleIndexIterable.this.tc.addIteratorCursor(VertexDoubleIndexIterable.this, this.cursor);
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
                if (VertexDoubleIndexIterable.this.thunderGraph.getThunder().getFirstVertexForKeyValueFromDoubleIndex(this.cursor, elementIdArray, VertexDoubleIndexIterable.this.key, VertexDoubleIndexIterable.this.value)) {
                    return new ThunderVertex(VertexDoubleIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexDoubleIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromDoubleIndex(this.cursor, elementIdArray, VertexDoubleIndexIterable.this.key, VertexDoubleIndexIterable.this.value)) {
                    return new ThunderVertex(VertexDoubleIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
