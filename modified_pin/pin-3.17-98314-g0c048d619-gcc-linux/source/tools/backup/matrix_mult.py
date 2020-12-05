def matrixmult (A, B):
    rows_A = len(A)
    cols_A = len(A[0])
    rows_B = len(B)
    cols_B = len(B[0])

    C = [[0 for row in range(cols_B)] for col in range(rows_A)]

    for i in range(rows_A):
        for j in range(cols_B):
            for k in range(cols_A):
                C[i][j] += A[i][k] * B[k][j]
    return C

if __name__=='__main__':
    x = [[1,2,3],[4,5,6],[7,8,9],[10,11,12]]
    y = [[1,2],[1,2],[3,4]]
    matrixmult(x,y)
