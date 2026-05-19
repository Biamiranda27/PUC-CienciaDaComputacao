#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
typedef struct {
    int ano, mes, dia;
} Data;

Data* parseData(const char* s) {
    if (!s || strlen(s) == 0 || strcasecmp(s, "NaN") == 0) return NULL;
    Data* d = malloc(sizeof(Data));
    sscanf(s, "%d-%d-%d", &d->ano, &d->mes, &d->dia);
    return d;
}

void formatarData(const Data* d, char* buf) {
    if (!d) { strcpy(buf, "NaN"); return; }
    sprintf(buf, "%02d/%02d/%04d", d->dia, d->mes, d->ano);
}
 
typedef struct {
    int hora, minuto;
} Hora;

Hora* parseHora(const char* s) {
    if (!s || strlen(s) == 0 || strcasecmp(s, "NaN") == 0) return NULL;
    Hora* h = malloc(sizeof(Hora));
    sscanf(s, "%d:%d", &h->hora, &h->minuto);
    return h;
}

void formatarHora(const Hora* h, char* buf) {
    if (!h) { strcpy(buf, "NaN"); return; }
    sprintf(buf, "%02d:%02d", h->hora, h->minuto);
}
 
typedef struct {
    int    id;
    char   nome[256];
    char   cidade[256];
    int    capacidade;
    double avaliacao;
    char   tiposCozinha[512];
    int    faixaPreco;
    Hora*  horarioAbertura;
    Hora*  horarioFechamento;
    Data*  dataAbertura;
    int    aberto;           
} Restaurante;
 
static void trim(char* s) {
    if (!s) return;
    
    int i = 0;
    while (s[i] && isspace((unsigned char)s[i])) i++;
    if (i) memmove(s, s + i, strlen(s + i) + 1);
     
    int len = (int)strlen(s);
    while (len > 0 && isspace((unsigned char)s[len-1])) s[--len] = '\0';
}
 
static void stripQuotes(char* s) {
    int len = (int)strlen(s);
    if (len >= 2 && s[0] == '"' && s[len-1] == '"') {
        memmove(s, s + 1, len - 2);
        s[len-2] = '\0';
    }
}

 
static int splitCsv(const char* linha, char campos[][512], int maxCampos) {
    int n = 0;
    const char* p = linha;
    while (*p && n < maxCampos) {
        char buf[512];
        int bi = 0;
        if (*p == '"') {
            p++;  
            while (*p) {
                if (*p == '"' && *(p+1) == '"') { buf[bi++] = '"'; p += 2; }
                else if (*p == '"') { p++; break; }
                else buf[bi++] = *p++;
            }
        } else {
            while (*p && *p != ',') buf[bi++] = *p++;
        }
        buf[bi] = '\0';
        trim(buf);
        strncpy(campos[n], buf, 511);
        campos[n][511] = '\0';
        n++;
        if (*p == ',') p++;
    }
    return n;
}

Restaurante* parseRestaurante(const char* linha) {
    Restaurante* r = calloc(1, sizeof(Restaurante));
    char campos[15][512];
    int n = splitCsv(linha, campos, 15);
    if (n < 10) { free(r); return NULL; }

    r->id         = atoi(campos[0]);
    strncpy(r->nome,   campos[1], 255);
    strncpy(r->cidade, campos[2], 255);
    r->capacidade = campos[3][0] ? atoi(campos[3]) : 0;
    r->avaliacao  = campos[4][0] ? atof(campos[4]) : 0.0;
 
    char tipos[512];
    strncpy(tipos, campos[5], 511);
    char limpo[512]; int li = 0;
    for (int i = 0; tipos[i]; i++) {
        char c = tipos[i];
        if (c != '[' && c != ']' && c != '\'') {
            if (c == ';') c = ',';    
            limpo[li++] = c;
        }
    }
    limpo[li] = '\0';
    strncpy(r->tiposCozinha, limpo, 511);
 
    r->faixaPreco = (int)strlen(campos[6]);
 
    if (campos[7][0] && strchr(campos[7], '-')) {
        char* sep = strchr(campos[7], '-');
        char abre[16] = {0}, fecha[16] = {0};
        int lenAbre = (int)(sep - campos[7]);
        strncpy(abre, campos[7], lenAbre);
        strncpy(fecha, sep + 1, 15);
        r->horarioAbertura   = parseHora(abre);
        r->horarioFechamento = parseHora(fecha);
    }

    r->dataAbertura = parseData(campos[8]);

    r->aberto = (strcasecmp(campos[9], "true") == 0 || campos[9][0] == '1') ? 1 : 0;

    return r;
}

