package org.glmdb.blueprints.jni;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Element;
import org.glmdb.blueprints.MDBStat;

import java.io.Closeable;
import java.nio.ByteBuffer;
import java.util.*;

import static org.glmdb.blueprints.jni.ThunderJni.*;
import static org.glmdb.blueprints.jni.Util.*;

/**
 * Date: 2013/11/18
 * Time: 8:07 PM
 */
public class Thunder extends NativeObject implements Closeable {

    private final Map<String, PropertyKeyEnumAndId> vertexPropertyKeyToIdMap = new HashMap<String, PropertyKeyEnumAndId>();
    private final Map<String, PropertyKeyEnumAndId> vertexPropertyKeyToIdToSyncMap = new HashMap<String, PropertyKeyEnumAndId>();
    private final Map<Integer, String> vertexPropertyKeyIdToNameMap = new HashMap<Integer, String>();
    private final Map<Integer, String> vertexPropertyKeyIdToNameSyncMap = new HashMap<Integer, String>();
    private Set<String> vertexIndexedKeys = new HashSet<String>();

    private final Map<String, PropertyKeyEnumAndId> edgePropertyKeyToIdMap = new HashMap<String, PropertyKeyEnumAndId>();
    private final Map<String, PropertyKeyEnumAndId> edgePropertyKeyToIdToSyncMap = new HashMap<String, PropertyKeyEnumAndId>();
    private final Map<Integer, String> edgePropertyKeyIdToNameMap = new HashMap<Integer, String>();
    private final Map<Integer, String> edgePropertyKeyIdToNameSyncMap = new HashMap<Integer, String>();
    private Set<String> edgeIndexedKeys = new HashSet<String>();

    private final Map<String, Integer> labelToIdMap = new HashMap<String, Integer>();
    private final Map<String, Integer> labelToIdToSyncMap = new HashMap<String, Integer>();
    private final Map<Integer, String> idToLabelMap = new HashMap<Integer, String>();
    private final Map<Integer, String> idToLabelSyncMap = new HashMap<Integer, String>();

    public Thunder(String path) {
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
        return (String) bytesToObject(PropertyTypeEnum.STRING, value[0]);
    }

    public Transaction createReadOnlyTransaction() {
        return createTransaction(null, true);
    }

    public Transaction createWriteTransaction() {
        return createTransaction(null, false);
    }

    private Transaction createTransaction(Transaction parent, boolean readOnly) {
        long txpointer[] = new long[1];
        checkErrorCode(mdb_txn_begin(pointer(), parent == null ? 0 : parent.pointer(), readOnly ? ThunderJni.MDB_RDONLY : 0, txpointer));
        return new Transaction(this, txpointer[0], readOnly);
    }

    public Cursor openCursor(Transaction tx, DbEnum dbEnum) {
        long cursor[] = new long[1];
        checkErrorCode(mdb_cursor_open(tx.pointer(), pointer(), dbEnum.ordinal(), cursor));
        return new Cursor(this, cursor[0]);
    }

