#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct { int ano, mes, dia; } Data;
typedef struct { int hora, minuto; } Hora;

typedef struct {
    int id;
    char nome[100];
    char cidade[100];
    int capacidade;
    double avaliacao;
    char tiposCozinha[10][50];
    int qtdTiposCozinha;
    int faixaPreco;
    Hora horarioAbertura, horarioFechamento;
    Data dataAbertura;
    bool aberto;
} Restaurante;

long long comparacoes = 0;
long long movimentacoes = 0;

void trim(char* out, const char* in) {
    while (*in == ' ' || *in == '\t' || *in == '\r' || *in == '\n') in++;
    size_t len = strlen(in);
    while (len > 0 && (in[len-1] == ' ' || in[len-1] == '\t' || in[len-1] == '\r' || in[len-1] == '\n')) len--;
    strncpy(out, in, len);
    out[len] = '\0';
}

Data parseData(const char* s) {
    Data d;
    sscanf(s, "%4d-%2d-%2d", &d.ano, &d.mes, &d.dia);
    return d;
}

Hora parseHora(const char* s) {
    Hora h;
    sscanf(s, "%2d:%2d", &h.hora, &h.minuto);
    return h;
}

void formatarData(Data d, char* out) { sprintf(out, "%02d/%02d/%04d", d.dia, d.mes, d.ano); }
void formatarHora(Hora h, char* out) { sprintf(out, "%02d:%02d", h.hora, h.minuto); }

Restaurante parseRestaurante(char* s) {
    Restaurante r;
    char tokens[11][200];
    int t_idx = 0;
    char* save;
    char* token = strtok_r(s, ",", &save);
    while (token != NULL && t_idx < 11) {
        trim(tokens[t_idx++], token);
        token = strtok_r(NULL, ",", &save);
    }
    r.id = atoi(tokens[0]);
    strcpy(r.nome, tokens[1]);
    strcpy(r.cidade, tokens[2]);
    r.capacidade = atoi(tokens[3]);
    r.avaliacao = atof(tokens[4]);
    r.qtdTiposCozinha = 0;
    char* save2;
    char* tc = strtok_r(tokens[5], ";", &save2);
    while (tc != NULL) {
        char limpo[50];
        trim(limpo, tc);
        strcpy(r.tiposCozinha[r.qtdTiposCozinha++], limpo);
        tc = strtok_r(NULL, ";", &save2);
    }
    r.faixaPreco = strlen(tokens[6]);
    char ha[10], hf[10];
    sscanf(tokens[7], "%[^-]-%s", ha, hf);
    char hal[10], hfl[10];
    trim(hal, ha); trim(hfl, hf);
    r.horarioAbertura = parseHora(hal);
    r.horarioFechamento = parseHora(hfl);
    r.dataAbertura = parseData(tokens[8]);
    r.aberto = (strcmp(tokens[9], "true") == 0 || strcmp(tokens[9], "1") == 0);
    return r;
}

void formatarRestaurante(Restaurante* r, char* out) {
    char fp[10] = "";
    for (int i = 0; i < r->faixaPreco && i < 9; i++) strcat(fp, "$");
    char tc[500] = "[";
    for (int i = 0; i < r->qtdTiposCozinha; i++) {
        if (i > 0) strcat(tc, ",");
        strcat(tc, r->tiposCozinha[i]);
    }
    strcat(tc, "]");
    char ha[10], hf[10], da[15];
    formatarHora(r->horarioAbertura, ha);
    formatarHora(r->horarioFechamento, hf);
    formatarData(r->dataAbertura, da);
    sprintf(out, "[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %s]",
        r->id, r->nome, r->cidade, r->capacidade, r->avaliacao,
        tc, fp, ha, hf, da, r->aberto ? "true" : "false");
}

typedef struct { int tamanho; Restaurante* restaurantes; } ColecaoRestaurantes;

