package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.jni.DbEnum;
import org.junit.Assert;
import org.junit.Test;

/**
 * Date: 2013/12/08
 * Time: 5:21 PM
 */
public class DataPersistTest extends BaseGlmdbGraphTest  {

    @Test
    public void testGraphDataPersists() {
        ThunderGraph graph = new ThunderGraph(this.dbPath);
        if (graph.getFeatures().isPersistent) {

            Vertex v = graph.addVertex(null);
            Vertex u = graph.addVertex(null);
            if (graph.getFeatures().supportsVertexProperties) {
                v.setProperty("name", "marko");
                u.setProperty("name", "pavel");
            }
            Edge e = graph.addEdge(null, v, u, "collaborator");
            if (graph.getFeatures().supportsEdgeProperties)
                e.setProperty("location", "internet");

            if (graph.getFeatures().supportsVertexIteration) {
                Assert.assertEquals(count(graph.getVertices()), 2);
            }
            if (graph.getFeatures().supportsEdgeIteration) {
                Assert.assertEquals(count(graph.getEdges()), 1);
            }

            graph.shutdown();

            graph = new ThunderGraph(this.dbPath);
            if (graph.getFeatures().supportsVertexIteration) {
                Assert.assertEquals(count(graph.getVertices()), 2);
                if (graph.getFeatures().supportsVertexProperties) {
                    for (Vertex vertex : graph.getVertices()) {
                        Assert.assertTrue(vertex.getProperty("name").equals("marko") || vertex.getProperty("name").equals("pavel"));
                    }
                }
            }
            if (graph.getFeatures().supportsEdgeIteration) {
                Assert.assertEquals(count(graph.getEdges()), 1);
                for (Edge edge : graph.getEdges()) {
                    Assert.assertEquals(edge.getLabel(), "collaborator");
                    if (graph.getFeatures().supportsEdgeProperties)
                        Assert.assertEquals(edge.getProperty("location"), "internet");
                }
            }

        }
        graph.commit();
//        graph.printDb(DbEnum.VERTEX_DB);
//        graph.printDb(DbEnum.EDGE_DB);
//        graph.printDb(DbEnum.VERTEX_PROPERTY_DB);
//        graph.printDb(DbEnum.EDGE_PROPERTY_DB);
//        graph.printDb(DbEnum.LABEL_DB);
        graph.printDb(DbEnum.CONFIG_DB);
        graph.shutdown();
    }
}
