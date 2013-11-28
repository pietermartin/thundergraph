package org.glmdb.blueprints.jni;

import java.io.Closeable;
import java.util.HashMap;
import java.util.Map;

import static org.glmdb.blueprints.jni.GlmdbJni.*;
import static org.glmdb.blueprints.jni.Util.checkErrorCode;
import static org.glmdb.blueprints.jni.Util.*;

/**
 * Date: 2013/11/18
 * Time: 8:07 PM
 */
public class Glmdb extends NativeObject implements Closeable {

    private final Map<String, PropertyKeyEnumAndId> propertyKeyToIdMap = new HashMap<String, PropertyKeyEnumAndId>();
    private final Map<String, PropertyKeyEnumAndId> propertyKeyToIdToSyncMap = new HashMap<String, PropertyKeyEnumAndId>();
    private final Map<String, Integer> labelToIdMap = new HashMap<String, Integer>();
    private final Map<String, Integer> labelToIdToSyncMap = new HashMap<String, Integer>();
    private final Map<Integer, String> idToLabelMap = new HashMap<Integer, String>();
    private final Map<Integer, String> idToLabelSyncMap = new HashMap<Integer, String>();

    public Glmdb(String path) {
        super(create(path));
    }

    private static long create(String path) {
        long env_ptr[] = new long[1];
        checkErrorCode(glmdb_env_create(path, env_ptr));
        return env_ptr[0];
    }

    public void close() {
        if (self != 0) {
            glmdb_env_close(self);
            self = 0;
        }
    }

    public Transaction createReadOnlyTransaction() {
        return createTransaction(null, true);
    }

    public Transaction createWriteTransaction() {
        return createTransaction(null, false);
    }

    private Transaction createTransaction(Transaction parent, boolean readOnly) {
        long txpointer[] = new long[1];
        checkErrorCode(mdb_txn_begin(pointer(), parent == null ? 0 : parent.pointer(), readOnly ? GlmdbJni.MDB_RDONLY : 0, txpointer));
        return new Transaction(this, txpointer[0]);
    }

    public Cursor openCursorToVertexDb(Transaction tx) {
        long cursor[] = new long[1];
        checkErrorCode(mdb_cursor_open_vertex_db(tx.pointer(), pointer(), cursor));
        return new Cursor(this, cursor[0]);
    }

    public Cursor openCursorToEdgeDb(Transaction tx) {
        long cursor[] = new long[1];
        checkErrorCode(mdb_cursor_open_edge_db(tx.pointer(), pointer(), cursor));
        return new Cursor(this, cursor[0]);
    }

//    public Cursor openCursorToPropertyKeyDb(Transaction tx) {
//        long cursor[] = new long[1];
//        checkErrorCode(mdb_cursor_open_propertykey_db(tx.pointer(), pointer(), cursor));
//        return new Cursor(this, cursor[0]);
//    }

    public long addVertex(Cursor cursor) {
        long vertexId[] = new long[1];
        checkErrorCode(mdb_add_vertex(pointer(), cursor.pointer(), vertexId));
        return vertexId[0];
    }

    public long getVertex(Cursor cursor, long vertexId) {
        long vertexIdArray[] = new long[1];
        checkErrorCode(mdb_get_vertex(cursor.pointer(), vertexId, vertexIdArray));
        return vertexIdArray[0];
    }

    public boolean getFirstVertex(Cursor cursor, long vertexIdArray[]) {
        int rc = mdb_get_first_vertex(cursor.pointer(), vertexIdArray);
        if (rc != MDB_NOTFOUND) {
            checkErrorCode(rc);
            return true;
        } else {
            return false;
        }
    }

    public boolean getNextVertex(Cursor cursor, long vertexIdArray[]) {
        int rc = mdb_get_next_vertex(cursor.pointer(), vertexIdArray);
        if (rc != MDB_NOTFOUND) {
            checkErrorCode(rc);
            return true;
        } else {
            return false;
        }
    }

