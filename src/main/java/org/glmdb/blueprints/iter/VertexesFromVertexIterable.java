package org.glmdb.blueprints.iter;

import com.tinkerpop.blueprints.Direction;
import com.tinkerpop.blueprints.Vertex;
import org.glmdb.blueprints.ThunderGraph;
import org.glmdb.blueprints.ThunderVertex;
import org.glmdb.blueprints.jni.DbEnum;

import java.util.*;

/**
 * Date: 2013/11/24
 * Time: 10:22 AM
 */
public class VertexesFromVertexIterable<T extends Vertex> extends BaseThunderIterable implements Iterable<ThunderVertex> {

    private final Direction direction;
    private final List<String> labels;

    public VertexesFromVertexIterable(ThunderGraph thunderGraph, long vertexId, Direction direction, String[] labels) {
        super(thunderGraph, vertexId);
        this.direction = direction;
        this.labels = new ArrayList<String>(Arrays.asList(labels));
    }

    @Override
    public Iterator<ThunderVertex> iterator() {
        if (this.labels.isEmpty()) {
            return new VertexesIterator();
        } else {
            return new VertexesIteratorForLabel();
        }
    }

    private class VertexesIteratorForLabel extends BaseFromVertexIterator<ThunderVertex> implements Iterator {

        private Iterator<String> labelIterator;

        private VertexesIteratorForLabel() {
            super(VertexesFromVertexIterable.this.tc);
            this.labelIterator = VertexesFromVertexIterable.this.labels.iterator();
            //No need to check hasNext as Iterator<ThunderEdge> iterator() ensures there is at least one label.
            this.currentLabel = this.labelIterator.next();
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.VERTEX_DB;
        }

        @Override
        protected VertexesFromVertexIterable getParentIterable() {
            return VertexesFromVertexIterable.this;
        }

