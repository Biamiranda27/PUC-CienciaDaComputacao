

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void metodo0611(int valor){
    int valor2 = valor*4;
    if(valor2==4){
        printf("%d ", valor2);
    }else{
        metodo0611(valor-1);
        printf("%d ",valor2);
    }
}


void metodo0612(int valor){
    int valor2=valor*4;
    if(valor2==4){
        printf("%d ", valor2);
    }else{
        printf("%d ",valor2);
        metodo0612(valor-1);
    }
}


void metodo0613(int valor){
    int num1=1;
    int valor2=(valor-1)*4;
    if(valor==1){
        printf("%d/%d ", num1,num1);
    }else{
        metodo0613(valor-1);
        printf("%d/%d ",num1,valor2);
    }
}


void metodo0614(int valor){
    int num1=1;
    int valor2=(valor-1)*4;
    if(valor==1){
        printf("%d/%d ",num1,num1);
    }else{
        printf("%d/%d ",num1,valor2);
        metodo0614(valor-1);
    }
}


void metodo0615(int valor,int a,int y){
    if(valor==1){
        printf("%d ",a);
        }else{
             printf("%d ",a);
        metodo0615(valor-1,a+y,y+2);
        }
}//5,4,2


void metodo0616(int valor,int a,int y){
    int num=1;
    if(valor==1){
        printf("%d/%d ",num,a);
    }else{
        printf("%d/%d ",num,a);
        metodo0616(valor-1,a+y,y+2);
    }
}


void metodo0617(char *palavra,int tamanho){
    if(palavra[tamanho]== '\0'){
        printf("\n");
    }else{
    printf("%c\n",palavra[tamanho]);
    metodo0617(palavra,tamanho+1);
    }
}


void metodo0618(char *palavra,int tamanho){
  if(tamanho==0){
    printf("\n");
  }if(palavra[tamanho]%2!=0){
    printf("%c",palavra[tamanho]);
  }else{
    metodo0618(palavra,tamanho-1);
  }
}


void metodo0619(char *palavra,int tamanho){
  if(tamanho==0){
    return;
  }metodo0619(palavra,tamanho-1);
  if(palavra[tamanho-1]>'M' && palavra[tamanho-1]<='Z'){
    printf("%c ",palavra[tamanho-1]);
  }
}


int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
int metodo0620(int quantidade, int n, int count) {
    int fib = fibonacci(n); if (fib % 2 == 0) {  
        count++;  
        if (count == quantidade) { 
            return fib; 
        }
    }
    return metodo0620(quantidade, n + 1, count);  
}


double metodo06E1(int x, int n) {
    if (n == 0) {
        return 1;  
    }
    return pow(x, 2 * n) + metodo06E1(x, n - 1);  
}


unsigned long long fatorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * fatorial(n - 1);
}
double metodo06E2(int n, int termo_atual) {
    if (termo_atual == 0) {
        return 1.0;  
    }
    int numerador = (1 << termo_atual) - 1;  
    unsigned long long denominador = fatorial(2 * termo_atual + 1);\
    return (double)numerador / denominador + metodo06E2(n, termo_atual - 1);
}


int main(){
    int opcao,num;
    do{
        printf("\nDigite um numero de 1-12: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1: metodo0611(5);break;
            /*
            4 8 12 16 20
             */
            case 2: metodo0612(5);break;
            /*
            20 16 12 8 4
             */
            case 3: metodo0613(5);break;
            /*
            1/1 1/4 1/8 1/12 1/16
             */
            case 4: metodo0614(5);break;
            /*
            1/16 1/12 1/8 1/4 1/1
             */
            case 5: metodo0615(5,4,2);break;
            /*
            4 6 10 16 24 
             */
            case 6: metodo0616(5,4,2);break;
            /*
            1/4 1/6 1/10 1/16 1/24 
             */
            case 7:metodo0617("abcde",0);break;
            /*
            a
            b
            c
            d
            e
             */
           case 8:metodo0618("P4LaVr@1",8);break;
            /*
            1
             */
            case 9:metodo0619("P4LaVr@1",8);break;
            /*
            P V
             */
        
            case 10:printf("%d",metodo0620(5,0,0));break;
            /*
            144 
            */
            case 11:printf("%.2f\n",metodo06E1(2,4));break;
            /*
            341.00
            */
            case 12:printf("%.15f\n",metodo06E2(4,3));break;
            /*
            1.193055555555556
            */
        }
    }while(opcao!=0);
}










