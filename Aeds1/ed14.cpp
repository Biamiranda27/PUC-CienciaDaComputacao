

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <algorithm>


class Objeto {
private:
    std::string a;
public:
    Objeto(const std::string& valor) : a(valor) {}
    int getInt() const {
        int valor;
        std::istringstream iss(a);
        if (iss >> valor) {
            char b;
            if (!(iss >> b)) {
                return valor; 
            }
        }
        return -1; 
    }
};
void metodo1411() {
    int n;
    std::cout << "Quantos objetos deseja criar? ";
    std::cin >> n;
    std::cin.ignore(); 
    std::vector<Objeto> objetos;
    for (int i = 0; i < n; ++i) {
        std::string x;
        std::cout << "Digite o conteúdo do objeto " << i + 1 << ": ";
        std::getline(std::cin, x);
        objetos.emplace_back(x);
    }
    for (int i = 0; i < n; ++i) {
        int resultado = objetos[i].getInt();
        std::cout << "Objeto " << i + 1 << ": " << resultado << std::endl;
    }
}


class Objeto {
private:
    std::string a;
public:
    Objeto(const std::string& valor) : a(value) {}
    double getDouble() const {
        double valor;
        std::istringstream iss(a);
        if (iss >> valor) {
            char b;
            if (!(iss >> b)) {
                return valor; 
            }
        }
        return 0.0; 
    }
};
void metodo1412() {
    int n;
    std::cout << "Quantos objetos deseja criar? ";
    std::cin >> n;
    std::cin.ignore(); 
    std::vector<Objeto> objetos;
    for (int i = 0; i < n; ++i) {
        std::string x;
        std::cout << "Digite o conteúdo do objeto " << i + 1 << ": ";
        std::getline(std::cin, x);
        objetos.emplace_back(x);
    }
    for (int i = 0; i < n; ++i) {
        double resultado = objetos[i].getDouble();
        std::cout << "Objeto " << i + 1 << ": " << resultado << std::endl;
    }
}


class Objeto {
private:
    std::string b;
public:
    Objeto(const std::string& valor) : b(valor) {}
    bool conteudo(const std::string& texto) const {
        return b.find(texto) != std::string::npos;
    }
};
void metodo1414() {
    int n;
    std::cout << "Quantos objetos deseja criar? ";
    std::cin >> n;
    std::cin.ignore(); 
    std::vector<Objeto> objetos;
    for (int i = 0; i < n; ++i) {
        std::string x;
        std::cout << "Digite o conteúdo do objeto " << i + 1 << ": ";
        std::getline(std::cin, x);
        objetos.emplace_back(x);
    }
    std::string procurar;
    std::cout << "Digite o texto a ser procurado: ";
    std::getline(std::cin, procurar);
    for (int i = 0; i < n; ++i) {
        bool result = objetos[i].conteudo(procurar);
        std::cout << "Objeto " << i + 1 << ": " << (result ? "true" : "false") << std::endl;
    }
}


class Objeto {
private:
    std::string conteudo;
public:
    Objeto(const std::string& valor) : conteudo(valor) {}
    bool getBoolean() const {
        std::string teste = conteudo;
        std::transform(teste.begin(), teste.end(), teste.begin(), ::tolower);
        if (teste == "true" || teste == "t" || teste == "1") {
            return true;
        }
        if (teste == "false" || teste == "f" || teste == "0") {
            return false;
        }
        return false;
    }
};
void metodo1413() {
    int n;
    std::cout << "Quantos objetos deseja criar? ";
    std::cin >> n;
    std::cin.ignore(); 
    std::vector<Objeto> objetos;
    for (int i = 0; i < n; ++i) {
        std::string x;
        std::cout << "Digite o conteúdo do objeto " << i + 1 << ": ";
        std::getline(std::cin, x);
        objetos.emplace_back(x);
    }
    for (int i = 0; i < n; ++i) {
        bool result = objetos[i].getBoolean();
        std::cout << "Objeto " << i + 1 << ": " << (result ? "true" : "false") << std::endl;
    }
}


