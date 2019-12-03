public class DynamicFibonacci {
    public static int dynamicFib(int n) {
	if (n <= 1) return n;

	int[] table = new int[n+1];
	table[0] = 0;
	table[1] = 1;

	int i;
	for (i = 2; i <= n; i++) {
	    table[i] = table[i-1] + table[i-2];
	}

	return table[n];
    }

    public static void main(String []args) {
	System.out.println("dynamicFib(0)");
	int n = 0;
	int x = dynamicFib(n);
	System.out.println(x);

	System.out.println("dynamicFib(1)");
	n = 1;
	x = dynamicFib(n);
	System.out.println(x);

	System.out.println("dynamicFib(2)");
	n = 2;
	x = dynamicFib(n);
	System.out.println(x);

	System.out.println("dynamicFib(3)");
	n = 3;
	x = dynamicFib(n);
	System.out.println(x);

	System.out.println("dynamicFib(10)");
	n = 10;
	x = dynamicFib(n);
	System.out.println(x);

	System.out.println("dynamicFib(25)");
	n = 25;
	x = dynamicFib(n);
	System.out.println(x);
    }
}
