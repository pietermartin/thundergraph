package org.glmdb.blueprints;

import com.tinkerpop.blueprints.*;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;
import org.glmdb.blueprints.jni.Glmdb;
import org.glmdb.blueprints.jni.Transaction;

import java.io.File;
import java.util.Set;

/**
 * Date: 2013/11/17
 * Time: 4:07 PM
 */
public class ThunderGraph implements TransactionalGraph, KeyIndexableGraph {

    private final Glmdb glmdb;
    private ThreadLocal<TransactionAndCursor> currentTransaction;
    private Features thunderGraphFeatures;

    public ThunderGraph(String dbPath) {
        this(new File(dbPath));
    }

    public ThunderGraph(File dbPath) {
        if (dbPath == null) {
            throw new IllegalStateException("The dbPath can not be null!");
        }
        if (!dbPath.exists()) {
            throw new IllegalStateException(String.format("The dbPath %s does not exist!", new String[]{dbPath.getAbsolutePath()}));
        }

        this.thunderGraphFeatures = new Features();

        thunderGraphFeatures.isPersistent = true; // Depends on setting

        // General
        thunderGraphFeatures.ignoresSuppliedIds = true;
        thunderGraphFeatures.isWrapper = false;
        thunderGraphFeatures.supportsDuplicateEdges = true;
        thunderGraphFeatures.supportsEdgeIndex = false;
        thunderGraphFeatures.supportsEdgeIteration = true;
        thunderGraphFeatures.supportsEdgeProperties = true;
        thunderGraphFeatures.supportsEdgeRetrieval = true;
        thunderGraphFeatures.supportsIndices = false;
        thunderGraphFeatures.supportsSelfLoops = true;
        thunderGraphFeatures.supportsThreadedTransactions = true;
        thunderGraphFeatures.supportsTransactions = true;
        thunderGraphFeatures.supportsVertexIndex = false;
        thunderGraphFeatures.supportsVertexIteration = true;
        thunderGraphFeatures.supportsVertexProperties = true;
        thunderGraphFeatures.supportsEdgeKeyIndex = true;
        thunderGraphFeatures.supportsKeyIndices = true;
        thunderGraphFeatures.supportsVertexKeyIndex = true;

        // Serialization
        thunderGraphFeatures.supportsBooleanProperty = true;
        thunderGraphFeatures.supportsDoubleProperty = true;
        thunderGraphFeatures.supportsDuplicateEdges = true;
        thunderGraphFeatures.supportsFloatProperty = true;
        thunderGraphFeatures.supportsIntegerProperty = true;
        thunderGraphFeatures.supportsLongProperty = true;
        thunderGraphFeatures.supportsStringProperty = true;
        thunderGraphFeatures.supportsMapProperty = false;
        thunderGraphFeatures.supportsMixedListProperty = false;
        thunderGraphFeatures.supportsUniformListProperty = false;
        thunderGraphFeatures.supportsPrimitiveArrayProperty = false;
        thunderGraphFeatures.supportsSerializableObjectProperty = false;

        glmdb = new Glmdb(dbPath.getAbsolutePath());
        this.currentTransaction = new ThreadLocal<TransactionAndCursor>();
    }

    @Override
    public void stopTransaction(Conclusion conclusion) {
        throw new UnsupportedOperationException("Use commit instead!");
    }

    @Override
    public Features getFeatures() {
        return this.thunderGraphFeatures;
    }

    @Override
    public Vertex addVertex(Object id) {
        TransactionAndCursor tc = this.getWriteTx();
        long vertexId = this.glmdb.addVertex(tc.getVertexCursor());
        return new ThunderVertex(this, vertexId);
    }

