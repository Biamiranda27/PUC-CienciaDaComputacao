

#include<stdio.h>
#include<string.h>
#include <ctype.h>

void metodo0411(int numeros, double num1, double num2, double num){
    int i=0, count=0, fora=0;
    getchar();
    printf("Digite a quantidade de números reais a serem testados: ");
    scanf("%d", &numeros);
    printf("Digite dois números reais para serem o limite: ");
    scanf("%lf %lf", &num1, &num2);
    printf("Digite %d numeros: ", numeros);
    for(i=0;i<numeros;i++){
        scanf("%lf\n",&num);
        if(num>=num1 && num<=num2){
            count++;
            printf("O numeros %.2lf esta no intervalo\n", num);
    }
    else{
        fora++;
        printf("O numeros %.2lf esta fora do intervalo\n", num);
    }
    }printf("%d números estão dentro do intervalo\n", count);
    printf("%d números estão fora do intervalo\n", fora);
    
    getchar();
}

void funcao02(char caracter[]){
    int i=0;
    for(i=0;i<strlen(caracter);i++){
    if(caracter[i]>='A' && caracter[i]<='Z'){
       //printf("A letra %c é maiuscula\n", caracter[i]);
    }
    }
}
void metodo0412(char caracter[]){
    int count=0, i=0;
    getchar();
    printf("Digite uma cadeia de caracteres: ");
    scanf("%s", &caracter[i]);
    for(i=0; i<strlen(caracter); i++){
    if(caracter[i]>='a' && caracter[i]<'m'){
        count++;
        printf("A letra %c é minuscula e menor que m\n", caracter[i]);
    } else{
        funcao02(caracter);
    }
    }
    printf("A cadeia de caracteres tem %d letras minusculas, menores que m", count);
}


void funcao03(char caracter[]){
    int i=0, count=0;
    printf("Digite uma cadeia de caracteres: ");
    scanf("%s", &caracter[i]);
    for(i=0;i<strlen(caracter); i++){
        if(caracter[i]>='a' && caracter[i]<'m'){
            count++;
            printf("%c é minúscula e menor que m\n", caracter[i]);
        }
    }
    printf("A cadeia de caracteres tem %d letras minúsculas e menor que m", count);
}
void metodo0413(){
    char caracter[100];
    funcao03(caracter);
    getchar();
}


void funcao04(char caracter[]){
    int i=0;
    printf("Digite uma cadeia de caracteres: ");
    scanf("%s", &caracter[i]);
    for(i=0;i<strlen(caracter); i++){
        if(caracter[i]>='a' && caracter[i]<'m'){
            printf("%c",caracter[i]);
        }
    }
}
void metodo0414(){
    char caracter[100];
    funcao04(caracter);
    getchar();
}


void funcao05(char caracter[]){
    int i=0, count=0;
    printf("Digite uma cadeia de caracteres: ");
    scanf("%s", &caracter[i]);
    for(i=0;i<strlen(caracter);i++){
        if(caracter[i]>='a' && caracter[i]<'m' || caracter[i]>='A' && caracter[i]<'M'){
            count++;
            printf("A letra %c é menor que m\n", caracter[i]);
        }
    }
    printf("A cadeia de caracteres tem %d letras menores que m", count);
}
void metodo0415(){
    char caracter[100];
    funcao05(caracter);
    getchar();
}


void funcao06(char caracter[]){
    int i=0;
    printf("Digite uma cadeia de caracteres: ");
    scanf("%s", &caracter[i]);
    for(i=0;i<strlen(caracter);i++){
        if(caracter[i]>'m' && caracter[i]<='z' || caracter[i]>'M' && caracter[i]<='Z'){
            printf("A letra %c é maior que m\n", caracter[i]);
        }
    }
}
void metodo0416(){
    char caracter[100];
    funcao06(caracter);
    getchar();
}


void funcao07(char caracter[]){
    int i=0, count=0;
    printf("Digite uma cadeia de caracteres: ");
    scanf("%s", &caracter[i]);
    for(i=0;i<strlen(caracter);i++){
        if(caracter[i]%2!=0 && !(caracter[i]>='a' && caracter[i]<='z' || caracter[i]>='A' && caracter[i]<='Z')){
            count++;
            printf("%c é impar\n", caracter[i]);
        }
    }
    printf("A cadeia de caracteres tem %d numeros impares", count);
}
void metodo0417(){
    char caracter[100];
    funcao07(caracter);
    getchar();
}


