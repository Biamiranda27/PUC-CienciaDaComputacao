#include<stdio.h>
#include<stdlib.h>
int main(){
int n;
int tn=0;
int q5=0;
do{
    scanf("%d",&n);
    if(n!=-1){
        tn++;
        if(n==5){
            q5++;
        }
    }
}while(n!=-1);
printf(" %d %d", tn, q5);
}
