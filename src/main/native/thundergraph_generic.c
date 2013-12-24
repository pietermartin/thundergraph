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
	rc = mdb_cursor_get(cursor, &vertexKey, &data, MDB_SET);
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

	//First delete all in edges
	while ((rc = mdb_cursor_get((MDB_cursor *) (long) vertexCursor, &key, &data, MDB_SET_RANGE)) == 0) {

		VertexDbId vertexDbId = *((VertexDbId *) (key.mv_data));
		if (vertexId == vertexDbId.vertexId) {
			if (vertexDbId.coreOrPropertyEnum == INLABEL || vertexDbId.coreOrPropertyEnum == OUTLABEL) {

				rc = internalRemoveEdge(edgeCursor, vertexDbId.edgeId);
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
				int propertyKeySize = propertyKeyInverseData.mv_size - sizeof(PropertyKeyInverseDataStruct);
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
						rc = removeStringIndex(stringIndexCursor, vertexId, vertexDbId.propertykeyId, propertyKeySize,
								(char *) data.mv_data);
						mdb_cursor_close(stringIndexCursor);
						break;
					default:
						rc = GLMDB_INVALID_SEQUENCE;
						break;
					}
					if (rc != 0) {
						goto fail;
					}
				}

				//delete current
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

int internalDeleteVertex(MDB_cursor *vertexCursor, MDB_cursor *inverseCursor, MDB_cursor *edgeCursor, VertexDbId vertexDbId,
		VertexDbId inverseId, MDB_val inverseKey, MDB_val data, MDB_val inverseData) {

	int rc;
	rc = internalRemoveEdge(edgeCursor, vertexDbId.edgeId);
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
	rc = mdb_cursor_get(inverseCursor, &inverseKey, &inverseData, MDB_SET);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}
	rc = mdb_cursor_del(inverseCursor, 0);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}

	//delete current
	rc = mdb_cursor_del(vertexCursor, 0);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}
	fail: return rc;

}

int internalRemoveEdge(MDB_cursor *cursor, jlong edgeId) {
	MDB_val edgeKey, edgeData;
	int rc = getEdge(cursor, edgeId, &edgeKey, &edgeData);
	if (rc == 0) {
		rc = mdb_cursor_del(cursor, 0);
	}

	while ((rc = mdb_cursor_get(cursor, &edgeKey, &edgeData, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (edgeKey.mv_data));
		if (edgeDbId.edgeId == edgeId) {
			rc = mdb_cursor_del((MDB_cursor *) (long) cursor, 0);
			if (rc == MDB_NOTFOUND) {
				printf("internalRemoveEdge  MDB_NOTFOUND %i\n", rc);
				//This happens at the end of the keys when it iterates forever on the last record.
				//When we delete what is already deleted it returns MDB_NOTFOUND
				break;
			}
			if (rc != 0) {
				printf("internalRemoveEdge %i\n", rc);
				rc = GLMDB_DB_CORRUPT;
				goto fail;
			}
		} else {
			break;
		}
	}
	if (rc == MDB_NOTFOUND) {
		rc = 0;
	}
	fail: return rc;
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
	rc = mdb_cursor_del((MDB_cursor *) (long) edgeCursor, 0);
	if (rc != 0) {
		rc = GLMDB_DB_CORRUPT;
		goto fail;
	}

	while ((rc = mdb_cursor_get((MDB_cursor *) (long) edgeCursor, &edgeKey, &data, MDB_NEXT)) == 0) {
		EdgeDbId edgeDbId = *((EdgeDbId *) (edgeKey.mv_data));
		if (edgeDbId.edgeId == edgeId) {
			rc = mdb_cursor_del((MDB_cursor *) (long) edgeCursor, 0);
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
