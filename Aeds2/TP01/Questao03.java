/*
Crie um metodo iterativo que recebe uma string e retorna true se a mesma e composta somente por vogais. Crie outro metodo iterativo que recebe uma string e 
retorna true se a mesma e composta somente por consoantes. Crie um terceiro metodo iterativo que recebe uma string e retorna true se a mesma corresponde a um 
numero inteiro. Crie um quarto metodo iterativo que recebe uma string e retorna true se a mesma corresponde a um numero real. Na saıda padrao, para cada linha 
de entrada, escreva outra de saıda da seguinte forma X1 X2 X3 X4 onde cada Xi e um booleano indicando se a e entrada e: composta somente por vogais (X1);
4. 5. 6. 7. 8. 9. 10. 11. 12. composta somente somente por consoantes (X2); um numero inteiro (X3); um numero real (X4). Se Xi for verdadeiro, seu valor ser a 
SIM, caso contrario, NAO.
*/

import java.util.*;
public class Is {
    static boolean vogal(String frase){
        boolean resp = false;
        int n = frase.length();
        int count = 0;
        for(int i = 0; i < n; i++){
            char c = Character.toLowerCase(frase.charAt(i));
            if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
                count++;
            }
        }
        if(count == n){
            resp = true;
        }
        return resp;
    }
    static boolean consoante(String frase){
        boolean resp = false;
        int n = frase.length();
        int count = 0;
        for(int i = 0; i < n; i++){
            char c = Character.toLowerCase(frase.charAt(i));
            if(!(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') && (c >= 'a' && c <= 'z')){
                count++;
            }
        }
        if(count == n){
            resp = true;
        }
        return resp;
    }
    static boolean inteiro(String frase){
        boolean resp = false;
        int n = frase.length();
        int count = 0;
        for(int i = 0; i < n; i++){
            char c = frase.charAt(i);
            if(c >= '0' && c <= '9'){
                count++;
            }
        }
        if(count == n){
            resp = true;
        }
        return resp;
    }
    static boolean real(String frase){
        boolean resp = false;
        int n = frase.length();
        int count = 0;
        for(int i = 0; i < n; i++){
            char c = frase.charAt(i);
            if(c <= '0' && c <= '9'){
                continue;
            } else if(c == ',' || c == '.'){
                count++;
            }
        }
        if(count == n){
            resp = true;
        }
        return resp;
    }


    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String palavra;
        //System.out.println("digite uma palavra: ");
        while(scanner.hasNextLine()){
        palavra = scanner.nextLine();
        if(palavra.equals("FIM")){
            break;
        }
        
        if(vogal(palavra) == true){
            System.out.print("SIM ");
        } else{
            System.out.print("NAO ");
        }
        if(consoante(palavra) == true){
            System.out.print("SIM ");
        } else{
            System.out.print("NAO ");
        }
        if(inteiro(palavra) == true){
            System.out.print("SIM ");
        } else{
            System.out.print("NAO ");
        }
        if(real(palavra) == true){
            System.out.println("SIM ");
        } else{
            System.out.println("NAO ");
        }
    }
        scanner.close();
    
}
}
