

#include<stdio.h>
#include<stdlib.h>

/* Incluir um método (0911) para ler as dimensões (quantidade de linhas e de colunas) de uma matriz real do teclado, 
bem como todos os seus elementos (apenas valores positivos ou zeros). Verificar se as dimensões não são nulas ou negativas.
Para testar, ler dados e mostrá-los na tela por outro método.
Exemplo: double positiveMatrix [10][10]; readPositiveDoubleMatrix ( 3, 3, positiveMatrix ); printDoubleMatrix ( 3, 3, positiveMatrix );
*/
void readPositiveMatriz(int linhas, int colunas, double matriz[linhas][colunas]) {
    int x, y;
    for (x = 0; x < linhas; x++) {
        for (y = 0; y < colunas; y++) {
            do {
                printf("Digite um valor real positivo para matriz[%d][%d]: ", x, y);
                scanf("%lf", &matriz[x][y]);
                if (matriz[x][y] < 0) {
                    printf("Valor inválido! Digite novamente.\n");
                }
            } while (matriz[x][y] < 0); 
        }
    }
}
void printMatriz(int linhas, int colunas, double matriz[linhas][colunas]){
    int x,y;
    for(x=0;x<linhas;x++){
        for (y=0;y<colunas;y++){
            printf("%lf\t",matriz[x][y]);
        }
        printf("\n");
    }
}
void metodo0911() {
    int linhas, colunas;
    double matriz[20][20];

    printf("Digite o número de linhas e colunas da matriz: ");
    scanf("%d %d", &linhas, &colunas);
    if (linhas > 0 && colunas > 0) {
        readPositiveMatriz(linhas, colunas, matriz);  
    } else {
        printf("Dimensões inválidas, digite novamente");
        metodo0911(); 
    }
    printMatriz(linhas,colunas,matriz);
}


/*Incluir um método (0912) para
gravar uma matriz real em arquivo.
A matriz e o nome do arquivo serão dados como parâmetros.
Para testar, usar a leitura da matriz do problema anterior.
Usar outro método para ler e recuperar a matriz do arquivo, antes de mostrá-la na tela.
Exemplo: double positiveMatrix [10][10];
readPositiveMatrix DoubleMatrix ( 3, 3, positiveMatrix ); fprintDoubleMatrix ( "MATRIX_01.TXT", 3, 3, positiveMatrix );*/

