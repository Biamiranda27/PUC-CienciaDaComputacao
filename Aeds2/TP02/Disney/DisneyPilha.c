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
    Show elemento;
    struct No* proximo;
} No;

// Função para inicializar um show vazio
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

// Função para ler uma linha CSV e preencher a struct Show
Show ler_show(char* linha) {
    Show s = criar_show_vazio();
    char* token;
    char* ptr = linha;
    char campo[12][MAX_LINE] = {{0}};
    int i = 0;
    bool aspas = false;
    int idx = 0;
    int campo_idx = 0;

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

    strcpy(s.show_id, strlen(campo[0]) ? campo[0] : "NaN");
    strcpy(s.type, strlen(campo[1]) ? campo[1] : "NaN");
    strcpy(s.title, strlen(campo[2]) ? campo[2] : "NaN");
    strcpy(s.director, strlen(campo[3]) ? campo[3] : "NaN");

    // Cast
    s.cast_size = 0;
    if (strlen(campo[4])) {
        token = strtok(campo[4], ",");
        while (token != NULL && s.cast_size < MAX_LIST) {
            while (*token == ' ') token++;
            strcpy(s.cast[s.cast_size++], token);
            token = strtok(NULL, ",");
        }
    }

    strcpy(s.country, strlen(campo[5]) ? campo[5] : "NaN");
    strcpy(s.date_added, strlen(campo[6]) ? campo[6] : "March 1, 1900");
    s.release_year = atoi(campo[7]);
    strcpy(s.rating, strlen(campo[8]) ? campo[8] : "NaN");
    strcpy(s.duration, strlen(campo[9]) ? campo[9] : "NaN");

    // Listed_in
    s.listed_in_size = 0;
    if (strlen(campo[10])) {
        token = strtok(campo[10], ",");
        while (token != NULL && s.listed_in_size < MAX_LIST) {
            while (*token == ' ') token++;
            strcpy(s.listed_in[s.listed_in_size++], token);
            token = strtok(NULL, ",");
        }
    }

    return s;
}

// Função para imprimir um Show
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

// Inserção na pilha
No* inserir_pilha(No* topo, Show s) {
    No* novo = (No*)malloc(sizeof(No));
    novo->elemento = s;
    novo->proximo = topo;
    return novo;
}

// Remoção da pilha
No* remover_pilha(No* topo, Show* removido) {
    if (topo == NULL) return NULL;
    *removido = topo->elemento;
    No* temp = topo;
    topo = topo->proximo;
    free(temp);
    return topo;
}

int tamanho_pilha(No* topo) {
    int tamanho = 0;
    while (topo != NULL) {
        tamanho++;
        topo = topo->proximo;
    }
    return tamanho;
}

void imprimir_pilha_com_indice(No* topo, int indice) {
    if (topo != NULL) {
        printf("[%d] ", indice);
        imprimir_show(topo->elemento);
        imprimir_pilha_com_indice(topo->proximo, indice - 1);
    }
}


// Busca por linha no arquivo
char* buscar_linha_por_id(const char* id, FILE* arquivo) {
    static char linha[MAX_LINE];
    rewind(arquivo);
    fgets(linha, MAX_LINE, arquivo); // pula cabeçalho

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
    No* pilha = NULL;

    while (scanf(" %[^\n]", entrada) && strcmp(entrada, "FIM") != 0) {
        linhas[total_ids] = strdup(entrada);
        total_ids++;
    }

    FILE* arquivo = fopen("/tmp/disneyplus.csv", "r");
    if (!arquivo) {
        printf("Arquivo não encontrado\n");
        return 1;
    }

    // Inserção inicial
    for (int i = 0; i < total_ids; i++) {
        char* linha = buscar_linha_por_id(linhas[i], arquivo);
        if (linha) {
            Show s = ler_show(linha);
            pilha = inserir_pilha(pilha, s);
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
                pilha = inserir_pilha(pilha, s);
            }
        } else if (entrada[0] == 'R') {
            Show removido;
            pilha = remover_pilha(pilha, &removido);
            printf("(R) %s\n", removido.title);
        }
    }
    int tamanho = tamanho_pilha(pilha);
    imprimir_pilha_com_indice(pilha, tamanho - 1);
    

    fclose(arquivo);
    return 0;
}
