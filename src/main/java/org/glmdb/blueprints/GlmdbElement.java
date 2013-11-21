package org.glmdb.blueprints;

import com.tinkerpop.blueprints.Element;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.Glmdb;

import java.util.Set;

/**
 * Date: 2013/11/17
 * Time: 4:06 PM
 */
public class GlmdbElement implements Element {

    protected Glmdb glmdb;
    protected Cursor cursor;
    protected long id;

    public GlmdbElement(Glmdb glmdb, Cursor cursor, long id) {
        this.glmdb = glmdb;
        this.cursor = cursor;
        this.id = id;
    }

    @Override
    public <T> T getProperty(String key) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public Set<String> getPropertyKeys() {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public void setProperty(String key, Object value) {
        if (value instanceof String) {
            setProperty(key, (String)value);
        }
    }

    public void setProperty(String key, boolean value) {
        System.out.print("boolean");
    }
    public void setProperty(String key, byte value) {
        System.out.print("byte");
    }
    public void setProperty(String key, short value) {
        System.out.print("short");
    }
    public void setProperty(String key, int value) {
        System.out.print("int");
    }
    public void setProperty(String key, long value) {
        System.out.print("long");
    }
    public void setProperty(String key, float value) {
        System.out.print("float");
    }
    public void setProperty(String key, double value) {
        System.out.print("double");
    }
    public void setProperty(String key, char value) {
        System.out.print("char");
    }
    public void setProperty(String key, String value) {
        this.glmdb.setProperty(this.cursor, this.id, key, value);

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
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }
}
