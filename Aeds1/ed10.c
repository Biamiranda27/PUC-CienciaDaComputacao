
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>
#define CONSTANTE 10


void numeros(FILE *f, int a,int b,int n){
    srand(time(NULL));
    int num,x; 
    fprintf(f,"%d numeros irão ser gravados no arquivo\n",n);
    for(x=0;x<n;x++){
        num = rand() % (b - a + 1) + a;
        fprintf(f,"Número aleatório entre %d e %d: %d\n",a,b,num);
    }
}
void metodo1011(){
    FILE *f;
    f = fopen("dados.txt","w");
    if(f == NULL){
        printf("Erro na abertura");
        system ("pause");
        exit (1);
    }
    int a,b,n;
    printf("Digite dois valores para serem o limite (o primeiro sendo menor que o segundo): ");
    scanf("%d %d", &a,&b);
    printf("Digite quantos numeros devem ser gerados: ");
    scanf("%d",&n);
    numeros(f,a,b,n);
    fclose(f);
}


void procurar(FILE *f, int n){
    int valor, encontrado = 0;
    while (fscanf(f, "%*[^:]: %d", &valor) != EOF) {
        if (valor == n) {
            encontrado = 1;
            break;  
        }
    }
    if(encontrado=>1){
        printf("Esse valor esta no arquivo");
    }else{
        printf("Nao tem esse valor no arquivo");
    }
}
void metodo1012(){
    FILE *f;
    f = fopen("dados.txt","r");
    if(f == NULL){
        printf("Erro na abertura\n");
        system("pause");
        exit (1);
    }
    int n;
    printf("Digite um numero: ");
    scanf("%d",&n);
    procurar(f,n);
    fclose(f);
}


bool comparar(char *palavra1,char *palavra2){
    int a,b;
    a=strlen(palavra1);
    b=strlen(palavra2);
    if(a==b){
        return true;
    }else{
        return false;
    }
}
void array(FILE *a, FILE *b){
    char palavra1[20];
    printf("Digite uma palavra: ");
    scanf("%s",palavra1);
    char palavra2[20];
    printf("Digite outra palavra: ");
    scanf("%s",palavra1);
    fprintf(a,"%s/n",palavra1);
    fprintf(b,"%s/n",palavra2);
    fclose(a);
    fclose(b);
    a = fopen("dados1.txt", "r");
    b = fopen("dados2.txt", "r");
    if (a == NULL || b == NULL) {
        printf("Erro na abertura");
        exit(1);
    }
    fscanf(a, "%s", palavra1);
    fscanf(b, "%s", palavra2);
    if(comparar(palavra1, palavra2)){
        printf("As palavras tem o mesmo tamanho");
    }
    else{
        printf("As palavras tem tamanhos diferentes");
    }
    fclose(a);
    fclose(b);
}
void metodo1013(){
    FILE *a;
    a = fopen("dados1.txt","w");
    if(a == NULL){
        printf("Erro na abertura");
        system("pause");
        exit(1);
    }
    FILE *b;
    b = fopen("dados2.txt","w");
    if(b == NULL){
        printf("Erro na abertura");
        system("pause");
        exit(1);
    }
    array(a,b);
    fclose(a);
    fclose(b);
}


void soma(FILE *a, FILE *b, int *array1, int *array2, int t1, int t2){
    int x,y,novo1=0,novo2=0,total=0;
    if(t1==t2){
        for(y=0;y<t2;y++){
            novo2+=array2[y]*CONSTANTE;
        }
        for(x=0;x<t1;x++){
            novo1+=array[x];
        }
        total=novo1+novo2;
        printf("A soma dos dois arranjos, com os elementos do segundo multiplicados por uma constante é: %d\n",total);
    }else{
        printf("Os arrays não tem o mesmo tamanho");
    }
}
void print_array(FILE *a, FILE *b, int *array1, int *array2, int t1, int t2){
    int x,y;
    for(x=0;x<t1;x++){
        printf("Digite o numero %d do array 1: ",x+1);
        scanf("%d",&array1[x]);
        fprintf(a,"O numero %d pertence ao array 1 \n",array1[x]);
    }
    for(y=0;y<t2;y++){
        printf("Digite o numero %d do array 2: ",y+1);
        scanf("%d",&array2[y]);
        fprintf(b,"O numero %d pertence ao array 2 \n",array2[y]);
    }
    soma(a,b,array1,array2,t1,t2);
}
void metodo1014(){
    FILE *a;
    a = fopen("dados1.txt","w");
    if(a == NULL){
        printf("Erro na abertura");
        exit(1);
    }
    FILE *b;
    b = fopen("dados2.txt","w");
    if(b == NULL){
        printf("Erro na abertura");
        exit(1);
    }
    int t1,t2;
    int array1[100],array2[100];
    printf("Digite o tamanho do primeiro array: ");
    scanf("%d",&t1);
    printf("Digite o tamanho do segundo array: ");
    scanf("%d",&t2);
    print_array(a,b,array1,array2,t1,t2);
    fclose(a);
    fclose(b);
}


