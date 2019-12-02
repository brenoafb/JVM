public class ByteArray {
    public static void main(String []args) {
	byte[] arr = new byte[5];

	System.out.println("Loading array:");
	int i;
	for (i = 0; i < 5; i++) {
		arr[i] = (byte) i;
	}

	System.out.println("Printing array:");
	for (i = 0; i < 5; i++) {
		System.out.println(arr[i]);
	}
    }
}
