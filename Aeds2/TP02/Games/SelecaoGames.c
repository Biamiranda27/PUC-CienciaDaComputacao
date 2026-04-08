/*Usando vetores, implemente o algoritmo de ordenação por seleção (Selection Sort) considerando que a chave de pesquisa é o atributo Name.

Entrada e saída padrão são iguais às da primeira questão.
Saída: os registros ordenados pelo atributo Name.
Além disso, crie um arquivo de log na pasta corrente com o nome suamatricula_selecao.txt, contendo uma única linha com:

Sua matrícula
Número de comparações (entre elementos do array)
Número de movimentações (entre elementos do array)
Tempo de execução do algoritmo de ordenação



 Todas as informações do arquivo de log devem ser separadas por uma tabulação (\t).*/

 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#define MAX_LINE_LENGTH 2048

typedef struct {
    int day;
    int month;
    int year;
    bool isValid;
} ReleaseDate;

typedef struct {
    char** elements;
    int count;
} StringArray;

void freeStringArray(StringArray* arr) {
    if (arr) {
        for (int i = 0; i < arr->count; i++) free(arr->elements[i]);
        free(arr->elements);
        arr->elements = NULL;
        arr->count = 0;
    }
}

StringArray cloneStringArray(const StringArray* original) {
    StringArray newArray = {NULL, 0};
    if (original && original->elements) {
        newArray.count = original->count;
        newArray.elements = (char**)malloc(newArray.count * sizeof(char*));
        for (int i = 0; i < newArray.count; i++) newArray.elements[i] = strdup(original->elements[i]);
    }
    return newArray;
}

void printStringArray(const StringArray* arr) {
    if (arr == NULL || arr->count == 0 || (arr->count == 1 && strcmp(arr->elements[0], "NaN") == 0)) {
        printf("[NaN]");
        return;
    }
    printf("[");
    for (int i = 0; i < arr->count; i++) {
        char *temp = strdup(arr->elements[i]);
        int len = strlen(temp), start = 0, end = len - 1;
        while(start < len && isspace((unsigned char)temp[start])) start++;
        while(end >= 0 && isspace((unsigned char)temp[end])) end--;
        if (start <= end) {
            temp[end + 1] = '\0';
            printf("%s%s", temp + start, (i < arr->count - 1) ? ", " : "");
        }
        free(temp);
    }
    printf("]");
}

typedef struct {
    char* App_Id;
    char* Name;
    ReleaseDate Release_Date;
    char* Estimated_Owners;
    double Price;
    StringArray Supported_Languages;
    int Metacritic_Score;
    double User_Score;
    int Achievements;
    char* Publishers;
    char* Developers;
    StringArray Categories;
    StringArray Genres;
    StringArray Tags;
} Games;

void Games_init(Games* game) {
    game->App_Id = strdup("NaN");
    game->Name = strdup("NaN");
    game->Release_Date = (ReleaseDate){0, 0, 0, false};
    game->Estimated_Owners = strdup("NaN");
    game->Price = 0.0;
    game->Supported_Languages = (StringArray){(char**)malloc(sizeof(char*)), 1};
    game->Supported_Languages.elements[0] = strdup("NaN");
    game->Metacritic_Score = -1;
    game->User_Score = -1.0;
    game->Achievements = 0;
    game->Publishers = strdup("NaN");
    game->Developers = strdup("NaN");
    game->Categories = (StringArray){(char**)malloc(sizeof(char*)), 1};
    game->Categories.elements[0] = strdup("NaN");
    game->Genres = (StringArray){(char**)malloc(sizeof(char*)), 1};
    game->Genres.elements[0] = strdup("NaN");
    game->Tags = (StringArray){(char**)malloc(sizeof(char*)), 1};
    game->Tags.elements[0] = strdup("NaN");
}

void Games_free(Games* game) {
    free(game->App_Id);
    free(game->Name);
    free(game->Estimated_Owners);
    freeStringArray(&game->Supported_Languages);
    free(game->Publishers);
    free(game->Developers);
    freeStringArray(&game->Categories);
    freeStringArray(&game->Genres);
    freeStringArray(&game->Tags);
}

