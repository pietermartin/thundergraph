package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.GlmdbGraph;
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
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 10; i++) {
            Vertex vertex2 = glmdbGraph.addVertex(null);
            vertex2.setProperty("name", "vertexIn" + i);
            Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            edge.setProperty("name", "edge" + i);
        }
        glmdbGraph.commit();

        List<String> edgeName = new ArrayList<String>();
        int count = 0;
        Vertex vertex1_1 = glmdbGraph.getVertex(0L);
        for (Edge edge : vertex1_1.getEdges(Direction.BOTH, "testLabel1")) {
            edgeName.add((String) edge.getProperty("name"));
            count++;
        }
        Assert.assertEquals(10, count);
        Assert.assertEquals("edge0", edgeName.get(0));
        Assert.assertEquals("edge1", edgeName.get(1));
        Assert.assertEquals("edge9", edgeName.get(9));

        glmdbGraph.commit();

        edgeName = new ArrayList<String>();
        count = 0;
        vertex1_1 = glmdbGraph.getVertex(0L);
        for (Edge edge : vertex1_1.getEdges(Direction.BOTH)) {
            edgeName.add((String) edge.getProperty("name"));
            count++;
        }
        Assert.assertEquals(10, count);
        Assert.assertEquals("edge0", edgeName.get(0));
        Assert.assertEquals("edge1", edgeName.get(1));
        Assert.assertEquals("edge9", edgeName.get(9));

        glmdbGraph.commit();



        Vertex vertex2_1 = glmdbGraph.getVertex(1L);
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

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }


    @Test
    public void testAllEdgesFromVertices() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 10; i++) {
            Vertex vertex2 = glmdbGraph.addVertex(null);
            vertex2.setProperty("name", "vertexIn1");
            Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            edge.setProperty("name", "edge1" + i);
        }
        for (int i = 0; i < 10; i++) {
            Vertex vertex2 = glmdbGraph.addVertex(null);
            vertex2.setProperty("name", "vertexIn1");
            Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel2");
            edge.setProperty("name", "edge2" + i);
        }
        glmdbGraph.commit();

        int count = 0;
        Vertex vertex1_1 = glmdbGraph.getVertex(0L);
        for (Edge edge : vertex1_1.getEdges(Direction.OUT)) {
            count++;
        }
        Assert.assertEquals(20, count);
        count = 0;
        vertex1_1 = glmdbGraph.getVertex(0L);
        for (Edge edge : vertex1_1.getEdges(Direction.OUT, "testLabel1")) {
            count++;
        }
        Assert.assertEquals(10, count);
        count = 0;
        vertex1_1 = glmdbGraph.getVertex(0L);
        for (Edge edge : vertex1_1.getEdges(Direction.OUT, "testLabel2")) {
            count++;
        }
        Assert.assertEquals(10, count);
        glmdbGraph.commit();
        glmdbGraph.shutdown();

    }

    @Test
    public void removeEdgefromIterTest() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 10; i++) {
            Vertex vertex2 = glmdbGraph.addVertex(null);
            vertex2.setProperty("name", "vertexIn1");
            Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            edge.setProperty("name", "edge1" + i);
        }
        glmdbGraph.commit();
        Assert.assertEquals(1, countIter(glmdbGraph.getVertex(5L).getEdges(Direction.IN, "testLabel1").iterator()));
        glmdbGraph.commit();

        glmdbGraph.printVertexDb();

        int count = 0;
        Vertex v = glmdbGraph.getVertex(0L);
        Iterator<Edge> iterator = v.getEdges(Direction.OUT, "testLabel1").iterator();
        while (iterator.hasNext()){
            Edge edge = iterator.next();
            count++;
            if (count == 5) {
                iterator.remove();
            }
        }
        glmdbGraph.commit();
        Assert.assertEquals(0, countIter(glmdbGraph.getVertex(5L).getEdges(Direction.IN, "testLabel1").iterator()));
        glmdbGraph.commit();

        v = glmdbGraph.getVertex(0L);
        iterator = v.getEdges(Direction.OUT, "testLabel1").iterator();
        while (iterator.hasNext()){
            iterator.next();
            iterator.remove();
        }
        glmdbGraph.commit();

        Assert.assertEquals(0, countIter(glmdbGraph.getVertex(0L).getEdges(Direction.OUT, "testLabel1").iterator()));
        glmdbGraph.commit();

        glmdbGraph.printVertexDb();
        glmdbGraph.shutdown();

    }

    @Test
    public void removeEdgefromIterWithoutLabelTest() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 10; i++) {
            Vertex vertex2 = glmdbGraph.addVertex(null);
            vertex2.setProperty("name", "vertexIn1");
            Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            edge.setProperty("name", "edge1" + i);
        }
        glmdbGraph.commit();
        Assert.assertEquals(1, countIter(glmdbGraph.getVertex(5L).getEdges(Direction.IN, "testLabel1").iterator()));
        glmdbGraph.commit();

        glmdbGraph.printVertexDb();

        int count = 0;
        Vertex v = glmdbGraph.getVertex(0L);
        Iterator<Edge> iterator = v.getEdges(Direction.OUT).iterator();
        while (iterator.hasNext()){
            Edge edge = iterator.next();
            count++;
            if (count == 5) {
                iterator.remove();
            }
        }
        glmdbGraph.commit();
        Assert.assertEquals(0, countIter(glmdbGraph.getVertex(5L).getEdges(Direction.IN, "testLabel1").iterator()));
        glmdbGraph.commit();

        v = glmdbGraph.getVertex(0L);
        iterator = v.getEdges(Direction.OUT).iterator();
        while (iterator.hasNext()){
            iterator.next();
            iterator.remove();
        }
        glmdbGraph.commit();

        Assert.assertEquals(0, countIter(glmdbGraph.getVertex(0L).getEdges(Direction.OUT, "testLabel1").iterator()));
        glmdbGraph.commit();

        glmdbGraph.printVertexDb();
        glmdbGraph.shutdown();

    }

    private int countIter(Iterator iter) {
        int count = 0;
        while (iter.hasNext()) {
            count++;
            iter.next();
        }
        return count;
    }

}