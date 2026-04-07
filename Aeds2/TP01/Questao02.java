/*
Crie um metodo iterativo que recebe uma string, sorteia duas letras minusculas aleatorias (codigo ASCII ≥’a’ e ≤’z’), substitui todas as ocorrencias da
primeira letra na string pela segunda e retorna a string com as alteracoes efetuadas. Na saıda padrao, para cada linha de entrada, execute o metodo desenvolvido 
nesta questao e mostre a string retornada como uma linha de saıda. Abaixo, observamos um exemplo de entrada supondo que para a primeira linha as letras sorteados 
foram o ’a’ e o ’q’. Para a segunda linha, foram o ’e’ e o ’k’.

EXEMPLO DE ENTRADA: o rato roeu a roupa do rei de roma e qwe qwe qwe ewq ewq ewq FIM´

EXEMPLO DE SAIDA:
o rqto roeu q roupq do rei de romq
k qwk qwk qwk kwq kwq kwq

A classe Random do Java gera numeros (ou letras) aleatorios e o exemplo abaixo mostra uma letra minuscula na tela. Em especial, destacamos que: i) seed e a 
semente para geracao de numeros aleatorios; ii) nesta questao, por causa da correcao automatica, a seed sera quatro; iii) a disciplina de Estatıstica e 
Probabilidade faz uma discussao sobre “aleatorio”.
Random gerador= new Random( ) ;
2 gerador. setSeed ( 4 ) ;
3 System. out. println ( ( char ) (’ a ’ + (Math. abs( gerador. nextInt ( ) ) % 2 6 ) ) ) ;
*/

import java.util.*;


class AlteracaoAleatoria{

    static String trocar(String string, char letra1, char letra2){
        char[] caracteres = string.toCharArray(); //para manipular os caracteres da palavra
        int n = string.length();
        for(int i = 0; i < n; i++){
            if(caracteres[i] == letra1){
                caracteres[i] = letra2;
            }
        }
        return new String(caracteres);

    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String string;
        Random gerador = new Random();
        gerador.setSeed(4);
        //System.out.println("digite a string: ");
        while(scanner.hasNextLine()){
            string = scanner.nextLine();
            if(string.equals("FIM")){
                break;
            }

            char letra1 = ((char)('a' + (Math.abs(gerador.nextInt ()) % 26)));
            char letra2 = ((char)('a' + (Math.abs(gerador.nextInt ()) % 26)));
            System.out.println(trocar(string, letra1, letra2));

        }
        scanner.close();
    }
}

     
    


