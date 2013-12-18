package org.glmdb.blueprints.test._boolean;

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
public class IndexBooleanTest extends BaseGlmdbGraphTest {

    @Test
    public void testIndexBooleanOnVertex() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            thunderGraph.createKeyIndex("name1", Vertex.class);
            thunderGraph.createKeyIndex("name2", Vertex.class);
            thunderGraph.commit();

            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name1", true);
            v1.setProperty("name2", false);
            Vertex v2 = thunderGraph.addVertex(null);
            v2.setProperty("name1", true);
            v2.setProperty("name2", false);

            thunderGraph.commit();

            Set<String> indexedKeys = thunderGraph.getIndexedKeys(Vertex.class);
            Assert.assertEquals(2, indexedKeys.size());
            Assert.assertTrue(indexedKeys.contains("name1"));
            Assert.assertTrue(indexedKeys.contains("name2"));

            Iterable<Vertex> name11s = thunderGraph.getVertices("name1", true);
            Assert.assertEquals(2, countIter(name11s.iterator()));
            Iterable<Vertex> name21s = thunderGraph.getVertices("name1", false);
            Assert.assertEquals(0, countIter(name21s.iterator()));

            name11s = thunderGraph.getVertices("name2", true);
            Assert.assertEquals(0, countIter(name11s.iterator()));
            name21s = thunderGraph.getVertices("name2", false);
            Assert.assertEquals(2, countIter(name21s.iterator()));

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

            thunderGraph.printDb(DbEnum.EDGE_BOOLEAN_INDEX);

        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void dropBooleanIndexTest() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {
            thunderGraph.createKeyIndex("name1", Vertex.class);
            thunderGraph.commit();

            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name1", true);
            Vertex v2 = thunderGraph.addVertex(null);
            v2.setProperty("name1", true);
            Vertex v3 = thunderGraph.addVertex(null);
            v3.setProperty("name1", true);

            thunderGraph.commit();

            Assert.assertEquals(3, count(thunderGraph.getVertices("name1", true)));
            Assert.assertEquals(3, thunderGraph.getDbEntries(DbEnum.VERTEX_BOOLEAN_INDEX));

            thunderGraph.dropKeyIndex("name1", Vertex.class);

            thunderGraph.commit();

            //Still finds it just not via the index
            Assert.assertEquals(0, thunderGraph.getDbEntries(DbEnum.VERTEX_BOOLEAN_INDEX));
            Assert.assertEquals(3, count(thunderGraph.getVertices("name1", true)));
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
            v1.setProperty("name1", true);
            Vertex v2 = thunderGraph.addVertex(null);
            v2.setProperty("name1", true);
            Vertex v3 = thunderGraph.addVertex(null);
            v3.setProperty("name1", true);
            thunderGraph.commit();

            Assert.assertEquals(3, count(thunderGraph.getVertices("name1", true)));
            v1.setProperty("name1", false);
            thunderGraph.commit();

            Assert.assertEquals(2, count(thunderGraph.getVertices("name1", true)));
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

            thunderGraph.printDb(DbEnum.EDGE_BOOLEAN_INDEX);
            thunderGraph.dropKeyIndex("name1", Edge.class);
            thunderGraph.printDb(DbEnum.EDGE_BOOLEAN_INDEX);

        } finally {
            thunderGraph.shutdown();
        }
    }

    @Test
    public void testReindexOnVertex() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {

            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name1", true);
            Vertex v2 = thunderGraph.addVertex(null);
            v2.setProperty("name1", true);
            Vertex v3 = thunderGraph.addVertex(null);
            v3.setProperty("name1", true);
            thunderGraph.commit();

            Assert.assertEquals(3, count(thunderGraph.getVertices("name1", true)));
            Assert.assertEquals(0, thunderGraph.getDbEntries(DbEnum.VERTEX_BOOLEAN_INDEX));

            thunderGraph.createKeyIndex("name1", Vertex.class);
            Assert.assertEquals(3, count(thunderGraph.getVertices("name1", true)));
            Assert.assertEquals(3, thunderGraph.getDbEntries(DbEnum.VERTEX_BOOLEAN_INDEX));

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
            thunderGraph.printDb(DbEnum.EDGE_BOOLEAN_INDEX);

            thunderGraph.createKeyIndex("name1", Edge.class);
            Assert.assertEquals(3, count(thunderGraph.getEdges("name1", true)));
            thunderGraph.printDb(DbEnum.EDGE_BOOLEAN_INDEX);

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
            v1.setProperty("name", true);
            thunderGraph.commit();
            Assert.assertEquals(1, thunderGraph.getDbEntries(DbEnum.VERTEX_BOOLEAN_INDEX));

            v1.remove();
            thunderGraph.commit();
            Assert.assertEquals(0, thunderGraph.getDbEntries(DbEnum.VERTEX_BOOLEAN_INDEX));
        } finally {
            thunderGraph.shutdown();
        }

    }

}