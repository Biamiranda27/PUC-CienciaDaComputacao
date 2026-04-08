#include<stdio.h>
int nd(int n){
int d=1;
while (n%2==0){
    n/=2;
    d++;
}
for(int i=3;i*i<=n;i+=2){
    int c=0;
    while(n%i==0){
        n/=i;
        c++;
    }
    d*=(c+1);
}
if(n>2){
    d*=2;
}
return d;
}
int main(){
int n;

scanf("%d",&n);
int d=nd(n);
printf(" %d\n", d);
return 0;
}