void formatarRestaurante(const Restaurante* r) {
     
    char cozinha[512];
    snprintf(cozinha, sizeof(cozinha), "[%s]", r->tiposCozinha);
 
    char preco[16] = {0};
    for (int i = 0; i < r->faixaPreco && i < 10; i++) preco[i] = '$';

    char dataFmt[32], abreFmt[16], fechaFmt[16];
    formatarData(r->dataAbertura, dataFmt);
    formatarHora(r->horarioAbertura,   abreFmt);
    formatarHora(r->horarioFechamento, fechaFmt);

    printf("[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %s]\n",
           r->id, r->nome, r->cidade, r->capacidade, r->avaliacao,
           cozinha, preco, abreFmt, fechaFmt, dataFmt,
           r->aberto ? "true" : "false");
}

void liberarRestaurante(Restaurante* r) {
    if (!r) return;
    free(r->horarioAbertura);
    free(r->horarioFechamento);
    free(r->dataAbertura);
    free(r);
}
 
typedef struct {
    Restaurante** lista;
    int tamanho;
    int capacidade;
} ColecaoRestaurantes;

ColecaoRestaurantes* criarColecao(int cap) {
    ColecaoRestaurantes* c = malloc(sizeof(ColecaoRestaurantes));
    c->lista     = malloc(cap * sizeof(Restaurante*));
    c->tamanho   = 0;
    c->capacidade = cap;
    return c;
}

void lerCsv(ColecaoRestaurantes* col, const char* caminho) {
    FILE* f = fopen(caminho, "r");
    if (!f) { fprintf(stderr, "Erro ao abrir %s\n", caminho); return; }
    char linha[4096];
    fgets(linha, sizeof(linha), f);  
    while (fgets(linha, sizeof(linha), f)) {
         
        linha[strcspn(linha, "\n")] = '\0';
        if (col->tamanho < col->capacidade) {
            Restaurante* r = parseRestaurante(linha);
            if (r) col->lista[col->tamanho++] = r;
        }
    }
    fclose(f);
}

Restaurante* buscarPorId(ColecaoRestaurantes* col, int id) {
    for (int i = 0; i < col->tamanho; i++)
        if (col->lista[i] && col->lista[i]->id == id)
            return col->lista[i];
    return NULL;
}
 
typedef struct No {
    Restaurante* dado;
    struct No*   prox;
} No;

typedef struct {
    No*  frente;    
    No*  tras;     
    int  tamanho;
} FilaEncadeada;

FilaEncadeada* criarFila() {
    FilaEncadeada* f = malloc(sizeof(FilaEncadeada));
    f->frente  = NULL;
    f->tras    = NULL;
    f->tamanho = 0;
    return f;
}
 
void inserir(FilaEncadeada* f, Restaurante* r) {
    No* novo = malloc(sizeof(No));
    novo->dado = r;
    novo->prox = NULL;

    if (!f->tras) {                
        f->frente = novo;
        f->tras   = novo;
    } else {
        f->tras->prox = novo;
        f->tras       = novo;
    }
    f->tamanho++;
}
 
Restaurante* remover(FilaEncadeada* f) {
    if (!f->frente) return NULL;

    No* removido = f->frente;
    Restaurante* r = removido->dado;

    f->frente = removido->prox;
    if (!f->frente) f->tras = NULL;
    free(removido);
    f->tamanho--;

    printf("(R)%s\n", r->nome);
    return r;
}
 
void mostrar(FilaEncadeada* f) {
    int pos = 0;
    No* atual = f->frente;
    while (atual) {
        printf("[%d] ", pos++);
        formatarRestaurante(atual->dado);
        atual = atual->prox;
    }
}
 
int main() {
    ColecaoRestaurantes* colecao = criarColecao(2000);
    lerCsv(colecao, "/tmp/restaurantes.csv");

    FilaEncadeada* fila = criarFila();
 
    int id;
    while (scanf("%d", &id) == 1 && id != -1) {
        Restaurante* r = buscarPorId(colecao, id);
        if (r) inserir(fila, r);
    }
 
    int numComandos;
    if (scanf("%d", &numComandos) == 1) {
        for (int i = 0; i < numComandos; i++) {
            char cmd[4];
            scanf("%3s", cmd);
            if (strcmp(cmd, "I") == 0) {
                int idCmd;
                scanf("%d", &idCmd);
                Restaurante* r = buscarPorId(colecao, idCmd);
                if (r) inserir(fila, r);
            } else if (strcmp(cmd, "R") == 0) {
                remover(fila);
            }
        }
    }
 
    mostrar(fila);
 
    No* cur = fila->frente;
    while (cur) {
        No* prox = cur->prox;
        free(cur);
        cur = prox;
    }
    free(fila);
 
    for (int i = 0; i < colecao->tamanho; i++)
        liberarRestaurante(colecao->lista[i]);
    free(colecao->lista);
    free(colecao);

    return 0;
}