    public boolean getFirstVertexForKeyValue(Cursor cursor, long vertexIdArray[], String key, Object value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.propertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            int rc = mdb_get_first_vertex_for_key_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, objectToBytes(propertyKeyEnumAndId.propertyTypeEnum, value));
            if (rc != MDB_NOTFOUND) {
                checkErrorCode(rc);
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyValue(Cursor cursor, long vertexIdArray[], String key, Object value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.propertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            int rc = mdb_get_next_vertex_for_key_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, objectToBytes(propertyKeyEnumAndId.propertyTypeEnum, value));
            if (rc != MDB_NOTFOUND) {
                checkErrorCode(rc);
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public void getEdge(Cursor cursor, long edgeId, String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        long edgeIdArray[] = new long[1];
        int labelIdArray[] = new int[1];
        checkErrorCode(mdb_get_edge(cursor.pointer(), edgeId, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray));
        if (edgeIdArray[0] != edgeId) {
            throw new IllegalStateException("Edge id from db is not the same as passed in. This is a bug!!!");
        }
        labelArray[0] = this.idToLabelMap.get(labelIdArray[0]);
    }

    public boolean getFirstEdge(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        int labelIdArray[] = new int[1];
        int rc = mdb_get_first_edge(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
        if (rc != MDB_NOTFOUND) {
            checkErrorCode(rc);
            labelArray[0] = this.idToLabelMap.get(labelIdArray[0]);
            return true;
        } else {
            return false;
        }
    }

    public boolean getNextEdge(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        int labelIdArray[] = new int[1];
        int rc = mdb_get_next_edge(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
        if (rc != MDB_NOTFOUND) {
            checkErrorCode(rc);
            labelArray[0] = this.idToLabelMap.get(labelIdArray[0]);
            return true;
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, Object value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.propertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            int labelIdArray[] = new int[1];
            int rc = mdb_get_first_edge_for_key_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, objectToBytes(propertyKeyEnumAndId.propertyTypeEnum, value));
            if (rc != MDB_NOTFOUND) {
                checkErrorCode(rc);
                labelArray[0] = this.idToLabelMap.get(labelIdArray[0]);
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, Object value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.propertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            int labelIdArray[] = new int[1];
            int rc = mdb_get_next_edge_for_key_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, objectToBytes(propertyKeyEnumAndId.propertyTypeEnum, value));
            if (rc != MDB_NOTFOUND) {
                checkErrorCode(rc);
                labelArray[0] = this.idToLabelMap.get(labelIdArray[0]);
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeFromVertex(Cursor cursor, String label, long fromVertexId, long edgeIdArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        Integer labelId = this.labelToIdMap.get(label);
        if (labelId != null) {
            int rc = mdb_get_first_edge_from_vertex(cursor.pointer(), labelId, fromVertexId, edgeIdArray, outVertexIdArray, inVertexIdArray);
            if (rc != MDB_NOTFOUND) {
                checkErrorCode(rc);
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextEdgeFromVertex(Cursor cursor, String label, long fromVertexId, long edgeIdArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        Integer labelId = this.labelToIdMap.get(label);
        if (labelId != null) {
            int rc = mdb_get_next_edge_from_vertex(cursor.pointer(), labelId, fromVertexId, edgeIdArray, outVertexIdArray, inVertexIdArray);
            if (rc == MDB_NOTFOUND || rc == GLMDB_END_OF_EDGES) {
                return false;
            } else {
                checkErrorCode(rc);
                return true;
            }
        } else {
            return false;
        }
    }

    public long addEdge(Transaction txn, long outVertexId, long inVertexId, String label) {
        Integer labelId = this.getOrPutLabel(txn, label);
        long edgeId[] = new long[1];
        checkErrorCode(mdb_add_edge(this.pointer(), txn.pointer(), outVertexId, inVertexId, labelId, edgeId));
        return edgeId[0];
    }

    public void setProperty(Transaction txn, Cursor cursor, long vertexId, String key, Object value, boolean vertexProperty) {
        if (value instanceof String) {
            Integer propertyKeyId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.STRING);
            checkErrorCode(mdb_set_property_string(cursor.pointer(), vertexId, propertyKeyId, (String) value, vertexProperty));
        } else if (value instanceof Boolean) {
            Integer propertyKeyId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.BOOLEAN);
            checkErrorCode(mdb_set_property_boolean(cursor.pointer(), vertexId, propertyKeyId, (Boolean) value, vertexProperty));
        } else if (value instanceof Integer) {
            Integer propertyKeyId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.INT);
            checkErrorCode(mdb_set_property_int(cursor.pointer(), vertexId, propertyKeyId, (Integer) value, vertexProperty));
        } else if (value instanceof Long) {
            Integer propertyKeyId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.LONG);
            checkErrorCode(mdb_set_property_long(cursor.pointer(), vertexId, propertyKeyId, (Long) value, vertexProperty));
        } else if (value instanceof Float) {
            Integer propertyKeyId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.FLOAT);
            checkErrorCode(mdb_set_property_float(cursor.pointer(), vertexId, propertyKeyId, (Float) value, vertexProperty));
        } else if (value instanceof Double) {
            Integer propertyKeyId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.DOUBLE);
            checkErrorCode(mdb_set_property_double(cursor.pointer(), vertexId, propertyKeyId, (Double) value, vertexProperty));
        } else if (value instanceof Character) {
            Integer propertyKeyId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.CHAR);
            checkErrorCode(mdb_set_property_char(cursor.pointer(), vertexId, propertyKeyId, (Character) value, vertexProperty));
        } else if (value instanceof Byte) {
            Integer propertyKeyId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.BYTE);
            checkErrorCode(mdb_set_property_byte(cursor.pointer(), vertexId, propertyKeyId, (Byte) value, vertexProperty));
        } else if (value instanceof Short) {
            Integer propertyKeyId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.SHORT);
            checkErrorCode(mdb_set_property_short(cursor.pointer(), vertexId, propertyKeyId, (Short) value, vertexProperty));
        } else {
            throw new IllegalStateException(String.format("Unsupported value type %s", new String[]{value.getClass().getName()}));
        }
    }

