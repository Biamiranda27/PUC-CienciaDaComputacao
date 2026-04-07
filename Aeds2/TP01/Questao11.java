/*
Crie um metodo recursivo que recebe uma string como parametro e retorna a string invertida. Na saıda padrao, para cada linha de entrada, escreva uma linha de
saıda com a string invertida. Por exemplo, se a entrada for “abcde”, a saıda deve ser “edcba”.
*/


import java.util.Scanner;

public class InvercaoStringR {

    public static void reverso(String string) {
        if (string.length() > 0) {
            reversoRecursivo(string, string.length() - 1);
            System.out.println(); 
        }
    }

    private static void reversoRecursivo(String string, int indice) {
        if (indice >= 0) {
            System.out.print(string.charAt(indice));
            reversoRecursivo(string, indice - 1);
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String string;

        while (scanner.hasNext()) {
            string = scanner.next();
            if (string.equals("FIM")) {
                break;
            }
            reverso(string);
        }
        scanner.close();
    }
}

