#include<stdio.h>
int main(){
float t;
float a=1;
float r=0;
float s;
scanf("%f",&t);
for(float i=1;i<=t;i++){
    s=a/i;
    a=a+2;
    r=r+s;
}
printf("%.2f",r);
}
