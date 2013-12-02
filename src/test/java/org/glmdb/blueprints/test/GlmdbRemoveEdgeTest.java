package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import junit.framework.Assert;
import org.glmdb.blueprints.GlmdbGraph;
import org.junit.Test;

/**
 * Date: 2013/11/30
 * Time: 6:58 PM
 */
public class GlmdbRemoveEdgeTest extends BaseGlmdbGraphTest {

    @Test
    public void removeEdgeTest() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        for (int i = 0; i < 5; i++) {
            Vertex vertex2 = glmdbGraph.addVertex(null);
            vertex2.setProperty("name0", "test0" + i);
            vertex1.addEdge("test", vertex2);
        }
        glmdbGraph.commit();

        glmdbGraph.printVertexDb();
        glmdbGraph.printEdgeDb();
        Assert.assertEquals(6, countVertices(glmdbGraph));
        Assert.assertEquals(5, countEdges(glmdbGraph));

        glmdbGraph.getEdge(4L).remove();
        glmdbGraph.commit();
        Assert.assertEquals(6, countVertices(glmdbGraph));
        Assert.assertEquals(4, countEdges(glmdbGraph));

        glmdbGraph.getEdge(3L).remove();
        glmdbGraph.commit();
        Assert.assertEquals(6, countVertices(glmdbGraph));
        Assert.assertEquals(3, countEdges(glmdbGraph));

        glmdbGraph.getEdge(2L).remove();
        glmdbGraph.commit();
        Assert.assertEquals(6, countVertices(glmdbGraph));
        Assert.assertEquals(2, countEdges(glmdbGraph));

        glmdbGraph.getEdge(1L).remove();
        glmdbGraph.commit();
        Assert.assertEquals(6, countVertices(glmdbGraph));
        Assert.assertEquals(1, countEdges(glmdbGraph));

        glmdbGraph.getEdge(0L).remove();
        glmdbGraph.commit();
        Assert.assertEquals(6, countVertices(glmdbGraph));
        Assert.assertEquals(0, countEdges(glmdbGraph));

        glmdbGraph.printVertexDb();
        glmdbGraph.printEdgeDb();

        glmdbGraph.shutdown();
    }

    private int countVertices(GlmdbGraph glmdbGraph) {
        int result = 0;
        for (Vertex v : glmdbGraph.getVertices()) {
            result++;
        }
        return result;
    }

    private int countEdges(GlmdbGraph glmdbGraph) {
        int result = 0;
        for (Edge e : glmdbGraph.getEdges()) {
            result++;
        }
        return result;
    }

}
