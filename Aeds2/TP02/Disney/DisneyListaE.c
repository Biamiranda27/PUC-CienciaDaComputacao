#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 1000
#define MAX_FIELD 100
#define MAX_LIST 20

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

typedef struct No {
    Show dado;
    struct No* prox;
} No;

typedef struct {
    No* topo;
    int tamanho;
} Pilha;

void inicializar_pilha(Pilha* p) {
    p->topo = NULL;
    p->tamanho = 0;
}

bool inserir_pilha(Pilha* p, Show s) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) return false;
    novo->dado = s;
    novo->prox = p->topo;
    p->topo = novo;
    p->tamanho++;
    return true;
}

bool remover_pilha(Pilha* p, Show* removido) {
    if (p->topo == NULL) return false;
    No* temp = p->topo;
    *removido = temp->dado;
    p->topo = temp->prox;
    free(temp);
    p->tamanho--;
    return true;
}

void liberar_pilha(Pilha* p) {
    Show temp;
    while (remover_pilha(p, &temp));
}

void imprimir_pilha_com_indice(Pilha* p) {
    No* atual = p->topo;
    int idx = p->tamanho - 1;
    while (atual != NULL) {
        Show s = atual->dado;
        printf("[%d] => %s ## %s ## %s ## %s ## [", idx, s.show_id, s.title, s.type, s.director);
        for (int j = 0; j < s.cast_size; j++) {
            printf("%s", s.cast[j]);
            if (j < s.cast_size - 1) printf(", ");
        }
        printf("] ## %s ## %s ## %d ## %s ## %s ## [", s.country, s.date_added, s.release_year, s.rating, s.duration);
        for (int j = 0; j < s.listed_in_size; j++) {
            printf("%s", s.listed_in[j]);
            if (j < s.listed_in_size - 1) printf(", ");
        }
        printf("] ##\n");
        atual = atual->prox;
        idx--;
    }
}

Show criar_show_vazio() {
    Show s;
    strcpy(s.show_id, "NaN");
    strcpy(s.type, "NaN");
    strcpy(s.title, "NaN");
    strcpy(s.director, "NaN");
    s.cast_size = 0;
    strcpy(s.country, "NaN");
    strcpy(s.date_added, "March 1, 1900");
    s.release_year = 0;
    strcpy(s.rating, "NaN");
    strcpy(s.duration, "NaN");
    s.listed_in_size = 0;
    return s;
}

Show ler_show(char* linha) {
    Show s = criar_show_vazio();
    char campo[12][MAX_LINE] = {{0}};
    int campo_idx = 0, idx = 0;
    bool aspas = false;
    for (char* ptr = linha; *ptr; ptr++) {
        if (*ptr == '"') {
            aspas = !aspas;
        } else if (*ptr == ',' && !aspas) {
            campo[campo_idx][idx] = '\0';
            campo_idx++; idx = 0;
        } else {
            campo[campo_idx][idx++] = *ptr;
        }
    }
    campo[campo_idx][idx] = '\0';

    strcpy(s.show_id, strlen(campo[0]) ? campo[0] : "NaN");
    strcpy(s.type, strlen(campo[1]) ? campo[1] : "NaN");
    strcpy(s.title, strlen(campo[2]) ? campo[2] : "NaN");
    strcpy(s.director, strlen(campo[3]) ? campo[3] : "NaN");

    s.cast_size = 0;
    if (strlen(campo[4])) {
        char* token = strtok(campo[4], ",");
        while (token && s.cast_size < MAX_LIST) {
            while (*token == ' ') token++;
            strncpy(s.cast[s.cast_size++], token, MAX_FIELD);
            token = strtok(NULL, ",");
        }
    }

    strcpy(s.country, strlen(campo[5]) ? campo[5] : "NaN");
    strcpy(s.date_added, strlen(campo[6]) ? campo[6] : "March 1, 1900");
    s.release_year = strlen(campo[7]) ? atoi(campo[7]) : 0;
    strcpy(s.rating, strlen(campo[8]) ? campo[8] : "NaN");
    strcpy(s.duration, strlen(campo[9]) ? campo[9] : "NaN");

    s.listed_in_size = 0;
    if (strlen(campo[10])) {
        char* token = strtok(campo[10], ",");
        while (token && s.listed_in_size < MAX_LIST) {
            while (*token == ' ') token++;
            strncpy(s.listed_in[s.listed_in_size++], token, MAX_FIELD);
            token = strtok(NULL, ",");
        }
    }

    return s;
}

char* buscar_linha_por_id(const char* id, FILE* arquivo) {
    static char linha[MAX_LINE];
    rewind(arquivo);
    fgets(linha, MAX_LINE, arquivo); // pular cabeçalho

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
    Pilha pilha;
    inicializar_pilha(&pilha);

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
            Show s = ler_show(linha);
            inserir_pilha(&pilha, s);
        }
        free(linhas[i]);
    }

    int n;
    scanf("%d", &n);
    getchar(); // consumir newline

    for (int i = 0; i < n; i++) {
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        if (entrada[0] == 'I') {
            char id[MAX_FIELD];
            sscanf(entrada, "I %s", id);
            char* linha = buscar_linha_por_id(id, arquivo);
            if (linha) {
                Show s = ler_show(linha);
                inserir_pilha(&pilha, s);
            }
        } else if (entrada[0] == 'R') {
            Show removido;
            if (remover_pilha(&pilha, &removido)) {
                printf("(R) %s\n", removido.title);
            }
        }
    }

    imprimir_pilha_com_indice(&pilha);
    liberar_pilha(&pilha);
    fclose(arquivo);
    return 0;
}
