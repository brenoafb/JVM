public class ShortCast {
    public static void main (String args[]) {
	int xInt = 1;
	short xShort = (short) xInt;
	System.out.println(xInt);
	System.out.println(xShort);

	xInt = -256;
	xShort = (short) xInt;
	System.out.println(xInt);
	System.out.println(xShort);

	xInt = -32678;
	xShort = (short) xInt;
	System.out.println(xInt);
	System.out.println(xShort);

	xInt = 32677;
	xShort = (short) xInt;
	System.out.println(xInt);
	System.out.println(xShort);
    }
}
