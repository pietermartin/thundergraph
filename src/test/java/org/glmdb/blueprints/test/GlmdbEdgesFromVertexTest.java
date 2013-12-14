package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.junit.Assert;
import org.junit.Test;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Date: 2013/11/26
 * Time: 9:52 PM
 */
public class GlmdbEdgesFromVertexTest extends BaseGlmdbGraphTest {

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
        for (int i = 0; i < 10; i++) {
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
        while (iterator.hasNext()){
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
        while (iterator.hasNext()){
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
        for (int i = 0; i < 10; i++) {
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
        while (iterator.hasNext()){
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
        iterator = v.getEdges(Direction.OUT).iterator();
        while (iterator.hasNext()){
            iterator.next();
            iterator.remove();
        }
        thunderGraph.commit();

        Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getEdges(Direction.OUT, "testLabel1").iterator()));
        thunderGraph.commit();

        thunderGraph.shutdown();

    }

}