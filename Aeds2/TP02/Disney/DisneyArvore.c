#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

typedef struct Show {
    char* showId;
    char* type;
    char* title;
    char* director;
    char** cast;
    int cast_len;
    char* country;
    char* dateAdded;
    int releaseYear;
    char* rating;
    char* duration;
    char** listedIn;
    int listedIn_len;
} Show;

Show* show_create_empty();
void free_show(Show* s);
Show* show_clone(Show* original);
int show_strToInt(const char* str);
char** show_split_and_trim(const char* str, const char* delimiter, int* count);
void show_ler(Show* s, char* in);
Show* show_create_from_string(char* in);
void show_swap(int i, int j, char** array);
void show_quickSort(int esq, int dir, char** array);
Show** show_csv_read(const char* filepath, int* num_shows);
void show_print(Show* s);

typedef struct No {
    Show* show;
    struct No* esq;
    struct No* dir;
    int height; // Adicionado para a AVL
} No;

No* no_create(Show* show);
void free_no_recursive(No* no);

typedef struct ArvoreBinaria { // Renomeado para ArvoreAVL conceitualmente
    No* raiz;
    int comparacoes;
} ArvoreBinaria; // Mantido o nome para consistência com o original, mas agora é AVL

ArvoreBinaria* arvore_create();
void arvore_free(ArvoreBinaria* arvore);

// Funções auxiliares para AVL
int height(No* no);
int max(int a, int b);
int getBalance(No* no);
No* rotateRight(No* y);
No* rotateLeft(No* x);

No* arvore_inserir_recursivo(No* no, Show* show, int* comparacoes);
void arvore_inserir(ArvoreBinaria* arvore, Show* show);
bool arvore_pesquisar_recursivo(No* no, const char* nome, int* comparacoes);
bool arvore_pesquisar(ArvoreBinaria* arvore, const char* nome);

Show* show_create_empty() {
    Show* s = (Show*) malloc(sizeof(Show));
    if (s == NULL) { perror("Erro ao alocar Show"); exit(EXIT_FAILURE); }

    s->showId = NULL;
    s->type = NULL;
    s->title = NULL;
    s->director = NULL;
    s->cast = NULL;
    s->cast_len = 0;
    s->country = NULL;
    s->dateAdded = NULL;
    s->releaseYear = 0;
    s->rating = NULL;
    s->duration = NULL;
    s->listedIn = NULL;
    s->listedIn_len = 0;
    return s;
}

void free_show(Show* s) {
    if (s == NULL) return;

    free(s->showId);
    free(s->type);
    free(s->title);
    free(s->director);

    if (s->cast != NULL) {
        for (int i = 0; i < s->cast_len; i++) {
            free(s->cast[i]);
        }
        free(s->cast);
    }

    free(s->country);
    free(s->dateAdded);
    free(s->rating);
    free(s->duration);

    if (s->listedIn != NULL) {
        for (int i = 0; i < s->listedIn_len; i++) {
            free(s->listedIn[i]);
        }
        free(s->listedIn);
    }
}

Show* show_clone(Show* original) {
    if (original == NULL) return NULL;

    Show* s = show_create_empty();
    if (original->showId) s->showId = strdup(original->showId);
    if (original->type) s->type = strdup(original->type);
    if (original->title) s->title = strdup(original->title);
    if (original->director) s->director = strdup(original->director);

    s->cast_len = original->cast_len;
    if (original->cast) {
        s->cast = (char**)malloc(s->cast_len * sizeof(char*));
        if (s->cast == NULL) { perror("Erro ao alocar cast"); exit(EXIT_FAILURE); }
        for (int i = 0; i < s->cast_len; i++) {
            s->cast[i] = strdup(original->cast[i]);
        }
    }

    if (original->country) s->country = strdup(original->country);
    if (original->dateAdded) s->dateAdded = strdup(original->dateAdded);
    s->releaseYear = original->releaseYear;
    if (original->rating) s->rating = strdup(original->rating);
    if (original->duration) s->duration = strdup(original->duration);

    s->listedIn_len = original->listedIn_len;
    if (original->listedIn) {
        s->listedIn = (char**)malloc(s->listedIn_len * sizeof(char*));
        if (s->listedIn == NULL) { perror("Erro ao alocar listedIn"); exit(EXIT_FAILURE); }
        for (int i = 0; i < s->listedIn_len; i++) {
            s->listedIn[i] = strdup(original->listedIn[i]);
        }
    }
    return s;
}

