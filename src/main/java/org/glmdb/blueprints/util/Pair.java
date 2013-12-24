package org.glmdb.blueprints.util;

/**
 * Date: 2013/12/24
 * Time: 3:10 PM
 */
public class Pair<T1, T2> {
    private T1 obj1;
    private T2 obj2;

    public Pair(T1 obj1, T2 obj2) {
        this.obj1 = obj1;
        this.obj2 = obj2;
    }

    public void setFirst(T1 obj1) {
        this.obj1 = obj1;
    }

    public void setSecond(T2 obj2) {
        this.obj2 = obj2;
    }

    public T1 getFirst() {
        return obj1;
    }

    public T2 getSecond() {
        return obj2;
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Pair)) return false;

        Pair<T1,T2> pair = (Pair<T1,T2>) o;

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

    public static <T1, T2> Pair<T1, T2> make(T1 obj1, T2 obj2) {
        return new Pair<T1, T2>(obj1, obj2);
    }

}
