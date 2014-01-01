package org.glmdb.blueprints.test.performance;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Vertex;
import junit.framework.Assert;
import org.apache.commons.lang.time.StopWatch;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.test.BaseGlmdbGraphTest;
import org.junit.Test;

import java.util.Iterator;

/**
 * Date: 2013/12/30
 * Time: 4:44 PM
 */
public class IndexSpeedTest extends BaseGlmdbGraphTest {

//    @Test
    public void testIndexSpeed() {
        ThunderGraph g = new ThunderGraph(this.dbPath);
        try {

            g.createKeyIndex("many", Vertex.class);

            int NUMBER_TO_ITER = 10000000;

            StopWatch stopWatch = new StopWatch();
            stopWatch.start();

            Vertex one = g.addVertex(null);
            one.setProperty("one", -1);
            long previousSplitTime = 0;
            for (int i = 0; i < NUMBER_TO_ITER; i++) {
                Vertex many = g.addVertex(null);
                many.setProperty("many", i);
                g.addEdge(null, one, many, "toMany");

                if (i != 0 && i % 1000000 == 0) {
                    stopWatch.split();
                    long splitTime = stopWatch.getSplitTime();
                    System.out.println(i + " " + stopWatch.toString() + " 100000 in " + (splitTime - previousSplitTime));
                    previousSplitTime = stopWatch.getSplitTime();
                    g.commit();
                }
            }
            g.commit();
            stopWatch.stop();
            System.out.println("write " + NUMBER_TO_ITER + " = " + stopWatch.toString());

            stopWatch.reset();
            stopWatch.start();

            for (int i = 0; i < NUMBER_TO_ITER; i++) {
                Iterator<Vertex> iter = g.getVertices("many", i).iterator();
                Assert.assertTrue(iter.hasNext());

                if (i != 0 && i % 1000000 == 0) {
                    stopWatch.split();
                    long splitTime = stopWatch.getSplitTime();
                    System.out.println(i + " " + stopWatch.toString() + " 1000000 in " + (splitTime - previousSplitTime));
                    previousSplitTime = stopWatch.getSplitTime();
                }

            }

            stopWatch.stop();
            System.out.println("read " + NUMBER_TO_ITER + " = " + stopWatch.toString());
        } finally {
            g.shutdown();
        }
    }

}
