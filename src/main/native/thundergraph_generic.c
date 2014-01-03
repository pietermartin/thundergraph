#include "thundergraph_generic.h"

#ifndef THUNDERGRAPH_STRING
#define THUNDERGRAPH_STRING
#include "thundergraph_string.h"
#endif
#ifndef THUNDERGRAPH_INT
#define THUNDERGRAPH_INT
#include "thundergraph_int.h"
#endif
#ifndef THUNDERGRAPH_LONG
#define THUNDERGRAPH_LONG
#include "thundergraph_long.h"
#endif
#ifndef THUNDERGRAPH_FLOAT
#define THUNDERGRAPH_FLOAT
#include "thundergraph_float.h"
#endif
#ifndef THUNDERGRAPH_DOUBLE
#define THUNDERGRAPH_DOUBLE
#include "thundergraph_double.h"
#endif
#ifndef THUNDERGRAPH_BOOLLEAN
#define THUNDERGRAPH_BOOLEAN
#include "thundergraph_boolean.h"
#endif
#ifndef THUNDERGRAPH_SHORT
#define THUNDERGRAPH_SHORT
#include "thundergraph_short.h"
#endif
#ifndef THUNDERGRAPH_CHAR
#define THUNDERGRAPH_CHAR
#include "thundergraph_char.h"
#endif
#ifndef THUNDERGRAPH_BYTE
#define THUNDERGRAPH_BYTE
#include "thundergraph_byte.h"
#endif

int getVertexProperty(MDB_cursor *cursor, jlong vertexId, jint propertyKeyId, MDB_val *data) {
	MDB_val key;
	VertexDbId id;
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VPROPERTY_KEY;
	id.propertykeyId = propertyKeyId;
	id.labelId = -1;
	id.edgeId = -1LL;
	key.mv_size = sizeof(VertexDbId);
	key.mv_data = &id;
	return mdb_cursor_get(cursor, &key, data, MDB_SET_KEY);
}

int getFirstVertex(MDB_cursor *cursor, long long *vertexIdResultC) {

	int rc;
	unsigned char foundVertex = 1;
	MDB_val key, data;

	rc = mdb_cursor_get(cursor, &key, &data, MDB_FIRST);
	if (rc == 0) {
		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (vertexDbId.coreOrPropertyEnum == VCORE) {
			foundVertex = 0;
		} else {
			rc = GLMDB_DB_CORRUPT;
		}
	}

	if (rc == 0 && foundVertex == 0) {
		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		*vertexIdResultC = vertexDbId.vertexId;
	}

	return rc;

}

int getNextVertex(MDB_cursor *cursor, long long previousVertexId, long long *vertexIdResultC) {

	int rc;
	unsigned char foundVertex = 1;
	MDB_val vertexKey, data;
	//This is bypassing some bug somewhere
	//TODO remove this mdb_cursor_get
	rc = mdb_cursor_get(cursor, &vertexKey, &data, MDB_FIRST);

	VertexDbId id;
	initVertexDbId(&id);
	id.vertexId = (long long) previousVertexId + 1LL;
//	id.coreOrPropertyEnum = VCORE;
	vertexKey.mv_size = sizeof(VertexDbId);
	vertexKey.mv_data = &id;
	rc = mdb_cursor_get(cursor, &vertexKey, &data, MDB_SET_RANGE);
	if (rc == 0) {
		VertexDbId vertexDbId = *((VertexDbId *) (vertexKey.mv_data));

		if (vertexDbId.coreOrPropertyEnum == VCORE) {
			foundVertex = 0;
		}
	}

	if (rc == 0 && foundVertex == 0) {
		VertexDbId vertexDbId = *((VertexDbId *) (vertexKey.mv_data));
		*vertexIdResultC = vertexDbId.vertexId;
	}

	return rc;

}

