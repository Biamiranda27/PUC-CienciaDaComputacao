


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void programa0111(int lado){
    printf("Digite um numero inteiro que represente o lado de um quadrado: ");
    scanf("%d", &lado);
    int lado2 = 0, area = 0;
    lado2 = lado*2;
    area = lado2*lado2;
    printf("A area de outro quadrado com o lado equivalente ao dobro do lado original é: %d", area);
}
int main(){
    int lado;
    programa0111(lado);
    return(0);
}
/*
Digite um numero inteiro que represente o lado de um quadrado: 5
 A area de outro quadrado com o lado equivalente ao dobro do lado original é: 100
*/ 


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void programa0112(int lado){
printf("Digite o lado de um quadrado: ");
scanf("%d", &lado);
double terco = 0, area = 0, perimetro = 0;
terco = (1.0/3.0)*lado;
area = terco*terco;
perimetro = 4*terco;
printf("A area e o perimetro de um quadrado com um terço do tamanho dado anteriormente é: %lf, %lf, respectivamente", area, perimetro);
}
int main(){
    int lado;
    programa0112(lado);
    return(0);
}
/* 
Digite o lado de um quadrado: 5
A area e o perimetro de um quadrado com um terço do tamanho dado anteriormente é: 2.777778, 6.666667, respectivamente 
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void programa0113(int num1, int num2){
    printf("Digite dois valores que representem lados de um retangulo: ");
    scanf("%d %d", &num1, &num2);
    int tres = 0;
    tres = (num1*3)*(num2*3);
    printf("A area com valores aumentados em tres vezes cada: %d", tres);
}
int main(){
    int num1, num2;
    programa0113(num1, num2);
    return(0);
}
/*
Digite dois valores que representem lados de um retangulo: 3 5
A area com valores aumentados em tres vezes cada: 135 
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void programa0114(int num1, int num2){
    printf("Digite um valor para a largura e comprimento de um retangulo: ");
    scanf("%d %d", &num1, &num2);
    double area = 0, sexto1 = 0, sexto2 = 0, perimetro = 0;
    sexto1 = (1.0/6.0)*num1;
    sexto2 = (1.0/6.0)*num2;
    area = sexto1*sexto2;
    perimetro = (2*num1)+(2*num2);
    printf("A area e o perimetro de um retangulo com um sexto dos tamanhos da largura e comprimento dados é: %lf, %lf, respectivamente", area, perimetro);
}
int main(){
    int num1, num2;
    programa0114(num1, num2);
    return(0);
}
/*
Digite um valor para a largura e comprimento de um retangulo: 3 5
A area e o perimetro de um retangulo com um sexto dos tamanhos da largura e comprimento dados é: 0.416667, 16.000000, respectivamente 
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void programa0115(double base, double altura){
    printf("Digite dois valores reais que representem a base e a altura de um triangulo: ");
    scanf("%lf %lf", &base, &altura);
    double metade = 0, area = 0;
    metade = altura/2.0;
    area = (base*metade)/2.0;
    printf("A area do triangulo com a metade da altura dada é: %lf", area);
}
int main(){
    double base, altura;
    programa0115(base, altura);
    return(0);
}
/*
Digite dois valores reais que representem a base e a altura de um triangulo: 3 4
A area do triangulo com a metade da altura dada é: 3.000000 
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void programa0116(double lado){
    printf("Digite um valor real que representa o lado de um triangulo equilatero: ");
    scanf("%lf", &lado);
    double quatro = 0, altura = 0, area = 0, perimetro = 0;
    quatro = 4*lado;
    altura = (quatro*sqrt(3))/2.0;
    area = (quatro*altura)/2.0;
    perimetro = 3*quatro;
    printf("A altura, area e o perimetro do triangulo com quatro vezes o tamanho do lado dado é: %lf, %lf, %lf, respectivamente");
}
int main(){
    double lado;
    programa0116(lado);
    return(0);
}
/*
Digite um valor real que representa o lado de um triangulo equilatero: 5
A altura, area e o perimetro do triangulo com quatro vezes o tamanho do lado dado é: -nan, 0.000000, 0.000000, respectivamente 
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void programa0117(double lado){
    printf("Digite um valor real que representa a medida de um lado do cubo: ");
    scanf("%lf", &lado);
    double sete = 0, volume = 0;
    sete = lado*7;
    volume = pow(sete,3);
    printf("O volume do cubo com sete vezes a medida do lado é: %lf", volume);
}
int main(){
    double lado;
    programa0117(lado);
    return(0);
}
/*
Digite um valor real que representa a medida de um lado do cubo: 5
O volume do cubo com sete vezes a medida do lado é: 42875.000000 
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void programa0118(double comprimento, double, largura, double altura){
    printf("Digite valores para o comprimento, largura e altura: ");
    scanf("%lf %lf %lf", &comprimento, &largura, &altura);
    double quinto1 = 0, quinto2 = 0, quinto3 = 0, volume = 0;
    quinto1 = (1.0/5.0)*comprimento;
    quinto2 = (1.0/5.0)*largura;
    quinto3 = (1.0/5.0)*altura;
    volume = comprimento*largura*altura;
    printf("O volume do paralelepipedo com um quinto dos valores dado: %lf", volume); 
}
int main(){
    double comprimento, largura, altura;
    programa0118(comprimento, largura, altura);
    return(0);
}
/*
Digite valores para o comprimento, largura e altura: 3 4 5
O volume do paralelepipedo com um quinto dos valores dado: 60.000000 
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14

void exemplo0119(double raio){
    printf("Digite o valor do raio de um circulo: ");
    scanf("%lf", &raio);
    double area = 0, quarto = 0, semicirculo = 0;
    quarto = (1.0/4.0)*raio;
    area = PI*(pow(quatro,2));
    semicirculo = area/2.0;
    printf("A area de um semicirculo com um quarto do raio dado é: %lf", semicirculo);
}
int main(){
    double raio;
    exemplo0119(raio);
    return(0);
}
/*
Digite o valor do raio de um circulo: 5
A area de um semicirculo com um quarto do raio dado é: 2.453125
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14

void exemplo0120(double raio){
    printf("Digite um valor real que representa o raio de uma esfera: ");
    scanf("%lf", &raio);
    double volume = 0, tres = 0;
    tres = (3.0/5.0)*raio;
    volume = (4.0/3.0)*PI*(pow(tres,3));
    printf("O volume da esfera com tres quintos do raio dado é: %lf", volume);
}
int main(){
    double raio;
    exemplo0120(raio);
    return(0);
}
/*
Digite um valor real que representa o raio de uma esfera: 5
O volume da esfera com tres quintos do raio dado é: 113.040000
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14

void programa01E1(double raio){
printf("Digite um valor real que defina a area de uma circuferencia: ");
    scanf("%lf", &raio);
    double area = 0, nono = 0;
    area = PI * (pow(raio,2));
    nono = area/9.0;
    printf("O raio de um nono dessa circuferencia é: %lf", nono);
}
int main(){
    double raio;
    programa01E1(raio);
    return(0);
}
/*
Digite um valor real que defina a area de uma circuferencia: 5
O raio de um nono dessa circuferencia é: 8.722222 
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14

void programa01E2(double raio){
    printf("Digite um valor real que represente o volume de uma esfera: ");
    scanf("%lf", &raio);
    double volume = 0, fracao = 0, area = 0;
    volume = (4.0/3.0)*PI*(pow(raio,3));
    fracao = (3.0/7.0)*volume;
    area = 4*PI*(pow(raio,2));
    printf("O raio de tres setimos do volume da esfere e a area da superfice é: %lf, %lf, respectivamente", fracao, area);
}
int main(){
    double raio;
    programa01E2(raio);
    return(0);
}
/*
Digite um valor real que represente o volume de uma esfera: 5
O raio de tres setimos do volume da esfere e a area da superfice é: 224.285714, 314.000000, respectivamente
*/
