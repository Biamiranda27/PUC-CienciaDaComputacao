#include<stdio.h>
int main(){
int m;
int a;
int b;
int c;
scanf("%d",&m);
scanf("%d",&a);
scanf("%d", &b);
scanf("%d",&c);
c=m-(a+b);
if(c>a && c>b){
    printf("%d",c);
} else if(a>c && a>b){
printf("%d",a);
} else if(b>a && b>c){
printf("%d",b);
}
}
