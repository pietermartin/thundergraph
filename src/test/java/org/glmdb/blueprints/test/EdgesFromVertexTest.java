package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.apache.commons.lang.time.StopWatch;
import org.glmdb.blueprints.ThunderGraph;
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
//This class is responsible to test 100% code coverage of EdgesFromVertexIterable
public class EdgesFromVertexTest extends BaseGlmdbGraphTest {

    @Test
    public void testEdgesFromVertices() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
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
        Assert.assertEquals("edge0", edgeName.get(0));
        Assert.assertEquals("edge1", edgeName.get(1));
        Assert.assertEquals("edge9", edgeName.get(9));

        thunderGraph.commit();

        edgeName = new ArrayList<String>();
        count = 0;
        vertex1_1 = thunderGraph.getVertex(0L);
        for (Edge edge : vertex1_1.getEdges(Direction.BOTH)) {
            edgeName.add((String) edge.getProperty("name"));
            count++;
        }
        Assert.assertEquals(10, count);
        Assert.assertEquals("edge0", edgeName.get(0));
        Assert.assertEquals("edge1", edgeName.get(1));
        Assert.assertEquals("edge9", edgeName.get(9));

        thunderGraph.commit();


        Vertex vertex2_1 = thunderGraph.getVertex(1L);
        Assert.assertTrue(!vertex2_1.getEdges(Direction.OUT, "testLabel1").iterator().hasNext());
        Assert.assertTrue(vertex2_1.getEdges(Direction.IN, "testLabel1").iterator().hasNext());

        count = 0;
        edgeName.clear();
        for (Edge edge : vertex2_1.getEdges(Direction.IN, "testLabel1")) {
            edgeName.add((String) edge.getProperty("name"));
            Vertex vIn = edge.getVertex(Direction.IN);
            Assert.assertEquals("vertexIn0", vIn.getProperty("name"));
            Vertex vOut = edge.getVertex(Direction.OUT);
            Assert.assertEquals("vertexOut1", vOut.getProperty("name"));
            count++;
        }
        Assert.assertEquals(1, count);
        Assert.assertEquals("edge0", edgeName.get(0));

