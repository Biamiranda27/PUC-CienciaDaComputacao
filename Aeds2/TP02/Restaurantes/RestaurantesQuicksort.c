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

void trim_field(char* string) {
    if (string == NULL) return;
    int inicio = 0, fim = strlen(string) - 1;
    while (string[inicio] == ' ' || string[inicio] == '\"' || string[inicio] == '\n' || string[inicio] == '\r') inicio++;
    while (fim >= inicio && (string[fim] == ' ' || string[fim] == '\"' || string[fim] == '\n' || string[fim] == '\r')) fim--;
    int i = 0;
    for (int j = inicio; j <= fim; j++) {
        if (string[j] != '\n' && string[j] != '\r') string[i++] = string[j];
    }
    string[i] = '\0';
}

void clean_array_chars(char* string) {
    int i = 0, j = 0;
    while (string[i]) {
        if (string[i] != '[' && string[i] != ']' && string[i] != '\'') string[j++] = string[i];
        i++;
    }
    string[j] = '\0';
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
        if (i != 5) trim_field(campos[i]);
    }
    
    restaurante->id = atoi(campos[0]);
    restaurante->nome = strdup(campos[1]);
    restaurante->cidade = strdup(campos[2]);
    restaurante->capacidade = (strlen(campos[3]) > 0) ? atoi(campos[3]) : 0;
    restaurante->avaliacao = (strlen(campos[4]) > 0) ? atof(campos[4]) : 0.0;
    
    if (strlen(campos[5]) > 0) {
        clean_array_chars(campos[5]);
        char* token = strtok(campos[5], ",;");
        restaurante->tipos_cozinha = malloc(20 * sizeof(char*));
        while (token != NULL) {
            trim_field(token);
            restaurante->tipos_cozinha[restaurante->n_tipos_cozinha++] = strdup(token);
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

void formatar_restaurante(Restaurante* restaurante, char* buffer) {
    char data_str[20], hora_abertura_str[10], hora_fechamento_str[10];
    
    if (restaurante->data_abertura.ano == 0) sprintf(data_str, "NaN");
    else sprintf(data_str, "%02d/%02d/%04d", restaurante->data_abertura.dia, restaurante->data_abertura.mes, restaurante->data_abertura.ano);
    
    if (restaurante->horario_abertura.hora == -1) sprintf(hora_abertura_str, "NaN");
    else sprintf(hora_abertura_str, "%02d:%02d", restaurante->horario_abertura.hora, restaurante->horario_abertura.minuto);
    
    if (restaurante->horario_fechamento.hora == -1) sprintf(hora_fechamento_str, "NaN");
    else sprintf(hora_fechamento_str, "%02d:%02d", restaurante->horario_fechamento.hora, restaurante->horario_fechamento.minuto);
    
    char cozinha_str[500] = "[";
    for (int i = 0; i < restaurante->n_tipos_cozinha; i++) {
        strcat(cozinha_str, restaurante->tipos_cozinha[i]);
        if (i < restaurante->n_tipos_cozinha - 1) strcat(cozinha_str, ", ");
    }
    strcat(cozinha_str, "]");
    
    char preco_str[10] = "";
    for (int i = 0; i < restaurante->faixa_preco; i++) strcat(preco_str, "$");
    
    sprintf(buffer, "[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %s]",
            restaurante->id, restaurante->nome, restaurante->cidade, restaurante->capacidade, restaurante->avaliacao, cozinha_str, preco_str, hora_abertura_str, hora_fechamento_str, data_str, restaurante->aberto ? "true" : "false");
}

void swap(Restaurante** a, Restaurante** b, int* mov) {
    Restaurante* temp = *a;
    *a = *b;
    *b = temp;
    (*mov) += 3;
}

int compare(Restaurante* a, Restaurante* b, int* comp) {
    (*comp)++;
    if (a->avaliacao < b->avaliacao) return -1;
    if (a->avaliacao > b->avaliacao) return 1;
    (*comp)++;
    return strcmp(a->nome, b->nome);
}

void quicksort(Restaurante** array, int esq, int dir, int* comp, int* mov) {
    int i = esq, j = dir;
    Restaurante* pivo = array[(esq + dir) / 2];
    
    while (i <= j) {
        while (compare(array[i], pivo, comp) < 0) i++;
        while (compare(array[j], pivo, comp) > 0) j--;
        if (i <= j) {
            swap(&array[i], &array[j], mov);
            i++; j--;
        }
    }
    
    if (esq < j) quicksort(array, esq, j, comp, mov);
    if (i < dir) quicksort(array, i, dir, comp, mov);
}

int main() {
    Colecao_Restaurantes colecao;
    colecao.tamanho = 0;
    colecao.restaurantes = (Restaurante**) malloc(2000 * sizeof(Restaurante*));
    
    FILE* file = fopen("/tmp/restaurantes.csv", "r");
    if (file) {
        char linha[2048];
        fgets(linha, sizeof(linha), file);
        while (fgets(linha, sizeof(linha), file)) colecao.restaurantes[colecao.tamanho++] = parse_restaurante(linha);
        fclose(file);
    }
    
    Restaurante* selecionados[2000];
    int n_selecionados = 0, idBusca;
    
    while (scanf("%d", &idBusca) == 1 && idBusca != -1) {
        for (int i = 0; i < colecao.tamanho; i++) {
            if (colecao.restaurantes[i]->id == idBusca) {
                selecionados[n_selecionados++] = colecao.restaurantes[i];
                break;
            }
        }
    }
    
    int comp = 0, mov = 0;
    clock_t inicio = clock();
    
    if (n_selecionados > 0) quicksort(selecionados, 0, n_selecionados - 1, &comp, &mov);
    
    double tempo = ((double)(clock() - inicio)) / CLOCKS_PER_SEC * 1000.0;
    char buffer[1024];
    
    for (int i = 0; i < n_selecionados; i++) {
        formatar_restaurante(selecionados[i], buffer);
        printf("%s\n", buffer);
    }
    
    FILE* log = fopen("882406_quicksort.txt", "w");
    if (log) {
        fprintf(log, "882406\t%d\t%d\t%.2f\n", comp, mov, tempo);
        fclose(log);
    }
    
    return 0;
}