int removeVertex(MDB_txn *txn, GLMDB_env *genv, jlong vertexId) {
	//Remove all out and in edges
	int rc;
	MDB_val key, data;
	MDB_val inverseKey, inverseData;
	VertexDbId inverseId;
	initVertexDbId(&inverseId);
	MDB_cursor *vertexCursor;
	MDB_cursor *inverseCursor;
	MDB_cursor *edgeCursor;
	MDB_cursor *vertexPropertyKeyInverseDbCursor;
	rc = mdb_cursor_open(txn, genv->vertexDb, &vertexCursor);
	if (rc != 0) {
		goto fail;
	}
	rc = mdb_cursor_open(txn, genv->vertexDb, &inverseCursor);
	if (rc != 0) {
		goto fail;
	}
	rc = mdb_cursor_open(txn, genv->edgeDb, &edgeCursor);
	if (rc != 0) {
		goto fail;
	}
	rc = mdb_cursor_open(txn, genv->vertexPropertyKeyInverseDb, &vertexPropertyKeyInverseDbCursor);
	if (rc != 0) {
		goto fail;
	}
	VertexDbId id;
	initVertexDbId(&id);
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VCORE;
	key.mv_size = sizeof(VertexDbId);
	key.mv_data = &id;

	rc = mdb_del(txn, genv->vertexDb, &key, &data);
	if (rc != 0) {
		goto fail;
	}

	initVertexDbId(&id);
	id.vertexId = vertexId;
	id.coreOrPropertyEnum = VCORE;
	key.mv_size = sizeof(VertexDbId);
	key.mv_data = &id;

	//First delete all edges
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) vertexCursor, &key, &data, MDB_SET_RANGE)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (vertexId == vertexDbId.vertexId) {
			if (vertexDbId.coreOrPropertyEnum == INLABEL || vertexDbId.coreOrPropertyEnum == OUTLABEL) {

				rc = internalRemoveEdge(genv, txn, edgeCursor, vertexDbId.edgeId);
				if (rc != 0) {
					rc = GLMDB_DB_CORRUPT;
					goto fail;
				}
				//get the inverse side
				inverseId.vertexId = *(long long *) data.mv_data;
				inverseId.coreOrPropertyEnum = (vertexDbId.coreOrPropertyEnum == OUTLABEL ? INLABEL : OUTLABEL);
				inverseId.labelId = vertexDbId.labelId;
				inverseId.edgeId = vertexDbId.edgeId;
				inverseKey.mv_size = sizeof(VertexDbId);
				inverseKey.mv_data = &inverseId;

				//delete inverse
				rc = mdb_del(txn, genv->vertexDb, &inverseKey, &inverseData);
				if (rc != 0) {
					rc = GLMDB_DB_CORRUPT;
					goto fail;
				}

				//delete current
				key.mv_size = sizeof(VertexDbId);
				key.mv_data = &vertexDbId;
				rc = mdb_del(txn, genv->vertexDb, &key, &data);
				if (rc != 0) {
					rc = GLMDB_DB_CORRUPT;
					goto fail;
				}

			} else if (vertexDbId.coreOrPropertyEnum == VPROPERTY_KEY) {

				//If it was indexed then remove all entries from the index
				MDB_val propertyKeyInverseKey, propertyKeyInverseData;
				propertyKeyInverseKey.mv_size = sizeof(int);
				propertyKeyInverseKey.mv_data = &(vertexDbId.propertykeyId);

				rc = mdb_cursor_get(vertexPropertyKeyInverseDbCursor, &propertyKeyInverseKey, &propertyKeyInverseData, MDB_SET_KEY);
				if (rc != 0) {
					rc = GLMDB_PROPERTY_KEY_NOT_FOUND;
					goto fail;
				}

				PropertyKeyInverseDataStruct *propertyKeyInverseDataStruct = (PropertyKeyInverseDataStruct *) propertyKeyInverseData.mv_data;
				if (propertyKeyInverseDataStruct->indexed == 1) {
					switch (propertyKeyInverseDataStruct->type) {
					case BOOLEAN:
						;
						MDB_cursor *booleanIndexCursor;
						rc = mdb_cursor_open(txn, genv->vertexBooleanIndexDb, &booleanIndexCursor);
						if (rc != 0) {
							goto fail;
						}
						rc = removeBooleanIndex(booleanIndexCursor, vertexId, vertexDbId.propertykeyId, *((unsigned char *) data.mv_data));
						mdb_cursor_close(booleanIndexCursor);
						break;
					case BYTE:
						;
						MDB_cursor *byteIndexCursor;
						rc = mdb_cursor_open(txn, genv->vertexByteIndexDb, &byteIndexCursor);
						if (rc != 0) {
							goto fail;
						}
						rc = removeByteIndex(byteIndexCursor, vertexId, vertexDbId.propertykeyId, *((signed char *) data.mv_data));
						mdb_cursor_close(byteIndexCursor);
						break;
					case SHORT:
						;
						MDB_cursor *shortIndexCursor;
						rc = mdb_cursor_open(txn, genv->vertexShortIndexDb, &shortIndexCursor);
						if (rc != 0) {
							goto fail;
						}
						rc = removeShortIndex(shortIndexCursor, vertexId, vertexDbId.propertykeyId, *((short *) data.mv_data));
						mdb_cursor_close(shortIndexCursor);
						break;
					case INT:
						;
						MDB_cursor *intIndexCursor;
						rc = mdb_cursor_open(txn, genv->vertexIntIndexDb, &intIndexCursor);
						if (rc != 0) {
							goto fail;
						}
						rc = removeIntIndex(intIndexCursor, vertexId, vertexDbId.propertykeyId, *((int *) data.mv_data));
						mdb_cursor_close(intIndexCursor);
						break;
					case LONG:
						;
						MDB_cursor *longIndexCursor;
						rc = mdb_cursor_open(txn, genv->vertexLongIndexDb, &longIndexCursor);
						if (rc != 0) {
							goto fail;
						}
						rc = removeLongIndex(longIndexCursor, vertexId, vertexDbId.propertykeyId, *((long long *) data.mv_data));
						mdb_cursor_close(longIndexCursor);
						break;
					case FLOAT:
						;
						MDB_cursor *floatIndexCursor;
						rc = mdb_cursor_open(txn, genv->vertexFloatIndexDb, &floatIndexCursor);
						if (rc != 0) {
							goto fail;
						}
						rc = removeFloatIndex(floatIndexCursor, vertexId, vertexDbId.propertykeyId, *((float *) data.mv_data));
						mdb_cursor_close(floatIndexCursor);
						break;
					case DOUBLE:
						;
						MDB_cursor *doubleIndexCursor;
						rc = mdb_cursor_open(txn, genv->vertexDoubleIndexDb, &doubleIndexCursor);
						if (rc != 0) {
							goto fail;
						}
						rc = removeDoubleIndex(doubleIndexCursor, vertexId, vertexDbId.propertykeyId, *((double *) data.mv_data));
						mdb_cursor_close(doubleIndexCursor);
						break;
					case CHAR:
						;
						MDB_cursor *charIndexCursor;
						rc = mdb_cursor_open(txn, genv->vertexCharIndexDb, &charIndexCursor);
						if (rc != 0) {
							goto fail;
						}
						rc = removeCharIndex(charIndexCursor, vertexId, vertexDbId.propertykeyId, *((unsigned short *) data.mv_data));
						mdb_cursor_close(charIndexCursor);
						break;
					case STRING:
						;
						MDB_cursor *stringIndexCursor;
						rc = mdb_cursor_open(txn, genv->vertexStringIndexDb, &stringIndexCursor);
						if (rc != 0) {
							goto fail;
						}
						rc = removeStringIndex(stringIndexCursor, vertexId, vertexDbId.propertykeyId, data.mv_size, (char *) data.mv_data);
						mdb_cursor_close(stringIndexCursor);
						break;
					default:
						rc = GLMDB_INVALID_SEQUENCE;
						break;
					}
					if (rc != 0) {
						rc = GLMDB_DB_CORRUPT;
						goto fail;
					}
				}

				//delete current, i.e. the edge property
				key.mv_size = sizeof(VertexDbId);
				key.mv_data = &vertexDbId;
				rc = mdb_del(txn, genv->vertexDb, &key, &data);
				if (rc != 0) {
					rc = GLMDB_DB_CORRUPT;
					goto fail;
				}

			} else if (vertexDbId.coreOrPropertyEnum == VCORE) {
				rc = GLMDB_DB_CORRUPT;
				goto fail;
			} else {
				rc = GLMDB_DB_CORRUPT;
				goto fail;
			}

			initVertexDbId(&id);
			id.vertexId = vertexId;
			id.coreOrPropertyEnum = VCORE;
			key.mv_size = sizeof(VertexDbId);
			key.mv_data = &id;
		} else {
			break;
		}

	}

	fail: if (rc == MDB_NOTFOUND) {
		//This means MDB_NEXT returned nada, i.e. there were no more edges to delete
		rc = 0;
	}
	mdb_cursor_close(vertexPropertyKeyInverseDbCursor);
	mdb_cursor_close(vertexCursor);
	mdb_cursor_close(inverseCursor);
	mdb_cursor_close(edgeCursor);
	return rc;
}

