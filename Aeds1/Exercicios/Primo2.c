#include<stdio.h>
int p(int n){
if(n<=1){
    return 0;
}
for (int i =2;i*i<=n;i++){
    if(n%i==0){
        return 0;
    }
}
return 1;
}
int main(){
int ma;
int me;
scanf("%d",&me);
scanf("%d",&ma);
if(ma<=me){
    return 1;
}

for(int i=me;i<=ma;i++){
    if (p(i)){
        printf("%d\t",i);
    }
}
printf("\t");
return 0;
}
