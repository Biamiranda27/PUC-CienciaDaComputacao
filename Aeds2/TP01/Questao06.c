/*
Crie um metodo iterativo que recebe duas strings como parametros e retorna true se as strings sao anagramas uma da outra, ou false caso contrario. Na saıda 
padrao, para cada par de strings de entrada, escreva uma linha de saıda com SIM/NAO indicando se as strings sao anagramas. Por exemplo, se as entradas forem 
“listen” e “silent”, a saıda deve ser SIM.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void verificar_anagrama(char string1[], char string2[]) {
    int freq[256] = {0};
    int n1 = strlen(string1);
    int n2 = strlen(string2);

    if (n1 != n2) {
        printf("NÃO\n");
        return;
    }

    for (int i = 0; i < n1; i++) {
        freq[(unsigned char)tolower(string1[i])]++;
        freq[(unsigned char)tolower(string2[i])]--;
    }

    for (int i = 0; i < 256; i++) {
        if (freq[i] != 0) {
            printf("NÃO\n");
            return;
        }
    }
    printf("SIM\n");
}

int main() {
    char string1[100], string2[100], separador[10];

    //printf("digite as strings: ");
    while (scanf("%s %s %s", string1, separador, string2) == 3) {
        if (strcmp(string1, "FIM") == 0) break;
        
        verificar_anagrama(string1, string2);
    }

    return 0;
}

