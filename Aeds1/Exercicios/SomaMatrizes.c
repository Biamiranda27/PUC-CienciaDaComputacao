//Crie uma função chamada soma_matrizes que receba duas matrizes e suas dimensões, e retorne a soma delas.
// A função deve armazenar o resultado em uma matriz de saída.

#include <stdio.h>

void soma_matrizes(int linhas, int colunas, int A[linhas][colunas], int B[linhas][colunas], int C[linhas][colunas]) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}
int main() {
    int A[2][2] = {{1, 2}, {3, 4}};
    int B[2][2] = {{5, 6}, {7, 8}};
    int C[2][2];
    soma_matrizes(2, 2, A, B, C);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}
