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

void limpar_string(char* string) {
    if (string == NULL) return;
    int inicio = 0, fim = strlen(string) - 1;
    
    while (string[inicio] == ' ' || string[inicio] == '\"' || string[inicio] == '[' || string[inicio] == '\'' || string[inicio] == '\n' || string[inicio] == '\r') inicio++;
    
    while (fim >= inicio && (string[fim] == ' ' || string[fim] == '\"' || string[fim] == ']' || string[fim] == '\'' || string[fim] == '\n' || string[fim] == '\r')) fim--;
    
    int i = 0;
    for (int j = inicio; j <= fim; j++) {
        if (string[j] != '\n' && string[j] != '\r') {
            string[i++] = string[j];
        }
    }
    string[i] = '\0';
}

Data parse_data(char* string) {
    Data data = {0, 0, 0};
    if (string == NULL || strlen(string) == 0 || strcmp(string, "NaN") == 0) return data;
    sscanf(string, "%d-%d-%d", &data.ano, &data.mes, &data.dia);
    return data;
}

void formatar_data(Data* data, char* buffer) {
    if (data->ano == 0 && data->mes == 0 && data->dia == 0) sprintf(buffer, "NaN");
    else sprintf(buffer, "%02d/%02d/%04d", data->dia, data->mes, data->ano);
}

Hora parse_hora(char* string) {
    Hora hora = {-1, -1}; 
    if (string == NULL || strlen(string) == 0 || strcmp(string, "NaN") == 0) return hora;
    sscanf(string, "%d:%d", &hora.hora, &hora.minuto);
    return hora;
}

void formatar_hora(Hora* hora, char* buffer) {
    if (hora->hora == -1) sprintf(buffer, "NaN");
    else sprintf(buffer, "%02d:%02d", hora->hora, hora->minuto);
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
        if (*ptr == '\"') {
            in_quotes = !in_quotes;
        } else if (*ptr == ',' && !in_quotes) {
            *ptr = '\0';
            if (count < 15) campos[count++] = start;
            start = ptr + 1;
        }
        ptr++;
    }
    if (count < 15) campos[count++] = start;

    for(int i = 0; i < count; i++) {
        limpar_string(campos[i]);
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
            limpar_string(token);
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
    
    formatar_data(&restaurante->data_abertura, data_str);
    formatar_hora(&restaurante->horario_abertura, hora_abertura_str);
    formatar_hora(&restaurante->horario_fechamento, hora_fechamento_str);

    char cozinha_str[500] = "[";
    for (int i = 0; i < restaurante->n_tipos_cozinha; i++) {
        strcat(cozinha_str, restaurante->tipos_cozinha[i]);
        if (i < restaurante->n_tipos_cozinha - 1) {
            strcat(cozinha_str, ", "); 
        }
    }
    strcat(cozinha_str, "]");

    char preco_str[10] = "";
    for (int i = 0; i < restaurante->faixa_preco; i++) strcat(preco_str, "$");

    sprintf(buffer, "[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %s]",
            restaurante->id, restaurante->nome, restaurante->cidade, restaurante->capacidade, restaurante->avaliacao, cozinha_str, preco_str,
            hora_abertura_str, hora_fechamento_str, data_str, restaurante->aberto ? "true" : "false");
}

void ler_csv_colecao(Colecao_Restaurantes* colecao, char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) return;

    char linha[1024];
    fgets(linha, sizeof(linha), file);

    while (fgets(linha, sizeof(linha), file) != NULL) {
        colecao->restaurantes[colecao->tamanho++] = parse_restaurante(linha);
    }
    fclose(file);
}

Colecao_Restaurantes* ler_csv() {
    Colecao_Restaurantes* colecao = (Colecao_Restaurantes*) malloc(sizeof(Colecao_Restaurantes));
    colecao->tamanho = 0;
    colecao->restaurantes = (Restaurante**) malloc(2000 * sizeof(Restaurante*));
    
    ler_csv_colecao(colecao, "/tmp/restaurantes.csv"); 
    return colecao;
}

void selecao(Restaurante** array, int n, int* comparacoes, int* movimentacoes) {
    for (int i = 0; i < (n - 1); i++) {
        int menor = i;
        for (int j = (i + 1); j < n; j++) {
            (*comparacoes)++;
            if (strcmp(array[menor]->nome, array[j]->nome) > 0) {
                menor = j;
            }
        }
        if (menor != i) {
            Restaurante* temp = array[i];
            array[i] = array[menor];
            array[menor] = temp;
            (*movimentacoes) += 3;
        }
    }
}

int main() {
    Colecao_Restaurantes* colecao = ler_csv();
    int idBusca;
    char buffer[1024];
    
    Restaurante* selecionados[2000];
    int n_selecionados = 0;

    while (scanf("%d", &idBusca) == 1 && idBusca != -1) {
        for (int i = 0; i < colecao->tamanho; i++) {
            if (colecao->restaurantes[i]->id == idBusca) {
                selecionados[n_selecionados++] = colecao->restaurantes[i];
                break;
            }
        }
    }

    int comparacoes = 0;
    int movimentacoes = 0;

    clock_t inicio = clock();
    selecao(selecionados, n_selecionados, &comparacoes, &movimentacoes);
    clock_t fim = clock();
    
    double tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000.0;

    for (int i = 0; i < n_selecionados; i++) {
        formatar_restaurante(selecionados[i], buffer);
        printf("%s\n", buffer);
    }

    FILE* log = fopen("882406_selecao.txt", "w");
    if (log != NULL) {
        fprintf(log, "882406\t%d\t%d\t%.2f\n", comparacoes, movimentacoes, tempo_execucao);
        fclose(log);
    }

    for (int i = 0; i < colecao->tamanho; i++) {
        free(colecao->restaurantes[i]->nome);
        free(colecao->restaurantes[i]->cidade);
        for(int j = 0; j < colecao->restaurantes[i]->n_tipos_cozinha; j++){
            free(colecao->restaurantes[i]->tipos_cozinha[j]);
        }
        free(colecao->restaurantes[i]->tipos_cozinha);
        free(colecao->restaurantes[i]);
    }
    free(colecao->restaurantes);
    free(colecao);

    return 0;
}