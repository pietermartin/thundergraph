package org.glmdb.blueprints.test._string;

import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.test.BaseGlmdbGraphTest;
import org.junit.Test;

import java.util.Iterator;

/**
 * Date: 2013/12/20
 * Time: 7:11 PM
 */
public class EdgeStringIterTest extends BaseGlmdbGraphTest {

    @Test
    public void testEdgeStringIterRemove() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        try {

            Vertex v1 = thunderGraph.addVertex(null);
            v1.setProperty("name", "name1");
            for (int i = 0; i < 60; i++) {
                Vertex v2 = thunderGraph.addVertex(null);
                Edge e = v1.addEdge("label1", v2);
                e.setProperty("name", "name1");
                e.setProperty("name1", "name" + i);
            }

            int count = 0;
            Iterator<Edge> edgeIter =  thunderGraph.getEdges("name", "name1").iterator();
            while (edgeIter.hasNext()) {
                Edge e = edgeIter.next();
                System.out.println(count++ + " " + e.getProperty("name1"));
                edgeIter.remove();
            }

//            for (Edge e: thunderGraph.getEdges("name", "name1")) {
//                System.out.println(count++ + " " + e.getProperty("name"));
//                e.remove();
//            }

        } finally {
            thunderGraph.shutdown();
        }
    }

}