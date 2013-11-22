package org.glmdb.blueprints.jni;

import java.io.Closeable;

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
            GlmdbJni.mdb_cursor_close(self);
            self=0;
        }
    }

    public void renew(Transaction tx) {
        Util.checkErrorCode(GlmdbJni.mdb_cursor_renew(tx.pointer(), pointer()));
    }

}
