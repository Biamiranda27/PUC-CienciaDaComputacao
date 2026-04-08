#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
// Necessário para strptime (comum em ambientes Linux/GCC, mas não padrão ANSI C)
#define __USE_XOPEN 
#include <time.h> 

#define MAX_LINE_LENGTH 4096
#define MAX_GAMES 20000
#define MAX_TOKENS 50

// --- Estruturas de Dados ---

typedef struct {
    char* elements[MAX_TOKENS];
    int count;
} StringArray;

typedef struct {
    char App_Id[64];
    char Name[512];
    char Release_Date[32];
    char Estimated_Owners[64];
    double Price;
    StringArray Supported_Languages;
    int Metacritic_Score;
    double User_Score;
    int Achievements;
    char Publishers[256];
    char Developers[256];
    StringArray Categories;
    StringArray Genres;
    StringArray Tags;
} Game;

typedef struct Node {
    Game game;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
    int size;
} PilhaGames;

// --- Funções Auxiliares de Manipulação de Strings/Memória ---

void trim_inplace(char* s) {
    if (!s) return;
    int i = 0;
    while (isspace((unsigned char)s[i])) i++;
    int j = 0;
    while (s[i]) s[j++] = s[i++];
    s[j] = '\0';
    j--;
    while (j >= 0 && isspace((unsigned char)s[j])) s[j--] = '\0';
}

char* strdup_safe(const char* s) {
    if (!s) return NULL;
    char* r = (char*)malloc(strlen(s) + 1);
    if (r) strcpy(r, s);
    return r;
}

void split_list_field(const char* field, StringArray* arr) {
    arr->count = 0;
    if (!field || strcmp(field, "NaN") == 0 || strlen(field) == 0) {
        arr->elements[arr->count++] = strdup_safe("NaN");
        return;
    }
    char tmp[MAX_LINE_LENGTH];
    strncpy(tmp, field, sizeof(tmp)-1);
    tmp[sizeof(tmp)-1] = '\0';
    char* start = tmp;
    
    // Remove espaços/tabs iniciais e colchetes/parênteses
    while (*start == ' ' || *start == '\t') start++;
    if (*start == '[' || *start == '(') start++;
    char* end = tmp + strlen(tmp) - 1;
    while (end > start && (*end == ' ' || *end == '\t')) end--;
    if (*end == ']' || *end == ')') *end = '\0';
    
    // Substitui aspas simples/duplas por espaço para facilitar o strtok
    for (char* p = start; *p; p++) if (*p == '\'' || *p == '\"') *p = ' ';
    
    char* tok = strtok(start, ",");
    while (tok && arr->count < MAX_TOKENS) {
        // Trim inicial
        while (*tok && isspace((unsigned char)*tok)) tok++;
        // Trim final
        char *q = tok + strlen(tok) - 1;
        while (q >= tok && isspace((unsigned char)*q)) { *q = '\0'; q--; }
        
        if (strlen(tok) > 0) {
            arr->elements[arr->count++] = strdup_safe(tok);
        }
        tok = strtok(NULL, ",");
    }
    if (arr->count == 0) arr->elements[arr->count++] = strdup_safe("NaN");
}