void readPositiveMatrix(int linhas, int colunas, double matriz[linhas][colunas]) {
    int x, y;
    for (x=0;x<linhas;x++) {
        for (y=0;y<colunas;y++) {
            do {
                printf("Digite um valor real positivo para matriz[%d][%d]: ", x, y);
                scanf("%lf", &matriz[x][y]);
                if (matriz[x][y] < 0) {
                    printf("Valor inválido! Digite novamente.\n");
                }
            } while (matriz[x][y] < 0); 
        }
    }
}
void fprintDoubleMatrix(const char* nomeArquivo, int linhas, int colunas, double matriz[linhas][colunas]) {
    int i,j;
    FILE* file = fopen(nomeArquivo, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    fprintf(file, "%d %d\n", linhas, colunas);
    for (i=0;i<linhas;i++) {
        for (j=0;j<colunas;j++) {
            fprintf(file, "%lf ", matriz[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file); 
    printf("Matriz gravada em %s\n", nomeArquivo);
}
void freadDoubleMatrix(const char* nomeArquivo, int* linhas, int* colunas, double matriz[*linhas][*colunas]) {
    int i,j;
    FILE* file = fopen(nomeArquivo, "r"); 
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    fscanf(file, "%d %d", linhas, colunas);
    for (i=0;i<*linhas;i++) {
        for (j=0;j<*colunas;j++) {
            fscanf(file, "%lf", &matriz[i][j]);
        }
    }
    fclose(file); 
    printf("Matriz %s lida\n", nomeArquivo);
}
void printMatriz(int linhas, int colunas, double matriz[linhas][colunas]){
    int x, y;
    for (x=0;x<linhas;x++) {
        for (y=0;y<colunas;y++) {
            printf("%lf\t", matriz[x][y]);
        }
        printf("\n");
    }
}
void metodo0912() {
    double positiveMatrix[10][10];
    int linhas = 3, colunas = 3;
    double matriz[10][10];
    int linhasLidas, colunasLidas;
    readPositiveMatrix(linhas, colunas, positiveMatrix);
    fprintDoubleMatrix("MATRIX_01.TXT", linhas, colunas, positiveMatrix);
    freadDoubleMatrix("MATRIX_01.TXT", &linhasLidas, &colunasLidas, matriz);
    printf("Matriz lida do arquivo:\n");
    printMatriz(linhasLidas, colunasLidas, matriz);
}


/*Incluir um método (0913) para
mostrar somente os valores na diagonal principal de uma matriz real, se for quadrada.
Exemplo: double positiveMatrix [10][10];
readPositiveMatrix DoubleMatrix ( 3, 3, positiveMatrix ); printDiagonalDoubleMatrix ( 3, 3, positiveMatrix );
*/

void readMatriz(int linhas, int colunas, double matriz[linhas][colunas]){
    int x,y;
    for(x=0;x<linhas;x++){
        for(y=0;y<colunas;y++){
            printf("Digite um numero real para a matriz [%d][%d]: ",x,y);
            scanf("%lf",&matriz[x][y]);
        }
    }
}
void printDiagonalMatriz(int linhas,int colunas,double matriz[linhas][colunas]){
    //diagonal principal é linha=coluna
    int x,y;
    for(x=0;x<linhas;x++){
        for(y=0;y<colunas;y++){
            if(x==y){
                printf("%lf\t",matriz[x][y]);
            }
        }
    }
}
void metodo0913(){
    int linhas,colunas;
    double matriz[20][20];
    printf("Digite o numero de linhas e colunas: ");
    scanf("%d %d",&linhas,&colunas);
    if(linhas==colunas){
        readMatriz(linhas,colunas,matriz);
    }else{
        printf("Dimensões inválidas, digite novamente\n");
        metodo0913();
    }
    printDiagonalMatriz(linhas,colunas,matriz);
}


/*Incluir um método (0914) para
mostrar somente os valores na diagonal secundária de uma matriz real, se for quadrada.
Exemplo: double positiveMatrix [10][10]; readPositiveDoubleMatrix ( 3, 3, positiveMatrix ); printSDiagonalDoubleMatrix ( 3, 3, positiveMatrix );*/

void readMatriz(int linhas, int colunas, double matriz[linhas][colunas]){
    int x,y;
    for(x=0;x<linhas;x++){
        for(y=0;y<colunas;y++){
            printf("Digite um numero real para a matriz [%d][%d]: ",x,y);
            scanf("%lf",&matriz[x][y]);
        }
    }
}
void printDiagonalMatriz(int linhas,int colunas,double matriz[linhas][colunas]){
    int x;
    for(x=0;x<linhas;x++){
     printf("%lf\t", matriz[x][colunas - x - 1]);
    }
    printf("\n");
}
void metodo0914(){
    int linhas,colunas;
    double matriz[20][20];
    printf("Digite o numero de linhas e colunas: ");
    scanf("%d %d",&linhas,&colunas);
    if(linhas==colunas){
        readMatriz(linhas,colunas,matriz);
    }else{
        printf("Dimensões inválidas, digite novamente\n");
        metodo0914();
    }
    printDiagonalMatriz(linhas,colunas,matriz);
}


/*Incluir um método (0915) para
mostrar somente os valores abaixo e na diagonal principal de uma matriz real, se for quadrada.
Exemplo: double positiveMatrix [10][10]; readPositiveDoubleMatrix ( 3, 3, positiveMatrix ); printLDTriangleDoubleMatrix ( 3, 3, positiveMatrix );*/

void readMatriz(int linhas, int colunas, double matriz[linhas][colunas]){
    int x,y;
    for(x=0;x<linhas;x++){
        for(y=0;y<colunas;y++){
            printf("Digite um numero real para a matriz [%d][%d]: ",x,y);
            scanf("%lf",&matriz[x][y]);
        }
    }
}
void printDiagonalMatriz(int linhas,int colunas,double matriz[linhas][colunas]){
    int x,y;
    for(x=0;x<linhas;x++){
        for(y=0;y<colunas;y++){
            if(x==y){
                printf("%lf\t",matriz[x][y]);
            }else if(x>y){
                printf("%lf\t",matriz[x][y]);
            } 
            printf("\t");
        }
    printf("\n");
    }
}
void metodo0915(){
    int linhas,colunas;
    double matriz[20][20];
    printf("Digite o numero de linhas e colunas: ");
    scanf("%d %d",&linhas,&colunas);
    if(linhas==colunas){
        readMatriz(linhas,colunas,matriz);
    }else{
        printf("Dimensões inválidas, digite novamente\n");
        metodo0915();
    }
    printDiagonalMatriz(linhas,colunas,matriz);
}


/*Incluir um método (0916) para
mostrar somente os valores acima e na diagonal principal de uma matriz real, se for quadrada.
Exemplo: double positiveMatrix [10][10]; readPositiveDoubleMatrix ( 3, 3, positiveMatrix ); printLUTriangleDoubleMatrix ( 3, 3, positiveMatrix );*/

void readMatriz(int linhas, int colunas, double matriz[linhas][colunas]){
    int x,y;
    for(x=0;x<linhas;x++){
        for(y=0;y<colunas;y++){
            printf("Digite um numero real para a matriz [%d][%d]: ",x,y);
            scanf("%lf",&matriz[x][y]);
        }
    }
}
void printDiagonalMatriz(int linhas,int colunas,double matriz[linhas][colunas]){
    int x,y;
    for(x=0;x<linhas;x++){
        for(y=0;y<colunas;y++){
            if(x==y){
                printf("%lf\t",matriz[x][y]);
            }else if(x<y){
                printf("%lf\t",matriz[x][y]);
            } 
            printf("\t");
        }
    printf("\n");
    }
}
void metodo0916(){
    int linhas,colunas;
    double matriz[20][20];
    printf("Digite o numero de linhas e colunas: ");
    scanf("%d %d",&linhas,&colunas);
    if(linhas==colunas){
        readMatriz(linhas,colunas,matriz);
    }else{
        printf("Dimensões inválidas, digite novamente\n");
        metodo0916();
    }
    printDiagonalMatriz(linhas,colunas,matriz);
}


/* Incluir um método (0917) para
mostrar somente os valores abaixo e na diagonal secundária de uma matriz real, se for quadrada.
Exemplo: double positiveMatrix [10][10]; readPositiveDoubleMatrix ( 3, 3, positiveMatrix ); printSLDTriangleDoubleMatrix ( 3, 3, positiveMatrix );*/

void readMatriz(int linhas, int colunas, double matriz[linhas][colunas]){
    int x,y;
    for(x=0;x<linhas;x++){
        for(y=0;y<colunas;y++){
            printf("Digite um numero real para a matriz [%d][%d]: ",x,y);
            scanf("%lf",&matriz[x][y]);
        }
    }
}
void printDiagonalMatriz(int linhas,int colunas,double matriz[linhas][colunas]){
    int x,y;
    for(x=0;x<linhas;x++){
        for(y=0;y<colunas;y++){
            if(x+y>=linhas-1){
                printf("%lf\t",matriz[x][y]);
            }
    }
}
}
void metodo0917(){
    int linhas,colunas;
    double matriz[20][20];
    printf("Digite o numero de linhas e colunas: ");
    scanf("%d %d",&linhas,&colunas);
    if(linhas==colunas){
        readMatriz(linhas,colunas,matriz);
    }else{
        printf("Dimensões inválidas, digite novamente\n");
        metodo0917();
    }
    printDiagonalMatriz(linhas,colunas,matriz);
}

/*Incluir um método (0918) para
mostrar somente os valores acima e na diagonal secundária de uma matriz real, se for quadrada.
Exemplo: double positiveMatrix [10][10]; readPositiveDoubleMatrix ( 3, 3, positiveMatrix ); printSLUTriangleDoubleMatrix ( 3, 3, positiveMatrix );*/

void readMatriz(int linhas, int colunas, double matriz[linhas][colunas]){
    int x,y;
    for(x=0;x<linhas;x++){
        for(y=0;y<colunas;y++){
            printf("Digite um numero real para a matriz [%d][%d]: ",x,y);
            scanf("%lf",&matriz[x][y]);
        }
    }
}
void printDiagonalMatriz(int linhas,int colunas,double matriz[linhas][colunas]){
    int x,y;
    for(x=0;x<linhas;x++){
        for(y=0;y<colunas;y++){
            if(x+y<=linhas-1){
                printf("%lf\t",matriz[x][y]);
            }
    }
}
}
void metodo0918(){
    int linhas,colunas;
    double matriz[20][20];
    printf("Digite o numero de linhas e colunas: ");
    scanf("%d %d",&linhas,&colunas);
    if(linhas==colunas){
        readMatriz(linhas,colunas,matriz);
    }else{
        printf("Dimensões inválidas, digite novamente\n");
        metodo0918();
    }
    printDiagonalMatriz(linhas,colunas,matriz);
}


/*Incluir uma função (0919) para
testar se não são todos zeros os valores abaixo da diagonal principal de uma matriz real quadrada.
Exemplo: double positiveMatrix [10][10];
readPositiveDoubleMatrix ( 3, 3, positiveMatrix ); bool result = allZerosLTriangleDoubleMatrix ( 3, 3, positiveMatrix );*/

void readMatriz(int linhas, int colunas, double matriz[linhas][colunas]){
    int x,y;
    for(x=0;x<linhas;x++){
        for(y=0;y<colunas;y++){
            printf("Digite um numero real para a matriz [%d][%d]: ",x,y);
            scanf("%lf",&matriz[x][y]);
        }
    }
}
void printDiagonalMatriz(int linhas,int colunas,double matriz[linhas][colunas]){
    int x,y,count=0;
    for(x=0;x<linhas;x++){
        for(y=0;y<colunas;y++){
             if(x>y){
                if(matriz[x][y]!=0){
                printf("%lf\t",matriz[x][y]);
                }else{
                    count++;
                }
            } 
            printf("\t");
        }
    printf("\n");
    }if(count>=linhas){
        printf("Todos os valores sao igual a zero");
    }
}
void metodo0919(){
    int linhas,colunas;
    double matriz[20][20];
    printf("Digite o numero de linhas e colunas: ");
    scanf("%d %d",&linhas,&colunas);
    if(linhas==colunas){
        readMatriz(linhas,colunas,matriz);
    }else{
        printf("Dimensões inválidas, digite novamente\n");
        metodo0919();
    }
    printDiagonalMatriz(linhas,colunas,matriz);
}

/*Incluir uma função (0920) para
testar se são zeros os valores acima da diagonal principal de uma matriz real quadrada.
Exemplo: double positiveMatrix [10][10];
readPositiveDoubleMatrix ( 3, 3, positiveMatrix ); bool result = allZerosUTriangleDoubleMatrix ( 3, 3, positiveMatrix );*/

void readMatriz(int linhas, int colunas, double matriz[linhas][colunas]){
    int x,y;
    for(x=0;x<linhas;x++){
        for(y=0;y<colunas;y++){
            printf("Digite um numero real para a matriz [%d][%d]: ",x,y);
            scanf("%lf",&matriz[x][y]);
        }
    }
}
void printDiagonalMatriz(int linhas,int colunas,double matriz[linhas][colunas]){
    int x,y,count=0;
    for(x=0;x<linhas;x++){
        for(y=0;y<colunas;y++){
             if(x<y){
                 if(matriz[x][y]==0){
                count++;
                 }else{
                     printf("%lf\t",matriz[x][y]);
                 }
            } 
            printf("\t");
        }
    printf("\n");
    }if(count>=linhas){
        printf("Os valores são iguais a zero");
    }
}
void metodo0920(){
    int linhas,colunas;
    double matriz[20][20];
    printf("Digite o numero de linhas e colunas: ");
    scanf("%d %d",&linhas,&colunas);
    if(linhas==colunas){
        readMatriz(linhas,colunas,matriz);
    }else{
        printf("Dimensões inválidas, digite novamente\n");
        metodo0920();
    }
    printDiagonalMatriz(linhas,colunas,matriz);
}


/*Incluir definições e testes (09E1) testes para
ler do teclado as quantidades de linhas e colunas de uma matriz,
e montar uma matriz com a característica abaixo,
a qual deverá ser gravada em arquivo, após o retorno.
Exemplos:
1 4 7 1 3 2 5 8 2 4 3 6 9
1 5 9 13 2 6 10 14 3 7 11 15 4 8 12 16*/

void matriz2(FILE *f,int linhas,int colunas,int matriz[linhas][colunas]){
int x,y;
for(x=0;x<linhas;x++){
    for(y=0;y<colunas;y++){
        fprintf(f,"%d\t",matriz[x][y]);
    }
    fprintf(f,"\n");
}
fprintf(f,"\n");
}
void matriz3(FILE *f,int linhas,int colunas,int matriz[linhas][colunas]){
int x,y;
for(x=0;x<linhas;x++){
    for(y=0;y<colunas;y++){
        fprintf(f,"%d\t",matriz[x][y]);
    }
    fprintf(f,"\n");
}
fprintf(f,"\n");
}
void matriz4(FILE *f,int linhas,int colunas,int matriz[linhas][colunas]){
int x,y;
for(x=0;x<linhas;x++){
    for(y=0;y<colunas;y++){
        fprintf(f,"%d\t",matriz[x][y]);
    }
    fprintf(f,"\n");
}
}
void metodo09E1(){
    int a[2][2] = {{1,3},{2,4}};
    int b[3][3] = {{1,4,7},{2,5,8},{3,6,9}};
    int c[4][4] = {{1,5,9,13},{2,6,10,14},{3,7,11,15},{4,8,12,16}};
    FILE *f;
    f = fopen("matriz.txt","w");
    if(f==NULL){
        printf("Erro ao abrir");
        system("pause");
        return(1);
    }
    matriz2(f,2,2,a);
    matriz3(f,3,3,b);
    matriz4(f,4,4,c);
    fclose(f);
}

/*Incluir definições e testes (09E2) para
ler do teclado as quantidades de linhas e colunas de uma matriz,
e montar uma matriz com a característica abaixo,
a qual deverá ser gravada em arquivo, após o retorno.
Exemplos:
16 15 14 13 9 8 7 12 11 10 9 436548765 213214321*/

void matriz2(FILE *f,int linhas,int colunas,int matriz[linhas][colunas]){
int x,y;
for(x=0;x<linhas;x++){
    for(y=0;y<colunas;y++){
        fprintf(f,"%d\t",matriz[x][y]);
    }
    fprintf(f,"\n");
}
fprintf(f,"\n");
}
void matriz3(FILE *f,int linhas,int colunas,int matriz[linhas][colunas]){
int x,y;
for(x=0;x<linhas;x++){
    for(y=0;y<colunas;y++){
        fprintf(f,"%d\t",matriz[x][y]);
    }
    fprintf(f,"\n");
}
fprintf(f,"\n");
}
void matriz4(FILE *f,int linhas,int colunas,int matriz[linhas][colunas]){
int x,y;
for(x=0;x<linhas;x++){
    for(y=0;y<colunas;y++){
        fprintf(f,"%d\t",matriz[x][y]);
    }
    fprintf(f,"\n");
}
}
void metodo09E2(){
    int a[2][2] = {{4,3},{2,1}};
    int b[3][3] = {{9,8,7},{6,5,4},{3,2,1}};
    int c[4][4] = {{16,15,14,13},{12,11,10,9},{8,7,6,5,},{4,3,2,1}};
    FILE *f;
    f = fopen("matriz.txt","w");
    if(f==NULL){
        printf("Erro ao abrir");
        system("pause");
        return(1);
    }
    matriz2(f,2,2,a);
    matriz3(f,3,3,b);
    matriz4(f,4,4,c)
    fclose(f);
}


int main(){
    int opcao;
    do{
        printf("Digite um numero de 1-12: \n");
        scanf("%d",&opcao);
        switch(opcao){
            case 1: metodo0911();break;
/*
            Digite um valor real positivo para matriz[0][0]: 1
            Digite um valor real positivo para matriz[0][1]: 2
            Digite um valor real positivo para matriz[1][0]: 3
            Digite um valor real positivo para matriz[1][1]: 4
            1.000000        2.000000
            3.000000        4.000000
*/

           case 2: metodo0912();break;
/*
            Digite um valor real positivo para matriz[0][0]: 1.1
Digite um valor real positivo para matriz[0][1]: 2.2
Digite um valor real positivo para matriz[0][2]: 3.3
Digite um valor real positivo para matriz[1][0]: 4.4
Digite um valor real positivo para matriz[1][1]: 5.5
Digite um valor real positivo para matriz[1][2]: 6.6
Digite um valor real positivo para matriz[2][0]: 7.7
Digite um valor real positivo para matriz[2][1]: 8.8
Digite um valor real positivo para matriz[2][2]: 9.9

Matriz gravada em MATRIX_01.TXT
Matriz lida de MATRIX_01.TXT
Matriz lida do arquivo:
1.100000    2.200000    3.300000    
4.400000    5.500000    6.600000    
7.700000    8.800000    9.900000    

3 3
1.100000 2.200000 3.300000 
4.400000 5.500000 6.600000 
7.700000 8.800000 9.900000 

*/

           case 3: metodo0913();break;
/*
            Digite o numero de linhas e colunas: 3 3
Digite um numero real para a matriz [0][0]: 1
Digite um numero real para a matriz [0][1]: 2
Digite um numero real para a matriz [0][2]: 3
Digite um numero real para a matriz [1][0]: 4
Digite um numero real para a matriz [1][1]: 5
Digite um numero real para a matriz [1][2]: 6
Digite um numero real para a matriz [2][0]: 7
Digite um numero real para a matriz [2][1]: 8
Digite um numero real para a matriz [2][2]: 9
1.000000        5.000000        9.000000
*/

           case 4: metodo0914();break;
/*
            Digite o numero de linhas e colunas: 3 3
Digite um numero real para a matriz [0][0]: 1
Digite um numero real para a matriz [0][1]: 2
Digite um numero real para a matriz [0][2]: 3
Digite um numero real para a matriz [1][0]: 4
Digite um numero real para a matriz [1][1]: 5
Digite um numero real para a matriz [1][2]: 6
Digite um numero real para a matriz [2][0]: 7
Digite um numero real para a matriz [2][1]: 8
Digite um numero real para a matriz [2][2]: 9
3.000000        5.000000        7.000000
*/

           case 5: metodo0915();break;
/*
            Digite o numero de linhas e colunas: 3 3
Digite um numero real para a matriz [0][0]: 1
Digite um numero real para a matriz [0][1]: 2
Digite um numero real para a matriz [0][2]: 3
Digite um numero real para a matriz [1][0]: 4
Digite um numero real para a matriz [1][1]: 5
Digite um numero real para a matriz [1][2]: 6
Digite um numero real para a matriz [2][0]: 7
Digite um numero real para a matriz [2][1]: 8
Digite um numero real para a matriz [2][2]: 9
1.000000
4.000000                5.000000
7.000000                8.000000                9.000000
*/

           case 6: metodo0916();break;
/*
            Digite o numero de linhas e colunas: 3 3
Digite um numero real para a matriz [0][0]: 1
Digite um numero real para a matriz [0][1]: 2
Digite um numero real para a matriz [0][2]: 3
Digite um numero real para a matriz [1][0]: 4
Digite um numero real para a matriz [1][1]: 5
Digite um numero real para a matriz [1][2]: 6
Digite um numero real para a matriz [2][0]: 7
Digite um numero real para a matriz [2][1]: 8
Digite um numero real para a matriz [2][2]: 9
1.000000                2.000000                3.000000
        5.000000                6.000000
                9.000000
*/

           case 7: metodo0917();break;
/*
            Digite o numero de linhas e colunas: 3 3
Digite um numero real para a matriz [0][0]: 1
Digite um numero real para a matriz [0][1]: 2
Digite um numero real para a matriz [0][2]: 3
Digite um numero real para a matriz [1][0]: 4
Digite um numero real para a matriz [1][1]: 5
Digite um numero real para a matriz [1][2]: 6
Digite um numero real para a matriz [2][0]: 7
Digite um numero real para a matriz [2][1]: 8
Digite um numero real para a matriz [2][2]: 9
3.000000        5.000000        6.000000        7.000000        8.000000       9.000000
            */

           case 8: metodo0918();break;
/*
            Digite o numero de linhas e colunas: 3 3
Digite um numero real para a matriz [0][0]: 1
Digite um numero real para a matriz [0][1]: 2
Digite um numero real para a matriz [0][2]: 3
Digite um numero real para a matriz [1][0]: 4
Digite um numero real para a matriz [1][1]: 5
Digite um numero real para a matriz [1][2]: 6
Digite um numero real para a matriz [2][0]: 7
Digite um numero real para a matriz [2][1]: 8
Digite um numero real para a matriz [2][2]: 9
1.000000        2.000000        3.000000        4.000000        5.000000       7.000000
*/

           case 9: metodo0919();break;
/*
            Digite o numero de linhas e colunas: 3 3
Digite um numero real para a matriz [0][0]: 1
Digite um numero real para a matriz [0][1]: 2
Digite um numero real para a matriz [0][2]: 3
Digite um numero real para a matriz [1][0]: 4
Digite um numero real para a matriz [1][1]: 5
Digite um numero real para a matriz [1][2]: 6
Digite um numero real para a matriz [2][0]: 7 
Digite um numero real para a matriz [2][1]: 8
Digite um numero real para a matriz [2][2]: 9

4.000000
7.000000                8.000000

        Digite o numero de linhas e colunas: 3 3
Digite um numero real para a matriz [0][0]: 1
Digite um numero real para a matriz [0][1]: 2
Digite um numero real para a matriz [0][2]: 3
Digite um numero real para a matriz [1][0]: 0
Digite um numero real para a matriz [1][1]: 4
Digite um numero real para a matriz [1][2]: 5
Digite um numero real para a matriz [2][0]: 0
Digite um numero real para a matriz [2][1]: 0
Digite um numero real para a matriz [2][2]: 6



Todos os valores sao igual a zero
*/

           case 10: metodo0920();break;
/*
            Digite o numero de linhas e colunas: 3 3
Digite um numero real para a matriz [0][0]: 1
Digite um numero real para a matriz [0][1]: 2
Digite um numero real para a matriz [0][2]: 3
Digite um numero real para a matriz [1][0]: 4
Digite um numero real para a matriz [1][1]: 5
Digite um numero real para a matriz [1][2]: 6
Digite um numero real para a matriz [2][0]: 7
Digite um numero real para a matriz [2][1]: 8
Digite um numero real para a matriz [2][2]: 9
        2.000000                3.000000
                6.000000

    Digite o numero de linhas e colunas: 3 3
Digite um numero real para a matriz [0][0]: 1
Digite um numero real para a matriz [0][1]: 0
Digite um numero real para a matriz [0][2]: 0
Digite um numero real para a matriz [1][0]: 2
Digite um numero real para a matriz [1][1]: 3
Digite um numero real para a matriz [1][2]: 0
Digite um numero real para a matriz [2][0]: 4
Digite um numero real para a matriz [2][1]: 5
Digite um numero real para a matriz [2][2]: 6



Os valores são iguais a zero
*/

           case 11: metodo09E1();break;
/*
4    3    
2    1    

9    8    7    
6    5    4    
3    2    1    

16   15   14   13    
12   11   10   9    
8    7    6    5    
4    3    2    1    

*/

           case 12: metodo09E2();break;
/*
1   3   
2   4   

1   4   7   
2   5   8   
3   6   9   

1   5   9   13   
2   6   10  14   
3   7   11  15   
4   8   12  16   

*/

           default: printf("Numero invalido");break;
        }
    }
    return (0);
}
