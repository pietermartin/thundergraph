package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Element;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.Glmdb;
import org.glmdb.blueprints.jni.Transaction;

import java.util.Set;

/**
 * Date: 2013/11/17
 * Time: 4:06 PM
 */
public abstract class GlmdbElement implements Element {

    protected Glmdb glmdb;
    protected Transaction txn;
    protected Cursor cursor;
    protected long id;

    public GlmdbElement(Glmdb glmdb, Transaction txn, Cursor cursor, long id) {
        this.glmdb = glmdb;
        this.txn = txn;
        this.cursor = cursor;
        this.id = id;
    }

    @Override
    public Set<String> getPropertyKeys() {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public <T> T removeProperty(String key) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public void remove() {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public Object getId() {
        return this.id;
    }
}
