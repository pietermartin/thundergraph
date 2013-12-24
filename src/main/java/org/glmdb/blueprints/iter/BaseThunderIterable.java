package org.glmdb.blueprints.iter;

import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.TransactionAndCursor;

/**
 * Date: 2013/12/24
 * Time: 3:15 PM
 */
public abstract class BaseThunderIterable {

    protected ThunderGraph thunderGraph;
    protected TransactionAndCursor tc;
    protected long vertexId;
    private boolean refresh;

    public BaseThunderIterable() {

    }

    BaseThunderIterable(ThunderGraph thunderGraph, long vertexId) {
        this.thunderGraph = thunderGraph;
        this.tc = this.thunderGraph.getReadOnlyTx();
        this.vertexId = vertexId;
    }

    public boolean isRefresh() {
        return refresh;
    }

    public void setRefresh(boolean refresh) {
        this.refresh = refresh;
    }
}
