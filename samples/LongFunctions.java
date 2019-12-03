public class LongFunctions {

    public static long getSmallLong() {
	return -9223372036854775808l;
    }

    public static long longIdentity(long x) {
	return x;
    }

    public static void twoLongs(long x, long y) {
	System.out.print("x = ");
	System.out.println(x);
	System.out.print("y = ");
	System.out.println(y);
    }

    public static long returnLong(long x, long y) {
	return x;
    }

    public static void main(String[] args) {
	long smallLong = getSmallLong();
	System.out.println(smallLong);

	long bigLong = 922337203685477580l;
	System.out.println(bigLong);
	bigLong = longIdentity(bigLong);
	System.out.println(bigLong);

	twoLongs(smallLong, bigLong);

	long anotherLong = returnLong(smallLong, bigLong);
	System.out.print("anotherLong = ");
	System.out.println(anotherLong);
    }
}
