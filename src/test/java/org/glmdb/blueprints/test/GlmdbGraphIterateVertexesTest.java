package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.GlmdbGraph;
import org.junit.Assert;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

/**
 * Date: 2013/11/24
 * Time: 11:01 AM
 */
public class GlmdbGraphIterateVertexesTest extends BaseGlmdbGraphTest  {


    @Test
    public void testIterVertices() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 1000; i++) {
            Vertex vertex2 = glmdbGraph.addVertex(null);
            vertex2.setProperty("name", "vertexIn" + i);
            Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            edge.setProperty("name", "edge" + i);
        }
        glmdbGraph.commit();

        List<String> vertexName = new ArrayList<String>();
        int count = 0;
        Iterable<Vertex> iter = glmdbGraph.getVertices();
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

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testCursorReset() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 1000; i++) {
            Vertex vertex2 = glmdbGraph.addVertex(null);
            vertex2.setProperty("name", "vertexIn" + i);
            Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            edge.setProperty("name", "edge" + i);
        }
        glmdbGraph.commit();

        List<String> vertexName = new ArrayList<String>();
        int count = 0;
        Iterable<Vertex> iter = glmdbGraph.getVertices();
        for (Vertex vertex : iter) {
            count++;
            if (count == 500) {
                break;
            }
        }

        count = 0;
        iter = glmdbGraph.getVertices();
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

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

    @Test
    public void testIterVerticesForKeyValue() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 1000; i++) {
            Vertex vertex2 = glmdbGraph.addVertex(null);
            if (i < 500) {
                vertex2.setProperty("name", "vertexIn1");
            } else {
                vertex2.setProperty("name", "vertexIn2");
            }
            Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            edge.setProperty("name", "edge" + i);
        }
        glmdbGraph.commit();

        List<String> vertexName = new ArrayList<String>();
        int count = 0;
        Iterable<Vertex> iter = glmdbGraph.getVertices("name", "vertexIn1");
        for (Vertex vertex : iter) {
            vertexName.add((String)vertex.getProperty("name"));
            count++;
        }
        Assert.assertEquals(500, count);
        Assert.assertEquals("vertexIn1", vertexName.get(0));
        Assert.assertEquals("vertexIn1", vertexName.get(1));
        Assert.assertEquals("vertexIn1", vertexName.get(499));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

}