        thunderGraph.commit();
        thunderGraph.shutdown();
    }


    @Test
    public void testAllEdgesFromVertices() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        Vertex vertex1 = thunderGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 10; i++) {
            Vertex vertex2 = thunderGraph.addVertex(null);
            vertex2.setProperty("name", "vertexIn1");
            Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            edge.setProperty("name", "edge1" + i);
        }
        for (int i = 0; i < 10; i++) {
            Vertex vertex2 = thunderGraph.addVertex(null);
            vertex2.setProperty("name", "vertexIn1");
            Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel2");
            edge.setProperty("name", "edge2" + i);
        }
        thunderGraph.commit();

        int count = 0;
        Vertex vertex1_1 = thunderGraph.getVertex(0L);
        for (Edge ignored : vertex1_1.getEdges(Direction.OUT)) {
            count++;
        }
        Assert.assertEquals(20, count);
        count = 0;
        vertex1_1 = thunderGraph.getVertex(0L);
        for (Edge ignored : vertex1_1.getEdges(Direction.OUT, "testLabel1")) {
            count++;
        }
        Assert.assertEquals(10, count);
        count = 0;
        vertex1_1 = thunderGraph.getVertex(0L);
        for (Edge ignored : vertex1_1.getEdges(Direction.OUT, "testLabel2")) {
            count++;
        }
        Assert.assertEquals(10, count);
        thunderGraph.commit();
        thunderGraph.shutdown();

    }

    @Test
    public void removeEdgefromIterTest() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        Vertex vertex1 = thunderGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 100; i++) {
            Vertex vertex2 = thunderGraph.addVertex(null);
            vertex2.setProperty("name", "vertexIn1");
            Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            edge.setProperty("name", "edge1" + i);
        }
        thunderGraph.commit();
        Assert.assertEquals(1, countIter(thunderGraph.getVertex(5L).getEdges(Direction.IN, "testLabel1").iterator()));
        thunderGraph.commit();

        int count = 0;
        Vertex v = thunderGraph.getVertex(0L);
        Iterator<Edge> iterator = v.getEdges(Direction.OUT, "testLabel1").iterator();
        while (iterator.hasNext()) {
            iterator.next();
            count++;
            if (count == 5) {
                iterator.remove();
            }
        }
        thunderGraph.commit();
        Assert.assertEquals(0, countIter(thunderGraph.getVertex(5L).getEdges(Direction.IN, "testLabel1").iterator()));
        thunderGraph.commit();

        v = thunderGraph.getVertex(0L);
        iterator = v.getEdges(Direction.OUT, "testLabel1").iterator();
        while (iterator.hasNext()) {
            iterator.next();
            iterator.remove();
        }
        thunderGraph.commit();

        Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getEdges(Direction.OUT, "testLabel1").iterator()));
        thunderGraph.commit();

        thunderGraph.shutdown();

    }

    @Test
    public void removeEdgefromIterWithoutLabelTest() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        Vertex vertex1 = thunderGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 100; i++) {
            Vertex vertex2 = thunderGraph.addVertex(null);
            vertex2.setProperty("name", "vertexIn1");
            Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            edge.setProperty("name", "edge1" + i);
        }
        thunderGraph.commit();
        Assert.assertEquals(1, countIter(thunderGraph.getVertex(5L).getEdges(Direction.IN, "testLabel1").iterator()));
        thunderGraph.commit();

        int count = 0;
        Vertex v = thunderGraph.getVertex(0L);
        Iterator<Edge> iterator = v.getEdges(Direction.OUT).iterator();
        Assert.assertEquals(100, count(iterator));
        iterator = v.getEdges(Direction.OUT).iterator();
        while (iterator.hasNext()) {
            iterator.next();
            count++;
            if (count == 5) {
                iterator.remove();
            }
        }
        thunderGraph.commit();
        Assert.assertEquals(0, countIter(thunderGraph.getVertex(5L).getEdges(Direction.IN).iterator()));
        thunderGraph.commit();

        v = thunderGraph.getVertex(0L);
        iterator = v.getEdges(Direction.OUT).iterator();
        while (iterator.hasNext()) {
            iterator.next();
            iterator.remove();
        }
        thunderGraph.commit();

        Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getEdges(Direction.OUT).iterator()));
        thunderGraph.commit();

        thunderGraph.shutdown();

    }

    @Test
    public void removeEdgefromIterWithoutLabelTest1() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        Vertex vertex1 = thunderGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 1000; i++) {
            Vertex vertex2 = thunderGraph.addVertex(null);
            vertex2.setProperty("name", "vertexIn1");
            Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            edge.setProperty("name", "edge1" + i);
        }
        thunderGraph.commit();

        int count = 0;
        Vertex v = thunderGraph.getVertex(0L);
        Iterator<Edge> iterator = v.getEdges(Direction.OUT).iterator();
        while (iterator.hasNext()) {
            Edge edge = iterator.next();
            count++;
            if (count == 5) {
                iterator.remove();
            }
        }
        thunderGraph.commit();
        Assert.assertNull(thunderGraph.getEdge(4L));
        thunderGraph.commit();

        v = thunderGraph.getVertex(0L);
        iterator = v.getEdges(Direction.OUT).iterator();
        while (iterator.hasNext()) {
            iterator.next();
            iterator.remove();
        }
        thunderGraph.commit();

        Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getEdges(Direction.OUT, "testLabel1").iterator()));
        thunderGraph.commit();
        thunderGraph.shutdown();

    }

    @Test
    public void removeEdgeFromIterWithoutLabelTest2() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        Vertex vertex1 = thunderGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 1000; i++) {
            Vertex vertex2 = thunderGraph.addVertex(null);
            vertex2.setProperty("name", "vertexIn1");
            Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            edge.setProperty("name", "edge1" + i);
        }
        thunderGraph.commit();

        int count = 0;
        Vertex v = thunderGraph.getVertex(0L);
        Iterator<Edge> iterator = v.getEdges(Direction.OUT).iterator();
        while (iterator.hasNext()) {
            iterator.next();
            count++;
            if (count == 5) {
                iterator.remove();
            }
        }
        thunderGraph.commit();
        Assert.assertNull(thunderGraph.getEdge(4L));
        thunderGraph.commit();

        v = thunderGraph.getVertex(0L);
        iterator = v.getEdges(Direction.OUT).iterator();
        while (iterator.hasNext()) {
            iterator.next();
            iterator.remove();
        }
        thunderGraph.commit();

        Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getEdges(Direction.OUT).iterator()));
        thunderGraph.commit();
        thunderGraph.shutdown();

    }

    @Test
    public void removeEdgeFromIterTest1() {
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
            Iterator<Edge> iterator = v.getEdges(Direction.OUT).iterator();
            while (iterator.hasNext()) {
                iterator.next();
                count++;
                if (count == 5) {
                    iterator.remove();
                }
            }
            thunderGraph.commit();
            Assert.assertNotNull(thunderGraph.getVertex(5L));
            Assert.assertNull(thunderGraph.getEdge(4L));
            thunderGraph.commit();

            v = thunderGraph.getVertex(0L);
            iterator = v.getEdges(Direction.OUT).iterator();
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
    public void removeEdgeFromIterTest2() {
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
            Iterator<Edge> iterator = v.getEdges(Direction.OUT).iterator();
            while (iterator.hasNext()) {
                Edge e = iterator.next();
                count++;
                if (count == 5) {
                    e.remove();
                }
            }
            thunderGraph.commit();
            Assert.assertNotNull(thunderGraph.getVertex(5L));
            Assert.assertNull(thunderGraph.getEdge(4L));
            thunderGraph.commit();

            v = thunderGraph.getVertex(0L);
            iterator = v.getEdges(Direction.OUT).iterator();
            while (iterator.hasNext()) {
                Edge e = iterator.next();
                e.remove();
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
    public void removeEdgeFromIterTest3() {
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
            Iterator<Edge> iterator = v.getEdges(Direction.OUT).iterator();
            while (iterator.hasNext()) {
                count++;
                Edge e = iterator.next();
                e.remove();
                if (count == 999) {
                    break;
                }
            }
            thunderGraph.commit();
            v = thunderGraph.getVertex(0L);
            Assert.assertEquals(1, count(v.getVertices(Direction.OUT)));
            iterator = v.getEdges(Direction.OUT).iterator();
            while (iterator.hasNext()) {
                Edge e = iterator.next();
                e.remove();
            }
            Assert.assertEquals(0, count(v.getVertices(Direction.OUT)));
            Assert.assertEquals(0, count(v.getEdges(Direction.OUT)));
            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void removeEdgeFromIterTest4() {
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
            Iterator<Edge> iterator = v.getEdges(Direction.OUT).iterator();
            //Remove the first out edge
            Edge firstOutEdge = thunderGraph.getEdge(0L);
            firstOutEdge.remove();
            while (iterator.hasNext()) {
                Edge e = iterator.next();
                Assert.assertEquals(1L, e.getId());
                break;
            }

            while (iterator.hasNext()) {
                iterator.next();
                iterator.remove();
                break;
            }
            v = thunderGraph.getVertex(0L);
            Assert.assertEquals(998, count(v.getEdges(Direction.OUT)));

            thunderGraph.commit();

            while (iterator.hasNext()) {
                iterator.next();
                iterator.remove();
            }
            v = thunderGraph.getVertex(0L);
            //one remains as we called next to assert 2L without removing it
            Assert.assertEquals(1, count(v.getEdges(Direction.OUT)));
            Assert.assertEquals(1L, v.getEdges(Direction.OUT).iterator().next().getId());
            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }
    }


    @Test
    public void removeEdgeFromIterWithLabelsTest1() {
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
            Iterator<Edge> iterator = v.getEdges(Direction.OUT, "testLabel1").iterator();
            while (iterator.hasNext()) {
                iterator.next();
                count++;
                if (count == 5) {
                    iterator.remove();
                }
            }
            thunderGraph.commit();
            Assert.assertNotNull(thunderGraph.getVertex(5L));
            Assert.assertNull(thunderGraph.getEdge(4L));
            thunderGraph.commit();

            v = thunderGraph.getVertex(0L);
            iterator = v.getEdges(Direction.OUT, "testLabel1").iterator();
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
    public void removeEdgeFromIterWithLabelsTest2() {
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
            Iterator<Edge> iterator = v.getEdges(Direction.OUT, "testLabel1").iterator();
            while (iterator.hasNext()) {
                Edge e = iterator.next();
                count++;
                if (count == 5) {
                    e.remove();
                }
            }
            thunderGraph.commit();
            Assert.assertNotNull(thunderGraph.getVertex(5L));
            Assert.assertNull(thunderGraph.getEdge(4L));
            thunderGraph.commit();

            v = thunderGraph.getVertex(0L);
            iterator = v.getEdges(Direction.OUT, "testLabel1").iterator();
            while (iterator.hasNext()) {
                Edge e = iterator.next();
                e.remove();
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
    public void removeEdgeFromIterWithLabelsTest3() {
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
            Iterator<Edge> iterator = v.getEdges(Direction.OUT, "testLabel1").iterator();
            while (iterator.hasNext()) {
                count++;
                Edge e = iterator.next();
                e.remove();
                if (count == 999) {
                    break;
                }
            }
            thunderGraph.commit();
            v = thunderGraph.getVertex(0L);
            Assert.assertEquals(1, count(v.getEdges(Direction.OUT, "testLabel1")));
            iterator = v.getEdges(Direction.OUT, "testLabel1").iterator();
            while (iterator.hasNext()) {
                Edge e = iterator.next();
                e.remove();
            }
            Assert.assertEquals(0, count(v.getVertices(Direction.OUT, "testLabel1")));
            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void removeEdgeFromIterWithLabelsTest4() {
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
            Iterator<Edge> iterator = v.getEdges(Direction.OUT, "testLabel1").iterator();
            //Remove the first out vertex
            Vertex firstOutVertex = thunderGraph.getVertex(1L);
            firstOutVertex.remove();
            while (iterator.hasNext()) {
                Edge e = iterator.next();
                Assert.assertEquals(1L, e.getId());
                break;
            }

            while (iterator.hasNext()) {
                iterator.next();
                iterator.remove();
                break;
            }
            v = thunderGraph.getVertex(0L);
            Assert.assertEquals(998, count(v.getEdges(Direction.OUT, "testLabel1")));

            thunderGraph.commit();

            while (iterator.hasNext()) {
                iterator.next();
                iterator.remove();
            }
            v = thunderGraph.getVertex(0L);
            //one remains as we called next to assert 2L without removing it
            Assert.assertEquals(1, count(v.getEdges(Direction.OUT, "testLabel1")));
            Assert.assertEquals(1L, v.getEdges(Direction.OUT, "testLabel1").iterator().next().getId());
            thunderGraph.commit();
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

            Assert.assertEquals(10000, count(thunderGraph.getVertex(0L).getEdges(Direction.IN)));
            Assert.assertEquals(10000, count(thunderGraph.getVertex(0L).getEdges(Direction.IN, "testIn")));

            Iterator<Edge> iter = thunderGraph.getVertex(0L).getEdges(Direction.IN, "testIn").iterator();
            iter.next();

            thunderGraph.commit();
            Edge e = iter.next();
            Assert.assertEquals(1L, e.getId());

            iter = thunderGraph.getVertex(0L).getEdges(Direction.IN).iterator();
            iter.next();

            thunderGraph.commit();
            e = iter.next();
            Assert.assertEquals(1L, e.getId());

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

            Assert.assertEquals(2000, count(thunderGraph.getVertex(0L).getEdges(Direction.IN)));
            Assert.assertEquals(1000, count(thunderGraph.getVertex(0L).getEdges(Direction.IN, "test1")));
            Assert.assertEquals(1000, count(thunderGraph.getVertex(0L).getEdges(Direction.IN, "test2")));
            Assert.assertEquals(2000, count(thunderGraph.getVertex(0L).getEdges(Direction.IN, "test1", "test2")));

            thunderGraph.commit();

            for (Vertex v : thunderGraph.getVertex(0L).getVertices(Direction.IN, "test1")) {
                Assert.assertEquals(1, count(v.getEdges(Direction.OUT, "test1")));
                v.getEdges(Direction.OUT, "test1").iterator().next().remove();
            }
            Assert.assertEquals(1000, count(thunderGraph.getVertex(0L).getEdges(Direction.IN)));
            Assert.assertEquals(0, count(thunderGraph.getVertex(0L).getEdges(Direction.IN, "test1")));
            Assert.assertEquals(1000, count(thunderGraph.getVertex(0L).getEdges(Direction.IN, "test2")));
            Assert.assertEquals(1000, count(thunderGraph.getVertex(0L).getEdges(Direction.IN, "test1", "test2")));

        } finally {
            stopWatch.stop();
            System.out.println(stopWatch.toString());
            thunderGraph.shutdown();
        }
    }

    @Test
    public void removeEdgeFromIterTestDirectionBoth() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex vertex1 = thunderGraph.addVertex(null);
            vertex1.setProperty("name", "vertexOut1");
            for (int i = 0; i < (102); i++) {
                Vertex vertex2 = thunderGraph.addVertex(null);
                vertex2.setProperty("name", "vertexInaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" + i);
                Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
                edge.setProperty("name", "edge1aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" + i);
            }
            Vertex v = thunderGraph.getVertex(0L);
            for (Edge e : v.getEdges(Direction.BOTH)) {
                e.remove();
            }
            thunderGraph.printDb(DbEnum.VERTEX_DB);
            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }

    }

}