void parse_csv_line_to_game(const char* line, Game* g) {
    char tmp[MAX_LINE_LENGTH];
    strncpy(tmp, line, sizeof(tmp)-1);
    tmp[sizeof(tmp)-1] = '\0';
    char parts[14][MAX_LINE_LENGTH];
    for (int i = 0; i < 14; i++) parts[i][0] = '\0';
    int part = 0;
    bool inQuotes = false;
    int idx = 0;
    
    // Lógica para lidar com campos entre aspas que contém vírgulas
    for (int i = 0; tmp[i] != '\0' && part < 14; i++) {
        char c = tmp[i];
        if (c == '"') { 
            inQuotes = !inQuotes; 
            continue; 
        }
        if (c == ',' && !inQuotes) {
            parts[part][idx] = '\0';
            part++;
            idx = 0;
            continue;
        }
        if (idx < MAX_LINE_LENGTH - 1) {
            parts[part][idx++] = c;
        }
    }
    parts[part][idx] = '\0';
    
    for (int i = 0; i <= part; i++) trim_inplace(parts[i]);
    for (int i = part + 1; i < 14; i++) strcpy(parts[i], "NaN");

    strcpy(g->App_Id, strlen(parts[0]) ? parts[0] : "NaN");
    strcpy(g->Name, strlen(parts[1]) ? parts[1] : "NaN");

    if (strlen(parts[2]) && strcmp(parts[2],"NaN")!=0) {
        struct tm tm_date = {0};
        char date_buffer[32];
        strncpy(date_buffer, parts[2], sizeof(date_buffer) - 1);
        date_buffer[sizeof(date_buffer) - 1] = '\0';
        
        if (strptime(date_buffer, "%b %d, %Y", &tm_date) != NULL) {
            strftime(g->Release_Date, sizeof(g->Release_Date), "%d/%m/%Y", &tm_date);
        } else {
            strcpy(g->Release_Date, "NaN");
        }
    } else {
        strcpy(g->Release_Date, "NaN");
    }

    strcpy(g->Estimated_Owners, strlen(parts[3]) ? parts[3] : "NaN");
    g->Price = (strlen(parts[4])==0 || strcmp(parts[4],"NaN")==0) ? 0.0 : atof(parts[4]);
    split_list_field(parts[5], &g->Supported_Languages);
    g->Metacritic_Score = (strlen(parts[6])==0 || strcmp(parts[6],"NaN")==0) ? -1 : atoi(parts[6]);
    g->User_Score = (strlen(parts[7])==0 || strcmp(parts[7],"NaN")==0) ? 0.0 : atof(parts[7]);
    g->Achievements = (strlen(parts[8])==0 || strcmp(parts[8],"NaN")==0) ? 0 : atoi(parts[8]);
    strcpy(g->Publishers, strlen(parts[9]) ? parts[9] : "NaN");
    strcpy(g->Developers, strlen(parts[10]) ? parts[10] : "NaN");
    split_list_field(parts[11], &g->Categories);
    split_list_field(parts[12], &g->Genres);
    split_list_field(parts[13], &g->Tags);
}

void clone_game(Game* dest, const Game* src) {
    *dest = *src;
    
    #define CLONE_STRING_ARRAY(arr_name) \
        dest->arr_name.count = src->arr_name.count; \
        for (int i = 0; i < src->arr_name.count; i++) \
            dest->arr_name.elements[i] = strdup_safe(src->arr_name.elements[i]);

    CLONE_STRING_ARRAY(Supported_Languages)
    CLONE_STRING_ARRAY(Categories)
    CLONE_STRING_ARRAY(Genres)
    CLONE_STRING_ARRAY(Tags)
    
    #undef CLONE_STRING_ARRAY
}

void free_game_resources(Game* g) {
    #define FREE_STRING_ARRAY(arr_name) \
        for (int i = 0; i < g->arr_name.count; i++) free(g->arr_name.elements[i]);
    
    FREE_STRING_ARRAY(Supported_Languages)
    FREE_STRING_ARRAY(Categories)
    FREE_STRING_ARRAY(Genres)
    FREE_STRING_ARRAY(Tags)
    
    #undef FREE_STRING_ARRAY
}

// --- Funções da Pilha ---

void startPilha(PilhaGames* pilha) { pilha->top = NULL; pilha->size = 0; }

void empilhar(PilhaGames* pilha, const Game* g) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) exit(2); 
    clone_game(&node->game, g);
    node->next = pilha->top;
    pilha->top = node;
    pilha->size++;
}

