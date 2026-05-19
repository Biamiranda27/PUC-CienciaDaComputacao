#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 

typedef struct {
    int ano, mes, dia;
} Data;

typedef struct {
    int hora, minuto;
} Hora;

typedef struct {
    int      id;
    char     nome[256];
    char     cidade[256];
    int      capacidade;
    double   avaliacao;
    char     tiposCozinha[512];
    int      faixaPreco;
    Hora     horarioAbertura;
    Hora     horarioFechamento;
    int      temHorarioAbertura;
    int      temHorarioFechamento;
    Data     dataAbertura;
    int      temData;
    int      aberto;
} Restaurante;

typedef struct No {
    Restaurante  elemento;
    struct No   *esq;
    struct No   *dir;
} No;

typedef struct {
    No  *raiz;
    int  comparacoes;
} ArvoreBinaria;

typedef struct {
    Restaurante *restaurantes;
    int          tamanho;
    int          capacidadeMax;
} ColecaoRestaurantes;
 

void formatarData(const Data *d, char *buf, int bufSize) {
    snprintf(buf, bufSize, "%02d/%02d/%04d", d->dia, d->mes, d->ano);
}
 
int parseData(const char *s, Data *out) {
    if (!s || strlen(s) == 0 || strcasecmp(s, "NaN") == 0)
        return 0;
    int a, m, d;
    if (sscanf(s, "%d-%d-%d", &a, &m, &d) == 3) {
        out->ano = a; out->mes = m; out->dia = d;
        return 1;
    }
    return 0;
}
 

void formatarHora(const Hora *h, char *buf, int bufSize) {
    snprintf(buf, bufSize, "%02d:%02d", h->hora, h->minuto);
}
 
int parseHora(const char *s, Hora *out) {
    if (!s || strlen(s) == 0 || strcasecmp(s, "NaN") == 0)
        return 0;
    int h, m;
    if (sscanf(s, "%d:%d", &h, &m) == 2) {
        out->hora = h; out->minuto = m;
        return 1;
    }
    return 0;
}
 

void formatarRestaurante(const Restaurante *r) {
     
    char preco[16] = "";
    for (int i = 0; i < r->faixaPreco && i < 15; i++)
        preco[i] = '$';
    preco[r->faixaPreco] = '\0';

    char dataStr[32]  = "NaN";
    char horaAb[16]   = "NaN";
    char horaFe[16]   = "NaN";

    if (r->temData)             formatarData(&r->dataAbertura, dataStr, sizeof(dataStr));
    if (r->temHorarioAbertura)  formatarHora(&r->horarioAbertura,  horaAb, sizeof(horaAb));
    if (r->temHorarioFechamento) formatarHora(&r->horarioFechamento, horaFe, sizeof(horaFe));

    printf("[%d ## %s ## %s ## %d ## %.1f ## [%s] ## %s ## %s-%s ## %s ## %s]\n",
           r->id, r->nome, r->cidade, r->capacidade, r->avaliacao,
           r->tiposCozinha, preco, horaAb, horaFe, dataStr,
           r->aberto ? "true" : "false");
}
 
static void trim(char *s) {
    
    int start = 0;
    while (s[start] == ' ' || s[start] == '"') start++;
    int len = strlen(s);
     
    int end = len - 1;
    while (end >= start && (s[end] == ' ' || s[end] == '"' || s[end] == '\r' || s[end] == '\n'))
        end--;
    int newLen = end - start + 1;
    if (newLen < 0) newLen = 0;
    memmove(s, s + start, newLen);
    s[newLen] = '\0';
}
 
static int splitCsv(const char *linha, char campos[][512], int maxCampos) {
    int  fieldIdx = 0;
    int  charIdx  = 0;
    int  inQuotes = 0;
    int  len      = strlen(linha);

    campos[0][0] = '\0';
    int ci = 0;

    for (int i = 0; i <= len && fieldIdx < maxCampos; i++) {
        char c = linha[i];
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if ((c == ',' && !inQuotes) || c == '\0') {
            campos[fieldIdx][ci] = '\0';
            trim(campos[fieldIdx]);
            fieldIdx++;
            ci = 0;
            if (fieldIdx < maxCampos) campos[fieldIdx][0] = '\0';
        } else {
            if (ci < 511) campos[fieldIdx][ci++] = c;
        }
    }
    return fieldIdx;
}

Restaurante parseRestaurante(const char *linha) {
    Restaurante r;
    memset(&r, 0, sizeof(r));

    char campos[12][512];
    int  n = splitCsv(linha, campos, 12);
    if (n < 10) return r;

    r.id         = atoi(campos[0]);
    strncpy(r.nome,   campos[1], 255);
    strncpy(r.cidade, campos[2], 255);
    r.capacidade = campos[3][0] ? atoi(campos[3]) : 0;
    r.avaliacao  = campos[4][0] ? atof(campos[4]) : 0.0;
 
    char tipos[512];
    strncpy(tipos, campos[5], 511);
    char limpo[512];
    int li = 0;
    for (int i = 0; tipos[i]; i++) {
        char c = tipos[i];
        if (c == '[' || c == ']' || c == '\'') continue;
        if (c == ';') c = ',';
        limpo[li++] = c;
    }
    limpo[li] = '\0';
    strncpy(r.tiposCozinha, limpo, 511);
 
    r.faixaPreco = campos[6][0] ? (int)strlen(campos[6]) : 0;
 
    if (campos[7][0] && strchr(campos[7], '-')) {
        char *sep = strchr(campos[7], '-');
        char horaAbStr[16] = {0};
        char horaFeStr[16] = {0};
        strncpy(horaAbStr, campos[7], (int)(sep - campos[7]));
        strncpy(horaFeStr, sep + 1, 15);
        r.temHorarioAbertura   = parseHora(horaAbStr, &r.horarioAbertura);
        r.temHorarioFechamento = parseHora(horaFeStr,  &r.horarioFechamento);
    }

    r.temData = parseData(campos[8], &r.dataAbertura);

    r.aberto = (strcasecmp(campos[9], "true") == 0 || strcmp(campos[9], "1") == 0);

    return r;
}
 

