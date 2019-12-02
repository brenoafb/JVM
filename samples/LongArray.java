public class LongArray {
    public static void main(String []args) {
	long[] arr = new long[5];

	System.out.println("Loading array:");
	int i;
	for (i = 0; i < 5; i++) {
		arr[i] = i;
	}

	System.out.println("Printing array:");
	for (i = 0; i < 5; i++) {
		System.out.println(arr[i]);
	}
    }
}
