package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Element;

/**
 * Date: 2013/11/17
 * Time: 4:06 PM
 */
public abstract class GlmdbElement implements Element {

    protected ThunderGraph thunderGraph;
    protected long id;

    public GlmdbElement(ThunderGraph thunderGraph, long id) {
        this.thunderGraph = thunderGraph;
        this.id = id;
    }

    @Override
    public Object getId() {
        return this.id;
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof GlmdbElement) {
            return ((GlmdbElement)o).getId().equals(getId());
        } else {
            return false;
        }
    }

    @Override
    public int hashCode() {
        return getId().hashCode();
    }

}
