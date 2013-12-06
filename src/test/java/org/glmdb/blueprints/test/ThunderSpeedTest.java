package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Vertex;
import org.apache.commons.lang.time.StopWatch;
import org.glmdb.blueprints.ThunderGraph;
import org.junit.Test;

/**
 * Date: 2013/12/02
 * Time: 10:02 PM
 */
public class ThunderSpeedTest extends BaseGlmdbGraphTest {

    @Test
    public void testSpeedDude() {
        ThunderGraph g = new ThunderGraph(this.dbPath);
        StopWatch stopWatch = new StopWatch();
        stopWatch.start();

        Vertex one = g.addVertex(null);
        one.setProperty("one", "1");
        long previousSplitTime = 0;
        for (int i = 0; i < 10000; i++) {
            Vertex many = g.addVertex(null);
            many.setProperty("many", "2");
            g.addEdge(null, one, many, "toMany");

            if (i != 0 && i % 100000 == 0) {
                stopWatch.split();
                long splitTime = stopWatch.getSplitTime();
                System.out.println(i + " " + stopWatch.toString() + " 100000 in " + (splitTime - previousSplitTime));
                previousSplitTime = stopWatch.getSplitTime();
                g.commit();
            }
        }
        g.commit();
        stopWatch.stop();
        System.out.println(stopWatch.toString());

        stopWatch.reset();
        stopWatch.start();
        Vertex startV = g.getVertex(0L);
        for (Vertex v : startV.getVertices(Direction.OUT, "toMany")) {
            v.getProperty("many");
        }
        stopWatch.stop();
        System.out.println(stopWatch.toString());
        g.shutdown();
    }
}
