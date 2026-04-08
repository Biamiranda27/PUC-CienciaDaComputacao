#include <stdio.h>
#include <float.h>

int main() {
    int N;

    // Fase de preenchimento do vetor
    scanf("%d", &N);

    float notas[N];

    for (int i = 0; i < N; i++) {
        scanf("%f", &notas[i]);
    }

    // Fase de processamento do vetor
    float maiorNota = -FLT_MAX;
    float menorNota = FLT_MAX;
    float somaNotas = 0.0;

    for (int i = 0; i < N; i++) {
        if (notas[i] > maiorNota) {
            maiorNota = notas[i];
        }
        if (notas[i] < menorNota) {
            menorNota = notas[i];
        }
        somaNotas += notas[i];
    }

    float mediaNotas = somaNotas / N;

    // Impressão da maior nota, menor nota e média das notas
    printf(" %.1f\t", maiorNota);
    printf("%.1f\t", menorNota);
    printf("%.1f\t", mediaNotas);

    return 0;
}
