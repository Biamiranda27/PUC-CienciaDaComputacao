

#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <vector>
#include <algorithm>

char* str_push_back(char* s, char c) {
    int tamanho = strlen(s);
    char* novo = new char[tamanho + 2]; 
    strcpy(novo, s);
    novo[tamanho] = c; 
    novo[tamanho + 1] = '\0';
    return novo;
}
void metodo1511() {
    std::string palavra;
    std::cout << "Digite uma palavra: " << std::endl;
    std::cin >> palavra;
    std::cin.get();
    char* string = new char[palavra.length() + 1]; 
    strcpy(string, palavra.c_str()); 
    char c;
    std::cout << "Digite o caractere a ser acrescentado: " << std::endl;
    std::cin >> c;
    std::cin.get();
    char* novaString = str_push_back(string, c);
    delete[] string; 
    std::cout << "String modificada: " << novaString << std::endl;
    delete[] novaString; 
}

char* str_pop_back(char* s) {
    if (s == nullptr || s[0] == '\0') {
        return s; 
    }
    size_t tamanho = strlen(s); 
    s[tamanho - 1] = '\0'; 
    return s; 
}
void metodo1512() {
    char palavra[100];
    std::cout << "Digite uma string: " << std::endl;
    std::cin.getline(palavra, 100);
    std::cout << "String após remover o último caractere: " << str_pop_back(palavra) << std::endl;
    //std::cin.get();
}

char* str_push_front(char c, char *s) {
    if (s == nullptr) {
        return nullptr; 
    }
    size_t tamanho = strlen(s);
    for (size_t i = tamanho; i > 0; --i) {
        s[i] = s[i - 1]; 
    }
    s[0] = c;  
    s[tamanho + 1] = '\0'; 
    return s;      
}
void metodo1513() {
    char carac[100] = "hello", palavra;
    std::cout << "Digite um caractere para adicionar ao início: " << std::endl;
    std::cin >> palavra;
    std::cin.get();
    str_push_front(palavra, carac);
    std::cout << "String após adicionar o caractere no início: " << carac << std::endl;
}

char* str_pop_front(char *s) {
    if (s == nullptr || *s == '\0') {
        return s; 
    }
    size_t tamanho = strlen(s);
    for (size_t i = 0; i < tamanho; ++i) {
        s[i] = s[i + 1]; 
    }
    return s; 
}
void metodo1514() {
    char palavra[100];
    std::cout << "Digite uma string: " << std::endl;
    std::cin.getline(palavra, 100);
    str_pop_front(palavra);
    std::cout << "String após remoção do primeiro caractere: " << palavra << std::endl;
}

char* str_push_mid(char *s, char c) {
    if (s == nullptr || strlen(s) < 2) {
        return s; 
    }
    size_t tamanho = strlen(s);
    size_t m = tamanho / 2; 
    for (size_t i = tamanho; i > m; --i) {
        s[i] = s[i - 1];
    }
    s[m] = c;      
    s[tamanho + 1] = '\0'; 
    return s;   
}
void metodo1515() {
    char string[100];
    char c;
    std::cout << "Digite uma string: " << std::endl;
    std::cin.getline(string, 100);
    if (strlen(string) < 2) {
        std::cout << "Não é possível fazer, a string deve ter 2 caracteres no mínimo" << std::endl;
        return;
    }
    std::cout << "Digite um caractere para inserir no meio: " << std::endl;
    std::cin >> c;
    std::cin.get();
    str_push_mid(string, c);
    std::cout << "String modificada: " << string << std::endl;
}

char* str_pop_mid(char *s) {
    if (s == nullptr || strlen(s) < 2) {
        return s; 
    }
    size_t tamanho = strlen(s);
    size_t m = tamanho / 2; 
    for (size_t i = m; i < tamanho; ++i) {
        s[i] = s[i + 1];
    }
    return s; 
}
void metodo1516() {
    char string[100];
    std::cout << "Digite uma string: " << std::endl;
    std::cin.getline(string, 100);
    if (strlen(string) < 2) {
        std::cout << "Não é possível fazer, a string deve ter 2 caracteres no mínimo" << std::endl;
        return;
    }
    str_pop_mid(string);
    std::cout << "String após remover o caractere do meio: " << string << std::endl;
}

