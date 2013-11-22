package org.glmdb.blueprints.jni;

import java.io.UnsupportedEncodingException;

import static org.glmdb.blueprints.jni.GlmdbJni.mdb_strerror;

/**
 * Date: 2013/11/19
 * Time: 7:19 PM
 */
public class Util {

    static void checkErrorCode(int rc) {
        if( rc != 0 ) {
            String msg = mdb_strerror(rc);
            throw new GLMDBException(msg, rc);
        }
    }

    static String string(byte[] value) {
        if( value == null) {
            return null;
        }
        try {
            return new String(value, "UTF-8");
        } catch (UnsupportedEncodingException e) {
            throw new RuntimeException(e);
        }
    }

    public static byte[] bytes(String value) {
        if( value == null) {
            return null;
        }
        try {
            return value.getBytes("UTF-8");
        } catch (UnsupportedEncodingException e) {
            throw new RuntimeException(e);
        }
    }
}
