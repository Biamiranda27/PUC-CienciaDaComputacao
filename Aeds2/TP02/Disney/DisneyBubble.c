#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_SHOWS 1500
#define MAX_STR 256

typedef struct {
    char show_id[MAX_STR];
    char type[MAX_STR];
    char title[MAX_STR];
    char director[MAX_STR];
    char cast[MAX_STR];
    char country[MAX_STR];
    char date_added[MAX_STR];
    int release_year;
    char rating[MAX_STR];
    char duration[MAX_STR];
    char listed_in[MAX_STR];
} Show;

void lerShow(Show *s, char *linha) {
    char *campos[12];
    int campoIndex = 0, entreAspas = 0, bufIndex = 0;
    char buffer[MAX_STR], *ptr = linha;

    while (*ptr != '\0' && campoIndex < 12) {
        if (*ptr == '"') {
            entreAspas = !entreAspas;
        } else if (*ptr == ',' && !entreAspas) {
            buffer[bufIndex] = '\0';
            campos[campoIndex++] = strdup(buffer);
            bufIndex = 0;
        } else {
            buffer[bufIndex++] = *ptr;
        }
        ptr++;
    }
    buffer[bufIndex] = '\0';
    campos[campoIndex] = strdup(buffer);

    strcpy(s->show_id, strlen(campos[0]) ? campos[0] : "NaN");
    strcpy(s->type, strlen(campos[1]) ? campos[1] : "NaN");
    strcpy(s->title, strlen(campos[2]) ? campos[2] : "NaN");
    strcpy(s->director, strlen(campos[3]) ? campos[3] : "NaN");
    strcpy(s->cast, strlen(campos[4]) ? campos[4] : "NaN");
    strcpy(s->country, strlen(campos[5]) ? campos[5] : "NaN");
    strcpy(s->date_added, strlen(campos[6]) ? campos[6] : "NaN");
    s->release_year = strlen(campos[7]) ? atoi(campos[7]) : -1;
    strcpy(s->rating, strlen(campos[8]) ? campos[8] : "NaN");
    strcpy(s->duration, strlen(campos[9]) ? campos[9] : "NaN");
    strcpy(s->listed_in, strlen(campos[10]) ? campos[10] : "NaN");

    for (int j = 0; j <= campoIndex; j++) free(campos[j]);
}

void ordenarCast(char *cast) {
    if (strcmp(cast, "NaN") == 0) return;

    char nomes[MAX_SHOWS][MAX_STR];
    int qtd = 0;

    char *token = strtok(cast, ",");
    while (token != NULL && qtd < MAX_SHOWS) {
        while (*token == ' ') token++;
        strncpy(nomes[qtd++], token, MAX_STR);
        token = strtok(NULL, ",");
    }

    for (int i = 0; i < qtd - 1; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (strcmp(nomes[i], nomes[j]) > 0) {
                char temp[MAX_STR];
                strcpy(temp, nomes[i]);
                strcpy(nomes[i], nomes[j]);
                strcpy(nomes[j], temp);
            }
        }
    }

    cast[0] = '\0';
    for (int i = 0; i < qtd; i++) {
        strcat(cast, nomes[i]);
        if (i < qtd - 1) strcat(cast, ", ");
    }
}

void imprimirShow(Show *s) {
    char castOrdenado[MAX_STR];
    strcpy(castOrdenado, s->cast);
    ordenarCast(castOrdenado);

    printf("=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##\n",
           s->show_id, s->title, s->type, s->director, castOrdenado, s->country,
           s->date_added, s->release_year, s->rating, s->duration, s->listed_in);
}

time_t parseDate(const char *data) {
    if (strcmp(data, "NaN") == 0) return 0;

    struct tm tm = {0};
    setlocale(LC_TIME, "C");
    if (strptime(data, "%B %d, %Y", &tm) == NULL) {
        return 0;
    }
    return mktime(&tm);
}

int compararShows(const Show *a, const Show *b) {
    time_t da = parseDate(a->date_added);
    time_t db = parseDate(b->date_added);
    if (da != db) return (da < db) ? -1 : 1;
    return strcasecmp(a->title, b->title);
}

void bubbleSort(Show arr[], int n, int *comparacoes, int *movimentacoes) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (compararShows(&arr[j], &arr[j + 1]) > 0) {
                Show temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                (*movimentacoes) += 3;
            }
        }
    }
}

int pesquisaBinaria(Show arr[], int n, char *titulo, int *comparacoes) {
    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        (*comparacoes)++;
        int cmp = strcmp(arr[meio].title, titulo);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            esq = meio + 1;
        else
            dir = meio - 1;
    }
    return -1;
}

int main() {
    FILE *arquivo = fopen("/tmp/disneyplus.csv", "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    Show listaOrdenada[MAX_SHOWS];
    int quantidadeTotal = 0;
    char linhaCSV[4096];

    fgets(linhaCSV, sizeof(linhaCSV), arquivo);
    while (fgets(linhaCSV, sizeof(linhaCSV), arquivo) && quantidadeTotal < MAX_SHOWS) {
        linhaCSV[strcspn(linhaCSV, "\n")] = 0;
        lerShow(&listaOrdenada[quantidadeTotal++], linhaCSV);
    }
    fclose(arquivo);

    Show listaFinal[MAX_SHOWS];
    int quantidadeFinal = 0;
    char entradaUsuario[MAX_STR];

    while (fgets(entradaUsuario, sizeof(entradaUsuario), stdin)) {
        entradaUsuario[strcspn(entradaUsuario, "\n")] = 0;
        if (strcmp(entradaUsuario, "FIM") == 0) break;
        for (int i = 0; i < quantidadeTotal; i++) {
            if (strcmp(listaOrdenada[i].show_id, entradaUsuario) == 0) {
                listaFinal[quantidadeFinal++] = listaOrdenada[i];
                break;
            }
        }
    }

    int totalComparacoes = 0, totalMovimentacoes = 0;
    clock_t inicio = clock();
    bubbleSort(listaFinal, quantidadeFinal, &totalComparacoes, &totalMovimentacoes);
    clock_t fim = clock();
    double tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;

    for (int i = 0; i < quantidadeFinal; i++) {
        imprimirShow(&listaFinal[i]);
    }

    FILE *arquivoLog = fopen("845860_bubblesort.txt", "w");
    if (arquivoLog) {
        fprintf(arquivoLog, "845860\t%d\t%d\t%.2lf\n", totalComparacoes, totalMovimentacoes, tempoExecucao);
        fclose(arquivoLog);
    }

    if (fgets(entradaUsuario, sizeof(entradaUsuario), stdin)) {
        entradaUsuario[strcspn(entradaUsuario, "\n")] = 0;
        int comparacoesBin = 0;
        pesquisaBinaria(listaFinal, quantidadeFinal, entradaUsuario, &comparacoesBin);
    }

    return 0;
}