void mostrarPilha(const PilhaGames* pilha) {
    Node* nodes[MAX_GAMES];
    Node* current = pilha->top;
    int idx = 0;
    
    while (current && idx < MAX_GAMES) {
        nodes[idx++] = current;
        current = current->next;
    }
    
    for (int i = idx-1; i >= 0; i--) {
        Game* g = &nodes[i]->game;
        printf("[%d] => %s ## %s ## %s ## %s ## %.2f ## [",
               idx-1-i, g->App_Id, g->Name, g->Release_Date, g->Estimated_Owners, g->Price);
        for (int j = 0; j < g->Supported_Languages.count; j++) {
            printf("%s", g->Supported_Languages.elements[j]);
            if (j < g->Supported_Languages.count-1) printf(", ");
        }
        printf("] ## %d ## %.1f ## %d ## [%s] ## [%s] ## [",
               g->Metacritic_Score, g->User_Score, g->Achievements, g->Publishers, g->Developers);
        for (int j = 0; j < g->Categories.count; j++) {
            printf("%s", g->Categories.elements[j]);
            if (j < g->Categories.count-1) printf(", ");
        }
        printf("] ## [");
        for (int j = 0; j < g->Genres.count; j++) {
            printf("%s", g->Genres.elements[j]);
            if (j < g->Genres.count-1) printf(", ");
        }
        printf("] ## [");
        for (int j = 0; j < g->Tags.count; j++) {
            printf("%s", g->Tags.elements[j]);
            if (j < g->Tags.count-1) printf(", ");
        }
        printf("] ##\n");
    }
}

// --- Função Principal ---

int main() {
    FILE* fp = fopen("/tmp/games.csv", "r");
    if (!fp) {
        perror("Erro ao abrir /tmp/games.csv");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    if (!fgets(line, sizeof(line), fp)) { fclose(fp); return 1; } 

    Game* all = (Game*)malloc(MAX_GAMES * sizeof(Game));
    char** ids = (char**)malloc(MAX_GAMES * sizeof(char*));
    int total = 0;

    // 1. Leitura e parsing dos dados (populando o array 'all')
    while (fgets(line, sizeof(line), fp) && total < MAX_GAMES) {
        line[strcspn(line, "\r\n")] = 0;
        parse_csv_line_to_game(line, &all[total]);
        ids[total] = strdup_safe(all[total].App_Id);
        total++;
    }
    fclose(fp);

    PilhaGames pilha;
    startPilha(&pilha);

    // 2. Leitura dos IDs a serem empilhados (até "FIM")
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\r\n")] = 0;
        if (strcmp(line, "FIM") == 0) break;
        for (int i = 0; i < total; i++) {
            if (strcmp(ids[i], line) == 0) {
                empilhar(&pilha, &all[i]);
                break;
            }
        }
    }
    
    // Contador para a saída de remoção (R), inicia em 1
    int contadorR = 1; 

    // 3. Leitura do número de comandos de manipulação
    int nComandos;
    if (scanf("%d", &nComandos) != 1) nComandos = 0; 
    
    // Correção: Consumir o '\n' que ficou no buffer para não atrapalhar o fgets abaixo
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    // 4. Execução dos comandos (II e RI)
    for (int i = 0; i < nComandos; i++) {
        // Leitura da linha completa do comando (mais robusto)
        if (!fgets(line, sizeof(line), stdin)) continue;
        line[strcspn(line, "\r\n")] = 0; 
        
        char comando[4] = "";
        char arg1[64] = "";

        // Parsagem da linha usando sscanf
        int parsed = sscanf(line, "%3s %63s", comando, arg1);

        if (strcmp(comando, "II") == 0 && parsed >= 2) {
            // Insere no Início (Empilha)
            for (int j = 0; j < total; j++) {
                if (strcmp(ids[j], arg1) == 0) {
                    empilhar(&pilha, &all[j]);
                    break;
                }
            }
        } else if (strcmp(comando, "RI") == 0) {
            // Remove do Início (Desempilha)
            if (pilha.top) {
                Node* node = pilha.top;
                pilha.top = node->next;
                pilha.size--;
                
                // SAÍDA DA REMOÇÃO
                printf("(R) %s\n%d\n", node->game.Name, contadorR++); 
                
                // Liberação de memória do nó removido
                free_game_resources(&node->game);
                free(node);
            }
        }
    }

    // 5. Mostrar o estado final da Pilha
    mostrarPilha(&pilha);

    // 6. Limpeza da memória (pilha restante)
    Node* current = pilha.top;
    while(current) {
        Node* next = current->next;
        free_game_resources(&current->game);
        free(current);
        current = next;
    }

    // Libera o array de jogos e ids
    for (int i = 0; i < total; i++) free(ids[i]);
    free(ids);
    free(all);

    return 0;
}