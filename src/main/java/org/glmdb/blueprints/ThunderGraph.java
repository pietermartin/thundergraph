package org.glmdb.blueprints;

import com.tinkerpop.blueprints.*;
import com.tinkerpop.blueprints.util.DefaultGraphQuery;
import org.glmdb.blueprints.iter.AllEdgeIterable;
import org.glmdb.blueprints.iter.AllVertexIterable;
import org.glmdb.blueprints.iter._boolean.EdgeBooleanIndexIterable;
import org.glmdb.blueprints.iter._boolean.EdgeForKeyBooleanValueIterable;
import org.glmdb.blueprints.iter._boolean.VertexBooleanIndexIterable;
import org.glmdb.blueprints.iter._boolean.VertexForKeyBooleanValueIterable;
import org.glmdb.blueprints.iter._byte.EdgeByteIndexIterable;
import org.glmdb.blueprints.iter._byte.EdgeForKeyByteValueIterable;
import org.glmdb.blueprints.iter._byte.VertexByteIndexIterable;
import org.glmdb.blueprints.iter._byte.VertexForKeyByteValueIterable;
import org.glmdb.blueprints.iter._char.EdgeCharIndexIterable;
import org.glmdb.blueprints.iter._char.EdgeForKeyCharValueIterable;
import org.glmdb.blueprints.iter._char.VertexCharIndexIterable;
import org.glmdb.blueprints.iter._char.VertexForKeyCharValueIterable;
import org.glmdb.blueprints.iter._double.EdgeDoubleIndexIterable;
import org.glmdb.blueprints.iter._double.EdgeForKeyDoubleValueIterable;
import org.glmdb.blueprints.iter._double.VertexDoubleIndexIterable;
import org.glmdb.blueprints.iter._double.VertexForKeyDoubleValueIterable;
import org.glmdb.blueprints.iter._float.EdgeFloatIndexIterable;
import org.glmdb.blueprints.iter._float.EdgeForKeyFloatValueIterable;
import org.glmdb.blueprints.iter._float.VertexFloatIndexIterable;
import org.glmdb.blueprints.iter._float.VertexForKeyFloatValueIterable;
import org.glmdb.blueprints.iter._int.EdgeForKeyIntValueIterable;
import org.glmdb.blueprints.iter._int.EdgeIntIndexIterable;
import org.glmdb.blueprints.iter._int.VertexForKeyIntValueIterable;
import org.glmdb.blueprints.iter._int.VertexIntIndexIterable;
import org.glmdb.blueprints.iter._long.EdgeForKeyLongValueIterable;
import org.glmdb.blueprints.iter._long.EdgeLongIndexIterable;
import org.glmdb.blueprints.iter._long.VertexForKeyLongValueIterable;
import org.glmdb.blueprints.iter._long.VertexLongIndexIterable;
import org.glmdb.blueprints.iter._short.EdgeForKeyShortValueIterable;
import org.glmdb.blueprints.iter._short.EdgeShortIndexIterable;
import org.glmdb.blueprints.iter._short.VertexForKeyShortValueIterable;
import org.glmdb.blueprints.iter._short.VertexShortIndexIterable;
import org.glmdb.blueprints.iter._string.EdgeForKeyStringValueIterable;
import org.glmdb.blueprints.iter._string.EdgeStringIndexIterable;
import org.glmdb.blueprints.iter._string.VertexForKeyStringValueIterable;
import org.glmdb.blueprints.iter._string.VertexStringIndexIterable;
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
        if (this.thunder.getIndexedKeys(true).contains(key)) {
            if (value instanceof String) {
                return new VertexStringIndexIterable(this, key, (String)value);
            } else if (value instanceof Integer) {
                return new VertexIntIndexIterable(this, key, (Integer)value);
            } else if (value instanceof Long) {
                return new VertexLongIndexIterable(this, key, (Long)value);
            } else if (value instanceof Float) {
                return new VertexFloatIndexIterable(this, key, (Float)value);
            } else if (value instanceof Double) {
                return new VertexDoubleIndexIterable(this, key, (Double)value);
            } else if (value instanceof Boolean) {
                return new VertexBooleanIndexIterable(this, key, (Boolean)value);
            } else if (value instanceof Short) {
                return new VertexShortIndexIterable(this, key, (Short)value);
            } else if (value instanceof Character) {
                return new VertexCharIndexIterable(this, key, (Character)value);
            } else if (value instanceof Byte) {
                return new VertexByteIndexIterable(this, key, (Byte)value);
            } else {
                throw new RuntimeException("Not yet implemented!");
            }
        } else {
            if (value instanceof String) {
                return new VertexForKeyStringValueIterable(this, key, (String)value);
            } else if (value instanceof Integer) {
                return new VertexForKeyIntValueIterable(this, key, (Integer)value);
            } else if (value instanceof Long) {
                return new VertexForKeyLongValueIterable(this, key, (Long)value);
            } else if (value instanceof Float) {
                return new VertexForKeyFloatValueIterable(this, key, (Float)value);
            } else if (value instanceof Double) {
                return new VertexForKeyDoubleValueIterable(this, key, (Double)value);
            } else if (value instanceof Boolean) {
                return new VertexForKeyBooleanValueIterable(this, key, (Boolean)value);
            } else if (value instanceof Short) {
                return new VertexForKeyShortValueIterable(this, key, (Short)value);
            } else if (value instanceof Character) {
                return new VertexForKeyCharValueIterable(this, key, (Character)value);
            } else if (value instanceof Byte) {
                return new VertexForKeyByteValueIterable(this, key, (Byte)value);
            } else {
                throw new RuntimeException("Not yet implemented!");
            }
        }
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

        long edgeIdResult = this.thunder.getEdge(tc.getEdgeCursor(), edgeId, labelArray, outVertexIdArray, inVertexIdArray);
        if (edgeIdResult != -1 && edgeIdResult != edgeId) {
            throw new IllegalStateException("db returned a vertex with a different id! This is a bug, should never happen");
        }
        if (edgeIdResult != -1) {
            return new ThunderEdge(this, edgeId, labelArray[0], outVertexIdArray[0], inVertexIdArray[0]);
        } else {
            return null;
        }
    }

    @Override
    public Iterable<Edge> getEdges() {
        return new AllEdgeIterable(this);
    }

    @Override
    public Iterable<Edge> getEdges(String key, Object value) {
        if (this.thunder.getIndexedKeys(false).contains(key)) {
            if (value instanceof String) {
                return new EdgeStringIndexIterable(this, key, (String)value);
            } else if (value instanceof Integer) {
                return new EdgeIntIndexIterable(this, key, (Integer)value);
            } else if (value instanceof Long) {
                return new EdgeLongIndexIterable(this, key, (Long)value);
            } else if (value instanceof Float) {
                return new EdgeFloatIndexIterable(this, key, (Float)value);
            } else if (value instanceof Double) {
                return new EdgeDoubleIndexIterable(this, key, (Double)value);
            } else if (value instanceof Boolean) {
                return new EdgeBooleanIndexIterable(this, key, (Boolean)value);
            } else if (value instanceof Short) {
                return new EdgeShortIndexIterable(this, key, (Short)value);
            } else if (value instanceof Character) {
                return new EdgeCharIndexIterable(this, key, (Character)value);
            } else if (value instanceof Byte) {
                return new EdgeByteIndexIterable(this, key, (Byte)value);
            } else {
                throw new RuntimeException("Not yet implemented!");
            }
        } else {
            if (value instanceof String) {
                return new EdgeForKeyStringValueIterable(this, key, (String)value);
            } else if (value instanceof Integer) {
                return new EdgeForKeyIntValueIterable(this, key, (Integer)value);
            } else if (value instanceof Long) {
                return new EdgeForKeyLongValueIterable(this, key, (Long)value);
            } else if (value instanceof Float) {
                return new EdgeForKeyFloatValueIterable(this, key, (Float)value);
            } else if (value instanceof Double) {
                return new EdgeForKeyDoubleValueIterable(this, key, (Double)value);
            } else if (value instanceof Boolean) {
                return new EdgeForKeyBooleanValueIterable(this, key, (Boolean)value);
            } else if (value instanceof Short) {
                return new EdgeForKeyShortValueIterable(this, key, (Short)value);
            } else if (value instanceof Character) {
                return new EdgeForKeyCharValueIterable(this, key, (Character)value);
            } else if (value instanceof Byte) {
                return new EdgeForKeyByteValueIterable(this, key, (Byte)value);
            } else {
                throw new RuntimeException("Not yet implemented!");
            }
        }
    }


    @Override
    public GraphQuery query() {
        //TODO
        return new DefaultGraphQuery(this);
    }

    @Override
    public void shutdown() {
        // As per Blueprints tests, shutdown() implies automatic commit
        this.commit();
        this.thunder.close();
    }

    @Override
    public void commit() {
//        printDb(DbEnum.LABEL_DB);
//        printDb(DbEnum.VERTEX_DB);
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
        this.internalRollback();
    }

    //This is here to avoid method overriding rollback
    //As rollback gets called when a readonly transaction is upgraded to a writable one
    private void internalRollback() {
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

    public TransactionAndCursor getReadOnlyTx() {
        return this.getTx(true);
    }

    public TransactionAndCursor getWriteTx() {
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
            Cursor vertexCursor = this.thunder.openCursor(t, DbEnum.VERTEX_DB);
            Cursor edgeCursor = this.thunder.openCursor(t, DbEnum.EDGE_DB);
            tc = new TransactionAndCursor(t, vertexCursor, edgeCursor, readOnly);
            this.currentTransaction.set(tc);
        }
        //If a write txn is needed and a read only is current then commit the read only txn and open a write txn
        if (!readOnly && tc.isReadOnly()) {
//            //Copy the current open iterator cursors to the new TransactionAndCursor
//            Set<Pair<BaseThunderIterable, Cursor>> iteratorCursors = tc.getCopyOfIteratorCursorsCopy();
            this.internalRollback();
            //Only one thread is allowed to write at a time
            synchronized (this.thunder) {
                Transaction t = this.thunder.createWriteTransaction();
                Cursor vertexCursor = this.thunder.openCursor(t, DbEnum.VERTEX_DB);
                Cursor edgeCursor = this.thunder.openCursor(t, DbEnum.EDGE_DB);
                tc = new TransactionAndCursor(t, vertexCursor, edgeCursor, readOnly);
//                tc.setIteratorCursors(iteratorCursors);
                this.currentTransaction.set(tc);
            }
        }
        return tc;
    }

    @Override
    public <T extends Element> void dropKeyIndex(String key, Class<T> elementClass) {
        if (key == null) {
            throw new IllegalStateException("key in dropKeyIndex can not be null");
        }
        if (elementClass == null) {
            throw new IllegalStateException("elementClass in dropKeyIndex can not be null");
        }
        if (elementClass.equals(Vertex.class)) {
            TransactionAndCursor tc = this.getWriteTx();
            this.thunder.dropKeyIndex(tc.getTxn(), key, true);

        } else if (elementClass.equals(Edge.class)) {
            TransactionAndCursor tc = this.getWriteTx();
            this.thunder.dropKeyIndex(tc.getTxn(), key, false);
        } else {
            throw new IllegalStateException("Unsupported elementClass " + elementClass.getName());
        }
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
        if (elementClass == null) {
            throw new IllegalStateException("elementClass in getIndexedKeys can not be null");
        }
        if (elementClass.equals(Vertex.class)) {
            return this.thunder.getIndexedKeys(true);
        } else if (elementClass.equals(Edge.class)) {
            return this.thunder.getIndexedKeys(false);
        } else {
            throw new IllegalStateException("Unsupported elementClass " + elementClass.getName());
        }
    }

    public Thunder getThunder() {
        return thunder;
    }

    public int getDbEntries(DbEnum dbEnum) {
        TransactionAndCursor tc = this.getReadOnlyTx();
        return this.thunder.getDbEntries(tc.getTxn(), dbEnum);
    }

    public void printDb(DbEnum dbEnum) {
        TransactionAndCursor tc = this.getReadOnlyTx();
        this.thunder.printDb(tc.getTxn(), dbEnum);
    }

    public MDBStat getMDBStat(DbEnum dbEnum) {
        TransactionAndCursor tc = this.getReadOnlyTx();
        return this.thunder.getMDBStat(tc.getTxn(), dbEnum);
    }

    public String getDbPath() {
        return this.thunder.getDbPath();
    }

    @Override
    public String toString() {
        return "thundergraph[" + this.getDbPath() + "]";
    }

}
