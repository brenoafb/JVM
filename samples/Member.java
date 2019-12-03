public class Member {
    static int intStatic;
    static double doubleStatic;
    static long longStatic;
    static float floatStatic;

    static short shortStatic;
    static byte byteStatic;
    static boolean boolStatic;
    static char charStatic;

    public static void main(String[] args) {
	intStatic = 3;
	System.out.println(intStatic);

	doubleStatic = 3.1415;
	System.out.println(doubleStatic);

	longStatic = 12858497253L;
	System.out.println(longStatic);

	floatStatic = 2.78f;
	System.out.println(floatStatic);

	shortStatic = 32767;
	System.out.println(shortStatic);

	byteStatic = (byte) 127;
	System.out.println(byteStatic);

	boolStatic = true;
	System.out.println(boolStatic);

	charStatic = 'c';
	System.out.println(charStatic);
    }
}
