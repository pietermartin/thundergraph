package org.glmdb.blueprints.iter;

import com.tinkerpop.blueprints.Direction;
import org.glmdb.blueprints.ThunderElement;
import org.glmdb.blueprints.TransactionAndCursor;

import java.util.Iterator;

/**
 * Date: 2013/12/25
 * Time: 8:22 PM
 */
abstract class BaseForKeyValueIterator<E extends ThunderElement> extends BaseThunderIterator<ThunderElement> implements Iterator {

    BaseForKeyValueIterator(TransactionAndCursor tc) {
        super(tc);
    }

    @Override
    public void remove() {
        if (this.cursorIsReadOnly) {
            //Upgrade transaction to a writable one.
            //Replace the current cursor with a new one from the writable transaction
            this.tc = this.getParentIterable().thunderGraph.getWriteTx();
            this.cursorIsReadOnly = false;
            this.cursor = this.getParentIterable().thunderGraph.getThunder().openAndPositionCursorOnEdgeInVertexDb(
                    this.tc.getTxn(),
                    this.getParentIterable().vertexId,
                    (this.currentEdgeOutVertexId == this.getParentIterable().vertexId ? Direction.OUT : Direction.IN),
                    this.currentLabel,
                    this.edgeId
            );
        }
        this.internalRemove();
    }

    protected abstract void internalRemove();

}
