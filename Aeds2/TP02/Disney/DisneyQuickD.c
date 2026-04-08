#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_STR 256

typedef struct {
    char id[MAX_STR];
    char tipo[MAX_STR];
    char titulo[MAX_STR];
    char diretor[MAX_STR];
    char elenco[MAX_STR];
    char pais[MAX_STR];
    char data_adicionada[MAX_STR];
    int ano_lancamento;
    char classificacao[MAX_STR];
    char duracao[MAX_STR];
    char categorias[MAX_STR];
} Show;

typedef struct No {
    Show show;
    struct No *ant;
    struct No *prox;
} No;

No* novoNo(Show s) {
    No* no = (No*)malloc(sizeof(No));
    no->show = s;
    no->ant = no->prox = NULL;
    return no;
}

void inserirFim(No **inicio, No **fim, Show s) {
    No *novo = novoNo(s);
    if (*inicio == NULL) {
        *inicio = *fim = novo;
    } else {
        (*fim)->prox = novo;
        novo->ant = *fim;
        *fim = novo;
    }
}

void imprimirShow(Show *show);
void ordenarElenco(char *elenco);
time_t parseData(const char *data);
int compararShows(const Show *a, const Show *b);

void lerShow(Show *show, char *linha) {
    char *campos[12];
    int campoIndex = 0, entreAspas = 0;
    char *ptr = linha;
    char buffer[MAX_STR];
    int bufIndex = 0;

    while (*ptr && campoIndex < 12) {
        if (*ptr == '"') entreAspas = !entreAspas;
        else if (*ptr == ',' && !entreAspas) {
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

    strcpy(show->id, strlen(campos[0]) ? campos[0] : "NaN");
    strcpy(show->tipo, strlen(campos[1]) ? campos[1] : "NaN");
    strcpy(show->titulo, strlen(campos[2]) ? campos[2] : "NaN");
    strcpy(show->diretor, strlen(campos[3]) ? campos[3] : "NaN");
    strcpy(show->elenco, strlen(campos[4]) ? campos[4] : "NaN");
    strcpy(show->pais, strlen(campos[5]) ? campos[5] : "NaN");
    strcpy(show->data_adicionada, strlen(campos[6]) ? campos[6] : "NaN");
    show->ano_lancamento = strlen(campos[7]) ? atoi(campos[7]) : -1;
    strcpy(show->classificacao, strlen(campos[8]) ? campos[8] : "NaN");
    strcpy(show->duracao, strlen(campos[9]) ? campos[9] : "NaN");
    strcpy(show->categorias, strlen(campos[10]) ? campos[10] : "NaN");

    for (int j = 0; j <= campoIndex; j++) free(campos[j]);
}

void ordenarElenco(char *elenco) {
    if (strcmp(elenco, "NaN") == 0) return;
    char nomes[50][MAX_STR];
    int qtd = 0;

    char *token = strtok(elenco, ",");
    while (token && qtd < 50) {
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

    elenco[0] = '\0';
    for (int i = 0; i < qtd; i++) {
        strcat(elenco, nomes[i]);
        if (i < qtd - 1) strcat(elenco, ", ");
    }
}

void imprimirShow(Show *show) {
    char elencoOrdenado[MAX_STR];
    strcpy(elencoOrdenado, show->elenco);
    ordenarElenco(elencoOrdenado);

    printf("=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##\n",
           show->id, show->titulo, show->tipo, show->diretor, elencoOrdenado, show->pais,
           show->data_adicionada, show->ano_lancamento, show->classificacao, show->duracao, show->categorias);
}

time_t parseData(const char *data) {
    if (strcmp(data, "NaN") == 0) return 0;
    struct tm tm = {0};
    setlocale(LC_TIME, "C");
    if (strptime(data, "%B %d, %Y", &tm) == NULL) return 0;
    return mktime(&tm);
}

int compararShows(const Show *a, const Show *b) {
    time_t da = parseData(a->data_adicionada);
    time_t db = parseData(b->data_adicionada);
    if (da != db) return (da < db) ? -1 : 1;
    return strcasecmp(a->titulo, b->titulo);
}

No* ultimaNo(No *no) {
    while (no && no->prox) no = no->prox;
    return no;
}

void trocarDados(Show *a, Show *b) {
    Show tmp = *a;
    *a = *b;
    *b = tmp;
}

No* particao(No *low, No *high, int *comp, int *mov) {
    Show pivo = high->show;
    No *i = low->ant;

    for (No *j = low; j != high; j = j->prox) {
        (*comp)++;
        if (compararShows(&j->show, &pivo) <= 0) {
            i = (i == NULL) ? low : i->prox;
            trocarDados(&i->show, &j->show);
            (*mov) += 3;
        }
    }
    i = (i == NULL) ? low : i->prox;
    trocarDados(&i->show, &high->show);
    (*mov) += 3;
    return i;
}

void quickSortLista(No *low, No *high, int *comp, int *mov) {
    if (high && low != high && low != high->prox) {
        No *pi = particao(low, high, comp, mov);
        quickSortLista(low, pi->ant, comp, mov);
        quickSortLista(pi->prox, high, comp, mov);
    }
}

int main() {
    FILE *arquivo = fopen("/tmp/disneyplus.csv", "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    Show todos[1500];
    int total = 0;
    char linha[4096];

    fgets(linha, sizeof(linha), arquivo);
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0;
        lerShow(&todos[total++], linha);
    }
    fclose(arquivo);

    No *inicio = NULL, *fim = NULL;
    char entrada[MAX_STR];
    while (fgets(entrada, sizeof(entrada), stdin)) {
        entrada[strcspn(entrada, "\n")] = 0;
        if (strcmp(entrada, "FIM") == 0) break;

        for (int i = 0; i < total; i++) {
            if (strcmp(todos[i].id, entrada) == 0) {
                inserirFim(&inicio, &fim, todos[i]);
                break;
            }
        }
    }

    int comparacoes = 0, movimentacoes = 0;
    clock_t ini = clock();

    quickSortLista(inicio, fim, &comparacoes, &movimentacoes);

    clock_t fim_exec = clock();
    double tempo = (double)(fim_exec - ini) / CLOCKS_PER_SEC * 1000.0;

    for (No *atual = inicio; atual != NULL; atual = atual->prox)
        imprimirShow(&atual->show);

    FILE *log = fopen("845860_quicksort2.txt", "w");
    if (log) {
        fprintf(log, "845860\t%d\t%d\t%.2lf\n", comparacoes, movimentacoes, tempo);
        fclose(log);
    }

    return 0;
}
