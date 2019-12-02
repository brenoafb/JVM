public class FloatArray {
    public static void main(String []args) {
	float[] arr = new float[5];

	System.out.println("Loading array:");
	int i;
	for (i = 0; i < 5; i++) {
		arr[i] = (float) i;
	}

	System.out.println("Printing array:");
	for (i = 0; i < 5; i++) {
		System.out.println(arr[i]);
	}
    }
}
