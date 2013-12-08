package org.glmdb.blueprints.jni;

import static org.glmdb.blueprints.jni.GlmdbJni.*;

/**
 * Date: 2013/11/19
 * Time: 9:07 PM
 */
public class Transaction extends NativeObject {

    private final Glmdb env;

    Transaction(Glmdb env, long self) {
        super(self);
        this.env = env;
    }

    public void renew() {
        Util.checkErrorCode(mdb_txn_renew(pointer()));
    }

    public void commit() {
        if( self != 0  ) {
            Util.checkErrorCode(mdb_txn_commit(this.env.pointer(), self));
            self = 0;
        }
    }

    public void reset() {
        checkAllocated();
        mdb_txn_reset(pointer());
    }

    public void abort() {
        if( self != 0  ) {
            mdb_txn_abort(this.env.pointer(), self);
            self = 0;
        }
    }
}
