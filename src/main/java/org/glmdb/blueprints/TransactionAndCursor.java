package org.glmdb.blueprints;

import org.glmdb.blueprints.iter.BaseThunderIterator;
import org.glmdb.blueprints.jni.Cursor;
import org.glmdb.blueprints.jni.DbEnum;
import org.glmdb.blueprints.jni.Transaction;

import java.lang.ref.WeakReference;
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
//    private Set<IteratorAndCursor> iteratorCursors = new HashSet<IteratorAndCursor>();
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
    public void closeAndRemoveCursor(BaseThunderIterator iter, DbEnum dbEnum, Cursor cursor) {

        this.availableCursors.get(dbEnum).add(cursor);
        this.openCursors.remove(cursor);

//        //Remove the iter and cursor from the cache.
//        Iterator<IteratorAndCursor> iteratorAndCursorIterator = this.iteratorCursors.iterator();
//        while (iteratorAndCursorIterator.hasNext()) {
//            IteratorAndCursor ic = iteratorAndCursorIterator.next();
//            if (ic.getFirst().get() != null && ic.getFirst().get() == iter) {
//                iteratorAndCursorIterator.remove();
//            }
//        }
    }

//    public void addIteratorCursor(BaseThunderIterator iter, Cursor cursor) {
//        //Close unused cursors. This is an appropriate place to do this as when another iter is created chances are the old ones are finished
//        Iterator<IteratorAndCursor> iteratorAndCursorIterator = this.iteratorCursors.iterator();
//        while (iteratorAndCursorIterator.hasNext()) {
//            IteratorAndCursor ic = iteratorAndCursorIterator.next();
//            if (ic.getFirst().get() == null) {
//                ic.getSecond().close();
//                iteratorAndCursorIterator.remove();
//            }
//        }
//        IteratorAndCursor pair = new IteratorAndCursor(new WeakReference<BaseThunderIterator>(iter), cursor);
//        this.iteratorCursors.add(pair);
//    }

    public void addOpenCursor(Cursor cursor) {
        if (cursor == null) {
            System.out.print("");
        }
        this.openCursors.add(cursor);
    }

    void closeCursors() {
        this.vertexCursor.close();
        this.edgeCursor.close();
//        for (IteratorAndCursor pair : this.iteratorCursors) {
////            if (pair.getFirst().get()!=null) {
////                pair.getFirst().get().setRefresh(true);
////            }
//            pair.getSecond().close();
//        }
//        this.iteratorCursors.clear();
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

    private static final class IteratorAndCursor {

        WeakReference<BaseThunderIterator> obj1;
        Cursor obj2;

        public IteratorAndCursor(WeakReference<BaseThunderIterator>  obj1, Cursor obj2) {
            this.obj1 = obj1;
            this.obj2 = obj2;
        }

        public void setFirst(WeakReference<BaseThunderIterator>  obj1) {
            this.obj1 = obj1;
        }

        public void setSecond(Cursor obj2) {
            this.obj2 = obj2;
        }

        public WeakReference<BaseThunderIterator>  getFirst() {
            return obj1;
        }

        public Cursor getSecond() {
            return obj2;
        }

        public boolean equals(Object o) {
            if (this == o) return true;
            if (!(o instanceof IteratorAndCursor)) return false;

            IteratorAndCursor pair = (IteratorAndCursor) o;

            if (obj1 != null ? !obj1.equals(pair.obj1) : pair.obj1 != null) return false;
            if (obj2 != null ? !obj2.equals(pair.obj2) : pair.obj2 != null) return false;

            return true;
        }

        public int hashCode() {
            int result;
            result = (obj1 != null ? obj1.hashCode() : 0);
            result = 31 * result + (obj2 != null ? obj2.hashCode() : 0);
            return result;
        }

//        public static <WeakReference<BaseThunderIterator> , Cursor> Pair<WeakReference<BaseThunderIterator> , Cursor> make(WeakReference<BaseThunderIterator>  obj1, Cursor obj2) {
//            return new Pair<WeakReference<BaseThunderIterator> , Cursor>(obj1, obj2);
//        }

    }

    public Cursor getAndRemoveAvailableCursor(DbEnum dbEnum) {
        return availableCursors.get(dbEnum).remove(0);
    }

    public boolean hasAvailableCursors(DbEnum dbEnum) {
        return !this.availableCursors.get(dbEnum).isEmpty();
    }

}
