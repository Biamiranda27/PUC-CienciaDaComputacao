#include<stdio.h>
int main(){
int v=1;
int a=0;
int b=0;
int c=0;
int d=0;
int n=0;
float di;
float cont=0;
float vb=0;
while(v>0){
    scanf("%d", &v);
    switch(v){
case 1:
    a++;
    cont++;
    break;
case 2:
    b++;
    cont++;
    break;
case 3:
    c++;
    cont++;
    break;
case 4:
    d++;
    cont++;
    break;
case 5:
    n++;
    cont++;
    break;
case 6:
    vb++;
    cont++;
    break;
    }
}
di=(100/cont)*vb;
printf("%d %d %d %d\n %d\n %.2f", a, b, c, d, n, di);
}
