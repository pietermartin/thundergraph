package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Vertex;
import junit.framework.Assert;
import org.glmdb.blueprints.ThunderGraph;
import org.junit.Test;

/**
 * Date: 2013/12/08
 * Time: 6:31 PM
 */
public class SequencesPersistTest extends BaseGlmdbGraphTest {

    @Test
    public void testSequencePersist() {
        ThunderGraph graph = new ThunderGraph(this.dbPath);
        Vertex v = graph.addVertex(null);
        v.setProperty("lala", "lala");
        graph.commit();

        graph.shutdown();

        graph = new ThunderGraph(this.dbPath);
        v = graph.addVertex(null);
        Assert.assertEquals(1L, v.getId());

        graph.shutdown();

    }
}
