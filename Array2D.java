public class Array2D {
	public static void main(String args[]) {
		int[][] arr = new int[3][3];
		int i, j;

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				arr[i][j] = i+j;
			}
		}

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				System.out.print(arr[i][j]);
				System.out.print(" ");
			}
			System.out.println("");
		}
	}
}
