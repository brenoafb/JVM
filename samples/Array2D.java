public class Array2D {
	public static void main(String args[]) {
		int[][] arr_int = new int[3][3];
		float[][] arr_float = new float[3][3];
		double[][] arr_double = new double[3][3];
		long[][] arr_long = new long[3][3];
		int i, j;

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				arr_int[i][j] = i+j;
			}
		}

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				System.out.print(arr_int[i][j]);
				System.out.print(" ");
			}
			System.out.println("");
		}
		System.out.println("");

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				arr_float[i][j] = (float) i+j;
			}
		}

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				System.out.print(arr_float[i][j]);
				System.out.print(" ");
			}
			System.out.println("");
		}
		System.out.println("");

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				arr_double[i][j] = (double) i+j;
			}
		}

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				System.out.print(arr_double[i][j]);
				System.out.print(" ");
			}
			System.out.println("");
		}
		System.out.println("");

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				arr_long[i][j] = i+j;
			}
		}

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				System.out.print(arr_long[i][j]);
				System.out.print(" ");
			}
			System.out.println("");
		}
		System.out.println("");
	}
}
