package org.glmdb.blueprints.test;

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
public class GlmdbGraphTestVertexes {

    File dbPath = null;

    @Before
    public void beforeTests() throws IOException {
        this.dbPath = new File("/tmp/testdb");
        FileUtils.deleteDirectory(this.dbPath);
        this.dbPath.mkdir();
    }

    @Test
    public void testOpenGraph() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddVertex() {
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        for (int i = 0; i < 10000; i++) {
            Vertex vertex = glmdbGraph.addVertex(null);
            vertex.setProperty("name0", "pieter0" + i);
            vertex.setProperty("name1", "pieter1" + i);
            vertex.setProperty("name2", "pieter2" + i);
            vertex.setProperty("name3", "pieter3" + i);
        }
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

        Vertex vertex = glmdbGraph.getVertex(1L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals("pieter01", vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(1000L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals("pieter01000", vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(1000L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals("pieter11000", vertex.getProperty("name1"));

        glmdbGraph.commit();

        glmdbGraph.shutdown();
    }

    @Test
    public void testAddVertexPropertyBoolean() {
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        for (int i = 0; i < 10000; i++) {
            Vertex vertex = glmdbGraph.addVertex(null);
            if (i % 2 == 0) {
                vertex.setProperty("name0", true);
            } else {
                vertex.setProperty("name0", false);
            }
        }
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));

        Vertex vertex = glmdbGraph.getVertex(0L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(true, vertex.getProperty("name0"));

        vertex = glmdbGraph.getVertex(1L);
        Assert.assertNotNull(vertex);
        Assert.assertEquals(false, vertex.getProperty("name0"));

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
