/*
Crie um metodo recursivo que recebe um numero inteiro como parametro e retorna a soma de seus dıgitos. Na saıda padrao, para cada linha de entrada, escreva uma 
linha de saıda com o resultado da soma dos dıgitos. Por exemplo, se a entrada for 12345, a saıda deve ser 15.
*/

import java.util.*;
public class SomaDigitosR {

    static int soma(int n){
    if(n == 0){
        return 0;
    } 
    return (n % 10) + soma(n / 10);
}

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String palavra;
        int numero;

        //System.out.println("digite o numero: ");
        while(scanner.hasNextLine()){
            palavra = scanner.nextLine();
            if(palavra.equals("FIM")){
            break;
        }
        numero = Integer.parseInt(palavra);
        System.out.println(soma(numero));
        }
        scanner.close();
    }
}


