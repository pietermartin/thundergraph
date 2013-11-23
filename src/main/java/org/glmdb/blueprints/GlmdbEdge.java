package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.Glmdb;
import org.glmdb.blueprints.jni.Transaction;

/**
 * Date: 2013/11/23
 * Time: 8:54 PM
 */
public class GlmdbEdge extends GlmdbElement implements Edge {

    private String label;
    private long outVertexId;
    private long inVertexId;

    public GlmdbEdge(Glmdb glmdb, Transaction txn, Cursor cursor, long id, String label, long outVertexId, long inVertexId) {
        super(glmdb, txn, cursor, id);
        this.label = label;
        this.outVertexId = outVertexId;
        this.inVertexId = inVertexId;
    }

    @Override
    public Vertex getVertex(Direction direction) throws IllegalArgumentException {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public String getLabel() {
        return this.label;
    }

    public long getOutVertexId() {
        return outVertexId;
    }

    public long getInVertexId() {
        return inVertexId;
    }

}