    @Override
    public Vertex getVertex(Object id) {
        if (id == null) {
            throw new IllegalArgumentException("The vertex ID passed to getVertex() is null");
        }
        if (!(id instanceof Long)) {
            try {
                id = Long.valueOf(id.toString());
            } catch (NumberFormatException e) {
                return null;
            }
        }

        Long vertexId = (Long) id;
        TransactionAndCursor tc = this.getReadOnlyTx();
        long vertexIdResult = this.glmdb.getVertex(tc.getVertexCursor(), vertexId);
        if (vertexIdResult != -1 && vertexIdResult != vertexId) {
            throw new IllegalStateException("db returned a vertex with a different id! This is a bug, should never happen");
        }
        if (vertexIdResult != -1) {
            return new ThunderVertex(this, vertexId);
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
        if (label == null) {
            throw new IllegalArgumentException("Edge label can not be null"); // Enforced by 2.3.0 test case
        }
        TransactionAndCursor tc = this.getWriteTx();
        long edgeId = this.glmdb.addEdge(tc.getTxn(), (Long) outVertex.getId(), (Long) inVertex.getId(), label);
        return new ThunderEdge(this, edgeId, label, (Long) outVertex.getId(), (Long) inVertex.getId());
    }

    @Override
    public Edge getEdge(Object id) {
        if (id == null) {
            throw new IllegalArgumentException("The edge ID passed to getEdge() is null");
        }
        if (!(id instanceof Long)) {
            try {
                id = Long.valueOf(id.toString());
            } catch (NumberFormatException e) {
                return null;
            }
        }
        Long edgeId = (Long) id;
        TransactionAndCursor tc = this.getReadOnlyTx();
        String labelArray[] = new String[1];
        long outVertexIdArray[] = new long[1];
        long inVertexIdArray[] = new long[1];
        this.glmdb.getEdge(tc.getEdgeCursor(), edgeId, labelArray, outVertexIdArray, inVertexIdArray);
        return new ThunderEdge(this, edgeId, labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
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
        // As per Blueprints tests, shutdown() implies automatic commit
        this.commit();
        this.glmdb.close();
    }

    @Override
    public void commit() {
        TransactionAndCursor tc = this.currentTransaction.get();
        if (tc != null) {
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
    }

    @Override
    public void rollback() {
        TransactionAndCursor tc = this.currentTransaction.get();
        if (tc != null) {
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
        } else {
            //nada
        }
    }

    public boolean isTxActive() {
        return this.currentTransaction.get() != null;
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
            this.rollback();
            //Only one thread is allowed to write at a time
            synchronized (this.glmdb) {
                Transaction t = this.glmdb.createWriteTransaction();

                //All current iterator cursors need to be upgraded
//                this.cursor = GlmdbEdgesFromVertexIterable.this.thunderGraph.getGlmdb().openAndPositionCursorOnEdgeInVertexDb(
//                        GlmdbEdgesFromVertexIterable.this.tc.getTxn(),
//                        GlmdbEdgesFromVertexIterable.this.vertexId,
//                        (this.internalNext.getOutVertexId() == GlmdbEdgesFromVertexIterable.this.vertexId ? Direction.OUT : Direction.IN),
//                        this.internalNext.getLabel(),
//                        this.internalNext.id
//                );


                Cursor vertexCursor = this.glmdb.openCursorToVertexDb(t);
                Cursor edgeCursor = this.glmdb.openCursorToEdgeDb(t);
                tc = new TransactionAndCursor(t, vertexCursor, edgeCursor, readOnly);
                this.currentTransaction.set(tc);
            }
        }
        return tc;
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
            TransactionAndCursor tc = this.getWriteTx();
            this.glmdb.createKeyIndex(tc.getTxn(), key, true);

        } else if (elementClass.equals(Edge.class)) {
            TransactionAndCursor tc = this.getWriteTx();
            this.glmdb.createKeyIndex(tc.getTxn(), key, false);
        } else {
            throw new IllegalStateException("Unsupported elementClass " + elementClass.getName());
        }
    }

    @Override
    public <T extends Element> Set<String> getIndexedKeys(Class<T> elementClass) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    Glmdb getGlmdb() {
        return glmdb;
    }

    public void printDb(DbEnum dbEnum) {
        TransactionAndCursor tc = this.getReadOnlyTx();
        this.glmdb.printDb(tc.getTxn(), dbEnum);
    }

    public String getDbPath() {
        return this.glmdb.getDbPath();
    }

    @Override
    public String toString() {
        return "thundergraph[" + this.getDbPath() + "]";
    }

}
