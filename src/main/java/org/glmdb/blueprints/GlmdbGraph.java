package org.glmdb.blueprints;

import com.tinkerpop.blueprints.*;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.Glmdb;
import org.glmdb.blueprints.jni.Transaction;

import java.io.File;
import java.util.Set;

/**
 * Date: 2013/11/17
 * Time: 4:07 PM
 */
public class GlmdbGraph implements TransactionalGraph, KeyIndexableGraph {

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
        throw new UnsupportedOperationException("Use commit instead!");
    }

    @Override
    public Features getFeatures() {
        //TODO
        throw new RuntimeException("Not yet implemented!");
    }

    @Override
    public Vertex addVertex(Object id) {
        TransactionAndCursor tc = this.getWriteTx();
        long vertexId = this.glmdb.addVertex(tc.getVertexCursor());
        return new GlmdbVertex(this, vertexId);
    }

    @Override
    public Vertex getVertex(Object id) {
        if (!(id instanceof Long)) {
            throw new IllegalStateException("Vertex id must be a java.lang.Long");
        }
        Long vertexId = (Long)id;
        TransactionAndCursor tc = this.getReadOnlyTx();
        long vertexIdResult =  this.glmdb.getVertex(tc.getVertexCursor(), vertexId.longValue());
        if (vertexIdResult != -1 && vertexIdResult != vertexId) {
            throw new IllegalStateException("db returned a vertex with a different id! This is a bug, should never happen");
        }
        if (vertexIdResult != -1) {
            return new GlmdbVertex(this, vertexId);
        } else {
            return null;
        }
    }

    @Override
    public void removeVertex(Vertex vertex) {
        vertex.remove();
    }

    @Override
    public void removeEdge(Edge edge) {
        edge.remove();
    }

    @Override
    public Iterable<Vertex> getVertices() {
        return new GlmdbAllVertexIterable(this);
    }

    @Override
    public Iterable<Vertex> getVertices(String key, Object value) {
        return new GlmdbVertexForKeyValueIterable(this, key, value);
    }

    @Override
    public Edge addEdge(Object id, Vertex outVertex, Vertex inVertex, String label) {
        TransactionAndCursor tc = this.getWriteTx();
        long edgeId = this.glmdb.addEdge(tc.getTxn(), (Long)outVertex.getId(), (Long)inVertex.getId(), label);
        return new GlmdbEdge(this, edgeId, label, (Long)outVertex.getId(), (Long)inVertex.getId());
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
        this.glmdb.getEdge(tc.getEdgeCursor(), edgeId.longValue(), labelArray, outVertexIdArray, inVertexIdArray);
        return new GlmdbEdge(this, edgeId, labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
    }

    @Override
    public Iterable<Edge> getEdges() {
        return new GlmdbAllEdgeIterable(this);
    }

    @Override
    public Iterable<Edge> getEdges(String key, Object value) {
        return new GlmdbEdgeForKeyValueIterable(this, key, value);
    }

    @Override
    public GraphQuery query() {
        //TODO
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public void shutdown() {
        this.glmdb.close();
    }

    @Override
    public void commit() {
        TransactionAndCursor tc = this.currentTransaction.get();
        if (!tc.isReadOnly()) {
            synchronized (this.glmdb) {
                tc.closeCursors();
                tc.getTxn().commit();
                this.glmdb.synchronizeMaps();
            }
        } else {
            tc.closeCursors();
            tc.getTxn().commit();
        }
        this.currentTransaction.remove();
        this.currentTransaction.set(null);
    }

    @Override
    public void rollback() {
        TransactionAndCursor tc = this.currentTransaction.get();
        if (!tc.isReadOnly()) {
            synchronized (this.glmdb) {
                tc.closeCursors();
                tc.getTxn().abort();
                this.glmdb.unsynchronizePropertyKeyMap();
            }
        } else {
            tc.closeCursors();
            tc.getTxn().abort();
        }
        this.currentTransaction.remove();
    }

    TransactionAndCursor getReadOnlyTx() {
        return this.getTx(true);
    }

    TransactionAndCursor getWriteTx() {
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
        if (!readOnly && tc.isReadOnly()) {
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

    Glmdb getGlmdb() {
        return glmdb;
    }

    public void printVertexDb() {
        this.glmdb.printVertexDbX();
    }

    public void printEdgeDb() {
        this.glmdb.printEdgeDbX();
    }

    @Override
    public <T extends Element> void dropKeyIndex(String key, Class<T> elementClass) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public <T extends Element> void createKeyIndex(String key, Class<T> elementClass, Parameter... indexParameters) {
        if (key == null) {
            throw new IllegalStateException("key in createKeyIndex can not be null");
        }
        if (elementClass == null) {
            throw new IllegalStateException("elementClass in createKeyIndex can not be null");
        }
        if (elementClass.equals(Vertex.class)) {
//            this.glmdb.createVertexKeyIndex(key);
        } else if (elementClass.equals(Edge.class)) {
//            this.glmdb.createEdgeKeyIndex(key);
        } else {
            throw new IllegalStateException("Unsupported elementClass " + elementClass.getName());
        }
    }

    @Override
    public <T extends Element> Set<String> getIndexedKeys(Class<T> elementClass) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }
}
