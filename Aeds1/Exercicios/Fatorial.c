#include<stdio.h>
int main(){
int n;
int m=1;
scanf("%d",&n);
for(int i=1;i<n;i++){
    m=m*(i+1);
}
printf("%d",m);
}