int internalRemoveEdge(GLMDB_env *genv, MDB_txn *txn, MDB_cursor *edgeCursor, jlong edgeId) {
	MDB_val edgeKey, edgeData;
	int rc = getEdge(edgeCursor, edgeId, &edgeKey, &edgeData);
	if (rc == 0) {
		rc = mdb_del(txn, genv->edgeDb, &edgeKey, &edgeData);
	}
	if (rc == 0) {
		//delete the properties
		rc = deleteEdgeProperties(genv, txn, edgeCursor, edgeKey, edgeData, edgeId);
	}

	if (rc == MDB_NOTFOUND) {
		rc = 0;
	}
	return rc;
}

int removeEdge(MDB_txn *txn, GLMDB_env *genv, jlong edgeId) {

	int rc = 0;
	MDB_val edgeKey, vertexKey, data, vertexData;
	MDB_cursor *edgeCursor;
	MDB_cursor *vertexCursor;

	rc = mdb_cursor_open(txn, genv->vertexDb, &vertexCursor);
	if (rc != 0) {
		goto fail;
	}
	rc = mdb_cursor_open(txn, genv->edgeDb, &edgeCursor);
	if (rc != 0) {
		goto fail;
	}

	rc = getEdge(edgeCursor, edgeId, &edgeKey, &data);
	if (rc != 0) {
		goto fail;
	}
	EdgeData edgeData = *((EdgeData *) (data.mv_data));

	VertexDbId vertexDbId;

//Delete the out edge
	vertexDbId.vertexId = edgeData.vertexOutId;
	vertexDbId.coreOrPropertyEnum = OUTLABEL;
	vertexDbId.labelId = edgeData.labelId;
	vertexDbId.edgeId = edgeId;
	vertexKey.mv_size = sizeof(VertexDbId);
	vertexKey.mv_data = &vertexDbId;

	rc = mdb_cursor_get(vertexCursor, &vertexKey, &vertexData, MDB_SET);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}
	rc = mdb_cursor_del((MDB_cursor *) (long) vertexCursor, 0);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}

//Delete the in edge
	vertexDbId.vertexId = edgeData.vertexInId;
	vertexDbId.coreOrPropertyEnum = INLABEL;
	vertexDbId.labelId = edgeData.labelId;
	vertexDbId.edgeId = edgeId;
	vertexKey.mv_size = sizeof(VertexDbId);
	vertexKey.mv_data = &vertexDbId;

	rc = mdb_cursor_get(vertexCursor, &vertexKey, &vertexData, MDB_SET);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}
	rc = mdb_cursor_del((MDB_cursor *) (long) vertexCursor, 0);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}

//delete the edge
	MDB_val edgeKeyToDelete, edgeDataToDelete;
	EdgeDbId edgeDbIdToDelete;
	edgeDbIdToDelete.edgeId = edgeId;
	edgeDbIdToDelete.coreOrPropertyEnum = ECORE;
	edgeDbIdToDelete.propertykeyId = -1;
	edgeKeyToDelete.mv_size = sizeof(EdgeDbId);
	edgeKeyToDelete.mv_data = &edgeDbIdToDelete;
	rc = mdb_del(txn, genv->edgeDb, &edgeKeyToDelete, &edgeDataToDelete);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}

	//delete the properties
	rc = deleteEdgeProperties(genv, txn, edgeCursor, edgeKey, data, edgeId);

	if (rc == MDB_NOTFOUND) {
		rc = 0;
	}
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}

	fail: mdb_cursor_close(vertexCursor);
	mdb_cursor_close(edgeCursor);

	return rc;
}