char* str_insert(char *s, char c, int p) {
    if (s == nullptr || p < 0 || p > (int)strlen(s)) {
        return s; 
    }
    size_t tamanho = strlen(s);
    for (size_t i = tamanho; i >= (size_t)p; --i) {
        s[i + 1] = s[i];
    }
    s[p] = c;     
    s[tamanho + 1] = '\0'; 
    return s;   
}
void metodo1517() {
    char string[100];
    char c;
    int p;
    std::cout << "Digite uma string: " << std::endl;
    std::cin.getline(string, 100);
    std::cout << "Digite um caractere para inserir: " << std::endl;
    std::cin >> c;
    std::cin.get();
    std::cout << "Digite a posição onde inserir: " << std::endl;
    std::cin >> p;
    std::cin.get();
    if (p < 0 || p > (int)strlen(string)) {
        std::cout << "Posição inválida" << std::endl;
        return;
    }
    str_insert(string, c, p);
    std::cout << "String após inserção: " << string << std::endl;
}

char* str_remove(char *s, int p) {
    if (s == nullptr || p < 0 || p >= (int)strlen(s)) {
        return s; 
    }
    size_t tamanho = strlen(s);
    for (size_t i = p; i < tamanho; ++i) {
        s[i] = s[i + 1];
    }
    return s; 
}
void metodo1518() {
    char string[100];
    int p;
    std::cout << "Digite uma string: " << std::endl;
    std::cin.getline(string, 100);
    std::cout << "Digite a posição de onde remover: " << std::endl;
    std::cin >> p;
    std::cin.get();
    if (p < 0 || p >= (int)strlen(string)) {
        std::cout << "Posição inválida" << std::endl;
        return;
    }
    str_remove(string, p);
    std::cout << "String após remoção: " << string << std::endl;
}

char* str_chr(char *s, char c) {
    if (s == nullptr) {
        return nullptr;
    }
    while (*s != '\0') { 
        if (*s == c) {
            return s;
        }
        s++; 
    }
    return nullptr; 
}
void metodo1519() {
    char string[100];
    char c;
    std::cout << "Digite uma string: " << std::endl;
    std::cin.getline(string, 100);
    std::cout << "Digite um caractere: " << std::endl;
    std::cin >> c;
    std::cin.get();
    char* result = str_chr(string, c);
    if (result != nullptr) {
        std::cout << "Caractere '" << c << "' encontrado na posição: " << (result - string) << std::endl;
    } else {
        std::cout << "Caractere não encontrado" << std::endl;
    }
}


char* str_tok(char *s, char d) {
    if (s == nullptr) {
        return nullptr; 
    }
    char* start = s;
    while (*s != '\0') {
        if (*s == d) {
            *s = '\0'; 
            return start; 
        }
        s++; 
    }
    return start;
}
void metodo1520() {
    char string[100];
    char d;
    std::cout << "Digite uma string: " << std::endl;
    std::cin.getline(string, 100);
    std::cout << "Digite o delimitador: " << std::endl;
    std::cin >> d;
    std::cin.get();
    char* t = str_tok(string, d);
    if (t != nullptr) {
        std::cout << t << std::endl;
        while (*t != '\0') {
            t++; 
            if (*t != '\0') {
                std::cout << str_tok(t, d) << std::endl;
            }
        }
    } else {
        std::cout << "Delimitador não encontrado" << std::endl;
    }
    std::cin.get();
}


