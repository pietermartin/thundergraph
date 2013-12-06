package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import com.tinkerpop.blueprints.util.ExceptionFactory;

import java.util.Set;

/**
 * Date: 2013/11/23
 * Time: 8:54 PM
 */
public class GlmdbEdge extends GlmdbElement implements Edge {

    private String label;
    private long outVertexId;
    private long inVertexId;

    public GlmdbEdge(ThunderGraph thunderGraph, long id, String label, long outVertexId, long inVertexId) {
        super(thunderGraph, id);
        this.label = label;
        this.outVertexId = outVertexId;
        this.inVertexId = inVertexId;
    }

    @Override
    public void setProperty(String key, Object value) {
        TransactionAndCursor tc = this.thunderGraph.getWriteTx();
        this.thunderGraph.getGlmdb().setProperty(tc.getTxn(), tc.getEdgeCursor(), this.id, key, value, false);
    }

    @Override
    public <T> T getProperty(String key) {
        TransactionAndCursor tc = this.thunderGraph.getReadOnlyTx();
        return (T) this.thunderGraph.getGlmdb().getProperty(tc.getEdgeCursor(), this.id, key, false);
    }

    @Override
    public <T> T removeProperty(String key) {
        TransactionAndCursor tc = this.thunderGraph.getWriteTx();
        return (T) this.thunderGraph.getGlmdb().removeProperty(tc.getVertexCursor(), this.id, key, false);
    }

    @Override
    public Set<String> getPropertyKeys() {
        TransactionAndCursor tc = this.thunderGraph.getReadOnlyTx();
        return this.thunderGraph.getGlmdb().getPropertyKeys(tc.getEdgeCursor(), this.id, false);
    }


    @Override
    public Vertex getVertex(Direction direction) throws IllegalArgumentException {
        if (direction.equals(Direction.OUT)) {
            return new ThunderVertex(this.thunderGraph, this.outVertexId);
        } else if (direction.equals(Direction.IN)) {
            return new ThunderVertex(this.thunderGraph, this.inVertexId);
        } else {
            throw ExceptionFactory.bothIsNotSupported();
        }
    }

    @Override
    public void remove() {
        TransactionAndCursor tc = this.thunderGraph.getWriteTx();
        this.thunderGraph.getGlmdb().removeEdge(tc.getTxn(), this.id);
    }

    @Override
    public String getLabel() {
        return this.label;
    }

    long getOutVertexId() {
        return outVertexId;
    }

    long getInVertexId() {
        return inVertexId;
    }

}
