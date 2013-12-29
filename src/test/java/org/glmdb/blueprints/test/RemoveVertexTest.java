package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Vertex;
import junit.framework.Assert;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.jni.DbEnum;
import org.junit.Test;

/**
 * Date: 2013/11/30
 * Time: 6:58 PM
 */
public class RemoveVertexTest extends BaseGlmdbGraphTest {

    @Test
    public void removeVertexTest() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex vertex1 = thunderGraph.addVertex(null);
            for (int i = 0; i < 5; i++) {
                Vertex vertex2 = thunderGraph.addVertex(null);
                vertex2.setProperty("name0", "test0" + i);
                vertex1.addEdge("test", vertex2);
            }
            thunderGraph.commit();

            Assert.assertEquals(6, countIter(thunderGraph.getVertices().iterator()));

            thunderGraph.getVertex(5L).remove();
            thunderGraph.commit();
            Assert.assertEquals(5, countIter(thunderGraph.getVertices().iterator()));

            thunderGraph.getVertex(4L).remove();
            thunderGraph.commit();
            Assert.assertEquals(4, countIter(thunderGraph.getVertices().iterator()));

            thunderGraph.getVertex(3L).remove();
            thunderGraph.commit();
            Assert.assertEquals(3, countIter(thunderGraph.getVertices().iterator()));

            thunderGraph.getVertex(2L).remove();
            thunderGraph.commit();
            Assert.assertEquals(2, countIter(thunderGraph.getVertices().iterator()));

            thunderGraph.getVertex(1L).remove();
            thunderGraph.commit();
            Assert.assertEquals(1, countIter(thunderGraph.getVertices().iterator()));

            thunderGraph.getVertex(0L).remove();
            thunderGraph.commit();

            Assert.assertEquals(0, countIter(thunderGraph.getVertices().iterator()));
        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void deleteManyVerticesTest() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            for (int i = 0; i < 1000; i++) {
                Vertex vertex1 = thunderGraph.addVertex(null);
                vertex1.setProperty("name0", "test" + i);
            }
            thunderGraph.commit();
            Assert.assertEquals(1000, count(thunderGraph.getVertices()));

            for (long i = 0; i < 1000; i++) {
                Vertex v = thunderGraph.getVertex(i);
                v.remove();
            }

            thunderGraph.commit();
            Assert.assertEquals(0, count(thunderGraph.getVertices()));

        } finally {
            thunderGraph.shutdown();
        }
    }

}
