public class LongCasts {
	public static void main(String args[]) {
		long l = 314159;
		double d = (double) l;
		float f = (float) l;
		int i = (int) l;

		System.out.println("long:");
		System.out.println(l);
		System.out.println("double:");
		System.out.println(d);
		System.out.println("float:");
		System.out.println(f);
		System.out.println("int:");
		System.out.println(i);

	}
}
