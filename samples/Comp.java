public class Comp {
    public static void main(String []args) {
	int u = 1;
	int x = 1;
	int y = 2;
	int z = 3;

	// True
	if (x < y) {
	    System.out.println("1 is less than 2");
	}

	// True
	if (z > x) {
	    System.out.println("3 is greater than 1");
	}

	// True
	if (y <= z) {
	    System.out.println("2 is less than or equal to 3");
	}

	// True
	if (x != y) {
	    System.out.println("1 is not equal to 2");
	}

	// True
	if (u == x) {
	    System.out.println("1 is equal to 1");
	}

	// True
	if (u >= x) {
	    System.out.println("1 is greater than or equal to 1");
	}

	// True
	if (u <= x) {
	    System.out.println("1 is less than or equal to 1");
	}

	// False
	if (u != x) {
	    System.out.println("1 is not equal to 1");
	}

	// False
	if (x >= y) {
	    System.out.println("1 is greater than or equal to 2");
	}
    }
}
