package org.glmdb.blueprints.test.iter;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.test.BaseGlmdbGraphTest;
import org.junit.Assert;
import org.junit.Test;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Date: 2013/11/24
 * Time: 11:01 AM
 */
public class IterateEdgesTest extends BaseGlmdbGraphTest {


    @Test
    public void testAddEdge() {
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

        List<String> edgeName = new ArrayList<String>();
        List<String> vertexOutName = new ArrayList<String>();
        List<String> vertexInName = new ArrayList<String>();
        int count = 0;
        Iterable<Edge> iter = thunderGraph.getEdges();
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

        int count = 0;
        Iterable<Edge> iter = thunderGraph.getEdges();
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
        iter = thunderGraph.getEdges();
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

        thunderGraph.commit();
        thunderGraph.shutdown();
    }


    @Test
    public void testIterEdgesForKeyValue() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        Vertex vertex1 = thunderGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 1000; i++) {
            Vertex vertex2 = thunderGraph.addVertex(null);
            if (i < 500) {
                vertex2.setProperty("name", "vertexIn1");
                Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
                edge.setProperty("name", "edge1");
            } else {
                vertex2.setProperty("name", "vertexIn2");
                Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
                edge.setProperty("name", "edge2");
            }
        }
        thunderGraph.commit();

        List<String> edgeName = new ArrayList<String>();
        int count = 0;
        Iterable<Edge> iter = thunderGraph.getEdges("name", "edge1");
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
        iter = thunderGraph.getEdges("name", "edge2");
        for (Edge edge : iter) {
            edgeName.add((String)edge.getProperty("name"));
            count++;
        }
        Assert.assertEquals(500, count);
        Assert.assertEquals("edge2", edgeName.get(0));
        Assert.assertEquals("edge2", edgeName.get(1));
        Assert.assertEquals("edge2", edgeName.get(499));

        thunderGraph.commit();
        thunderGraph.shutdown();
    }

    //Remove must test on a significant number of edges. i.e. > 100.
    //Else they pass, something to do mdb page size me thinks
    @Test
    public void testRemove() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name", "name1");

            for (int i = 0; i < 1000; i++) {

                Vertex v2 = thunderGraph.addVertex(null);
                v2.setProperty("name", "name2");

                Edge e = thunderGraph.addEdge(null, v1, v2, "label1");
                e.setProperty("name", "name1");

            }

            thunderGraph.commit();

            Assert.assertEquals(1000, count(thunderGraph.getEdges()));
            Assert.assertEquals(1000, count(thunderGraph.getEdges("name", "name1")));

            Iterator<Edge> edgeIter = thunderGraph.getEdges().iterator();
            while (edgeIter.hasNext()) {

                Edge e = edgeIter.next();
                edgeIter.remove();

            }

        } finally {
            thunderGraph.shutdown();
        }
    }
}
