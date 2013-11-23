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
public class GlmdbGraphTestEdges {

    File dbPath = null;

    @Before
    public void beforeTests() throws IOException {
        this.dbPath = new File("/tmp/testdb");
        FileUtils.deleteDirectory(this.dbPath);
        this.dbPath.mkdir();
    }


    @Test
    public void testAddEdge() {
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();

        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

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
        long start = System.currentTimeMillis();
        System.out.println();
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

        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

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
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        edge.setProperty("testPropertyEdge1", true);
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());
        Assert.assertEquals(true, edgeTest.getProperty("testPropertyEdge1"));

        glmdbGraph.commit();

        glmdbGraph.shutdown();
    }

    @Test
    public void testAddEdgePropertyShort() {
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        edge.setProperty("testPropertyEdge1", (short)10);
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());
        Assert.assertEquals((short)10, edgeTest.getProperty("testPropertyEdge1"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddEdgePropertyInt() {
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        edge.setProperty("testPropertyEdge1", 10);
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());
        Assert.assertEquals(10, edgeTest.getProperty("testPropertyEdge1"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddEdgePropertyLong() {
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        edge.setProperty("testPropertyEdge1", 10L);
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());
        Assert.assertEquals(10L, edgeTest.getProperty("testPropertyEdge1"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddEdgePropertyFloat() {
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        edge.setProperty("testPropertyEdge1", 10.101F);
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());
        Assert.assertEquals(10.101F, edgeTest.getProperty("testPropertyEdge1"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddEdgePropertyDouble() {
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        edge.setProperty("testPropertyEdge1", 10.101D);
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());
        Assert.assertEquals(10.101D, edgeTest.getProperty("testPropertyEdge1"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddEdgePropertyChar() {
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        edge.setProperty("testPropertyEdge1", 'a');
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());
        Assert.assertEquals('a', edgeTest.getProperty("testPropertyEdge1"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddVertexPropertyByte() {
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertex1");
        Vertex vertex2 = glmdbGraph.addVertex(null);
        vertex2.setProperty("name", "vertex2");
        Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
        edge.setProperty("testPropertyEdge1", (byte)0x65);
        Assert.assertEquals("testLabel1", edge.getLabel());
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

        Edge edgeTest = glmdbGraph.getEdge(0L);
        Assert.assertNotNull("Edge must not be null!!!", edgeTest);
        Assert.assertEquals("testLabel1", edgeTest.getLabel());
        Assert.assertEquals((byte)0x65, edgeTest.getProperty("testPropertyEdge1"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }


}
