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
    public void testAddVertexPropertyShort() {
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        for (short i = 0; i < 10000; i++) {
            Vertex vertex = glmdbGraph.addVertex(null);
            vertex.setProperty("name0", i);
        }
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

        Vertex vertex = glmdbGraph.getVertex(0L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals((short)0, vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(1L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals((short)1, vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(111L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals((short)111, vertex.getProperty("name0"));

        glmdbGraph.commit();

        glmdbGraph.shutdown();
    }

    @Test
    public void testAddVertexPropertyInt() {
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        for (int i = 0; i < 10000; i++) {
            Vertex vertex = glmdbGraph.addVertex(null);
            vertex.setProperty("name0", i);
        }
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

        Vertex vertex = glmdbGraph.getVertex(0L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(0, vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(1L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(1, vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(111L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(111, vertex.getProperty("name0"));

        glmdbGraph.commit();

        glmdbGraph.shutdown();
    }

    @Test
    public void testAddVertexPropertyLong() {
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        for (long i = 0; i < 10000; i++) {
            Vertex vertex = glmdbGraph.addVertex(null);
            vertex.setProperty("name0", i);
        }
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

        Vertex vertex = glmdbGraph.getVertex(0L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(0L, vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(1L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(1L, vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(111L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(111L, vertex.getProperty("name0"));

        glmdbGraph.commit();

        glmdbGraph.shutdown();
    }

    @Test
    public void testAddVertexPropertyFloat() {
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        for (float i = 0; i < 10000; i++) {
            Vertex vertex = glmdbGraph.addVertex(null);
            vertex.setProperty("name0", i);
        }
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

        Vertex vertex = glmdbGraph.getVertex(0L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(0F, vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(1L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(1.0F, vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(111L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(111.0F, vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(9999L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(9999.0F, vertex.getProperty("name0"));

        glmdbGraph.commit();

        vertex = glmdbGraph.addVertex(null);
        vertex.setProperty("testFloat", 123.321F);
        glmdbGraph.commit();
        vertex = glmdbGraph.getVertex(10000L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(123.321F, vertex.getProperty("testFloat"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddVertexPropertyDouble() {
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        for (double i = 0; i < 10000; i++) {
            Vertex vertex = glmdbGraph.addVertex(null);
            vertex.setProperty("name0", i);
        }
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

        Vertex vertex = glmdbGraph.getVertex(0L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(0D, vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(1L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(1.0D, vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(111L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(111.0D, vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(9999L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(9999.0D, vertex.getProperty("name0"));

        glmdbGraph.commit();

        vertex = glmdbGraph.addVertex(null);
        vertex.setProperty("testDouble", 123.321123D);
        glmdbGraph.commit();
        vertex = glmdbGraph.getVertex(10000L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(123.321123D, vertex.getProperty("testDouble"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddVertexPropertyChar() {
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        for (int i = 0; i < 1000; i++) {
            Vertex vertex = glmdbGraph.addVertex(null);
            vertex.setProperty("name0", (char)i);
        }
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

        Vertex vertex = glmdbGraph.getVertex(0L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals((char)0, vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(1L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals((char)1, vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(111L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals((char)111, vertex.getProperty("name0"));

        glmdbGraph.commit();

        vertex = glmdbGraph.addVertex(null);
        vertex.setProperty("testChar", 'a');
        glmdbGraph.commit();
        vertex = glmdbGraph.getVertex(1000L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals('a', vertex.getProperty("testChar"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddVertexPropertyByte() {
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);

        byte[] bytes = ByteBuffer.allocate(4).putInt(10000).array();
        for (int i = 0; i < bytes.length; i++) {
            Vertex vertex = glmdbGraph.addVertex(null);
            vertex.setProperty("name0", bytes[i]);
        }
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

        Vertex vertex = glmdbGraph.getVertex(0L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(bytes[0], vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(1L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(bytes[1], vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(3L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(bytes[3], vertex.getProperty("name0"));

        glmdbGraph.commit();

        vertex = glmdbGraph.addVertex(null);
        vertex.setProperty("testByte", (byte) 0x65);
        glmdbGraph.commit();
        vertex = glmdbGraph.getVertex(4L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals((byte) 0x65, vertex.getProperty("testByte"));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }


}
