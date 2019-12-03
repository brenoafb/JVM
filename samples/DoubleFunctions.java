public class DoubleFunctions {

    public static double getPi() {
	return 3.14159265358979323846;
    }

    public static double passParam(double x) {
	return x;
    }

    public static void main(String[] args) {
	double pi = getPi();
	System.out.print("pi=");
	System.out.println(pi);

	pi = passParam(pi);
	System.out.print("pi=");
	System.out.println(pi);
    }
}
