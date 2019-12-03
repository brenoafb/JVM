public class LongFunctions {

    public static long getSmallLong() {
	return -9223372036854775808l;
    }

    public static void main(String[] args) {
	long smallLong = getSmallLong();
	System.out.println(smallLong);

    }
}
