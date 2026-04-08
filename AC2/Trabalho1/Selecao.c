#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void swap(int *array, int menor, int i){
    int tmp = array[menor];
    array[menor] = array[i];
    array[i] = tmp;
}

void selecao(int *array, int n){
    for(int i = 0; i < (n-1); i++){
        int menor = i;
        for(int j = (i+1); j < n; j++){
            if(array[j] < array[menor]){
                menor = j;
            }
        }
        swap(array, menor, i);
    }
}

int main(){
    FILE *arquivo;
    arquivo = fopen("dados.txt", "r");
    if(arquivo == NULL){
        printf("erro na abertura do arquivo");
        return 1;
    }

    int n;

    if(fscanf(arquivo, "%d", &n) != 1){
        printf("erro na leitura do tamanho do array");
        fclose(arquivo);
        return 1;
    }

    int array[n];

   for(int i = 0; i < n; i++){
    if(fscanf(arquivo, "%d", &array[i]) != 1){
        printf("erro ao ler os dados do array");
        fclose(arquivo);
        return 1;
    }
   }
   fclose(arquivo);

   printf("array original: ");
    for(int i = 0; i < n; i++){
        printf("%d\t",array[i]);
    }
    printf("\n");

    clock_t inicio, fim;
    double tempoExecusao;
    inicio = clock();

    selecao(array, n);

    fim = clock();

    printf("array ordenado: ");
    for(int i = 0; i < n; i++){
        printf("%d\t", array[i]);
    }
    printf("\n");

    tempoExecusao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("tempo gasto: %f segundos\n", tempoExecusao);
    
    return 0;
}
