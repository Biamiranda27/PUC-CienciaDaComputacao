//Crie uma programa que lê uma string e um caractere, e retorne o número de vezes que esse caractere aparece na string.
#include<stdio.h>
int main(){
  char string[50];
  char caracter;
  int count=0;
  char a;
  printf("Digite uma string: ");
  fgets(string,50,stdin);
  printf("Digite um caracter: ");
  scanf("%c", &caracter);
  getchar();
  for(a=0;a<49;a++){
    if(string[a]==caracter){
      count++;
    }
  }printf("Esse caracter apareceu %d vezes", count);
  return 0;
}