    public Object getProperty(Cursor cursor, long vertexId, String key, boolean vertexProperty) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.propertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            byte[][] value = new byte[1][];
            checkErrorCode(mdb_get_property_array(cursor.pointer(), vertexId, propertyKeyEnumAndId.id, value, vertexProperty));
            return bytesToObject(propertyKeyEnumAndId.propertyTypeEnum, value[0]);
        } else {
            return null;
        }
    }

    private Integer getOrPutPropertyKey(Transaction txn, String propertyKey, PropertyTypeEnum propertyTypeEnum) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.propertyKeyToIdMap.get(propertyKey);
        int propertyKeyId;
        if (propertyKeyEnumAndId == null) {
            int propertyKeyIdArray[] = new int[1];
            checkErrorCode(mdb_set_propertykey(this.pointer(), txn.pointer(), propertyKey, propertyTypeEnum.ordinal(), propertyKeyIdArray));
            propertyKeyId = propertyKeyIdArray[0];
            this.propertyKeyToIdMap.put(propertyKey, new PropertyKeyEnumAndId(propertyTypeEnum, propertyKeyId));
            this.propertyKeyToIdToSyncMap.put(propertyKey, new PropertyKeyEnumAndId(propertyTypeEnum, propertyKeyId));
        } else {
            propertyKeyId = propertyKeyEnumAndId.id;
        }
        return propertyKeyId;
    }

    private Integer getOrPutLabel(Transaction txn, String label) {
        Integer labelId = this.labelToIdMap.get(label);
        if (labelId == null) {
            int labelIdArray[] = new int[1];
            checkErrorCode(mdb_set_label(this.pointer(), txn.pointer(), label, labelIdArray));
            labelId = labelIdArray[0];
            this.labelToIdMap.put(label, labelId);
            this.idToLabelMap.put(labelId, label);
            this.labelToIdToSyncMap.put(label, labelId);
            this.idToLabelSyncMap.put(labelId, label);
        }
        return labelId;
    }

    public void synchronizeMaps() {
        this.propertyKeyToIdMap.putAll(this.propertyKeyToIdToSyncMap);
        this.propertyKeyToIdToSyncMap.clear();
        this.labelToIdMap.putAll(this.labelToIdToSyncMap);
        this.labelToIdToSyncMap.clear();
        this.idToLabelMap.putAll(this.idToLabelSyncMap);
        this.idToLabelSyncMap.clear();
    }

    public void unsynchronizePropertyKeyMap() {
        for (String key : this.propertyKeyToIdToSyncMap.keySet()) {
            this.propertyKeyToIdMap.remove(key);
        }
        this.propertyKeyToIdToSyncMap.clear();

        for (String key : this.labelToIdToSyncMap.keySet()) {
            this.labelToIdMap.remove(key);
        }
        this.labelToIdToSyncMap.clear();

        for (Integer key : this.idToLabelSyncMap.keySet()) {
            this.idToLabelMap.remove(key);
        }
        this.idToLabelSyncMap.clear();

    }

    public void printVertexDbX() {
        checkErrorCode(printVertexDb(pointer()));
    }
}
