#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE 1024
#define MAX_STR 256
#define MAX_SHOWS 1500

typedef struct {
    char id[MAX_STR];
    char tipo[MAX_STR];
    char titulo[MAX_STR];
    char diretor[MAX_STR];
    char elenco[MAX_STR];
    char pais[MAX_STR];
    char data_adicao[MAX_STR];
    int ano_lancamento;
    char classificacao[MAX_STR];
    char duracao[MAX_STR];
    char generos[MAX_STR];
} Programa;

void removerAspas(char *str) {
    char temp[MAX_STR];
    int j = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] != '"') temp[j++] = str[i];
    }
    temp[j] = '\0';
    strcpy(str, temp);
}

void ordenarElenco(char *elenco) {
    if (strcmp(elenco, "NaN") == 0) return;

    char nomes[50][MAX_STR];
    int qtd = 0;

    char *token = strtok(elenco, ",");
    while (token != NULL && qtd < 50) {
        while (*token == ' ') token++;
        removerAspas(token);
        strncpy(nomes[qtd++], token, MAX_STR);
        token = strtok(NULL, ",");
    }

    for (int i = 0; i < qtd - 1; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (strcasecmp(nomes[i], nomes[j]) > 0) {
                char temp[MAX_STR];
                strcpy(temp, nomes[i]);
                strcpy(nomes[i], nomes[j]);
                strcpy(nomes[j], temp);
            }
        }
    }

    elenco[0] = '\0';
    for (int i = 0; i < qtd; i++) {
        strcat(elenco, nomes[i]);
        if (i < qtd - 1) strcat(elenco, ", ");
    }
}

void imprimirPrograma(Programa *p) {
    char dataFormatada[50] = "NaN";
    if (strcmp(p->data_adicao, "NaN") != 0) {
        struct tm tm = {0};
        strptime(p->data_adicao, "%b %d, %Y", &tm);
        strftime(dataFormatada, sizeof(dataFormatada), "%B %e, %Y", &tm);
        for (int i = 0; dataFormatada[i]; i++) {
            if (dataFormatada[i] == ' ' && dataFormatada[i + 1] == ' ')
                memmove(&dataFormatada[i], &dataFormatada[i + 1], strlen(&dataFormatada[i + 1]) + 1);
        }
    }

    char elencoOrdenado[MAX_STR];
    strcpy(elencoOrdenado, p->elenco);
    ordenarElenco(elencoOrdenado);

    printf("=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##\n",
           p->id, p->titulo, p->tipo, p->diretor, elencoOrdenado, p->pais,
           dataFormatada, p->ano_lancamento, p->classificacao, p->duracao, p->generos);
}

int dividirLinhaCSV(const char *linha, char campos[12][MAX_STR]) {
    int i = 0, inQuotes = 0, col = 0, ci = 0;
    char ch;
    while ((ch = linha[i++]) != '\0') {
        if (ch == '"') {
            inQuotes = !inQuotes;
        } else if (ch == ',' && !inQuotes) {
            campos[col][ci] = '\0';
            col++;
            ci = 0;
        } else {
            campos[col][ci++] = ch;
        }
    }
    campos[col][ci] = '\0';
    return col + 1;
}

int buscarProgramaPorID(const char *id, const char *arquivo, Programa *p) {
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    char linha[MAX_LINE];
    fgets(linha, sizeof(linha), fp);

    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\n")] = '\0';
        char campos[12][MAX_STR];
        int qtd = dividirLinhaCSV(linha, campos);
        if (strcmp(campos[0], id) != 0) continue;

        strcpy(p->id, strlen(campos[0]) ? campos[0] : "NaN");
        strcpy(p->tipo, strlen(campos[1]) ? campos[1] : "NaN");
        strcpy(p->titulo, strlen(campos[2]) ? campos[2] : "NaN");
        strcpy(p->diretor, strlen(campos[3]) ? campos[3] : "NaN");
        strcpy(p->elenco, strlen(campos[4]) ? campos[4] : "NaN");
        strcpy(p->pais, strlen(campos[5]) ? campos[5] : "NaN");
        strcpy(p->data_adicao, strlen(campos[6]) ? campos[6] : "NaN");
        p->ano_lancamento = strlen(campos[7]) ? atoi(campos[7]) : -1;
        strcpy(p->classificacao, strlen(campos[8]) ? campos[8] : "NaN");
        strcpy(p->duracao, strlen(campos[9]) ? campos[9] : "NaN");
        strcpy(p->generos, strlen(campos[10]) ? campos[10] : "NaN");

        fclose(fp);
        return 1;
    }

    fclose(fp);
    return 0;
}

int main() {
    char entrada[MAX_STR];
    const char *arquivo = "/tmp/disneyplus.csv";

    while (fgets(entrada, sizeof(entrada), stdin)) {
        entrada[strcspn(entrada, "\n")] = '\0';
        if (strcmp(entrada, "FIM") == 0) break;

        Programa p;
        if (buscarProgramaPorID(entrada, arquivo, &p)) {
            imprimirPrograma(&p);
        } else {
            printf("=> NaN ## NaN ## NaN ## NaN ## [NaN] ## NaN ## NaN ## -1 ## NaN ## NaN ## [NaN] ##\n");
        }
    }

    return 0;
}
