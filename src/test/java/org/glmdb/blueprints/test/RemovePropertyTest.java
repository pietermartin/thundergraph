package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.junit.Assert;
import org.junit.Test;

/**
 * Date: 2013/11/19
 * Time: 11:24 PM
 */
public class RemovePropertyTest extends BaseGlmdbGraphTest  {

    @Test
    public void testRemoveVertex() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        for (int i = 0; i < 5; i++) {
            Vertex vertex = thunderGraph.addVertex(null);
            vertex.setProperty("name0", "pieter0" + i);
            vertex.setProperty("name1", "pieter1" + i);
            vertex.setProperty("name2", "pieter2" + i);
            vertex.setProperty("name3", "pieter3" + i);
        }
        thunderGraph.commit();
        Vertex vertex = thunderGraph.getVertex(0L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals("pieter00", vertex.getProperty("name0"));
        String value = vertex.removeProperty("name0");
        Assert.assertEquals("pieter00", value);
        value = vertex.removeProperty("name1");
        Assert.assertEquals("pieter10", value);
        value = vertex.removeProperty("name2");
        Assert.assertEquals("pieter20", value);
        value = vertex.removeProperty("name3");
        Assert.assertEquals("pieter30", value);
        thunderGraph.commit();


        vertex = thunderGraph.getVertex(1L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals("pieter01", vertex.getProperty("name0"));
        value = vertex.removeProperty("name0");
        Assert.assertEquals("pieter01", value);
        value = vertex.removeProperty("name1");
        Assert.assertEquals("pieter11", value);
        value = vertex.removeProperty("name2");
        Assert.assertEquals("pieter21", value);
        value = vertex.removeProperty("name3");
        Assert.assertEquals("pieter31", value);
        thunderGraph.commit();

        vertex = thunderGraph.getVertex(2L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals("pieter02", vertex.getProperty("name0"));
        value = vertex.removeProperty("name0");
        Assert.assertEquals("pieter02", value);
        value = vertex.removeProperty("name1");
        Assert.assertEquals("pieter12", value);
        value = vertex.removeProperty("name2");
        Assert.assertEquals("pieter22", value);
        value = vertex.removeProperty("name3");
        Assert.assertEquals("pieter32", value);
        thunderGraph.commit();

        vertex = thunderGraph.getVertex(3L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals("pieter03", vertex.getProperty("name0"));
        value = vertex.removeProperty("name0");
        Assert.assertEquals("pieter03", value);
        value = vertex.removeProperty("name1");
        Assert.assertEquals("pieter13", value);
        value = vertex.removeProperty("name2");
        Assert.assertEquals("pieter23", value);
        value = vertex.removeProperty("name3");
        Assert.assertEquals("pieter33", value);
        thunderGraph.commit();

        vertex = thunderGraph.getVertex(4L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals("pieter04", vertex.getProperty("name0"));
        value = vertex.removeProperty("name0");
        Assert.assertEquals("pieter04", value);
        value = vertex.removeProperty("name1");
        Assert.assertEquals("pieter14", value);
        value = vertex.removeProperty("name2");
        Assert.assertEquals("pieter24", value);
        value = vertex.removeProperty("name3");
        Assert.assertEquals("pieter34", value);
        thunderGraph.commit();

        thunderGraph.shutdown();
    }

    @Test
    public void testEmptyPropertyReturnsNull() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        Vertex vertex = thunderGraph.addVertex(null);
        vertex.setProperty("name0", "pieter0");
        Vertex vertex1 = thunderGraph.addVertex(null);
        vertex1.setProperty("name0", "pieter0");
        Edge edge = thunderGraph.addEdge(null, vertex, vertex1, "test");
        edge.setProperty("name0", "pieter1");
        thunderGraph.commit();
        Vertex testV = thunderGraph.getVertex(0L);
        Assert.assertEquals("pieter0", testV.getProperty("name0"));
        Assert.assertEquals("pieter0", testV.removeProperty("name0"));
        Assert.assertNull(testV.getProperty("name0"));

        Edge testE = thunderGraph.getEdge(0L);
        Assert.assertEquals("pieter1", testE.getProperty("name0"));
        Assert.assertEquals("pieter1", testE.removeProperty("name0"));
        Assert.assertNull(testV.getProperty("name0"));

        thunderGraph.shutdown();
    }

}
