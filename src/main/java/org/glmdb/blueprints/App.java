package org.glmdb.blueprints;

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
