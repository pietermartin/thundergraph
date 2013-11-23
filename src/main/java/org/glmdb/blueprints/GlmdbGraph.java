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
        throw new RuntimeException("Use commit instead!");
    }

    @Override
    public Features getFeatures() {
        throw new RuntimeException("Not yet implemented!");
    }

    @Override
    public Vertex addVertex(Object id) {
        TransactionAndCursor tc = this.getWriteTx();
        long vertexId = this.glmdb.addVertex(tc.vertexCursor);
        return new GlmdbVertex(this.glmdb, tc.txn, tc.vertexCursor, vertexId);
    }

    @Override
    public Vertex getVertex(Object id) {
        if (!(id instanceof Long)) {
            throw new IllegalStateException("Vertex id must be a java.lang.Long");
        }
        Long vertexId = (Long)id;
        TransactionAndCursor tc = this.getReadOnlyTx();
        long vertexIdResult =  this.glmdb.getVertex(tc.vertexCursor, vertexId.longValue());
        if (vertexIdResult != vertexId) {
            throw new RuntimeException("db returned a vertex with a different id! This is a bug, should never happen");
        }
        if (vertexIdResult != -1) {
            return new GlmdbVertex(this.glmdb, tc.txn, tc.vertexCursor, vertexId);
        } else {
            return null;
        }
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
        TransactionAndCursor tc = this.getWriteTx();
        long edgeId = this.glmdb.addEdge(tc.txn, (Long)outVertex.getId(), (Long)inVertex.getId(), label);
        return new GlmdbEdge(this.glmdb, tc.txn, tc.edgeCursor, edgeId, label, (Long)outVertex.getId(), (Long)inVertex.getId());
    }

    @Override
    public Edge getEdge(Object id) {
        if (!(id instanceof Long)) {
            throw new IllegalStateException("Edge id must be a java.lang.Long");
        }
        Long edgeId = (Long)id;
        TransactionAndCursor tc = this.getReadOnlyTx();
        String labelArray[] = new String[1];
        long outVertexIdArray[] = new long[1];
        long inVertexIdArray[] = new long[1];
        this.glmdb.getEdge(tc.edgeCursor, edgeId.longValue(), labelArray, outVertexIdArray, inVertexIdArray);
        return new GlmdbEdge(this.glmdb, tc.txn, tc.edgeCursor, edgeId, labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
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
        TransactionAndCursor tc = this.currentTransaction.get();
        if (!tc.readOnly) {
            synchronized (this.glmdb) {
                tc.vertexCursor.close();
                tc.edgeCursor.close();
                tc.txn.commit();
                this.glmdb.synchronizeMaps();
            }
        } else {
            tc.vertexCursor.close();
            tc.edgeCursor.close();
            tc.txn.commit();
        }
        this.currentTransaction.remove();
    }

    @Override
    public void rollback() {
        TransactionAndCursor tc = this.currentTransaction.get();
        if (!tc.readOnly) {
            synchronized (this.glmdb) {
                tc.vertexCursor.close();
                tc.edgeCursor.close();
                tc.txn.abort();
                this.glmdb.unsynchronizePropertyKeyMap();
            }
        } else {
            tc.vertexCursor.close();
            tc.edgeCursor.close();
            tc.txn.abort();
        }
        this.currentTransaction.remove();
    }

    private TransactionAndCursor getReadOnlyTx() {
        return this.getTx(true);
    }

    private TransactionAndCursor getWriteTx() {
        return this.getTx(false);
    }

    private TransactionAndCursor getTx(boolean readOnly) {
        TransactionAndCursor tc = this.currentTransaction.get();
        if (tc == null) {
            Transaction t;
            if (readOnly) {
                t = this.glmdb.createReadOnlyTransaction();
            } else {
                t = this.glmdb.createWriteTransaction();
            }
            Cursor vertexCursor = this.glmdb.openCursorToVertexDb(t);
            Cursor edgeCursor = this.glmdb.openCursorToEdgeDb(t);
            tc = new TransactionAndCursor(t, vertexCursor, edgeCursor, readOnly);
            this.currentTransaction.set(tc);
        }
        //If a write txn is needed and a read only is current then commit the read only txn and open a write txn
        if (!readOnly && tc.readOnly) {
            this.commit();
            //Only one thread is allowed to write at a time
            synchronized (this.glmdb) {
                Transaction t = this.glmdb.createWriteTransaction();
                Cursor vertexCursor = this.glmdb.openCursorToVertexDb(t);
                Cursor edgeCursor = this.glmdb.openCursorToEdgeDb(t);
                tc = new TransactionAndCursor(t, vertexCursor, edgeCursor, readOnly);
                this.currentTransaction.set(tc);
            }
        }
        return tc;
    }

    private static class TransactionAndCursor {

        private Transaction txn;
        private Cursor vertexCursor;
        private Cursor edgeCursor;
        private boolean readOnly;

        private TransactionAndCursor(Transaction txn, Cursor vertexCursor, Cursor edgeCursor, boolean readOnly) {
            this.txn = txn;
            this.vertexCursor = vertexCursor;
            this.edgeCursor = edgeCursor;
            this.readOnly = readOnly;
        }

    }
}
