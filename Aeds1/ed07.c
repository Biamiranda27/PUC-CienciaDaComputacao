
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

void metodo0711(FILE *arquivo, int quantidade) {
    int contador = 0;
    int numero = 3;
    while (contador < quantidade) {
        if (numero % 3 == 0 && numero % 2 != 0) {  
            fprintf(arquivo, "%d ", numero);
            contador++;
        }
        numero++;
    }
}
int main() {
    int quantidade;
    FILE *arquivo = fopen("multiplos3impares.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    printf("Digite a quantidade de múltiplos de 3 ímpares que deseja gravar: ");
    scanf("%d", &quantidade);
    metodo0711(arquivo, quantidade);
    fclose(arquivo);
    printf("Valores gravados com sucesso no arquivo 'multiplos3impares.txt'!\n");
    return 0;
}// 3 9 15 21 27


void metodo0712(FILE *arquivo, int quantidade) {
    int numero = 60; 
    int contador = 0;
    while (contador < quantidade && numero >= 36) {
        if (numero % 6 == 0 && numero % 2 == 0) {  
            fprintf(arquivo, "%d ", numero); 
            contador++;
        }
        numero -= 6; 
    }
}
int main() {
    int quantidade;
    FILE *arquivo = fopen("multiplos6pares.txt", "w");\
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    printf("Digite a quantidade de múltiplos de 6 pares que deseja gravar: ");
    scanf("%d", &quantidade);
    metodo0712(arquivo, quantidade);
    fclose(arquivo);
    printf("Valores gravados com sucesso no arquivo 'multiplos6pares.txt'!\n");
    return 0;
}// 60 54 48 42 36


void metodo0713(FILE *arquivo, int quantidade) {
    int valor = 1;
    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d ", valor);
        valor *= 4;  // 
    }
}
int main() {
    int quantidade;
    FILE *arquivo = fopen("sequencia.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    printf("Digite a quantidade de valores da sequência que deseja gravar: ");
    scanf("%d", &quantidade);
    metodo0713(arquivo, quantidade);
    fclose(arquivo);
    printf("Valores gravados com sucesso no arquivo 'sequencia.txt'!\n");
    return 0;
}//1 4 16 64 256


void metodo0714(FILE *arquivo, int quantidade) {
    float valor = 1.0 / 256; 
    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "1/%.0f ", 1 / valor); 
        valor *= 4;  
    }
}
int main() {
    int quantidade;
    FILE *arquivo = fopen("sequencia_decrescente.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    printf("Digite a quantidade de valores da sequência que deseja gravar: ");
    scanf("%d", &quantidade);
    metodo0714(arquivo, quantidade);
    fclose(arquivo);
    printf("Valores gravados com sucesso no arquivo 'sequencia_decrescente.txt'!\n");
    return 0;
}// 1/256 1/64 1/16 1/4 1


void metodo0715(FILE *arquivo, int n, float x) {
    float valor = 1.0; 
    for (int i = 0; i < n; i++) {
        fprintf(arquivo, "%.5f ", valor); 
        valor = 1 / pow(x, (i + 1) * 2); 
    }
}
int main() {
    int n;
    float x;
    FILE *arquivo = fopen("sequencia_potencias.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    printf("Digite a quantidade de termos da sequência (n): ");
    scanf("%d", &n);
    printf("Digite o valor de x: ");
    scanf("%f", &x);
    metodo0715(arquivo, n, x);
    fclose(arquivo);
    printf("Valores gravados com sucesso no arquivo 'sequencia_potencias.txt'!\n");
    return 0;
}//1.00000 0.25000 0.06250 0.01563 0.00391


float funcao0716(int quantidade) {
    FILE *arquivo;
    float valor, soma = 0;
    int count = 0;
    arquivo = fopen("sequencia_potencias.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo 'sequencia_potencias.txt'!\n");
        exit(1);
    }
    while (count < quantidade && fscanf(arquivo, "%f ", &valor) != EOF) {
        soma += valor;
        count++;
    }
    fclose(arquivo);
    return soma; 
}
void metodo0716(int quantidade, float soma) {
    FILE *arquivo;
    arquivo = fopen("RESULTADO06.TXT", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo 'RESULTADO06.TXT'!\n");
        exit(1);
    }
    fprintf(arquivo, "Quantidade: %d, Soma: %.5f ", quantidade, soma);
    fclose(arquivo);
}
int main() {
    int quantidade;
    float soma;
    printf("Digite a quantidade de valores a serem somados: ");
    scanf("%d", &quantidade);
    soma = funcao0716(quantidade);
    metodo0716(quantidade, soma);
    printf("Resultado gravado com sucesso no arquivo 'RESULTADO06.TXT'!\n");
    return 0;
}//Quantidade: 5, Soma: 1.33204


float funcao0717(int quantidade, float x) {
    float soma = 0;
    int expoente;
    for (int i = quantidade; i > 0; i--) {
        expoente = i * 2;
        soma += 1 / pow(x, expoente); 
    }
    return soma;
}
void metodo0717(int quantidade, float soma) {
    FILE *arquivo;
    arquivo = fopen("RESULTADO07.TXT", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo 'RESULTADO07.TXT'!\n");
        return;
    }
    fprintf(arquivo, "Quantidade: %d, Soma: %.5f ", quantidade, soma);
    fclose(arquivo);
}
int main() {
    int n;
    float x, soma;
    printf("Digite a quantidade de termos a serem somados: ");
    scanf("%d", &n);
    printf("Digite o valor de x: ");
    scanf("%f", &x);
    soma = funcao0717(n, x);
    metodo0717(n, soma);
    printf("Resultado gravado com sucesso no arquivo 'RESULTADO07.TXT'!\n");
    return 0;
}//Quantidade: 5, Soma: 0.33302


void metodo0718(int quantidade) {
    FILE *arquivo;
    int fib1 = 0, fib2 = 1, fibAtual, count = 0;
    arquivo = fopen("RESULTADO08.TXT", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo 'RESULTADO08.TXT'!\n");
        return;
    }
    while (count < quantidade) {
        fibAtual = fib1 + fib2;  
        fib1 = fib2;
        fib2 = fibAtual;
        if (fibAtual % 2 == 0) {
            fprintf(arquivo, "%d ", fibAtual);
            count++;  
        }
    }
    fprintf(arquivo, "\n");  
    fclose(arquivo);  
}
int main() {
    int n;
    printf("Digite a quantidade de números pares da série de Fibonacci: ");
    scanf("%d", &n);
    metodo0718(n);
    printf("Resultado gravado com sucesso no arquivo 'RESULTADO08.TXT'!\n");
    return 0;
}// 2 8 34 144 610


int funcao0719(char *cadeia) {
    int contador = 0;
    for (int i = 0; cadeia[i] != '\0'; i++) {
        if (islower(cadeia[i])) {  
            contador++;
        }
    }
    return contador;
}
void metodo0719() {
    FILE *entrada, *saida;
    char cadeia[100];
    int minuscula;
    entrada = fopen("entrada.txt", "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        return;
    }
    saida = fopen("RESULTADO09.TXT", "a");
    if (saida == NULL) {
        printf("Erro ao abrir o arquivo 'RESULTADO09.TXT'!\n");
        fclose(entrada);
        return;
    }
    while (fgets(cadeia, sizeof(cadeia), entrada) != NULL) {
        if (cadeia[strlen(cadeia) - 1] == '\n') {
            cadeia[strlen(cadeia) - 1] = '\0';
        }
        minuscula = funcao0719(cadeia);
        fprintf(saida, "Cadeia: %s - Minúsculas: %d\n", cadeia, minuscula);
    }
    fclose(entrada);
    fclose(saida);
}
int main() {
    metodo0719();
    printf("Resultados gravados no arquivo 'RESULTADO09.TXT'!\n");
    return 0;
}// Cadeia: PaReDe de TiJoLoS AmaRElOs - Minúsculas: 9


int funcao0720(char *cadeia) {
    int count = 0;
    for (int i = 0; cadeia[i] != '\0'; i++) {
        if (isdigit(cadeia[i]) && cadeia[i] <= '4') {  
            count++;
        }
    }
    return count;
}
void metodo0720() {
    FILE *entrada, *saida;
    char cadeia[100];
    int quantidade;
    entrada = fopen("entrada.txt", "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        return;
    }
    saida = fopen("RESULTADO10.TXT", "a");
    if (saida == NULL) {
        printf("Erro ao abrir o arquivo 'RESULTADO10.TXT'!\n");
        fclose(entrada);
        return;
    }
    while (fgets(cadeia, sizeof(cadeia), entrada) != NULL) {
        if (cadeia[strlen(cadeia) - 1] == '\n') {
            cadeia[strlen(cadeia) - 1] = '\0';
        }
        quantidade = funcao0720(cadeia);
        fprintf(saida, "Cadeia: %s - Dígitos <= 4: %d\n", cadeia, quantidade);
    }
    fclose(entrada);
    fclose(saida);
}
int main() {
    metodo0720();
    printf("Resultados gravados no arquivo 'RESULTADO10.TXT'!\n");
    return 0;
}// Cadeia: P4R3D3 de T1J0L05 4maR3105 - Dígitos <= 4: 6


void metodo07E1(int numero) {
    FILE *arquivo;
    arquivo = fopen("RESULTADO_DIVISORES.TXT", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo 'RESULTADO_DIVISORES.TXT'!\n");
        return;
    }
    fprintf(arquivo, "Divisores pares de %d em ordem decrescente: ", numero);
    for (int i = numero; i >= 1; i--) {
        if (numero % i == 0 && i % 2 == 0) {  
            fprintf(arquivo, "%d ", i);  
        }
    }
    fprintf(arquivo, "\n"); 
    fclose(arquivo);  
}
int main() {
    int n;
    printf("Digite um número inteiro: ");
    scanf("%d", &n);
    metodo07E1(n);
    printf("Divisores pares gravados no arquivo 'RESULTADO_DIVISORES.TXT'!\n");
    return 0;
}// Divisores pares de 36 em ordem decrescente: 36 18 12 6 4 2 


int funcao07E2(char *arquivo) {
    FILE *arquivo;
    char palavra[100];
    int count = 0;
    arquivo = fopen("arquivo.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo '%s'!\n", arquivo);
        return -1;
    }
    while (fgets(palavra, sizeof(palavra), arquivo) != NULL) {
        palavra[strcspn(palavra, "\n")] = 0;
        if (tolower(palavra[0]) == 'd') {
            count++;
        }
    }
    fclose(arquivo);
    return count;
}
int main() {
    char arquivo[100];
    int total;
    printf("Digite o nome do arquivo (com extensão): ");
    scanf("%s", arquivo);
    total = funcao07E2(arquivo);
    if (total >= 0) {
        printf("Total de palavras que começam com 'd' ou 'D': %d\n", total);
    }
    return 0;
}/*
cachorro, Dado, pessego, dia
Total de palavras que começam com 'd' ou 'D': 2
*/