int crescente(int *array, int i){
    int x,a=array[0];
    for(x=1;x<i;x++){
        if(a>array[x]){
            return 0;
        }
        a=array[x];
    }
    return 1;
}
int ler_array(FILE *f, int *array){
   int i=0;
    while (fscanf(f, "%d", &array[i]) != EOF) {
        i++; 
    }
     return i;
}
 void metodo1015(){
    FILE *f;
    f = fopen("dados1.txt","r");
    if(f==NULL){
        printf("Erro na abertura");
        exit(1);
    }
    int array[100];
    int n = ler_array(f,array);
    if(crescente(array,n)){
        printf("O array esta em ordem crescente");
    }else{
        printf("O array não esta em ordem crescente");
    }
    fclose(f);
 }


void transpota(FILE *f,int matriz[][30],int linha,int coluna){
    int x,y;
    for(x=0;x<coluna;x++){
        for(y=0;y<linha;y++){
            printf("%d",matriz[y][x]);
            fprintf(f,"%d ",matriz[y][x]);
        }
        printf("\n");
        fprintf(f,"\n");
    }
}
void numeros(FILE *f,int matriz[][30],int linha,int coluna){
    int x,y;
    fprintf(f,"A matriz é: ");
    for(x=0;x<linha;x++){
        for(y=0;y<coluna;y++){
            printf("Digite um numero para a linha %d e coluna %d: ",x,y);
            scanf("%d ",&matriz[x][y]);
            fprintf(f,"%d ",matriz[x][y]);
        }
        fprintf("\n");
    }
    printf("A mesma matriz transpota é: \n");
    fprintf(f,"A matriz transpota é: ");
    transpota(f,matriz,linha,coluna);
}
int tamanho(int linha,int coluna){
    if(linha==coluna){
        return 1;
    }
    return 0;
}
void metodo1016(){
    FILE *f;
    f = fopen("dados1.txt","w");
    if(f==NULL){
        printf("Erro na abertura");
        exit(1);
    }
    int matriz[30][30],linha,coluna;
    printf("Digite o numero de linhas e colunas para a matriz: ");
    scanf("%d %d",&linha, &coluna);
    if(tamanho(linha,coluna)){
        printf("Os tamanhos das matrizes são compativeis");
    }else{
        printf("Os tamanhos das matrizes não são compativeis");
    }

        numeros(f,matriz,linha,coluna);
    fclose(f);
}


int testar(matriz[][40],int x,int y){
    int a,b;
    for(a=0;a<x;a++){
        for(b=0;b<y;b++){
            if(matriz[a][b]==0){
                return 0;
            }
        }
    }
    return 1;
}
int ler_matriz(FILE *f,matriz[][40],int *coluna){
    int x=0,y=0;
    while (fscanf(f, "%d", &matriz[x][y]) != EOF) {
        y++; 
        if(fgetc(f)=='\n'){
            x++;
            *coluna=y;
            y=0;
        }
    }
     return x;
}
void metodo1017(){
    FILE *f;
    f = fopen("dados1.txt","r");
    if(f==NULL){
        printf("Erro na abertura");
        exit (1);
    }
    int matriz[40][40],coluna=0;
    int linha = ler_matriz(f,matriz,&coluna);
    if(testar(matriz,linha,coluna)){
        printf("So tem valores nulos");
    }else{
        printf("Não tem so valores nulos");
    }
    fclose(f);
}


