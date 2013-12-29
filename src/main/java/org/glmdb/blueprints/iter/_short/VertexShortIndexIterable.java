package org.glmdb.blueprints.iter._short;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.ThunderVertex;
import org.glmdb.blueprints.TransactionAndCursor;
import org.glmdb.blueprints.iter.BaseThunderIterable;
import org.glmdb.blueprints.iter.BaseThunderIterator;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class VertexShortIndexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private String key;
    private short value;

    public VertexShortIndexIterable(ThunderGraph thunderGraph, String key, short value) {
        super(thunderGraph);
        this.key = key;
        this.value = value;
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        return new VertexShortIndexIterator();
    }

    private final class VertexShortIndexIterator extends BaseThunderIterator<ThunderVertex> implements Iterator {

        private boolean goToFirst = true;

        public VertexShortIndexIterator() {
            super(VertexShortIndexIterable.this.tc);
        }

        @Override
        protected VertexShortIndexIterable getParentIterable() {
            return VertexShortIndexIterable.this;
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.VERTEX_SHORT_INDEX;
        }

        @Override
        public void remove() {
            throw new RuntimeException("Not yet implemented!");
        }

        @Override
        protected ThunderVertex internalNext() {
            long elementIdArray[] = new long[1];
            if (this.goToFirst) {
                this.goToFirst = false;
                if (VertexShortIndexIterable.this.thunderGraph.getThunder().getFirstVertexForKeyValueFromShortIndex(this.cursor, elementIdArray, VertexShortIndexIterable.this.key, VertexShortIndexIterable.this.value)) {
                    return new ThunderVertex(VertexShortIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            } else {
                if (VertexShortIndexIterable.this.thunderGraph.getThunder().getNextVertexForKeyValueFromShortIndex(this.cursor, elementIdArray, VertexShortIndexIterable.this.key, VertexShortIndexIterable.this.value)) {
                    return new ThunderVertex(VertexShortIndexIterable.this.thunderGraph, elementIdArray[0]);
                } else {
                    return null;
                }
            }
        }

    }

}
