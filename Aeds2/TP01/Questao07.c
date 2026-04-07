/*
Crie um metodo iterativo que recebe uma string como parametro e retorna o comprimento da substring mais longa sem caracteres repetidos. Na saıda padrao, 
para cada linha de entrada, escreva uma linha de saıda com o comprimento da substring mais longa sem repeticao. Por exemplo, se a entrada for “abcabcbb”, a 
saıda deve ser 3 (correspondendo a substring “abc”).
*/

#include <stdio.h>
#include <string.h>

int tamanho(char string[]) {
    int n = strlen(string);
    int max = 0;
    int inicio = 0;
    int ultima[256]; 

    for (int i = 0; i < 256; i++) {
        ultima[i] = -1;
    }
    for (int j = 0; j < n; j++) {
        unsigned char c = string[j]; // para nao ter numeros negativos
        if (ultima[c] >= inicio) {
            inicio = ultima[c] + 1;
        }
        ultima[c] = j;
        int atual = j - inicio + 1;
        if (atual > max) {
            max = atual;
        }
    }
    return max;
}

int main() {
    char string[1000]; 
    while (scanf("%s", string) == 1) {
        if (strcmp(string, "FIM") == 0) {
            break;
        }
        printf("%d\n", tamanho(string));
    }
    return 0;
}


