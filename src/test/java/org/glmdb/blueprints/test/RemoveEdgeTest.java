package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import junit.framework.Assert;
import org.glmdb.blueprints.ThunderGraph;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.UUID;

/**
 * Date: 2013/11/30
 * Time: 6:58 PM
 */
public class RemoveEdgeTest extends BaseGlmdbGraphTest {

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


        thunderGraph.shutdown();
    }

    @Test
    public void testRemovingVertices() {
        ThunderGraph graph = new ThunderGraph(this.dbPath);
        int vertexCount = 50;
        List<Vertex> vertices = new ArrayList<Vertex>();
        List<Edge> edges = new ArrayList<Edge>();

        for (int i = 0; i < vertexCount; i++) {
            vertices.add(graph.addVertex(null));
        }

        for (int i = 0; i < vertexCount; i = i + 2) {
            Vertex a = vertices.get(i);
            Vertex b = vertices.get(i + 1);
            edges.add(graph.addEdge(null, a, b, "a" + UUID.randomUUID()));

        }

        graph.commit();

        Random random = new Random();
        int counter = 0;
        for (Vertex v : vertices) {
            counter = counter + 1;
            if (random.nextBoolean())
                graph.removeVertex(v);
            else
                v.remove();
            if ((counter + 1) % 2 == 0) {
                if (graph.getFeatures().supportsEdgeIteration) {
                    Assert.assertEquals(edges.size() - ((counter + 1) / 2), count(graph.getEdges()));
                }
            }

            if (graph.getFeatures().supportsVertexIteration) {
                Assert.assertEquals(vertices.size() - counter, count(graph.getVertices()));
            }
        }
        graph.shutdown();
    }



    private int countVertices(ThunderGraph thunderGraph) {
        int result = 0;
        for (Vertex ignored : thunderGraph.getVertices()) {
            result++;
        }
        return result;
    }

    private int countEdges(ThunderGraph thunderGraph) {
        int result = 0;
        for (Edge ignored : thunderGraph.getEdges()) {
            result++;
        }
        return result;
    }

}