int show_strToInt(const char* str) {
    int len = strlen(str);
    int data = 0;
    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (c >= '0' && c <= '9') {
            data = (10 * data) + (c - '0');
        }
    }
    return data;
}

void show_set_showId(Show* s, const char* x) {
    if (s->showId) free(s->showId);
    s->showId = strdup((x == NULL || strcmp(x, "") == 0) ? "NaN" : x);
}

void show_set_type(Show* s, const char* x) {
    if (s->type) free(s->type);
    s->type = strdup((x == NULL || strcmp(x, "") == 0) ? "NaN" : x);
}

void show_set_title(Show* s, const char* x) {
    if (s->title) free(s->title);
    s->title = strdup((x == NULL || strcmp(x, "") == 0) ? "NaN" : x);
}

void show_set_director(Show* s, const char* x) {
    if (s->director) free(s->director);
    s->director = strdup((x == NULL || strcmp(x, "") == 0) ? "NaN" : x);
}

void show_set_country(Show* s, const char* x) {
    if (s->country) free(s->country);
    s->country = strdup((x == NULL || strcmp(x, "") == 0) ? "NaN" : x);
}

void show_set_dateAdded(Show* s, const char* x) {
    if (s->dateAdded) free(s->dateAdded);
    s->dateAdded = strdup((x == NULL || strcmp(x, "") == 0) ? "NaN" : x);
}

void show_set_rating(Show* s, const char* x) {
    if (s->rating) free(s->rating);
    s->rating = strdup((x == NULL || strcmp(x, "") == 0) ? "NaN" : x);
}

void show_set_duration(Show* s, const char* x) {
    if (s->duration) free(s->duration);
    s->duration = strdup((x == NULL || strcmp(x, "") == 0) ? "NaN" : x);
}

void show_set_cast(Show* s, char** new_cast, int count) {
    if (s->cast) {
        for (int i = 0; i < s->cast_len; i++) free(s->cast[i]);
        free(s->cast);
    }
    s->cast = NULL;
    s->cast_len = 0;

    if (count == 1 && (new_cast[0] == NULL || strcmp(new_cast[0], "") == 0 || strcmp(new_cast[0], " ") == 0)) {
        s->cast = (char**) malloc(sizeof(char*));
        if (s->cast == NULL) { perror("Erro ao alocar cast para NaN"); exit(EXIT_FAILURE); }
        s->cast[0] = strdup("NaN");
        s->cast_len = 1;
    } else if (count > 0 && new_cast != NULL) {
        s->cast = (char**) malloc(count * sizeof(char*));
        if (s->cast == NULL) { perror("Erro ao alocar cast"); exit(EXIT_FAILURE); }
        for (int i = 0; i < count; i++) {
            s->cast[i] = strdup(new_cast[i]);
        }
        s->cast_len = count;
    }
}

void show_set_listedIn(Show* s, char** new_listedIn, int count) {
    if (s->listedIn) {
        for (int i = 0; i < s->listedIn_len; i++) free(s->listedIn[i]);
        free(s->listedIn);
    }
    s->listedIn = NULL;
    s->listedIn_len = 0;

    if (count == 1 && (new_listedIn[0] == NULL || strcmp(new_listedIn[0], "") == 0 || strcmp(new_listedIn[0], " ") == 0)) {
        s->listedIn = (char**) malloc(sizeof(char*));
        if (s->listedIn == NULL) { perror("Erro ao alocar listedIn para NaN"); exit(EXIT_FAILURE); }
        s->listedIn[0] = strdup("NaN");
        s->listedIn_len = 1;
    } else if (count > 0 && new_listedIn != NULL) {
        s->listedIn = (char**) malloc(count * sizeof(char*));
        if (s->listedIn == NULL) { perror("Erro ao alocar listedIn"); exit(EXIT_FAILURE); }
        for (int i = 0; i < count; i++) {
            s->listedIn[i] = strdup(new_listedIn[i]);
        }
        s->listedIn_len = count;
    }
}


