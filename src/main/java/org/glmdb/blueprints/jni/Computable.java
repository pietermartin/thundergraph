package org.glmdb.blueprints.jni;

/**
 * Created with IntelliJ IDEA.
 * User: pieter
 * Date: 2013/11/23
 * Time: 9:12 AM
 * To change this template use File | Settings | File Templates.
 */
public interface Computable<A, V> {
    V compute(A arg) throws InterruptedException;
}
