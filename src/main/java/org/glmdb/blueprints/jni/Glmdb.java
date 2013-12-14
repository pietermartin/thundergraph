package org.glmdb.blueprints.jni;

import com.tinkerpop.blueprints.Direction;

import java.io.Closeable;
import java.util.*;

import static org.glmdb.blueprints.jni.GlmdbJni.*;
import static org.glmdb.blueprints.jni.Util.*;

/**
 * Date: 2013/11/18
 * Time: 8:07 PM
 */
public class Glmdb extends NativeObject implements Closeable {

    private final Map<String, PropertyKeyEnumAndId> vertexPropertyKeyToIdMap = new HashMap<String, PropertyKeyEnumAndId>();
    private final Map<String, PropertyKeyEnumAndId> vertexPropertyKeyToIdToSyncMap = new HashMap<String, PropertyKeyEnumAndId>();
    private final Map<Integer, String> vertexPropertyKeyIdToNameMap = new HashMap<Integer, String>();
    private final Map<Integer, String> vertexPropertyKeyIdToNameSyncMap = new HashMap<Integer, String>();

    private final Map<String, PropertyKeyEnumAndId> edgePropertyKeyToIdMap = new HashMap<String, PropertyKeyEnumAndId>();
    private final Map<String, PropertyKeyEnumAndId> edgePropertyKeyToIdToSyncMap = new HashMap<String, PropertyKeyEnumAndId>();
    private final Map<Integer, String> edgePropertyKeyIdToNameMap = new HashMap<Integer, String>();
    private final Map<Integer, String> edgePropertyKeyIdToNameSyncMap = new HashMap<Integer, String>();

    private final Map<String, Integer> labelToIdMap = new HashMap<String, Integer>();
    private final Map<String, Integer> labelToIdToSyncMap = new HashMap<String, Integer>();
    private final Map<Integer, String> idToLabelMap = new HashMap<Integer, String>();
    private final Map<Integer, String> idToLabelSyncMap = new HashMap<Integer, String>();

