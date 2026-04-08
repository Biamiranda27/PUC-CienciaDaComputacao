#include<stdio.h>
int main(){
    int n;
    int m=0;
    int p=0;
    scanf("%d",&n);
    int vetor[n];
    for(int i=0;i<n;i++){
        scanf("%d",&vetor[i]);
        if(vetor[i]>=m){
            m=vetor[i];
            p=i;
        }
    }
    printf("%d %d\n", m, p);
    return 0;
}