Games Games_clone(const Games* original) {
    Games newGame;
    newGame.Price = original->Price;
    newGame.Release_Date = original->Release_Date;
    newGame.Metacritic_Score = original->Metacritic_Score;
    newGame.User_Score = original->User_Score;
    newGame.Achievements = original->Achievements;
    newGame.App_Id = strdup(original->App_Id);
    newGame.Name = strdup(original->Name);
    newGame.Estimated_Owners = strdup(original->Estimated_Owners);
    newGame.Publishers = strdup(original->Publishers);
    newGame.Developers = strdup(original->Developers);
    newGame.Supported_Languages = cloneStringArray(&original->Supported_Languages);
    newGame.Categories = cloneStringArray(&original->Categories);
    newGame.Genres = cloneStringArray(&original->Genres);
    newGame.Tags = cloneStringArray(&original->Tags);
    return newGame;
}

char* clean_field(char* field) {
    if (!field) return field;
    while (isspace((unsigned char)*field)) field++;
    char *end = field + strlen(field) - 1;
    while (end > field && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
    if (field[0] == '"' && field[strlen(field) - 1] == '"') {
        field++;
        field[strlen(field) - 1] = 0;
    }
    return field;
}

StringArray parseStringArray(char* data, const char* delimiter) {
    StringArray arr = {NULL, 0};
    if (!data || strcmp(data, "NaN") == 0 || strlen(data) == 0) {
        arr.count = 1;
        arr.elements = (char**)malloc(sizeof(char*));
        arr.elements[0] = strdup("NaN");
        return arr;
    }
    char* working_data = strdup(data);
    if (working_data[0] == '[' && working_data[strlen(working_data)-1] == ']') {
        working_data[strlen(working_data)-1] = '\0';
        memmove(working_data, working_data + 1, strlen(working_data));
    }
    for (size_t i = 0; i < strlen(working_data); i++)
        if (working_data[i] == '\'') working_data[i] = ' ';
    char* temp = strdup(working_data);
    char* token = strtok(temp, delimiter);
    while (token != NULL) { arr.count++; token = strtok(NULL, delimiter); }
    free(temp);
    arr.elements = (char**)malloc(arr.count * sizeof(char*));
    int i = 0;
    char* saveptr;
    token = strtok_r(working_data, delimiter, &saveptr);
    while (token != NULL) {
        while (isspace((unsigned char)*token)) token++;
        char* end = token + strlen(token) - 1;
        while (end > token && isspace((unsigned char)*end)) end--;
        end[1] = '\0';
        arr.elements[i++] = strdup(token);
        token = strtok_r(NULL, delimiter, &saveptr);
    }
    free(working_data);
    return arr;
}

ReleaseDate parseDate(const char* dateStr) {
    ReleaseDate date = {0, 0, 0, false};
    if (dateStr == NULL || strcmp(dateStr, "NaN") == 0) return date;
    struct tm tm;
    if (strptime(dateStr, "%b %d, %Y", &tm) != NULL) {
        date.day = tm.tm_mday;
        date.month = tm.tm_mon + 1;
        date.year = tm.tm_year + 1900;
        date.isValid = true;
    }
    return date;
}

void Games_lerCSV(Games* game, char* linha) {
    Games_free(game);
    Games_init(game);
    char* fields[14];
    for(int i = 0; i < 14; i++) fields[i] = "NaN";
    char* line_copy = strdup(linha);
    char* current = line_copy;
    for (int i = 0; i < 14 && current != NULL; i++) {
        char* start = current;
        char* end = NULL;
        bool in_quotes = false;
        while (*current != '\0') {
            if (*current == '"') in_quotes = !in_quotes;
            else if (*current == ',' && !in_quotes) { end = current; break; }
            current++;
        }
        if (end != NULL) {
            *end = '\0';
            fields[i] = clean_field(start);
            current = end + 1;
        } else {
            fields[i] = clean_field(start);
            current = NULL;
        }
    }
    free(game->App_Id); game->App_Id = strdup(fields[0]);
    free(game->Name); game->Name = strdup(fields[1]);
    game->Release_Date = parseDate(fields[2]);
    free(game->Estimated_Owners); game->Estimated_Owners = strdup(fields[3]);
    game->Price = (strcmp(fields[4], "NaN") == 0) ? 0.0 : atof(fields[4]);
    freeStringArray(&game->Supported_Languages);
    game->Supported_Languages = parseStringArray(fields[5], ",");
    game->Metacritic_Score = (strcmp(fields[6], "NaN") == 0) ? -1 : atoi(fields[6]);
    game->User_Score = (strcmp(fields[7], "NaN") == 0) ? -1.0 : atof(fields[7]);
    game->Achievements = (strcmp(fields[8], "NaN") == 0) ? 0 : atoi(fields[8]);
    free(game->Publishers); game->Publishers = strdup(fields[9]);
    free(game->Developers); game->Developers = strdup(fields[10]);
    freeStringArray(&game->Categories); game->Categories = parseStringArray(fields[11], ",");
    freeStringArray(&game->Genres); game->Genres = parseStringArray(fields[12], ",");
    freeStringArray(&game->Tags); game->Tags = parseStringArray(fields[13], ",");
    free(line_copy);
}

void Games_imprimirCSV(const Games* game) {
    printf("=> %s ## %s ## ", game->App_Id, game->Name);
    if (game->Release_Date.isValid) printf("%02d/%02d/%d ## ", game->Release_Date.day, game->Release_Date.month, game->Release_Date.year);
    else printf("NaN ## ");
    printf("%s ## %.1f ## ", game->Estimated_Owners, game->Price);
    printStringArray(&game->Supported_Languages);
    printf(" ## %d ## %.1f ## %d ## [%s] ## [%s] ## ", game->Metacritic_Score, game->User_Score, game->Achievements, game->Publishers, game->Developers);
    printStringArray(&game->Categories);
    printf(" ## ");
    printStringArray(&game->Genres);
    printf(" ## ");
    printStringArray(&game->Tags);
    printf(" ##\n");
}

typedef struct {
    char* id;
    char* line;
} CSVRecord;

CSVRecord* ArquivoCSV = NULL;
int csv_count = 0;
long comparacoes = 0, movimentacoes = 0;

char* find_line_by_id(const char* id) {
    for (int i = 0; i < csv_count; i++) if (strcmp(ArquivoCSV[i].id, id) == 0) return ArquivoCSV[i].line;
    return NULL;
}

void selecao(Games* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (strcmp(arr[j].Name, arr[min].Name) < 0)
                min = j;
        }
        if (min != i) {
            Games temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
            movimentacoes += 3;
        }
    }
}

