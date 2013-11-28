package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Direction;
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
public class GlmdbGraphIterateEdgesTest extends BaseGlmdbGraphTest  {


    @Test
    public void testAddEdge() {
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

        List<String> edgeName = new ArrayList<String>();
        List<String> vertexOutName = new ArrayList<String>();
        List<String> vertexInName = new ArrayList<String>();
        int count = 0;
        Iterable<Edge> iter = glmdbGraph.getEdges();
        for (Edge edge : iter) {
            if (count % 100 == 0) {
                edgeName.add((String)edge.getProperty("name"));
                vertexOutName.add((String)edge.getVertex(Direction.OUT).getProperty("name"));
                vertexInName.add((String)edge.getVertex(Direction.IN).getProperty("name"));
            }
            count++;
        }
        Assert.assertEquals(1000, count);
        Assert.assertEquals("edge0", edgeName.get(0));
        Assert.assertEquals("edge900", edgeName.get(9));
        Assert.assertEquals("vertexOut1", vertexOutName.get(0));
        Assert.assertEquals("vertexOut1", vertexOutName.get(9));
        Assert.assertEquals("vertexIn0", vertexInName.get(0));
        Assert.assertEquals("vertexIn900", vertexInName.get(9));

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

        int count = 0;
        Iterable<Edge> iter = glmdbGraph.getEdges();
        for (Edge edge : iter) {
            if (count == 500) {
                break;
            }
            count++;
        }

        count = 0;
        List<String> edgeName = new ArrayList<String>();
        List<String> vertexOutName = new ArrayList<String>();
        List<String> vertexInName = new ArrayList<String>();
        iter = glmdbGraph.getEdges();
        for (Edge edge : iter) {
            if (count % 100 == 0) {
                edgeName.add((String)edge.getProperty("name"));
                vertexOutName.add((String)edge.getVertex(Direction.OUT).getProperty("name"));
                vertexInName.add((String)edge.getVertex(Direction.IN).getProperty("name"));
            }
            count++;
        }
        Assert.assertEquals(1000, count);
        Assert.assertEquals("edge0", edgeName.get(0));
        Assert.assertEquals("edge900", edgeName.get(9));
        Assert.assertEquals("vertexOut1", vertexOutName.get(0));
        Assert.assertEquals("vertexOut1", vertexOutName.get(9));
        Assert.assertEquals("vertexIn0", vertexInName.get(0));
        Assert.assertEquals("vertexIn900", vertexInName.get(9));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }


    @Test
    public void testIterEdgesForKeyValue() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 1000; i++) {
            Vertex vertex2 = glmdbGraph.addVertex(null);
            if (i < 500) {
                vertex2.setProperty("name", "vertexIn1");
                Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
                edge.setProperty("name", "edge1");
            } else {
                vertex2.setProperty("name", "vertexIn2");
                Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
                edge.setProperty("name", "edge2");
            }
        }
        glmdbGraph.commit();

        List<String> edgeName = new ArrayList<String>();
        int count = 0;
        Iterable<Edge> iter = glmdbGraph.getEdges("name", "edge1");
        for (Edge edge : iter) {
            edgeName.add((String)edge.getProperty("name"));
            count++;
        }
        Assert.assertEquals(500, count);
        Assert.assertEquals("edge1", edgeName.get(0));
        Assert.assertEquals("edge1", edgeName.get(1));
        Assert.assertEquals("edge1", edgeName.get(499));

        edgeName.clear();
        count = 0;
        iter = glmdbGraph.getEdges("name", "edge2");
        for (Edge edge : iter) {
            edgeName.add((String)edge.getProperty("name"));
            count++;
        }
        Assert.assertEquals(500, count);
        Assert.assertEquals("edge2", edgeName.get(0));
        Assert.assertEquals("edge2", edgeName.get(1));
        Assert.assertEquals("edge2", edgeName.get(499));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }
}