int deleteEdgeProperties(GLMDB_env *genv, MDB_txn *txn, MDB_cursor *edgeCursor, MDB_val edgeKey, MDB_val data, jlong edgeId) {
	int rc = 0;
	MDB_cursor *edgePropertyKeyInverseDbCursor;
	rc = mdb_cursor_open(txn, genv->edgePropertyKeyInverseDb, &edgePropertyKeyInverseDbCursor);
	if (rc != 0) {
		goto fail;
	}

	//delete the properties
	while ((rc = mdb_cursor_get(edgeCursor, &edgeKey, &data, MDB_NEXT)) == 0) {

		EdgeDbId edgeDbId = *((EdgeDbId *) (edgeKey.mv_data));
		if (edgeDbId.edgeId == edgeId && edgeDbId.coreOrPropertyEnum == EPROPERTY_KEY) {

			//If it was indexed then remove all entries from the index
			MDB_val propertyKeyInverseKey, propertyKeyInverseData;
			propertyKeyInverseKey.mv_size = sizeof(int);
			propertyKeyInverseKey.mv_data = &edgeDbId.propertykeyId;

			rc = mdb_cursor_get(edgePropertyKeyInverseDbCursor, &propertyKeyInverseKey, &propertyKeyInverseData, MDB_SET_KEY);
			if (rc != 0) {
				rc = GLMDB_PROPERTY_KEY_NOT_FOUND;
				goto fail;
			}

			PropertyKeyInverseDataStruct *propertyKeyInverseDataStruct = (PropertyKeyInverseDataStruct *) propertyKeyInverseData.mv_data;
			if (propertyKeyInverseDataStruct->indexed == 1) {
				switch (propertyKeyInverseDataStruct->type) {
				case BOOLEAN:
					;
					MDB_cursor *booleanIndexCursor;
					rc = mdb_cursor_open(txn, genv->edgeBooleanIndexDb, &booleanIndexCursor);
					if (rc != 0) {
						goto fail;
					}
					rc = removeBooleanIndex(booleanIndexCursor, edgeId, edgeDbId.propertykeyId, *((unsigned char *) data.mv_data));
					mdb_cursor_close(booleanIndexCursor);
					break;
				case BYTE:
					;
					MDB_cursor *byteIndexCursor;
					rc = mdb_cursor_open(txn, genv->edgeByteIndexDb, &byteIndexCursor);
					if (rc != 0) {
						goto fail;
					}
					rc = removeByteIndex(byteIndexCursor, edgeId, edgeDbId.propertykeyId, *((signed char *) data.mv_data));
					mdb_cursor_close(byteIndexCursor);
					break;
				case SHORT:
					;
					MDB_cursor *shortIndexCursor;
					rc = mdb_cursor_open(txn, genv->edgeShortIndexDb, &shortIndexCursor);
					if (rc != 0) {
						goto fail;
					}
					rc = removeShortIndex(shortIndexCursor, edgeId, edgeDbId.propertykeyId, *((short *) data.mv_data));
					mdb_cursor_close(shortIndexCursor);
					break;
				case INT:
					;
					MDB_cursor *intIndexCursor;
					rc = mdb_cursor_open(txn, genv->edgeIntIndexDb, &intIndexCursor);
					if (rc != 0) {
						goto fail;
					}
					rc = removeIntIndex(intIndexCursor, edgeId, edgeDbId.propertykeyId, *((int *) data.mv_data));
					mdb_cursor_close(intIndexCursor);
					break;
				case LONG:
					;
					MDB_cursor *longIndexCursor;
					rc = mdb_cursor_open(txn, genv->edgeLongIndexDb, &longIndexCursor);
					if (rc != 0) {
						goto fail;
					}
					rc = removeLongIndex(longIndexCursor, edgeId, edgeDbId.propertykeyId, *((long long *) data.mv_data));
					mdb_cursor_close(longIndexCursor);
					break;
				case FLOAT:
					;
					MDB_cursor *floatIndexCursor;
					rc = mdb_cursor_open(txn, genv->edgeFloatIndexDb, &floatIndexCursor);
					if (rc != 0) {
						goto fail;
					}
					rc = removeFloatIndex(floatIndexCursor, edgeId, edgeDbId.propertykeyId, *((float *) data.mv_data));
					mdb_cursor_close(floatIndexCursor);
					break;
				case DOUBLE:
					;
					MDB_cursor *doubleIndexCursor;
					rc = mdb_cursor_open(txn, genv->edgeDoubleIndexDb, &doubleIndexCursor);
					if (rc != 0) {
						goto fail;
					}
					rc = removeDoubleIndex(doubleIndexCursor, edgeId, edgeDbId.propertykeyId, *((double *) data.mv_data));
					mdb_cursor_close(doubleIndexCursor);
					break;
				case CHAR:
					;
					MDB_cursor *charIndexCursor;
					rc = mdb_cursor_open(txn, genv->edgeCharIndexDb, &charIndexCursor);
					if (rc != 0) {
						goto fail;
					}
					rc = removeCharIndex(charIndexCursor, edgeId, edgeDbId.propertykeyId, *((unsigned short *) data.mv_data));
					mdb_cursor_close(charIndexCursor);
					break;
				case STRING:
					;
					MDB_cursor *stringIndexCursor;
					rc = mdb_cursor_open(txn, genv->edgeStringIndexDb, &stringIndexCursor);
					if (rc != 0) {
						goto fail;
					}
					rc = removeStringIndex(stringIndexCursor, edgeId, edgeDbId.propertykeyId, data.mv_size, (char *) data.mv_data);
					mdb_cursor_close(stringIndexCursor);
					break;
				default:
					rc = GLMDB_INVALID_SEQUENCE;
					break;
				}
				if (rc != 0) {
					rc = GLMDB_DB_CORRUPT;
					goto fail;
				}
			}

			//delete the edge property
			rc = mdb_del(txn, genv->edgeDb, &edgeKey, &data);
			if (rc == MDB_NOTFOUND) {
				//This happens at the end of the keys when it iterates forever on the last record.
				//When we delete what is already deleted it returns MDB_NOTFOUND
				break;
			}
			if (rc != 0) {
				rc = GLMDB_DB_CORRUPT;
				goto fail;
			}
		} else {
			break;
		}
	}
	fail: mdb_cursor_close(edgePropertyKeyInverseDbCursor);
	return rc;
}

