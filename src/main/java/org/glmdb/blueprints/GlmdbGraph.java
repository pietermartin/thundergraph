package org.glmdb.blueprints;

import com.tinkerpop.blueprints.*;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.Glmdb;
import org.glmdb.blueprints.jni.Transaction;

import java.io.File;

/**
 * Date: 2013/11/17
 * Time: 4:07 PM
 */
public class GlmdbGraph implements TransactionalGraph {

    private Glmdb glmdb;
    private ThreadLocal<TransactionAndCursor> currentTransaction;

    public GlmdbGraph(String dbPath) {
        this(new File(dbPath));
    }

    public GlmdbGraph(File dbPath) {
        if (dbPath == null) {
            throw new IllegalStateException("The dbPath can not be null!");
        }
        if (!dbPath.exists()) {
            throw new IllegalStateException(String.format("The dbPath %s does not exist!", new String[]{dbPath.getAbsolutePath()}));
        }
        glmdb = new Glmdb(dbPath.getAbsolutePath());
        this.currentTransaction = new ThreadLocal<TransactionAndCursor>();
    }

    @Override
    public void stopTransaction(Conclusion conclusion) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public Features getFeatures() {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public Vertex addVertex(Object id) {
        TransactionAndCursor tc = getTx();
        long vertexId = this.glmdb.addVertex(tc.cursor);
        return new GlmdbVertex(this.glmdb, tc.cursor, vertexId);
    }

    @Override
    public Vertex getVertex(Object id) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public void removeVertex(Vertex vertex) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public Iterable<Vertex> getVertices() {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public Iterable<Vertex> getVertices(String key, Object value) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public Edge addEdge(Object id, Vertex outVertex, Vertex inVertex, String label) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public Edge getEdge(Object id) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public void removeEdge(Edge edge) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public Iterable<Edge> getEdges() {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public Iterable<Edge> getEdges(String key, Object value) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public GraphQuery query() {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public void shutdown() {
        this.glmdb.close();
    }

    @Override
    public void commit() {
        this.getTx().cursor.close();
        this.getTx().txn.commit();
    }

    @Override
    public void rollback() {
        this.getTx().cursor.close();
        this.getTx().txn.abort();
    }

    private TransactionAndCursor getTx() {
        TransactionAndCursor tc = this.currentTransaction.get();
        if (tc == null) {
            Transaction t = this.glmdb.createTransaction();
            Cursor c = this.glmdb.openCursorToVertexDb(t);
            tc = new TransactionAndCursor(t, c);
            this.currentTransaction.set(tc);
        }
        return tc;
    }

    private static class TransactionAndCursor {

        private Transaction txn;
        private Cursor cursor;

        private TransactionAndCursor(Transaction txn, Cursor cursor) {
            this.txn = txn;
            this.cursor = cursor;
        }

    }
}
