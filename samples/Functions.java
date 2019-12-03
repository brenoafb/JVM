public class Functions {
    public static void voidVoidFunc() {
	System.out.println("Hello from voidVoid.");
    }

    public static int intIntFunc(int x) {
	System.out.print("intInt received ");
	System.out.print(x);
	System.out.print(". Returning ");
	System.out.println(x+1);
	return x+1;
    }

    public static int intVoidFunc() {
	int n = 1234;
	System.out.print("intVoid returning ");
	System.out.println(n);
	return n;
    }

    public static void main(String[] args) {
	int n = 10;
	voidVoidFunc();
	int ret = intIntFunc(n);
	System.out.print(ret);
	ret = intVoidFunc();
	System.out.println(ret);
    }
}