void initVertexDbId(VertexDbId *vertexDbId) {
	vertexDbId->vertexId = -1LL;
	vertexDbId->coreOrPropertyEnum = VCORE;
	vertexDbId->propertykeyId = -1;
	vertexDbId->labelId = -1;
	vertexDbId->edgeId = -1LL;
}

void initEdgeDbId(EdgeDbId *edgeDbId) {
	edgeDbId->edgeId = -1LL;
	edgeDbId->coreOrPropertyEnum = ECORE;
	edgeDbId->propertykeyId = -1;
}

void initEdgeData(EdgeData *edgeData) {
	edgeData->vertexInId = -1LL;
	edgeData->vertexOutId = -1LL;
	edgeData->labelId = -1;
}

int getEdge(MDB_cursor *cursor, jlong edgeId, MDB_val *edgeKey, MDB_val *edgeData) {
	EdgeDbId id;
	id.edgeId = (long) edgeId;
	id.coreOrPropertyEnum = ECORE;
	id.propertykeyId = -1;
	(*edgeKey).mv_size = sizeof(EdgeDbId);
	(*edgeKey).mv_data = &id;
	return mdb_cursor_get((MDB_cursor *) (long) cursor, edgeKey, edgeData, MDB_SET_KEY);
}

void printVertexRecord(MDB_val key, MDB_val data) {

	VertexDbId vertexDbId = (*((VertexDbId *) (key.mv_data)));
	switch (vertexDbId.coreOrPropertyEnum) {
	case VCORE:
		printf("key: %lld, labelId = %i, type = VCORE, propertyKey: %i, edgeId = %lld,  data: %s\n", (long long) vertexDbId.vertexId,
				vertexDbId.labelId, vertexDbId.propertykeyId, (long long) vertexDbId.edgeId,
				*((char *) data.mv_data) == '\0' ? "NULL" : "????");
		break;
	case VPROPERTY_KEY:
		printf("key: %lld, labelId = %i, type = VPROPERTY_KEY, propertyKey: %i, edgeId = %lld,  data: %.*s\n",
				(long long) vertexDbId.vertexId, vertexDbId.labelId, vertexDbId.propertykeyId, (long long) vertexDbId.edgeId,
				(int) data.mv_size, (char *) data.mv_data);
		break;
	case OUTLABEL:
		printf("key: %lld, labelId = %i, type = OUTLABEL, propertyKey: %i, edgeId = %lld,  data: %lld\n", (long long) vertexDbId.vertexId,
				vertexDbId.labelId, vertexDbId.propertykeyId, (long long) vertexDbId.edgeId, *(long long *) data.mv_data);
		break;
	case INLABEL:
		printf("key: %lld, labelId = %i, type = INLABEL, propertyKey: %i, edgeId = %lld,  data: %lld\n", (long long) vertexDbId.vertexId,
				vertexDbId.labelId, vertexDbId.propertykeyId, (long long) vertexDbId.edgeId, *(long long *) data.mv_data);
		break;
	}
}

int getFirstEdgefromVertex(MDB_cursor *cursor, jint direction, jint labelId, jlong fromVertexId, jlong *edgeIdResultC, jlong *outVertexIdC,
		jlong *inVertexIdC) {

	int rc;
	MDB_val key, data;
	VertexDbId id;
	initVertexDbId(&id);
	id.vertexId = fromVertexId;
	switch (direction) {
	case 0:
		id.coreOrPropertyEnum = OUTLABEL;
		break;
	case 1:
		id.coreOrPropertyEnum = INLABEL;
		break;
	case 2:
		//for direction both place the cursor at the first out label
		id.coreOrPropertyEnum = OUTLABEL;
		break;
	default:
		rc = GLMDB_UNDEFINED_DIRECTION;
		goto fail;
	}
	id.labelId = labelId;
	key.mv_size = sizeof(VertexDbId);
	key.mv_data = &id;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_SET_RANGE);
	if (rc == 0) {
		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (fromVertexId == vertexDbId.vertexId && labelId == vertexDbId.labelId) {

			switch (direction) {
			case 0:
				if (vertexDbId.coreOrPropertyEnum != OUTLABEL) {
					rc = GLMDB_END_OF_EDGES;
					goto fail;
				}
				*outVertexIdC = vertexDbId.vertexId;
				*inVertexIdC = *((jlong *) (data.mv_data));
				break;
			case 1:
				if (vertexDbId.coreOrPropertyEnum != INLABEL) {
					rc = GLMDB_END_OF_EDGES;
					goto fail;
				}
				*outVertexIdC = *((jlong *) (data.mv_data));
				*inVertexIdC = vertexDbId.vertexId;
				break;
			case 2:
				if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
					*outVertexIdC = vertexDbId.vertexId;
					*inVertexIdC = *((jlong *) (data.mv_data));
				} else if (vertexDbId.coreOrPropertyEnum == INLABEL) {
					*outVertexIdC = *((jlong *) (data.mv_data));
					*inVertexIdC = vertexDbId.vertexId;
				} else {
					rc = GLMDB_END_OF_EDGES;
					goto fail;
				}
				break;
			default:
				rc = GLMDB_UNDEFINED_DIRECTION;
				goto fail;
			}

			*edgeIdResultC = vertexDbId.edgeId;
		} else {
			rc = GLMDB_END_OF_EDGES;
		}
	}
	fail: return rc;
}

