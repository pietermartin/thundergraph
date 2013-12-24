package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.junit.Assert;
import org.junit.Test;

import java.util.Iterator;

/**
 * Date: 2013/12/24
 * Time: 2:40 PM
 */
public class VertexIterTest extends BaseGlmdbGraphTest {

    @Test
    public void removeVertexFromIterTest() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
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
        Iterator<Vertex> iterator = thunderGraph.getVertices().iterator();
        while (iterator.hasNext()){
            iterator.next();
            count++;
            if (count == 5) {
                iterator.remove();
            }
        }
        thunderGraph.commit();
        Assert.assertNull(thunderGraph.getVertex(5L));
        Assert.assertEquals(999, count(thunderGraph.getVertices()));
        thunderGraph.commit();

        iterator = thunderGraph.getVertices().iterator();
        while (iterator.hasNext()){
            iterator.next();
            iterator.remove();
        }
        thunderGraph.commit();

        Assert.assertEquals(0, countIter(thunderGraph.getVertices().iterator()));
        Assert.assertEquals(0, countIter(thunderGraph.getEdges().iterator()));
        thunderGraph.commit();

        thunderGraph.shutdown();

    }

    @Test
    public void removeVertexFromIterTest3() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
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
        iterator = v.getVertices(Direction.OUT).iterator();
        while (iterator.hasNext()){
            iterator.next();
            iterator.remove();
        }
        thunderGraph.commit();

        Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getVertices(Direction.OUT).iterator()));
        Assert.assertEquals(0, countIter(thunderGraph.getVertex(0L).getEdges(Direction.OUT).iterator()));
        thunderGraph.commit();

        thunderGraph.shutdown();

    }

}