    public Cursor openAndPositionCursorOnEdgeInVertexDb(Transaction tx, long vertexId, Direction direction, String label, long edgeId) {
        Integer labelId = this.getOrPutLabel(tx, label);
        long cursor[] = new long[1];
        //this calls mdb_cursor_get with MDB_SET_RANGE
        int rc = mdb_cursor_open_and_position_on_edge_vertex_db(tx.pointer(), pointer(), vertexId, direction.ordinal(), labelId, edgeId, cursor);
        if (rc == MDB_NOTFOUND) {
            return null;
        } else {
            checkErrorCode(rc);
            return new Cursor(this, cursor[0]);
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInVertexStringIndexDb(Transaction tx, long vertexId, String key, String value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.STRING) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_vertex_string_index_db(tx.pointer(), pointer(), vertexId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInEdgeStringIndexDb(Transaction tx, long edgeId, String key, String value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.STRING) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_edge_string_index_db(tx.pointer(), pointer(), edgeId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInEdgeShortIndexDb(Transaction tx, long edgeId, String key, short value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.SHORT) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_edge_short_index_db(tx.pointer(), pointer(), edgeId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInEdgeLongIndexDb(Transaction tx, long edgeId, String key, long value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.LONG) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_edge_long_index_db(tx.pointer(), pointer(), edgeId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInEdgeIntIndexDb(Transaction tx, long edgeId, String key, int value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.INT) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_edge_int_index_db(tx.pointer(), pointer(), edgeId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInEdgeFloatIndexDb(Transaction tx, long edgeId, String key, float value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.FLOAT) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_edge_float_index_db(tx.pointer(), pointer(), edgeId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInEdgeDoubleIndexDb(Transaction tx, long edgeId, String key, double value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.DOUBLE) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_edge_double_index_db(tx.pointer(), pointer(), edgeId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInEdgeCharIndexDb(Transaction tx, long edgeId, String key, char value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.CHAR) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_edge_char_index_db(tx.pointer(), pointer(), edgeId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInEdgeByteIndexDb(Transaction tx, long edgeId, String key, byte value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BYTE) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_edge_byte_index_db(tx.pointer(), pointer(), edgeId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInEdgeBooleanIndexDb(Transaction tx, long edgeId, String key, boolean value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BOOLEAN) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_edge_boolean_index_db(tx.pointer(), pointer(), edgeId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInVertexShortIndexDb(Transaction tx, long vertexId, String key, short value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.SHORT) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_vertex_short_index_db(tx.pointer(), pointer(), vertexId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInVertexLongIndexDb(Transaction tx, long vertexId, String key, long value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.LONG) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_vertex_long_index_db(tx.pointer(), pointer(), vertexId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInVertexIntIndexDb(Transaction tx, long vertexId, String key, int value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.INT) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_vertex_int_index_db(tx.pointer(), pointer(), vertexId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInVertexFloatIndexDb(Transaction tx, long vertexId, String key, float value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.FLOAT) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_vertex_float_index_db(tx.pointer(), pointer(), vertexId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInVertexDoubleIndexDb(Transaction tx, long vertexId, String key, double value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.DOUBLE) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_vertex_double_index_db(tx.pointer(), pointer(), vertexId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInVertexCharIndexDb(Transaction tx, long vertexId, String key, char value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.CHAR) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_vertex_char_index_db(tx.pointer(), pointer(), vertexId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInVertexByteIndexDb(Transaction tx, long vertexId, String key, byte value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BYTE) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_vertex_byte_index_db(tx.pointer(), pointer(), vertexId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnKeyValueInVertexBooleanIndexDb(Transaction tx, long vertexId, String key, boolean value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BOOLEAN) {
                long cursor[] = new long[1];
                int rc = mdb_cursor_open_and_position_on_key_value_vertex_boolean_index_db(tx.pointer(), pointer(), vertexId, propertyKeyEnumAndId.id, value, cursor);
                if (rc == MDB_NOTFOUND) {
                    return null;
                } else {
                    checkErrorCode(rc);
                    return new Cursor(this, cursor[0]);
                }
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    public Cursor openAndPositionCursorOnVertexInVertexDb(Transaction tx, long vertexId) {
        long cursor[] = new long[1];
        //this calls mdb_cursor_get with MDB_SET_RANGE
        int rc = mdb_cursor_open_and_position_on_vertex_vertex_db(tx.pointer(), pointer(), vertexId, cursor);
        if (rc == MDB_NOTFOUND) {
            return null;
        } else {
            checkErrorCode(rc);
            return new Cursor(this, cursor[0]);
        }
    }

    public Cursor openAndPositionCursorOnEdgePropertyInEdgeDb(Transaction tx, long edgeId, String propertyKey) {
        long cursor[] = new long[1];
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(propertyKey);
        checkErrorCode(mdb_cursor_open_and_position_on_edge_edge_db(tx.pointer(), pointer(), edgeId, propertyKeyEnumAndId.id, cursor));
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

    public boolean getFirstVertexForKeyStringValue(Cursor cursor, long vertexIdArray[], String key, String value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.STRING) {
                int rc = mdb_get_first_vertex_for_key_string_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyStringValue(Cursor cursor, long vertexIdArray[], String key, String value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.STRING) {
                int rc = mdb_get_next_vertex_for_key_string_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public long getEdge(Cursor cursor, long edgeId, String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        long edgeIdArray[] = new long[1];
        int labelIdArray[] = new int[1];
        int rc = mdb_get_edge(cursor.pointer(), edgeId, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);

        if (rc == MDB_NOTFOUND) {
            return -1;
        } else {
            checkErrorCode(rc);
            if (edgeIdArray[0] != edgeId) {
                throw new IllegalStateException("Edge id from db is not the same as passed in. This is a bug!!!");
            }
        }
        labelArray[0] = this.idToLabelMap.get(labelIdArray[0]);
        return edgeId;
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

    public boolean getFirstEdgeForKeyStringValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, String value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.STRING) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_string_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyStringValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, String value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.STRING) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_string_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }

    public boolean getCurrentVertexFromVertexStringIndexDb(Cursor cursor, long vertexIdArray[], String key, String value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.STRING) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_vertex_from_vertex_string_index_db(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getCurrentEdgeFromEdgeStringIndexDb(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, String value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.STRING) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_edge_from_edge_string_index_db(edgeStringIndexDbCursor.pointer(),  edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getCurrentEdgeFromEdgeShortIndexDb(Cursor edgeShortIndexDbCursor, Cursor edgeDbCursor, String key, short value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.SHORT) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_edge_from_edge_short_index_db(edgeShortIndexDbCursor.pointer(),  edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getCurrentEdgeFromEdgeLongIndexDb(Cursor edgeLongIndexDbCursor, Cursor edgeDbCursor, String key, long value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.LONG) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_edge_from_edge_long_index_db(edgeLongIndexDbCursor.pointer(),  edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getCurrentEdgeFromEdgeIntIndexDb(Cursor edgeIntIndexDbCursor, Cursor edgeDbCursor, String key, int value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.INT) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_edge_from_edge_int_index_db(edgeIntIndexDbCursor.pointer(),  edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getCurrentEdgeFromEdgeFloatIndexDb(Cursor edgeFloatIndexDbCursor, Cursor edgeDbCursor, String key, float value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.FLOAT) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_edge_from_edge_float_index_db(edgeFloatIndexDbCursor.pointer(),  edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getCurrentEdgeFromEdgeDoubleIndexDb(Cursor edgeDoubleIndexDbCursor, Cursor edgeDbCursor, String key, double value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.DOUBLE) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_edge_from_edge_double_index_db(edgeDoubleIndexDbCursor.pointer(),  edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getCurrentEdgeFromEdgeCharIndexDb(Cursor edgeCharIndexDbCursor, Cursor edgeDbCursor, String key, char value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.CHAR) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_edge_from_edge_char_index_db(edgeCharIndexDbCursor.pointer(),  edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getCurrentEdgeFromEdgeByteIndexDb(Cursor edgeByteIndexDbCursor, Cursor edgeDbCursor, String key, byte value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BYTE) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_edge_from_edge_byte_index_db(edgeByteIndexDbCursor.pointer(),  edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getCurrentEdgeFromEdgeBooleanIndexDb(Cursor edgeBooleanIndexDbCursor, Cursor edgeDbCursor, String key, boolean value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BOOLEAN) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_edge_from_edge_boolean_index_db(edgeBooleanIndexDbCursor.pointer(),  edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelArray, outVertexIdArray, inVertexIdArray);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getCurrentVertexFromVertexShortIndexDb(Cursor cursor, long vertexIdArray[], String key, short value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.SHORT) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_vertex_from_vertex_short_index_db(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getCurrentVertexFromVertexLongIndexDb(Cursor cursor, long vertexIdArray[], String key, long value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.LONG) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_vertex_from_vertex_long_index_db(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getCurrentVertexFromVertexIntIndexDb(Cursor cursor, long vertexIdArray[], String key, int value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.INT) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_vertex_from_vertex_int_index_db(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getCurrentVertexFromVertexFloatIndexDb(Cursor cursor, long vertexIdArray[], String key, float value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.FLOAT) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_vertex_from_vertex_float_index_db(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getCurrentVertexFromVertexDoubleIndexDb(Cursor cursor, long vertexIdArray[], String key, double value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.DOUBLE) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_vertex_from_vertex_double_index_db(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getCurrentVertexFromVertexCharIndexDb(Cursor cursor, long vertexIdArray[], String key, char value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.CHAR) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_vertex_from_vertex_char_index_db(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getCurrentVertexFromVertexByteIndexDb(Cursor cursor, long vertexIdArray[], String key, byte value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BYTE) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_vertex_from_vertex_byte_index_db(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getCurrentVertexFromVertexBooleanIndexDb(Cursor cursor, long vertexIdArray[], String key, boolean value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BOOLEAN) {
                //this calls mdb_cursor_get with MDB_GET_CURRENT
                //if the first call finds nothing the it calls MDB_GET_NEXT
                int rc = mdb_get_current_vertex_from_vertex_boolean_index_db(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc == MDB_NOTFOUND) {
                    return false;
                } else {
                    checkErrorCode(rc);
                    return true;
                }
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

    public boolean getCurrentEdgeFromVertex(Cursor cursor, Direction direction, String label, long fromVertexId, long edgeIdArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        Integer labelId = this.labelToIdMap.get(label);
        if (labelId != null) {
            //this calls mdb_cursor_get with MDB_GET_CURRENT
            //if the first call finds nothing the it calls MDB_GET_NEXT
            int rc = mdb_get_current_edge_from_vertex(cursor.pointer(), direction.ordinal(), labelId, fromVertexId, edgeIdArray, outVertexIdArray, inVertexIdArray);
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

    public boolean getFirstEdgeFromVertexAllLabels(Cursor cursor, Direction direction, long fromVertexId, String labelArray[], long edgeIdArray[], long outVertexIdArray[], long inVertexIdArray[]) {
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

    public boolean getNextEdgeFromVertexAllLabels(Cursor cursor, Direction direction, long fromVertexId, String labelArray[], long edgeIdArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        int labelIdArray[] = new int[1];
        labelIdArray[0] = this.labelToIdMap.get(labelArray[0]);
        int rc = mdb_get_next_edge_from_vertex_all_labels(cursor.pointer(), direction.ordinal(), fromVertexId, labelIdArray, edgeIdArray, outVertexIdArray, inVertexIdArray);
        if (rc == MDB_NOTFOUND || rc == GLMDB_END_OF_EDGES) {
            return false;
        } else {
            checkErrorCode(rc);
            labelArray[0] = this.idToLabelMap.get(labelIdArray[0]);
            return true;
        }
    }

    public boolean getCurrentEdgeFromVertexAllLabels(Cursor cursor, Direction direction, long fromVertexId, String labelArray[], long edgeIdArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        int labelIdArray[] = new int[1];
        int rc = mdb_get_current_edge_from_vertex_all_labels(cursor.pointer(), direction.ordinal(), fromVertexId, labelIdArray, edgeIdArray, outVertexIdArray, inVertexIdArray);
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

    public void setProperty(Transaction txn, Cursor cursor, long elementId, String key, Object value, boolean vertex) {
        boolean indexed = (vertex ? this.vertexIndexedKeys.contains(key) : this.edgeIndexedKeys.contains(key));
        if (value instanceof String) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.STRING, vertex, indexed);
            checkErrorCode(mdb_set_property_string(this.pointer(), txn.pointer(), cursor.pointer(), elementId, propertyKeyEnumAndId.id, (String) value, vertex, propertyKeyEnumAndId.indexed));
        } else if (value instanceof Boolean) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.BOOLEAN, vertex, indexed);
            checkErrorCode(mdb_set_property_boolean(this.pointer(), txn.pointer(), cursor.pointer(), elementId, propertyKeyEnumAndId.id, (Boolean) value, vertex, propertyKeyEnumAndId.indexed));
        } else if (value instanceof Integer) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.INT, vertex, indexed);
            checkErrorCode(mdb_set_property_int(this.pointer(), txn.pointer(), cursor.pointer(), elementId, propertyKeyEnumAndId.id, (Integer) value, vertex, propertyKeyEnumAndId.indexed));
        } else if (value instanceof Long) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.LONG, vertex, indexed);
            checkErrorCode(mdb_set_property_long(this.pointer(), txn.pointer(), cursor.pointer(), elementId, propertyKeyEnumAndId.id, (Long) value, vertex, propertyKeyEnumAndId.indexed));
        } else if (value instanceof Float) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.FLOAT, vertex, indexed);
            checkErrorCode(mdb_set_property_float(this.pointer(), txn.pointer(), cursor.pointer(), elementId, propertyKeyEnumAndId.id, (Float) value, vertex, propertyKeyEnumAndId.indexed));
        } else if (value instanceof Double) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.DOUBLE, vertex, indexed);
            checkErrorCode(mdb_set_property_double(this.pointer(), txn.pointer(), cursor.pointer(), elementId, propertyKeyEnumAndId.id, (Double) value, vertex, propertyKeyEnumAndId.indexed));
        } else if (value instanceof Character) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.CHAR, vertex, indexed);
            checkErrorCode(mdb_set_property_char(this.pointer(), txn.pointer(), cursor.pointer(), elementId, propertyKeyEnumAndId.id, (Character) value, vertex, propertyKeyEnumAndId.indexed));
        } else if (value instanceof Byte) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.BYTE, vertex, indexed);
            checkErrorCode(mdb_set_property_byte(this.pointer(), txn.pointer(), cursor.pointer(), elementId, propertyKeyEnumAndId.id, (Byte) value, vertex, propertyKeyEnumAndId.indexed));
        } else if (value instanceof Short) {
            PropertyKeyEnumAndId propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.SHORT, vertex, indexed);
            checkErrorCode(mdb_set_property_short(this.pointer(), txn.pointer(), cursor.pointer(), elementId, propertyKeyEnumAndId.id, (Short) value, vertex, propertyKeyEnumAndId.indexed));
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
        Cursor vertexCursor = openCursor(txn, DbEnum.VERTEX_PROPERTY_DB);
        Cursor edgeCursor = openCursor(txn, DbEnum.EDGE_PROPERTY_DB);
        try {
            int rc = mdb_get_first_property_key(vertexCursor.pointer(), propertyKeyIdArray, propertyTypeEnumArray, propertyIndexedArray, propertyKeyArray);
            while (rc == 0) {
                PropertyTypeEnum propertyTypeEnum = PropertyTypeEnum.fromOrdinal(propertyTypeEnumArray[0]);
                String key = (String) bytesToObject(PropertyTypeEnum.STRING, propertyKeyArray[0]);
                PropertyKeyEnumAndId propertyKeyEnumAndId = new PropertyKeyEnumAndId(propertyTypeEnum, propertyKeyIdArray[0], propertyIndexedArray[0]);
                this.vertexPropertyKeyToIdMap.put(key, propertyKeyEnumAndId);
                this.vertexPropertyKeyIdToNameMap.put(propertyKeyIdArray[0], key);

                if (propertyKeyEnumAndId.indexed) {
                    this.vertexIndexedKeys.add(key);
                }

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
                PropertyKeyEnumAndId propertyKeyEnumAndId = new PropertyKeyEnumAndId(propertyTypeEnum, propertyKeyIdArray[0], propertyIndexedArray[0]);
                this.edgePropertyKeyToIdMap.put(key, propertyKeyEnumAndId);
                this.edgePropertyKeyIdToNameMap.put(propertyKeyIdArray[0], key);
                if (propertyKeyEnumAndId.indexed) {
                    this.edgeIndexedKeys.add(key);
                }

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
        Cursor labelCursor = openCursor(txn, DbEnum.LABEL_DB);
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
        Set<String> tmpIndexedKeys;

        if (vertex) {
            tmpPropertyKeyToIdMap = this.vertexPropertyKeyToIdMap;
            tmpPropertyKeyToIdToSyncMap = this.vertexPropertyKeyToIdToSyncMap;
            tmpPropertyKeyIdToNameMap = this.vertexPropertyKeyIdToNameMap;
            tmpPropertyKeyIdToNameSyncMap = this.vertexPropertyKeyIdToNameSyncMap;
            tmpIndexedKeys = this.vertexIndexedKeys;
        } else {
            tmpPropertyKeyToIdMap = this.edgePropertyKeyToIdMap;
            tmpPropertyKeyToIdToSyncMap = this.edgePropertyKeyToIdToSyncMap;
            tmpPropertyKeyIdToNameMap = this.edgePropertyKeyIdToNameMap;
            tmpPropertyKeyIdToNameSyncMap = this.edgePropertyKeyIdToNameSyncMap;
            tmpIndexedKeys = this.edgeIndexedKeys;
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
            if (indexed) {
                tmpIndexedKeys.add(propertyKey);
            }
        } else {
            //Check if the property's indexed or type needs updating
            if (indexed != propertyKeyEnumAndId.indexed || propertyTypeEnum != propertyKeyEnumAndId.propertyTypeEnum) {

                //TODO reindex all properties
                boolean reindex = (indexed != propertyKeyEnumAndId.indexed) && indexed;

                int propertyKeyIdArray[] = new int[]{propertyKeyEnumAndId.id};
                //Do not unset the type
                if (propertyTypeEnum == PropertyTypeEnum.UNSET) {
                    checkErrorCode(mdb_set_propertykey(this.pointer(), txn.pointer(), propertyKey, propertyKeyEnumAndId.propertyTypeEnum.ordinal(), propertyKeyIdArray, vertex, indexed, true));
                } else {
                    checkErrorCode(mdb_set_propertykey(this.pointer(), txn.pointer(), propertyKey, propertyTypeEnum.ordinal(), propertyKeyIdArray, vertex, indexed, true));
                }
                propertyKeyId = propertyKeyIdArray[0];
                //Do a little sanity check
                if (propertyKeyId != propertyKeyEnumAndId.id) {
                    throw new IllegalStateException("Property key id is suppose to be the same!!! This should never happen!!!");
                }
                propertyKeyEnumAndId.indexed = indexed;
                if (propertyTypeEnum != PropertyTypeEnum.UNSET) {
                    propertyKeyEnumAndId.propertyTypeEnum = propertyTypeEnum;
                }
                tmpPropertyKeyToIdMap.put(propertyKey, propertyKeyEnumAndId);
                tmpPropertyKeyToIdToSyncMap.put(propertyKey, propertyKeyEnumAndId);
                tmpPropertyKeyIdToNameMap.put(propertyKeyId, propertyKey);
                tmpPropertyKeyIdToNameSyncMap.put(propertyKeyId, propertyKey);
                if (indexed) {
                    tmpIndexedKeys.add(propertyKey);
                }
                if (reindex) {
                    checkErrorCode(mdb_reindex_property(this.pointer(), txn.pointer(), propertyKeyEnumAndId.id, propertyKeyEnumAndId.propertyTypeEnum.ordinal(), vertex));
                }
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

    public void dropKeyIndex(Transaction txn, String key, boolean vertex) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = null;
        if (vertex) {
            if (this.vertexIndexedKeys.remove(key)) {
                propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.UNSET, vertex, false);
            }
        } else {
            if (this.edgeIndexedKeys.remove(key)) {
                propertyKeyEnumAndId = this.getOrPutPropertyKey(txn, key, PropertyTypeEnum.UNSET, vertex, false);
            }
        }
        if (propertyKeyEnumAndId != null && propertyKeyEnumAndId.propertyTypeEnum != PropertyTypeEnum.UNSET) {

            checkErrorCode(mdb_delete_index(this.pointer(), txn.pointer(), propertyKeyEnumAndId.id, vertex, propertyKeyEnumAndId.propertyTypeEnum.ordinal()));

        }
    }

    public Set<String> getIndexedKeys(Boolean vertex) {
        if (vertex) {
            return this.vertexIndexedKeys;
        } else {
            return this.edgeIndexedKeys;
        }
    }

    public boolean getFirstVertexForKeyValueFromStringIndex(Cursor cursor, long vertexIdArray[], String key, String value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.STRING) {
                int rc = mdb_get_first_vertex_for_key_value_from_string_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyValueFromStringIndex(Cursor cursor, long vertexIdArray[], String key, String value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.STRING) {
                int rc = mdb_get_next_vertex_for_key_value_for_string_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyValueFromStringIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, String value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.STRING) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_value_from_string_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyValueFromStringIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, String value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.STRING) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_value_for_string_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    //int
    public boolean getFirstVertexForKeyIntValue(Cursor cursor, long vertexIdArray[], String key, int value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.INT) {
                int rc = mdb_get_first_vertex_for_key_int_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyIntValue(Cursor cursor, long vertexIdArray[], String key, int value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.INT) {
                int rc = mdb_get_next_vertex_for_key_int_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstVertexForKeyValueFromIntIndex(Cursor cursor, long vertexIdArray[], String key, int value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.INT) {
                int rc = mdb_get_first_vertex_for_key_value_from_int_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyValueFromIntIndex(Cursor cursor, long vertexIdArray[], String key, int value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.INT) {
                int rc = mdb_get_next_vertex_for_key_value_for_int_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyValueFromIntIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, int value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.INT) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_value_from_int_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyValueFromIntIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, int value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.INT) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_value_for_int_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyIntValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, int value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.INT) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_int_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyIntValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, int value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.INT) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_int_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }


    //long
    public boolean getFirstVertexForKeyLongValue(Cursor cursor, long vertexIdArray[], String key, long value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.LONG) {
                int rc = mdb_get_first_vertex_for_key_long_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyLongValue(Cursor cursor, long vertexIdArray[], String key, long value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.LONG) {
                int rc = mdb_get_next_vertex_for_key_long_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstVertexForKeyValueFromLongIndex(Cursor cursor, long vertexIdArray[], String key, long value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.LONG) {
                int rc = mdb_get_first_vertex_for_key_value_from_long_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyValueFromLongIndex(Cursor cursor, long vertexIdArray[], String key, long value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.LONG) {
                int rc = mdb_get_next_vertex_for_key_value_for_long_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyValueFromLongIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, long value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.LONG) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_value_from_long_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyValueFromLongIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, long value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.LONG) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_value_for_long_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyLongValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, long value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.LONG) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_long_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyLongValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, long value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.LONG) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_long_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }

    //float
    public boolean getFirstVertexForKeyFloatValue(Cursor cursor, long vertexIdArray[], String key, float value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.FLOAT) {
                int rc = mdb_get_first_vertex_for_key_float_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyFloatValue(Cursor cursor, long vertexIdArray[], String key, float value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.FLOAT) {
                int rc = mdb_get_next_vertex_for_key_float_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstVertexForKeyValueFromFloatIndex(Cursor cursor, long vertexIdArray[], String key, float value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.FLOAT) {
                int rc = mdb_get_first_vertex_for_key_value_from_float_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyValueFromFloatIndex(Cursor cursor, long vertexIdArray[], String key, float value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.FLOAT) {
                int rc = mdb_get_next_vertex_for_key_value_for_float_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyValueFromFloatIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, float value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.FLOAT) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_value_from_float_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyValueFromFloatIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, float value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.FLOAT) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_value_for_float_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyFloatValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, float value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.FLOAT) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_float_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyFloatValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, float value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.FLOAT) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_float_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }

    //double
    public boolean getFirstVertexForKeyDoubleValue(Cursor cursor, long vertexIdArray[], String key, double value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.DOUBLE) {
                int rc = mdb_get_first_vertex_for_key_double_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyDoubleValue(Cursor cursor, long vertexIdArray[], String key, double value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.DOUBLE) {
                int rc = mdb_get_next_vertex_for_key_double_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstVertexForKeyValueFromDoubleIndex(Cursor cursor, long vertexIdArray[], String key, double value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.DOUBLE) {
                int rc = mdb_get_first_vertex_for_key_value_from_double_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyValueFromDoubleIndex(Cursor cursor, long vertexIdArray[], String key, double value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.DOUBLE) {
                int rc = mdb_get_next_vertex_for_key_value_for_double_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyValueFromDoubleIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, double value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.DOUBLE) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_value_from_double_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyValueFromDoubleIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, double value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.DOUBLE) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_value_for_double_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyDoubleValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, double value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.DOUBLE) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_double_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyDoubleValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, double value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.DOUBLE) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_double_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }

    //boolean
    public boolean getFirstVertexForKeyBooleanValue(Cursor cursor, long vertexIdArray[], String key, boolean value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BOOLEAN) {
                int rc = mdb_get_first_vertex_for_key_boolean_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyBooleanValue(Cursor cursor, long vertexIdArray[], String key, boolean value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BOOLEAN) {
                int rc = mdb_get_next_vertex_for_key_boolean_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstVertexForKeyValueFromBooleanIndex(Cursor cursor, long vertexIdArray[], String key, boolean value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BOOLEAN) {
                int rc = mdb_get_first_vertex_for_key_value_from_boolean_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyValueFromBooleanIndex(Cursor cursor, long vertexIdArray[], String key, boolean value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BOOLEAN) {
                int rc = mdb_get_next_vertex_for_key_value_for_boolean_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyValueFromBooleanIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, boolean value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BOOLEAN) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_value_from_boolean_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyValueFromBooleanIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, boolean value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BOOLEAN) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_value_for_boolean_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyBooleanValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, boolean value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BOOLEAN) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_boolean_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyBooleanValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, boolean value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BOOLEAN) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_boolean_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }

    //short
    public boolean getFirstVertexForKeyShortValue(Cursor cursor, long vertexIdArray[], String key, short value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.SHORT) {
                int rc = mdb_get_first_vertex_for_key_short_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyShortValue(Cursor cursor, long vertexIdArray[], String key, short value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.SHORT) {
                int rc = mdb_get_next_vertex_for_key_short_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstVertexForKeyValueFromShortIndex(Cursor cursor, long vertexIdArray[], String key, short value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.SHORT) {
                int rc = mdb_get_first_vertex_for_key_value_from_short_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyValueFromShortIndex(Cursor cursor, long vertexIdArray[], String key, short value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.SHORT) {
                int rc = mdb_get_next_vertex_for_key_value_for_short_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyValueFromShortIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, short value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.SHORT) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_value_from_short_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyValueFromShortIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, short value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.SHORT) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_value_for_short_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyShortValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, short value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.SHORT) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_short_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyShortValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, short value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.SHORT) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_short_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }

    //char
    public boolean getFirstVertexForKeyCharValue(Cursor cursor, long vertexIdArray[], String key, char value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.CHAR) {
                int rc = mdb_get_first_vertex_for_key_char_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyCharValue(Cursor cursor, long vertexIdArray[], String key, char value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.CHAR) {
                int rc = mdb_get_next_vertex_for_key_char_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstVertexForKeyValueFromCharIndex(Cursor cursor, long vertexIdArray[], String key, char value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.CHAR) {
                int rc = mdb_get_first_vertex_for_key_value_from_char_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyValueFromCharIndex(Cursor cursor, long vertexIdArray[], String key, char value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.CHAR) {
                int rc = mdb_get_next_vertex_for_key_value_for_char_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyValueFromCharIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, char value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.CHAR) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_value_from_char_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyValueFromCharIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, char value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.CHAR) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_value_for_char_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyCharValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, char value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.CHAR) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_char_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyCharValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, char value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.CHAR) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_char_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }

    //byte
    public boolean getFirstVertexForKeyByteValue(Cursor cursor, long vertexIdArray[], String key, byte value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BYTE) {
                int rc = mdb_get_first_vertex_for_key_byte_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyByteValue(Cursor cursor, long vertexIdArray[], String key, byte value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BYTE) {
                int rc = mdb_get_next_vertex_for_key_byte_value(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstVertexForKeyValueFromByteIndex(Cursor cursor, long vertexIdArray[], String key, byte value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BYTE) {
                int rc = mdb_get_first_vertex_for_key_value_from_byte_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getNextVertexForKeyValueFromByteIndex(Cursor cursor, long vertexIdArray[], String key, byte value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.vertexPropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BYTE) {
                int rc = mdb_get_next_vertex_for_key_value_for_byte_index(cursor.pointer(), vertexIdArray, propertyKeyEnumAndId.id, value);
                if (rc != MDB_NOTFOUND) {
                    checkErrorCode(rc);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyValueFromByteIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, byte value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BYTE) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_value_from_byte_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyValueFromByteIndex(Cursor edgeStringIndexDbCursor, Cursor edgeDbCursor, String key, byte value, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[]) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            //Make sure it is a string property
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BYTE) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_value_for_byte_index(edgeStringIndexDbCursor.pointer(), edgeDbCursor.pointer(), propertyKeyEnumAndId.id, value, edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray);
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
        } else {
            return false;
        }
    }

    public boolean getFirstEdgeForKeyByteValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, byte value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BYTE) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_first_edge_for_key_byte_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }

    public boolean getNextEdgeForKeyByteValue(Cursor cursor, long edgeIdArray[], String labelArray[], long outVertexIdArray[], long inVertexIdArray[], String key, byte value) {
        PropertyKeyEnumAndId propertyKeyEnumAndId = this.edgePropertyKeyToIdMap.get(key);
        if (propertyKeyEnumAndId != null) {
            if (propertyKeyEnumAndId.propertyTypeEnum == PropertyTypeEnum.BYTE) {
                int labelIdArray[] = new int[1];
                int rc = mdb_get_next_edge_for_key_byte_value(cursor.pointer(), edgeIdArray, labelIdArray, outVertexIdArray, inVertexIdArray, propertyKeyEnumAndId.id, value);
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
        } else {
            return false;
        }
    }

    public int getDbEntries(Transaction txn, DbEnum dbEnum) {
        return this.getMDBStat(txn, dbEnum).getMs_entries();
    }


    public MDBStat getMDBStat(Transaction txn, DbEnum dbEnum) {
        int ms_psize[] = new int[1];
        int ms_depth[] = new int[1];
        int ms_branch_pages[] = new int[1];
        int ms_leaf_pages[] = new int[1];
        int ms_overflow_pages[] = new int[1];
        int ms_entries[] = new int[1];
        checkErrorCode(mdb_stat(this.pointer(), txn.pointer(), dbEnum.ordinal(), ms_psize, ms_depth, ms_branch_pages, ms_leaf_pages, ms_overflow_pages, ms_entries));
        return new MDBStat(ms_psize[0], ms_depth[0], ms_branch_pages[0], ms_leaf_pages[0], ms_overflow_pages[0], ms_entries[0]);
    }

}
