package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import com.tinkerpop.blueprints.VertexQuery;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.Glmdb;
import org.glmdb.blueprints.jni.Transaction;

import java.util.Set;

/**
 * Date: 2013/11/17
 * Time: 4:06 PM
 */
public class GlmdbVertex extends GlmdbElement implements Vertex {

    public GlmdbVertex(GlmdbGraph glmdbGraph, long id) {
        super(glmdbGraph, id);
    }

    @Override
    public void setProperty(String key, Object value) {
        TransactionAndCursor tc = this.glmdbGraph.getWriteTx();
        this.glmdbGraph.getGlmdb().setProperty(tc.getTxn(), tc.getVertexCursor(), this.id, key, value, true);
    }

    @Override
    public <T> T getProperty(String key) {
        TransactionAndCursor tc = this.glmdbGraph.getReadOnlyTx();
        return (T) this.glmdbGraph.getGlmdb().getProperty(tc.getVertexCursor(), this.id, key, true);
    }

    @Override
    public <T> T removeProperty(String key) {
        TransactionAndCursor tc = this.glmdbGraph.getWriteTx();
        return (T) this.glmdbGraph.getGlmdb().removeProperty(tc.getVertexCursor(), this.id, key, true);
    }

    @Override
    public Set<String> getPropertyKeys() {
        TransactionAndCursor tc = this.glmdbGraph.getReadOnlyTx();
        return this.glmdbGraph.getGlmdb().getPropertyKeys(tc.getVertexCursor(), this.id, true);
    }

    @Override
    public Iterable<Edge> getEdges(Direction direction, String... labels) {
        return new GlmdbEdgesFromVertexIterable(this.glmdbGraph, this.id, direction, labels);
    }

    @Override
    public Iterable<Vertex> getVertices(Direction direction, String... labels) {
        return new GlmdbVertexesFromVertexIterable(this.glmdbGraph, this.id, direction, labels);
    }

    @Override
    public VertexQuery query() {
        //TODO
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public Edge addEdge(String label, Vertex inVertex) {
        return this.glmdbGraph.addEdge(null, this, inVertex, label);
    }

    @Override
    public void remove() {
        TransactionAndCursor tc = this.glmdbGraph.getWriteTx();
        this.glmdbGraph.getGlmdb().removeVertex(tc.getTxn(), this.id);
    }
}
