package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.apache.commons.io.FileUtils;
import org.glmdb.blueprints.GlmdbGraph;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;

/**
 * Date: 2013/11/19
 * Time: 11:24 PM
 */
public class GlmdbGraphEdgesTest extends BaseGlmdbGraphTest {

    @Test
    public void testAddEdge() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();

        Vertex vertexTest1 = glmdbGraph.getVertex(0L);
        Assert.assertNotNull(vertexTest1);
        Assert.assertEquals(vertexTest1.getProperty("name"), "vertex1");

        Vertex vertexTest2 = glmdbGraph.getVertex(1L);
        Assert.assertNotNull(vertexTest2);
        Assert.assertEquals(vertexTest2.getProperty("name"), "vertex2");

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddEdgeViaVertex() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");

        vertex1.addEdge("testLabel1", vertex2);
        glmdbGraph.commit();

        Vertex vertexTest1 = glmdbGraph.getVertex(0L);
        Assert.assertNotNull(vertexTest1);
        Assert.assertEquals(vertexTest1.getProperty("name"), "vertex1");

        Vertex vertexTest2 = glmdbGraph.getVertex(1L);
        Assert.assertNotNull(vertexTest2);
        Assert.assertEquals(vertexTest2.getProperty("name"), "vertex2");

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddManyEdges() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        for (int i = 0; i < 1000000; i++) {
            Vertex vertex2 = glmdbGraph.addVertex(null);
            vertex2.setProperty("name", "vertex2");
            Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            Assert.assertEquals("testLabel1", edge.getLabel());
        }
        glmdbGraph.commit();

        Vertex vertexTest1 = glmdbGraph.getVertex(0L);
        Assert.assertNotNull(vertexTest1);
        Assert.assertEquals(vertexTest1.getProperty("name"), "vertex1");

        Vertex vertexTest2 = glmdbGraph.getVertex(1L);
        Assert.assertNotNull(vertexTest2);
        Assert.assertEquals(vertexTest2.getProperty("name"), "vertex2");

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());

        glmdbGraph.commit();

        glmdbGraph.shutdown();
    }

    @Test
    public void testAddEdgePropertyBoolean() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        edge.setProperty("testPropertyEdge1", true);
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());
        Assert.assertEquals(true, edgeTest.getProperty("testPropertyEdge1"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddEdgePropertyShort() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        edge.setProperty("testPropertyEdge1", (short)10);
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());
        Assert.assertEquals((short)10, edgeTest.getProperty("testPropertyEdge1"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddEdgePropertyInt() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        edge.setProperty("testPropertyEdge1", 10);
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());
        Assert.assertEquals(10, edgeTest.getProperty("testPropertyEdge1"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddEdgePropertyLong() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        edge.setProperty("testPropertyEdge1", 10L);
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());
        Assert.assertEquals(10L, edgeTest.getProperty("testPropertyEdge1"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddEdgePropertyFloat() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        edge.setProperty("testPropertyEdge1", 10.101F);
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());
        Assert.assertEquals(10.101F, edgeTest.getProperty("testPropertyEdge1"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddEdgePropertyDouble() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        edge.setProperty("testPropertyEdge1", 10.101D);
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());
        Assert.assertEquals(10.101D, edgeTest.getProperty("testPropertyEdge1"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddEdgePropertyChar() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        edge.setProperty("testPropertyEdge1", 'a');
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());
        Assert.assertEquals('a', edgeTest.getProperty("testPropertyEdge1"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddVertexPropertyByte() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        edge.setProperty("testPropertyEdge1", (byte)0x65);
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());
        Assert.assertEquals((byte)0x65, edgeTest.getProperty("testPropertyEdge1"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

}
