package org.glmdb.blueprints;

import com.tinkerpop.blueprints.*;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;
import org.glmdb.blueprints.jni.Thunder;
import org.glmdb.blueprints.jni.Transaction;

import java.io.File;
import java.util.Set;

/**
 * Date: 2013/11/17
 * Time: 4:07 PM
 */
public class ThunderGraph implements TransactionalGraph, KeyIndexableGraph {

    private final Thunder thunder;
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

        thunder = new Thunder(dbPath.getAbsolutePath());
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
        long vertexId = this.thunder.addVertex(tc.getVertexCursor());
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
        long vertexIdResult = this.thunder.getVertex(tc.getVertexCursor(), vertexId);
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
        return new AllVertexIterable(this);
    }

    @Override
    public Iterable<Vertex> getVertices(String key, Object value) {
        return new VertexForKeyValueIterable(this, key, value);
    }

    @Override
    public Edge addEdge(Object id, Vertex outVertex, Vertex inVertex, String label) {
        if (label == null) {
            throw new IllegalArgumentException("Edge label can not be null"); // Enforced by 2.3.0 test case
        }
        TransactionAndCursor tc = this.getWriteTx();
        long edgeId = this.thunder.addEdge(tc.getTxn(), (Long) outVertex.getId(), (Long) inVertex.getId(), label);
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
        this.thunder.getEdge(tc.getEdgeCursor(), edgeId, labelArray, outVertexIdArray, inVertexIdArray);
        return new ThunderEdge(this, edgeId, labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
    }

    @Override
    public Iterable<Edge> getEdges() {
        return new AllEdgeIterable(this);
    }

    @Override
    public Iterable<Edge> getEdges(String key, Object value) {
        return new EdgeForKeyValueIterable(this, key, value);
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
        this.thunder.close();
    }

    @Override
    public void commit() {
        TransactionAndCursor tc = this.currentTransaction.get();
        if (tc != null) {
            if (!tc.isReadOnly()) {
                synchronized (this.thunder) {
                    tc.closeCursors();
                    tc.getTxn().commit();
                    this.thunder.synchronizeMaps();
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
                synchronized (this.thunder) {
                    tc.closeCursors();
                    tc.getTxn().abort();
                    this.thunder.unsynchronizePropertyKeyMap();
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
                t = this.thunder.createReadOnlyTransaction();
            } else {
                t = this.thunder.createWriteTransaction();
            }
            Cursor vertexCursor = this.thunder.openCursorToVertexDb(t);
            Cursor edgeCursor = this.thunder.openCursorToEdgeDb(t);
            tc = new TransactionAndCursor(t, vertexCursor, edgeCursor, readOnly);
            this.currentTransaction.set(tc);
        }
        //If a write txn is needed and a read only is current then commit the read only txn and open a write txn
        if (!readOnly && tc.isReadOnly()) {
            this.rollback();
            //Only one thread is allowed to write at a time
            synchronized (this.thunder) {
                Transaction t = this.thunder.createWriteTransaction();

                //All current iterator cursors need to be upgraded
//                this.cursor = EdgesFromVertexIterable.this.thunderGraph.getThunder().openAndPositionCursorOnEdgeInVertexDb(
//                        EdgesFromVertexIterable.this.tc.getTxn(),
//                        EdgesFromVertexIterable.this.vertexId,
//                        (this.internalNext.getOutVertexId() == EdgesFromVertexIterable.this.vertexId ? Direction.OUT : Direction.IN),
//                        this.internalNext.getLabel(),
//                        this.internalNext.id
//                );


                Cursor vertexCursor = this.thunder.openCursorToVertexDb(t);
                Cursor edgeCursor = this.thunder.openCursorToEdgeDb(t);
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
            this.thunder.createKeyIndex(tc.getTxn(), key, true);

        } else if (elementClass.equals(Edge.class)) {
            TransactionAndCursor tc = this.getWriteTx();
            this.thunder.createKeyIndex(tc.getTxn(), key, false);
        } else {
            throw new IllegalStateException("Unsupported elementClass " + elementClass.getName());
        }
    }

    @Override
    public <T extends Element> Set<String> getIndexedKeys(Class<T> elementClass) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    Thunder getThunder() {
        return thunder;
    }

    public void printDb(DbEnum dbEnum) {
        TransactionAndCursor tc = this.getReadOnlyTx();
        this.thunder.printDb(tc.getTxn(), dbEnum);
    }

    public String getDbPath() {
        return this.thunder.getDbPath();
    }

    @Override
    public String toString() {
        return "thundergraph[" + this.getDbPath() + "]";
    }

}
