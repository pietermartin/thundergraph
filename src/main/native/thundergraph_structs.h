#include <string.h>
#include <jni.h>
#include "lmdb.h"

/** @defgroup  errors	Return Codes
 *
 *	lmdb uses -30600 to -30800, we'll go under them
 *	@{
 */
/** key/data pair already exists */
#define GLMDB_WRITE_NULL	(-30599)
#define GLMDB_END_OF_EDGES	(-30598)
#define GLMDB_UNDEFINED_DIRECTION	(-30597)
#define GLMDB_DB_CORRUPT	(-30596)
#define GLMDB_DB_INVALID_DIRECTION	(-30595)
#define GLMDB_DB_INVALID_EDGE	(-30594)
#define GLMDB_INVALID_SEQUENCE	(-30593)
#define GLMDB_INVALID_DB	(-30592)
#define GLMDB_PROPERTY_KEY_NOT_FOUND	(-30591)
#define GLMDB_INVALID_STRING	(-30590)

typedef struct GLMDB_env {
	MDB_env *env;
	MDB_dbi configDb;
	MDB_dbi vertexDb;
	MDB_dbi edgeDb;
	MDB_dbi vertexPropertyKeyDb;
	MDB_dbi vertexPropertyKeyInverseDb;

	MDB_dbi vertexBooleanIndexDb;
	MDB_dbi vertexByteIndexDb;
	MDB_dbi vertexShortIndexDb;
	MDB_dbi vertexIntIndexDb;
	MDB_dbi vertexLongIndexDb;
	MDB_dbi vertexFloatIndexDb;
	MDB_dbi vertexDoubleIndexDb;
	MDB_dbi vertexCharIndexDb;
	MDB_dbi vertexStringIndexDb;

	MDB_dbi edgePropertyKeyDb;
	MDB_dbi edgePropertyKeyInverseDb;

	MDB_dbi edgeBooleanIndexDb;
	MDB_dbi edgeByteIndexDb;
	MDB_dbi edgeShortIndexDb;
	MDB_dbi edgeIntIndexDb;
	MDB_dbi edgeLongIndexDb;
	MDB_dbi edgeFloatIndexDb;
	MDB_dbi edgeDoubleIndexDb;
	MDB_dbi edgeCharIndexDb;
	MDB_dbi edgeStringIndexDb;

	MDB_dbi labelDb;

	long long vertexIdSequence;
	long long edgeIdSequence;
	int vertexPropertyKeyIdSequence;
	int edgePropertyKeyIdSequence;
	int labelIdSequence;
	char *path;
} GLMDB_env;

enum DbEnum {
	VERTEX_DB,
	EDGE_DB,
	VERTEX_PROPERTY_DB,
	VERTEX_PROPERTY_INVERSE_DB,
	EDGE_PROPERTY_DB,
	EDGE_PROPERTY_INVERSE_DB,
	LABEL_DB,
	CONFIG_DB,
	VERTEX_BOOLEAN_INDEX,
	VERTEX_BYTE_INDEX,
	VERTEX_SHORT_INDEX,
	VERTEX_INT_INDEX,
	VERTEX_LONG_INDEX,
	VERTEX_FLOAT_INDEX,
	VERTEX_DOUBLE_INDEX,
	VERTEX_CHAR_INDEX,
	VERTEX_STRING_INDEX,
	EDGE_BOOLEAN_INDEX,
	EDGE_BYTE_INDEX,
	EDGE_SHORT_INDEX,
	EDGE_INT_INDEX,
	EDGE_LONG_INDEX,
	EDGE_FLOAT_INDEX,
	EDGE_DOUBLE_INDEX,
	EDGE_CHAR_INDEX,
	EDGE_STRING_INDEX
};

enum SequenceEnum {
	VERTEX_ID_SEQUENCE, EDGE_ID_SEQUENCE, VERTEX_PROPERTY_KEY_ID_SEQUENCE, EDGE_PROPERTY_KEY_ID_SEQUENCE, LABEL_ID_SEQUENCE
};

enum VertexCoreOrPropertyEnum {
	VCORE, VPROPERTY_KEY, OUTLABEL, INLABEL
};

enum EdgeCoreOrPropertyEnum {
	ECORE, EPROPERTY_KEY
};

typedef struct VertexDbId {
	long long vertexId;
	enum VertexCoreOrPropertyEnum coreOrPropertyEnum;
	int propertykeyId;
	int labelId;
	long long edgeId;
} VertexDbId;

typedef struct EdgeDbId {
	jlong edgeId;
	enum EdgeCoreOrPropertyEnum coreOrPropertyEnum;
	jint propertykeyId;
} EdgeDbId;

typedef struct EdgeData {
	jlong vertexInId;
	jlong vertexOutId;
	jint labelId;
} EdgeData;

enum PropertyTypeEnum {
	BOOLEAN,
	BYTE,
	SHORT,
	INT,
	LONG,
	FLOAT,
	DOUBLE,
	CHAR,
	STRING,
	ARRAY_BOOLEAN,
	ARRAY_BYTE,
	ARRAY_SHORT,
	ARRAY_INT,
	ARRAY_LONG,
	ARRAY_FLOAT,
	ARRAY_DOUBLE,
	ARRAY_CHAR,
	ARRAY_STRING,
	UNSET
};

typedef struct PropertyKeyDataStruct {
	jint propertyKeyId;
	enum PropertyTypeEnum type;
	jboolean indexed;
} PropertyKeyDataStruct;

typedef struct PropertyKeyInverseDataStruct {
	enum PropertyTypeEnum type;
	jboolean indexed;
	char propertyKey[0];
} PropertyKeyInverseDataStruct;

typedef struct StringIndexKeyStruct {
	jint propertyKeyId;
	long long elementId;
	char value[0];
} StringIndexKeyStruct;

typedef struct IntIndexKeyStruct {
	jint propertyKeyId;
	long long elementId;
	int value;
} IntIndexKeyStruct;

typedef struct LongIndexKeyStruct {
	jint propertyKeyId;
	long long elementId;
	long long value;
} LongIndexKeyStruct;

typedef struct FloatIndexKeyStruct {
	jint propertyKeyId;
	long long elementId;
	float value;
} FloatIndexKeyStruct;

typedef struct DoubleIndexKeyStruct {
	jint propertyKeyId;
	long long elementId;
	double value;
} DoubleIndexKeyStruct;

typedef struct BooleanIndexKeyStruct {
	jint propertyKeyId;
	long long elementId;
	unsigned char value;
} BooleanIndexKeyStruct;

typedef struct ShortIndexKeyStruct {
	jint propertyKeyId;
	long long elementId;
	short value;
} ShortIndexKeyStruct;

typedef struct CharIndexKeyStruct {
	jint propertyKeyId;
	long long elementId;
	unsigned short value;
} CharIndexKeyStruct;

typedef struct ByteIndexKeyStruct {
	jint propertyKeyId;
	long long elementId;
	signed char value;
} ByteIndexKeyStruct;

