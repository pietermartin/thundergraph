package org.glmdb.blueprints.iter._byte;

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
public class VertexByteIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private final ThunderGraph thunderGraph;
    private final TransactionAndCursor tc;
    private String key;
    private byte value;

    public VertexByteIndexIterable(ThunderGraph thunderGraph, String key, byte value) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexByteIndexIterator();
    }

    private final class VertexByteIndexIterator implements Iterator<ThunderVertex> {

        private ThunderVertex next;
        private boolean goToFirst = true;
        private Cursor cursor;
        private boolean cursorIsReadOnly;

        public VertexByteIndexIterator() {
            this.cursorIsReadOnly = VertexByteIndexIterable.this.tc.isReadOnly();
            this.cursor = VertexByteIndexIterable.this.thunderGraph.getThunder().openCursor(VertexByteIndexIterable.this.tc.getTxn(), DbEnum.VERTEX_BYTE_INDEX);
            VertexByteIndexIterable.this.tc.addIteratorCursor(VertexByteIndexIterable.this, this.cursor);
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
                if (VertexByteIndexIterable.this.thunderGraph.getThunder().getFirstVertexForKeyValueFromByteIndex(this.cursor, elementIdArray, VertexByteIndexIterable.this.key, VertexByteIndexIterable.this.value)) {
                    return new ThunderVertex(VertexByteIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexByteIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromByteIndex(this.cursor, elementIdArray, VertexByteIndexIterable.this.key, VertexByteIndexIterable.this.value)) {
                    return new ThunderVertex(VertexByteIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