int main() {
    FILE* file = fopen("/tmp/games.csv", "r");
    if (file == NULL) return 1;
    char buffer[MAX_LINE_LENGTH];
    fgets(buffer, MAX_LINE_LENGTH, file);
    long initial_pos = ftell(file);
    int line_count = 0;
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) line_count++;
    fseek(file, initial_pos, SEEK_SET);
    ArquivoCSV = (CSVRecord*)malloc(line_count * sizeof(CSVRecord));
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
        char* line_copy = strdup(buffer);
        char* id = strdup(line_copy);
        char* comma = strchr(id, ',');
        if (comma) *comma = '\0';
        size_t len = strlen(line_copy);
        if (len > 0 && line_copy[len - 1] == '\n') line_copy[len - 1] = '\0';
        ArquivoCSV[csv_count].id = id;
        ArquivoCSV[csv_count].line = line_copy;
        csv_count++;
    }
    fclose(file);

    char input[100];
    Games games[1000];
    int count = 0;
    while (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        if (strcmp(input, "FIM") == 0) break;
        char* csv_line = find_line_by_id(input);
        if (csv_line) {
            Games_init(&games[count]);
            Games_lerCSV(&games[count], csv_line);
            count++;
        }
    }

    clock_t start = clock();
    selecao(games, count);
    clock_t end = clock();
    double tempo = (double)(end - start) / CLOCKS_PER_SEC;

    for (int i = 0; i < count; i++) Games_imprimirCSV(&games[i]);

    FILE* log = fopen("845860_selecao.txt", "w");
    fprintf(log, "845860\t%ld\t%ld\t%.3f\n", comparacoes, movimentacoes, tempo);
    fclose(log);

    for (int i = 0; i < count; i++) Games_free(&games[i]);
    for (int i = 0; i < csv_count; i++) { free(ArquivoCSV[i].id); free(ArquivoCSV[i].line); }
    free(ArquivoCSV);
    return 0;
}
