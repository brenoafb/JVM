public class LongFibonacci {
    public static long fib(long n) {
	if (n <= 1) {
	    return n;
	}

	return fib(n-1) + fib(n-2);
    }

    public static void main(String []args) {
	System.out.println("Fib(0)");
	long n = 0;
	long x = fib(n);
	System.out.println(x);

	System.out.println("Fib(1)");
	n = 1;
	x = fib(n);
	System.out.println(x);

	System.out.println("Fib(2)");
	n = 2;
	x = fib(n);
	System.out.println(x);

	System.out.println("Fib(3)");
	n = 3;
	x = fib(n);
	System.out.println(x);

	System.out.println("Fib(10)");
	n = 10;
	x = fib(n);
	System.out.println(x);

	System.out.println("Fib(25)");
	n = 25;
	x = fib(n);
	System.out.println(x);
    }
}
