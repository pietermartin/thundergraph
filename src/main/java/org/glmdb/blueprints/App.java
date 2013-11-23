package org.glmdb.blueprints;

import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.Glmdb;
import org.glmdb.blueprints.jni.Transaction;

import java.io.File;
import java.nio.ByteBuffer;

/**
 * Date: 2013/11/17
 * Time: 8:25 PM
 */
public class App {

    public static void main(String[] args) {
        Integer i = 2;
        byte[] bytes = ByteBuffer.allocate(4).putInt(i).array();
        System.out.println(bytes);
    }

}
