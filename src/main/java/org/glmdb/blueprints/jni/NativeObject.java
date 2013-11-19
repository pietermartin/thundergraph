package org.glmdb.blueprints.jni;

/**
 * Date: 2013/11/18
 * Time: 8:37 PM
 */
public class NativeObject {

    protected long self;

    protected NativeObject(long self) {
        this.self = self;
        if( self ==0 ) {
            throw new OutOfMemoryError("Failure allocating native heap memory");
        }
    }

    long pointer() {
        checkAllocated();
        return self;
    }

    public boolean isAllocated() {
        return self !=0;
    }

    protected void checkAllocated() {
        if( !isAllocated() ) {
            throw new RuntimeException("Native object has been freed.");
        }
    }
}
