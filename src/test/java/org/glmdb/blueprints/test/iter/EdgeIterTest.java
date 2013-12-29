package org.glmdb.blueprints.test.iter;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.test.BaseGlmdbGraphTest;
import org.junit.Assert;
import org.junit.Test;

import java.util.Iterator;

/**
 * Date: 2013/12/25
 * Time: 10:55 AM
 */
public class EdgeIterTest extends BaseGlmdbGraphTest {

    @Test
    public void removeEdgeFromIterTest() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex vertex1 = thunderGraph.addVertex(null);
            vertex1.setProperty("name", "vertexOut1");
            for (int i = 0; i < 1000; i++) {
                Vertex vertex2 = thunderGraph.addVertex(null);
                vertex2.setProperty("name", "vertexIn" + i);
                Edge edge = thunderGraph.addEdge(null, vertex1, vertex2, "testLabel1");
                edge.setProperty("name", "edge1" + i);
            }
            thunderGraph.commit();
            Assert.assertEquals(1, countIter(thunderGraph.getVertex(5L).getEdges(Direction.IN, "testLabel1").iterator()));
            Assert.assertNotNull(thunderGraph.getVertex(4L));
            Assert.assertEquals(1000, count(thunderGraph.getEdges()));
            thunderGraph.commit();

            int count = 0;
            Iterator<Edge> iterator = thunderGraph.getEdges().iterator();
            while (iterator.hasNext()) {
                Edge v = iterator.next();
                count++;
                if (count == 5) {
                    iterator.remove();
                }
            }
            thunderGraph.commit();
            Assert.assertNull(thunderGraph.getEdge(4L));
            Assert.assertEquals(999, count(thunderGraph.getEdges()));
            thunderGraph.commit();

            iterator = thunderGraph.getEdges().iterator();
            while (iterator.hasNext()) {
                iterator.next();
                iterator.remove();
            }
            thunderGraph.commit();

            Assert.assertEquals(0, countIter(thunderGraph.getEdges().iterator()));
            thunderGraph.commit();
        } finally {
            thunderGraph.shutdown();
        }

    }

}
