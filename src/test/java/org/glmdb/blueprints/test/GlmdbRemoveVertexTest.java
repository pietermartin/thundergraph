package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Vertex;
import junit.framework.Assert;
import org.glmdb.blueprints.ThunderGraph;
import org.junit.Test;

/**
 * Date: 2013/11/30
 * Time: 6:58 PM
 */
public class GlmdbRemoveVertexTest  extends BaseGlmdbGraphTest {

    @Test
    public void removeVertexTest() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        Vertex vertex1 = thunderGraph.addVertex(null);
        for (int i = 0; i < 5; i++) {
            Vertex vertex2 = thunderGraph.addVertex(null);
            vertex2.setProperty("name0", "test0" + i);
            vertex1.addEdge("test", vertex2);
        }
        thunderGraph.commit();

        thunderGraph.printVertexDb();

        Assert.assertEquals(6, countVertices(thunderGraph));

        thunderGraph.getVertex(5L).remove();
        thunderGraph.commit();
        Assert.assertEquals(5, countVertices(thunderGraph));

        thunderGraph.getVertex(4L).remove();
        thunderGraph.commit();
        Assert.assertEquals(4, countVertices(thunderGraph));

        thunderGraph.getVertex(3L).remove();
        thunderGraph.commit();
        Assert.assertEquals(3, countVertices(thunderGraph));

        thunderGraph.getVertex(2L).remove();
        thunderGraph.commit();
        Assert.assertEquals(2, countVertices(thunderGraph));

        thunderGraph.getVertex(1L).remove();
        thunderGraph.commit();
        Assert.assertEquals(1, countVertices(thunderGraph));

        thunderGraph.getVertex(0L).remove();
        thunderGraph.commit();

        thunderGraph.printVertexDb();
        Assert.assertEquals(0, countVertices(thunderGraph));

        thunderGraph.shutdown();
    }

    private int countVertices(ThunderGraph thunderGraph) {
        int result = 0;
        for (Vertex v : thunderGraph.getVertices()) {
            result++;
        }
        return result;
    }
}