ColecaoRestaurantes *criarColecao(int cap) {
    ColecaoRestaurantes *c = malloc(sizeof(ColecaoRestaurantes));
    c->restaurantes   = malloc(sizeof(Restaurante) * cap);
    c->tamanho        = 0;
    c->capacidadeMax  = cap;
    return c;
}

void liberarColecao(ColecaoRestaurantes *c) {
    free(c->restaurantes);
    free(c);
}

void lerCsv(ColecaoRestaurantes *col, const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (!f) { fprintf(stderr, "Erro ao abrir %s\n", caminho); return; }

    char linha[4096];
    fgets(linha, sizeof(linha), f); 

    while (fgets(linha, sizeof(linha), f)) {
        if (col->tamanho >= col->capacidadeMax) break;
        col->restaurantes[col->tamanho++] = parseRestaurante(linha);
    }
    fclose(f);
}
 

static No *criarNo(Restaurante r) {
    No *n = malloc(sizeof(No));
    n->elemento = r;
    n->esq = n->dir = NULL;
    return n;
}

static No *inserirNo(No *raiz, Restaurante r) {
    if (!raiz) return criarNo(r);
    int cmp = strcmp(r.nome, raiz->elemento.nome);
    if      (cmp < 0) raiz->esq = inserirNo(raiz->esq, r);
    else if (cmp > 0) raiz->dir = inserirNo(raiz->dir, r);
     
    return raiz;
}

void abInserir(ArvoreBinaria *ab, Restaurante r) {
    ab->raiz = inserirNo(ab->raiz, r);
}

static void pesquisarNo(ArvoreBinaria *ab, const char *nome, No *no) {
    if (!no) {
        printf("NAO\n");
        return;
    }
    ab->comparacoes++;
    if (strcmp(nome, no->elemento.nome) == 0) {
        printf("SIM\n");
    } else {
        ab->comparacoes++;
        if (strcmp(nome, no->elemento.nome) < 0) {
            printf("esq ");
            pesquisarNo(ab, nome, no->esq);
        } else {
            printf("dir ");
            pesquisarNo(ab, nome, no->dir);
        }
    }
}

void abPesquisar(ArvoreBinaria *ab, const char *nome) {
    printf("raiz ");
    pesquisarNo(ab, nome, ab->raiz);
}

static void emOrdem(No *no) {
    if (!no) return;
    emOrdem(no->esq);
    formatarRestaurante(&no->elemento);
    emOrdem(no->dir);
}

void abMostrarEmOrdem(ArvoreBinaria *ab) {
    emOrdem(ab->raiz);
}

static void liberarArvore(No *no) {
    if (!no) return;
    liberarArvore(no->esq);
    liberarArvore(no->dir);
    free(no);
}
 

int main(void) {
    ColecaoRestaurantes *colecao = criarColecao(2000);
    lerCsv(colecao, "/tmp/restaurantes.csv");

    ArvoreBinaria ab = { .raiz = NULL, .comparacoes = 0 };

    char linha[512];
 
    while (fgets(linha, sizeof(linha), stdin)) {
         
        linha[strcspn(linha, "\r\n")] = '\0';
        if (strcmp(linha, "-1") == 0) break;
        if (linha[0] == '\0') continue;

        int idBusca = atoi(linha);
        for (int i = 0; i < colecao->tamanho; i++) {
            if (colecao->restaurantes[i].id == idBusca) {
                abInserir(&ab, colecao->restaurantes[i]);
                break;
            }
        }
    }
 
    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    while (fgets(linha, sizeof(linha), stdin)) {
        linha[strcspn(linha, "\r\n")] = '\0';
        if (strcmp(linha, "FIM") == 0) break;
        if (linha[0] == '\0') continue;
        abPesquisar(&ab, linha);
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);
    long ms = (fim.tv_sec  - inicio.tv_sec)  * 1000L
            + (fim.tv_nsec - inicio.tv_nsec) / 1000000L;
 
    abMostrarEmOrdem(&ab);
 
    FILE *log = fopen("882406_arvoreBinaria.txt", "w");
    if (log) {
        fprintf(log, "882406\t%d\t%ld\n", ab.comparacoes, ms);
        fclose(log);
    } else {
        fprintf(stderr, "Erro ao escrever o log\n");
    }
 
    liberarArvore(ab.raiz);
    liberarColecao(colecao);
    return 0;
}