package org.glmdb.blueprints;

import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.Glmdb;
import org.glmdb.blueprints.jni.Transaction;

import java.io.File;

/**
 * Date: 2013/11/17
 * Time: 8:25 PM
 */
public class App {

    public static void main(String[] args) {
        File path = new File("/tmp/testdb");
        if (path.exists()) {
            path.delete();
        }
        path.mkdir();
        Glmdb glmdb_env = new Glmdb("/tmp/testdb");

        Transaction t = glmdb_env.createTransaction();
        Cursor cursor = glmdb_env.openCursorToVertexDb(t);
        glmdb_env.addVertex(cursor);
        cursor.close();
        t.commit();

        glmdb_env.close();
    }

}
