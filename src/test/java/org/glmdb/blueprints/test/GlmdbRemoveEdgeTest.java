package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import junit.framework.Assert;
import org.glmdb.blueprints.ThunderGraph;
import org.junit.Test;

/**
 * Date: 2013/11/30
 * Time: 6:58 PM
 */
public class GlmdbRemoveEdgeTest extends BaseGlmdbGraphTest {

    @Test
    public void removeEdgeTest() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        Vertex vertex1 = thunderGraph.addVertex(null);
        for (int i = 0; i < 5; i++) {
            Vertex vertex2 = thunderGraph.addVertex(null);
            vertex2.setProperty("name0", "test0" + i);
            vertex1.addEdge("test", vertex2);
        }
        thunderGraph.commit();

        thunderGraph.printVertexDb();
        thunderGraph.printEdgeDb();
        Assert.assertEquals(6, countVertices(thunderGraph));
        Assert.assertEquals(5, countEdges(thunderGraph));

        thunderGraph.getEdge(4L).remove();
        thunderGraph.commit();
        Assert.assertEquals(6, countVertices(thunderGraph));
        Assert.assertEquals(4, countEdges(thunderGraph));

        thunderGraph.getEdge(3L).remove();
        thunderGraph.commit();
        Assert.assertEquals(6, countVertices(thunderGraph));
        Assert.assertEquals(3, countEdges(thunderGraph));

        thunderGraph.getEdge(2L).remove();
        thunderGraph.commit();
        Assert.assertEquals(6, countVertices(thunderGraph));
        Assert.assertEquals(2, countEdges(thunderGraph));

        thunderGraph.getEdge(1L).remove();
        thunderGraph.commit();
        Assert.assertEquals(6, countVertices(thunderGraph));
        Assert.assertEquals(1, countEdges(thunderGraph));

        thunderGraph.getEdge(0L).remove();
        thunderGraph.commit();
        Assert.assertEquals(6, countVertices(thunderGraph));
        Assert.assertEquals(0, countEdges(thunderGraph));

        thunderGraph.printVertexDb();
        thunderGraph.printEdgeDb();

        thunderGraph.shutdown();
    }

    private int countVertices(ThunderGraph thunderGraph) {
        int result = 0;
        for (Vertex v : thunderGraph.getVertices()) {
            result++;
        }
        return result;
    }

    private int countEdges(ThunderGraph thunderGraph) {
        int result = 0;
        for (Edge e : thunderGraph.getEdges()) {
            result++;
        }
        return result;
    }

}
