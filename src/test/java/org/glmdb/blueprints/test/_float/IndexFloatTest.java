package org.glmdb.blueprints.test._float;

import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.jni.DbEnum;
import org.glmdb.blueprints.test.BaseGlmdbGraphTest;
import org.junit.Assert;
import org.junit.Test;

import java.util.Iterator;
import java.util.Set;

/**
 * Date: 2013/12/14
 * Time: 8:35 PM
 */
public class IndexFloatTest extends BaseGlmdbGraphTest {

    @Test
    public void testIndexFloatOnVertex() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            thunderGraph.createKeyIndex("name1", Vertex.class);
            thunderGraph.createKeyIndex("name2", Vertex.class);
            thunderGraph.commit();

            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name1", 11F);
            v1.setProperty("name2", 12F);
            Vertex v2 = thunderGraph.addVertex(null);
            v2.setProperty("name1", 21F);
            v2.setProperty("name2", 22F);

            thunderGraph.commit();

            Set<String> indexedKeys = thunderGraph.getIndexedKeys(Vertex.class);
            Assert.assertEquals(2, indexedKeys.size());
            Assert.assertTrue(indexedKeys.contains("name1"));
            Assert.assertTrue(indexedKeys.contains("name2"));

            Iterable<Vertex> name11s = thunderGraph.getVertices("name1", 11F);
            Assert.assertEquals(1, count(name11s.iterator()));
            Iterable<Vertex> name21s = thunderGraph.getVertices("name1", 21F);
            Assert.assertEquals(1, count(name21s.iterator()));

