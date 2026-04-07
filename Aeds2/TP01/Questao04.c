/*
Crie um metodo iterativo que recebe uma string como parametro e retorna a string invertida. Na saıda padrao, para cada linha de entrada, escreva uma linha de
saıda com a string invertida. Por exemplo, se a entrada for “abcde”, a saıda deve ser “edcba”.
*/

#include <stdio.h>
#include <string.h>

void reverso(char string[], int n){
   for(int i = n-1; i >=0; i--){
    printf("%c", string[i]);
   }
   printf("\n");
}
int main(){
    char string[500];
    //printf("digite a string: ");
    while(1){
    scanf("%s", string);
    if (strcmp(string, "FIM") == 0) {
            break;
        }
    int n = strlen(string);
    reverso(string, n);

    } 
}


