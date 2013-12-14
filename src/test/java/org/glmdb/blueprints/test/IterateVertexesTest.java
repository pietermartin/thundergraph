package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.junit.Assert;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

/**
 * Date: 2013/11/24
 * Time: 11:01 AM
 */
public class IterateVertexesTest extends BaseGlmdbGraphTest  {


    @Test
    public void testIterVertices() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        Vertex vertex1 = thunderGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 1000; i++) {
            Vertex vertex2 = thunderGraph.addVertex(null);
            vertex2.setProperty("name", "vertexIn" + i);
            Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            edge.setProperty("name", "edge" + i);
        }
        thunderGraph.commit();

        List<String> vertexName = new ArrayList<String>();
        int count = 0;
        Iterable<Vertex> iter = thunderGraph.getVertices();
        for (Vertex vertex : iter) {
            vertexName.add((String)vertex.getProperty("name"));
            count++;
        }
        Assert.assertEquals(1001, count);
        Assert.assertEquals("vertexOut1", vertexName.get(0));
        Assert.assertEquals("vertexIn0", vertexName.get(1));
        Assert.assertEquals("vertexIn1", vertexName.get(2));
        Assert.assertEquals("vertexIn2", vertexName.get(3));
        Assert.assertEquals("vertexIn999", vertexName.get(1000));

        thunderGraph.commit();
        thunderGraph.shutdown();
    }

    @Test
    public void testCursorReset() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        Vertex vertex1 = thunderGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 1000; i++) {
            Vertex vertex2 = thunderGraph.addVertex(null);
            vertex2.setProperty("name", "vertexIn" + i);
            Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            edge.setProperty("name", "edge" + i);
        }
        thunderGraph.commit();

        List<String> vertexName = new ArrayList<String>();
        int count = 0;
        Iterable<Vertex> iter = thunderGraph.getVertices();
        for (Vertex vertex : iter) {
            count++;
            if (count == 500) {
                break;
            }
        }

        count = 0;
        iter = thunderGraph.getVertices();
        for (Vertex vertex : iter) {
            vertexName.add((String)vertex.getProperty("name"));
            count++;
        }

        Assert.assertEquals(1001, count);
        Assert.assertEquals("vertexOut1", vertexName.get(0));
        Assert.assertEquals("vertexIn0", vertexName.get(1));
        Assert.assertEquals("vertexIn1", vertexName.get(2));
        Assert.assertEquals("vertexIn2", vertexName.get(3));
        Assert.assertEquals("vertexIn999", vertexName.get(1000));

        thunderGraph.commit();
        thunderGraph.shutdown();
    }

    @Test
    public void testIterVerticesForKeyValue() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        Vertex vertex1 = thunderGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 1000; i++) {
            Vertex vertex2 = thunderGraph.addVertex(null);
            if (i < 500) {
                vertex2.setProperty("name", "vertexIn1");
            } else {
                vertex2.setProperty("name", "vertexIn2");
            }
            Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            edge.setProperty("name", "edge" + i);
        }
        thunderGraph.commit();

        List<String> vertexName = new ArrayList<String>();
        int count = 0;
        Iterable<Vertex> iter = thunderGraph.getVertices("name", "vertexIn1");
        for (Vertex vertex : iter) {
            vertexName.add((String)vertex.getProperty("name"));
            count++;
        }
        Assert.assertEquals(500, count);
        Assert.assertEquals("vertexIn1", vertexName.get(0));
        Assert.assertEquals("vertexIn1", vertexName.get(1));
        Assert.assertEquals("vertexIn1", vertexName.get(499));

        thunderGraph.commit();
        thunderGraph.shutdown();
    }

}
