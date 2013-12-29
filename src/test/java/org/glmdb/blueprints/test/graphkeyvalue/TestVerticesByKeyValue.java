package org.glmdb.blueprints.test.graphkeyvalue;

import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.test.BaseGlmdbGraphTest;
import org.junit.Assert;
import org.junit.Test;

import java.util.Iterator;

/**
 * Date: 2013/12/25
 * Time: 8:57 PM
 */
public class TestVerticesByKeyValue extends BaseGlmdbGraphTest {

    @Test
    public void testVerticesByKeyValue() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name1", 1);
            Vertex v2 = thunderGraph.addVertex(null);
            v2.setProperty("name1", 1);
            Vertex v3 = thunderGraph.addVertex(null);
            v3.setProperty("name1", 1);
            thunderGraph.commit();

            Assert.assertEquals(3, count(thunderGraph.getVertices("name1", 1)));

        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testVerticesByKeyValueMany() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name0", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

            for (int i = 0; i < 10000; i++) {

                if (i % 2 == 0) {
                    Vertex v2 = thunderGraph.addVertex(null);
                    v2.setProperty("name1", "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
                    thunderGraph.addEdge(null, v1, v2, "label1");
                } else {
                    Vertex v2 = thunderGraph.addVertex(null);
                    v2.setProperty("name2", "ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc");
                    thunderGraph.addEdge(null, v1, v2, "label1");
                }

            }

            thunderGraph.commit();

            Assert.assertEquals(10001, count(thunderGraph.getVertices()));
            Assert.assertEquals(10000, count(thunderGraph.getEdges()));

            Assert.assertEquals(1, count(thunderGraph.getVertices("name0", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")));
            Assert.assertEquals(5000, count(thunderGraph.getVertices("name1", "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")));
            Assert.assertEquals(5000, count(thunderGraph.getVertices("name2", "ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc")));

            Assert.assertEquals(0, count(thunderGraph.getVertices("name0", "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")));
            Assert.assertEquals(0, count(thunderGraph.getVertices("name1", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")));
            Assert.assertEquals(0, count(thunderGraph.getVertices("name2", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")));

        } finally {
            thunderGraph.shutdown();
        }

    }

    @Test
    public void testRefreshingCursor() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name0", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

            for (int i = 0; i < 1000; i++) {

                if (i % 2 == 0) {
                    Vertex v2 = thunderGraph.addVertex(null);
                    v2.setProperty("name1", "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
                    thunderGraph.addEdge(null, v1, v2, "label1");
                } else {
                    Vertex v2 = thunderGraph.addVertex(null);
                    v2.setProperty("name2", "ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc");
                    thunderGraph.addEdge(null, v1, v2, "label1");
                }

            }

            thunderGraph.commit();

            Iterator<Vertex> iter = thunderGraph.getVertices("name1", "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb").iterator();
            Assert.assertTrue(iter.hasNext());
            iter.next();

            thunderGraph.commit();
            Assert.assertTrue(iter.hasNext());
            iter.next();

            thunderGraph.commit();

        } finally {
            thunderGraph.shutdown();
        }
    }

}