char** show_split_and_trim(const char* str, const char* delimiter, int* count) {
    char* s_copy = strdup(str);
    if (s_copy == NULL) { perror("Erro ao duplicar string para split"); exit(EXIT_FAILURE); }

    char* token;
    char* rest = s_copy;
    char** result = NULL;
    *count = 0;
    int capacity = 4;

    result = (char**) malloc(capacity * sizeof(char*));
    if (result == NULL) { perror("Erro ao alocar array de tokens"); exit(EXIT_FAILURE); }

    char* saveptr;

    token = strtok_r(rest, delimiter, &saveptr);

    while (token != NULL) {
        char* trimmed_token = token;
        while(isspace((unsigned char)*trimmed_token)) trimmed_token++;
        char* end = trimmed_token + strlen(trimmed_token) - 1;
        while(end >= trimmed_token && isspace((unsigned char)*end)) *end-- = '\0';

        if (strlen(trimmed_token) > 0) {
            if (*count >= capacity) {
                capacity *= 2;
                result = (char**) realloc(result, capacity * sizeof(char*));
                if (result == NULL) { perror("Erro ao realocar array de tokens"); exit(EXIT_FAILURE); }
            }
            result[*count] = strdup(trimmed_token);
            if (result[*count] == NULL) { perror("Erro ao duplicar token"); exit(EXIT_FAILURE); }
            (*count)++;
        }

        token = strtok_r(NULL, delimiter, &saveptr);
    }
    free(s_copy);

    if (*count == 0) {
        free(result);
        return NULL;
    }
    result = (char**) realloc(result, (*count) * sizeof(char*));
    if (result == NULL) { perror("Erro ao realocar array final de tokens"); exit(EXIT_FAILURE); }

    return result;
}


void show_ler(Show* s, char* in) {
    char* simplify = (char*) malloc(strlen(in) + 1);
    if (simplify == NULL) { perror("Erro ao alocar simplify"); exit(EXIT_FAILURE); }

    bool in_quotes = false;
    int simplify_idx = 0;
    for (int i = 0; i < strlen(in); i++) {
        char c = in[i];
        if (c == '"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            simplify[simplify_idx++] = '|';
        } else {
            simplify[simplify_idx++] = c;
        }
    }
    simplify[simplify_idx] = '\0';

    char* ShowStr[11];
    int field_idx = 0;
    char* token;
    char* rest = simplify;
    char* saveptr_simplify;

    token = strtok_r(rest, "|", &saveptr_simplify);
    while (token != NULL && field_idx < 11) {
        if (token[0] == '"' && token[strlen(token) - 1] == '"') {
            token[strlen(token) - 1] = '\0';
            token++;
        }
        ShowStr[field_idx++] = token;
        token = strtok_r(NULL, "|", &saveptr_simplify);
    }
    
    for (int i = field_idx; i < 11; i++) {
        ShowStr[i] = "";
    }


    show_set_showId(s, ShowStr[0]);
    show_set_type(s, ShowStr[1]);
    show_set_title(s, ShowStr[2]);
    show_set_director(s, ShowStr[3]);

    int cast_count = 0;
    char** temp_cast = show_split_and_trim(ShowStr[4], ",", &cast_count);
    show_quickSort(0, cast_count - 1, temp_cast);
    show_set_cast(s, temp_cast, cast_count);
    if (temp_cast) {
        for(int i = 0; i < cast_count; i++) free(temp_cast[i]);
        free(temp_cast);
    }

    show_set_country(s, ShowStr[5]);
    show_set_dateAdded(s, ShowStr[6]);
    s->releaseYear = show_strToInt(ShowStr[7]);
    show_set_rating(s, ShowStr[8]);
    show_set_duration(s, ShowStr[9]);

    int listedIn_count = 0;
    char** temp_listedIn = show_split_and_trim(ShowStr[10], ",", &listedIn_count);
    show_quickSort(0, listedIn_count - 1, temp_listedIn);
    show_set_listedIn(s, temp_listedIn, listedIn_count);
    if (temp_listedIn) {
        for(int i = 0; i < listedIn_count; i++) free(temp_listedIn[i]);
        free(temp_listedIn);
    }

    free(simplify);
}

Show* show_create_from_string(char* in) {
    Show* created = show_create_empty();
    show_ler(created, in);
    return created;
}

