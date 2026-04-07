

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#define MAX_PALAVRAS 100
#define MAX_TAMANHO_PALAVRA 50

void metodo0811(){
    int array[100],n,i;
    printf("Digite o tamanho do array: ");
    scanf("%d",&n);
    if(n>0){
    for(i=0;i<n;i++){
        printf("Digite o numero %d: ",i);
        scanf("%d", &array[i]);
        while(array[i]<0 || array[i]%2==0){
            printf("Digite outro numero %d: ",i);
            scanf("%d",&array[i]);
        }
    }
    } else{
        printf("Digite outro valor para o tamanho do array: ");
        scanf("%d",&n);
    }
}


void metodo0812(){
    char arquivo[100];
    int array[100],tamanho,i;
    printf("Digite o nome do arquivo (com a extensão .txt): ");
    scanf("%s",&arquivo);
    FILE *f;
    f=fopen(arquivo,"w");
    if(f==NULL){
        printf("Erro na abertura");
        system("pause");
        exit(1);
    }
    printf("Digite o tamanho do array: \n");
    scanf("%d",&tamanho);
    for(i=0;i<tamanho;i++){
        printf("Digite o numero %d: \n");
        scanf("%d",&array[i]);
        while(array[i]<0 || array[i]%2==0){
            printf("Digite outro numero %d: \n",i);
            scanf("%d",&array[i]);
        }
    }
    fprintf(f,"%d\n",tamanho);
    for(i=0;i<tamanho;i++){
        fprintf(f,"%d\n",array[i]);
    }
    fclose(f);
    printf("O tamanho do array e seus números foram gravado no arquivo %s\n",arquivo);
}


void funcao(int n1,int n2,int v,FILE *f){
    int vetor[100],i,numero;
    int gerarlnt(int inferior, int superior) {
        return rand() % (superior - inferior + 1) + inferior;
    }
    for(i=0;i<v;i++){
    numero = gerarlnt(n1,n2);
    vetor[i]=numero;
    }
for(i=0;i<v;i++){
        fprintf(f,"%d\n",vetor[i]);
    }
}
void metodo0813(){
    int num1,num2,vezes;
    FILE *f;
    f = fopen("dados.txt","w");
    if(f == NULL){
        printf("Erro na abertura");
        system("pause");
        exit(1);
    }
    printf("Digite dois numeros para serem o limite: \n");
    scanf("%d %d",&num1, &num2);
    printf("Quantos numeros voce deseja que sejam gerados: \n");
    scanf("%d",&vezes);
    fprintf(f,"Quantidade de numeros: %d\n",vezes);
    funcao(num1,num2,vezes,f);
    fclose(f);
}


void lerArquivo(int array[], int *n) {
    int i;
    FILE *f;
    f = fopen("dados.txt", "r");  
    if (f == NULL) {
        printf("Erro na abertura");
        system("pause");
        exit(1);
    }
    fscanf(f, "%d", n);  
    for (i=0;i<*n;i++) {
        fscanf(f, "%d", &array[i]);  
    }
    fclose(f);
}
int acharMenorImpar(int array[], int n) {
    int menor = -1,i;  
    for (i = 0;i<n;i++) {
        if (array[i]%2!=0) { 
            if (menor == -1 || array[i] < menor) {
                menor = array[i];  
            }
        }
    }
    return menor;
}
void metodo0814() {
    int array[100],n; 
    lerArquivo(array, &n);
    int menorImpar = acharMenorImpar(array, n);
    if (menorImpar != -1) {
        printf("O menor numero impar no arranjo e: %d\n", menorImpar);
    } else {
        printf("Nao ha numeros impares no arranjo.\n");
    }
}


void lerArquivo(int *n, int array[]){
    int i;
    FILE *f;
    f = fopen("dados.txt","r");
    if(f == NULL){
        printf("Erro na abertura");
        system("pause");
        exit(1);
    }
    fscanf(f,"%d",n);
    for(i=0;i<*n;i++){
        fscanf(f,"%d",&array[i]);
    }
    fclose(f);
}
void acharMaiorParDivisivelPorTres(int n,int array[]){
    int maior = 3,i;
  for(i=0;i<n;i++){
    if(array[i]%2==0){
        if(array[i]%3==0){
        maior=array[i];
        }
    }
  }
  printf("O maior par divisivel por tres é: %d",maior); 
}
void metodo0815(){
    int array[100],n;
    lerArquivo(&n,array);
    acharMaiorParDivisivelPorTres(n,array);
}