void funcao08(char caracter[]){
    int i=0;
    printf("Digite uma cadeia de caracteres: ");
    scanf("%s", &caracter[i]);
    for(i=0;i<strlen(caracter);i++){
        if(!(caracter[i]>='A' && caracter[i]<='Z' || caracter[i]>='a' && caracter[i]<='z' || caracter[i]>='0' && caracter[i]<='9')){
            printf("%c é um caracter não alfanumerico\n", caracter[i]);
        }
    }
}
void metodo0418(){
    char caracter[100];
    funcao08(caracter);
    getchar();
}


void funcao09(char caracter[]){
    int i=0;
    printf("Digite uma  cadeia de caracteres: ");
    scanf("%s", &caracter[i]);
    for(i=0;i<strlen(caracter); i++){
        if(caracter[i]>='A' && caracter[i]<='Z' || caracter[i]>='a' && caracter[i]<='z' || caracter[i]>='0' && caracter[i]<='9'){
            printf("%c é um caracter alfanumerico\n", caracter[i]);
        }
    }
}
void metodo0419(){
    char caracter[100];
    funcao09(caracter);
    getchar();
}


void funcao10(char caracter[]) {
    int cadeia, total= 0, count=0;
    printf("Digite a quantidade de cadeias de caracteres: ");
    scanf("%d", &cadeia);
    getchar();
    printf("Digite a cadeia de caracteres: ");
    for (int i = 0; i < cadeia; i++) {
        fgets(caracter, sizeof(caracter), stdin);
        caracter[strcspn(caracter, "\n")] = 0;
        for (int j = 0; j < strlen(caracter); j++) {
            if (isalnum(caracter[j])) {
                count++;
            }
        }
        printf("A cadeia '%s' contém %d símbolos alfanuméricos.\n", caracter, count);
        
    }
    printf("Total acumulado de símbolos alfanuméricos: %d\n", count);
    getchar();
}


void metodo0420(){
    char caracter[100];
    funcao10(caracter);
    getchar();
}


void funcao11(char caracter[]) {
    int n, total= 0, count=0;
    printf("Digite a quantidade de cadeias de caracteres: ");
    scanf("%d", &n);
    getchar();
    printf("Digite a cadeia de caracteres: ");
    for (int i = 0; i < n; i++) {
        fgets(caracter, sizeof(caracter), stdin);  
        caracter[strcspn(caracter, "\n")] = 0;
        for (int j = 0; j < strlen(caracter); j++) {
            if (isalnum(caracter[j]) || isspace(caracter[j])) {  
                count++;
            }
        }

        printf("A cadeia '%s' contém %d símbolos alfanuméricos e espaços.\n", caracter, count);
    }
    printf("Total acumulado de símbolos alfanuméricos e espaços: %d\n", count);
}
void metodo04E1(){
    char caracter[100];
    funcao11(caracter);
    getchar();
}


void funcao12(char palavra1[], char palavra2[]) {
    int digitos1 = 0, digitos2 = 0;
    printf("Digite a primeira cadeia de caracteres: ");
    getchar();
    fgets(palavra1, 100, stdin);
    palavra1[strcspn(palavra1, "\n")] = 0;  
    printf("Digite a segunda cadeia de caracteres: ");
    getchar();
    fgets(palavra2, 100, stdin);
    palavra2[strcspn(palavra2, "\n")] = 0; 
    for (int i = 0; i < strlen(palavra1); i++) {
        if (isdigit(palavra1[i])) {
            digitos1++;
        }
    }
    for (int i = 0; i < strlen(palavra2); i++) {
        if (isdigit(palavra2[i])) {
            digitos2++;
        }
    }
    if (digitos1 > digitos2) {
        printf("A primeira cadeia '%s' contém mais dígitos (%d)\n", palavra1, digitos1);
    } else if (digitos2 > digitos1) {
        printf("A segunda cadeia '%s' contém mais dígitos (%d)\n", palavra2, digitos2);
    } else {
        printf("Ambas as cadeias têm a mesma quantidade de dígitos (%d)\n", digitos1);
    }
}


void metodo04E2(){
    char palavra1[100];
    char palavra2[100];
    funcao12(palavra1, palavra2);
}


