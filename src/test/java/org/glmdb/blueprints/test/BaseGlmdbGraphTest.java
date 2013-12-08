package org.glmdb.blueprints.test;

import org.apache.commons.io.FileUtils;
import org.junit.Before;

import java.io.File;
import java.io.IOException;
import java.util.Iterator;

/**
 * Date: 2013/11/24
 * Time: 11:01 AM
 */
public abstract class BaseGlmdbGraphTest {

    protected File dbPath = null;
    protected static final String PATH = "/tmp/testdb";

    @Before
    public void beforeTests() throws IOException {
        this.dbPath = new File(PATH);
        FileUtils.deleteDirectory(this.dbPath);
        this.dbPath.mkdir();
    }

    protected int countIter(Iterator iter) {
        int count = 0;
        while (iter.hasNext()) {
            count++;
            iter.next();
        }
        return count;
    }

    public static int count(final Iterable iterable) {
        return count(iterable.iterator());
    }

    public static int count(final Iterator iterator) {
        int counter = 0;
        while (iterator.hasNext()) {
            iterator.next();
            counter++;
        }
        return counter;
    }
}
