package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Graph;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.junit.Assert;
import org.junit.Test;

import java.util.HashSet;
import java.util.Set;
import java.util.UUID;

/**
 * Date: 2013/11/19
 * Time: 11:24 PM
 */
public class GlmdbGraphGetPropertyKeysTest extends BaseGlmdbGraphTest {

    @Test
    public void testEmptyPropertyKeys() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        Vertex vertex1 = thunderGraph.addVertex(null);
        for (int i = 0; i < 5; i++) {
            Vertex vertex2 = thunderGraph.addVertex(null);
            Assert.assertEquals(0, vertex2.getPropertyKeys().size());
            Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "test");
            Assert.assertEquals(0, edge.getPropertyKeys().size());
        }
        thunderGraph.shutdown();
    }

    @Test
    public void testPropertyKeys() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        for (int i = 0; i < 5; i++) {
            Vertex vertex = thunderGraph.addVertex(null);
            vertex.setProperty("name0", "pieter0" + i);
            vertex.setProperty("name1", "pieter1" + i);
            vertex.setProperty("name2", "pieter2" + i);
            vertex.setProperty("name3", "pieter3" + i);
            Set<String> propertyKeys = vertex.getPropertyKeys();
            Assert.assertEquals(4, propertyKeys.size());
        }
        Set<String> propertyKeys = thunderGraph.getVertex(1L).getPropertyKeys();
        Assert.assertEquals(4, propertyKeys.size());
        thunderGraph.commit();

        propertyKeys = thunderGraph.getVertex(1L).getPropertyKeys();
        Assert.assertEquals(4, propertyKeys.size());
        boolean hasName0 = false;
        boolean hasName1 = false;
        boolean hasName2 = false;
        boolean hasName3 = false;
        for (String s : propertyKeys) {
            if (s.equals("name0")) {
                hasName0 = true;
            } else if (s.equals("name1")) {
                hasName1 = true;
            } else if (s.equals("name2")) {
                hasName2 = true;
            } else if (s.equals("name3")) {
                hasName3 = true;
            } else {
                Assert.fail("property key not found!");
            }
        }
        Assert.assertTrue(hasName0 && hasName1 && hasName2 && hasName3);
        thunderGraph.shutdown();
    }

    @Test
    public void testAddManyVertexProperties() {
        ThunderGraph graph = new ThunderGraph(this.dbPath);
        if (graph.getFeatures().supportsVertexProperties && graph.getFeatures().supportsStringProperty) {
            Set<Vertex> vertices = new HashSet<Vertex>();
            for (int i = 0; i < 50; i++) {
                Vertex vertex = graph.addVertex(null);
                for (int j = 0; j < 15; j++) {
                    String key1 = UUID.randomUUID().toString();
                    String value1 = UUID.randomUUID().toString();
                    vertex.setProperty(key1, value1);
                }
                vertices.add(vertex);
            }
            graph.commit();
            graph.printVertexPropertyKeyDb();

            if (graph.getFeatures().supportsVertexIteration)
                Assert.assertEquals(50, count(graph.getVertices()));
            Assert.assertEquals(50, vertices.size());
            for (Vertex vertex : vertices) {
                Assert.assertEquals(15, vertex.getPropertyKeys().size());
            }
        }
        graph.commit();
        graph.shutdown();
    }

    @Test
    public void testEdgePropertyKeys() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        Vertex vertex = thunderGraph.addVertex(null);
        for (int i = 0; i < 5; i++) {
            Vertex vertex1 = thunderGraph.addVertex(null);
            vertex1.setProperty("name", "a" + i);
            Edge edge = vertex.addEdge("label1", vertex1);
            edge.setProperty("name" + i, i);
        }
        thunderGraph.commit();
        thunderGraph.printVertexDb();

        Set<String> propertyKeys = thunderGraph.getEdge(0L).getPropertyKeys();
        Assert.assertEquals(1, propertyKeys.size());

        propertyKeys = thunderGraph.getEdge(1L).getPropertyKeys();
        Assert.assertEquals(1, propertyKeys.size());

        propertyKeys = thunderGraph.getEdge(2L).getPropertyKeys();
        Assert.assertEquals(1, propertyKeys.size());

        propertyKeys = thunderGraph.getEdge(3L).getPropertyKeys();
        Assert.assertEquals(1, propertyKeys.size());

        thunderGraph.shutdown();
    }

}
