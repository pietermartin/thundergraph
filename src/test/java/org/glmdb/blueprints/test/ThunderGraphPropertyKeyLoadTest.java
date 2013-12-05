package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Vertex;
import junit.framework.Assert;
import org.glmdb.blueprints.GlmdbGraph;
import org.junit.Test;

/**
 * Date: 2013/12/05
 * Time: 7:44 AM
 */
public class ThunderGraphPropertyKeyLoadTest extends BaseGlmdbGraphTest {

    @Test
    public void testLoadPropertyKeyDb() {
        GlmdbGraph g = new GlmdbGraph(this.dbPath);
        Vertex one = g.addVertex(null);
        one.setProperty("one", "1");
        for (int i = 0; i < 10; i++) {
            Vertex many = g.addVertex(null);
            many.setProperty("many" + i, i);
            g.addEdge(null, one, many, "toMany");

        }
        g.commit();
        g.printVertexDb();

        g.shutdown();

        g = new GlmdbGraph(this.dbPath);
        Assert.assertEquals("1", g.getVertex(0L).getProperty("one"));
        g.printVertexDb();

        g.shutdown();

    }
}
