package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.junit.Assert;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static com.tinkerpop.blueprints.Direction.BOTH;

/**
 * Date: 2013/12/07
 * Time: 8:57 PM
 */
public class ThunderGraphTestBothEdges extends BaseGlmdbGraphTest {

    @Test
    public void test() {
        ThunderGraph graph = new ThunderGraph(this.dbPath);
        Vertex a = graph.addVertex(null);
        Vertex b = graph.addVertex(null);
        Vertex c = graph.addVertex(null);
        graph.addEdge(null, a, b, "knows");
        graph.addEdge(null, b, c, "knows");
        graph.addEdge(null, a, c, "hates");
        graph.addEdge(null, a, b, "hates");
        graph.addEdge(null, c, c, "hates");

        Assert.assertEquals(2, count(b.getVertices(BOTH, "knows").iterator()));
        Assert.assertEquals(2, count(b.getEdges(BOTH, "knows").iterator()));
        Assert.assertTrue(asList(b.getVertices(BOTH, "knows")).contains(a));
        count(c.getEdges(BOTH, "hates"));
        Assert.assertEquals(3, count(c.getEdges(BOTH, "hates")));
        graph.commit();
        graph.shutdown();
    }

    public static <T> List<T> asList(Iterable<T> iterable) {
        List<T> list = new ArrayList<T>();
        for (T object : iterable) {
            list.add(object);
        }
        return list;

    }

}