char* str_prefix(char *p, char *s) {
    if (p == nullptr || s == nullptr) {
        return nullptr;
    }
    while (*s != '\0') {
        char *comeco = s;
        char *a = p;
        while (*a != '\0' && *s != '\0' && *a == *s) {
            p++;
            s++;
        }
        if (*a == '\0') {
            return comeco;  
        }
        s = comeco;
    }
    return nullptr;
}
void metodo15E1() {
    char string[100], p[100];
    std::cout << "Digite a string: " << std::endl;
    std::cin.getline(string, 100);
    std::cout << "Digite um prefixo: " << std::endl;
    std::cin.getline(p, 100);
    char* resultado = str_prefix(p, string);
    if (resultado != nullptr) {
        std::cout << "Prefixo encontrado na posição: " << (resultado - string) << std::endl;
    } else {
        std::cout << "Não tem esse prefixo" << std::endl;
    }
    std::cin.get();
}


char* str_suffix(char* s, char* sufixo) {
    if (s == nullptr || sufixo == nullptr) {
        return nullptr;
    }
    int tamanhoS = strlen(s);       
    int tamanhoSu = strlen(sufixo);  

    if (tamanhoSu > tamanhoS) {
        return nullptr; 
    }
    char* inicioSu = s + tamanhoS - tamanhoSu;
    if (strcmp(inicioSu, sufixo) == 0) {
        return inicioSu;
    }
    return nullptr; 
}
void metodo15E2() {
    char string[100], s[100];
    std::cout << "Digite a string: " << std::endl;
    std::cin.getline(string, 100);
    std::cout << "Digite um sufixo: " << std::endl;
    std::cin.getline(s, 100);
    char* resultado = str_suffix(string, s);
    if (resultado != nullptr) {
        std::cout << "Sufixo encontrado na posição: " << (resultado - string) << std::endl;
    } else {
        std::cout << "Não tem esse sufixo" << std::endl;
    }
    std::cin.get();
}




int main() {
    int opcao;
    do {
        std::cout << "Digite um número entre 1-12: ";
        std::cin >> opcao;
        std::cin.get();
        switch(opcao) {
            case 1: metodo1511(); break;
            /*
Digite uma palavra: 
hello  
Digite o caractere a ser acrescentado: 
a
String modificada: helloa
            */
           case 2: metodo1512(); break;
            /*
Digite uma string: 
hello
String após remover o último caractere: hell
            */
           case 3: metodo1513(); break;
            /*
Digite um caractere para adicionar ao início: 
a
String após adicionar o caractere no início: ahello
            */
           case 4: metodo1514(); break;
            /*
Digite uma string: 
hello
String após remoção do primeiro caractere: ello
            */
           case 5: metodo1515(); break;
            /*
Digite uma string: 
hello
Digite um caractere para inserir no meio: 
a
String modificada: heallo
            */
           case 6: metodo1516(); break;
            /*
Digite uma string: 
hello
String após remover o caractere do meio: helo
            */
           case 7: metodo1517(); break;
            /*
Digite uma string: 
hello
Digite um caractere para inserir: 
a
Digite a posição onde inserir: 
2
String após inserção: heallo
            */
           case 8: metodo1518(); break;
            /*
Digite uma string: 
hello
Digite a posição de onde remover: 
2
String após remoção: helo
            */
           case 9: metodo1519(); break;
            /*
Digite uma string: 
hello
Digite um caractere: 
l
Caractere 'l' encontrado na posição: 2
            */
           case 10: metodo1520(); break;
            /*
Digite uma string: 
hello
Digite o delimitador: 
l
he
e
            */
           case 11: metodo15E1(); break;
            /*
Digite a string: 
hello
Digite um prefixo: 
h
Prefixo encontrado na posição: 0
            */
           case 12: metodo15E2(); break;
            /*
Digite a string: 
hello
Digite um sufixo: 
o
Sufixo encontrado na posição: 4
            */
           default: std::cout << "Opção inválida"; break;
        }
    } while (opcao != 0); 
    return 0;
}
