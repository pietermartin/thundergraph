package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.*;
import com.tinkerpop.blueprints.impls.GraphTest;
import junit.framework.Assert;
import org.apache.commons.io.FileUtils;
import org.glmdb.blueprints.ThunderGraph;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.Method;

/**
 * Date: 2013/12/07
 * Time: 12:01 AM
 */
public class BlueprintsTest
        extends GraphTest
{

    public void testVertexTestSuite() throws Exception {
        this.stopWatch();
        doTestSuite(new VertexTestSuite(this));
        printTestPerformance("VertexTestSuite", this.stopWatch());
    }

    public void testEdgeTestSuite() throws Exception {
        this.stopWatch();
        doTestSuite(new EdgeTestSuite(this));
        printTestPerformance("EdgeTestSuite", this.stopWatch());
    }

    public void testGraphTestSuite() throws Exception {
        this.stopWatch();
        doTestSuite(new GraphTestSuite(this));
        printTestPerformance("GraphTestSuite", this.stopWatch());
    }

    public void testKeyIndexableGraphTestSuite() throws Exception {
        this.stopWatch();
        doTestSuite(new KeyIndexableGraphTestSuite(this));
        printTestPerformance("KeyIndexableGraphTestSuite", this.stopWatch());
    }

//    public void testIndexableGraphTestSuite() throws Exception {
//        this.stopWatch();
//        doTestSuite(new IndexableGraphTestSuite(this));
//        printTestPerformance("IndexableGraphTestSuite", this.stopWatch());
//    }

    public void testIndexTestSuite() throws Exception {
        this.stopWatch();
        doTestSuite(new IndexTestSuite(this));
        printTestPerformance("IndexTestSuite", this.stopWatch());
    }

//    public void testGraphMLReaderTestSuite() throws Exception {
//        this.stopWatch();
//        doTestSuite(new GraphMLReaderTestSuite(this));
//        printTestPerformance("GraphMLReaderTestSuite", this.stopWatch());
//    }
//
//    public void testGMLReaderTestSuite() throws Exception {
//        this.stopWatch();
//        doTestSuite(new GMLReaderTestSuite(this));
//        printTestPerformance("GMLReaderTestSuite", this.stopWatch());
//    }
//
//    public void testGraphSONReaderTestSuite() throws Exception {
//        this.stopWatch();
//        doTestSuite(new GraphSONReaderTestSuite(this));
//        printTestPerformance("GraphSONReaderTestSuite", this.stopWatch());
//    }

    public Graph generateGraph() {
        File dbPath = new File("/tmp/thundergraph");
        try {
            FileUtils.deleteDirectory(dbPath);
        } catch (IOException e) {
            Assert.fail(e.getMessage());
        }
        dbPath.mkdir();
        return new ThunderGraph(dbPath);
    }

    @Override
    public Graph generateGraph(String graphDirectoryName) {
        File dbPath = new File(graphDirectoryName);
        try {
            FileUtils.deleteDirectory(dbPath);
        } catch (IOException e) {
            Assert.fail(e.getMessage());
        }
        dbPath.mkdir();
        return new ThunderGraph(dbPath);
    }

    public void doTestSuite(final TestSuite testSuite) throws Exception {
        String doTest = System.getProperty("testTinkerGraph");
        if (doTest == null || doTest.equals("true")) {
            for (Method method : testSuite.getClass().getDeclaredMethods()) {
                if (method.getName().startsWith("test")) {
                    System.out.println("Testing " + method.getName() + "...");
                    method.invoke(testSuite);
                }
            }
        }
    }
}
