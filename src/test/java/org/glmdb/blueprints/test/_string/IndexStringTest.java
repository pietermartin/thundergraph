package org.glmdb.blueprints.test._string;

import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.jni.DbEnum;
import org.glmdb.blueprints.test.BaseGlmdbGraphTest;
import org.junit.Assert;
import org.junit.Test;

import java.util.Set;

/**
 * Date: 2013/12/14
 * Time: 8:35 PM
 */
public class IndexStringTest extends BaseGlmdbGraphTest {

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
    public void testIndexStringOnEdge() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            thunderGraph.createKeyIndex("name1", Edge.class);
            Vertex v1 = thunderGraph.addVertex(null);
            Vertex v2 = thunderGraph.addVertex(null);
            Vertex v3 = thunderGraph.addVertex(null);
            Edge e1 = v1.addEdge("edge1", v2);
            e1.setProperty("name1", "aaaa");
            Edge e2 = v1.addEdge("edge1", v3);
            e2.setProperty("name1", "aaaa");
            thunderGraph.commit();

            Assert.assertEquals(1, thunderGraph.getIndexedKeys(Edge.class).size());
            Assert.assertEquals(0, count(thunderGraph.getEdges("name", "aaaa").iterator()));
            Assert.assertEquals(2, count(thunderGraph.getEdges("name1", "aaaa").iterator()));
            Assert.assertEquals(0, count(thunderGraph.getEdges("name1", "bbbb").iterator()));

            thunderGraph.printDb(DbEnum.EDGE_STRING_INDEX);

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
            e1.setProperty("name1", "aaaa");
            e2.setProperty("name1", "aaaa");
            e3.setProperty("name1", "aaaa");
            thunderGraph.commit();

            Assert.assertEquals(3, count(thunderGraph.getEdges("name1", "aaaa")));
            e1.setProperty("name1", "bbbb");
            thunderGraph.commit();

            Assert.assertEquals(2, count(thunderGraph.getEdges("name1", "aaaa")));
            e2.setProperty("name1", "bbbb");
            thunderGraph.commit();

            Assert.assertEquals(1, count(thunderGraph.getEdges("name1", "aaaa")));
            e3.setProperty("name1", "bbbb");
            thunderGraph.commit();

            Assert.assertEquals(0, count(thunderGraph.getEdges("name1", "aaaa")));
            Assert.assertEquals(3, count(thunderGraph.getEdges("name1", "bbbb")));

            thunderGraph.printDb(DbEnum.EDGE_STRING_INDEX);
            thunderGraph.dropKeyIndex("name1", Edge.class);
            thunderGraph.printDb(DbEnum.EDGE_STRING_INDEX);

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

            e1.setProperty("name1", "aaaa1");
            e2.setProperty("name1", "aaaa1");
            e3.setProperty("name1", "aaaa1");

            thunderGraph.commit();

            Assert.assertEquals(3, count(thunderGraph.getEdges("name1", "aaaa1")));
            thunderGraph.printDb(DbEnum.EDGE_STRING_INDEX);

            thunderGraph.createKeyIndex("name1", Edge.class);
            Assert.assertEquals(3, count(thunderGraph.getEdges("name1", "aaaa1")));
            thunderGraph.printDb(DbEnum.EDGE_STRING_INDEX);

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

}