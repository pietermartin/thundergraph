package org.glmdb.blueprints.test.performance;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Vertex;
import junit.framework.Assert;
import org.apache.commons.io.FileUtils;
import org.apache.commons.lang.time.StopWatch;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.test.BaseGlmdbGraphTest;
import org.junit.Test;

import java.io.File;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Date: 2013/12/02
 * Time: 10:02 PM
 */
public class SpeedTest extends BaseGlmdbGraphTest {

//    @Test
    public void testSpeedDude1() {
        ThunderGraph g = new ThunderGraph(this.dbPath);
        try {

            int NUMBER_TO_ITER = 10000000;

            StopWatch stopWatch = new StopWatch();
            stopWatch.start();

            Vertex one = g.addVertex(null);
            one.setProperty("one", "1");
            long previousSplitTime = 0;
            for (int i = 0; i < NUMBER_TO_ITER; i++) {
                Vertex many = g.addVertex(null);
                many.setProperty("many", "2");
                g.addEdge(null, one, many, "toMany");

                if (i != 0 && i % 1000000 == 0) {
                    stopWatch.split();
                    long splitTime = stopWatch.getSplitTime();
                    System.out.println(i + " " + stopWatch.toString() + " 1000000 in " + (splitTime - previousSplitTime));
                    previousSplitTime = stopWatch.getSplitTime();
                    g.commit();
                }
            }
            g.commit();
            stopWatch.stop();
            System.out.println("write " + NUMBER_TO_ITER + " = " + stopWatch.toString());

            stopWatch.reset();
            stopWatch.start();
            int count = 1;
            Vertex startV = g.getVertex(one.getId());
            for (Vertex v : startV.getVertices(Direction.OUT)) {
                v.getProperty("many");
                if (count++ % 1000000 == 0) {
                    System.out.println("read 1000000 vertex, id = " + v.getId());
                }
            }
            stopWatch.stop();
            System.out.println("read " + NUMBER_TO_ITER + " = " + stopWatch.toString());
        } finally {
            g.shutdown();
        }
    }

    //    @Test
    public void testSpeedDude2() throws IOException {
        ThunderGraph g = new ThunderGraph(this.dbPath);
        try {
            int NUMBER_TO_ITER = 10000000;

            StopWatch stopWatch = new StopWatch();
            stopWatch.start();

            Object[] ids = new Object[(NUMBER_TO_ITER / 10) + 1];
            int objectIdCount = 0;

            Vertex previous = g.addVertex(null);
            previous.setProperty("one", "1");
            ids[objectIdCount++] = previous.getId();
            long previousSplitTime = 0;
            for (int i = 1; i <= NUMBER_TO_ITER; i++) {
                Vertex many = g.addVertex(null);
                many.setProperty("many", i);
                g.addEdge(null, previous, many, "toMany");

                if (i != 0 && i % 10 == 0) {
                    previous = many;
                    ids[objectIdCount++] = previous.getId();
                }

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
            previousSplitTime = 0;
            int count = 0;
            for (Object id : ids) {
                count++;
                Vertex vertex = g.getVertex(id);

                for (Vertex v : vertex.getVertices(Direction.OUT, "toMany")) {
                    v.getProperty("many");
                }
                if (count == ids.length) {
                    Assert.assertEquals(0, count(vertex.getVertices(Direction.OUT, "toMany")));
                } else {
                    Assert.assertEquals(10, count(vertex.getVertices(Direction.OUT, "toMany")));
                }

                for (Vertex v : vertex.getVertices(Direction.OUT)) {
                    v.getProperty("many");
                }
                if (count == ids.length) {
                    Assert.assertEquals(0, count(vertex.getVertices(Direction.OUT)));
                } else {
                    Assert.assertEquals(10, count(vertex.getVertices(Direction.OUT)));
                }

                if (count % 100000 == 0) {
                    stopWatch.split();
                    long splitTime = stopWatch.getSplitTime();
                    System.out.println(id + " " + stopWatch.toString() + " 100000 in " + (splitTime - previousSplitTime));
                    previousSplitTime = stopWatch.getSplitTime();
                }
            }
            stopWatch.stop();
            System.out.println("read 10000000 = " + stopWatch.toString());
        } finally {
            g.shutdown();
        }
    }

    //    @Test
    public void testSpeedLinkedList() {
        ThunderGraph g = new ThunderGraph(this.dbPath);
        try {

            int NUMBER_TO_ITER = 10000000;

            StopWatch stopWatch = new StopWatch();
            stopWatch.start();

            Vertex one = g.addVertex(null);
            Vertex start = one;
            one.setProperty("one", "1");
            StringBuilder sb = new StringBuilder();
            sb.append("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
            sb.append("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
            sb.append("cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc");
            sb.append("dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd");
            sb.append("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");
            long previousSplitTime = 0;
            for (int i = 0; i < NUMBER_TO_ITER; i++) {
                Vertex many = g.addVertex(null);
                many.setProperty("many1", sb.toString());
                many.setProperty("many2", sb.toString());
                many.setProperty("many3", sb.toString());
                many.setProperty("many4", sb.toString());
                many.setProperty("many5", sb.toString());
                g.addEdge(null, one, many, "toMany");
                one = many;

                if (i != 0 && i % 10000 == 0) {
                    g.commit();
                }
                if (i != 0 && i % 1000000 == 0) {
                    stopWatch.split();
                    long splitTime = stopWatch.getSplitTime();
                    System.out.println(i + " " + stopWatch.toString() + " 100000 in " + (splitTime - previousSplitTime));
                    previousSplitTime = stopWatch.getSplitTime();
                }
            }
            g.commit();
            stopWatch.stop();
            System.out.println("write 10000000 = " + stopWatch.toString());

            stopWatch.reset();
            stopWatch.start();
            int count = 1;
            Vertex startV = g.getVertex(start.getId());
            Iterator<Vertex> vertices = startV.getVertices(Direction.OUT).iterator();
            while (vertices.hasNext()) {
                Vertex next = vertices.next();
                Assert.assertEquals(sb.toString(), next.getProperty("many1"));
                vertices.hasNext();
                vertices = next.getVertices(Direction.OUT).iterator();
                if (count++ % 1000000 == 0) {
                    System.out.println("next vertex id = " + next.getId());
                }
            }

            stopWatch.stop();
            System.out.println("read " + NUMBER_TO_ITER + " = " + stopWatch.toString());
        } finally {
            g.shutdown();
        }
    }

}