void lerArquivo(int *n, int array[]){
    int i;
    FILE *f;
    f = fopen("dados.txt","r");
    if(f == NULL){
        printf("Erro na abertura");
        system("pause");
        exit(1);
    }
    fscanf(f,"%d",n);
    for(i=0;i<*n;i++){
        fscanf(f,"%d",&array[i]);
    }
    fclose(f);
}
void acharMedia(int n,int array[100],FILE *a,FILE *c){
   int m = 0,media,b;
for(int i=0;i<n;i++){
    m+=array[i];
}media=m/n;
for(i=0;i<n;i++){
    b=array[i];
    if(b<=media){
        fprintf(c,"%d é menor ou igual a media\n ",b);
    }else{
        fprintf(a,"%d é maior que a media\n ",b);
    }
} 
} 
void metodo0816(){
    int array[100],n,i;
    lerArquivo(&n,array);
    FILE *d;
    d = fopen("menores.txt","w");
    if(f == NULL){
        printf("Erro na abertura");
        system("pause");
        exit(1);
    }
    FILE *a;
    a = fopen("maiores.txt","w");
    if(a == NULL){
        printf("Erro na abertura");
        system("pause");
        exit(1);
    }
    acharMedia(n,array,d,a);
    fclose(d);
    fclose(a);
}


void funcao(int n,int array[100]){
    int m=array[0],i;
    for(i=1;i<n;i++){
        if(m>array[i]){
            printf("O array esta em ordem crescente");
        }else{
            printf("O array esta em ordem decrescente");
        }
    }
}
void metodo0817(){
    int array[100],n,i;
    printf("Digite quantos numeros voce deseja digitar: ");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        printf("Digite o numero %d: \n",i);
        scanf("%d",&array[i]);
    }
    funcao(n,array);
}


void lerArquivo(int *n, int array[]){
    int i;
    FILE *f;
    f = fopen("dados.txt","r");
    if(f == NULL){
        printf("Erro na abertura");
        system("pause");
        exit(1);
    }
    fscanf(f,"%d",n);
    for(i=0;i<*n;i++){
        fscanf(f,"%d",&array[i]);
    }
    fclose(f);
}
void acharValor(int n,int num,int array[]){
    int i,a;
    for(i=0;i<n;i++){
        a = array[i];
        if(a==num){
            printf("Esse numero exite");
        } else{
            printf("Esse numero não exite");
        }
    }
}
void metodo0818(){
    int num,n,array[100];
    lerArquivo(&n,array);
    printf("Digite um numero: ");
    scanf("%d",num);
    acharValor(n,num,array);
}


void lerArquivo(int *n, int array[]){
    int i;
    FILE *f;
    f = fopen("dados.txt","r");
    if(f == NULL){
        printf("Erro na abertura");
        system("pause");
        exit(1);
    }
    fscanf(f,"%d",n);
    for(i=0;i<*n;i++){
        fscanf(f,"%d",&array[i]);
    }
    fclose(f);
}
void acharPosicao(int n,int num,int array){
    int i,a;
    for(i=0;i<n;i++){
        a = array[i];
        if(a==num){
            printf("Esse numero exite e esta na posicao %d",i);
        } else{
            printf("Esse numero não exite");
        }
    }
}
void metodo0819(){
    int num,n,array[100];
    lerArquivo(&n,array);
    printf("Digite um numero: ");
    scanf("%d",num);
    acharPosicao(n,num,array);
}


void lerArquivo(int *n, int array[]){
    int i;
    FILE *f;
    f = fopen("dados.txt","r");
    if(f == NULL){
        printf("Erro na abertura");
        system("pause");
        exit(1);
    }
    fscanf(f,"%d",n);
    for(i=0;i<*n;i++){
        fscanf(f,"%d",&array[i]);
    }
    fclose(f);
}
void acharQuantos(int n,int num,int array[]){
    int i,a,count=0;
    for(i=0;i<n;i++){
        a = array[i];
        if(a==num){
            count++;
        } 
    }printf("Esse numero aparece %d vezes",count);
}
void metodo0820(){
    int num,n,array[100];
    lerArquivo(&n,array);
    printf("Digite um numero: ");
    scanf("%d",&num);
    acharQuantos(n,num,array);
}


int calcularDivisoresImpares(int n, int divisores[]) {
    int count = 0,i;
    for (i=1;i<=n;i++) {
        if (n%i==0 && i%2!=0) {
            divisores[count] = i;
            count++;
        }
    }
    return count;
}
void gravarDivisoresArquivo(int divisores[], int quantidade) {
    int i;
    FILE *f;
    f = fopen("divisores.txt", "w");
    if (f == NULL) {
        printf("Erro na abertura");
        system("pause");
        exit(1);
    }
    fprintf(f, "Divisores ímpares:\n");
    for (i=0;i<quantidade;i++) {
        fprintf(f, "%d\n", divisores[i]);
    }
    fclose(f);
}
void metodo08E1() {
    int n,vezes,i;
    int divisores[100]; 
    printf("Digite um valor inteiro: ");
    scanf("%d", &n);
    vezes = calcularDivisoresImpares(n, divisores);
    printf("Divisores ímpares de %d:\n", n);
    for (i=0;i<vezes;i++) {
        printf("%d ", divisores[i]);
    }
    printf("\n");
    gravarDivisoresArquivo(divisores,vezes);
}


