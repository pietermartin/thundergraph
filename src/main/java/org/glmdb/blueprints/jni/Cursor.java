package org.glmdb.blueprints.jni;

import java.io.Closeable;

import static  org.glmdb.blueprints.jni.GlmdbJni.*;
import static org.glmdb.blueprints.jni.Util.*;

/**
 * Date: 2013/11/19
 * Time: 9:31 PM
 */
public class Cursor extends NativeObject implements Closeable {

    private final Glmdb env;

    Cursor(Glmdb env, long self) {
        super(self);
        this.env = env;
    }

    public void close() {
        if( self!=0 ) {
            mdb_cursor_close(self);
            self=0;
        }
    }

    public void renew(Transaction tx) {
        checkErrorCode(mdb_cursor_renew(tx.pointer(), pointer()));
    }

}
