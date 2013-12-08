package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Graph;
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
        Edge w = graph.addEdge(null, a, b, "knows");
        Edge x = graph.addEdge(null, b, c, "knows");
        Edge y = graph.addEdge(null, a, c, "hates");
        Edge z = graph.addEdge(null, a, b, "hates");
        Edge zz = graph.addEdge(null, c, c, "hates");

        Assert.assertEquals(2, count(b.getVertices(BOTH, "knows").iterator()));
        Assert.assertEquals(2, count(b.getEdges(BOTH, "knows").iterator()));
        Assert.assertTrue(asList(b.getVertices(BOTH, "knows")).contains(a));
        count(c.getEdges(BOTH, "hates"));
        Assert.assertEquals(3, count(c.getEdges(BOTH, "hates")));
        graph.commit();
        graph.printVertexDb();
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
