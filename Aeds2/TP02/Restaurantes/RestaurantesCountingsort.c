#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    int ano;
    int mes;
    int dia;
} Data;

typedef struct {
    int hora;
    int minuto;
} Hora;

typedef struct {
    int id;
    char* nome;
    char* cidade;
    int capacidade;
    double avaliacao;
    int n_tipos_cozinha;
    char** tipos_cozinha;
    int faixa_preco;
    Hora horario_abertura;
    Hora horario_fechamento;
    Data data_abertura;
    bool aberto;
} Restaurante;

typedef struct {
    int tamanho;
    Restaurante** restaurantes;
} Colecao_Restaurantes;

void remove_newlines(char* str) {
    if (!str) return;
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != '\r' && str[i] != '\n') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

void trim_field(char* str) {
    if (str == NULL) return;
    int inicio = 0, fim = strlen(str) - 1;
    while (inicio <= fim && (str[inicio] == ' ' || str[inicio] == '\t' || str[inicio] == '\"')) inicio++;
    while (fim >= inicio && (str[fim] == ' ' || str[fim] == '\t' || str[fim] == '\"')) fim--;
    int i = 0;
    for (int j = inicio; j <= fim; j++) {
        str[i++] = str[j];
    }
    str[i] = '\0';
}

void trim_array_token(char* str) {
    if (str == NULL) return;
    int inicio = 0, fim = strlen(str) - 1;
    while (inicio <= fim && (str[inicio] == ' ' || str[inicio] == '\t' || str[inicio] == '\'' || str[inicio] == '\"' || str[inicio] == '[' || str[inicio] == ']')) inicio++;
    while (fim >= inicio && (str[fim] == ' ' || str[fim] == '\t' || str[fim] == '\'' || str[fim] == '\"' || str[fim] == '[' || str[fim] == ']')) fim--;
    int i = 0;
    for (int j = inicio; j <= fim; j++) {
        str[i++] = str[j];
    }
    str[i] = '\0';
}

Data parse_data(char* string) {
    Data data = {0, 0, 0};
    if (string == NULL || strlen(string) == 0 || strcmp(string, "NaN") == 0) return data;
    sscanf(string, "%d-%d-%d", &data.ano, &data.mes, &data.dia);
    return data;
}

Hora parse_hora(char* string) {
    Hora hora = {-1, -1};
    if (string == NULL || strlen(string) == 0 || strcmp(string, "NaN") == 0) return hora;
    sscanf(string, "%d:%d", &hora.hora, &hora.minuto);
    return hora;
}

Restaurante* parse_restaurante(char* string) {
    Restaurante* restaurante = (Restaurante*) malloc(sizeof(Restaurante));
    restaurante->n_tipos_cozinha = 0;
    restaurante->tipos_cozinha = NULL;
    
    char* campos[15];
    for (int i = 0; i < 15; i++) campos[i] = "";
    
    int count = 0;
    char* ptr = string;
    bool in_quotes = false;
    char* start = ptr;
    
    while (*ptr) {
        if (*ptr == '\"') in_quotes = !in_quotes;
        else if (*ptr == ',' && !in_quotes) {
            *ptr = '\0';
            if (count < 15) campos[count++] = start;
            start = ptr + 1;
        }
        ptr++;
    }
    if (count < 15) campos[count++] = start;
    
    for(int i = 0; i < count; i++) {
        trim_field(campos[i]);
    }
    
    restaurante->id = atoi(campos[0]);
    restaurante->nome = strdup(campos[1]);
    restaurante->cidade = strdup(campos[2]);
    restaurante->capacidade = (strlen(campos[3]) > 0) ? atoi(campos[3]) : 0;
    restaurante->avaliacao = (strlen(campos[4]) > 0) ? atof(campos[4]) : 0.0;
    
    if (strlen(campos[5]) > 0) {
        char* token = strtok(campos[5], ",;");
        restaurante->tipos_cozinha = malloc(20 * sizeof(char*));
        while (token != NULL) {
            trim_array_token(token);
            if (strlen(token) > 0) {
                restaurante->tipos_cozinha[restaurante->n_tipos_cozinha++] = strdup(token);
            }
            token = strtok(NULL, ",;");
        }
    }
    
    restaurante->faixa_preco = strlen(campos[6]);
    
    if (strlen(campos[7]) > 0 && strchr(campos[7], '-') != NULL) {
        char* traco = strchr(campos[7], '-');
        *traco = '\0';
        restaurante->horario_abertura = parse_hora(campos[7]);
        restaurante->horario_fechamento = parse_hora(traco + 1);
    } else {
        restaurante->horario_abertura = parse_hora("NaN");
        restaurante->horario_fechamento = parse_hora("NaN");
    }
    
    restaurante->data_abertura = parse_data(campos[8]);
    restaurante->aberto = (strcasecmp(campos[9], "true") == 0 || strcmp(campos[9], "1") == 0);
    
    return restaurante;
}

