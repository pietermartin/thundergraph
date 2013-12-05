package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import junit.framework.Assert;
import org.glmdb.blueprints.GlmdbGraph;
import org.junit.Test;

/**
 * Date: 2013/12/05
 * Time: 7:44 AM
 */
public class ThunderGraphPropertyKeyLoadTest extends BaseGlmdbGraphTest {

    @Test
    public void testLoadPropertyKeyDb() {
        GlmdbGraph g = new GlmdbGraph(this.dbPath);
        Vertex one = g.addVertex(null);
        one.setProperty("one", "1");
        for (int i = 0; i < 10; i++) {
            Vertex many = g.addVertex(null);
            many.setProperty("many" + i, i);
            Edge edge = g.addEdge(null, one, many, "toMany");
            edge.setProperty("edgeName" + i, "name");

        }
        g.commit();

        g.shutdown();

        g = new GlmdbGraph(this.dbPath);
        Assert.assertEquals("1", g.getVertex(0L).getProperty("one"));

        Assert.assertEquals(10, countIter(g.getVertex(0L).getVertices(Direction.OUT).iterator()));
        int count = 0;
        for (Vertex v : g.getVertex(0L).getVertices(Direction.OUT)) {
            Assert.assertEquals("many" + count++, v.getPropertyKeys().iterator().next());
        }

        Assert.assertEquals(10, countIter(g.getVertex(0L).getEdges(Direction.OUT).iterator()));
        count = 0;
        for (Edge edge : g.getVertex(0L).getEdges(Direction.OUT)) {
            Assert.assertEquals("edgeName" + count++, edge.getPropertyKeys().iterator().next());
        }

        g.shutdown();

    }
}
