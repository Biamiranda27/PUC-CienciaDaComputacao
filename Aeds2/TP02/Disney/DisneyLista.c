#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_LINE_LEN 1024
#define MAX_FIELDS 12

typedef struct {
    char *show_id;
    char *type;
    char *title;
    char *director;

    char **cast;   
    int cast_count;

    char *country;

    char date_added[32]; 
    int release_year;

    char *rating;
    char *duration;

    char **listed_in;  
    int listed_in_count;
} Show;

void free_show(Show *s);
void print_show(const Show *s);
int parse_csv_line(const char *line, char fields[MAX_FIELDS][MAX_LINE_LEN]);
void parse_show(Show *s, char fields[MAX_FIELDS][MAX_LINE_LEN]);
char **split_and_trim(const char *str, int *count);
void free_string_array(char **arr, int count);
int equals_str(const char *a, const char *b);

int main() {
    char input_id[100];
    char **ids = NULL;
    int id_count = 0;

    while (1) {
        if (!fgets(input_id, sizeof(input_id), stdin)) break;

        input_id[strcspn(input_id, "\r\n")] = 0;
        if (strcmp(input_id, "FIM") == 0) break;

        ids = realloc(ids, sizeof(char*) * (id_count + 1));
        ids[id_count] = strdup(input_id);
        id_count++;
    }

    FILE *file = fopen("/tmp/disneyplus.csv", "r");
    if (!file) {
        fprintf(stderr, "Arquivo não encontrado\n");

        for (int i = 0; i < id_count; i++) free(ids[i]);
        free(ids);
        return 1;
    }

    char line[MAX_LINE_LEN];
    if (!fgets(line, sizeof(line), file)) {
        fprintf(stderr, "Arquivo vazio\n");
        fclose(file);
        for (int i = 0; i < id_count; i++) free(ids[i]);
        free(ids);
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {

        line[strcspn(line, "\r\n")] = 0;

        char fields[MAX_FIELDS][MAX_LINE_LEN];
        if (!parse_csv_line(line, fields)) {
            continue;
        }

        for (int i = 0; i < id_count; i++) {
            if (strcmp(ids[i], fields[0]) == 0) {
                Show s = {0};
                parse_show(&s, fields);
                print_show(&s);
                free_show(&s);
                break;
            }
        }
    }

    fclose(file);

    for (int i = 0; i < id_count; i++) free(ids[i]);
    free(ids);

    return 0;
}

void free_show(Show *s) {
    if (s->show_id) free(s->show_id);
    if (s->type) free(s->type);
    if (s->title) free(s->title);
    if (s->director) free(s->director);
    free_string_array(s->cast, s->cast_count);
    if (s->country) free(s->country);
    if (s->rating) free(s->rating);
    if (s->duration) free(s->duration);
    free_string_array(s->listed_in, s->listed_in_count);
}

void print_show(const Show *s) {
    printf("=> %s ## %s ## %s ## %s ## [", s->show_id, s->title, s->type, s->director);
    for (int i = 0; i < s->cast_count; i++) {
        printf("%s", s->cast[i]);
        if (i < s->cast_count - 1) printf(", ");
    }
    printf("] ## %s ## %s ## %d ## %s ## %s ## [", s->country, s->date_added, s->release_year, s->rating, s->duration);
    for (int i = 0; i < s->listed_in_count; i++) {
        printf("%s", s->listed_in[i]);
        if (i < s->listed_in_count - 1) printf(", ");
    }
    printf("] ##\n");
}

int parse_csv_line(const char *line, char fields[MAX_FIELDS][MAX_LINE_LEN]) {
    int field_idx = 0;
    int i = 0, j = 0;
    int in_quotes = 0;
    char curr_field[MAX_LINE_LEN] = {0};

    while (*line) {
        char c = *line;
        if (c == '"') {
            in_quotes = !in_quotes;
        }
        else if (c == ',' && !in_quotes) {
            curr_field[j] = '\0';
            if (field_idx >= MAX_FIELDS) return 0; 
            strcpy(fields[field_idx], curr_field);
            field_idx++;
            j = 0;
            curr_field[0] = '\0';
        } else {
            curr_field[j++] = c;
            if (j >= MAX_LINE_LEN - 1) j = MAX_LINE_LEN - 1;
        }
        line++;
    }
    curr_field[j] = '\0';
    if (field_idx >= MAX_FIELDS) return 0;
    strcpy(fields[field_idx], curr_field);
    field_idx++;

    while (field_idx < MAX_FIELDS) {
        strcpy(fields[field_idx], "NaN");
        field_idx++;
    }

    return 1;
}

void trim(char *str) {

    char *start = str;
    while(isspace((unsigned char)*start)) start++;

    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) *end-- = '\0';
}

char **split_and_trim(const char *str, int *count) {
    char *copy = strdup(str);
    char *token;
    char **result = NULL;
    int n = 0;

    if (strlen(copy) == 0 || strcmp(copy, "NaN") == 0) {
        *count = 0;
        free(copy);
        return NULL;
    }

    token = strtok(copy, ",");
    while (token) {
        char *trimmed = strdup(token);
        trim(trimmed);
        result = realloc(result, sizeof(char*) * (n + 1));
        result[n++] = trimmed;
        token = strtok(NULL, ",");
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(result[i], result[j]) > 0) {
                char *temp = result[i];
                result[i] = result[j];
                result[j] = temp;
            }
        }
    }
    *count = n;
    free(copy);
    return result;
}

void free_string_array(char **arr, int count) {
    if (!arr) return;
    for (int i = 0; i < count; i++) {
        free(arr[i]);
    }
    free(arr);
}

int equals_str(const char *a, const char *b) {
    if (a == NULL && b == NULL) return 1;
    if (a == NULL || b == NULL) return 0;
    return strcmp(a, b) == 0;
}

void parse_show(Show *s, char fields[MAX_FIELDS][MAX_LINE_LEN]) {

#define ASSIGN_OR_DEFAULT(dest, src) \
    do { \
        if (equals_str(src, "NaN") || strlen(src) == 0) dest = strdup("NaN"); \
        else dest = strdup(src); \
    } while (0)

    ASSIGN_OR_DEFAULT(s->show_id, fields[0]);
    ASSIGN_OR_DEFAULT(s->type, fields[1]);
    ASSIGN_OR_DEFAULT(s->title, fields[2]);
    ASSIGN_OR_DEFAULT(s->director, fields[3]);

    s->cast = split_and_trim(fields[4], &s->cast_count);
    ASSIGN_OR_DEFAULT(s->country, fields[5]);


    if (equals_str(fields[6], "NaN") || strlen(fields[6]) == 0) {
        strncpy(s->date_added, "March 1, 1900", sizeof(s->date_added));
    } else {
        strncpy(s->date_added, fields[6], sizeof(s->date_added));
    }
    s->date_added[sizeof(s->date_added)-1] = '\0';

    // release_year
    s->release_year = 0;
    if (!equals_str(fields[7], "NaN") && strlen(fields[7]) > 0) {
        s->release_year = atoi(fields[7]);
    }

    ASSIGN_OR_DEFAULT(s->rating, fields[8]);
    ASSIGN_OR_DEFAULT(s->duration, fields[9]);

    s->listed_in = split_and_trim(fields[10], &s->listed_in_count);
}