void show_swap(int i, int j, char** array) {
    if (array == NULL || i == j) return;
    char* temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void show_quickSort(int esq, int dir, char** array) {
    if (array == NULL || esq >= dir)
        return;

    int i = esq, j = dir;
    char* pivo = array[esq + (dir - esq) / 2];

    while (i <= j) {
        while (strcmp(array[i], pivo) < 0)
            i++;
        while (strcmp(array[j], pivo) > 0)
            j--;
        if (i <= j) {
            show_swap(i, j, array);
            i++;
            j--;
        }
    }
    if (esq < j)
        show_quickSort(esq, j, array);
    if (i < dir)
        show_quickSort(i, dir, array);
}

Show** show_csv_read(const char* filepath, int* num_shows) {
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Erro ao abrir arquivo");
        return NULL;
    }

    char line[4096];
    Show** shows = NULL;
    *num_shows = 0;
    int capacity = 10;

    shows = (Show**) malloc(capacity * sizeof(Show*));
    if (shows == NULL) { perror("Erro ao alocar array de shows"); exit(EXIT_FAILURE); }

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        
        if (*num_shows >= capacity) {
            capacity *= 2;
            shows = (Show**) realloc(shows, capacity * sizeof(Show*));
            if (shows == NULL) { perror("Erro ao realocar array de shows"); exit(EXIT_FAILURE); }
        }
        shows[*num_shows] = show_create_from_string(line);
        (*num_shows)++;
    }

    fclose(file);
    return shows;
}

void show_print(Show* s) {
    if (s == NULL) {
        printf("Show nulo\n");
        return;
    }
    printf("ID: %s\n", s->showId ? s->showId : "N/A");
    printf("Tipo: %s\n", s->type ? s->type : "N/A");
    printf("Titulo: %s\n", s->title ? s->title : "N/A");
    printf("Diretor: %s\n", s->director ? s->director : "N/A");
    printf("Elenco: [");
    for (int i = 0; i < s->cast_len; i++) {
        printf("%s%s", s->cast[i] ? s->cast[i] : "N/A", (i < s->cast_len - 1) ? ", " : "");
    }
    printf("]\n");
    printf("Pais: %s\n", s->country ? s->country : "N/A");
    printf("Data Adicionada: %s\n", s->dateAdded ? s->dateAdded : "N/A");
    printf("Ano de Lancamento: %d\n", s->releaseYear);
    printf("Avaliacao: %s\n", s->rating ? s->rating : "N/A");
    printf("Duracao: %s\n", s->duration ? s->duration : "N/A");
    printf("Listado Em: [");
    for (int i = 0; i < s->listedIn_len; i++) {
        printf("%s%s", s->listedIn[i] ? s->listedIn[i] : "N/A", (i < s->listedIn_len - 1) ? ", " : "");
    }
    printf("]\n");
    printf("--------------------------------------\n");
}


No* no_create(Show* show) {
    No* no = (No*) malloc(sizeof(No));
    if (no == NULL) { perror("Erro ao alocar No"); exit(EXIT_FAILURE); }
    no->show = show;
    no->esq = NULL;
    no->dir = NULL;
    no->height = 1; 
    return no;
}

void free_no_recursive(No* no) {
    if (no != NULL) {
        free_no_recursive(no->esq);
        free_no_recursive(no->dir);
        free(no);
    }
}

ArvoreBinaria* arvore_create() {
    ArvoreBinaria* arvore = (ArvoreBinaria*) malloc(sizeof(ArvoreBinaria));
    if (arvore == NULL) { perror("Erro ao alocar ArvoreBinaria"); exit(EXIT_FAILURE); }
    arvore->raiz = NULL;
    arvore->comparacoes = 0;
    return arvore;
}

void arvore_free(ArvoreBinaria* arvore) {
    if (arvore == NULL) return;
    free_no_recursive(arvore->raiz);
    free(arvore);
}