int letraD(char palavra[]) {
    int tamanho = strlen(palavra);
    char primeira = palavra[0];
    char ultima = palavra[tamanho - 1];\
    if (tolower(primeira) == 'd' || tolower(ultima) == 'd') {
        return 1; 
    }else{
    return 0; 
    }
}
int tamanho(char palavras[MAX_PALAVRAS][MAX_TAMANHO_PALAVRA], int totalPalavras, char resultado[10][MAX_TAMANHO_PALAVRA]) {
    int count = 0;
    for (int i = 0; i < totalPalavras && count < 10; i++) {
        if (!letraD(palavras[i])) {
            strcpy(resultado[count], palavras[i]);
            count++;
        }
    }
    return count; 
}
void metodo08E1() {
    FILE *f;
    char palavras[MAX_PALAVRAS][MAX_TAMANHO_PALAVRA];
    char resultado[10][MAX_TAMANHO_PALAVRA];
    int total = 0, i;
    f = fopen("palavras.txt", "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    while (fscanf(f, "%s", palavras[total]) != EOF && total < MAX_PALAVRAS) {
        total++;
    }
    fclose(f);
    int palavrasEncontradas = tamanho(palavras, total, resultado);
    if (palavrasEncontradas > 0) {
        printf("As palavras encontradas que não começam nem terminam com 'd' ou 'D' são:\n");
        for (i = 0; i < palavrasEncontradas; i++) {
            printf("%s\n", resultado[i]);
        }
    } else {
        printf("Nenhuma palavra encontrada que atenda aos critérios.\n");
    }
}




int main(){
    int opcao;
    do{
        printf("Digite um nuemro entre 1-12: ");
        scanf("%d",&opcao);
        switch(opcao){
    case 1: metodo0811();break;
    /*
    Digite o tamanho do array: 5
Digite o numero 0: 2
Digite outro numero 0: 3
Digite o numero 1: 5
Digite o numero 2: 7
Digite o numero 3: 8
Digite outro numero 3: 4
Digite outro numero 3: 2
Digite outro numero 3: 5
Digite o numero 4: 9
    */
    case 2: metodo0812();break;
    /*
    Digite o nome do arquivo (com a extensão .txt): numeros.txt
Digite o tamanho do array: 
4
Digite o numero 0: 
8
Digite outro numero 0: 
7
Digite o numero 1: 
12
Digite outro numero 1: 
3
Digite o numero 2: 
-5
Digite outro numero 2: 
5
Digite o numero 3: 
10
Digite outro numero 3: 
11
O tamanho do array e seus números foram gravado no arquivo numeros.txt
    */
    case 3: metodo0813();break;
    /*
    Digite dois numeros para serem o limite: 
10 50
Quantos numeros voce deseja que sejam gerados: 
5
Quantidade de numeros: 5
27
13
45
33
11
    */
    case 4: metodo0814();break;
    /*
    5
10
25
30
15
45
O menor numero impar no arranjo e: 15
    */
    case 5: metodo0815();break;
    /*
    6
12
8
18
5
9
24
O maior par divisivel por tres é: 24
    */
    case 6: metodo0816();break;
    /*
    5
10
20
30
40
50
10 é menor ou igual a media
20 é menor ou igual a media
30 é menor ou igual a media
40 é maior que a media
50 é maior que a media
    */
    case 7: metodo0817();break;
    /*
    Digite quantos números você deseja digitar: 5
Digite o número 1:
1
Digite o número 2:
2
Digite o número 3:
3
Digite o número 4:
4
Digite o número 5:
5
O array está em ordem crescente
    */
    case 8: metodo0818();break;
    /*
Digite um numero: 10
Esse numero existe
    */
    case 9: metodo0819();break;
    /*
    Digite um numero: 15
Esse numero existe e esta na posicao 2
    */
    case 10: metodo0820();break;
    /*
    Digite um numero: 2
    Esse numero aparece 4 vezes
    */
    case 11: metodo08E1();break;
    /*
    Divisores ímpares:
1
3
5
15
    */
    case 12: metodo08E2();break;
    /*
    dado cachorro panda davi doce uva casa amor
    As palavras encontradas que não começam nem terminam com 'd' ou 'D' são:
cachorro
panda
uva
casa
amor
    */
    default: printf("Opção invalida");break;
        }
    }while(opcao!=0);
    returm(0);
}
