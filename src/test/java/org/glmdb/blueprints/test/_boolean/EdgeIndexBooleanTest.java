package org.glmdb.blueprints.test._boolean;

import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.jni.DbEnum;
import org.glmdb.blueprints.test.BaseGlmdbGraphTest;
import org.junit.Assert;
import org.junit.Test;

import java.util.Iterator;

/**
 * Date: 2013/12/31
 * Time: 11:53 AM
 */
public class EdgeIndexBooleanTest extends BaseGlmdbGraphTest {

    @Test
    public void testIndexRemoval() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            thunderGraph.createKeyIndex("name1", Edge.class);
            Vertex v1 = thunderGraph.addVertex(null);
            Vertex v2 = thunderGraph.addVertex(null);
            Vertex v3 = thunderGraph.addVertex(null);
            Edge e1 = v1.addEdge("edge1", v2);
            e1.setProperty("name1", true);
            Edge e2 = v1.addEdge("edge1", v3);
            e2.setProperty("name1", true);
            thunderGraph.commit();

            Assert.assertEquals(2, thunderGraph.getDbEntries(DbEnum.EDGE_BOOLEAN_INDEX));
            e1.remove();
            Assert.assertEquals(1, thunderGraph.getDbEntries(DbEnum.EDGE_BOOLEAN_INDEX));
            e2.remove();
            Assert.assertEquals(0, thunderGraph.getDbEntries(DbEnum.EDGE_BOOLEAN_INDEX));
        } finally {
            thunderGraph.shutdown();
        }

    }

    @Test
    public void testIndexBooleanOnEdge() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            thunderGraph.createKeyIndex("name1", Edge.class);
            Vertex v1 = thunderGraph.addVertex(null);
            Vertex v2 = thunderGraph.addVertex(null);
            Vertex v3 = thunderGraph.addVertex(null);
            Edge e1 = v1.addEdge("edge1", v2);
            e1.setProperty("name1", true);
            Edge e2 = v1.addEdge("edge1", v3);
            e2.setProperty("name1", true);
            thunderGraph.commit();

            Assert.assertEquals(1, thunderGraph.getIndexedKeys(Edge.class).size());
            Assert.assertEquals(0, count(thunderGraph.getEdges("name", true).iterator()));
            Assert.assertEquals(2, count(thunderGraph.getEdges("name1", true).iterator()));
            Assert.assertEquals(0, count(thunderGraph.getEdges("name1", false).iterator()));

        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void dropBooleanIndexTest() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            thunderGraph.createKeyIndex("name1", Edge.class);
            thunderGraph.commit();

            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name1", "aaaa1");
            Edge e1 = v1.addEdge("label", thunderGraph.addVertex(null));
            e1.setProperty("name1", true);
            Edge e2 = v1.addEdge("label", thunderGraph.addVertex(null));
            e2.setProperty("name1", true);
            Edge e3 = v1.addEdge("label", thunderGraph.addVertex(null));
            e3.setProperty("name1", true);

            thunderGraph.commit();

            Assert.assertEquals(3, count(thunderGraph.getEdges("name1", true).iterator()));
            Assert.assertEquals(3, thunderGraph.getDbEntries(DbEnum.EDGE_BOOLEAN_INDEX));

            thunderGraph.dropKeyIndex("name1", Edge.class);

            //Still finds it just not via the index
            Assert.assertEquals(3, count(thunderGraph.getEdges("name1", true).iterator()));
            Assert.assertEquals(0, thunderGraph.getDbEntries(DbEnum.EDGE_BOOLEAN_INDEX));

            thunderGraph.commit();

        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testUpdateIndexedFieldOnEdge() {

        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            thunderGraph.createKeyIndex("name1", Edge.class);
            Vertex v1 = thunderGraph.addVertex(null);
            Vertex v2 = thunderGraph.addVertex(null);
            Vertex v3 = thunderGraph.addVertex(null);
            Vertex v4 = thunderGraph.addVertex(null);
            Edge e1 = v1.addEdge("label1", v2);
            Edge e2 = v1.addEdge("label1", v3);
            Edge e3 = v1.addEdge("label1", v4);
            e1.setProperty("name1", true);
            e2.setProperty("name1", true);
            e3.setProperty("name1", true);
            thunderGraph.commit();

            Assert.assertEquals(3, count(thunderGraph.getEdges("name1", true)));
            e1.setProperty("name1", false);
            thunderGraph.commit();

            Assert.assertEquals(2, count(thunderGraph.getEdges("name1", true)));
            e2.setProperty("name1", false);
            thunderGraph.commit();

            Assert.assertEquals(1, count(thunderGraph.getEdges("name1", true)));
            e3.setProperty("name1", false);
            thunderGraph.commit();

            Assert.assertEquals(0, count(thunderGraph.getEdges("name1", true)));
            Assert.assertEquals(3, count(thunderGraph.getEdges("name1", false)));

            Assert.assertEquals(3, thunderGraph.getDbEntries(DbEnum.EDGE_BOOLEAN_INDEX));
            thunderGraph.dropKeyIndex("name1", Edge.class);
            Assert.assertEquals(0, thunderGraph.getDbEntries(DbEnum.EDGE_BOOLEAN_INDEX));

        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testReindexOnEdge() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {

            Vertex v1 = thunderGraph.addVertex(null);
            Vertex v2 = thunderGraph.addVertex(null);
            Vertex v3 = thunderGraph.addVertex(null);
            Vertex v4 = thunderGraph.addVertex(null);

            Edge e1 = v1.addEdge("label1", v2);
            Edge e2 = v1.addEdge("label1", v3);
            Edge e3 = v1.addEdge("label1", v4);

            e1.setProperty("name1", true);
            e2.setProperty("name1", true);
            e3.setProperty("name1", true);

            thunderGraph.commit();

            Assert.assertEquals(3, count(thunderGraph.getEdges("name1", true)));
            Assert.assertEquals(0, thunderGraph.getDbEntries(DbEnum.EDGE_BOOLEAN_INDEX));

            thunderGraph.createKeyIndex("name1", Edge.class);
            Assert.assertEquals(3, count(thunderGraph.getEdges("name1", true)));
            Assert.assertEquals(3, thunderGraph.getDbEntries(DbEnum.EDGE_BOOLEAN_INDEX));

        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void deleteIndexedEdge() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            thunderGraph.createKeyIndex("name", Edge.class);

            Vertex v1 = thunderGraph.addVertex(null);
            Edge e1 = v1.addEdge("label", thunderGraph.addVertex(null));
            e1.setProperty("name", true);
            thunderGraph.commit();
            Assert.assertEquals(1, thunderGraph.getDbEntries(DbEnum.EDGE_BOOLEAN_INDEX));

            v1.remove();
            thunderGraph.commit();
            Assert.assertEquals(0, thunderGraph.getDbEntries(DbEnum.EDGE_BOOLEAN_INDEX));
        } finally {
            thunderGraph.shutdown();
        }

    }

    @Test
    public void testUpdateValuesInIndexKeys() throws Exception {
        ThunderGraph graph = new ThunderGraph(this.dbPath);
        try {
            graph.createKeyIndex("name", Edge.class);
            graph.commit();

            Vertex v1 = graph.addVertex(null);
            Edge e1 = v1.addEdge("label", graph.addVertex(null));
            e1.setProperty("name", true);
            Assert.assertEquals(e1.getProperty("name"), true);
            Assert.assertEquals(1, count(graph.getEdges()));
            graph.commit();

            e1 = graph.getEdges("name", true).iterator().next();
            Assert.assertEquals(e1.getProperty("name"), true);
            e1.setProperty("name", false);
            Assert.assertEquals(e1.getProperty("name"), false);
            Assert.assertEquals(1, count(graph.getEdges()));
            graph.commit();


            Assert.assertFalse(graph.getEdges("name", true).iterator().hasNext());
            e1 = graph.getEdges("name", false).iterator().next();
            Assert.assertEquals(e1.getProperty("name"), false);
            Assert.assertEquals(1, count(graph.getEdges()));
            graph.commit();

        } finally {
            graph.shutdown();
        }
    }

    @Test
    public void testPartialMatchFails() {
        ThunderGraph graph = new ThunderGraph(this.dbPath);
        try {
            graph.createKeyIndex("name", Edge.class);
            graph.commit();

            Vertex v1 = graph.addVertex(null);
            Edge e1 = v1.addEdge("label", graph.addVertex(null));
            e1.setProperty("name", true);

            graph.commit();

            Assert.assertEquals(1, count(graph.getEdges("name", true)));
            Assert.assertEquals(0, count(graph.getEdges("name", false)));
        } finally {
            graph.shutdown();
        }
    }

    @Test
    public void testCursorRefreshOnFirst() {

        ThunderGraph graph = new ThunderGraph(this.dbPath);
        try {
            graph.createKeyIndex("name", Edge.class);
            graph.commit();

            Vertex v1 = graph.addVertex(null);
            v1.setProperty("name", "aaaa");
            for (int i = 0; i < 10; i++) {
                Vertex v2 = graph.addVertex(null);
                v2.setProperty("name", "bbbb");
                Edge e = graph.addEdge(null, v1, v2, "label1");
                e.setProperty("name", true);
            }
            graph.commit();

            Assert.assertEquals(11, count(graph.getVertices()));
            Assert.assertEquals(1, count(graph.getVertices("name", "aaaa")));
            Assert.assertEquals(10, count(graph.getVertices("name", "bbbb")));
            Assert.assertEquals(10, count(graph.getEdges("name", true)));
            Iterator<Edge> iter = graph.getEdges("name", true).iterator();
            //This will cause the transaction to be upgraded to a writable transaction.
            //I.e. iter's cursor gets closed
            graph.getVertices("name", "bbbb").iterator().next().setProperty("name", "bbba");
            Edge e = iter.next();
            Assert.assertEquals(true, e.getProperty("name"));
        } finally {
            graph.shutdown();
        }

    }

    @Test
    public void testCursorRefreshOnNext() {

        ThunderGraph graph = new ThunderGraph(this.dbPath);
        try {
            graph.createKeyIndex("name", Edge.class);
            graph.commit();

            Vertex v1 = graph.addVertex(null);
            v1.setProperty("name", "aaaa");
            for (int i = 0; i < 10; i++) {
                Vertex v2 = graph.addVertex(null);
                v2.setProperty("name", "bbbb");
                Edge e = graph.addEdge(null, v1, v2, "label1");
                e.setProperty("name", true);
            }
            graph.commit();

            Assert.assertEquals(11, count(graph.getVertices()));
            Assert.assertEquals(1, count(graph.getVertices("name", "aaaa")));
            Assert.assertEquals(10, count(graph.getVertices("name", "bbbb")));
            Assert.assertEquals(10, count(graph.getEdges("name", true)));

            Iterator<Edge> iter = graph.getEdges("name", true).iterator();
            Edge e = iter.next();
            Assert.assertEquals(0L, e.getId());
            Assert.assertEquals(true, e.getProperty("name"));
            //This will cause the transaction to be upgraded to a writable transaction.
            //I.e. iter's cursor gets closed
            e.setProperty("name", false);
            e = iter.next();
            Assert.assertEquals(1L, e.getId());
            Assert.assertEquals(true, e.getProperty("name"));
            Assert.assertEquals(8, count(iter));
        } finally {
            graph.shutdown();
        }

    }

    @Test
    public void testRemove() {
        ThunderGraph graph = new ThunderGraph(this.dbPath);
        try {
            graph.createKeyIndex("name", Edge.class);
            graph.commit();

            Vertex v1 = graph.addVertex(null);
            v1.setProperty("name", "aaaa");
            for (int i = 0; i < 10; i++) {
                Vertex v2 = graph.addVertex(null);
                v2.setProperty("name", "bbbb");
                Edge e = graph.addEdge(null, v1, v2, "label1");
                e.setProperty("name", true);
            }
            graph.commit();

            Assert.assertEquals(11, count(graph.getVertices()));
            Assert.assertEquals(1, count(graph.getVertices("name", "aaaa")));
            Assert.assertEquals(10, count(graph.getVertices("name", "bbbb")));
            Assert.assertEquals(10, count(graph.getEdges("name", true)));

            Iterator<Edge> iter = graph.getEdges("name", true).iterator();
            Edge e = iter.next();
            Assert.assertEquals(0L, e.getId());
            Assert.assertEquals(true, e.getProperty("name"));
            iter.remove();
            Assert.assertNull(graph.getEdge(0L));
            Assert.assertEquals(9, count(iter));
        } finally {
            graph.shutdown();
        }
    }

    @Test(expected = IllegalStateException.class)
    public void testRemoveTransactionAlreadyWritableFail() {
        ThunderGraph graph = new ThunderGraph(this.dbPath);
        try {
            graph.createKeyIndex("name", Edge.class);
            graph.commit();

            Vertex v1 = graph.addVertex(null);
            v1.setProperty("name", "aaaa");
            for (int i = 0; i < 10; i++) {
                Vertex v2 = graph.addVertex(null);
                v2.setProperty("name", "bbbb");
                Edge e = graph.addEdge(null, v1, v2, "label1");
                e.setProperty("name", true);
            }
            graph.commit();

            Assert.assertEquals(11, count(graph.getVertices()));
            Assert.assertEquals(1, count(graph.getVertices("name", "aaaa")));
            Assert.assertEquals(10, count(graph.getVertices("name", "bbbb")));
            Assert.assertEquals(10, count(graph.getEdges("name", true)));

            Iterator<Edge> iter = graph.getEdges("name", true).iterator();
            Edge e = iter.next();
            e.setProperty("name", false);
            Assert.assertEquals(0L, e.getId());
            Assert.assertEquals(false, e.getProperty("name"));
            iter.remove();
            Assert.assertNull(graph.getEdge(0L));
            Assert.assertEquals(9, count(iter));

            graph.commit();
            iter = graph.getEdges("name", true).iterator();
            Assert.assertEquals(9, count(iter));

        } finally {
            graph.shutdown();
        }
    }

    @Test
    public void testRemoveTransactionAlreadyWritableSucceed() {
        ThunderGraph graph = new ThunderGraph(this.dbPath);
        try {
            graph.createKeyIndex("name", Edge.class);
            graph.commit();

            Vertex v1 = graph.addVertex(null);
            v1.setProperty("name", "aaaa");
            for (int i = 0; i < 10; i++) {
                Vertex v2 = graph.addVertex(null);
                v2.setProperty("name", "bbbb");
                Edge e = graph.addEdge(null, v1, v2, "label1");
                e.setProperty("name", true);
            }
            graph.commit();

            Assert.assertEquals(11, count(graph.getVertices()));
            Assert.assertEquals(1, count(graph.getVertices("name", "aaaa")));
            Assert.assertEquals(10, count(graph.getVertices("name", "bbbb")));
            Assert.assertEquals(10, count(graph.getEdges("name", true)));

            Iterator<Edge> iter = graph.getEdges("name", true).iterator();
            Edge e = iter.next();
            e.setProperty("name", true);
            Assert.assertEquals(0L, e.getId());
            Assert.assertEquals(true, e.getProperty("name"));
            iter.remove();
            Assert.assertNull(graph.getEdge(0L));
            Assert.assertEquals(9, count(iter));

            graph.commit();
            iter = graph.getEdges("name", true).iterator();
            Assert.assertEquals(9, count(iter));

        } finally {
            graph.shutdown();
        }
    }

}
