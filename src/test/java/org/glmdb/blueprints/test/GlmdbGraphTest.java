package org.glmdb.blueprints.test;

import com.tinkerpop.blueprints.Vertex;
import org.apache.commons.io.FileUtils;
import org.glmdb.blueprints.GlmdbGraph;
import org.glmdb.blueprints.GlmdbVertex;
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
        long start = System.currentTimeMillis();
        System.out.println();
        GlmdbGraph glmdbGraph = new GlmdbGraph(this.dbPath);
        for (int i = 0; i < 1000000; i++) {
            Vertex vertex = glmdbGraph.addVertex(null);
            vertex = glmdbGraph.addVertex(null);
        }
        glmdbGraph.commit();
        long end = System.currentTimeMillis();
        System.out.println("Time taken: " + String.valueOf(end - start));
        glmdbGraph.shutdown();
    }

}
