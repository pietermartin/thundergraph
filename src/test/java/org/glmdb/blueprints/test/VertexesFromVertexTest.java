package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.apache.commons.lang.time.StopWatch;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.ThunderVertex;
import org.glmdb.blueprints.jni.DbEnum;
import org.junit.Assert;
import org.junit.Test;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Date: 2013/11/26
 * Time: 9:52 PM
 */
public class VertexesFromVertexTest extends BaseGlmdbGraphTest {

    @Test
    public void testVerticesFromVertices() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex vertex1 = thunderGraph.addVertex(null);
            vertex1.setProperty("name", "vertexOut1");
            for (int i = 0; i < 10; i++) {
                Vertex vertex2 = thunderGraph.addVertex(null);
                vertex2.setProperty("name", "vertexIn" + i);
                Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
                edge.setProperty("name", "edge" + i);
            }
            thunderGraph.commit();

            List<String> edgeName = new ArrayList<String>();
            int count = 0;
            Vertex vertex1_1 = thunderGraph.getVertex(0L);
            for (Edge edge : vertex1_1.getEdges(Direction.BOTH, "testLabel1")) {
                edgeName.add((String) edge.getProperty("name"));
                count++;
            }
            Assert.assertEquals(10, count);
            thunderGraph.commit();

            List<String> vertexName = new ArrayList<String>();
            count = 0;
            vertex1_1 = thunderGraph.getVertex(0L);
            for (Vertex vertex : vertex1_1.getVertices(Direction.BOTH, "testLabel1")) {
                vertexName.add((String) vertex.getProperty("name"));
                count++;
            }
            Assert.assertEquals(10, count);
            Assert.assertEquals("vertexIn0", vertexName.get(0));
            Assert.assertEquals("vertexIn3", vertexName.get(3));
            Assert.assertEquals("vertexIn6", vertexName.get(6));
            Assert.assertEquals("vertexIn9", vertexName.get(9));
            thunderGraph.commit();