void formatar_restaurante(Restaurante* r, char* buffer) {
    char data_str[20], hora_abertura_str[10], hora_fechamento_str[10];
    
    if (r->data_abertura.ano == 0) sprintf(data_str, "NaN");
    else sprintf(data_str, "%02d/%02d/%04d", r->data_abertura.dia, r->data_abertura.mes, r->data_abertura.ano);
    
    if (r->horario_abertura.hora == -1) sprintf(hora_abertura_str, "NaN");
    else sprintf(hora_abertura_str, "%02d:%02d", r->horario_abertura.hora, r->horario_abertura.minuto);
    
    if (r->horario_fechamento.hora == -1) sprintf(hora_fechamento_str, "NaN");
    else sprintf(hora_fechamento_str, "%02d:%02d", r->horario_fechamento.hora, r->horario_fechamento.minuto);
    
    char cozinha_str[500] = "[";
    for (int i = 0; i < r->n_tipos_cozinha; i++) {
        strcat(cozinha_str, r->tipos_cozinha[i]);
        if (i < r->n_tipos_cozinha - 1) strcat(cozinha_str, ", ");
    }
    strcat(cozinha_str, "]");
    
    char preco_str[10] = "";
    for (int i = 0; i < r->faixa_preco; i++) strcat(preco_str, "$");
    
    sprintf(buffer, "[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %s]",
            r->id, r->nome, r->cidade, r->capacidade, r->avaliacao, cozinha_str, preco_str, hora_abertura_str, hora_fechamento_str, data_str, r->aberto ? "true" : "false");
}

void countingsort(Restaurante** array, int n, int* comp, int* mov) {
    if (n <= 1) return;
    int max = array[0]->capacidade;
    for (int i = 1; i < n; i++) {
        (*comp)++;
        if (array[i]->capacidade > max) {
            max = array[i]->capacidade;
        }
    }
    
    int* count = (int*) calloc((max + 1), sizeof(int));
    Restaurante** output = (Restaurante**) malloc(n * sizeof(Restaurante*));
    
    for (int i = 0; i < n; i++) {
        count[array[i]->capacidade]++;
    }
    
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }
    
    for (int i = n - 1; i >= 0; i--) {
        output[count[array[i]->capacidade] - 1] = array[i];
        count[array[i]->capacidade]--;
        (*mov)++;
    }
    
    for (int i = 0; i < n; i++) {
        array[i] = output[i];
        (*mov)++;
    }
    
    free(count);
    free(output);
}

int main() {
    Colecao_Restaurantes colecao;
    colecao.tamanho = 0;
    colecao.restaurantes = (Restaurante**) malloc(2000 * sizeof(Restaurante*));
    
    FILE* file = fopen("/tmp/restaurantes.csv", "r");
    if (file) {
        char linha[2048];
        fgets(linha, sizeof(linha), file);
        while (fgets(linha, sizeof(linha), file)) {
            remove_newlines(linha);
            colecao.restaurantes[colecao.tamanho++] = parse_restaurante(linha);
        }
        fclose(file);
    }
    
    Restaurante* selecionados[2000];
    int n_sel = 0, idBusca;
    
    while (scanf("%d", &idBusca) == 1 && idBusca != -1) {
        for (int i = 0; i < colecao.tamanho; i++) {
            if (colecao.restaurantes[i]->id == idBusca) {
                selecionados[n_sel++] = colecao.restaurantes[i];
                break;
            }
        }
    }
    
    int comp = 0, mov = 0;
    clock_t inicio = clock();
    
    if (n_sel > 0) countingsort(selecionados, n_sel, &comp, &mov);
    
    double tempo = ((double)(clock() - inicio)) / CLOCKS_PER_SEC * 1000.0;
    
    char buffer[1024];
    for (int i = 0; i < n_sel; i++) {
        formatar_restaurante(selecionados[i], buffer);
        printf("%s\n", buffer);
    }
    
    FILE* log = fopen("882406_countingsort.txt", "w");
    if (log) {
        fprintf(log, "882406\t%d\t%d\t%.2f\n", comp, mov, tempo);
        fclose(log);
    }
    
    return 0;
}