int getNextEdgefromVertex(MDB_cursor *cursor, jint direction, jint labelId, jlong fromVertexId, jlong *edgeIdResultC, jlong *outVertexIdC,
		jlong *inVertexIdC) {

	int rc = 0;
	VertexDbId id;
	initVertexDbId(&id);
	MDB_val key, data;
	key.mv_size = sizeof(VertexDbId);
	key.mv_data = &id;

	jlong tmpEdgeIdResultC;
	jlong tmpOutVertexIdC;
	jlong tmpInVertexIdC;

	//First do a MDB_GET_CURRENT. Check to see if the cursor has moved. i.e. the value has been removed from under it.
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_GET_CURRENT);
	if (rc != 0) {
		goto fail;
	}

//	printVertexRecord(key, data);

	VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
	if (fromVertexId == vertexDbId.vertexId && labelId == vertexDbId.labelId) {
		switch (direction) {
		case 0:
			if (vertexDbId.coreOrPropertyEnum != OUTLABEL) {
				rc = GLMDB_END_OF_EDGES;
				goto fail;
			}
			tmpOutVertexIdC = vertexDbId.vertexId;
			tmpInVertexIdC = *((jlong *) (data.mv_data));
			break;
		case 1:
			if (vertexDbId.coreOrPropertyEnum != INLABEL) {
				rc = GLMDB_END_OF_EDGES;
				goto fail;
			}
			tmpOutVertexIdC = *((jlong *) (data.mv_data));
			tmpInVertexIdC = vertexDbId.vertexId;
			break;
		case 2:
			if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
				tmpOutVertexIdC = vertexDbId.vertexId;
				tmpInVertexIdC = *((jlong *) (data.mv_data));
			} else if (vertexDbId.coreOrPropertyEnum == INLABEL) {
				tmpOutVertexIdC = *((jlong *) (data.mv_data));
				tmpInVertexIdC = vertexDbId.vertexId;
			} else {
				rc = GLMDB_END_OF_EDGES;
				goto fail;
			}
			break;
		default:
			rc = GLMDB_UNDEFINED_DIRECTION;
			goto fail;
		}
		tmpEdgeIdResultC = vertexDbId.edgeId;

//		printf("tmpEdgeIdResultC = %llu, tmpOutVertexIdC = %llu, tmpInVertexIdC = %llu\n", (long long)tmpEdgeIdResultC, (long long)tmpOutVertexIdC, (long long)tmpInVertexIdC);
//		printf("edgeIdResultC = %llu, outVertexIdC = %llu, inVertexIdC = %llu\n", (long long)*edgeIdResultC, (long long)*outVertexIdC, (long long)*inVertexIdC);

		if (tmpEdgeIdResultC == *edgeIdResultC && tmpOutVertexIdC == *outVertexIdC && tmpInVertexIdC == *inVertexIdC) {

//			printf("the same\n");

			rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT);
			if (rc != 0) {
				goto fail;
			}
//			printf("the same rc = %i\n", rc);
			vertexDbId = *((VertexDbId *) (key.mv_data));
			if (fromVertexId == vertexDbId.vertexId && labelId == vertexDbId.labelId) {
				switch (direction) {
				case 0:
					if (vertexDbId.coreOrPropertyEnum != OUTLABEL) {
						rc = GLMDB_END_OF_EDGES;
						goto fail;
					}
					*outVertexIdC = vertexDbId.vertexId;
					*inVertexIdC = *((jlong *) (data.mv_data));
					break;
				case 1:
					if (vertexDbId.coreOrPropertyEnum != INLABEL) {
						rc = GLMDB_END_OF_EDGES;
						goto fail;
					}
					*outVertexIdC = *((jlong *) (data.mv_data));
					*inVertexIdC = vertexDbId.vertexId;
					break;
				case 2:
					if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
						*outVertexIdC = vertexDbId.vertexId;
						*inVertexIdC = *((jlong *) (data.mv_data));
					} else if (vertexDbId.coreOrPropertyEnum == INLABEL) {
						*outVertexIdC = *((jlong *) (data.mv_data));
						*inVertexIdC = vertexDbId.vertexId;
					} else {
						rc = GLMDB_END_OF_EDGES;
						goto fail;
					}
					break;
				default:
					rc = GLMDB_UNDEFINED_DIRECTION;
					goto fail;
				}
			} else {
				rc = GLMDB_END_OF_EDGES;
			}
			*edgeIdResultC = vertexDbId.edgeId;

		} else {

//			printf("not the same\n");

			*outVertexIdC = tmpOutVertexIdC;
			*inVertexIdC = tmpInVertexIdC;
			*edgeIdResultC = tmpEdgeIdResultC;

		}

	} else {
		rc = GLMDB_END_OF_EDGES;
	}

	fail:
//	printf("getNextEdgefromVertex return %i\n", rc);
	return rc;
}

