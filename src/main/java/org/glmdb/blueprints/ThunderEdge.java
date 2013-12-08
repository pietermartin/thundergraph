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
public class ThunderEdge extends GlmdbElement implements Edge {

    private String label;
    private long outVertexId;
    private long inVertexId;

    public ThunderEdge(ThunderGraph thunderGraph, long id, String label, long outVertexId, long inVertexId) {
        super(thunderGraph, id);
        this.label = label;
        this.outVertexId = outVertexId;
        this.inVertexId = inVertexId;
    }

    @Override
    public void setProperty(String key, Object value) {
        if (value == null) {
            throw new IllegalArgumentException("A null property can not be stored. You can call removeProperty() instead");
        }
        if (key == null) {
            throw new IllegalArgumentException("Expecting non-null key in setProperty");
        } else if (key.length() == 0) {
            throw new IllegalArgumentException("Expecting non-empty key in setProperty");
        } else if (key.equals("id")) {
            throw new IllegalArgumentException("Can not set the 'id' property on an element");
        } else if (key.equals("label")) {
            throw new IllegalArgumentException("Can not set the 'label' property on an element");
        }
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
        return (T) this.thunderGraph.getGlmdb().removeProperty(tc.getEdgeCursor(), this.id, key, false);
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
