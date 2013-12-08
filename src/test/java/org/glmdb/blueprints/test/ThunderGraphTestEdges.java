package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.junit.Assert;
import org.junit.Test;

/**
 * Date: 2013/12/07
 * Time: 11:28 PM
 */
public class ThunderGraphTestEdges extends BaseGlmdbGraphTest {

    @Test
    public void testAddEdges() {
        ThunderGraph graph = new ThunderGraph(this.dbPath);

        Vertex v1 = graph.addVertex("1");
        Vertex v2 = graph.addVertex("2");
        Vertex v3 = graph.addVertex("3");
        graph.addEdge(null, v1, v2, "knows");
        graph.addEdge(null, v2, v3, "pets");
        graph.addEdge(null, v2, v3, "caresFor");
//        graph.commit();
//        graph.printVertexDb();
        Assert.assertEquals(1, count(v1.getEdges(Direction.OUT)));
        Assert.assertEquals(2, count(v2.getEdges(Direction.OUT)));
        Assert.assertEquals(0, count(v3.getEdges(Direction.OUT)));
        Assert.assertEquals(0, count(v1.getEdges(Direction.IN)));
        Assert.assertEquals(1, count(v2.getEdges(Direction.IN)));
        Assert.assertEquals(2, count(v3.getEdges(Direction.IN)));
        graph.shutdown();
    }
}
