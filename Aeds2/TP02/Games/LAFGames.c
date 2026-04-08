#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#define MAX_LINE_LENGTH 4096
#define MAX_GAMES 20000
#define MAX_LIST 1000
#define MAX_TOKENS 50

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

typedef struct {
    Game array[MAX_LIST];
    int n;
} ListaGames;


void trim_inplace(char* s) {
    if (!s) return;
    int i = 0;
    while (isspace((unsigned char)s[i])) i++;
    int j = 0;
    while (s[i]) s[j++] = s[i++];
    s[j] = '\0';
    j--;
    while (j >= 0 && isspace((unsigned char)s[j--])) s[j] = '\0';
}

char* strdup_safe(const char* s) {
    if (!s) return NULL;
    char* r = malloc(strlen(s) + 1);
    strcpy(r, s);
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
    while (*start == ' ' || *start == '\t') start++;
    if (*start == '[') start++;
    char* end = tmp + strlen(tmp) - 1;
    while (end > start && (*end == ' ' || *end == '\t')) end--;
    if (*end == ']') *end = '\0';
    for (char* p = start; *p; p++) if (*p == '\'' || *p == '\"') *p = ' ';
    char* tok = strtok(start, ",");
    while (tok && arr->count < MAX_TOKENS) {
        while (*tok && isspace((unsigned char)*tok)) tok++;
        char *q = tok + strlen(tok) - 1;
        while (q >= tok && isspace((unsigned char)*q)) { *q = '\0'; q--; }
        arr->elements[arr->count++] = strdup_safe(tok);
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
    for (int i = 0; tmp[i] != '\0' && part < 14; i++) {
        char c = tmp[i];
        if (c == '"') { inQuotes = !inQuotes; continue; }
        if (c == ',' && !inQuotes) {
            parts[part][idx] = '\0';
            part++;
            idx = 0;
            continue;
        }
        parts[part][idx++] = c;
    }
    parts[part][idx] = '\0';
    for (int i = 0; i <= part; i++) trim_inplace(parts[i]);
    for (int i = part + 1; i < 14; i++) strcpy(parts[i], "NaN");

    strcpy(g->App_Id, strlen(parts[0]) ? parts[0] : "NaN");
    strcpy(g->Name, strlen(parts[1]) ? parts[1] : "NaN");

    // DATA
    if (strlen(parts[2]) && strcmp(parts[2],"NaN")!=0) {
        struct tm tm_date = {0};
        if (strptime(parts[2], "%b %d, %Y", &tm_date) != NULL) {
            strftime(g->Release_Date, sizeof(g->Release_Date), "%d/%m/%Y", &tm_date);
        } else strcpy(g->Release_Date, "NaN");
    } else strcpy(g->Release_Date, "NaN");

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
    for (int i = 0; i < src->Supported_Languages.count; i++)
        dest->Supported_Languages.elements[i] = strdup_safe(src->Supported_Languages.elements[i]);
    dest->Supported_Languages.count = src->Supported_Languages.count;
    for (int i = 0; i < src->Categories.count; i++)
        dest->Categories.elements[i] = strdup_safe(src->Categories.elements[i]);
    dest->Categories.count = src->Categories.count;
    for (int i = 0; i < src->Genres.count; i++)
        dest->Genres.elements[i] = strdup_safe(src->Genres.elements[i]);
    dest->Genres.count = src->Genres.count;
    for (int i = 0; i < src->Tags.count; i++)
        dest->Tags.elements[i] = strdup_safe(src->Tags.elements[i]);
    dest->Tags.count = src->Tags.count;
}

void free_game_resources(Game* g) {
    for (int i = 0; i < g->Supported_Languages.count; i++) free(g->Supported_Languages.elements[i]);
    for (int i = 0; i < g->Categories.count; i++) free(g->Categories.elements[i]);
    for (int i = 0; i < g->Genres.count; i++) free(g->Genres.elements[i]);
    for (int i = 0; i < g->Tags.count; i++) free(g->Tags.elements[i]);
}


void startLista(ListaGames* lista) { lista->n = 0; }
void inserirFim(ListaGames* lista, const Game* g) { clone_game(&lista->array[lista->n++], g); }
void inserirInicio(ListaGames* lista, const Game* g) {
    for (int i = lista->n; i > 0; i--) lista->array[i] = lista->array[i-1];
    clone_game(&lista->array[0], g);
    lista->n++;
}
void inserirPos(ListaGames* lista, const Game* g, int pos) {
    for (int i = lista->n; i > pos; i--) lista->array[i] = lista->array[i-1];
    clone_game(&lista->array[pos], g);
    lista->n++;
}
Game removerInicio(ListaGames* lista) {
    Game g = lista->array[0];
    for (int i = 0; i < lista->n-1; i++) lista->array[i] = lista->array[i+1];
    lista->n--;
    return g;
}
Game removerFim(ListaGames* lista) { lista->n--; return lista->array[lista->n]; }
Game removerPos(ListaGames* lista, int pos) {
    Game g = lista->array[pos];
    for (int i = pos; i < lista->n-1; i++) lista->array[i] = lista->array[i+1];
    lista->n--;
    return g;
}


void print_string_array_exact(const StringArray* a) {
    printf("[");
    for (int i = 0; i < a->count; i++) {
        printf("%s", a->elements[i]);
        if (i < a->count - 1) printf(", ");
    }
    printf("]");
}

void imprimirGame_exact(const Game* g, int index) {
    printf("[%d] => %s ## %s ## %s ## %s ## %.2f ## ",
           index, g->App_Id, g->Name, g->Release_Date, g->Estimated_Owners, g->Price);
    print_string_array_exact(&g->Supported_Languages);
    printf(" ## %d ## %.1f ## %d ## [%s] ## [%s] ## ",
           g->Metacritic_Score, g->User_Score, g->Achievements, g->Publishers, g->Developers);
    print_string_array_exact(&g->Categories); printf(" ## ");
    print_string_array_exact(&g->Genres); printf(" ## ");
    print_string_array_exact(&g->Tags); printf(" ##\n");
}

void mostrar_exact(ListaGames* lista) {
    for (int i = 0; i < lista->n; i++) {
        imprimirGame_exact(&lista->array[i], i);
    }
}


int main() {
    FILE* fp = fopen("/tmp/games.csv", "r");
    if (!fp) return 1;

    char line[MAX_LINE_LENGTH];
    if (!fgets(line, sizeof(line), fp)) { fclose(fp); return 1; }

    Game* all = malloc(MAX_GAMES * sizeof(Game));
    char** ids = malloc(MAX_GAMES * sizeof(char*));
    int total = 0;

    while (fgets(line, sizeof(line), fp) && total < MAX_GAMES) {
        line[strcspn(line, "\r\n")] = 0;
        parse_csv_line_to_game(line, &all[total]);
        ids[total] = strdup_safe(all[total].App_Id);
        total++;
    }
    fclose(fp);

    ListaGames lista;
    startLista(&lista);

    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\r\n")] = 0;
        if (strcmp(line, "FIM") == 0) break;
        for (int i = 0; i < total; i++) {
            if (strcmp(ids[i], line) == 0) {
                inserirFim(&lista, &all[i]);
                break;
            }
        }
    }

    int nComandos;
    scanf("%d\n", &nComandos);
    for (int i = 0; i < nComandos; i++) {
        char comando[4], arg1[64];
        int pos;
        scanf("%s", comando);
        if (strcmp(comando, "II") == 0) {
            scanf("%s", arg1);
            for (int j = 0; j < total; j++) if (strcmp(ids[j], arg1) == 0) inserirInicio(&lista, &all[j]);
        } else if (strcmp(comando, "IF") == 0) {
            scanf("%s", arg1);
            for (int j = 0; j < total; j++) if (strcmp(ids[j], arg1) == 0) inserirFim(&lista, &all[j]);
        } else if (strcmp(comando, "I*") == 0) {
            scanf("%d %s", &pos, arg1);
            for (int j = 0; j < total; j++) if (strcmp(ids[j], arg1) == 0) inserirPos(&lista, &all[j], pos);
        } else if (strcmp(comando, "RI") == 0) {
            Game g = removerInicio(&lista);
            printf("(R) %s\n", g.Name);
        } else if (strcmp(comando, "RF") == 0) {
            Game g = removerFim(&lista);
            printf("(R) %s\n", g.Name);
        } else if (strcmp(comando, "R*") == 0) {
            scanf("%d", &pos);
            Game g = removerPos(&lista, pos);
            printf("(R) %s\n", g.Name);
        }
    }

    mostrar_exact(&lista);

    for (int i = 0; i < total; i++) free_game_resources(&all[i]);
    for (int i = 0; i < total; i++) free(ids[i]);
    free(ids);
    free(all);

    return 0;
}
