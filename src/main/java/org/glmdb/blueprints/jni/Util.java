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

    static byte[] objectToBytes(PropertyTypeEnum propertyTypeEnum, Object object) {
        switch (propertyTypeEnum) {
            case BOOLEAN:
                return toBytes((Boolean)object);
            case BYTE:
                return toBytes((Byte)object);
            case SHORT:
                return toBytes((Short)object);
            case INT:
                return toBytes((Integer)object);
            case LONG:
                return toBytes((Long)object);
            case FLOAT:
                return toBytes((Float)object);
            case DOUBLE:
                return toBytes((Double)object);
            case CHAR:
                return toBytes((Character)object);
            case STRING:
                return toBytes((String)object);
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

    static byte[] toBytes(Short object) {
        return ByteBuffer.allocate(2).putShort(object).array();
    }

    static Long toLong(byte[] value) {
        ByteBuffer wrapped = ByteBuffer.wrap(value);
        wrapped.order(ByteOrder.LITTLE_ENDIAN);
        long num = wrapped.getLong();
        return num;
    }

    static byte[] toBytes(Long object) {
        return ByteBuffer.allocate(8).putLong(object).array();
    }

    static Float toFloat(byte[] value) {
        ByteBuffer wrapped = ByteBuffer.wrap(value);
        wrapped.order(ByteOrder.LITTLE_ENDIAN);
        float num = wrapped.getFloat();
        return num;
    }

    static byte[] toBytes(Float object) {
        return ByteBuffer.allocate(4).putFloat(object).array();
    }

    static Double toDouble(byte[] value) {
        ByteBuffer wrapped = ByteBuffer.wrap(value);
        wrapped.order(ByteOrder.LITTLE_ENDIAN);
        double num = wrapped.getDouble();
        return num;
    }

    static byte[] toBytes(Double object) {
        return ByteBuffer.allocate(8).putDouble(object).array();
    }

    static Character toChar(byte[] value) {
        ByteBuffer wrapped = ByteBuffer.wrap(value);
        wrapped.order(ByteOrder.LITTLE_ENDIAN);
        char num = wrapped.getChar();
        return num;
    }

    static byte[] toBytes(Character object) {
        return ByteBuffer.allocate(2).putChar(object).array();
    }

    static Integer toInt(byte[] value) {
        ByteBuffer wrapped = ByteBuffer.wrap(value);
        wrapped.order(ByteOrder.LITTLE_ENDIAN);
        int num = wrapped.getInt();
        return num;
    }

    static byte[] toBytes(Integer object) {
        return ByteBuffer.allocate(4).putInt(object).array();
    }

    static Boolean toBoolean(byte[] value) {
        return value[0] != (byte) 0x00;
    }

    static byte[] toBytes(Boolean object) {
        return new byte[]{(byte)(object ? 0x01 : 0x00)};
    }

    static byte[] toBytes(Byte object) {
        return ByteBuffer.allocate(1).put(object).array();
    }

    static byte[] toBytes(String object) {
        try {
            return object.getBytes("UTF-8");
        } catch (UnsupportedEncodingException e) {
            throw new RuntimeException(e);
        }
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
