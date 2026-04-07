/*
O Imperador Julio Cesar foi um dos principais nomes do Imperio Romano. Entre suas contribuicoes, temos um algoritmo de criptografia chamado “Ciframento de
Cesar”. Segundo os historiadores, Cesar utilizava esse algoritmo para criptografar as mensagens que enviava aos seus generais durante as batalhas. A ideia basica 
e um simples deslocamento de caracteres. Assim, por exemplo, se a chave utilizada para criptografar as mensagens for 3, todas as ocorrencias do caractere ’a’ 
sao substituıdas pelo caractere ’d’, as do ’b’ por ’e’, e assim sucessivamente. Crie um m´etodo recursivo que recebe uma string como parˆametro e retorna
outra contendo a entrada de forma cifrada. Neste exercıcio, suponha a chave de ciframento tres. Na saıda padrao, para cada linha de entrada, escreva uma linha com 
a mensagem criptografada.
*/


#include <stdio.h>
#include <string.h>

void cifrar(char *mensagem) {
    if (*mensagem == '\0') {
        return;
    }
    char caractereAtual = *mensagem;

    if ((unsigned char)caractereAtual == 231) {
        caractereAtual = 'c';
    } else if ((unsigned char)caractereAtual == 233) {
        caractereAtual = 'e';
    } else if ((unsigned char)caractereAtual == 225 || (unsigned char)caractereAtual == 224 || (unsigned char)caractereAtual == 227) {
        caractereAtual = 'a';
    }
    char caractereNovo = (char)(caractereAtual + 3);
    printf("%c", caractereNovo);
    cifrar(mensagem + 1);
}

int main() {
    char mensagem[1000];

    while (fgets(mensagem, sizeof(mensagem), stdin)) {
        mensagem[strcspn(mensagem, "\n")] = '\0';
        if (strcmp(mensagem, "FIM") == 0) {
            break;
        }

        cifrar(mensagem);
        printf("\n");
    }
}
