/*
O Imperador Julio Cesar foi um dos principais nomes do Imperio Romano. Entre suas contribuicoes, temos um algoritmo de criptografia chamado “Ciframento de
Cesar”. Segundo os historiadores, Cesar utilizava esse algoritmo para criptografar as mensagens que enviava aos seus generais durante as batalhas. A ideia basica 
e um simples deslocamento de caracteres. Assim, por exemplo, se a chave utilizada para criptografar as mensagens for 3, todas as ocorrencias do caractere 
’a’ sao substituıdas pelo caractere ’d’, as do ’b’ por ’e’, e assim sucessivamente. Crie um metodo iterativo que recebe uma string como parametro e retorna
outra contendo a entrada de forma cifrada. Neste exercıcio, suponha a chave de ciframento tres. Na saıda padrao, para cada linha de entrada, escreva uma linha com 
a mensagem criptografada.
*/

import java.util.*;

public class CiframentoCesar {

    static String cifrar(String mensagem){
        String novaMensagem = "";
        int n = mensagem.length();
        char caractereAtual;
        char caractereNovo;
        for(int i = 0 ; i < n; i++){
            caractereAtual = mensagem.charAt(i);
            if(caractereAtual == 'ç'){
                caractereAtual = 'c';
            }
            if(caractereAtual == 'é'){
                caractereAtual = 'e';
            }
            if(caractereAtual == 'á' || caractereAtual == 'à' || caractereAtual == 'ã'){
                caractereAtual = 'a';
            }
            caractereNovo = (char) (caractereAtual + 3);
            novaMensagem += caractereNovo;
        }
        return novaMensagem;
    }
        
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String mensagem;

        //System.out.println("digite uma string: ");
        while(scanner.hasNextLine()){
            mensagem = scanner.nextLine();
            if(mensagem.equals("FIM") ){
                break;
            }
            System.out.println(cifrar(mensagem));
        }

        scanner.close();
    }
}

