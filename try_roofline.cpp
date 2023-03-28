void matmul_ijk(double **A, double **B, double **res, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                res[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}