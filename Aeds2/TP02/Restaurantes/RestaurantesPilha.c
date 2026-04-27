#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

typedef struct {
    Restaurante* array[2000];
    int topo;
} Pilha;

void remove_newlines(char* string) {
    if (!string) return;
    int i = 0, j = 0;
    while (string[i]) {
        if (string[i] != '\r' && string[i] != '\n') {
            string[j++] = string[i];
        }
        i++;
    }
    string[j] = '\0';
}

void trim_field(char* string) {
    if (string == NULL) return;
    int inicio = 0, fim = strlen(string) - 1;
    while (inicio <= fim && (string[inicio] == ' ' || string[inicio] == '\t' || string[inicio] == '\"')) inicio++;
    while (fim >= inicio && (string[fim] == ' ' || string[fim] == '\t' || string[fim] == '\"')) fim--;
    int i = 0;
    for (int j = inicio; j <= fim; j++) {
        string[i++] = string[j];
    }
    string[i] = '\0';
}

void trim_array_token(char* string) {
    if (string == NULL) return;
    int inicio = 0, fim = strlen(string) - 1;
    while (inicio <= fim && (string[inicio] == ' ' || string[inicio] == '\t' || string[inicio] == '\'' || string[inicio] == '\"' || string[inicio] == '[' || string[inicio] == ']')) inicio++;
    while (fim >= inicio && (string[fim] == ' ' || string[fim] == '\t' || string[fim] == '\'' || string[fim] == '\"' || string[fim] == '[' || string[fim] == ']')) fim--;
    int i = 0;
    for (int j = inicio; j <= fim; j++) {
        string[i++] = string[j];
    }
    string[i] = '\0';
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

void iniciar_pilha(Pilha* pilha) {
    pilha->topo = 0;
}

void empilhar(Pilha* pilha, Restaurante* restaurante) {
    if (pilha->topo < 2000) {
        pilha->array[pilha->topo++] = restaurante;
    }
}

Restaurante* desempilhar(Pilha* pilha) {
    if (pilha->topo > 0) {
        return pilha->array[--(pilha->topo)];
    }
    return NULL;
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
    
    Pilha pilha;
    iniciar_pilha(&pilha);
    
    int idBusca;
    while (scanf("%d", &idBusca) == 1 && idBusca != -1) {
        for (int i = 0; i < colecao.tamanho; i++) {
            if (colecao.restaurantes[i]->id == idBusca) {
                empilhar(&pilha, colecao.restaurantes[i]);
                break;
            }
        }
    }
    
    int num_comandos;
    if (scanf("%d", &num_comandos) == 1) {
        for (int i = 0; i < num_comandos; i++) {
            char comando[5];
            scanf("%s", comando);
            
            if (strcmp(comando, "I") == 0) {
                int id_inserir;
                scanf("%d", &id_inserir);
                for (int j = 0; j < colecao.tamanho; j++) {
                    if (colecao.restaurantes[j]->id == id_inserir) {
                        empilhar(&pilha, colecao.restaurantes[j]);
                        break;
                    }
                }
            } else if (strcmp(comando, "R") == 0) {
                Restaurante* removido = desempilhar(&pilha);
                if (removido != NULL) {
                    printf("(R)%s\n", removido->nome);
                }
            }
        }
    }
    
    char buffer[1024];
    for (int i = pilha.topo - 1; i >= 0; i--) {
        formatar_restaurante(pilha.array[i], buffer);
        printf("%s\n", buffer);
    }
    
    for (int i = 0; i < colecao.tamanho; i++) {
        free(colecao.restaurantes[i]->nome);
        free(colecao.restaurantes[i]->cidade);
        for(int j = 0; j < colecao.restaurantes[i]->n_tipos_cozinha; j++){
            free(colecao.restaurantes[i]->tipos_cozinha[j]);
        }
        free(colecao.restaurantes[i]->tipos_cozinha);
        free(colecao.restaurantes[i]);
    }
    free(colecao.restaurantes);
    
    return 0;
}