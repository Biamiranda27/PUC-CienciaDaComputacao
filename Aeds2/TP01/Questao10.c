/*
Crie um metodo recursivo que recebe uma string e retorna true se a mesma e composta somente por vogais. Crie outro metodo recursivo que recebe uma string e 
retorna true se a mesma e composta somente por consoantes. Crie um terceiro metodo recursivo que recebe uma string e retorna true se a mesma corresponde a um 
numero inteiro. Crie um quarto metodo recursivo que recebe uma string e retorna true se a mesma corresponde a um numero real. Na saıda padrao, para cada linha 
de entrada, escreva outra de saıda da seguinte forma X1 X2 X3 X4 onde cada Xi e um booleano indicando se a e entrada e: composta somente por vogais (X1);
4. 5. 6. 7. 8. 9. 10. 11. 12. composta somente somente por consoantes (X2); um n´umero inteiro (X3); um n´umero real (X4). Se Xi for verdadeiro, seu valor ser a 
SIM, caso contrario, NAO.
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


bool vogalR(char* frase, int i) {
    if (frase[i] == '\0') return true;
    char c = (char)tolower(frase[i]);
    if (!(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')) {
        return false;
    }
    return vogalR(frase, i + 1);
}

bool consoanteR(char* frase, int i) {
    if (frase[i] == '\0') return true;
    char c = (char)tolower(frase[i]);
    bool e_letra = (c >= 'a' && c <= 'z');
    bool e_v = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
    
    if (!e_letra || e_v) return false;
    return consoanteR(frase, i + 1);
}

bool inteiroR(char* frase, int i) {
    if (frase[i] == '\0') return true;
    if (frase[i] < '0' || frase[i] > '9') return false;
    return inteiroR(frase, i + 1);
}

bool realR(char* frase, int i, int count) {
    if (frase[i] == '\0') return true;
    
    if (frase[i] >= '0' && frase[i] <= '9') {
        return realR(frase, i + 1, count);
    } else if (frase[i] == ',' || frase[i] == '.') {
        if (count >= 1) return false;
        return realR(frase, i + 1, count + 1);
    }
    return false; 
}


bool vogal(char* frase) {
    if (strlen(frase) == 0) return false;
    return vogalR(frase, 0);
}

bool consoante(char* frase) {
    if (strlen(frase) == 0) return false;
    return consoanteR(frase, 0);
}

bool inteiro(char* frase) {
    if (strlen(frase) == 0) return false;
    return inteiroR(frase, 0);
}

bool real(char* frase) {
    if (strlen(frase) == 0) return false;
    return realR(frase, 0, 0);
}


int main() {
    char palavra[500];

    //printf("digite uma palavra: ");
    while (fgets(palavra, sizeof(palavra), stdin)) {
        palavra[strcspn(palavra, "\n")] = '\0';

        if (strcmp(palavra, "FIM") == 0) {
            break;
        }

        printf("%s ", vogal(palavra) ? "SIM" : "NAO");
        printf("%s ", consoante(palavra) ? "SIM" : "NAO");
        printf("%s ", inteiro(palavra) ? "SIM" : "NAO");
        printf("%s\n", real(palavra) ? "SIM" : "NAO");
    }

    return 0;
}