class Objeto {
private:
    std::string a;
public:
    Objeto(const std::string& valor) : a(valor) {}
    std::string toUpperCase() const {
        std::string conteudo = a;
        std::transform(conteudo.begin(), conteudo.end(), conteudo.begin(), ::toupper);
        return conteudo;
    }
};
void metodo1415() {
    int n;
    std::cout << "Quantos objetos deseja criar? ";
    std::cin >> n;
    std::cin.ignore();  
    std::vector<Objeto> objetos;
    for (int i = 0; i < n; ++i) {
        std::string x;
        std::cout << "Digite o conteúdo do objeto " << i + 1 << ": ";
        std::getline(std::cin, x);
        objetos.emplace_back(x); 
    }
    for (int i = 0; i < n; ++i) {
        std::string resultado = objetos[i].toUpperCase();
        std::cout << "Objeto " << i + 1 << " em maiúsculas: " << resultado << std::endl; // Adiciona quebra de linha
    }
}


class Objeto {
private:
    std::string a;
public:
    Objeto(const std::string& valor) : a(valor) {}
    std::string toLowerCase() const {
        std::string conteudo = a;
        std::transform(conteudo.begin(), conteudo.end(), conteudo.begin(), ::tolower);
        return conteudo;
    }
};
void metodo1416() {
    int n;
    std::cout << "Quantos objetos deseja criar? ";
    std::cin >> n;
    std::cin.ignore();  
    std::vector<Objeto> objetos;
    for (int i = 0; i < n; ++i) {
        std::string x;
        std::cout << "Digite o conteúdo do objeto " << i + 1 << ": ";
        std::getline(std::cin, x);
        objetos.emplace_back(x); 
    }
    for (int i = 0; i < n; ++i) {
        std::string resultado = objetos[i].toLowerCase();
        std::cout << "Objeto " << i + 1 << " em minúsculas: " << resultado << std::endl; // Adiciona a quebra de linha
    }
}


class Objeto {
private:
    std::string a;
public:
    Objeto(const std::string& valor) : a(valor) {}
    std::string encrypt(int chave) const {
        std::string conteudo = a;
        for (size_t i = 0; i < conteudo.length(); ++i) {
            char c = conteudo[i];
            if (isalpha(c)) {  
                char limite = (isupper(c)) ? 'A' : 'a'; 
                conteudo[i] = (c - limite + chave) % 26 + limite; 
            }
        }
        return conteudo;
    }
};
void metodo1418() {
    int n;
    std::cout << "Quantos objetos deseja criar? ";
    std::cin >> n;
    std::cin.ignore(); 
    std::vector<Objeto> objetos;
    for (int i = 0; i < n; ++i) {
        std::string x;
        std::cout << "Digite o conteúdo do objeto " << i + 1 << ": ";
        std::getline(std::cin, x);
        objetos.push_back(Objeto(x)); 
    }
    int chave;
    std::cout << "Digite a chave para a cifra de César: ";
    std::cin >> chave;
    for (int i = 0; i < n; ++i) {
        std::string resultado = objetos[i].encrypt(chave);
        std::cout << "Objeto " << i + 1 << " codificado: " << resultado << std::endl;
    }
}


class Objeto {
private:
    std::string a;
public:
    Objeto(const std::string& valor) {
        a = valor;
    }
    std::string encrypt(int chave) const {
        std::string conteudo = a;
        for (size_t i = 0; i < conteudo.length(); ++i) {
            char c = conteudo[i];
            if (isalpha(c)) {  
                char limite = (isupper(c)) ? 'A' : 'a'; 
                conteudo[i] = (c - limite + chave) % 26 + limite; 
            }
        }
        return conteudo;
    }
    std::string decrypt(int chave) const {
        std::string conteudo = a;
        for (size_t i = 0; i < conteudo.length(); ++i) {
            char c = conteudo[i];
            if (isalpha(c)) {  
                char limite = (isupper(c)) ? 'A' : 'a'; 
                conteudo[i] = (c - limite - chave + 26) % 26 + limite; 
            }
        }
        return conteudo;
    }
};
void metodo1419() {
    int n;
    std::cout << "Quantos objetos deseja criar? ";
    std::cin >> n;
    std::cin.ignore();  
    std::vector<Objeto> objetos;
    for (int i = 0; i < n; ++i) {
        std::string x;
        std::cout << "Digite o conteúdo do objeto " << i + 1 << ": ";
        std::getline(std::cin, x);
        objetos.push_back(Objeto(x));
    }
    int chave;
    std::cout << "Digite a chave para a cifra de César: ";
    std::cin >> chave;
    for (int i = 0; i < n; ++i) {
        std::string resultado = objetos[i].encrypt(chave);
        std::cout << "Objeto " << i + 1 << " codificado: " << resultado << std::endl;
    }
    for (int i = 0; i < n; ++i) {
        std::string resultado_decodificado = objetos[i].decrypt(chave);
        std::cout << "Objeto " << i + 1 << " decodificado: " << resultado_decodificado << std::endl;
    }
}