        @Override
        protected void internalRemove() {
            VertexesFromVertexIterable.this.thunderGraph.getThunder().removeVertex(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected ThunderVertex internalNext() {

            long edgeIdArray[] = new long[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];

            while (this.currentLabel != null) {
                if (this.goToFirst) {
                    this.goToFirst = false;

                    //Check if cursor needs reopening. This happens if a read only transaction is upgraded to a write transaction
                    //after the iterator was instantiated.
                    if (this.cursor ==null || !this.cursor.isAllocated()) {
                        refreshForFirst();
                    }

                    if (VertexesFromVertexIterable.this.thunderGraph.getThunder().getFirstEdgeFromVertex(
                            this.cursor, VertexesFromVertexIterable.this.direction, currentLabel, VertexesFromVertexIterable.this.vertexId, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                        this.currentEdgeOutVertexId = outVertexIdArray[0];
                        this.edgeId = edgeIdArray[0];
                        //Return the vertex that is not the from vertex.
                        if (outVertexIdArray[0] == VertexesFromVertexIterable.this.vertexId) {
                            return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, inVertexIdArray[0]);
                        } else {
                            return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, outVertexIdArray[0]);
                        }
                    } else {
                        if (this.labelIterator.hasNext()) {
                            this.currentLabel = this.labelIterator.next();
                            this.goToFirst = true;
                        } else {
                            this.currentLabel = null;
                        }
                    }
                } else {
                    //Check if cursor needs reopening. This happens if a read only transaction is upgraded to a write transaction
                    //after the iterator was instantiated.
                    if (this.cursor == null || !this.cursor.isAllocated()) {
                        refreshForNext();
                        if (this.cursor != null && VertexesFromVertexIterable.this.thunderGraph.getThunder().getCurrentEdgeFromVertex(
                                this.cursor, VertexesFromVertexIterable.this.direction, currentLabel, VertexesFromVertexIterable.this.vertexId, edgeIdArray, outVertexIdArray, inVertexIdArray)) {

                            //Check if the current is really the current.
                            //If the current has been removed then current is in fact the next
                            //if it is already next then do nothing, else get the next
                            if (this.edgeId == edgeIdArray[0]) {
                                if (VertexesFromVertexIterable.this.thunderGraph.getThunder().getNextEdgeFromVertex(
                                        this.cursor, VertexesFromVertexIterable.this.direction, currentLabel, VertexesFromVertexIterable.this.vertexId, edgeIdArray, outVertexIdArray, inVertexIdArray)) {

                                    this.currentEdgeOutVertexId = outVertexIdArray[0];
                                    this.edgeId = edgeIdArray[0];
                                    //Return the vertex that is not the from vertex.
                                    if (outVertexIdArray[0] == VertexesFromVertexIterable.this.vertexId) {
                                        return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, inVertexIdArray[0]);
                                    } else {
                                        return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, outVertexIdArray[0]);
                                    }

                                } else {
                                    return null;
                                }
                            } else {

                                this.currentEdgeOutVertexId = outVertexIdArray[0];
                                this.edgeId = edgeIdArray[0];
                                //Return the vertex that is not the from vertex.
                                if (outVertexIdArray[0] == VertexesFromVertexIterable.this.vertexId) {
                                    return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, inVertexIdArray[0]);
                                } else {
                                    return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, outVertexIdArray[0]);
                                }
                            }

                        } else {
                            return null;
                        }

                    } else {
                        if (VertexesFromVertexIterable.this.thunderGraph.getThunder().getNextEdgeFromVertex(
                                this.cursor, VertexesFromVertexIterable.this.direction, currentLabel, VertexesFromVertexIterable.this.vertexId, edgeIdArray, outVertexIdArray, inVertexIdArray)) {

                            this.currentEdgeOutVertexId = outVertexIdArray[0];
                            this.edgeId = edgeIdArray[0];
                            //Return the vertex that is not the from vertex.
                            if (outVertexIdArray[0] == VertexesFromVertexIterable.this.vertexId) {
                                return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, inVertexIdArray[0]);
                            } else {
                                return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, outVertexIdArray[0]);
                            }
                        } else {
                            if (this.labelIterator.hasNext()) {
                                this.currentLabel = this.labelIterator.next();
                                this.goToFirst = true;
                            } else {
                                this.currentLabel = null;
                            }
                        }
                    }
                }
            }
            return null;
        }
    }

    private class VertexesIterator extends BaseFromVertexIterator<ThunderVertex> implements Iterator {

        private VertexesIterator() {
            super(VertexesFromVertexIterable.this.tc);
        }

        @Override
        protected VertexesFromVertexIterable getParentIterable() {
            return VertexesFromVertexIterable.this;
        }

        @Override
        protected void internalRemove() {
            VertexesFromVertexIterable.this.thunderGraph.getThunder().removeVertex(this.tc.getTxn(), this.internalNext.getInternalId());
        }

        @Override
        protected DbEnum getDbEnum() {
            return DbEnum.VERTEX_DB;
        }

        @Override
        protected ThunderVertex internalNext() {

            String labelArray[] = new String[1];
            long edgeIdArray[] = new long[1];
            long outVertexIdArray[] = new long[1];
            long inVertexIdArray[] = new long[1];

            if (this.goToFirst) {
                this.goToFirst = false;

                //Check if cursor needs reopening. This happens if a read only transaction is upgraded to a write transaction
                //after the iterator was instantiated.
                if (this.cursor == null || !this.cursor.isAllocated()) {
                    refreshForFirst();
                }
                if (VertexesFromVertexIterable.this.thunderGraph.getThunder().getFirstEdgeFromVertexAllLabels(
                        this.cursor, VertexesFromVertexIterable.this.direction, VertexesFromVertexIterable.this.vertexId, labelArray, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                    this.currentLabel = labelArray[0];
                    this.currentEdgeOutVertexId = outVertexIdArray[0];
                    this.edgeId = edgeIdArray[0];
                    //Return the vertex that is not the from vertex.
                    if (outVertexIdArray[0] == VertexesFromVertexIterable.this.vertexId) {
                        return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, inVertexIdArray[0]);
                    } else {
                        return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, outVertexIdArray[0]);
                    }
                } else {
                    return null;
                }
            } else {

                //Check if cursor needs reopening. This happens if a read only transaction is upgraded to a write transaction
                //after the iterator was instantiated.
                if (this.cursor == null || !this.cursor.isAllocated()) {
                    refreshForNext();
                    if (this.cursor != null && VertexesFromVertexIterable.this.thunderGraph.getThunder().getCurrentEdgeFromVertexAllLabels(
                            this.cursor, VertexesFromVertexIterable.this.direction, VertexesFromVertexIterable.this.vertexId, labelArray, edgeIdArray, outVertexIdArray, inVertexIdArray)) {


                        //Check if the current is really the current.
                        //If the current has been removed then current is in fact the next
                        //if it is already next then do nothing, else get the next
                        if (this.edgeId == edgeIdArray[0]) {
                            if (VertexesFromVertexIterable.this.thunderGraph.getThunder().getNextEdgeFromVertexAllLabels(
                                    this.cursor, VertexesFromVertexIterable.this.direction, VertexesFromVertexIterable.this.vertexId, labelArray, edgeIdArray, outVertexIdArray, inVertexIdArray)) {

                                this.currentLabel = labelArray[0];
                                this.currentEdgeOutVertexId = outVertexIdArray[0];
                                this.edgeId = edgeIdArray[0];
                                //Return the vertex that is not the from vertex.
                                if (outVertexIdArray[0] == VertexesFromVertexIterable.this.vertexId) {
                                    return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, inVertexIdArray[0]);
                                } else {
                                    return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, outVertexIdArray[0]);
                                }

                            } else {
                                return null;
                            }
                        } else {

                            this.currentLabel = labelArray[0];
                            this.currentEdgeOutVertexId = outVertexIdArray[0];
                            this.edgeId = edgeIdArray[0];
                            //Return the vertex that is not the from vertex.
                            if (outVertexIdArray[0] == VertexesFromVertexIterable.this.vertexId) {
                                return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, inVertexIdArray[0]);
                            } else {
                                return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, outVertexIdArray[0]);
                            }
                        }

                    } else {
                        return null;
                    }

                } else {
                    if (VertexesFromVertexIterable.this.thunderGraph.getThunder().getNextEdgeFromVertexAllLabels(
                            this.cursor, VertexesFromVertexIterable.this.direction, VertexesFromVertexIterable.this.vertexId, labelArray, edgeIdArray, outVertexIdArray, inVertexIdArray)) {
                        this.currentLabel = labelArray[0];
                        this.currentEdgeOutVertexId = outVertexIdArray[0];
                        this.edgeId = edgeIdArray[0];
                        //Return the vertex that is not the from vertex.
                        if (outVertexIdArray[0] == VertexesFromVertexIterable.this.vertexId) {
                            return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, inVertexIdArray[0]);
                        } else {
                            return new ThunderVertex(VertexesFromVertexIterable.this.thunderGraph, outVertexIdArray[0]);
                        }
                    } else {
                        return null;
                    }
                }

            }

        }
    }

}
