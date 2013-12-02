package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.GlmdbGraph;
import org.junit.Assert;
import org.junit.Test;

import java.util.Set;

/**
 * Date: 2013/11/19
 * Time: 11:24 PM
 */
public class GlmdbGraphGetPropertyKeysTest extends BaseGlmdbGraphTest  {

    @Test
    public void testPropertyKeys() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        for (int i = 0; i < 5; i++) {
            Vertex vertex = glmdbGraph.addVertex(null);
            vertex.setProperty("name0", "pieter0" + i);
            vertex.setProperty("name1", "pieter1" + i);
            vertex.setProperty("name2", "pieter2" + i);
            vertex.setProperty("name3", "pieter3" + i);
        }
        glmdbGraph.commit();
        glmdbGraph.printVertexDb();

        Set<String> propertyKeys = glmdbGraph.getVertex(1L).getPropertyKeys();
        Assert.assertEquals(4, propertyKeys.size());
        boolean hasName0 = false;
        boolean hasName1 = false;
        boolean hasName2 = false;
        boolean hasName3 = false;
        for (String s : propertyKeys) {
            if (s.equals("name0")) {
                hasName0 = true;
            } else if (s.equals("name1")) {
                hasName1 = true;
            } else if (s.equals("name2")) {
                hasName2 = true;
            } else if (s.equals("name3")) {
                hasName3 = true;
            } else {
                Assert.fail("property key not found!");
            }
        }
        Assert.assertTrue(hasName0 && hasName1 && hasName2 && hasName3);
        glmdbGraph.shutdown();
    }

    @Test
    public void testEdgePropertyKeys() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        Vertex vertex = glmdbGraph.addVertex(null);
        for (int i = 0; i < 5; i++) {
            Vertex vertex1 = glmdbGraph.addVertex(null);
            vertex1.setProperty("name", "a" + i);
            Edge edge = vertex.addEdge("label1", vertex1);
            edge.setProperty("name" + i, i);
        }
        glmdbGraph.commit();
        glmdbGraph.printVertexDb();

        Set<String> propertyKeys = glmdbGraph.getEdge(0L).getPropertyKeys();
        Assert.assertEquals(0, propertyKeys.size());

        propertyKeys = glmdbGraph.getEdge(1L).getPropertyKeys();
        Assert.assertEquals(1, propertyKeys.size());

        propertyKeys = glmdbGraph.getEdge(2L).getPropertyKeys();
        Assert.assertEquals(1, propertyKeys.size());

        propertyKeys = glmdbGraph.getEdge(3L).getPropertyKeys();
        Assert.assertEquals(1, propertyKeys.size());

        glmdbGraph.shutdown();
    }

}
