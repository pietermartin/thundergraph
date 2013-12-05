package org.glmdb.blueprints.jni;

/**
 * Date: 2013/11/23
 * Time: 10:46 AM
 */
public enum PropertyTypeEnum {
    BOOLEAN, BYTE, SHORT, INT, LONG, FLOAT,  DOUBLE, CHAR, STRING,
    ARRAY_BOOLEAN, ARRAY_BYTE, ARRAY_SHORT, ARRAY_INT, ARRAY_LONG, ARRAY_FLOAT, ARRAY_DOUBLE, ARRAY_CHAR, ARRAY_STRING;

    public static PropertyTypeEnum fromOrdinal(int ordinal) {

        switch (ordinal) {
            case 0:
                return BOOLEAN;
            case 1:
                return BYTE;
            case 2:
                return SHORT;
            case 3:
                return INT;
            case 4:
                return LONG;
            case 5:
                return FLOAT;
            case 6:
                return DOUBLE;
            case 7:
                return CHAR;
            case 8:
                return STRING;
            case 9:
                return ARRAY_BOOLEAN;
            case 10:
                return ARRAY_BYTE;
            case 11:
                return ARRAY_SHORT;
            case 12:
                return ARRAY_INT;
            case 13:
                return ARRAY_LONG;
            case 14:
                return ARRAY_FLOAT;
            case 15:
                return ARRAY_DOUBLE;
            case 16:
                return ARRAY_CHAR;
            case 17:
                return ARRAY_STRING;
            default:
                throw new IllegalStateException("Unknown PropertyTypeEnum ordinal " + ordinal);

        }

    }
}
