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
 * Date: 2013/11/26
 * Time: 9:52 PM
 */
public class GlmdbEdgesFromVertexTest extends BaseGlmdbGraphTest {

    @Test
    public void testEdgesFromVertices() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        vertex1.setProperty("name", "vertexOut1");
        for (int i = 0; i < 1000000; i++) {
            Vertex vertex2 = glmdbGraph.addVertex(null);
            vertex2.setProperty("name", "vertexIn1");
            Edge edge = glmdbGraph.addEdge(null, vertex1, vertex2, "testLabel1");
            edge.setProperty("name", "edge" + i);
        }
        glmdbGraph.commit();

//        glmdbGraph.printVertexDb();
        List<String> edgeName = new ArrayList<String>();
        int count = 0;
        Vertex vertex1_1 = glmdbGraph.getVertex(0L);
        for (Edge edge : vertex1_1.getEdges(Direction.BOTH, "testLabel1")) {
            edgeName.add((String) edge.getProperty("name"));
            count++;
        }
        Assert.assertEquals(1000000, count);
        Assert.assertEquals("edge0", edgeName.get(0));
        Assert.assertEquals("edge1", edgeName.get(1));
        Assert.assertEquals("edge499", edgeName.get(499));

        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }
}