void ler_matriz1(FILE *a, int matriz1[][30],int linha,int coluna){
int x,y;
for(x=0;x<linha;x++){
    for(y=0;y<coluna;y++){
        fscanf(a,"%d",&matriz1[x][y]);
    }
}
}
void escrever_matriz2(FILE *b,int linha2,int coluna2,int matriz2[][30]){
    int x,y;
    fprintf(b,"Os valores da matriz são: \n");
    for(x=0;x<linha2;x++){
        for(y=0;y<coluna2;y++){
            printf("Digite um valor para a linha %d e coluna %d: ",x,y);
            scanf("%d",&matriz2[x][y]);
            fprintf(b,"%d ",matriz2[x][y]);
        }
    }
}
void comparar_valores(int matriz1[][30],int linha,int coluna, int matriz2[][30],int linha2, int coluna2){
    int x,y,iguais=1;
    for (x=0;x<linha;x++) {
        for (y=0;y<coluna;y++) {
            if (matriz1[x][y]!=matriz2[x][y]) {
                iguais=0;
                break;
            }
        }
        if (!iguais) break; // Sai do loop se encontrar valores diferentes
    }
    if (iguais) {
        printf("As matrizes são iguais.\n");
    } else {
        printf("As matrizes são diferentes.\n");
    }
}
void metodo1018(){
    FILE *a;
    a=fopen("dados1.txt","r");
    if(a==NULL){
        printf("Erro na abertura");
        exit(1);
    }
    FILE *b;
    b=fopen("dados2.txt","w");
    if(b==NULL){
        printf("Erro na abertura");
        exit(1);
    }
    int linha2,coluna2,linha,coluna,matriz2[30][30],int matriz1[30][30];
    printf("Digite o numero de linhas e colunas da matriz: ");
    scanf("%d %d",&linha2,&coluna2);
    fscanf(a, "%d %d", &linha, &coluna);
    ler_matriz1(a,matriz1,linha,coluna);
    escrever_matriz2(b,linha2,coluna2,matriz2);
    if(linha==linha2 && coluna==coluna2){
        comparar_valores(matriz1,linha,coluna,matriz2,linha2,coluna2);
    }
    else{
        printf("As matrizes não tem igualdades");
    }
    fclose(a);
    fclose(b);
}


void ler_matriz1(FILE *a, int matriz1[][30],int linha,int coluna){
int x,y;
for(x=0;x<linha;x++){
    for(y=0;y<coluna;y++){
        fscanf(a,"%d",&matriz1[x][y]);
    }
}
}
void lerMatriz2(FILE *b,int linha2,int coluna2,int matriz2[][30]){
int x,y;
for(x=0;x<linha2;x++){
    for(y=0;y<coluna2;y++){
        fscanf(b,"%d",&matriz2[x][y]);
    }
}
}
void somaMatriz(int linha2,int coluna2,int matriz2[][30],int matriz1[][30]){
    int x,y,novo=0,final=0;
    for(x=0;x<linha2;x++){
        for(y=0;y<coluna2;y++){
            novo=matriz2[x][y] * CONSTANTE;
            final+=novo+matriz1[x][y];
        }
    }
    printf("A soma das duas matrizes, com os elementos da segunda multiplicados por uma constante é: %d\n",final);
}
void compararValores(int matriz1[][30],int linha,int coluna, int matriz2[][30]){
    int x,y,iguais=1;
    for (int x = 0; x < linha; x++) {
        for (int y = 0; y < coluna; y++) {
            if (matriz1[x][y] != matriz2[x][y]){
                iguais = 0;
                break;
            }
        }
        if (!iguais) break;
    }
    if (iguais) {
        printf("As matrizes são iguais.\n");
    } else {
        printf("As matrizes são diferentes.\n");
            }
}
void metodo1019(){
    FILE *a;
    a=fopen("dados1.txt","r");
    if(a==NULL){
        printf("Erro na abertura");
        exit(1);
    }
    FILE *b;
    b=fopen("dados2.txt","r");
    if(b==NULL){
        printf("Erro na abertura");
        exit(1);
    }
    int linha2,coluna2,linha,coluna,matriz2[30][30],matriz1[30][30];
    fscanf(a, "%d %d", &linha, &coluna);
    fscanf(b,"%d %d",&linha2,&coluna2);
    ler_matriz1(a,matriz1,linha,coluna);
    lerMatriz2(b,linha2,coluna2,matriz2);
    if(linha==linha2 && coluna==coluna2){
        compararValores(matriz1,linha,coluna,matriz2);
        somaMatriz(linha2,coluna2,matriz2,matriz1);
    }
    else{
        printf("As matrizes não tem igualdades");
    }
    fclose(a);
    fclose(b);
}


