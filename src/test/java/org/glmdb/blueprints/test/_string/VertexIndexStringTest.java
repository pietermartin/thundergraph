package org.glmdb.blueprints.test._string;

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
public class VertexIndexStringTest extends BaseGlmdbGraphTest {

    @Test
    public void testIndexRemoval() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            thunderGraph.createKeyIndex("name1", Vertex.class);
            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name1", "aaaaaaaa");
            Vertex v2 = thunderGraph.addVertex(null);
            v2.setProperty("name1", "bbbbbbbb");
            Vertex v3 = thunderGraph.addVertex(null);
            v3.setProperty("name1", "cccccccc");
            v1.addEdge("edge1", v2);
            v1.addEdge("edge1", v3);
            thunderGraph.commit();

            Assert.assertEquals(3, thunderGraph.getDbEntries(DbEnum.VERTEX_STRING_INDEX));
            v2.remove();
            Assert.assertEquals(2, thunderGraph.getDbEntries(DbEnum.VERTEX_STRING_INDEX));
            v3.remove();
            Assert.assertEquals(1, thunderGraph.getDbEntries(DbEnum.VERTEX_STRING_INDEX));
        } finally {
            thunderGraph.shutdown();
        }

    }

    @Test
    public void testIndexStringOnVertex() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            thunderGraph.createKeyIndex("name1", Vertex.class);
            thunderGraph.createKeyIndex("name2", Vertex.class);
            thunderGraph.commit();

            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name1", "Balrog11");
            v1.setProperty("name2", "Balrog12");
            Vertex v2 = thunderGraph.addVertex(null);
            v2.setProperty("name1", "Balrog21");
            v2.setProperty("name2", "Balrog22");

            thunderGraph.commit();

            Set<String> indexedKeys = thunderGraph.getIndexedKeys(Vertex.class);
            Assert.assertEquals(2, indexedKeys.size());
            Assert.assertTrue(indexedKeys.contains("name1"));
            Assert.assertTrue(indexedKeys.contains("name2"));


            Iterable<Vertex> name11s = thunderGraph.getVertices("name1", "Balrog11");
            Assert.assertEquals(1, countIter(name11s.iterator()));
            Iterable<Vertex> name21s = thunderGraph.getVertices("name1", "Balrog21");
            Assert.assertEquals(1, countIter(name21s.iterator()));

            name11s = thunderGraph.getVertices("name1", "Balrog12");
            Assert.assertEquals(0, countIter(name11s.iterator()));
            name21s = thunderGraph.getVertices("name1", "Balrog22");
            Assert.assertEquals(0, countIter(name21s.iterator()));

        } finally {
            thunderGraph.shutdown();
        }

    }

    @Test
    public void dropStringIndexTest() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            thunderGraph.createKeyIndex("name1", Vertex.class);
            thunderGraph.commit();

            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name1", "aaaa1");
            Vertex v2 = thunderGraph.addVertex(null);
            v2.setProperty("name1", "aaaa1");
            Vertex v3 = thunderGraph.addVertex(null);
            v3.setProperty("name1", "aaaa1");

            thunderGraph.commit();

            Assert.assertEquals(3, count(thunderGraph.getVertices("name1", "aaaa1").iterator()));
            thunderGraph.printDb(DbEnum.VERTEX_STRING_INDEX);

            thunderGraph.dropKeyIndex("name1", Vertex.class);

            //Still finds it just not via the index
            Assert.assertEquals(3, count(thunderGraph.getVertices("name1", "aaaa1").iterator()));
            thunderGraph.printDb(DbEnum.VERTEX_STRING_INDEX);

            thunderGraph.commit();
            thunderGraph.printDb(DbEnum.VERTEX_STRING_INDEX);

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
            v1.setProperty("name1", "aaaa1");
            Vertex v2 = thunderGraph.addVertex(null);
            v2.setProperty("name1", "aaaa1");
            Vertex v3 = thunderGraph.addVertex(null);
            v3.setProperty("name1", "aaaa1");
            thunderGraph.commit();

            Assert.assertEquals(3, count(thunderGraph.getVertices("name1", "aaaa1")));
            v1.setProperty("name1", "aaaa2");
            thunderGraph.commit();

            Assert.assertEquals(2, count(thunderGraph.getVertices("name1", "aaaa1")));
        } finally {
            thunderGraph.shutdown();
        }
    }


    @Test
    public void testReindexOnVertex() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {

            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name1", "aaaa1");
            Vertex v2 = thunderGraph.addVertex(null);
            v2.setProperty("name1", "aaaa1");
            Vertex v3 = thunderGraph.addVertex(null);
            v3.setProperty("name1", "aaaa1");
            thunderGraph.commit();

            Assert.assertEquals(3, count(thunderGraph.getVertices("name1", "aaaa1")));
            Assert.assertEquals(0, thunderGraph.getDbEntries(DbEnum.VERTEX_STRING_INDEX));

            thunderGraph.createKeyIndex("name1", Vertex.class);
            Assert.assertEquals(3, count(thunderGraph.getVertices("name1", "aaaa1")));
            Assert.assertEquals(3, thunderGraph.getDbEntries(DbEnum.VERTEX_STRING_INDEX));

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
            v1.setProperty("name", "aaaa");
            thunderGraph.commit();
            thunderGraph.printDb(DbEnum.VERTEX_STRING_INDEX);

            v1.remove();
            thunderGraph.commit();
            thunderGraph.printDb(DbEnum.VERTEX_STRING_INDEX);
        } finally {
            thunderGraph.shutdown();
        }

    }

    @Test
    public void testUpdateValuesInIndexKeys() throws Exception {
        ThunderGraph graph = new ThunderGraph(this.dbPath);
        try {
            graph.createKeyIndex("name", Vertex.class);
            graph.commit();

            Vertex v1 = graph.addVertex(null);
            v1.setProperty("name", "marko");
            Assert.assertEquals(v1.getProperty("name"), "marko");
            Assert.assertEquals(1, count(graph.getVertices()));
            graph.commit();

            v1 = graph.getVertices("name", "marko").iterator().next();
            Assert.assertEquals(v1.getProperty("name"), "marko");
            v1.setProperty("name", "marko a. rodriguez");
            Assert.assertEquals(v1.getProperty("name"), "marko a. rodriguez");
            Assert.assertEquals(1, count(graph.getVertices()));
            graph.commit();


            Assert.assertFalse(graph.getVertices("name", "marko").iterator().hasNext());
            v1 = graph.getVertices("name", "marko a. rodriguez").iterator().next();
            Assert.assertEquals(v1.getProperty("name"), "marko a. rodriguez");
            Assert.assertEquals(1, count(graph.getVertices()));
            graph.commit();

        } finally {
            graph.shutdown();
        }
    }

    @Test
    public void testPartialMatchFails() {
        ThunderGraph graph = new ThunderGraph(this.dbPath);
        try {
            graph.createKeyIndex("name", Vertex.class);
            graph.commit();

            Vertex v1 = graph.addVertex(null);
            v1.setProperty("name", "aaaa");

            graph.commit();

            Assert.assertEquals(1, count(graph.getVertices("name", "aaaa")));
            Assert.assertEquals(0, count(graph.getVertices("name", "a")));
        } finally {
            graph.shutdown();
        }
    }

    @Test
    public void testCursorRefreshOnFirst() {

        ThunderGraph graph = new ThunderGraph(this.dbPath);
        try {
            graph.createKeyIndex("name", Vertex.class);
            graph.commit();

            Vertex v1 = graph.addVertex(null);
            v1.setProperty("name", "aaaa");
            for (int i = 0; i < 10; i++) {
                Vertex v2 = graph.addVertex(null);
                v2.setProperty("name", "bbbb");
                Edge e = graph.addEdge(null, v1, v2, "label1");
                e.setProperty("name", "cccc");
            }
            graph.commit();

            Assert.assertEquals(11, count(graph.getVertices()));
            Assert.assertEquals(1, count(graph.getVertices("name", "aaaa")));
            Assert.assertEquals(10, count(graph.getVertices("name", "bbbb")));
            Assert.assertEquals(10, count(graph.getEdges("name", "cccc")));
            Iterator<Vertex> iter = graph.getVertices("name", "aaaa").iterator();
            //This will cause the transaction to be upgraded to a writable transaction.
            //I.e. iter's cursor gets closed
            graph.getEdges("name", "cccc").iterator().next().setProperty("name", "cccd");
            Vertex v = iter.next();
            Assert.assertEquals("aaaa", v.getProperty("name"));
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
            v1.setProperty("name", "aaaa");
            for (int i = 0; i < 10; i++) {
                Vertex v2 = graph.addVertex(null);
                v2.setProperty("name", "bbbb");
                Edge e = graph.addEdge(null, v1, v2, "label1");
                e.setProperty("name", "cccc");
            }
            graph.commit();

            Assert.assertEquals(11, count(graph.getVertices()));
            Assert.assertEquals(1, count(graph.getVertices("name", "aaaa")));
            Assert.assertEquals(10, count(graph.getVertices("name", "bbbb")));
            Assert.assertEquals(10, count(graph.getEdges("name", "cccc")));

            Iterator<Vertex> iter = graph.getVertices("name", "bbbb").iterator();
            Vertex v = iter.next();
            Assert.assertEquals(1L, v.getId());
            Assert.assertEquals("bbbb", v.getProperty("name"));
            //This will cause the transaction to be upgraded to a writable transaction.
            //I.e. iter's cursor gets closed
            v.setProperty("name", "bbbba");
            v = iter.next();
            Assert.assertEquals(2L, v.getId());
            Assert.assertEquals("bbbb", v.getProperty("name"));
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
            v1.setProperty("name", "aaaa");
            for (int i = 0; i < 10; i++) {
                Vertex v2 = graph.addVertex(null);
                v2.setProperty("name", "bbbb");
                Edge e = graph.addEdge(null, v1, v2, "label1");
                e.setProperty("name", "cccc");
            }
            graph.commit();

            Assert.assertEquals(11, count(graph.getVertices()));
            Assert.assertEquals(1, count(graph.getVertices("name", "aaaa")));
            Assert.assertEquals(10, count(graph.getVertices("name", "bbbb")));
            Assert.assertEquals(10, count(graph.getEdges("name", "cccc")));

            Iterator<Vertex> iter = graph.getVertices("name", "bbbb").iterator();
            Vertex v = iter.next();
            Assert.assertEquals(1L, v.getId());
            Assert.assertEquals("bbbb", v.getProperty("name"));
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
            v1.setProperty("name", "aaaa");
            for (int i = 0; i < 10; i++) {
                Vertex v2 = graph.addVertex(null);
                v2.setProperty("name", "bbbb");
                Edge e = graph.addEdge(null, v1, v2, "label1");
                e.setProperty("name", "cccc");
            }
            graph.commit();

            Assert.assertEquals(11, count(graph.getVertices()));
            Assert.assertEquals(1, count(graph.getVertices("name", "aaaa")));
            Assert.assertEquals(10, count(graph.getVertices("name", "bbbb")));
            Assert.assertEquals(10, count(graph.getEdges("name", "cccc")));

            Iterator<Vertex> iter = graph.getVertices("name", "bbbb").iterator();
            Vertex v = iter.next();
            v.setProperty("name", "bbbba");
            Assert.assertEquals(1L, v.getId());
            Assert.assertEquals("bbbba", v.getProperty("name"));
            iter.remove();
            Assert.assertNull(graph.getVertex(1L));
            Assert.assertEquals(9, count(iter));

            graph.commit();
            iter = graph.getVertices("name", "bbbb").iterator();
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
            v1.setProperty("name", "aaaa");
            for (int i = 0; i < 10; i++) {
                Vertex v2 = graph.addVertex(null);
                v2.setProperty("name", "bbbb");
                Edge e = graph.addEdge(null, v1, v2, "label1");
                e.setProperty("name", "cccc");
            }
            graph.commit();

            Assert.assertEquals(11, count(graph.getVertices()));
            Assert.assertEquals(1, count(graph.getVertices("name", "aaaa")));
            Assert.assertEquals(10, count(graph.getVertices("name", "bbbb")));
            Assert.assertEquals(10, count(graph.getEdges("name", "cccc")));

            Iterator<Vertex> iter = graph.getVertices("name", "bbbb").iterator();
            Vertex v = iter.next();
            v.setProperty("name", "bbbb");
            Assert.assertEquals(1L, v.getId());
            Assert.assertEquals("bbbb", v.getProperty("name"));
            iter.remove();
            Assert.assertNull(graph.getVertex(1L));
            Assert.assertEquals(9, count(iter));

            graph.commit();
            iter = graph.getVertices("name", "bbbb").iterator();
            Assert.assertEquals(9, count(iter));

        } finally {
            graph.shutdown();
        }
    }


}