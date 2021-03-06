package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.junit.Assert;
import org.junit.Test;

import java.nio.ByteBuffer;

/**
 * Date: 2013/11/19
 * Time: 11:24 PM
 */
public class VertexesTest extends BaseGlmdbGraphTest {

    @Test
    public void testOpenGraph() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        thunderGraph.shutdown();
    }

    @Test
    public void testAddVertex() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            for (int i = 0; i < 10000; i++) {
                Vertex vertex = thunderGraph.addVertex(null);
                vertex.setProperty("name0", "pieter0" + i);
                vertex.setProperty("name1", "pieter1" + i);
                vertex.setProperty("name2", "pieter2" + i);
                vertex.setProperty("name3", "pieter3" + i);
            }
            thunderGraph.commit();

            Vertex vertex = thunderGraph.getVertex(1L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals("pieter01", vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(1000L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals("pieter01000", vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(1000L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals("pieter11000", vertex.getProperty("name1"));

            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testAddVertexPropertyBoolean() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            for (int i = 0; i < 10000; i++) {
                Vertex vertex = thunderGraph.addVertex(null);
                if (i % 2 == 0) {
                    vertex.setProperty("name0", true);
                } else {
                    vertex.setProperty("name0", false);
                }
            }
            thunderGraph.commit();

            Vertex vertex = thunderGraph.getVertex(0L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(true, vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(1L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(false, vertex.getProperty("name0"));

            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testReuseVertexInSubsequentTransaction() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            for (int i = 0; i < 10; i++) {
                Vertex vertex = thunderGraph.addVertex(null);
                vertex.setProperty("name" + i, "test" + i);
            }
            thunderGraph.commit();

            Vertex vertex = thunderGraph.getVertex(0L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals("test0", vertex.getProperty("name0"));
            thunderGraph.commit();

            vertex.setProperty("name0", "testtesttest");
            vertex.setProperty("testProperty", "testPropertyValue");
            thunderGraph.commit();
            Assert.assertEquals("testtesttest", vertex.getProperty("name0"));
            Assert.assertEquals("testPropertyValue", vertex.getProperty("testProperty"));

            vertex = thunderGraph.getVertex(0L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals("testtesttest", vertex.getProperty("name0"));
            Assert.assertEquals("testPropertyValue", vertex.getProperty("testProperty"));

            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testAddVertexPropertyShort() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            for (short i = 0; i < 10000; i++) {
                Vertex vertex = thunderGraph.addVertex(null);
                vertex.setProperty("name0", i);
            }
            thunderGraph.commit();

            Vertex vertex = thunderGraph.getVertex(0L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals((short) 0, vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(1L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals((short) 1, vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(111L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals((short) 111, vertex.getProperty("name0"));

            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testAddVertexPropertyInt() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            for (int i = 0; i < 1000; i++) {
                Vertex vertex = thunderGraph.addVertex(null);
                vertex.setProperty("name0", i);
            }
            thunderGraph.commit();

            Vertex vertex = thunderGraph.getVertex(0L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(0, vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(1L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(1, vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(111L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(111, vertex.getProperty("name0"));

            thunderGraph.commit();

            Assert.assertEquals(1, count(thunderGraph.getVertices("name0", 0)));
            Assert.assertEquals(1, count(thunderGraph.getVertices("name0", 1)));
            Assert.assertEquals(1, count(thunderGraph.getVertices("name0", 999)));

        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testAddVertexPropertyString() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            for (int i = 0; i < 1000; i++) {
                Vertex vertex = thunderGraph.addVertex(null);
                vertex.setProperty("name0", "name" + i);
            }
            thunderGraph.commit();

            Vertex vertex = thunderGraph.getVertex(0L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals("name" + 0, vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(1L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals("name" + 1, vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(111L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals("name" + 111, vertex.getProperty("name0"));

            thunderGraph.commit();

            for (int i = 0; i < 1000; i++) {
                Assert.assertEquals(1, count(thunderGraph.getVertices("name0", "name" + i)));
            }

        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testAddVertexPropertyLong() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            for (long i = 0; i < 10000; i++) {
                Vertex vertex = thunderGraph.addVertex(null);
                vertex.setProperty("name0", i);
            }
            thunderGraph.commit();

            Vertex vertex = thunderGraph.getVertex(0L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(0L, vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(1L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(1L, vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(111L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(111L, vertex.getProperty("name0"));

            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testAddVertexPropertyFloat() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            for (float i = 0; i < 10000; i++) {
                Vertex vertex = thunderGraph.addVertex(null);
                vertex.setProperty("name0", i);
            }
            thunderGraph.commit();

            Vertex vertex = thunderGraph.getVertex(0L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(0F, vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(1L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(1.0F, vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(111L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(111.0F, vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(9999L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(9999.0F, vertex.getProperty("name0"));

            thunderGraph.commit();

            vertex = thunderGraph.addVertex(null);
            vertex.setProperty("testFloat", 123.321F);
            thunderGraph.commit();
            vertex = thunderGraph.getVertex(10000L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(123.321F, vertex.getProperty("testFloat"));

            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testAddVertexPropertyDouble() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            for (double i = 0; i < 10000; i++) {
                Vertex vertex = thunderGraph.addVertex(null);
                vertex.setProperty("name0", i);
            }
            thunderGraph.commit();

            Vertex vertex = thunderGraph.getVertex(0L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(0D, vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(1L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(1.0D, vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(111L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(111.0D, vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(9999L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(9999.0D, vertex.getProperty("name0"));

            thunderGraph.commit();

            vertex = thunderGraph.addVertex(null);
            vertex.setProperty("testDouble", 123.321123D);
            thunderGraph.commit();
            vertex = thunderGraph.getVertex(10000L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(123.321123D, vertex.getProperty("testDouble"));

            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testAddVertexPropertyChar() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            for (int i = 0; i < 1000; i++) {
                Vertex vertex = thunderGraph.addVertex(null);
                vertex.setProperty("name0", (char) i);
            }
            thunderGraph.commit();

            Vertex vertex = thunderGraph.getVertex(0L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals((char) 0, vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(1L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals((char) 1, vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(111L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals((char) 111, vertex.getProperty("name0"));

            thunderGraph.commit();

            vertex = thunderGraph.addVertex(null);
            vertex.setProperty("testChar", 'a');
            thunderGraph.commit();
            vertex = thunderGraph.getVertex(1000L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals('a', vertex.getProperty("testChar"));

            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testAddVertexPropertyByte() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {

            byte[] bytes = ByteBuffer.allocate(4).putInt(10000).array();
            for (int i = 0; i < bytes.length; i++) {
                Vertex vertex = thunderGraph.addVertex(null);
                vertex.setProperty("name0", bytes[i]);
            }
            thunderGraph.commit();

            Vertex vertex = thunderGraph.getVertex(0L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(bytes[0], vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(1L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(bytes[1], vertex.getProperty("name0"));

            vertex = thunderGraph.getVertex(3L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals(bytes[3], vertex.getProperty("name0"));

            thunderGraph.commit();

            vertex = thunderGraph.addVertex(null);
            vertex.setProperty("testByte", (byte) 0x65);
            thunderGraph.commit();
            vertex = thunderGraph.getVertex(4L);
            Assert.assertNotNull(vertex);
            Assert.assertEquals((byte) 0x65, vertex.getProperty("testByte"));

            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testLargeStrings() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            StringBuilder sb = new StringBuilder();
            //TODO
            //Much bigger than this crashes the c code as it is too much to allocate on the stack
            for (int i = 0; i < 1000; i++) {
                sb.append("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
            }
            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name", sb.toString());
            Assert.assertEquals(sb.toString(), v1.getProperty("name"));

        } finally {
            thunderGraph.shutdown();
        }
    }

}
