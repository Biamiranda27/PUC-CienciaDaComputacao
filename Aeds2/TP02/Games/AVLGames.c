#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE 5000
#define MAX_TOKEN 500
#define LOG_FILE "845860_arvoreAVL.txt"

typedef struct {
    char App_Id[50];
    char Name[300];
    char Release_Date[50];
    char Estimated_Owners[50];
    double Price;
    char Supported_Languages[500];
    int Metacritic_Score;
    double User_Score;
    int Achievements;
    char Publishers[200];
    char Developers[200];
    char Categories[500];
    char Genres[500];
    char Tags[500];
} AVLGames;

typedef struct Node {
    AVLGames game;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

typedef struct {
    Node *root;
    int comparacoes;
} Tree;

int max(int a, int b) { return (a > b ? a : b); }

int height(Node *n) {
    return n ? n->height : 0;
}

int getBalance(Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node* newNode(AVLGames game) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->game = game;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insertRec(Tree *t, Node *node, AVLGames game) {

    if (node == NULL) return newNode(game);

    t->comparacoes++;
    int cmp = strcmp(game.Name, node->game.Name);

    if (cmp < 0)
        node->left = insertRec(t, node->left, game);

    else if (cmp > 0)
        node->right = insertRec(t, node->right, game);

    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && strcmp(game.Name, node->left->game.Name) < 0)
        return rightRotate(node);

    if (balance < -1 && strcmp(game.Name, node->right->game.Name) > 0)
        return leftRotate(node);

    if (balance > 1 && strcmp(game.Name, node->left->game.Name) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && strcmp(game.Name, node->right->game.Name) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void insert(Tree *t, AVLGames game) {
    t->root = insertRec(t, t->root, game);
}


void searchRec(Tree *t, Node *node, char *name) {
    if (node == NULL) {
        printf("NAO\n");
        return;
    }

    t->comparacoes++;
    int cmp = strcmp(name, node->game.Name);

    if (cmp == 0) {
        printf("SIM\n");
        return;
    }

    if (cmp < 0) {
        printf("esq ");
        searchRec(t, node->left, name);
    } else {
        printf("dir ");
        searchRec(t, node->right, name);
    }
}

void searchPrint(Tree *t, char *name) {
    printf("raiz ");
    searchRec(t, t->root, name);
}


void lerCSV(AVLGames *g, char *linha) {
    char temp[MAX_LINE];
    strcpy(temp, linha);

    char *token;
    int coluna = 0;

    char *ptr = temp;

    token = strtok(ptr, ",");
    while (token != NULL && coluna < 14) {

        switch (coluna) {
            case 0: strcpy(g->App_Id, token); break;
            case 1: strcpy(g->Name, token); break;
            case 2: strcpy(g->Release_Date, token); break;
            case 3: strcpy(g->Estimated_Owners, token); break;
            case 4: g->Price = atof(token); break;
            case 5: strcpy(g->Supported_Languages, token); break;
            case 6: g->Metacritic_Score = atoi(token); break;
            case 7: g->User_Score = atof(token); break;
            case 8: g->Achievements = atoi(token); break;
            case 9: strcpy(g->Publishers, token); break;
            case 10: strcpy(g->Developers, token); break;
            case 11: strcpy(g->Categories, token); break;
            case 12: strcpy(g->Genres, token); break;
            case 13: strcpy(g->Tags, token); break;
        }

        token = strtok(NULL, ",");
        coluna++;
    }
}

int main() {

    clock_t inicio = clock();

    Tree arvore;
    arvore.root = NULL;
    arvore.comparacoes = 0;

    FILE *f = fopen("/tmp/games.csv", "r");
    if (!f) {
        printf("Erro abrindo /tmp/games.csv\n");
        return 1;
    }

    char linha[MAX_LINE];
    fgets(linha, MAX_LINE, f); 

    char **map_ids = NULL;
    char **map_linhas = NULL;
    int map_count = 0;

    while (fgets(linha, MAX_LINE, f)) {

        char id[50];
        int i = 0;
        while (linha[i] != ',' && linha[i] != '\0') {
            id[i] = linha[i];
            i++;
        }
        id[i] = '\0';

        map_count++;
        map_ids = realloc(map_ids, map_count * sizeof(char*));
        map_linhas = realloc(map_linhas, map_count * sizeof(char*));

        map_ids[map_count-1] = strdup(id);
        map_linhas[map_count-1] = strdup(linha);
    }
    fclose(f);

    char entrada[300];

    while (1) {
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\r\n")] = 0;

        if (strcmp(entrada, "FIM") == 0) break;

        for (int i = 0; i < map_count; i++) {
            if (strcmp(map_ids[i], entrada) == 0) {

                AVLGames g;
                lerCSV(&g, map_linhas[i]);
                insert(&arvore, g);
                break;
            }
        }
    }

    while (1) {
        if (!fgets(entrada, sizeof(entrada), stdin)) break;

        entrada[strcspn(entrada, "\r\n")] = 0;
        if (strcmp(entrada, "FIM") == 0) break;

        printf("%s: ", entrada);
        searchPrint(&arvore, entrada);
    }

    double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;

    FILE *log = fopen(LOG_FILE, "w");
    fprintf(log, "845860\t%d\t%.3f", arvore.comparacoes, tempo);
    fclose(log);

    return 0;
}
