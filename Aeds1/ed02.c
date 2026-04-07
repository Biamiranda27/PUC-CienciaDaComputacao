

#include <stdio.h>
#include<string.h>

void procedimento0211(int numero){
    getchar();
    printf("Digite um numero inteiro: ");
    scanf("%d", &numero);
    if(numero%2==0){
        printf("O numero digitado é par");
    }
    else{
        printf("O numero digitado é impar");
    }
}


void procedimento0212(int numero){
    getchar();
    printf("Digite um numero inteiro: ");
    scanf("%d", &numero);
    if(numero%2==0 && numero>15){
        printf("O numero digitado é par e maior que 15");
    }
    else if(numero%2!=0 && numero<-15){
        printf("O numero digitado é impar e menor que -15");
    }
    else{
        printf("O numero digitado se encontra no intervalo de -15 e 15 ou é par menor que -15 ou impar maior que 15");
    }
}


void procedimento0213(int numero){
    getchar();
    printf("Digite um numero inteiro: ");
    scanf("%d", &numero);
    if(numero>25 && numero<45){
        printf("O numero digitado esta dentro do intervalo aberto de 25-45");
    }
    else{
        printf("O numero digitado esta fora do intervalo aberto de 25-45");
    }
}



void procedimento0214(int numero){
    getchar();
    printf("Digite um numero inteiro: ");
    scanf("%d", &numero);
    if(numero>=20 && numero<=60){
        printf("O numero digitado esta dentro do intervalo fechado de 20-60");
    }
    else{
        printf("O numero digitado esta fora do intervalo fechado de 20-60");
    }
}


void procedimento0215(int numero){
    getchar();
    printf("Digite um numero inteiro: ");
    scanf("%d", &numero);
    if(numero >= 15 && numero <= 24){
        printf("o numero esta presente em ambos os intervalos");
    }else if(numero <=10 || numero > 50 ){
        printf("o numero não se encontra em nenhum intervalo");
    }else{
        printf("o numero se encontra em apenas um intervalo");
    }
}


void procedimento0216(int numero1, int numero2){
    getchar();
    printf("Digite dois numeros inteiros: ");
    scanf("%d %d", &numero1, &numero2);
    if(numero1%2==0 && numero2%2!=0){
        printf("O primeiro numero digitado é par e o segundo é impar");
    }
    else{
        printf("Os numeros digitados não seguem a ordem de par e impar, consecutivamente");
    }
}


void procedimento0217(int numero1, int numero2){
    getchar();
    printf("Digite dois numeros inteiros: ");
    scanf("%d %d", &numero1, &numero2);
    if(numero1%2!=0 && numero1<0 && numero2%2==0 &&numero2>0){
        printf("O primeiro numero digitado é impar e negativo, e o segundo é par e positivo");
    }
    else{
        printf("Os numeros digitados não seguem a ordem de impar negativo e par positivo, respectivamente");
    }
}


void procedimento0218(double Numero1, double Numero2){
    double divisao=0;
    getchar();
    printf("Digite dois numeros reais: ");
    scanf("%lf %lf", &Numero1, &Numero2);
    divisao = Numero2/2.0;
    if(Numero1>divisao){
        printf("O primeiro numero digitado é maior que a metade do segundo");
    }
    else if(Numero1==divisao){
        printf("O primeiro numero digitado é igual a metade do segundo");
    }
    else{
        printf("O primeiro numero digitado é menor que a metade do segundo");
    }
}


void procedimento0219(double Numero1, double Numero2, double Numero3){
    getchar();
    printf("Digite tres numeros reais: ");
    scanf("%lf %lf %lf", &Numero1, &Numero2, &Numero3);
    if(Numero1!=Numero3 && Numero1<Numero2 && Numero3>Numero2){
        printf("O segundo numero digitado esta entre o primeiro e segundo numero digitados");
    }
    else{
        printf("O primeiro e ultimo numero são iguais ou o segundo numero digitado não esta entre o primeiro e terceiro");
    }
}


void procedimento0220(double Numero1, double Numero2, double Numero3){
    getchar();
    printf("Digite 3 numeros reais: ");
    scanf("%lf %lf %lf", &Numero1, &Numero2, &Numero3);
    if(Numero1!=Numero2 && Numero1!=Numero3 && Numero2!=Numero3 && Numero1<Numero2 && Numero3>Numero2){
        printf("Os numeros digitados são iguais entre si ou o segundo numero digitado esta entre o primeiro e o ultimo");
    }
    else{
        printf("Os numeros digitados são diferentes entre si e o segundo numero digitado não esta entre o primeiro e o ultimo");
    }
}


void procedimento02E1(char letra1, char letra2, char letra3){
    letra1='0';
    letra2 = '0';
    letra3 = '0';
    getchar();
    printf("Digite 3 caracteres: ");
    scanf("%c %c %c", &letra1, &letra2, &letra3);
    getchar();
    if(letra1>letra2 && letra1<letra3){
        printf("O primeiro caractere lido esta entre o segundo e o terceiro");
    }
    else if(letra1==letra2 || letra1==letra3 || letra2==letra3){
        printf("Os caracteres são iguais");
    }
    else{
        printf("O primeiro valor lido nao esta entre os outros dois ou não é igual a um deles");
    }
}


void procedimento02E2(char letra1, char letra2, char letra3){
    letra1='0';
    letra2 = '0';
    letra3 = '0';
    getchar();
    printf("Digite 3 caracteres: ");
    scanf("%c %c %c", &letra1, &letra2, &letra3);
    if(letra1!=letra2 && letra1!=letra3 && letra2!=letra3 && letra1<letra2 && letra1<letra3 || letra1>letra2 && letra1>letra3){
        printf("O primeiro valor lido esta fora do intervalo definido pelos outros dois, quando diferentes entre si");
        }
        else{
            printf("O primeiro valor lido esta entre o intervalo do segundo e terceiro ou os numeros são iguais");
        }
                }
    



