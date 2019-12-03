public class FloatFunctions {

    public static float getPi() {
	return 3.14159f;
    }

    public static float passParam(float x) {
	return x;
    }

    public static float addFloats(float x, float y) {
	return x + y;
    }

    public static float addFloatInt(float x, int y) {
	return x + (float) y;
    }

    public static void main(String[] args) {
	float pi = getPi();
	System.out.print("pi=");
	System.out.println(pi);

	pi = passParam(pi);
	System.out.print("pi=");
	System.out.println(pi);

	float e = 2.71828f;
	float sum = addFloats(e, pi);
	System.out.print("e + pi = ");
	System.out.println(sum);

	sum = addFloatInt(e, 1);
	System.out.print("e + 1 = ");
	System.out.println(sum);
    }
}
