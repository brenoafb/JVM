public class DoubleCasts {
	public static void main(String args[]) {
		double d = 3.14159;
		float f = (float) d;
		int i = (int) d;
		long l = (long) d;

		System.out.println("double:");
		System.out.println(d);
		System.out.println("float:");
		System.out.println(f);
		System.out.println("int:");
		System.out.println(i);

	}
}