int split(std::string sequencia[], const std::string& a) {
    std::istringstream stream(a);  
    std::string palavra;
    int count = 0;
    while (stream >> palavra) {
        sequencia[count] = palavra;  
        count++;  
    }
    return count; 
}
void metodo1420() {
    std::string a;
    std::cout << "Digite uma sequência de caracteres: ";
    std::getline(std::cin, a);  
    std::string sequencia[10]; 
    int num_palavras = split(sequencia, a);  
    std::cout << "Número de sequências encontradas: " << num_palavras << std::endl;
    for (int i = 0; i < num_palavras; i++) {
        std::cout << "Sequência " << i + 1 << ": " << sequencia[i] << std::endl;
    }
}


int split(std::string sequencia[], const std::string& str, char delimitador) {
    std::stringstream stream(str); 
    std::string palavra;
    int count = 0;
    while (std::getline(stream, palavra, delimitador)) {
        sequencia[count] = palavra;  
        count++;  
    }
    return count;  
}
void metodo14E1() {
    std::string str;
    char delimitador;
    std::cout << "Digite uma sequência de caracteres: ";
    std::getline(std::cin, str);  
    std::cout << "Digite um caractere para ser o delimitador: ";
    std::cin >> delimitador;
    std::string sequencia[10];
    int num_fragmentos = split(sequencia, str, delimitador);
    std::cout << "Número de fragmentos encontrados: " << num_fragmentos << std::endl;
    for (int i = 0; i < num_fragmentos; i++) {
        std::cout << "Fragmento " << i + 1 << ": " << sequencia[i] << std::endl;
    }
}


int split(std::string sequencia[], const std::string& a, char delimitador) {
    std::stringstream stream(a);  
    std::string palavra;
    int count = 0;
    while (std::getline(stream, palavra, delimitador)) {
        sequencia[count] = palavra;  
        count++;  
    }
    return count;  
}
std::string contrarioString(const std::string& a) {
    std::string reverso = a;  
    int left = 0, right = reverso.length() - 1;
    while (left < right) {
        std::swap(reverso[left], reverso[right]);
        left++;
        right--;
    }
    return reverso; 
}
void metodo14E2() {
    std::string a;
    char delimitador;
    std::cout << "Digite uma sequência de caracteres: ";
    std::getline(std::cin, a);  
    std::cout << "Digite um caracter para ser o delimitador: ";
    std::cin >> delimitador;
    std::string sequencia[10];
    int num_fragmentos = split(sequencia, a, delimitador);
    std::cout << "Número de fragmentos encontrados: " << num_fragmentos << std::endl;
    for (int i = 0; i < num_fragmentos; i++) {
        std::cout << "Fragmento " << i + 1 << ": " << sequencia[i] << std::endl;
    }
    std::string reverso = contrarioString(a);
    std::cout << "A string invertida é: " << reverso << std::endl;
}


