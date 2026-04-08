#include<stdio.h>
#include<stdlib.h>
int main(){
int num;
int i;
int f;
scanf("%d",&num);
f=0;
i=2;
while(i<=num/2){
    if(num%i==0){
        f=1;
        break;}
i++;}
if (f==0){
    printf("Numero primo");
} else{
printf("Nao primo");
}
return 0;
}