            vertexName.clear();
            count = 0;
            vertex1_1 = thunderGraph.getVertex(0L);
            for (Vertex vertex : vertex1_1.getVertices(Direction.BOTH)) {
                vertexName.add((String) vertex.getProperty("name"));
                count++;
            }
            Assert.assertEquals(10, count);
            Assert.assertEquals("vertexIn0", vertexName.get(0));
            Assert.assertEquals("vertexIn3", vertexName.get(3));
            Assert.assertEquals("vertexIn6", vertexName.get(6));
            Assert.assertEquals("vertexIn9", vertexName.get(9));
            thunderGraph.commit();

        } finally {
            thunderGraph.shutdown();
        }
    }


    @Test
    public void testVerticesFromVerticesMultipleLabels() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex vertex1 = thunderGraph.addVertex(null);
            vertex1.setProperty("name", "vertexOut1");
            for (int i = 0; i < 100; i++) {
                Vertex vertex2 = thunderGraph.addVertex(null);
                vertex2.setProperty("name", "vertexIn" + i);
                Edge edge;
                if (i < 20) {
                    edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel20");
                } else if (i < 40) {
                    edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel40");
                } else if (i < 60) {
                    edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel60");
                } else if (i < 80) {
                    edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel80");
                } else {
                    edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel100");
                }
                edge.setProperty("name", "edge" + i);
            }
            thunderGraph.commit();

            Vertex vertex1_1 = thunderGraph.getVertex(0L);
            Assert.assertEquals(20, count(vertex1_1.getEdges(Direction.OUT, "testLabel20")));
            thunderGraph.commit();

            vertex1_1 = thunderGraph.getVertex(0L);
            Assert.assertEquals(20, count(vertex1_1.getEdges(Direction.OUT, "testLabel40")));
            thunderGraph.commit();

            vertex1_1 = thunderGraph.getVertex(0L);
            Assert.assertEquals(20, count(vertex1_1.getEdges(Direction.OUT, "testLabel60")));
            thunderGraph.commit();

            vertex1_1 = thunderGraph.getVertex(0L);
            Assert.assertEquals(20, count(vertex1_1.getEdges(Direction.OUT, "testLabel80")));
            thunderGraph.commit();

            vertex1_1 = thunderGraph.getVertex(0L);
            Assert.assertEquals(20, count(vertex1_1.getEdges(Direction.OUT, "testLabel100")));
            thunderGraph.commit();

            vertex1_1 = thunderGraph.getVertex(0L);
            Assert.assertEquals(100, count(vertex1_1.getEdges(Direction.OUT)));
            thunderGraph.commit();

        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void removeVertexFromIterTest() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex vertex1 = thunderGraph.addVertex(null);
            vertex1.setProperty("name", "vertexOut1");
            for (int i = 0; i < 1000; i++) {
                Vertex vertex2 = thunderGraph.addVertex(null);
                vertex2.setProperty("name", "vertexIn" + i);
                Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
                edge.setProperty("name", "edge1" + i);
            }
            thunderGraph.commit();
            Assert.assertEquals(1, countIter(thunderGraph.getVertex(5L).getEdges(Direction.IN, "testLabel1").iterator()));
            thunderGraph.commit();

            int count = 0;
            Vertex v = thunderGraph.getVertex(0L);
            Iterator<Vertex> iterator = v.getVertices(Direction.OUT, "testLabel1").iterator();
            while (iterator.hasNext()) {
                iterator.next();
                count++;
                if (count == 5) {
                    iterator.remove();
                }
            }
            thunderGraph.commit();
            Assert.assertNull(thunderGraph.getVertex(5L));
            thunderGraph.commit();

            v = thunderGraph.getVertex(0L);
            iterator = v.getVertices(Direction.OUT, "testLabel1").iterator();
            while (iterator.hasNext()) {
                iterator.next();
                iterator.remove();
            }
            thunderGraph.commit();

            Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getVertices(Direction.OUT, "testLabel1").iterator()));
            Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getEdges(Direction.OUT, "testLabel1").iterator()));
            thunderGraph.commit();

        } finally {
            thunderGraph.shutdown();
        }

    }

    @Test
    public void removeVertexFromIterTest1() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex vertex1 = thunderGraph.addVertex(null);
            vertex1.setProperty("name", "vertexOut1");
            for (int i = 0; i < 1000; i++) {
                Vertex vertex2 = thunderGraph.addVertex(null);
                vertex2.setProperty("name", "vertexIn" + i);
                Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
                edge.setProperty("name", "edge1" + i);
            }
            thunderGraph.commit();

            int count = 0;
            Vertex v = thunderGraph.getVertex(0L);
            Iterator<Vertex> iterator = v.getVertices(Direction.OUT).iterator();
            while (iterator.hasNext()) {
                iterator.next();
                count++;
                if (count == 5) {
                    iterator.remove();
                }
            }
            thunderGraph.commit();
            Assert.assertNull(thunderGraph.getVertex(5L));
            thunderGraph.commit();

            v = thunderGraph.getVertex(0L);
            iterator = v.getVertices(Direction.OUT).iterator();
            while (iterator.hasNext()) {
                iterator.next();
                iterator.remove();
            }
            thunderGraph.commit();

            Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getVertices(Direction.OUT).iterator()));
            Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getEdges(Direction.OUT).iterator()));
            thunderGraph.commit();

        } finally {
            thunderGraph.shutdown();
        }

    }

    @Test
    public void removeVertexFromIterTest2() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex vertex1 = thunderGraph.addVertex(null);
            vertex1.setProperty("name", "vertexOut1");
            for (int i = 0; i < 1000; i++) {
                Vertex vertex2 = thunderGraph.addVertex(null);
                vertex2.setProperty("name", "vertexIn" + i);
                Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
                edge.setProperty("name", "edge1" + i);
            }
            thunderGraph.commit();

            int count = 0;
            Vertex v = thunderGraph.getVertex(0L);
            Iterator<Vertex> iterator = v.getVertices(Direction.OUT).iterator();
            while (iterator.hasNext()) {
                v = iterator.next();
                count++;
                if (count == 5) {
                    v.remove();
                }
            }
            thunderGraph.commit();
            Assert.assertNull(thunderGraph.getVertex(5L));
            thunderGraph.commit();

            v = thunderGraph.getVertex(0L);
            iterator = v.getVertices(Direction.OUT).iterator();
            while (iterator.hasNext()) {
                v = iterator.next();
                v.remove();
            }
            thunderGraph.commit();

            Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getVertices(Direction.OUT).iterator()));
            Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getEdges(Direction.OUT).iterator()));
            thunderGraph.commit();

        } finally {
            thunderGraph.shutdown();
        }

    }

    @Test
    public void removeVertexFromIterTest3() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex vertex1 = thunderGraph.addVertex(null);
            vertex1.setProperty("name", "vertexOut1");
            for (int i = 0; i < 1000; i++) {
                Vertex vertex2 = thunderGraph.addVertex(null);
                vertex2.setProperty("name", "vertexIn" + i);
                Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
                edge.setProperty("name", "edge1" + i);
            }
            thunderGraph.commit();

            int count = 0;
            Vertex v = thunderGraph.getVertex(0L);
            Iterator<Vertex> iterator = v.getVertices(Direction.OUT).iterator();
            while (iterator.hasNext()) {
                count++;
                v = iterator.next();
                v.remove();
                if (count == 999) {
                    break;
                }
            }
            thunderGraph.commit();
            v = thunderGraph.getVertex(0L);
            Assert.assertEquals(1, count(v.getVertices(Direction.OUT)));
            iterator = v.getVertices(Direction.OUT).iterator();
            while (iterator.hasNext()) {
                v = iterator.next();
                v.remove();
            }
            Assert.assertEquals(0, count(v.getVertices(Direction.OUT)));
            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void removeVertexFromIterTest4() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex vertex1 = thunderGraph.addVertex(null);
            vertex1.setProperty("name", "vertexOut1");
            for (int i = 0; i < 1000; i++) {
                Vertex vertex2 = thunderGraph.addVertex(null);
                vertex2.setProperty("name", "vertexIn" + i);
                Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
                edge.setProperty("name", "edge1" + i);
            }
            thunderGraph.commit();

            Vertex v = thunderGraph.getVertex(0L);
            Iterator<Vertex> iterator = v.getVertices(Direction.OUT).iterator();
            //Remove the first out vertex
            Vertex firstOutVertex = thunderGraph.getVertex(1L);
            firstOutVertex.remove();
            if (iterator.hasNext()) {
                v = iterator.next();
                Assert.assertEquals(2L, v.getId());
            }

            if (iterator.hasNext()) {
                iterator.next();
                iterator.remove();
            }
            v = thunderGraph.getVertex(0L);
            Assert.assertEquals(998, count(v.getVertices(Direction.OUT)));

            thunderGraph.commit();

            while (iterator.hasNext()) {
                iterator.next();
                iterator.remove();
            }
            v = thunderGraph.getVertex(0L);
            //one remains as we called next to assert 2L without removing it
            Assert.assertEquals(1, count(v.getVertices(Direction.OUT)));
            Assert.assertEquals(2L, v.getVertices(Direction.OUT).iterator().next().getId());
            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }
    }


    @Test
    public void removeVertexFromIterWithLabelsTest1() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex vertex1 = thunderGraph.addVertex(null);
            vertex1.setProperty("name", "vertexOut1");
            for (int i = 0; i < 1000; i++) {
                Vertex vertex2 = thunderGraph.addVertex(null);
                vertex2.setProperty("name", "vertexIn" + i);
                Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
                edge.setProperty("name", "edge1" + i);
            }
            thunderGraph.commit();

            int count = 0;
            Vertex v = thunderGraph.getVertex(0L);
            Iterator<Vertex> iterator = v.getVertices(Direction.OUT, "testLabel1").iterator();
            while (iterator.hasNext()) {
                iterator.next();
                count++;
                if (count == 5) {
                    iterator.remove();
                }
            }
            thunderGraph.commit();
            Assert.assertNull(thunderGraph.getVertex(5L));
            thunderGraph.commit();

            v = thunderGraph.getVertex(0L);
            iterator = v.getVertices(Direction.OUT, "testLabel1").iterator();
            while (iterator.hasNext()) {
                iterator.next();
                iterator.remove();
            }
            thunderGraph.commit();

            Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getVertices(Direction.OUT, "testLabel1").iterator()));
            Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getEdges(Direction.OUT, "testLabel1").iterator()));
            thunderGraph.commit();

        } finally {
            thunderGraph.shutdown();
        }

    }

    @Test
    public void removeVertexFromIterWithLabelsTest2() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex vertex1 = thunderGraph.addVertex(null);
            vertex1.setProperty("name", "vertexOut1");
            for (int i = 0; i < 1000; i++) {
                Vertex vertex2 = thunderGraph.addVertex(null);
                vertex2.setProperty("name", "vertexIn" + i);
                Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
                edge.setProperty("name", "edge1" + i);
            }
            thunderGraph.commit();

            int count = 0;
            Vertex v = thunderGraph.getVertex(0L);
            Iterator<Vertex> iterator = v.getVertices(Direction.OUT, "testLabel1").iterator();
            while (iterator.hasNext()) {
                v = iterator.next();
                count++;
                if (count == 5) {
                    v.remove();
                }
            }
            thunderGraph.commit();
            Assert.assertNull(thunderGraph.getVertex(5L));
            thunderGraph.commit();

            v = thunderGraph.getVertex(0L);
            iterator = v.getVertices(Direction.OUT, "testLabel1").iterator();
            while (iterator.hasNext()) {
                v = iterator.next();
                v.remove();
            }
            thunderGraph.commit();

            Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getVertices(Direction.OUT, "testLabel1").iterator()));
            Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getEdges(Direction.OUT, "testLabel1").iterator()));
            thunderGraph.commit();

        } finally {
            thunderGraph.shutdown();
        }

    }

    @Test
    public void removeVertexFromIterWithLabelsTest3() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex vertex1 = thunderGraph.addVertex(null);
            vertex1.setProperty("name", "vertexOut1");
            for (int i = 0; i < 1000; i++) {
                Vertex vertex2 = thunderGraph.addVertex(null);
                vertex2.setProperty("name", "vertexIn" + i);
                Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
                edge.setProperty("name", "edge1" + i);
            }
            thunderGraph.commit();

            int count = 0;
            Vertex v = thunderGraph.getVertex(0L);
            Iterator<Vertex> iterator = v.getVertices(Direction.OUT, "testLabel1").iterator();
            while (iterator.hasNext()) {
                count++;
                v = iterator.next();
                v.remove();
                if (count == 999) {
                    break;
                }
            }
            thunderGraph.commit();
            v = thunderGraph.getVertex(0L);
            Assert.assertEquals(1, count(v.getVertices(Direction.OUT, "testLabel1")));
            iterator = v.getVertices(Direction.OUT, "testLabel1").iterator();
            while (iterator.hasNext()) {
                v = iterator.next();
                v.remove();
            }
            Assert.assertEquals(0, count(v.getVertices(Direction.OUT, "testLabel1")));
            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void removeVertexFromIterWithLabelsTest4() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex vertex1 = thunderGraph.addVertex(null);
            vertex1.setProperty("name", "vertexOut1");
            for (int i = 0; i < 1000; i++) {
                Vertex vertex2 = thunderGraph.addVertex(null);
                vertex2.setProperty("name", "vertexIn" + i);
                Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
                edge.setProperty("name", "edge1" + i);
            }
            thunderGraph.commit();

            Vertex v = thunderGraph.getVertex(0L);
            Iterator<Vertex> iterator = v.getVertices(Direction.OUT, "testLabel1").iterator();
            //Remove the first out vertex
            Vertex firstOutVertex = thunderGraph.getVertex(1L);
            firstOutVertex.remove();
            while (iterator.hasNext()) {
                v = iterator.next();
                Assert.assertEquals(2L, v.getId());
                break;
            }

            while (iterator.hasNext()) {
                iterator.next();
                iterator.remove();
                break;
            }
            v = thunderGraph.getVertex(0L);
            Assert.assertEquals(998, count(v.getVertices(Direction.OUT, "testLabel1")));

            thunderGraph.commit();

            while (iterator.hasNext()) {
                iterator.next();
                iterator.remove();
            }
            v = thunderGraph.getVertex(0L);
            //one remains as we called next to assert 2L without removing it
            Assert.assertEquals(1, count(v.getVertices(Direction.OUT, "testLabel1")));
            Assert.assertEquals(2L, v.getVertices(Direction.OUT, "testLabel1").iterator().next().getId());
            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testInDirection() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {

            for (int i = 0; i < 10; i++) {
                Vertex v1 = thunderGraph.addVertex(null);
                v1.setProperty("name", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa " + i);
            }

            for (long i = 0; i < 10; i++) {
                Vertex v1 = thunderGraph.getVertex(i);
                for (long j = 0; j < 10; j++) {
                    if (j >= i) {
                        Vertex v2 = thunderGraph.getVertex(j);
                        thunderGraph.addEdge(null, v1, v2, "toSelf");
                        thunderGraph.addEdge(null, v1, v2, "toSelfAgain");
                    }
                }
            }
            Assert.assertEquals(10, count(thunderGraph.getVertices()));
            Assert.assertEquals(110, count(thunderGraph.getEdges()));
            thunderGraph.commit();

            Assert.assertEquals(20, count(thunderGraph.getVertex(0L).getEdges(Direction.OUT)));
            //This is one as the edge to itself is both a in and out
            Assert.assertEquals(2, count(thunderGraph.getVertex(0L).getEdges(Direction.IN)));
            Assert.assertEquals(4, count(thunderGraph.getVertex(1L).getEdges(Direction.IN)));
            Assert.assertEquals(6, count(thunderGraph.getVertex(2L).getEdges(Direction.IN)));
            Assert.assertEquals(8, count(thunderGraph.getVertex(3L).getEdges(Direction.IN)));
            Assert.assertEquals(10, count(thunderGraph.getVertex(4L).getEdges(Direction.IN)));
            Assert.assertEquals(12, count(thunderGraph.getVertex(5L).getEdges(Direction.IN)));
            Assert.assertEquals(14, count(thunderGraph.getVertex(6L).getEdges(Direction.IN)));
            Assert.assertEquals(16, count(thunderGraph.getVertex(7L).getEdges(Direction.IN)));
            Assert.assertEquals(18, count(thunderGraph.getVertex(8L).getEdges(Direction.IN)));
            Assert.assertEquals(20, count(thunderGraph.getVertex(9L).getEdges(Direction.IN)));

            Assert.assertEquals(10, count(thunderGraph.getVertex(0L).getEdges(Direction.OUT, "toSelf")));
            //This is one as the edge to itself is both a in and out
            Assert.assertEquals(1, count(thunderGraph.getVertex(0L).getEdges(Direction.IN, "toSelf")));
            Assert.assertEquals(2, count(thunderGraph.getVertex(1L).getEdges(Direction.IN, "toSelf")));
            Assert.assertEquals(3, count(thunderGraph.getVertex(2L).getEdges(Direction.IN, "toSelf")));
            Assert.assertEquals(4, count(thunderGraph.getVertex(3L).getEdges(Direction.IN, "toSelf")));
            Assert.assertEquals(5, count(thunderGraph.getVertex(4L).getEdges(Direction.IN, "toSelf")));
            Assert.assertEquals(6, count(thunderGraph.getVertex(5L).getEdges(Direction.IN, "toSelf")));
            Assert.assertEquals(7, count(thunderGraph.getVertex(6L).getEdges(Direction.IN, "toSelf")));
            Assert.assertEquals(8, count(thunderGraph.getVertex(7L).getEdges(Direction.IN, "toSelf")));
            Assert.assertEquals(9, count(thunderGraph.getVertex(8L).getEdges(Direction.IN, "toSelf")));
            Assert.assertEquals(10, count(thunderGraph.getVertex(9L).getEdges(Direction.IN, "toSelf")));

            Assert.assertEquals(10, count(thunderGraph.getVertex(0L).getEdges(Direction.OUT, "toSelfAgain")));
            //This is one as the edge to itself is both a in and out
            Assert.assertEquals(1, count(thunderGraph.getVertex(0L).getEdges(Direction.IN, "toSelfAgain")));
            Assert.assertEquals(2, count(thunderGraph.getVertex(1L).getEdges(Direction.IN, "toSelfAgain")));
            Assert.assertEquals(3, count(thunderGraph.getVertex(2L).getEdges(Direction.IN, "toSelfAgain")));
            Assert.assertEquals(4, count(thunderGraph.getVertex(3L).getEdges(Direction.IN, "toSelfAgain")));
            Assert.assertEquals(5, count(thunderGraph.getVertex(4L).getEdges(Direction.IN, "toSelfAgain")));
            Assert.assertEquals(6, count(thunderGraph.getVertex(5L).getEdges(Direction.IN, "toSelfAgain")));
            Assert.assertEquals(7, count(thunderGraph.getVertex(6L).getEdges(Direction.IN, "toSelfAgain")));
            Assert.assertEquals(8, count(thunderGraph.getVertex(7L).getEdges(Direction.IN, "toSelfAgain")));
            Assert.assertEquals(9, count(thunderGraph.getVertex(8L).getEdges(Direction.IN, "toSelfAgain")));
            Assert.assertEquals(10, count(thunderGraph.getVertex(9L).getEdges(Direction.IN, "toSelfAgain")));

        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testInDirectionTrivial() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {

            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

            Vertex v2 = thunderGraph.addVertex(null);
            v2.setProperty("name", "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");

            thunderGraph.addEdge(null, v1, v2, "testInEdge");

            Assert.assertEquals(1, count(thunderGraph.getVertex(0L).getEdges(Direction.OUT)));
            Assert.assertEquals(0, count(thunderGraph.getVertex(0L).getEdges(Direction.IN)));
            Assert.assertEquals(0, count(thunderGraph.getVertex(1L).getEdges(Direction.OUT)));
            Assert.assertEquals(1, count(thunderGraph.getVertex(1L).getEdges(Direction.IN)));

        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testInDirectionOnFirstAndNextIterCall() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("number", -1);
            for (int i = 0; i < 10000; i++) {
                Vertex v2 = thunderGraph.addVertex(null);
                v1.setProperty("number", i);
                thunderGraph.addEdge(null, v2, v1, "testIn");
            }

            Assert.assertEquals(10000, count(thunderGraph.getVertex(0L).getVertices(Direction.IN)));
            Assert.assertEquals(10000, count(thunderGraph.getVertex(0L).getVertices(Direction.IN, "testIn")));

            Iterator<Vertex> iter = thunderGraph.getVertex(0L).getVertices(Direction.IN, "testIn").iterator();
            Vertex v = iter.next();
            Assert.assertEquals(1L, v.getId());


            thunderGraph.commit();
            v = iter.next();
            Assert.assertEquals(2L, v.getId());

            iter = thunderGraph.getVertex(0L).getVertices(Direction.IN).iterator();
            v = iter.next();
            Assert.assertEquals(1L, v.getId());

            thunderGraph.commit();
            v = iter.next();
            Assert.assertEquals(2L, v.getId());

        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testEmptyLabels() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        StopWatch stopWatch = new StopWatch();
        stopWatch.start();
        try {
            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("number", -1);
            for (int i = 0; i < 1000; i++) {
                Vertex v2 = thunderGraph.addVertex(null);
                v1.setProperty("number", i);
                thunderGraph.addEdge(null, v2, v1, "test1");
                thunderGraph.addEdge(null, v2, v1, "test2");
            }

            Assert.assertEquals(2000, count(thunderGraph.getVertex(0L).getVertices(Direction.IN)));
            Assert.assertEquals(1000, count(thunderGraph.getVertex(0L).getVertices(Direction.IN, "test1")));
            Assert.assertEquals(1000, count(thunderGraph.getVertex(0L).getVertices(Direction.IN, "test2")));
            Assert.assertEquals(2000, count(thunderGraph.getVertex(0L).getVertices(Direction.IN, "test1", "test2")));

            thunderGraph.commit();

            for (Vertex v : thunderGraph.getVertex(0L).getVertices(Direction.IN, "test1")) {
                Assert.assertEquals(1, count(v.getEdges(Direction.OUT, "test1")));
                v.getEdges(Direction.OUT, "test1").iterator().next().remove();
            }
            Assert.assertEquals(1000, count(thunderGraph.getVertex(0L).getVertices(Direction.IN)));
            Assert.assertEquals(0, count(thunderGraph.getVertex(0L).getVertices(Direction.IN, "test1")));
            Assert.assertEquals(1000, count(thunderGraph.getVertex(0L).getVertices(Direction.IN, "test2")));
            Assert.assertEquals(1000, count(thunderGraph.getVertex(0L).getVertices(Direction.IN, "test1", "test2")));

        } finally {
            stopWatch.stop();
            System.out.println(stopWatch.toString());
            thunderGraph.shutdown();
        }
    }

}