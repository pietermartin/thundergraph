package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import com.tinkerpop.blueprints.VertexQuery;

/**
 * Date: 2013/11/17
 * Time: 4:06 PM
 */
public class GlmdbVertex extends GlmdbElement implements Vertex {

    private long id;

    public GlmdbVertex(long id) {
        this.id = id;
    }

    @Override
    public Iterable<Edge> getEdges(Direction direction, String... labels) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public Iterable<Vertex> getVertices(Direction direction, String... labels) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public VertexQuery query() {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public Edge addEdge(String label, Vertex inVertex) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }
}
