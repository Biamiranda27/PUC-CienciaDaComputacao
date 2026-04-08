#include<stdio.h>
int main(){
int n;
int d;
scanf("%d", &n);
while(n>0){
    d=n%10;
    printf("%d",d);
    n/=10;
}
printf("\n");
return 0;
}