ColecaoRestaurantes lerCsv(const char* path) {
    ColecaoRestaurantes c = {0, NULL};
    FILE* f = fopen(path, "r");
    if (!f) { fprintf(stderr, "Erro ao abrir: %s\n", path); return c; }
    char linha[1024];
    int count = 0;
    fgets(linha, sizeof(linha), f);
    while (fgets(linha, sizeof(linha), f)) {
        char limpa[1024];
        trim(limpa, linha);
        if (strlen(limpa) > 0) count++;
    }
    c.restaurantes = (Restaurante*)malloc(count * sizeof(Restaurante));
    fseek(f, 0, SEEK_SET);
    fgets(linha, sizeof(linha), f);
    while (fgets(linha, sizeof(linha), f)) {
        char limpa[1024];
        trim(limpa, linha);
        if (strlen(limpa) > 0)
            c.restaurantes[c.tamanho++] = parseRestaurante(limpa);
    }
    fclose(f);
    return c;
}

int compararRestaurantes(Restaurante* a, Restaurante* b) {
    comparacoes++;
    if (a->dataAbertura.ano != b->dataAbertura.ano) return a->dataAbertura.ano - b->dataAbertura.ano;
    comparacoes++;
    if (a->dataAbertura.mes != b->dataAbertura.mes) return a->dataAbertura.mes - b->dataAbertura.mes;
    comparacoes++;
    if (a->dataAbertura.dia != b->dataAbertura.dia) return a->dataAbertura.dia - b->dataAbertura.dia;
    return strcmp(a->nome, b->nome);
}

void trocar(Restaurante* a, Restaurante* b) {
    Restaurante tmp = *a; *a = *b; *b = tmp;
    movimentacoes += 3;
}

void reconstruirHeap(Restaurante* v, int tam) {
    for (int i = 1; i <= tam; i++) {
        int filho = i;
        while (filho > 1) {
            int pai = filho / 2;
            if (compararRestaurantes(&v[filho-1], &v[pai-1]) > 0) {
                trocar(&v[filho-1], &v[pai-1]);
                filho = pai;
            } else break;
        }
    }
}

void restaurarHeap(Restaurante* v, int tam) {
    int pai = 1;
    while (pai * 2 <= tam) {
        int filho = pai * 2;
        if (filho + 1 <= tam && compararRestaurantes(&v[filho], &v[filho-1]) > 0) filho++;
        if (compararRestaurantes(&v[filho-1], &v[pai-1]) > 0) {
            trocar(&v[pai-1], &v[filho-1]);
            pai = filho;
        } else break;
    }
}

void heapsortParcial(Restaurante* v, int n, int k) {
    reconstruirHeap(v, k);
    for (int i = k; i < n; i++) {
        if (compararRestaurantes(&v[i], &v[0]) < 0) {
            trocar(&v[0], &v[i]);
            restaurarHeap(v, k);
        }
    }
    for (int i = k; i > 1; i--) {
        trocar(&v[0], &v[i-1]);
        restaurarHeap(v, i - 1);
    }
}

int main() {
    ColecaoRestaurantes colecao = lerCsv("/tmp/restaurantes.csv");
    if (colecao.tamanho == 0) return 1;

    int max_ids = 100;
    int* idList = (int*)malloc(max_ids * sizeof(int));
    int qtd = 0;
    int valor;
    while (scanf("%d", &valor) == 1) {
        if (valor == -1) break;
        if (qtd >= max_ids) { max_ids *= 2; idList = (int*)realloc(idList, max_ids * sizeof(int)); }
        idList[qtd++] = valor;
    }

    Restaurante* selecionados = (Restaurante*)malloc(qtd * sizeof(Restaurante));
    int count = 0;
    for (int i = 0; i < qtd; i++)
        for (int j = 0; j < colecao.tamanho; j++)
            if (colecao.restaurantes[j].id == idList[i]) { selecionados[count++] = colecao.restaurantes[j]; break; }

    int k = 10;
    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    heapsortParcial(selecionados, count, k);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    long long tempo = (fim.tv_sec - inicio.tv_sec) * 1000000000LL + (fim.tv_nsec - inicio.tv_nsec);

    char buf[2048];
    for (int i = 0; i < count; i++) {
        formatarRestaurante(&selecionados[i], buf);
        printf("%s\n", buf);
    }

    FILE* fw = fopen("845860_heapsort_parcial.txt", "w");
    if (fw) { fprintf(fw, "845860\t%lld\t%lld\t%lld\n", comparacoes, movimentacoes, tempo); fclose(fw); }

    free(idList);
    free(selecionados);
    free(colecao.restaurantes);
    return 0;
}