int height(No* no) {
    if (no == NULL)
        return 0;
    return no->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getBalance(No* no) {
    if (no == NULL)
        return 0;
    return height(no->esq) - height(no->dir);
}

No* rotateRight(No* y) {
    No* x = y->esq;
    No* T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->height = 1 + max(height(y->esq), height(y->dir));
    x->height = 1 + max(height(x->esq), height(x->dir));

    return x;
}

No* rotateLeft(No* x) {
    No* y = x->dir;
    No* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->height = 1 + max(height(x->esq), height(x->dir));
    y->height = 1 + max(height(y->esq), height(y->dir));

    return y; 
}

No* arvore_inserir_recursivo(No* no, Show* show, int* comparacoes) {
    if (no == NULL) {
        return no_create(show);
    }

    (*comparacoes)++;
    int cmp = strcmp(show->title, no->show->title);

    if (cmp < 0) {
        no->esq = arvore_inserir_recursivo(no->esq, show, comparacoes);
    } else if (cmp > 0) {
        no->dir = arvore_inserir_recursivo(no->dir, show, comparacoes);
    } else {
        return no; 
    }

    no->height = 1 + max(height(no->esq), height(no->dir));

    int balance = getBalance(no);

    
    if (balance > 1 && strcmp(show->title, no->esq->show->title) < 0) {
        return rotateRight(no);
    }

    if (balance < -1 && strcmp(show->title, no->dir->show->title) > 0) {
        return rotateLeft(no);
    }

    if (balance > 1 && strcmp(show->title, no->esq->show->title) > 0) {
        no->esq = rotateLeft(no->esq);
        return rotateRight(no);
    }

    if (balance < -1 && strcmp(show->title, no->dir->show->title) < 0) {
        no->dir = rotateRight(no->dir);
        return rotateLeft(no);
    }

    return no; 
}

void arvore_inserir(ArvoreBinaria* arvore, Show* show) {
    arvore->raiz = arvore_inserir_recursivo(arvore->raiz, show, &(arvore->comparacoes));
}

bool arvore_pesquisar_recursivo(No* no, const char* nome, int* comparacoes) {
    if (no == NULL) {
        printf("NAO\n");
        return false;
    }
    (*comparacoes)++;
    int cmp = strcmp(nome, no->show->title);
    if (cmp == 0) {
        printf("SIM\n");
        return true;
    } else if (cmp < 0) {
        printf("esq ");
        return arvore_pesquisar_recursivo(no->esq, nome, comparacoes);
    } else {
        printf("dir ");
        return arvore_pesquisar_recursivo(no->dir, nome, comparacoes);
    }
}

bool arvore_pesquisar(ArvoreBinaria* arvore, const char* nome) {
    printf("raiz ");
    return arvore_pesquisar_recursivo(arvore->raiz, nome, &(arvore->comparacoes));
}


int main() {
    clock_t inicio = clock();

    int num_shows = 0;
    Show** lista = show_csv_read("/tmp/disneyplus.csv", &num_shows); 
    if (lista == NULL) {
        fprintf(stderr, "Erro ao carregar o arquivo CSV. Verifique o caminho e as permissoes.\n");
        return EXIT_FAILURE;
    }

    ArvoreBinaria* arvore = arvore_create();
    char entrada[256];

    while (fgets(entrada, sizeof(entrada), stdin) != NULL) {
        entrada[strcspn(entrada, "\n")] = '\0';
        if (strcmp(entrada, "FIM") == 0) {
            break;
        }

        bool found = false;
        for (int i = 0; i < num_shows; i++) {
            if (lista[i] != NULL && lista[i]->showId != NULL && strcmp(lista[i]->showId, entrada) == 0) {
                arvore_inserir(arvore, lista[i]);
                found = true;
                break;
            }
        }
        if (!found) {
        }
    }

    while (fgets(entrada, sizeof(entrada), stdin) != NULL) {
        entrada[strcspn(entrada, "\n")] = '\0';
        if (strcmp(entrada, "FIM") == 0) {
            break;
        }
        arvore_pesquisar(arvore, entrada);
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    FILE* log_file = fopen("845860_arvoreBinaria.txt", "w");
    if (log_file == NULL) {
        perror("Erro ao abrir arquivo de log");
    } else {
        fprintf(log_file, "845860\t%.3f\t%d\n", tempo, arvore->comparacoes);
        fclose(log_file);
    }

    for (int i = 0; i < num_shows; i++) {
        free_show(lista[i]);
        free(lista[i]);
    }
    free(lista);

    arvore_free(arvore);

    return 0;
}
