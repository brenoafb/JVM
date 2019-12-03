public class FloatCasts {
	public static void main(String args[]) {
		float f = 3.14159f;
		double d = (double) f;
		int i = (int) f;
		long l = (long) f;

		System.out.println("float:");
		System.out.println(f);
		System.out.println("double:");
		System.out.println(d);
		System.out.println("int:");
		System.out.println(i);
		System.out.println("long:");
		System.out.println(l);
	}
}
