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
public class GlmdbVertexesFromVertexTest extends BaseGlmdbGraphTest {

    @Test
    public void testVerticesFromVertices() {
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

        thunderGraph.printVertexDb();

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

        thunderGraph.shutdown();
    }


    @Test
    public void testVerticesFromVerticesMultipleLabels() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
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

        int count = 0;
        Vertex vertex1_1 = thunderGraph.getVertex(0L);
        for (Edge edge : vertex1_1.getEdges(Direction.OUT, "testLabel20")) {
            count++;
        }
        Assert.assertEquals(20, count);
        thunderGraph.commit();

        count = 0;
        vertex1_1 = thunderGraph.getVertex(0L);
        for (Edge edge : vertex1_1.getEdges(Direction.OUT, "testLabel40")) {
            count++;
        }
        Assert.assertEquals(20, count);
        thunderGraph.commit();

        count = 0;
        vertex1_1 = thunderGraph.getVertex(0L);
        for (Edge edge : vertex1_1.getEdges(Direction.OUT, "testLabel60")) {
            count++;
        }
        Assert.assertEquals(20, count);
        thunderGraph.commit();

        count = 0;
        vertex1_1 = thunderGraph.getVertex(0L);
        for (Edge edge : vertex1_1.getEdges(Direction.OUT, "testLabel80")) {
            count++;
        }
        Assert.assertEquals(20, count);
        thunderGraph.commit();

        count = 0;
        vertex1_1 = thunderGraph.getVertex(0L);
        for (Edge edge : vertex1_1.getEdges(Direction.OUT, "testLabel100")) {
            count++;
        }
        Assert.assertEquals(20, count);
        thunderGraph.commit();

        count = 0;
        vertex1_1 = thunderGraph.getVertex(0L);
        for (Edge edge : vertex1_1.getEdges(Direction.OUT)) {
            count++;
        }
        Assert.assertEquals(100, count);
        thunderGraph.commit();

        thunderGraph.shutdown();
    }

    @Test
    public void removeVertexfromIterTest() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        Vertex vertex1 = thunderGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 10; i++) {
            Vertex vertex2 = thunderGraph.addVertex(null);
            vertex2.setProperty("name", "vertexIn" + i);
            Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            edge.setProperty("name", "edge1" + i);
        }
        thunderGraph.commit();
        Assert.assertEquals(1, countIter(thunderGraph.getVertex(5L).getEdges(Direction.IN, "testLabel1").iterator()));
        thunderGraph.commit();

//        thunderGraph.printVertexDb();

        int count = 0;
        Vertex v = thunderGraph.getVertex(0L);
        Iterator<Vertex> iterator = v.getVertices(Direction.OUT, "testLabel1").iterator();
        while (iterator.hasNext()){
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
        while (iterator.hasNext()){
            Vertex vertex = iterator.next();
            System.out.println(vertex.getProperty("name"));
            iterator.remove();
        }
        thunderGraph.commit();

        Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getVertices(Direction.OUT, "testLabel1").iterator()));
        Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getEdges(Direction.OUT, "testLabel1").iterator()));
        thunderGraph.commit();

        thunderGraph.printVertexDb();
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

        thunderGraph.printVertexDb();

        int count = 0;
        Vertex v = thunderGraph.getVertex(0L);
        Iterator<Vertex> iterator = v.getVertices(Direction.OUT).iterator();
        while (iterator.hasNext()){
            Vertex vertex = iterator.next();
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
        while (iterator.hasNext()){
            iterator.next();
            iterator.remove();
        }
        thunderGraph.commit();

        Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getEdges(Direction.OUT, "testLabel1").iterator()));
        thunderGraph.commit();

        thunderGraph.printVertexDb();
        thunderGraph.shutdown();

    }

}