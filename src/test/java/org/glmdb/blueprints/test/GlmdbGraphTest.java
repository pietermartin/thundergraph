package org.glmdb.blueprints.test;

import org.apache.commons.io.FileUtils;
import org.glmdb.blueprints.GlmdbGraph;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import java.io.File;
import java.io.IOException;

/**
 * Date: 2013/11/19
 * Time: 11:24 PM
 */
public class GlmdbGraphTest {

    File dbPath = null;

    @Before
    public void beforeTests() throws IOException {
        this.dbPath = new File("/tmp/testdb");
        FileUtils.deleteDirectory(this.dbPath);
        this.dbPath.mkdir();
    }

    @Test
    public void testOpenGraph() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        glmdbGraph.shutdown();
    }

    @Test
    public void testAddVertex() {
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        glmdbGraph.addVertex(null);
        glmdbGraph.commit();
        glmdbGraph.shutdown();
    }

}
