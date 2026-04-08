#include <stdio.h>
#include <ctype.h>

int main() {
    char resultado_jogos[6];
    int vitorias = 0;


    for (int i = 0; i < 6; i++) {
        char input;
        do {
            scanf(" %c", &input);
            input = toupper(input);
            if (input != 'V' && input != 'P') {
                printf("Entrada inv�lida. Por favor, insira 'V' para vit�ria ou 'P' para derrota.\n");
            }
        } while (input != 'V' && input != 'P');

        resultado_jogos[i] = input;
        if (input == 'V')
            vitorias++;
    }


    int grupo;
    if (vitorias >= 5)
        grupo = 1;
    else if (vitorias >= 3)
        grupo = 2;
    else if (vitorias >= 1)
        grupo = 3;
    else
        grupo = -1;


    printf("%d\n", grupo);

    return 0;
}
