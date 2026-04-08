#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SHOWS 1000
#define MAX_LINE 5000

typedef struct {
    char show_id[20];
    char type[50];
    char title[200];
    char director[100];
    char cast[500];
    char country[100];
    char date_added[50];
    int release_year;
    char rating[10];
    char duration[20];
    char listed_in[200];
} Show;

int comparacoes = 0;
int movimentacoes = 0;

void limparCampo(char *str) {
    if (str[0] == '"') {
        memmove(str, str + 1, strlen(str));
        char *aspas = strchr(str, '"');
        if (aspas) *aspas = '\0';
    }
    while (str[0] == ' ') memmove(str, str + 1, strlen(str));
}

void normalizar(char *dest, const char *src) {
    strcpy(dest, src);
    for (int i = 0; dest[i]; i++) {
        if (dest[i] >= 'A' && dest[i] <= 'Z') {
            dest[i] = dest[i] + 32;
        }
    }
}

Show lerShow(char *linha) {
    Show s;
    char *token;
    int campo = 0;

    token = strtok(linha, ",");
    while (token != NULL && campo < 11) {
        limparCampo(token);
        switch (campo) {
            case 0: strcpy(s.show_id, token); break;
            case 1: strcpy(s.type, token); break;
            case 2: strcpy(s.title, token); break;
            case 3: strcpy(s.director, token); break;
            case 4: strcpy(s.cast, token); break;
            case 5: strcpy(s.country, token); break;
            case 6: strcpy(s.date_added, token); break;
            case 7: s.release_year = atoi(token); break;
            case 8: strcpy(s.rating, token); break;
            case 9: strcpy(s.duration, token); break;
            case 10: strcpy(s.listed_in, token); break;
        }
        token = strtok(NULL, ",");
        campo++;
    }

    return s;
}

void imprimirShow(Show s) {
    printf("=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##\n",
           s.show_id, s.title, s.type, s.director, s.cast, s.country,
           s.date_added[0] ? s.date_added : "NaN", s.release_year, s.rating,
           s.duration, s.listed_in);
}

void insertionSort(Show arr[], int n) {
    for (int i = 1; i < n; i++) {
        Show chave = arr[i];
        int j = i - 1;

        char chaveTipo[100], chaveTitulo[200];
        normalizar(chaveTipo, chave.type);
        normalizar(chaveTitulo, chave.title);

        comparacoes++;
        while (j >= 0) {
            char tipoAtual[100], tituloAtual[200];
            normalizar(tipoAtual, arr[j].type);
            normalizar(tituloAtual, arr[j].title);

            int cmpTipo = strcmp(tipoAtual, chaveTipo);
            int cmpTitulo = strcmp(tituloAtual, chaveTitulo);

            comparacoes++;
            if (cmpTipo > 0 || (cmpTipo == 0 && cmpTitulo > 0)) {
                arr[j + 1] = arr[j];
                movimentacoes++;
                j--;
            } else {
                break;
            }
        }

        arr[j + 1] = chave;
        movimentacoes++;
    }
}

int compararTitulos(const void *a, const void *b) {
    Show *s1 = (Show *)a;
    Show *s2 = (Show *)b;
    return strcmp(s1->title, s2->title);
}

int main() {
    Show todos[MAX_SHOWS];
    Show selecionados[10];
    char linhaOriginal[MAX_LINE];
    int total = 0;

    FILE *fp = fopen("/tmp/disneyplus.csv", "r");
    if (!fp) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fgets(linhaOriginal, MAX_LINE, fp); // cabeçalho

    while (fgets(linhaOriginal, MAX_LINE, fp) && total < MAX_SHOWS) {
        char linhaCopia[MAX_LINE];
        strcpy(linhaCopia, linhaOriginal);
        todos[total++] = lerShow(linhaCopia);
    }
    fclose(fp);

    qsort(todos, total, sizeof(Show), compararTitulos);

    for (int i = 0; i < 10 && i < total; i++) {
        selecionados[i] = todos[i];
    }

    clock_t inicio = clock();
    insertionSort(selecionados, 10);
    clock_t fim = clock();

    for (int i = 0; i < 10; i++) {
        imprimirShow(selecionados[i]);
    }

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;

    FILE *log = fopen("845860_insercao.txt", "w");
    fprintf(log, "845860\t%d\t%d\t%.2lf\n", comparacoes, movimentacoes, tempo);
    fclose(log);

    return 0;
}