    public Glmdb(String path) {
        super(create(path));
        loadPropertyKeys();
        loadLabels();
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

    public String getDbPath() {
        byte[][] value = new byte[1][];
        int rc = mdb_env_get_path(this.pointer(), value);
        checkErrorCode(rc);
        return (String)bytesToObject(PropertyTypeEnum.STRING, value[0]);
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
        return new Transaction(this, txpointer[0], readOnly);
    }

    public Cursor openCursorToVertexDb(Transaction tx) {
        long cursor[] = new long[1];
        checkErrorCode(mdb_cursor_open_vertex_db(tx.pointer(), pointer(), cursor));
        return new Cursor(this, cursor[0]);
    }

    Cursor openCursorToPropertyKeyDb(Transaction tx, boolean vertex) {
        long cursor[] = new long[1];
        checkErrorCode(mdb_cursor_open_property_key_db(tx.pointer(), pointer(), cursor, vertex));
        return new Cursor(this, cursor[0]);
    }

    Cursor openCursorToLabelDb(Transaction tx) {
        long cursor[] = new long[1];
        checkErrorCode(mdb_cursor_open_label_db(tx.pointer(), pointer(), cursor));
        return new Cursor(this, cursor[0]);
    }

    public Cursor openAndPositionCursorOnEdgeInVertexDb(Transaction tx, long vertexId, Direction direction, String label, long edgeId) {
        Integer labelId = this.getOrPutLabel(tx, label);
        long cursor[] = new long[1];
        checkErrorCode(mdb_cursor_open_and_position_on_edge_vertex_db(tx.pointer(), pointer(), vertexId, direction.ordinal(), labelId, edgeId, cursor));
        return new Cursor(this, cursor[0]);
    }

    public Cursor openCursorToEdgeDb(Transaction tx) {
        long cursor[] = new long[1];
        checkErrorCode(mdb_cursor_open_edge_db(tx.pointer(), pointer(), cursor));
        return new Cursor(this, cursor[0]);
    }

    public long addVertex(Cursor cursor) {
        long vertexId[] = new long[1];
        checkErrorCode(mdb_add_vertex(pointer(), cursor.pointer(), vertexId));
        return vertexId[0];
    }


    public long getVertex(Cursor cursor, long vertexId) {
        long vertexIdArray[] = new long[1];
        int rc = mdb_get_vertex(cursor.pointer(), vertexId, vertexIdArray);
        if (rc == MDB_NOTFOUND) {
            return -1;
        }
        checkErrorCode(rc);
        return vertexIdArray[0];
    }

    public void removeVertex(Transaction tx, long vertexId) {
        checkErrorCode(mdb_remove_vertex(this.pointer(), tx.pointer(), vertexId));
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

    public boolean getNextVertex(Cursor cursor, long previousId, long vertexIdArray[]) {
        int rc = mdb_get_next_vertex(cursor.pointer(), previousId, vertexIdArray);
        if (rc != MDB_NOTFOUND) {
            checkErrorCode(rc);
            return true;
        } else {
            return false;
        }
    }

    public boolean getFirstVertexForKeyValue(Cursor cursor, long vertexIdArray[], String key, Object value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
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
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
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

    public void removeEdge(Transaction tx, long edgeId) {
        checkErrorCode(mdb_remove_edge(this.pointer(), tx.pointer(), edgeId));
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

    public boolean getNextEdge(Cursor cursor, long previousEdgeId, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        int labelIdArray[] = new int[1];
        int rc = mdb_get_next_edge(cursor.pointer(), previousEdgeId, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
        if (rc != MDB_NOTFOUND) {
            checkErrorCode(rc);
            labelArray[0] = this.idToLabelMap.get(labelIdArray[0]);
            return true;
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, Object value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
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
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
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

    public boolean getFirstEdgeFromVertex(Cursor cursor, Direction direction, String label, long fromVertexId, long edgeIdArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        Integer labelId = this.labelToIdMap.get(label);
        if (labelId != null) {
            int rc = mdb_get_first_edge_from_vertex(cursor.pointer(), direction.ordinal(), labelId, fromVertexId, edgeIdArray, outVertexIdArray, inVertexIdArray);
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

    public boolean getNextEdgeFromVertex(Cursor cursor, Direction direction, String label, long fromVertexId, long edgeIdArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        Integer labelId = this.labelToIdMap.get(label);
        if (labelId != null) {
            int rc = mdb_get_next_edge_from_vertex(cursor.pointer(), direction.ordinal(), labelId, fromVertexId, edgeIdArray, outVertexIdArray, inVertexIdArray);
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

    public boolean getFirstEdgeFromVertex(Cursor cursor, Direction direction, long fromVertexId, String labelArray[], long edgeIdArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        int labelIdArray[] = new int[1];
        int rc = mdb_get_first_edge_from_vertex_all_labels(cursor.pointer(), direction.ordinal(), fromVertexId, labelIdArray, edgeIdArray, outVertexIdArray, inVertexIdArray);
        if (rc == MDB_NOTFOUND || rc == GLMDB_END_OF_EDGES) {
            return false;
        } else {
            checkErrorCode(rc);
            labelArray[0] = this.idToLabelMap.get(labelIdArray[0]);
            return true;
        }
    }

    public boolean getNextEdgeFromVertex(Cursor cursor, Direction direction, long fromVertexId, String labelArray[], long edgeIdArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        int labelIdArray[] = new int[1];
        int rc = mdb_get_next_edge_from_vertex_all_labels(cursor.pointer(), direction.ordinal(), fromVertexId, labelIdArray, edgeIdArray, outVertexIdArray, inVertexIdArray);
        if (rc == MDB_NOTFOUND || rc == GLMDB_END_OF_EDGES) {
            return false;
        } else {
            checkErrorCode(rc);
            labelArray[0] = this.idToLabelMap.get(labelIdArray[0]);
            return true;
        }
    }

    public long addEdge(Transaction txn, long outVertexId, long inVertexId, String label) {
        Integer labelId = this.getOrPutLabel(txn, label);
        long edgeId[] = new long[1];
        checkErrorCode(mdb_add_edge(this.pointer(), txn.pointer(), outVertexId, inVertexId, labelId, edgeId));
        return edgeId[0];
    }

    public void setProperty(Transaction txn, Cursor cursor, long vertexId, String key, Object value, boolean vertex) {
        if (value instanceof String) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.STRING, vertex, false);
            checkErrorCode(mdb_set_property_string(this.pointer(), txn.pointer(), cursor.pointer(), vertexId, propertyKeyEnumAndId.id, (String) value, vertex, propertyKeyEnumAndId.indexed));
        } else if (value instanceof Boolean) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.BOOLEAN, vertex, false);
            checkErrorCode(mdb_set_property_boolean(cursor.pointer(), vertexId, propertyKeyEnumAndId.id, (Boolean) value, vertex));
        } else if (value instanceof Integer) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.INT, vertex, false);
            checkErrorCode(mdb_set_property_int(cursor.pointer(), vertexId, propertyKeyEnumAndId.id, (Integer) value, vertex));
        } else if (value instanceof Long) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.LONG, vertex, false);
            checkErrorCode(mdb_set_property_long(cursor.pointer(), vertexId, propertyKeyEnumAndId.id, (Long) value, vertex));
        } else if (value instanceof Float) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.FLOAT, vertex, false);
            checkErrorCode(mdb_set_property_float(cursor.pointer(), vertexId, propertyKeyEnumAndId.id, (Float) value, vertex));
        } else if (value instanceof Double) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.DOUBLE, vertex, false);
            checkErrorCode(mdb_set_property_double(cursor.pointer(), vertexId, propertyKeyEnumAndId.id, (Double) value, vertex));
        } else if (value instanceof Character) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.CHAR, vertex, false);
            checkErrorCode(mdb_set_property_char(cursor.pointer(), vertexId, propertyKeyEnumAndId.id, (Character) value, vertex));
        } else if (value instanceof Byte) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.BYTE, vertex, false);
            checkErrorCode(mdb_set_property_byte(cursor.pointer(), vertexId, propertyKeyEnumAndId.id, (Byte) value, vertex));
        } else if (value instanceof Short) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.SHORT, vertex, false);
            checkErrorCode(mdb_set_property_short(cursor.pointer(), vertexId, propertyKeyEnumAndId.id, (Short) value, vertex));
        } else {
            throw new IllegalArgumentException(String.format("Unsupported value type %s", new String[]{value.getClass().getName()}));
        }
    }

    public Object getProperty(Cursor cursor, long vertexId, String key, boolean vertex) {
        PropertyKeyEnumAndId propertyKeyEnumAndId;
        if (vertex) {
            propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        } else {
            propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        }
        if (propertyKeyEnumAndId != null) {
            byte[][] value = new byte[1][];
            int rc = mdb_get_property_array(cursor.pointer(), vertexId, propertyKeyEnumAndId.id, value, vertex);
            if (rc != MDB_NOTFOUND) {
                checkErrorCode(rc);
                return bytesToObject(propertyKeyEnumAndId.propertyTypeEnum, value[0]);
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Object removeProperty(Cursor cursor, long elementId, String key, boolean vertex) {
        PropertyKeyEnumAndId propertyKeyEnumAndId;
        if (vertex) {
            propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        } else {
            propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        }
        if (propertyKeyEnumAndId != null) {
            byte[][] value = new byte[1][];
            int rc = mdb_del_property(cursor.pointer(), elementId, propertyKeyEnumAndId.id, value, vertex);
            if (rc != MDB_NOTFOUND) {
                checkErrorCode(rc);
                return bytesToObject(propertyKeyEnumAndId.propertyTypeEnum, value[0]);
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Set<String> getPropertyKeys(Cursor cursor, long elementId, boolean vertex) {
        int[][] values = new int[1][];
        int rc = mdb_get_property_keys(cursor.pointer(), elementId, values, vertex);
        if (rc != MDB_NOTFOUND) {
            checkErrorCode(rc);
            Set<String> result = new HashSet<String>(values[0].length);
            if (vertex) {
                for (int i : values[0]) {
                    result.add(this.vertexPropertyKeyIdToNameMap.get(i));
                }
            } else {
                for (int i : values[0]) {
                    result.add(this.edgePropertyKeyIdToNameMap.get(i));
                }
            }
            return result;
        } else {
            return Collections.emptySet();
        }
    }

    private void loadPropertyKeys() {

        int propertyKeyIdArray[] = new int[1];
        int propertyTypeEnumArray[] = new int[1];
        boolean propertyIndexedArray[] = new boolean[1];
        byte[][] propertyKeyArray = new byte[1][];

        Transaction txn = createReadOnlyTransaction();
        Cursor vertexCursor = openCursorToPropertyKeyDb(txn, true);
        Cursor edgeCursor = openCursorToPropertyKeyDb(txn, false);
        try {
            int rc = mdb_get_first_property_key(vertexCursor.pointer(), propertyKeyIdArray, propertyTypeEnumArray, propertyIndexedArray, propertyKeyArray);
            while (rc == 0) {
                PropertyTypeEnum propertyTypeEnum = PropertyTypeEnum.fromOrdinal(propertyTypeEnumArray[0]);
                String key = (String) bytesToObject(PropertyTypeEnum.STRING, propertyKeyArray[0]);
                this.vertexPropertyKeyToIdMap.put(key, new PropertyKeyEnumAndId(propertyTypeEnum, propertyKeyIdArray[0], propertyIndexedArray[0]));
                this.vertexPropertyKeyIdToNameMap.put(propertyKeyIdArray[0], key);

                rc = mdb_get_next_property_key(
                        vertexCursor.pointer(),
                        propertyKeyIdArray,
                        propertyTypeEnumArray,
                        propertyIndexedArray,
                        propertyKeyArray);
            }
            if (rc != MDB_NOTFOUND) {
                checkErrorCode(rc);
            }

            rc = mdb_get_first_property_key(edgeCursor.pointer(), propertyKeyIdArray, propertyTypeEnumArray, propertyIndexedArray, propertyKeyArray);
            while (rc == 0) {
                PropertyTypeEnum propertyTypeEnum = PropertyTypeEnum.fromOrdinal(propertyTypeEnumArray[0]);
                String key = (String) bytesToObject(PropertyTypeEnum.STRING, propertyKeyArray[0]);
                this.edgePropertyKeyToIdMap.put(key, new PropertyKeyEnumAndId(propertyTypeEnum, propertyKeyIdArray[0], propertyIndexedArray[0]));
                this.edgePropertyKeyIdToNameMap.put(propertyKeyIdArray[0], key);
                rc = mdb_get_next_property_key(edgeCursor.pointer(), propertyKeyIdArray, propertyTypeEnumArray, propertyIndexedArray, propertyKeyArray);
            }
            if (rc != MDB_NOTFOUND) {
                checkErrorCode(rc);
            }

        } finally {
            mdb_cursor_close(edgeCursor.pointer());
            mdb_cursor_close(vertexCursor.pointer());
            checkErrorCode(mdb_txn_commit(this.pointer(), txn.pointer(), true));
        }
    }

    private void loadLabels() {

        int labelIdArray[] = new int[1];
        byte[][] labelArray = new byte[1][];

        Transaction txn = createReadOnlyTransaction();
        Cursor labelCursor = openCursorToLabelDb(txn);
        try {
            int rc = mdb_get_first_label(labelCursor.pointer(), labelIdArray, labelArray);
            while (rc == 0) {
                String key = (String) bytesToObject(PropertyTypeEnum.STRING, labelArray[0]);
                this.labelToIdMap.put(key, labelIdArray[0]);
                this.idToLabelMap.put(labelIdArray[0], key);

                rc = mdb_get_next_label(
                        labelCursor.pointer(),
                        labelIdArray,
                        labelArray);
            }
            if (rc != MDB_NOTFOUND) {
                checkErrorCode(rc);
            }

        } finally {
            mdb_cursor_close(labelCursor.pointer());
            checkErrorCode(mdb_txn_commit(this.pointer(), txn.pointer(), true));
        }
    }

    private PropertyKeyEnumAndId getOrPutPropertyKey(Transaction txn, String propertyKey, PropertyTypeEnum propertyTypeEnum, boolean vertex, boolean indexed) {

        Map<String, PropertyKeyEnumAndId> tmpPropertyKeyToIdMap;
        Map<String, PropertyKeyEnumAndId> tmpPropertyKeyToIdToSyncMap;
        Map<Integer, String> tmpPropertyKeyIdToNameMap;
        Map<Integer, String> tmpPropertyKeyIdToNameSyncMap;

        if (vertex) {
            tmpPropertyKeyToIdMap = this.vertexPropertyKeyToIdMap;
            tmpPropertyKeyToIdToSyncMap = this.vertexPropertyKeyToIdToSyncMap;
            tmpPropertyKeyIdToNameMap = this.vertexPropertyKeyIdToNameMap;
            tmpPropertyKeyIdToNameSyncMap = this.vertexPropertyKeyIdToNameSyncMap;
        } else {
            tmpPropertyKeyToIdMap = this.edgePropertyKeyToIdMap;
            tmpPropertyKeyToIdToSyncMap = this.edgePropertyKeyToIdToSyncMap;
            tmpPropertyKeyIdToNameMap = this.edgePropertyKeyIdToNameMap;
            tmpPropertyKeyIdToNameSyncMap = this.edgePropertyKeyIdToNameSyncMap;
        }

        PropertyKeyEnumAndId propertyKeyEnumAndId = tmpPropertyKeyToIdMap.get(propertyKey);
        int propertyKeyId;
        if (propertyKeyEnumAndId == null) {
            int propertyKeyIdArray[] = new int[1];
            checkErrorCode(mdb_set_propertykey(this.pointer(), txn.pointer(), propertyKey, propertyTypeEnum.ordinal(), propertyKeyIdArray, vertex, indexed, false));
            propertyKeyId = propertyKeyIdArray[0];
            propertyKeyEnumAndId = new PropertyKeyEnumAndId(propertyTypeEnum, propertyKeyId, indexed);
            tmpPropertyKeyToIdMap.put(propertyKey, propertyKeyEnumAndId);
            tmpPropertyKeyToIdToSyncMap.put(propertyKey, propertyKeyEnumAndId);
            tmpPropertyKeyIdToNameMap.put(propertyKeyId, propertyKey);
            tmpPropertyKeyIdToNameSyncMap.put(propertyKeyId, propertyKey);
        } else {
            //Check if the property's indexed property needs updating
            if (indexed != propertyKeyEnumAndId.indexed) {
                //TODO reindex all properties
                int propertyKeyIdArray[] = new int[]{propertyKeyEnumAndId.id};
                checkErrorCode(mdb_set_propertykey(this.pointer(), txn.pointer(), propertyKey, propertyKeyEnumAndId.propertyTypeEnum.ordinal(), propertyKeyIdArray, vertex, indexed, true));
                propertyKeyId = propertyKeyIdArray[0];
                //Do a little sanity check
                if (propertyKeyId != propertyKeyEnumAndId.id) {
                    throw new IllegalStateException("Property key id is suppose to be the same!!! This should never happen!!!");
                }
                propertyKeyEnumAndId.indexed = true;
                tmpPropertyKeyToIdMap.put(propertyKey, propertyKeyEnumAndId);
                tmpPropertyKeyToIdToSyncMap.put(propertyKey, propertyKeyEnumAndId);
                tmpPropertyKeyIdToNameMap.put(propertyKeyId, propertyKey);
                tmpPropertyKeyIdToNameSyncMap.put(propertyKeyId, propertyKey);
            }
        }
        return propertyKeyEnumAndId;
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
        this.vertexPropertyKeyToIdMap.putAll(this.vertexPropertyKeyToIdToSyncMap);
        this.vertexPropertyKeyToIdToSyncMap.clear();
        this.vertexPropertyKeyIdToNameMap.putAll(this.vertexPropertyKeyIdToNameSyncMap);
        this.vertexPropertyKeyIdToNameSyncMap.clear();
        this.labelToIdMap.putAll(this.labelToIdToSyncMap);
        this.labelToIdToSyncMap.clear();
        this.idToLabelMap.putAll(this.idToLabelSyncMap);
        this.idToLabelSyncMap.clear();
    }

    public void unsynchronizePropertyKeyMap() {
        for (String key : this.vertexPropertyKeyToIdToSyncMap.keySet()) {
            this.vertexPropertyKeyToIdMap.remove(key);
        }
        this.vertexPropertyKeyToIdToSyncMap.clear();

        for (String key : this.labelToIdToSyncMap.keySet()) {
            this.labelToIdMap.remove(key);
        }
        this.labelToIdToSyncMap.clear();

        for (Integer key : this.idToLabelSyncMap.keySet()) {
            this.idToLabelMap.remove(key);
        }
        this.idToLabelSyncMap.clear();

    }

    public void printDb(Transaction txn, DbEnum dbEnum) {
        checkErrorCode(print_db(this.pointer(), txn.pointer(), dbEnum.ordinal()));
    }

    public void createKeyIndex(Transaction txn, String key, boolean vertex) {
        this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.UNSET, vertex, true);
    }

}
