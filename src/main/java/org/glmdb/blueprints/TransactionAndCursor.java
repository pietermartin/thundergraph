package org.glmdb.blueprints;

import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;
import org.glmdb.blueprints.jni.Transaction;

import java.util.*;

/**
 * Date: 2013/11/24
 * Time: 8:18 AM
 */
public class TransactionAndCursor {

    private Transaction txn;
    private Cursor vertexCursor;
    private Cursor edgeCursor;
    private boolean readOnly;
    private Set<Cursor> openCursors = new HashSet<Cursor>();
    private Map<DbEnum, List<Cursor>> availableCursors;

    TransactionAndCursor(Transaction txn, Cursor vertexCursor, Cursor edgeCursor, boolean readOnly) {
        this.txn = txn;
        this.vertexCursor = vertexCursor;
        this.edgeCursor = edgeCursor;
        this.readOnly = readOnly;
        //Prep the map
        this.availableCursors = new HashMap<DbEnum, List<Cursor>>();
        for (DbEnum dbEnum : DbEnum.values()) {
            this.availableCursors.put(dbEnum, new ArrayList<Cursor>());
        }
    }

    public Transaction getTxn() {
        return txn;
    }

    public Cursor getVertexCursor() {
        return vertexCursor;
    }

    public Cursor getEdgeCursor() {
        return edgeCursor;
    }

    public boolean isReadOnly() {
        return readOnly;
    }

    //This gets called from hasNext()
    public void closeAndRemoveCursor(DbEnum dbEnum, Cursor cursor) {

        this.availableCursors.get(dbEnum).add(cursor);
        this.openCursors.remove(cursor);
    }

    public void addOpenCursor(Cursor cursor) {
        this.openCursors.add(cursor);
    }

    void closeCursors() {
        this.vertexCursor.close();
        this.edgeCursor.close();
        for (Cursor openCursor : this.openCursors) {
            openCursor.close();
        }
        this.openCursors.clear();
        for (List<Cursor> openCursors : this.availableCursors.values()) {
            for (Cursor c : openCursors) {
                c.close();
            }
            openCursors.clear();
        }
    }

    public Cursor getAndRemoveAvailableCursor(DbEnum dbEnum) {
        return availableCursors.get(dbEnum).remove(0);
    }

    public boolean hasAvailableCursors(DbEnum dbEnum) {
        return !this.availableCursors.get(dbEnum).isEmpty();
    }

}
