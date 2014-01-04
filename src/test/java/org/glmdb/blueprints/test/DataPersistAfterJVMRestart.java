package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Vertex;
import org.apache.commons.io.FileUtils;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.jni.DbEnum;
import org.junit.Test;

import java.io.File;
import java.io.IOException;

/**
 * Date: 2014/01/03
 * Time: 4:29 PM
 */
public class DataPersistAfterJVMRestart {

    protected File dbPath = null;
    protected static final String PATH = "/tmp/testdb";

//    @Test
    public void testGraphDataPersists1() throws IOException {
        this.dbPath = new File(PATH);
        FileUtils.deleteDirectory(this.dbPath);
        this.dbPath.mkdir();
        ThunderGraph graph = new ThunderGraph(PATH);
        try {
            Vertex v1 = graph.addVertex(null);
            Vertex v2 = graph.addVertex(null);
            graph.addEdge(null, v1, v2, "label1");
            graph.addEdge(null, v1, v2, "label2");
            graph.commit();
        } finally {
            graph.shutdown();
        }
    }

//    @Test
    public void testGraphDataPersists2() {
        ThunderGraph graph = new ThunderGraph(PATH);
        try {
            graph.printDb(DbEnum.LABEL_DB);
        } finally {
            graph.shutdown();
        }
    }


}