int main(){
    int  numero, opcao, numero1, numero2;
    double Numero1, Numero2, Numero3;
    char letra1, letra2, letra3;
    do{
       printf("\nDigite um numero entre 1 a 12: ");
       scanf("%d", &opcao);
        switch(opcao){
case 1: procedimento0211(numero); break;
/*
Digite um numero inteiro: -6
O numero digitado é par 
Digite um numero inteiro: 0
O numero digitado é par 
Digite um numero inteiro: 9
O numero digitado é impar 
*/
case 2: procedimento0212(numero); break;
    /*
O numero digitado se encontra no intervalo de -15 e 15 ou é par menor que -15 ou impar maior que 15
Digite um numero inteiro: -17
O numero digitado é impar e menor que -15
Digite um numero inteiro: -16
O numero digitado se encontra no intervalo de -15 e 15 ou é par menor que -15 ou impar maior que 15 
Digite um numero inteiro: 6
O numero digitado se encontra no intervalo de -15 e 15 ou é par menor que -15 ou impar maior que 15
Digite um numero inteiro: 16
O numero digitado é par e maior que 15
Digite um numero inteiro: 19
O numero digitado se encontra no intervalo de -15 e 15 ou é par menor que -15 ou impar maior que 15
*/
case 3: procedimento0213(numero); break;
/*
Digite um numero inteiro: 15
O numero digitado esta fora do intervalo aberto de 25-45
Digite um numero inteiro: 30
O numero digitado esta dentro do intervalo aberto de 25-45
Digite um numero inteiro: 45
O numero digitado esta fora do intervalo aberto de 25-45
*/
case 4: procedimento0214(numero); break;
/*
Digite um numero inteiro: 5
O numero digitado esta fora do intervalo fechado de 20-60
Digite um numero inteiro: 20
O numero digitado esta dentro do intervalo fechado de 20-60
Digite um numero inteiro: 65
O numero digitado esta fora do intervalo fechado de 20-60 
*/
case 5: procedimento0215(numero); break;
/*
Digite um numero inteiro: 15
o numero se encontra em apenas um intervalo
Digite um numero inteiro: 20
o numero esta presente em ambos os intervalos
Digite um numero inteiro: 60
o numero não se encontra em nenhum intervalo
*/
case 6: procedimento0216(numero1, numero2); break;
/*
Digite dois numeros inteiros: 5 15
Os numeros digitados não seguem a ordem de par e impar, consecutivamente
Digite dois numeros inteiros: 50 63
O primeiro numero digitado é par e o segundo é impar
Digite dois numeros inteiros: 60 72
Os numeros digitados não seguem a ordem de par e impar, consecutivamente 
*/
case 7: procedimento0217(numero1, numero2); break;
/*
Digite dois numeros inteiros: -5 -15
Os numeros digitados não seguem a ordem de impar negativo e par positivo, respectivamente
Digite dois numeros inteiros: -13 20
O primeiro numero digitado é impar e negativo, e o segundo é par e positivo
Digite dois numeros inteiros: 60 72
Os numeros digitados não seguem a ordem de impar negativo e par positivo, respectivamente
*/
case 8: procedimento0218(Numero1, Numero2); break;
/*
Digite dois numeros reais: 0.5 1.5
O primeiro numero digitado é menor que a metade do segundo
Digite dois numeros reais: 5.0 10.0
O primeiro numero digitado é igual a metade do segundo
Digite dois numeros reais: 3.0 3.0
O primeiro numero digitado é maior que a metade do segundo
*/
case 9: procedimento0219(Numero1, Numero2, Numero3); break;
/*
Digite tres numeros reais: 0.75 0.5 1.8
O primeiro e ultimo numero são iguais ou o segundo numero digitado não esta entre o primeiro e terceiro 
Digite tres numeros reais: 1.2 3.7 5.9
O segundo numero digitado esta entre o primeiro e segundo numero digitados
*/
case 10: procedimento0220(Numero1, Numero2, Numero3); break;
/*
Digite 3 numeros reais: 1.2 3.6 8.9
Os numeros digitados são iguais entre si ou o segundo numero digitado esta entre o primeiro e o ultimo
Digite 3 numeros reais: 0.75 0.5 6.9
Os numeros digitados são diferentes entre si e o segundo numero digitado não esta entre o primeiro e o ultimo
Digite 3 numeros reais: 8.9 6.7 8.9
Os numeros digitados são diferentes entre si e o segundo numero digitado não esta entre o primeiro e o ultimo
*/
case 11: procedimento02E1(letra1, letra2, letra3); break;
/*
Digite 3 caracteres: a a c
Os caracteres são iguais ao
Digite 3 caracteres: f a z
O primeiro caractere lido esta entre o segundo e o terceiro
Digite 3 caracteres: a e c
O primeiro valor lido nao esta entre os outros dois ou não é igual a um deles
*/
case 12: procedimento02E2(letra1, letra2, letra3); break;
/*
Digite 3 caracteres: a e c
O primeiro valor lido esta fora do intervalo definido pelos outros dois, quando diferentes entre si
Digite 3 caracteres: a a a 
O primeiro valor lido esta entre o intervalo do segundo e terceiro ou os numeros são iguais
Digite 3 caracteres: b a c
O primeiro valor lido esta entre o intervalo do segundo e terceiro ou os numeros são iguais
*/
        default: printf("Opção invalida");
    }
    } while(opcao!=0);
    return (0);    
}
