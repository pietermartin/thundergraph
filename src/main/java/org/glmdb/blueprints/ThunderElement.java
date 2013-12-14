package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Element;

/**
 * Date: 2013/11/17
 * Time: 4:06 PM
 */
public abstract class ThunderElement implements Element {

    protected ThunderGraph thunderGraph;
    protected long id;

    public ThunderElement(ThunderGraph thunderGraph, long id) {
        this.thunderGraph = thunderGraph;
        this.id = id;
    }

    @Override
    public Object getId() {
        return this.id;
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof ThunderElement) {
            return ((ThunderElement)o).getId().equals(getId());
        } else {
            return false;
        }
    }

    @Override
    public int hashCode() {
        return getId().hashCode();
    }

}
