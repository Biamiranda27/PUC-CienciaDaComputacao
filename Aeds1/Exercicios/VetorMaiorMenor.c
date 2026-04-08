//Crie um programa que leia 10 números inteiros em um vetor e encontre o maior e o menor valor entre eles.
#include<stdio.h>
int main(){
  int vetor[10];
  int maior=-1;
  int menor=100000;
  for(int a=0;a<10;a++){
    printf("Digite o vetor[%d]: ",a);
    scanf("%d", &vetor[a]);
  } for(int a=0;a<10;a++){
    if(vetor[a]>maior){
      maior=vetor[a];
    }
  } printf("O maior valor é: %d\n", maior);
  for(int a=0;a<10;a++){
    if(vetor[a]<menor){
      menor=vetor[a];
    }
  } printf("O menor valor é: %d\n", menor);
}
