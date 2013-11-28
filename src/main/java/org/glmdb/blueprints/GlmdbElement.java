package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Element;

import java.util.Set;

/**
 * Date: 2013/11/17
 * Time: 4:06 PM
 */
public abstract class GlmdbElement implements Element {

    protected GlmdbGraph glmdbGraph;
    protected long id;

    public GlmdbElement(GlmdbGraph glmdbGraph, long id) {
        this.glmdbGraph = glmdbGraph;
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
