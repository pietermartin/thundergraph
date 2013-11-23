package org.glmdb.blueprints.jni;

import java.io.UnsupportedEncodingException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import static org.glmdb.blueprints.jni.GlmdbJni.mdb_strerror;

/**
 * Date: 2013/11/19
 * Time: 7:19 PM
 */
public class Util {

    static void checkErrorCode(int rc) {
        if (rc != 0) {
            String msg = mdb_strerror(rc);
            throw new GLMDBException(msg, rc);
        }
    }

    static Object bytesToObject(PropertyTypeEnum propertyTypeEnum, byte[] bytes) {

        switch (propertyTypeEnum) {
            case BOOLEAN:
                return toBoolean(bytes);
            case BYTE:
                return bytes[0];
            case SHORT:
                return toShort(bytes);
            case INT:
                return toInt(bytes);
            case LONG:
                return toLong(bytes);
            case FLOAT:
                return toFloat(bytes);
            case DOUBLE:
                return toDouble(bytes);
            case CHAR:
                return toChar(bytes);
            case STRING:
                return toString(bytes);
            case ARRAY_BOOLEAN:
                break;
            case ARRAY_BYTE:
                break;
            case ARRAY_SHORT:
                break;
            case ARRAY_INT:
                break;
            case ARRAY_LONG:
                break;
            case ARRAY_FLOAT:
                break;
            case ARRAY_DOUBLE:
                break;
            case ARRAY_CHAR:
                break;
            case ARRAY_STRING:
                break;
            default:
                throw new IllegalStateException("Unknown propertyTypeEnum " + propertyTypeEnum.name());
        }
        return null;
    }

    static Short toShort(byte[] value) {
        ByteBuffer wrapped = ByteBuffer.wrap(value);
        wrapped.order(ByteOrder.LITTLE_ENDIAN);
        short num = wrapped.getShort();
        return num;
    }

    static Long toLong(byte[] value) {
        ByteBuffer wrapped = ByteBuffer.wrap(value);
        wrapped.order(ByteOrder.LITTLE_ENDIAN);
        long num = wrapped.getLong();
        return num;
    }

    static Float toFloat(byte[] value) {
        ByteBuffer wrapped = ByteBuffer.wrap(value);
        wrapped.order(ByteOrder.LITTLE_ENDIAN);
        float num = wrapped.getFloat();
        return num;
    }

    static Double toDouble(byte[] value) {
        ByteBuffer wrapped = ByteBuffer.wrap(value);
        wrapped.order(ByteOrder.LITTLE_ENDIAN);
        double num = wrapped.getDouble();
        return num;
    }

    static Character toChar(byte[] value) {
        ByteBuffer wrapped = ByteBuffer.wrap(value);
        wrapped.order(ByteOrder.LITTLE_ENDIAN);
        char num = wrapped.getChar();
        return num;
    }

    static Integer toInt(byte[] value) {
        ByteBuffer wrapped = ByteBuffer.wrap(value);
        wrapped.order(ByteOrder.LITTLE_ENDIAN);
        int num = wrapped.getInt();
        return num;
    }

    static Boolean toBoolean(byte[] value) {
        return value[0] != (byte)0x00;
    }

    static String toString(byte[] value) {
        if (value == null) {
            return null;
        }
        try {
            return new String(value, "UTF-8");
        } catch (UnsupportedEncodingException e) {
            throw new RuntimeException(e);
        }
    }

    public static byte[] bytes(String value) {
        if (value == null) {
            return null;
        }
        try {
            return value.getBytes("UTF-8");
        } catch (UnsupportedEncodingException e) {
            throw new RuntimeException(e);
        }
    }
}
