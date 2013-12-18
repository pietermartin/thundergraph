package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import com.tinkerpop.blueprints.VertexQuery;
import org.glmdb.blueprints.iter.EdgesFromVertexIterable;
import org.glmdb.blueprints.iter.VertexesFromVertexIterable;

import java.util.Set;

/**
 * Date: 2013/11/17
 * Time: 4:06 PM
 */
public class ThunderVertex extends ThunderElement implements Vertex {

    public ThunderVertex(ThunderGraph thunderGraph, long id) {
        super(thunderGraph, id);
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
        this.thunderGraph.getThunder().setProperty(tc.getTxn(), tc.getVertexCursor(), this.id, key, value, true);
    }

    @Override
    public <T> T getProperty(String key) {
        TransactionAndCursor tc = this.thunderGraph.getReadOnlyTx();
        return (T) this.thunderGraph.getThunder().getProperty(tc.getVertexCursor(), this.id, key, true);
    }

    @Override
    public <T> T removeProperty(String key) {
        TransactionAndCursor tc = this.thunderGraph.getWriteTx();
        return (T) this.thunderGraph.getThunder().removeProperty(tc.getVertexCursor(), this.id, key, true);
    }

    @Override
    public Set<String> getPropertyKeys() {
        TransactionAndCursor tc = this.thunderGraph.getReadOnlyTx();
        return this.thunderGraph.getThunder().getPropertyKeys(tc.getVertexCursor(), this.id, true);
    }

    @Override
    public Iterable<Edge> getEdges(Direction direction, String... labels) {
        return new EdgesFromVertexIterable(this.thunderGraph, this.id, direction, labels);
    }

    @Override
    public Iterable<Vertex> getVertices(Direction direction, String... labels) {
        return new VertexesFromVertexIterable(this.thunderGraph, this.id, direction, labels);
    }

    @Override
    public VertexQuery query() {
        //TODO
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public Edge addEdge(String label, Vertex inVertex) {
        return this.thunderGraph.addEdge(null, this, inVertex, label);
    }

    @Override
    public void remove() {
        TransactionAndCursor tc = this.thunderGraph.getWriteTx();
        this.thunderGraph.getThunder().removeVertex(tc.getTxn(), this.id);
    }
}