void matriz1_ler(FILE *a,int linha1,int coluna1, int matriz1[][30]){
    int x,y;
    for(x=0;x<linha1;x++){
        for(y=0;y<coluna1;y++){
            fscanf(a,"%d",&matriz1[x][y]);
        }
    }
}
void matriz2_ler(FILE *b,int linha2,int coluna2, int matriz2[][30]){
    int x,y;
    for(x=0;x<linha2;x++){
        for(y=0;y<coluna2;y++){
            fscanf(b,"%d",&matriz2[x][y]);
        }
    }
}
void  produtoMatriz(int matriz1[][30],int matriz2[][30],int linha1,int coluna1,int linha2,int coluna2,int matriz3[][30]){
    int i,j,k;
    for(i=0;i<linha1;i++){
        for(j=0;j<coluna2;j++){
            matriz3[i][j]=0;
        }
    }
    for(i=0;i<linha1;i++){
        for(j=0;j<coluna2;j++){
            for(k=0;k<coluna1;k++){
            matriz3[i][j]+=matriz1[i][k]*matriz2[k][j];
            }
        }
    }
    printf("A matriz resultande do produto de duas matrizes é:\n");
    for(i=0;i<linha1;i++){
        for(j=0;j<coluna2;j++){
            printf("%d ",matriz3[i][j]);
        }
        printf("\n");
    }
}
void metodo1020(){
    FILE *a;
    a=fopen("dados1.txt","r");
    if(a==NULL){
        printf("Erro na abertura");
        exit(1);
    }
    FILE *b;
    b=fopen("dados2.txt","r");
    if(b==NULL){
        printf("Erro na abertura");
        exit(1);
    }
    int linha1,coluna1,linha2,coluna2, matriz1[30][30],matriz2[30][30],matriz3[30][30];
    fscanf(a,"%d %d",&linha1,&coluna1);
    fscanf(b,"%d %d",&linha2,&coluna2);
    matriz1_ler(a,linha1,coluna1,matriz1);
    matriz2_ler(b,linha2,coluna2,matriz2);
    if(coluna1==linha2){
        produtoMatriz(matriz1,matriz2,linha1,coluna1,linha2,coluna2,matriz3);
    }else{
        printf("As matrizes são de tamanho diferente");
    }
    fclose(a);
    fclose(b);
}


void ordenarDecrescente(int *array,int tamanho) {
    int i, j, temp;
    for (i=0;i<tamanho-1;i++) {
        for (j=0;j<tamanho-i-1;j++) {
            if (array[j]<array[j+1]) {
                temp=array[j];
                array[j]=array[j+1];
                array[j+1]=temp;
            }
        }
    }
}
void lerArranjo(FILE *f, int *array,int tamanho) {
    *tamanho = 0;
    while (fscanf(f, "%d", &array[*tamanho]) != EOF) {
        (*tamanho)++;
    }
}
void metodo10E1() {
    FILE *f;
    f=fopen("dados1.txt", "r");
    if(f==NULL) {
        printf("Erro na abertura");
        exit(1);
    }
    int array[100],tamanho;
    lerArranjo(f,array,tamanho)
    ordenarDecrescente(array, tamanho);
    printf("Arranjo em ordem decrescente:\n");
    imprimirArranjo(array, tamanho);
    fclose(f);
}


void lerMatriz1(FILE *a,int matriz1[][30],int linha1,int coluna1) {
    int x,y;
    for (x=0;x<linha1;x++) {
        for (y=0;y<coluna1;y++) {
            fscanf(a, "%d", &matriz1[x][y]);
        }
    }
}
void lerMatriz2(FILE *b,int matriz2[][30],int linha2,int coluna2) {
    int a,b;
    for (a=0;a<linha2;a++) {
        for (b=0;b<coluna2;b++) {
            fscanf(b, "%d", &matriz2[a][b]);
        }
    }
}
void produtoMatrizes(int matriz1[][30],int matriz2[][30],int resultado[][30],int linha1,int coluna1,int linha2,int coluna2) {
    int i,j,k;
    printf("Resultado do produto das matrizes:\n");
    for (i=0;i<linha1;i++) {
        for (j=0;j<coluna2;j++) {
            resultado[i][j] = 0;
            for (k=0;k<coluna1;k++) {
                resultado[i][j]+=matriz1[i][k]*matriz2[k][j];
                printf("%d ",resultado[i][j]);
            }
        }
    }
}
bool matrizIdentidade(int matriz[][30],int tamanho) {
    int i,j;
    for (i=0;i<tamanho;i++) {
        for (j=0;j<tamanho;j++) {
            if ((i==j && matriz[i][j]!=1) || (i!=j && matriz[i][j]!=0)) {
                return false;
            }
        }
    }
    return true;
}
void metodo10E2() {
    FILE *a;
    a=fopen("dados1.txt", "r");
    if(a==NULL) {
        printf("Erro na abertura");
        exit(1);
    }
    FILE *b;
    b=fopen("dados2.txt", "r");
    if(b==NULL) {
        printf("Erro na abertura");
        exit(1);
    }
    int matriz1[30][30],matriz2[30][30],linha1,coluna1,linha2,coluna2,resultado[30][30];
    fscanf(a, "%d %d",&linha1,&coluna1);
    fscanf(b, "%d %d",&linha2,&coluna2);
    lerMatriz(a, matriz1, &linha1, &coluna1);
    lerMatriz(b, matriz2, &linha2, &coluna2);
    if (coluna1 != linha2) {
        printf("As matrizes são de tamanho diferente\n");
        return;
    }
    produtoMatrizes(matriz1, matriz2, resultado, linha1, coluna1, linha2, coluna2);
    if (linha1 == coluna2 && matrizIdentidade(resultado, linha1)) {
        printf("O produto das matrizes é igual à matriz identidade.\n");
    } else {
        printf("O produto das matrizes não é igual à matriz identidade.\n");
    }
    fclose(a);
    fclose(b);
}



