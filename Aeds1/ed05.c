#include<stdio.h>
#include<string.h>
#include<math.h>


int funcao0511(int teste){
    int final1;
    for(int i=1;i<=teste;i++){
         final1 = i*4;
     printf("%d\n",final1);
    } 
}
void metodo0511(){
    int numero, resultado=0;
   printf("Digite um numero inteiro: ");
   scanf("%d", &numero);
   resultado = funcao0511(numero);
   printf("%d", resultado);
}


int funcao0512(int teste){
    int final1;
    for(int i=1;i<=teste;i++){
        final1 = i*3*4;
        printf("%d\n", final1);
    }
}
void metodo0512(){
    int numero, resultado=0;
    printf("Digite um numero inteiro: ");
    scanf("%d", &numero);
    resultado = funcao0512(numero);
    printf("%d", resultado);
}


int funcao0513(int teste){
    int final1;
    for(int i=teste;i>=1;i--){
        final1 = pow(3,i);
        printf("%d\n", final1);
    }
}
void metodo0513(){
    int numero, resultado;
    printf("Digite um numero: ");
    scanf("%d", &numero);
    resultado = funcao0513(numero);
    printf("%d", resultado);
}


int funcao0514(int teste){
    int final1;
    for(int i=1;i<=teste;i++){
        final1 = 4*i;
        printf("1/%d\n", final1);
    }
}
void metodo0514(){
    int numero, resultado;
    printf("Digite um numero: ");
    scanf("%d", &numero);
    resultado = funcao0514(numero);
    printf("%d", resultado);
}


int funcao0515(double Teste, int teste){
    int final1, num=1;
    for(int i=1; i<=teste;i++){
        final1 = pow(Teste,num);
        num = num+2;
        printf("1/%d\n", final1);
    }

}
void metodo0515(){
    double valor;
    int numero, resultado;
     printf("Digite um numero inteiro: ");
    scanf("%d", &numero);
    printf("Digite um numero real: ");
    scanf("%lf", &valor);
    resultado = funcao0515(valor, numero);
    printf("%d", resultado);
}


int funcao0516(int teste) {
    int soma = 0;
    int valor = 4;
    int contador = 0;
    while (contador < teste) {
        if (valor % 4 == 0 && valor % 5 != 0) {
            printf("%d ", valor);
            soma += valor;
            contador++;
        }
        valor++;
    }
    return soma;
}
void metodo0516() {
    int quantidade, resultado;
    printf("Digite a quantidade de valores: ");
    scanf("%d", &quantidade);
    resultado = funcao0516(quantidade);
    printf(" %d\n", resultado);
}


double funcao0517(int teste) {
    double soma = 0.0; 
    int valor = 3;    
    int contador = 0;
    while (contador < teste) {
        if (valor % 3 == 0 && valor % 5 != 0) {
            printf("1/%d ", valor); 
            soma += 1.0 / valor;    
            contador++;             
        }
        valor++; 
    }

    return soma; 
}

void metodo0517() {
    int quantidade;
    double resultado;
    printf("Digite a quantidade de valores: ");
    scanf("%d", &quantidade);
    resultado = funcao0517(quantidade);
    printf("\n%.6f\n", resultado);
}



int funcao0518(int teste){
    int final1, final2=0;
    for(int i=0;i<teste;i++){
        final1 = 4+i;
        final2 = final2+final1;
        printf(" %d + ", final1);
    }
    printf(" = %d\n", final2);
}
void metodo0518(){
    int numero, resultado;
    printf("Digite um numero: ");
    scanf("%d", &numero);
    resultado = funcao0518(numero);
    printf("%d", resultado);
}


int funcao0519(int teste){
    int finale, final2, final3=0;
    for(int i=0;i<teste;i++){
        finale = i+4;
        final2 = pow(finale,2);
        final3 = final3+final2;
        printf(" %d + ", final2);
    }
    printf(" = %d\n", final3);
}
void metodo0519(){
    int numero, resultado;
    printf("Digite um numero: ");
    scanf("%d", &numero);
    resultado = funcao0519(numero);
    printf("%d", resultado);
}


int funcao0520(int teste){
    int finale=0,numerador=1, final3=0 ; 
    numerador=numerador*teste;
     for(int i=teste;i>=1;i--){
        finale = finale+(4*i);
        printf(" 1/%d + ", finale);
         final3=final3+finale;
     }
    printf(" = %d/%d\n", numerador,final3);
    }

    void metodo0520() {
        int numero;
        double resultado;
        printf("Digite um numero: ");
        scanf("%d", &numero);
        resultado = funcao0520(numero);
        printf("%lf", resultado);
    }



int funcao05E1(int teste) {
    int resultado = 1;
    if (teste > 0) {
        for (int i = 1; i <= teste; i++) {
            resultado *= i; 
        }
    }

    return resultado;  
}
void metodo05E1() {
    int numero, resultado;
    printf("Digite um número inteiro: ");
    scanf("%d", &numero);
    resultado = funcao05E1(numero);
    printf("%d\n", resultado);
}



double funcao05E2(int teste) {
    double resultado = 1.0; 
    int numerador = 3, denominador = 2;
    for (int i = 1; i <= teste; i++) {
        double fatorial = 1.0;
        for (int j = 1; j <= denominador; j++) {
            fatorial *= j;  
        }
        resultado *= (1.0 + (double) numerador / fatorial); 
        numerador += 2;    
        denominador *= 2;  
    }
    return resultado;  
}
void metodo05E2() {
    int numero;
    double resultado;
    printf("Digite um numero: ");
    scanf("%d", &numero);
    resultado = funcao05E2(numero);
    printf(" %.6f\n", resultado);
}



int main() {
    int numero, teste;
    do{
        printf("\nDigite um numero entre 1-12: ");
        scanf("%d", &numero);
        switch(numero){
            case 1: metodo0511(); break;
            /*
            Digite um numero inteiro: 5
            4
            8
            12
            16
            20
            */
            case 2: metodo0512(); break;
            /*
            Digite um numero inteiro: 5
            12
            24
            36
            48
            60
            */
            case 3: metodo0513(); break;
            /*
            Digite um numero: 5
            243
            81
            27
            9
            3
            */
            case 4: metodo0514(); break;
            /*
            Digite um numero: 5
            1/4
            1/8
            1/12
            1/16
            1/20
            */
            case 5: metodo0515(); break;
            /*
            Digite um numero inteiro: 5
            Digite um numero real: 2
            1/2
            1/8
            1/32
            1/128
            1/512
            */
            case 6: metodo0516(); break;
            /*
            Digite a quantidade de valores: 5
            4 8 12 16 24  64
            */
            case 7: metodo0517(); break;
            /*
            Digite a quantidade de valores: 5
            1/3 1/6 1/9 1/12 1/18 
            0.750000
            */
            case 8: metodo0518(); break;
            /*
            Digite um numero: 5
            4 +  5 +  6 +  7 +  8 +  = 30
            */
            case 9: metodo0519(); break;
            /*
           Digite um numero: 5
           16 +  25 +  36 +  49 +  64 +  = 190
            */
            case 10: metodo0520(); break;
            /*
            Digite um numero: 5
             1/20 +  1/36 +  1/48 +  1/56 +  1/60 +  = 5/220
            */
            case 11: metodo05E1(); break;
            /*
            Digite um número inteiro: 5
            120
            */
            case 12: metodo05E2(); break;
            /*
            Digite um numero: 5
             3.021358
            */
            default: printf("Opção invalida");
        }
    } 
        while(numero!=0);
    return 0;
}



