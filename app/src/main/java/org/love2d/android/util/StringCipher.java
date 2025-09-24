package org.love2d.android.util;

/**
 * ClassName StringCipher
 * Description
 * Create by hjr
 * Date 2025/6/27 15:19
 */
public class StringCipher {
    // 使用一个简单的密钥。这个密钥本身也可以通过更复杂的方式生成。
    private static final byte KEY = (byte) 0xA9;

    public static String decrypt(byte[] encrypted) {
        byte[] decrypted = new byte[encrypted.length];
        for (int i = 0; i < encrypted.length; i++) {
            decrypted[i] = (byte) (encrypted[i] ^ KEY);
        }
        return new String(decrypted);
    }

    // 您可以用这个方法来生成加密后的字节数组，在开发时使用
    // 例如：printEncrypted("安全警告");
    public static void printEncrypted(String text) {
        byte[] bytes = text.getBytes();
        StringBuilder sb = new StringBuilder("new byte[] {");
        for (int i = 0; i < bytes.length; i++) {
            sb.append("(byte)(").append(bytes[i] ^ KEY).append(")");
            if (i < bytes.length - 1) {
                sb.append(", ");
            }
        }
        sb.append("}");
        System.out.println(sb.toString());
    }
}
