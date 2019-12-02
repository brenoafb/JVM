public class IntArray {
    public static void main(String []args) {
	int[] arr = new int[5];

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