int main(){
    int opcao;
    do{
        std::cout<< "Digite um numero entre 1-12: ";
        std::cin>> opcao;
        switch(opcao){
            case 1: metodo1411(); break;
            /*
Quantos objetos deseja criar? 4
Digite o conteúdo do objeto 1: 123
Digite o conteúdo do objeto 2: rwf
Digite o conteúdo do objeto 3: 2f3
Digite o conteúdo do objeto 4: vre
Objeto 1: 123
Objeto 2: -1
Objeto 3: -1
Objeto 4: -1
            */
           case 2: metodo1412(); break;
            /*
Quantos objetos deseja criar? 3
Digite o conteúdo do objeto 1: 12.0
Digite o conteúdo do objeto 2: 1 
Digite o conteúdo do objeto 3: ds
Objeto 1: 12
Objeto 2: 1
Objeto 3: 0
            */
           case 3: metodo1413(); break;
            /*
Quantos objetos deseja criar? 4
Digite o conteúdo do objeto 1: 0
Digite o conteúdo do objeto 2: fdf
Digite o conteúdo do objeto 3: true
Digite o conteúdo do objeto 4: 24
Objeto 1: false
Objeto 2: false
Objeto 3: true
Objeto 4: false
            */
           case 4: metodo1414(); break;
            /*
Quantos objetos deseja criar? 4
Digite o conteúdo do objeto 1: sdg
Digite o conteúdo do objeto 2: 345
Digite o conteúdo do objeto 3: gr5
Digite o conteúdo do objeto 4: g
Digite o texto a ser procurado: g
Objeto 1: true
Objeto 2: false
Objeto 3: true
Objeto 4: true
            */
           case 5: metodo1415(); break;
            /*
Quantos objetos deseja criar? 5
Digite o conteúdo do objeto 1: Gkdk
Digite o conteúdo do objeto 2: hdd
Digite o conteúdo do objeto 3: 24
Digite o conteúdo do objeto 4: cd4
Digite o conteúdo do objeto 5: BJSL
Objeto 1 em maiúsculas: GKDK
Objeto 2 em maiúsculas: HDD
Objeto 3 em maiúsculas: 24
Objeto 4 em maiúsculas: CD4
Objeto 5 em maiúsculas: BJSL
            */
           case 6: metodo1416(); break;
            /*
Quantos objetos deseja criar? 5
Digite o conteúdo do objeto 1: dsjc
Digite o conteúdo do objeto 2: AGYST
Digite o conteúdo do objeto 3: Fbjdh
Digite o conteúdo do objeto 4: jd
Digite o conteúdo do objeto 5: TUYA
Objeto 1 em minúsculas: dsjc
Objeto 2 em minúsculas: agyst
Objeto 3 em minúsculas: fbjdh
Objeto 4 em minúsculas: jd
Objeto 5 em minúsculas: tuya
            */
           //case 7: metodo1417(); break;
            /*

            */
           case 8: metodo1418(); break;
            /*
Quantos objetos deseja criar? 4
Digite o conteúdo do objeto 1: sjfi
Digite o conteúdo do objeto 2: sjd8
Digite o conteúdo do objeto 3: abhd6
Digite o conteúdo do objeto 4: GTGS
Digite a chave para a cifra de César: 3
Objeto 1 codificado: vmil
Objeto 2 codificado: vmg8
Objeto 3 codificado: dekg6
Objeto 4 codificado: JWJV
            */
           case 9: metodo1419(); break;
            /*
Quantos objetos deseja criar? 4
Digite o conteúdo do objeto 1: fjds
Digite o conteúdo do objeto 2: HGJS
Digite o conteúdo do objeto 3: i28jd
Digite o conteúdo do objeto 4: jsyGH
Digite a chave para a cifra de César: 1
Objeto 1 codificado: gket
Objeto 2 codificado: IHKT
Objeto 3 codificado: j28ke
Objeto 4 codificado: ktzHI
Objeto 1 decodificado: eicr
Objeto 2 decodificado: GFIR
Objeto 3 decodificado: h28ic
Objeto 4 decodificado: irxFG
            */
           case 10: metodo1420(); break;
            /*
Digite uma sequência de caracteres: hello world
Número de sequências encontradas: 2
Sequência 1: hello
Sequência 2: world
            */
           case 11: metodo14E1(); break;
            /*
Digite uma sequência de caracteres: hello world
Digite um caractere para ser o delimitador: l
Número de fragmentos encontrados: 4
Fragmento 1: he
Fragmento 2: 
Fragmento 3: o wor
Fragmento 4: d
            */
           case 12: metodo14E2(); break;
            /*
Digite uma sequência de caracteres: hello world
Digite um caracter para ser o delimitador: l
Número de fragmentos encontrados: 4
Fragmento 1: he
Fragmento 2: 
Fragmento 3: o wor
Fragmento 4: d
A string invertida é: dlrow olleh
            */
           default: std::cerr<< "Opção invalida"; break;
        }
    }while(opcao!=0);
    return 0;
}