            name11s = thunderGraph.getVertices("name1", 12F);
            Assert.assertEquals(0, countIter(name11s.iterator()));
            name21s = thunderGraph.getVertices("name1", 22F);
            Assert.assertEquals(0, count(name21s.iterator()));

        } finally {
            thunderGraph.shutdown();
        }

    }

    @Test
    public void testIndexFloatOnEdge() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            thunderGraph.createKeyIndex("name1", Edge.class);
            Vertex v1 = thunderGraph.addVertex(null);
            Vertex v2 = thunderGraph.addVertex(null);
            Vertex v3 = thunderGraph.addVertex(null);
            Edge e1 = v1.addEdge("edge1", v2);
            e1.setProperty("name1", 1F);
            Edge e2 = v1.addEdge("edge1", v3);
            e2.setProperty("name1", 1F);
            thunderGraph.commit();

            Assert.assertEquals(1, thunderGraph.getIndexedKeys(Edge.class).size());
            Assert.assertEquals(0, count(thunderGraph.getEdges("name", 1F).iterator()));
            Assert.assertEquals(2, count(thunderGraph.getEdges("name1", 1F).iterator()));
            Assert.assertEquals(0, count(thunderGraph.getEdges("name1", 2F).iterator()));

            thunderGraph.printDb(DbEnum.EDGE_FLOAT_INDEX);

        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void dropFloatIndexTest() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            thunderGraph.createKeyIndex("name1", Vertex.class);
            thunderGraph.commit();

            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name1", 1F);
            Vertex v2 = thunderGraph.addVertex(null);
            v2.setProperty("name1", 1F);
            Vertex v3 = thunderGraph.addVertex(null);
            v3.setProperty("name1", 1F);

            thunderGraph.commit();

            Assert.assertEquals(3, count(thunderGraph.getVertices("name1", 1F)));
            Assert.assertEquals(3, thunderGraph.getDbEntries(DbEnum.VERTEX_FLOAT_INDEX));

            thunderGraph.dropKeyIndex("name1", Vertex.class);

            thunderGraph.commit();

            //Still finds it just not via the index
            Assert.assertEquals(0, thunderGraph.getDbEntries(DbEnum.VERTEX_FLOAT_INDEX));
            Assert.assertEquals(3, count(thunderGraph.getVertices("name1", 1F)));
        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testUpdateIndexedField() {

        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            thunderGraph.createKeyIndex("name1", Vertex.class);
            thunderGraph.commit();

            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name1", 1F);
            Vertex v2 = thunderGraph.addVertex(null);
            v2.setProperty("name1", 1F);
            Vertex v3 = thunderGraph.addVertex(null);
            v3.setProperty("name1", 1F);
            thunderGraph.commit();

            Assert.assertEquals(3, count(thunderGraph.getVertices("name1", 1F)));
            v1.setProperty("name1", 2F);
            thunderGraph.commit();

            Assert.assertEquals(2, count(thunderGraph.getVertices("name1", 1F)));
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
            e1.setProperty("name1", 1F);
            e2.setProperty("name1", 1F);
            e3.setProperty("name1", 1F);
            thunderGraph.commit();

            Assert.assertEquals(3, count(thunderGraph.getEdges("name1", 1F)));
            e1.setProperty("name1", 2F);
            thunderGraph.commit();

            Assert.assertEquals(2, count(thunderGraph.getEdges("name1", 1F)));
            e2.setProperty("name1", 2F);
            thunderGraph.commit();

            Assert.assertEquals(1, count(thunderGraph.getEdges("name1", 1F)));
            e3.setProperty("name1", 2F);
            thunderGraph.commit();

            Assert.assertEquals(0, count(thunderGraph.getEdges("name1", 1F)));
            Assert.assertEquals(3, count(thunderGraph.getEdges("name1", 2F)));

            thunderGraph.printDb(DbEnum.EDGE_FLOAT_INDEX);
            thunderGraph.dropKeyIndex("name1", Edge.class);
            thunderGraph.printDb(DbEnum.EDGE_FLOAT_INDEX);

        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testReindexOnVertex() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {

            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name1", 1F);
            Vertex v2 = thunderGraph.addVertex(null);
            v2.setProperty("name1", 1F);
            Vertex v3 = thunderGraph.addVertex(null);
            v3.setProperty("name1", 1F);
            thunderGraph.commit();

            Assert.assertEquals(3, count(thunderGraph.getVertices("name1", 1F)));
            Assert.assertEquals(0, thunderGraph.getDbEntries(DbEnum.VERTEX_FLOAT_INDEX));

            thunderGraph.createKeyIndex("name1", Vertex.class);
            Assert.assertEquals(3, count(thunderGraph.getVertices("name1", 1F)));
            Assert.assertEquals(3, thunderGraph.getDbEntries(DbEnum.VERTEX_FLOAT_INDEX));

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

            e1.setProperty("name1", 1F);
            e2.setProperty("name1", 1F);
            e3.setProperty("name1", 1F);

            thunderGraph.commit();

            Assert.assertEquals(3, count(thunderGraph.getEdges("name1", 1F)));
            thunderGraph.printDb(DbEnum.EDGE_FLOAT_INDEX);

            thunderGraph.createKeyIndex("name1", Edge.class);
            Assert.assertEquals(3, count(thunderGraph.getEdges("name1", 1F)));
            thunderGraph.printDb(DbEnum.EDGE_FLOAT_INDEX);

        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void deleteIndexedVertex() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            thunderGraph.createKeyIndex("name", Vertex.class);

            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name", 1F);
            thunderGraph.commit();
            Assert.assertEquals(1, thunderGraph.getDbEntries(DbEnum.VERTEX_FLOAT_INDEX));

            v1.remove();
            thunderGraph.commit();
            Assert.assertEquals(0, thunderGraph.getDbEntries(DbEnum.VERTEX_FLOAT_INDEX));
        } finally {
            thunderGraph.shutdown();
        }

    }

    @Test
    public void testCursorRefreshOnFirst() {

        ThunderGraph graph = new ThunderGraph(this.dbPath);
        try {
            graph.createKeyIndex("name", Vertex.class);
            graph.commit();

            Vertex v1 = graph.addVertex(null);
            v1.setProperty("name", 1F);
            for (int i = 0; i < 10; i++) {
                Vertex v2 = graph.addVertex(null);
                v2.setProperty("name", 2F);
                Edge e = graph.addEdge(null, v1, v2, "label1");
                e.setProperty("name", "cccc");
            }
            graph.commit();

            Assert.assertEquals(11, count(graph.getVertices()));
            Assert.assertEquals(1, count(graph.getVertices("name", 1F)));
            Assert.assertEquals(10, count(graph.getVertices("name", 2F)));
            Assert.assertEquals(10, count(graph.getEdges("name", "cccc")));
            Iterator<Vertex> iter = graph.getVertices("name", 1F).iterator();
            //This will cause the transaction to be upgraded to a writable transaction.
            //I.e. iter's cursor gets closed
            graph.getEdges("name", "cccc").iterator().next().setProperty("name", "cccd");
            Vertex v = iter.next();
            Assert.assertEquals(1F, v.getProperty("name"));
        } finally {
            graph.shutdown();
        }

    }

    @Test
    public void testCursorRefreshOnNext() {

        ThunderGraph graph = new ThunderGraph(this.dbPath);
        try {
            graph.createKeyIndex("name", Vertex.class);
            graph.commit();

            Vertex v1 = graph.addVertex(null);
            v1.setProperty("name", 1F);
            for (int i = 0; i < 10; i++) {
                Vertex v2 = graph.addVertex(null);
                v2.setProperty("name", 2F);
                Edge e = graph.addEdge(null, v1, v2, "label1");
                e.setProperty("name", "cccc");
            }
            graph.commit();

            Assert.assertEquals(11, count(graph.getVertices()));
            Assert.assertEquals(1, count(graph.getVertices("name", 1F)));
            Assert.assertEquals(10, count(graph.getVertices("name", 2F)));
            Assert.assertEquals(10, count(graph.getEdges("name", "cccc")));

            Iterator<Vertex> iter = graph.getVertices("name", 2F).iterator();
            Vertex v = iter.next();
            Assert.assertEquals(1L, v.getId());
            Assert.assertEquals(2F, v.getProperty("name"));

            //This will cause the transaction to be upgraded to a writable transaction.
            //I.e. iter's cursor gets closed
            v.setProperty("name", 3F);

            v = iter.next();
            Assert.assertEquals(2L, v.getId());
            Assert.assertEquals(2F, v.getProperty("name"));
            Assert.assertEquals(8, count(iter));
        } finally {
            graph.shutdown();
        }

    }

    @Test
    public void testRemove() {
        ThunderGraph graph = new ThunderGraph(this.dbPath);
        try {
            graph.createKeyIndex("name", Vertex.class);
            graph.commit();

            Vertex v1 = graph.addVertex(null);
            v1.setProperty("name", 1F);
            for (int i = 0; i < 10; i++) {
                Vertex v2 = graph.addVertex(null);
                v2.setProperty("name", 2F);
                Edge e = graph.addEdge(null, v1, v2, "label1");
                e.setProperty("name", "cccc");
            }
            graph.commit();

            Assert.assertEquals(11, count(graph.getVertices()));
            Assert.assertEquals(1, count(graph.getVertices("name", 1F)));
            Assert.assertEquals(10, count(graph.getVertices("name", 2F)));
            Assert.assertEquals(10, count(graph.getEdges("name", "cccc")));

            Iterator<Vertex> iter = graph.getVertices("name", 2F).iterator();
            Vertex v = iter.next();
            Assert.assertEquals(1L, v.getId());
            Assert.assertEquals(2F, v.getProperty("name"));
            iter.remove();
            Assert.assertNull(graph.getVertex(1L));
            Assert.assertEquals(9, count(iter));
        } finally {
            graph.shutdown();
        }
    }

    @Test(expected = IllegalStateException.class)
    public void testRemoveTransactionAlreadyWritableFail() {
        ThunderGraph graph = new ThunderGraph(this.dbPath);
        try {
            graph.createKeyIndex("name", Vertex.class);
            graph.commit();

            Vertex v1 = graph.addVertex(null);
            v1.setProperty("name", 1F);
            for (int i = 0; i < 10; i++) {
                Vertex v2 = graph.addVertex(null);
                v2.setProperty("name", 2F);
                Edge e = graph.addEdge(null, v1, v2, "label1");
                e.setProperty("name", "cccc");
            }
            graph.commit();

            Assert.assertEquals(11, count(graph.getVertices()));
            Assert.assertEquals(1, count(graph.getVertices("name", 1F)));
            Assert.assertEquals(10, count(graph.getVertices("name", 2F)));
            Assert.assertEquals(10, count(graph.getEdges("name", "cccc")));

            Iterator<Vertex> iter = graph.getVertices("name", 2F).iterator();
            Vertex v = iter.next();
            v.setProperty("name", 3F);
            Assert.assertEquals(1L, v.getId());
            Assert.assertEquals(3F, v.getProperty("name"));
            iter.remove();
            Assert.assertNull(graph.getVertex(1L));
            Assert.assertEquals(9, count(iter));

            graph.commit();
            iter = graph.getVertices("name", 2F).iterator();
            Assert.assertEquals(9, count(iter));

        } finally {
            graph.shutdown();
        }
    }

    @Test
    public void testRemoveTransactionAlreadyWritableSucceed() {
        ThunderGraph graph = new ThunderGraph(this.dbPath);
        try {
            graph.createKeyIndex("name", Vertex.class);
            graph.commit();

            Vertex v1 = graph.addVertex(null);
            v1.setProperty("name", 1F);
            for (int i = 0; i < 10; i++) {
                Vertex v2 = graph.addVertex(null);
                v2.setProperty("name", 2F);
                Edge e = graph.addEdge(null, v1, v2, "label1");
                e.setProperty("name", "cccc");
            }
            graph.commit();

            Assert.assertEquals(11, count(graph.getVertices()));
            Assert.assertEquals(1, count(graph.getVertices("name", 1F)));
            Assert.assertEquals(10, count(graph.getVertices("name", 2F)));
            Assert.assertEquals(10, count(graph.getEdges("name", "cccc")));

            Iterator<Vertex> iter = graph.getVertices("name", 2F).iterator();
            Vertex v = iter.next();
            v.setProperty("name", 2F);
            Assert.assertEquals(1L, v.getId());
            Assert.assertEquals(2F, v.getProperty("name"));
            iter.remove();
            Assert.assertNull(graph.getVertex(1L));
            Assert.assertEquals(9, count(iter));

            graph.commit();
            iter = graph.getVertices("name", 2F).iterator();
            Assert.assertEquals(9, count(iter));

        } finally {
            graph.shutdown();
        }
    }

}