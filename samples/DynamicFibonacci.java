public class DynamicFibonacci {
    public static int memoFib(int n, int[] table) {
	if (table[n] != -1) {
	    return table[n];
	}

	int f = memoFib(n-1, table) + memoFib(n-2, table);
	table[n] = f;
	return f;
    }

    public static void initTable(int n, int[] table) {
	int i;
	for (i = 0; i < n; i++) {
	    table[i] = -1;
	}

	table[0] = 0;
	table[1] = 1;
    }

    public static void main(String []args) {
	int n = 100;
	int[] table = new int[n];
	initTable(n, table);

	System.out.println("memoFib(0)");
	n = 0;
	int x = memoFib(n, table);
	System.out.println(x);

	System.out.println("memoFib(1)");
	n = 1;
	x = memoFib(n, table);
	System.out.println(x);

	System.out.println("memoFib(2)");
	n = 2;
	x = memoFib(n, table);
	System.out.println(x);

	System.out.println("memoFib(3)");
	n = 3;
	x = memoFib(n, table);
	System.out.println(x);

	System.out.println("memoFib(10)");
	n = 10;
	x = memoFib(n, table);
	System.out.println(x);

	System.out.println("memoFib(25)");
	n = 25;
	x = memoFib(n, table);
	System.out.println(x);
    }
}
