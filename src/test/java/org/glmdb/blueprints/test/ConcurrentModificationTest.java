package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.*;
import org.glmdb.blueprints.ThunderGraph;
import org.junit.Assert;
import org.junit.Test;

/**
 * Date: 2013/12/08
 * Time: 1:42 PM
 */
public class ConcurrentModificationTest extends BaseGlmdbGraphTest {

    @Test
    public void testConcurrentModification() {
        ThunderGraph graph = new ThunderGraph(this.dbPath);
        Vertex a = graph.addVertex(null);
        Vertex b = graph.addVertex(null);
        Vertex c = graph.addVertex(null);
        System.out.println(a.getId());
        System.out.println(b.getId());
        System.out.println(c.getId());
        if (graph.getFeatures().supportsVertexIteration) {
            for (Vertex vertex : graph.getVertices()) {
                System.out.println(vertex.getId());
                graph.addEdge(null, vertex, a, "x");
                graph.addEdge(null, vertex, a, "y");
            }

            for (Vertex vertex : graph.getVertices()) {
                System.out.println(vertex.getId());
                Assert.assertEquals(BaseTest.count(vertex.getEdges(Direction.OUT)), 2);
                for (Edge edge : vertex.getEdges(Direction.OUT)) {
                    graph.removeEdge(edge);
                }
            }
            for (Vertex vertex : graph.getVertices()) {
                graph.removeVertex(vertex);
            }
        } else if (graph.getFeatures().supportsEdgeIteration) {
            for (int i = 0; i < 10; i++) {
                graph.addEdge(null, graph.addVertex(null), graph.addVertex(null), "test");
            }
            for (Edge edge : graph.getEdges()) {
                graph.removeEdge(edge);
            }
        }
        graph.commit();
        graph.shutdown();

    }
}
