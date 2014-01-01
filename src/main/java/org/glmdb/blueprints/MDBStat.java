package org.glmdb.blueprints;

/**
 * Date: 2013/12/31
 * Time: 12:56 PM
 */
public class MDBStat {

    private int ms_psize;
    /**
     * < Size of a database page.
     * This is currently the same for all databases.
     */
    private int ms_depth;
    /**
     * < Depth (height) of the B-tree
     */
    private int ms_branch_pages;
    /**
     * < Number of internal (non-leaf) pages
     */
    private int ms_leaf_pages;
    /**
     * < Number of leaf pages
     */
    private int ms_overflow_pages;
    /**
     * < Number of overflow pages
     */
    private int ms_entries;
    public MDBStat(int ms_psize, int ms_depth, int ms_branch_pages, int ms_leaf_pages, int ms_overflow_pages, int ms_entries) {
        this.ms_psize = ms_psize;
        this.ms_depth = ms_depth;
        this.ms_branch_pages = ms_branch_pages;
        this.ms_leaf_pages = ms_leaf_pages;
        this.ms_overflow_pages = ms_overflow_pages;
        this.ms_entries = ms_entries;
    }

    public int getMs_psize() {
        return ms_psize;
    }

    public int getMs_depth() {
        return ms_depth;
    }

    public int getMs_branch_pages() {
        return ms_branch_pages;
    }

    public int getMs_leaf_pages() {
        return ms_leaf_pages;
    }

    public int getMs_overflow_pages() {
        return ms_overflow_pages;
    }

    public int getMs_entries() {
        return ms_entries;
    }
}
