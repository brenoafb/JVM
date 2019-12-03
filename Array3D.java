public class Array3D {
	public static void main(String args[]) {
		int[][][] arr_int = new int[3][3][3];
		float[][][] arr_float = new float[3][3][3];
		int i, j, k;

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				for (k = 0; k < 3; k++) {
					arr_int[i][j][k] = i+j+k;
				}

			}
		}

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				for (k = 0; k < 3; k++) {
					System.out.print(arr_int[i][j][k]);
					System.out.print(" ");
				}
				System.out.println("");
			}
			System.out.println("");
		}

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				for (k = 0; k < 3; k++) {
					arr_float[i][j][k] = (float) i+j+k;
				}

			}
		}

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				for (k = 0; k < 3; k++) {
					System.out.print(arr_float[i][j][k]);
					System.out.print(" ");
				}
				System.out.println("");
			}
			System.out.println("");
		}

	}
}
