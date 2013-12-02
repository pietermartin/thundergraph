package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Vertex;
import junit.framework.Assert;
import org.glmdb.blueprints.GlmdbGraph;
import org.junit.Test;

/**
 * Date: 2013/11/30
 * Time: 6:58 PM
 */
public class GlmdbRemoveVertexTest  extends BaseGlmdbGraphTest {

    @Test
    public void removeVertexTest() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex1 = glmdbGraph.addVertex(null);
        for (int i = 0; i < 5; i++) {
            Vertex vertex2 = glmdbGraph.addVertex(null);
            vertex2.setProperty("name0", "test0" + i);
            vertex1.addEdge("test", vertex2);
        }
        glmdbGraph.commit();

        glmdbGraph.printVertexDb();

        Assert.assertEquals(6, countVertices(glmdbGraph));

        glmdbGraph.getVertex(5L).remove();
        glmdbGraph.commit();
        Assert.assertEquals(5, countVertices(glmdbGraph));

        glmdbGraph.getVertex(4L).remove();
        glmdbGraph.commit();
        Assert.assertEquals(4, countVertices(glmdbGraph));

        glmdbGraph.getVertex(3L).remove();
        glmdbGraph.commit();
        Assert.assertEquals(3, countVertices(glmdbGraph));

        glmdbGraph.getVertex(2L).remove();
        glmdbGraph.commit();
        Assert.assertEquals(2, countVertices(glmdbGraph));

        glmdbGraph.getVertex(1L).remove();
        glmdbGraph.commit();
        Assert.assertEquals(1, countVertices(glmdbGraph));

        glmdbGraph.getVertex(0L).remove();
        glmdbGraph.commit();

        glmdbGraph.printVertexDb();
        Assert.assertEquals(0, countVertices(glmdbGraph));

        glmdbGraph.shutdown();
    }

    private int countVertices(GlmdbGraph glmdbGraph) {
        int result = 0;
        for (Vertex v : glmdbGraph.getVertices()) {
            result++;
        }
        return result;
    }
}