int main(){
    int opcao;
    do{
        printf("Digite um numero entre 1-12: ");
        scanf("%d",&opcao);
        switch(opcao){
            case 1: metodo1011();break;
            /*
Digite dois valores para serem o limite (o primeiro sendo menor que o segundo): 10 20
Digite quantos numeros devem ser gerados: 5
5 numeros irão ser gravados no arquivo
Número aleatório entre 10 e 20: 14
Número aleatório entre 10 e 20: 17
Número aleatório entre 10 e 20: 12
Número aleatório entre 10 e 20: 19
Número aleatório entre 10 e 20: 11
            */
           case 2: metodo1012();break;
            /*
Digite um número: 14
Esse valor está no arquivo.
            */
           case 3: metodo1013();break;
            /*
Digite a primeira palavra: palavra
Digite a segunda palavra: carro
As palavras têm tamanhos diferentes
            */
           case 4: metodo1014();break;
            /*
Digite o tamanho do primeiro array: 3
Digite o tamanho do segundo array: 3
Digite o numero 1 do array 1: 5
Digite o numero 2 do array 1: 10
Digite o numero 3 do array 1: 15
Digite o numero 1 do array 2: 2
Digite o numero 2 do array 2: 4
Digite o numero 3 do array 2: 6
A soma dos dois arranjos, com os elementos do segundo multiplicados por uma constante é: 95
            */
           case 5: metodo1015();break;
            /*
5 10 15
O array está em ordem crescente
            */
           case 6: metodo1016();break;
            /*
Digite o número de linhas e colunas para a matriz: 2 3
Digite um número para a linha 0 e coluna 0: 1
Digite um número para a linha 0 e coluna 1: 2
Digite um número para a linha 0 e coluna 2: 3
Digite um número para a linha 1 e coluna 0: 4
Digite um número para a linha 1 e coluna 1: 5
Digite um número para a linha 1 e coluna 2: 6
A matriz é:
1 2 3
4 5 6
A matriz transposta é:
1 4
2 5
3 6
            */
           case 7: metodo1017();break;
            /*
1 4
2 5
3 6
A matriz contém valores diferentes de zero.
            */
           case 8: metodo1018();break;
            /*
Digite o número de linhas e colunas para a segunda matriz: 2 2
Digite um valor para a linha 0 e coluna 0: 1
Digite um valor para a linha 0 e coluna 1: 2
Digite um valor para a linha 1 e coluna 0: 3
Digite um valor para a linha 1 e coluna 1: 4
As matrizes são iguais.
            */
           case 9: metodo1019();break;
            /*
1 4
2 5
3 6

1 2
3 4

As matrizes não tem igualdades
            */
           case 10: metodo1020();break;
            /*
1 4
2 5
3 6

1 2
3 4

As matrizes são de tamanho diferente
            */
           case 11: metodo10E1();break;
            /*
1 4
2 5
3 6

Elementos da matriz em ordem decrescente:
6 5 4 3 2 1
            */
           case 12: metodo10E2();break;
            /*
1 4
2 5
3 6

1 2
3 4

As matrizes são de tamanhos diferentes
            */
           default: printf("Numero invalido\n");break;
        }
    } while(opcao!=0);
    return (0);
}
