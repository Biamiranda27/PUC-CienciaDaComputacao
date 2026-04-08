//Crie um programa que leia 10 números inteiros em um vetor e imprima apenas os elementos pares.
#include<stdio.h>
int main(){
    int vetor[10];
    for(int i=0;i<10;i++){
      printf("Digite o vetor[%d]: ",i);
      scanf("%d", &vetor[i]);
    }for(int i=0;i<10;i++){
      if(vetor[i]%2==0){
        printf("%d\t", vetor[i]);
      }
    }
}