int getCurrentEdgefromVertex(MDB_cursor *cursor, jint direction, jint labelId, jlong fromVertexId, jlong *edgeIdResultC,
		jlong *outVertexIdC, jlong *inVertexIdC) {

	int rc = 0;
	VertexDbId id;
	initVertexDbId(&id);
	MDB_val key, data;
	key.mv_size = sizeof(VertexDbId);
	key.mv_data = &id;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_GET_CURRENT);
	if (rc != 0) {
		goto fail;
	}
	unsigned char foundEdge = 0;
	VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
	if (fromVertexId == vertexDbId.vertexId && labelId == vertexDbId.labelId) {
		switch (direction) {
		case 0:
			if (vertexDbId.coreOrPropertyEnum != OUTLABEL) {
				rc = GLMDB_END_OF_EDGES;
				goto fail;
			}
			*outVertexIdC = vertexDbId.vertexId;
			*inVertexIdC = *((jlong *) (data.mv_data));
			foundEdge = 1;
			break;
		case 1:
			if (vertexDbId.coreOrPropertyEnum != INLABEL) {
				rc = GLMDB_END_OF_EDGES;
				goto fail;
			}
			*outVertexIdC = *((jlong *) (data.mv_data));
			*inVertexIdC = vertexDbId.vertexId;
			foundEdge = 1;
			break;
		case 2:
			if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
				*outVertexIdC = vertexDbId.vertexId;
				*inVertexIdC = *((jlong *) (data.mv_data));
			} else if (vertexDbId.coreOrPropertyEnum == INLABEL) {
				*outVertexIdC = *((jlong *) (data.mv_data));
				*inVertexIdC = vertexDbId.vertexId;
			} else {
				rc = GLMDB_END_OF_EDGES;
				goto fail;
			}
			foundEdge = 1;
			break;
		default:
			rc = GLMDB_UNDEFINED_DIRECTION;
			goto fail;
		}
		*edgeIdResultC = vertexDbId.edgeId;
	} else {
		rc = GLMDB_END_OF_EDGES;
	}

	if (foundEdge == 0) {
		rc = getNextEdgefromVertex(cursor, direction, labelId, fromVertexId, edgeIdResultC, outVertexIdC, inVertexIdC);
	}

	fail: return rc;
}

int getFirstEdgefromVertexAllLabels(MDB_cursor *cursor, jint direction, jlong fromVertexId, jint *labelIdResultC, jlong *edgeIdResultC,
		jlong *outVertexIdC, jlong *inVertexIdC) {

	int rc;
	MDB_val key, data;
	VertexDbId id;
	initVertexDbId(&id);
	id.vertexId = fromVertexId;
	id.coreOrPropertyEnum = VCORE;
	key.mv_size = sizeof(VertexDbId);
	key.mv_data = &id;
	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_SET_RANGE);
	VertexDbId sanityCheckVertexDbId = *((VertexDbId *) (key.mv_data));
	if (sanityCheckVertexDbId.coreOrPropertyEnum != VCORE) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}

	if (rc == 0) {

		while ((rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_NEXT)) == 0) {

			VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
			if (fromVertexId == vertexDbId.vertexId) {
				if (direction == 0) {
					if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
						*outVertexIdC = vertexDbId.vertexId;
						*inVertexIdC = *((jlong *) (data.mv_data));
						*labelIdResultC = vertexDbId.labelId;
						*edgeIdResultC = vertexDbId.edgeId;
						break;
					}
				} else if (direction == 1) {
					if (vertexDbId.coreOrPropertyEnum == INLABEL) {
						*outVertexIdC = *((jlong *) (data.mv_data));
						*inVertexIdC = vertexDbId.vertexId;
						*labelIdResultC = vertexDbId.labelId;
						*edgeIdResultC = vertexDbId.edgeId;
						break;
					}
				} else {
					if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
						*outVertexIdC = vertexDbId.vertexId;
						*inVertexIdC = *((jlong *) (data.mv_data));
						*labelIdResultC = vertexDbId.labelId;
						*edgeIdResultC = vertexDbId.edgeId;
						break;
					} else if (vertexDbId.coreOrPropertyEnum == INLABEL) {
						*outVertexIdC = *((jlong *) (data.mv_data));
						*inVertexIdC = vertexDbId.vertexId;
						*labelIdResultC = vertexDbId.labelId;
						*edgeIdResultC = vertexDbId.edgeId;
						break;
					}
				}
			} else {
				rc = GLMDB_END_OF_EDGES;
			}
		}
	}
	fail: return rc;
}

int getCurrentEdgefromVertexAllLabels(MDB_cursor *cursor, jint direction, jlong fromVertexId, jint *labelIdResultC, jlong *edgeIdResultC,
		jlong *outVertexIdC, jlong *inVertexIdC) {

	int rc = 0;
	VertexDbId id;
	initVertexDbId(&id);
	MDB_val key, data;

	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_GET_CURRENT);

	unsigned char foundEdge = 0;
	VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
	if (fromVertexId == vertexDbId.vertexId) {

		if (direction == 0) {
			if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
				*outVertexIdC = vertexDbId.vertexId;
				*inVertexIdC = *((jlong *) (data.mv_data));
				*labelIdResultC = vertexDbId.labelId;
				*edgeIdResultC = vertexDbId.edgeId;
				foundEdge = 1;
			}
		} else if (direction == 1) {
			if (vertexDbId.coreOrPropertyEnum == INLABEL) {
				*outVertexIdC = *((jlong *) (data.mv_data));
				*inVertexIdC = vertexDbId.vertexId;
				*labelIdResultC = vertexDbId.labelId;
				*edgeIdResultC = vertexDbId.edgeId;
				foundEdge = 1;
			}
		} else {
			if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
				*outVertexIdC = vertexDbId.vertexId;
				*inVertexIdC = *((jlong *) (data.mv_data));
			} else if (vertexDbId.coreOrPropertyEnum == INLABEL) {
				*outVertexIdC = *((jlong *) (data.mv_data));
				*inVertexIdC = vertexDbId.vertexId;
			} else {
				rc = GLMDB_END_OF_EDGES;
				goto fail;
			}
			*labelIdResultC = vertexDbId.labelId;
			*edgeIdResultC = vertexDbId.edgeId;
			foundEdge = 1;
		}
	} else {
		rc = GLMDB_END_OF_EDGES;
		goto fail;
	}

	if (foundEdge == 0) {
		rc = getNextEdgefromVertexAllLabels(cursor, direction, fromVertexId, labelIdResultC, edgeIdResultC, outVertexIdC, inVertexIdC);
	}

	fail: return rc;
}

