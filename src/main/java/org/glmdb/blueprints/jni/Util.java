package org.glmdb.blueprints.jni;

import static  org.glmdb.blueprints.jni.GlmdbJni.*;

/**
 * Date: 2013/11/19
 * Time: 7:19 PM
 */
public class Util {

    public static void checkErrorCode(int rc) {
        if( rc != 0 ) {
            String msg = mdb_strerror(rc);
            throw new GLMDBException(msg, rc);
        }
    }
}
