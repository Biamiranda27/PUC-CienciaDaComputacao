/*
Crie um metodo iterativo que recebe uma string como parametro e retorna true se a string e uma senha valida, ou false caso contrario. Uma senha e considerada
valida se contem pelo menos 8 caracteres, incluindo pelo menos uma letra maiuscula, uma letra minuscula, um numero e um caractere especial 
(por exemplo, !, @, #, etc.). Na saıda padrao, para cada linha de entrada, escreva uma linha de saıda com SIM/NAO indicando se a senha e valida. Por exemplo, 
se a entrada for “Senha123!”s, a saıda deve ser SIM.
*/

import java.util.*;

public class ValidacaoSenha {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String senha;
        //System.out.println("digite a senha: ");
        while(scanner.hasNextLine()){
            senha = scanner.nextLine();
            if(senha.equals("FIM")){
                break;
            }
        boolean tamanho = true;
        boolean maiusculo = false;
        boolean minusculo = false;
        boolean numero = false;
        boolean especial = false;
        if(senha.length() < 8){
            tamanho = false;
        } else{
        for(int i = 0; i < senha.length(); i++){
            char c = senha.charAt(i);
            if(c >= 'A' && c <= 'Z'){
                maiusculo = true;
            } 
            else if(c >= 'a' && c <= 'z'){
                minusculo = true;
            }
            else if(c >= '0' && c <= '9'){
                numero = true;
            }
            else if(c >= '!' || c <= '@' || c <= '#' || c <= '$' || c <= '%' || c <= '&' || c <= '*'){
                especial = true;
            }
        }
    }
        if(maiusculo == true && minusculo == true && numero == true && especial == true && tamanho == true){
            System.out.println("SIM");
        }else{
            System.out.println("NAO");
        }
    
    }
        scanner.close();
    }    
}