/**
 * labelIdResultC, edgeIdResultC, outVertexIdC, inVertexIdC are in out parameters.
 * in is the previous values, out is the next values
 */
int getNextEdgefromVertexAllLabels(MDB_cursor *cursor, jint direction, jlong fromVertexId, jint *labelIdResultC, jlong *edgeIdResultC,
		jlong *outVertexIdC, jlong *inVertexIdC) {

//	printf("getNextEdgefromVertexAllLabels start \n");
	int rc = 0;
	VertexDbId id;
	initVertexDbId(&id);
	MDB_val key, data;
	jint tmpLabelIdResultC = -1;
	jlong tmpEdgeIdResultC = -1LL;
	jlong tmpOutVertexIdC = -1LL;
	jlong tmpInVertexIdC = -1LL;

	rc = mdb_cursor_get((MDB_cursor *) (long) cursor, &key, &data, MDB_GET_CURRENT);
	if (rc == 0) {
//		printVertexRecord(key, data);
		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (fromVertexId == vertexDbId.vertexId) {
			if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
				tmpOutVertexIdC = vertexDbId.vertexId;
				tmpInVertexIdC = *((jlong *) (data.mv_data));
			} else if (vertexDbId.coreOrPropertyEnum == INLABEL) {
				tmpOutVertexIdC = *((jlong *) (data.mv_data));
				tmpInVertexIdC = vertexDbId.vertexId;
			} else {
				//The vertex id is the same so this should not be possible
//				printf("whooo haaaa core is %i\n", vertexDbId.coreOrPropertyEnum);
//				rc = GLMDB_DB_CORRUPT;
//				goto fail;
			}
			tmpLabelIdResultC = vertexDbId.labelId;
			tmpEdgeIdResultC = vertexDbId.edgeId;
		} else {
			rc = GLMDB_END_OF_EDGES;
			goto fail;
		}

//		printf("tmpLabelIdResultC = %i, tmpEdgeIdResultC = %llu, tmpOutVertexIdC = %llu, tmpInVertexIdC = %llu\n", tmpLabelIdResultC,
//				(long long) tmpEdgeIdResultC, (long long) tmpOutVertexIdC, (long long) tmpInVertexIdC);
//		printf("labelIdResultC = %i, edgeIdResultC = %llu, outVertexIdC = %llu, inVertexIdC = %llu\n", *labelIdResultC,
//				(long long) *edgeIdResultC, (long long) *outVertexIdC, (long long) *inVertexIdC);

		unsigned char callNext = 1;
		if (tmpLabelIdResultC == *labelIdResultC && tmpEdgeIdResultC == *edgeIdResultC && tmpOutVertexIdC == *outVertexIdC
				&& tmpInVertexIdC == *inVertexIdC) {

//			printf("its the same call MDB_NEXT\n");
			callNext = 0;
		} else {

//			printf("not the same\n");

			//Check if it is the right direction. If so take it and return, else continue and call MDB_NEXT

			if ((direction == 0 && vertexDbId.coreOrPropertyEnum == OUTLABEL)
					|| (direction == 1 && vertexDbId.coreOrPropertyEnum == INLABEL)
					|| (direction == 2 && (vertexDbId.coreOrPropertyEnum == OUTLABEL || vertexDbId.coreOrPropertyEnum == INLABEL))) {

//				printf("not the same nut just different direction call MDB_NEXT\n");
				*outVertexIdC = tmpOutVertexIdC;
				*inVertexIdC = tmpInVertexIdC;
				*labelIdResultC = tmpLabelIdResultC;
				*edgeIdResultC = tmpEdgeIdResultC;

//				printf("not callNext \n");

			} else {
//				printf("callNext \n");
				callNext = 0;
			}
		}
		if (callNext == 0) {

//			printf("callNext before while\n");

			while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {

//				printVertexRecord(key, data);

				vertexDbId = *((VertexDbId *) (key.mv_data));
				if (fromVertexId == vertexDbId.vertexId) {

//					printf("fromVertexId == vertexDbId.vertexId\n");

					if (direction == 0) {
//						printf("direction == 0\n");
						if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
							*outVertexIdC = vertexDbId.vertexId;
							*inVertexIdC = *((jlong *) (data.mv_data));
							*labelIdResultC = vertexDbId.labelId;
							*edgeIdResultC = vertexDbId.edgeId;
							break;
						}
					} else if (direction == 1) {
//						printf("direction == 1\n");
						if (vertexDbId.coreOrPropertyEnum == INLABEL) {
							*outVertexIdC = *((jlong *) (data.mv_data));
							*inVertexIdC = vertexDbId.vertexId;
							*labelIdResultC = vertexDbId.labelId;
							*edgeIdResultC = vertexDbId.edgeId;
							break;
						}
					} else {
//						printf("halo direction both\n");
						if (vertexDbId.coreOrPropertyEnum == OUTLABEL) {
							*outVertexIdC = vertexDbId.vertexId;
							*inVertexIdC = *((jlong *) (data.mv_data));
							*labelIdResultC = vertexDbId.labelId;
							*edgeIdResultC = vertexDbId.edgeId;
							break;
						} else if (vertexDbId.coreOrPropertyEnum == INLABEL) {
							*outVertexIdC = *((jlong *) (data.mv_data));
							*inVertexIdC = vertexDbId.vertexId;
							*labelIdResultC = vertexDbId.labelId;
							*edgeIdResultC = vertexDbId.edgeId;
							break;
						}
					}
				} else {
					rc = GLMDB_END_OF_EDGES;
					goto fail;
				}
			}
		}

	} else {
	}

	fail:
//	printf("getNextEdgefromVertexAllLabels result %i\n", rc);
	return rc;
}
