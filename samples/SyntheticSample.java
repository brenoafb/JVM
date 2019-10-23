import java.lang.reflect.Method;

public class SyntheticSample {

	public static void main(String args[]) {

		SampleNestedClass nestObj = new SampleNestedClass();
		System.out.println("Nested Variable: " + nestObj.aPrivateVariable);

		Class c = nestObj.getClass();
		Method[] methods = c.getDeclaredMethods();

		for (Method m : methods) {
			System.out
					.println("m: " + m + " m.isSynthetic: " + m.isSynthetic());
		}

	}

	private static final class SampleNestedClass {
		private String aPrivateVariable = "A Private Variable!";

	}

}