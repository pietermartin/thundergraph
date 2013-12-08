package org.glmdb.blueprints.test;

import junit.framework.Assert;
import org.glmdb.blueprints.ThunderGraph;
import org.junit.Test;

/**
 * Date: 2013/12/08
 * Time: 1:37 AM
 */
public class ThunderGraphToStringTest extends BaseGlmdbGraphTest {

    @Test
    public void testPath() {
        ThunderGraph thunderGraph = new ThunderGraph(this.dbPath);
        Assert.assertEquals(PATH, thunderGraph.getDbPath());
        thunderGraph.shutdown();
    }
}