int main(){
    int opcao, numeros;
    double num1, num2, num;
    char caracter[100], palavra1[100], palavra2[100];
    do{
    printf("\nDigite um numero de 1 a 12: ");
    scanf("%d", &opcao);
    switch(opcao){
        case 1: metodo0411(numeros,num1,num2,num); break;
        /*
           Digite a quantidade de números reais a serem testados: 10
           Digite dois números reais para serem o limite: 13.6 22.6
           Digite 10 numeros: 5.1 10.5 12.4 14.2 15.3 18.3 20.4 21.7 23.1 24.2
           O numeros 5.10 esta fora do intervalo
           O numeros 10.50 esta fora do intervalo
           O numeros 12.40 esta fora do intervalo
           O numeros 14.20 esta no intervalo
           O numeros 15.30 esta no intervalo
           O numeros 18.30 esta no intervalo
           O numeros 20.40 esta no intervalo
           O numeros 21.70 esta no intervalo
           O numeros 23.10 esta fora do intervalo
           O numeros 24.20 esta fora do intervalo
           5 números estão dentro do intervalo
           5 números estão fora do intervalo
        */
       case 2: metodo0412(caracter); break;
        /*
           Digite uma cadeia de caracteres: AaKkLmMO*Nx
           A letra a é minuscula e menor que m
           A letra k é minuscula e menor que m
           A cadeia de caracteres tem 2 letras minusculas, menores que m
        */
       case 3: metodo0413(); break;
        /*
           a é minúscula e menor que m
           k é minúscula e menor que m
           A cadeia de caracteres tem 2 letras minúsculas e menor que m
        */
       case 4: metodo0414(); break;
        /*
          Digite uma cadeia de caracteres: AaKkLmMO*Nx
          ak
        */
       case 5: metodo0415(); break;
        /*
          Digite uma cadeia de caracteres: AaKkLmMO*Nx
          A letra A é menor que m
          A letra a é menor que m
          A letra K é menor que m
          A letra k é menor que m
          A letra L é menor que m
          A cadeia de caracteres tem 5 letras menores que m
        */
       case 6: metodo0416(); break;
        /*
           Digite uma cadeia de caracteres: AaKkLmMO*Nx
           A letra O é maior que m
           A letra N é maior que m
           A letra x é maior que m
        */
       case 7: metodo0417(); break;
        /*
           Digite uma cadeia de caracteres: A1b2C3d4E5f6
           1 é impar
           3 é impar
           5 é impar
           A cadeia de caracteres tem 3 numeros impares
        */
       case 8: metodo0418(); break;
        /*
           Digite uma cadeia de caracteres: (A1b2+C3d4)*IE5f6
           ( é um caracter não alfanumerico
           + é um caracter não alfanumerico
           ) é um caracter não alfanumerico
           * é um caracter não alfanumerico
        */
       case 9: metodo0419(); break;
        /*
          Digite uma  cadeia de caracteres: (A1b2+C3d4)*IE5f6
          A é um caracter alfanumerico
          1 é um caracter alfanumerico
          b é um caracter alfanumerico
          2 é um caracter alfanumerico
          C é um caracter alfanumerico
          3 é um caracter alfanumerico
          d é um caracter alfanumerico
          4 é um caracter alfanumerico
          I é um caracter alfanumerico
          E é um caracter alfanumerico
          5 é um caracter alfanumerico
          f é um caracter alfanumerico
          6 é um caracter alfanumerico
        */
       case 10: metodo0420(); break;
        /*
          Digite a quantidade de cadeias de caracteres: 3
          Digite a cadeia de caracteres: (A1b2+C3d4)*E5f6 [P&&Q]||[R&&!S] (a<b&&b<c)
          A cadeia '(A1b2+C' contém 5 símbolos alfanuméricos.
          A cadeia '3d4)*E5' contém 10 símbolos alfanuméricos.
          A cadeia 'f6 [P&&' contém 13 símbolos alfanuméricos.
          Total acumulado de símbolos alfanuméricos: 13
        */
       case 11: metodo04E1(); break;
        /*
          Digite a quantidade de cadeias de caracteres: 3
          Digite a cadeia de caracteres: (A1b2+C3d4)*E5f6
          A cadeia '(A1b2+C' contém 5 símbolos alfanuméricos e espaços.
          A cadeia '3d4)*E5' contém 10 símbolos alfanuméricos e espaços.
          A cadeia 'f6' contém 12 símbolos alfanuméricos e espaços.
          Total acumulado de símbolos alfanuméricos e espaços: 12
        */
       case 12: metodo04E2(); break;
        /*
          Digite a primeira cadeia de caracteres: A1b2
          Digite a segunda cadeia de caracteres: C3d4E5
          A segunda cadeia '3d4E5' contém mais dígitos (3)
        */
       default: printf("Opção invalida");
    }
    }
        while(opcao!=0);
    return(0);
}
