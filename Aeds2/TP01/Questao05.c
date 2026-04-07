/*
Crie um metodo recursivo que recebe um numero inteiro como parametro e retorna a soma de seus dıgitos. Na saıda padrao, para cada linha de entrada,
escreva uma linha de saıda com o resultado da soma dos dıgitos. Por exemplo, se a entrada for 12345, a saıda deve ser 15.
*/

#include <stdio.h>
#include<string.h>
#include <stdlib.h>

int soma(int n){
    if(n == 0){
        return 0;
    } 
    return (n % 10) + soma(n / 10);
}
int main(){
    char string[50];
    int numero;
    //printf("digite um numero: ");
    while(1){
    scanf("%s", string);
    if(strcmp(string, "FIM") == 0){
        break;
    }
    numero = atoi(string); // converte string para numero
    printf("%d\n", soma(numero));
    }
}
