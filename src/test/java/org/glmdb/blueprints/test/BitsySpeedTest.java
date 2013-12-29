package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import org.apache.commons.io.FileUtils;
import org.glmdb.blueprints.ThunderGraph;
import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.io.File;
import java.io.IOException;
import java.util.*;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Date: 2013/12/26
 * Time: 1:18 PM
 */
public class BitsySpeedTest extends BaseGlmdbGraphTest {

    ThunderGraph graph;
    File dbPath = null;
    static final String PATH = "/tmp/testdb";
    private Throwable toThrow;
    Random rand = new Random();

    @Before
    public void before() throws IOException {
        this.dbPath = new File(PATH);
        FileUtils.deleteDirectory(this.dbPath);
        this.dbPath.mkdir();
        graph = new ThunderGraph(this.dbPath);
    }


    @After
    public void after() {
        graph.shutdown();
    }

    //    @Test
    public void testMultiThreadedCommits() throws Exception {
        int NUMBER_OF_RETRIES = 3;
        int SCALE_UP_TO_NUMBER_OF_REQUEST = 3;
        for (int k = 1; k <= SCALE_UP_TO_NUMBER_OF_REQUEST; k++) {
            for (int m = 1; m <= NUMBER_OF_RETRIES; m++) {
                for (int numThreads : new int[]{k}) {
                    final int numVerticesPerThread = 1000000 / numThreads;
                    int numElements = 2 * numVerticesPerThread * numThreads;

                    ExecutorService service = Executors.newFixedThreadPool(7);

                    final Object[] startVertex = new Object[numThreads];

                    System.out.println("numThreads = " + numThreads);

                    final CountDownLatch cdl = new CountDownLatch(numThreads);
                    long ts = System.currentTimeMillis();
                    for (int i = 0; i < numThreads; i++) {
                        final int tid = i;
                        service.submit(new Runnable() {
                            @Override
                            public void run() {
                                Object prevId = null;
                                for (int j = 0; j < numVerticesPerThread; j++) {
                                    Vertex v = graph.addVertex(null);
                                    if (prevId == null) {
                                        startVertex[tid] = v.getId();
                                    } else {
                                        Vertex prevV = graph.getVertex(prevId);
                                        graph.addEdge(null, prevV, v, "test");
                                    }
                                    graph.commit();

                                    prevId = v.getId();
                                }

                                cdl.countDown();
                            }
                        });
                    }

                    cdl.await();

                    double duration = System.currentTimeMillis() - ts;
                    System.out.println("Took " + duration + "ms to save " + numElements + " vertices+edges. Rate = " + (duration / numElements) + "ms per vertex. TPS = " + ((double) numElements * 1000 / duration));

                    // Wait 10 seconds between tests
                    Thread.sleep(10000);

                    final CountDownLatch cdl2 = new CountDownLatch(numThreads);
                    ts = System.currentTimeMillis();
                    for (int i = 0; i < numThreads; i++) {
                        final int tid = i;
                        service.submit(new Runnable() {
                            @Override
                            public void run() {
                                for (int k = 0; k < 1; k++) {
                                    int count = 0;
                                    Vertex v = graph.getVertex(startVertex[tid]);

                                    Edge e;
                                    do {
                                        Iterator<Edge> eIter = v.getEdges(Direction.OUT).iterator();
                                        if (!eIter.hasNext()) {
                                            break;
                                        } else {
                                            count++;
                                            v = eIter.next().getVertex(Direction.IN);
                                        }
                                    } while (true);

                                    if (numVerticesPerThread != count + 1) {
                                        System.out.println("Mistmatch between " + numVerticesPerThread + " and " + count);
                                    }

                                    graph.commit();
                                }

                                cdl2.countDown();
                            }
                        });
                    }

                    cdl2.await();

                    duration = System.currentTimeMillis() - ts;
                    System.out.println("Took " + duration + "ms to query " + numElements + " vertices+edge. Rate = " + (duration / numElements) + "ms per vertex. TPS = " + ((double) numElements * 1000 / duration));

                    service.shutdown();
                    after();
                    before();

                }
            }
        }
    }

//    @Test
    public void testMultiThreadedReadsOnBipartiteGraph() throws Exception {
        final int numVertices = 1000000; // 100K vertices
        final int numIters = 100000;
        final int numElements = 8 * numIters; // expected to visit 8 v/e per iteration
        final int partSize = numVertices / 2;
        final int numPerCommit = 1000;

        final String label = "test";
        final Object[] outVertices = new Object[partSize];
        final Object[] inVertices = new Object[partSize];

        // Vertices
        for (int i = 0; i < partSize; i++) {
            outVertices[i] = graph.addVertex(null).getId();
            inVertices[i] = graph.addVertex(null).getId();

            if (i % numPerCommit == 0) {
                graph.commit();
            }
        }

        // Edges
        for (int i = 0; i < partSize; i++) {
            Vertex outVertex = graph.getVertex(outVertices[i]);
            outVertex.addEdge(label, graph.getVertex(inVertices[(5 * i + 1) % partSize]));
            outVertex.addEdge(label, graph.getVertex(inVertices[(5 * i + 4) % partSize]));
            outVertex.addEdge(label, graph.getVertex(inVertices[(5 * i + 7) % partSize]));

            if (i % numPerCommit == 0) {
                graph.commit();
            }
        }
        graph.commit();

        final int numRuns = 3;
        Map<Integer, String> calcStrMap = new HashMap<Integer, String>();

        for (int run = 0; run < numRuns; run++) {
//            ((BitsyGraph)graph).setDefaultIsolationLevel(BitsyIsolationLevel.READ_COMMITTED);
            for (final int numThreads : new int[]{1/*, 2, 3, 4, 5, 10, 25, 50, 100, 150, 250, 500, 750, 1000*/}) {
                ExecutorService service = Executors.newFixedThreadPool(numThreads);

                final CountDownLatch cdl = new CountDownLatch(numThreads);
                long ts = System.currentTimeMillis();

//                ((BitsyGraph)graph).setDefaultIsolationLevel(BitsyIsolationLevel.READ_COMMITTED);
                System.out.println("Running bi-partite read test with " + numThreads + " threads");
                for (int i = 0; i < numThreads; i++) {
                    final int tid = i;
                    System.out.println("Scheduling read work for thread " + tid);
                    service.submit(new Runnable() {
                        @Override
                        public void run() {
                            try {
                                Vertex v = graph.getVertex(outVertices[0]);
                                long startTime = System.currentTimeMillis();
//                                for (int k = 0; k < 1 * numIters / numThreads; k++) {
                                for (int k = 0; k < 100 * numIters / numThreads; k++) {
                                    Assert.assertNotNull(v);

                                    Vertex nextV = randomVertex(v.getVertices(Direction.OUT, label));

                                    Assert.assertNotNull(nextV);

                                    // Take a random edge back
                                    Vertex backV = randomVertex(nextV.getVertices(Direction.IN));
                                    if (backV != null) {
                                        v = backV;
                                    }
                                    if (k % 1000000 == 0) {
                                        long endTime = System.currentTimeMillis();
                                        System.out.println(endTime - startTime);
                                        startTime = endTime;
                                    }
                                }

                                System.out.println("Thread " + tid + " is done");
                            } catch (Throwable t) {
                                setException(t);
                            } finally {
                                cdl.countDown();
                            }
                        }

                        private Vertex randomVertex(Iterable<Vertex> vertices) {
                            List<Vertex> options = new ArrayList<Vertex>();
                            for (Vertex option : vertices) {
                                options.add(option);
                            }

                            if (options.isEmpty()) {
                                return null;
                            } else {
                                return options.get(rand.nextInt(options.size()));
                            }
                        }

                    });
                }

                cdl.await();

                if (getException() != null) {
                    throw new RuntimeException("Error in testMultiThreadedReadsOnBipartiteGraph", getException());
                }

                service.shutdown();

                long duration = System.currentTimeMillis() - ts;
                double tps = ((double) numElements * 100000 / duration);
                System.out.println("Took " + duration + "ms to query " + numElements + " vertices+edge 100 times. Rate = " + (duration / numElements) + "ms per vertex. TPS = " + tps);

                String calcStr = calcStrMap.get(numThreads);
                if (calcStr == null) {
                    calcStrMap.put(numThreads, "=(" + tps);
                } else {
                    calcStrMap.put(numThreads, calcStr + " + " + tps);
                }
            }
        }

        for (Map.Entry<Integer, String> entry : calcStrMap.entrySet()) {
            System.out.println(entry.getKey() + ": " + entry.getValue() + ")/3");
        }

//        ((BitsyGraph)graph).setDefaultIsolationLevel(BitsyIsolationLevel.REPEATABLE_READ);
    }

    private void setException(Throwable t) {
        this.toThrow = t;
    }

    private Throwable getException() {
        return toThrow;
    }
}
