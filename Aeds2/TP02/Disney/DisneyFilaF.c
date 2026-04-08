#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_LINE 1000
#define MAX_FIELD 100
#define MAX_LIST 20
#define TAM_FILA 5

typedef struct {
    char show_id[MAX_FIELD];
    char type[MAX_FIELD];
    char title[MAX_FIELD];
    char director[MAX_FIELD];
    char cast[MAX_LIST][MAX_FIELD];
    int cast_size;
    char country[MAX_FIELD];
    char date_added[MAX_FIELD];
    int release_year;
    char rating[MAX_FIELD];
    char duration[MAX_FIELD];
    char listed_in[MAX_LIST][MAX_FIELD];
    int listed_in_size;
} Show;

typedef struct Celula {
    Show show;
    struct Celula* prox;
} Celula;

typedef struct {
    Celula* inicio;
    Celula* fim;
    int tamanho;
} Fila;

void inicializar_fila(Fila* f) {
    f->inicio = f->fim = NULL;
    f->tamanho = 0;
}

bool inserir_fila(Fila* f, Show s) {
    Celula* nova = malloc(sizeof(Celula));
    if (!nova) return false;

    nova->show = s;
    nova->prox = NULL;

    if (f->fim) f->fim->prox = nova;
    else f->inicio = nova;

    f->fim = nova;
    f->tamanho++;
    return true;
}

bool remover_fila(Fila* f, Show* removido) {
    if (f->tamanho == 0) return false;

    Celula* tmp = f->inicio;
    *removido = tmp->show;

    f->inicio = tmp->prox;
    if (!f->inicio) f->fim = NULL;

    free(tmp);
    f->tamanho--;
    return true;
}

int media_release_year(Fila* f) {
    if (f->tamanho == 0) return 0;

    int soma = 0;
    int count = 0;
    for (Celula* c = f->inicio; c != NULL; c = c->prox) {
        soma += c->show.release_year;
        count++;
    }
    return (int)round((float)soma / count);
}

void imprimir_show(Show s) {
    printf("=> %s ## %s ## %s ## %s ## [", s.show_id, s.title, s.type, s.director);
    for (int i = 0; i < s.cast_size; i++) {
        printf("%s", s.cast[i]);
        if (i < s.cast_size - 1) printf(", ");
    }
    printf("] ## %s ## %s ## %d ## %s ## %s ## [", s.country, s.date_added, s.release_year, s.rating, s.duration);
    for (int i = 0; i < s.listed_in_size; i++) {
        printf("%s", s.listed_in[i]);
        if (i < s.listed_in_size - 1) printf(", ");
    }
    printf("] ##\n");
}

void imprimir_fila(Fila* f) {
    int i = 0;
    for (Celula* c = f->inicio; c != NULL; c = c->prox, i++) {
        printf("[%d] ", i);
        imprimir_show(c->show);
    }
}

void ler_linha_csv(char* linha, Show* s) {
    char* token;
    char* ptr = linha;
    char campo[12][MAX_LINE] = {{0}};
    int idx = 0, campo_idx = 0;
    bool aspas = false;

    *s = (Show){0};
    strcpy(s->show_id, "NaN");
    strcpy(s->type, "NaN");
    strcpy(s->title, "NaN");
    strcpy(s->director, "NaN");
    strcpy(s->country, "NaN");
    strcpy(s->date_added, "March 1, 1900");
    strcpy(s->rating, "NaN");
    strcpy(s->duration, "NaN");

    while (*ptr) {
        if (*ptr == '"') {
            aspas = !aspas;
        } else if (*ptr == ',' && !aspas) {
            campo[campo_idx][idx] = '\0';
            campo_idx++;
            idx = 0;
        } else {
            campo[campo_idx][idx++] = *ptr;
        }
        ptr++;
    }
    campo[campo_idx][idx] = '\0';

    if (strlen(campo[0])) strcpy(s->show_id, campo[0]);
    if (strlen(campo[1])) strcpy(s->type, campo[1]);
    if (strlen(campo[2])) strcpy(s->title, campo[2]);
    if (strlen(campo[3])) strcpy(s->director, campo[3]);

    s->cast_size = 0;
    if (strlen(campo[4])) {
        token = strtok(campo[4], ",");
        while (token && s->cast_size < MAX_LIST) {
            while (*token == ' ') token++;
            strcpy(s->cast[s->cast_size++], token);
            token = strtok(NULL, ",");
        }
    }

    if (strlen(campo[5])) strcpy(s->country, campo[5]);
    if (strlen(campo[6])) strcpy(s->date_added, campo[6]);
    if (strlen(campo[7])) s->release_year = atoi(campo[7]);
    if (strlen(campo[8])) strcpy(s->rating, campo[8]);
    if (strlen(campo[9])) strcpy(s->duration, campo[9]);

    s->listed_in_size = 0;
    if (strlen(campo[10])) {
        token = strtok(campo[10], ",");
        while (token && s->listed_in_size < MAX_LIST) {
            while (*token == ' ') token++;
            strcpy(s->listed_in[s->listed_in_size++], token);
            token = strtok(NULL, ",");
        }
    }
}

char* buscar_linha_por_id(const char* id, FILE* arquivo) {
    static char linha[MAX_LINE];
    rewind(arquivo);
    fgets(linha, MAX_LINE, arquivo); // cabeçalho

    while (fgets(linha, MAX_LINE, arquivo)) {
        char id_atual[MAX_FIELD];
        sscanf(linha, "%[^,]", id_atual);
        if (strcmp(id, id_atual) == 0) {
            return linha;
        }
    }
    return NULL;
}

int main() {
    char entrada[MAX_FIELD];
    char* linhas[1000];
    int total_ids = 0;
    Fila fila;
    inicializar_fila(&fila);

    while (scanf(" %[^\n]", entrada) && strcmp(entrada, "FIM") != 0) {
        linhas[total_ids++] = strdup(entrada);
    }

    FILE* arquivo = fopen("/tmp/disneyplus.csv", "r");
    if (!arquivo) {
        printf("Arquivo não encontrado\n");
        return 1;
    }

    for (int i = 0; i < total_ids; i++) {
        char* linha = buscar_linha_por_id(linhas[i], arquivo);
        if (linha) {
            Show s;
            ler_linha_csv(linha, &s);
            if (fila.tamanho == TAM_FILA) {
                Show removido;
                remover_fila(&fila, &removido);
                printf("(R) %s\n", removido.title);
            }
            inserir_fila(&fila, s);
            printf("[Media] %d\n", media_release_year(&fila));
        }
        free(linhas[i]);
    }

    int n;
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        if (entrada[0] == 'I') {
            char id[MAX_FIELD];
            sscanf(entrada, "I %s", id);
            char* linha = buscar_linha_por_id(id, arquivo);
            if (linha) {
                Show s;
                ler_linha_csv(linha, &s);
                if (fila.tamanho == TAM_FILA) {
                    Show removido;
                    remover_fila(&fila, &removido);
                    printf("(R) %s\n", removido.title);
                }
                inserir_fila(&fila, s);
                printf("[Media] %d\n", media_release_year(&fila));
            }
        }
    }

    imprimir_fila(&fila);
    fclose(arquivo);
    return 0;
}
