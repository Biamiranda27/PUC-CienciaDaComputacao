

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>


class Nome {
public:
    std::string name;
    void lerNome() {
        std::cout << "Digite um nome: ";
        std::getline(std::cin, name); 
        if (!name.empty()) {
            std::cout << "Nome: " << name;
        } else {
            std::cerr << "Não foi digitado um nome para ser atribuído";
        }
    }
};
void metodo1311() {
    Nome pessoa;
    pessoa.lerNome(); 
}


class Telefone{
    public:
    std::string numero;
    void testarNumero(){
        std::cout<< "Digite um numero de telefone: ";
        std::cin >> numero;
        if(!numero.empty()){
            std::cout<< "Telefone: "<<numero;
        }else{
            std::cerr<< "Não foi digitado um numero para ser atribuido";
        }
    }
};
void metodo1312(){
    Telefone pessoa;
    pessoa.testarNumero();
}


class Telefone {
private:
    std::string telefone;
    bool telefoneValido(const std::string& tel) const {
        for (size_t i = 0; i < tel.length(); ++i) {
            if (!isdigit(tel[i]) && tel[i] != '-') {
                return false; 
            }
        }
        return true; 
    }
public:
    void lerNumero() {
        std::string numero;
        std::cout << "Digite o telefone: ";
        std::getline(std::cin, numero);

        if (!numero.empty() && telefoneValido(numero)) {
            telefone = numero;
            std::cout << "Telefone válido " << std::endl;
        } else {
            std::cerr << "Número inválido";
        }
    }
    void exibirNumero() const {
        if (!telefone.empty()) {
            std::cout << "Telefone: " << telefone << std::endl;
        } else {
            std::cout << "Nenhum telefone foi armazenado" << std::endl;
        }
    }
};
void metodo1313() {
    Telefone pessoa;
    pessoa.lerNumero();
    pessoa.exibirNumero();
}


class Pessoa {
public:
    std::string nome;
    int idade;
    std::string telefone;
    bool lerDeArquivo(const std::string& nomeArquivo) {
        std::ifstream arquivo(nomeArquivo); 
        if (!arquivo.is_open()) { 
            std::cerr << "Erro na abertura do arquivo"<< std::endl;
            return false;
        }
        std::getline(arquivo, nome); 
        arquivo >> idade; 
        arquivo.ignore(); 
        std::getline(arquivo, telefone); 
        arquivo.close(); 
        return true;
    }
    void exibirDados() const {
        std::cout << "Nome: " << nome << std::endl;
        std::cout << "Idade: " << idade << std::endl;
        std::cout << "Telefone: " << telefone << std::endl;
    }
};
void metodo1314() {
    Pessoa pessoa;
    if (!pessoa.lerDeArquivo("pessoa1.txt")) {
        std::cerr << "Erro ao ler os dados do arquivo." << std::endl;
    } else {
         pessoa.exibirDados();
    }
}


class Pessoa {
public:
    std::string nome;
    std::string telefone;
    void salvarDados(std::ofstream& arquivo) {
        std::cout << "Digite o nome: ";
        std::getline(std::cin, nome); 
        std::cout << "Digite o telefone: ";
        std::getline(std::cin, telefone); 
        size_t tamanhoNome = nome.size();
        size_t tamanhoTelefone = telefone.size();
        size_t tamanhoTotal = tamanhoNome + tamanhoTelefone;
        arquivo << tamanhoTotal << std::endl;
        arquivo << nome << std::endl;
        arquivo << telefone << std::endl;
    }
};
void metodo1315() {
    std::ofstream arquivo("Pessoa1.txt"); 
    if (!arquivo.is_open()) {
        std::cerr << "Erro na abertura do arquivo" << std::endl;
        return;
    }
    Pessoa p1;
    p1.salvarDados(arquivo); 
    arquivo.close();
}


class Pessoa {
public:
    std::string nome;
    std::string telefone1;
    std::string telefone2;
    void gravarDados(std::ofstream& f) {
        std::cout << "Digite o nome: ";
        std::getline(std::cin, nome);
        f << nome << std::endl;
        std::cout << "Digite o telefone 1: ";
        std::getline(std::cin, telefone1);
        f << telefone1 << std::endl;
        std::cout << "Digite o telefone 2: ";
        std::getline(std::cin, telefone2);
        f << telefone2 << std::endl;
    }
};
void metodo1316() {
    std::ofstream f("Pessoa1.txt");
    if (!f.is_open()) {
        std::cerr << "Erro na abertura do arquivo" << std::endl;
        return;
    }
    Pessoa p1;
    p1.gravarDados(f);
    f.close();
}


class Contato {
public:
    std::string nome;
    std::vector<std::string> telefones;
    int quantidadeTelefones;
    Contato() : quantidadeTelefones(0) {}
    void definirNome() {
        std::cout << "Digite o nome do contato: ";
        std::getline(std::cin, nome);
    }
    bool adicionarTelefone() {
        if (quantidadeTelefones >= 15) {
            std::cerr << "Não pode adicionar mais que 15 numeros telefonicos" << std::endl;
            return false;
        }
        std::string telefone;
        std::cout << "Digite o número de telefone: ";
        std::getline(std::cin, telefone);

        telefones.push_back(telefone);
        quantidadeTelefones++;
        return true;
    }
    int obterQuantidadeTelefones() const {
        return quantidadeTelefones;
    }
    void exibirContato() const {
        std::cout << "Nome: " << nome << std::endl;
        std::cout << "Quantidade de telefones: " << quantidadeTelefones << std::endl;
        for (int i = 0; i < quantidadeTelefones; i++) {
            std::cout << "Telefone " << i + 1 << ": " << telefones[i] << std::endl;
        }
    }
};
void metodo1317() {
    Contato contato;
    contato.definirNome();
    std::string opcao = "sim";
    while (opcao == "sim" || opcao == "Sim" || opcao == "SIM") {
        if (contato.obterQuantidadeTelefones() < 15) {
            contato.adicionarTelefone();
            std::cout << "Deseja adicionar outro telefone? (sim/nao): ";
            std::cin >> opcao;
            std::cin.ignore(); 
        } else {
            std::cout << "Já foi digitado 15 telefones" << std::endl;
            opcao = "nao"; 
        }
    }
    contato.exibirContato();
}


class Contato {
public:
    std::string nome;
    std::string telefone1;
    std::string telefone2;
    int quantidadeTelefones;
    Contato() : quantidadeTelefones(0) {}
    void definirNome() {
        std::cout << "Digite o nome do contato: ";
        std::getline(std::cin, nome);
    }
    void definirPrimeiroTelefone() {
        std::cout << "Digite o primeiro telefone: ";
        std::getline(std::cin, telefone1);
        quantidadeTelefones = 1;
    }
    void adicionarSegundoTelefone() {
        std::string opcao;
        if (quantidadeTelefones == 1) {
            std::cout << "Deseja adicionar um segundo telefone? (sim/nao): ";
            std::cin >> opcao;
            std::cin.ignore(); 
            if (opcao == "sim" || opcao == "Sim" || opcao == "Sim") {
                std::cout << "Digite o segundo telefone: ";
                std::getline(std::cin, telefone2);
                quantidadeTelefones = 2;
            }
        } else {
            std::cout << "Já tem um segundo telefone ou nenhum telefone foi adicionado" << std::endl;
            opcao = "nao";
        }
    }
    int obterQuantidadeTelefones() const {
        return quantidadeTelefones;
    }
    void exibirDados() const {
        std::cout << "Nome: " << nome << std::endl;
        if (quantidadeTelefones > 0) {
            std::cout << "Telefone 1: " << telefone1 << std::endl;
        }
        if (quantidadeTelefones > 1) {
            std::cout << "Telefone 2: " << telefone2 << std::endl;
        }
    }
};
void metodo1318() {
    Contato pessoa;
    pessoa.definirNome();
    pessoa.definirPrimeiroTelefone();
    pessoa.exibirDados();
    pessoa.adicionarSegundoTelefone();
    pessoa.exibirDados();
}


class Contato {
public:
    std::string nome;
    std::string telefone1;
    std::string telefone2;
    int quantidadeTelefones;
    Contato() : quantidadeTelefones(0) {}
    void definirNome() {
        std::cout << "Digite o nome do contato: ";
        std::getline(std::cin, nome);
    }
    void definirPrimeiroTelefone() {
        std::cout << "Digite o primeiro telefone: ";
        std::getline(std::cin, telefone1);
        quantidadeTelefones = 1;
    }
    void adicionarSegundoTelefone() {
        std::string opcao;
        if (quantidadeTelefones == 1) {
            std::cout << "Deseja adicionar um segundo telefone? (sim/nao): ";
            std::cin >> opcao;
            std::cin.ignore();  
            if (opcao == "sim" || opcao == "Sim" || opcao == "SIM") {
                std::cout << "Digite o segundo telefone: ";
                std::getline(std::cin, telefone2);
                quantidadeTelefones = 2;
            }
        } else {
            std::cout << "Já existe um segundo telefone ou nenhum telefone foi adicionado" << std::endl;
            opcao = "nao";
        }
    }
    void alterarSegundoTelefone() {
        if (quantidadeTelefones == 2) {
            std::cout << "Digite um novo numero para o segundo telefone: ";
            std::getline(std::cin, telefone2);
        } else {
            std::cerr << "Erro, o contato nao tem dois telefones";
        }
    }
    int obterQuantidadeTelefones() const {
        return quantidadeTelefones;
    }
    void exibirDados() const {
        std::cout << "Nome: " << nome << std::endl;
        if (quantidadeTelefones > 0) {
            std::cout << "Telefone 1: " << telefone1 << std::endl;
        }
        if (quantidadeTelefones > 1) {
            std::cout << "Telefone 2: " << telefone2 << std::endl;
        }
    }
};
void metodo1319() {
    Contato pessoa;
    pessoa.definirNome();
    pessoa.definirPrimeiroTelefone();
    pessoa.exibirDados();
    pessoa.adicionarSegundoTelefone();
    pessoa.exibirDados();
    pessoa.alterarSegundoTelefone();
    pessoa.exibirDados();
}


class Contato {
public:
    std::string nome;
    std::string telefone1;
    std::string telefone2;
    int quantidadeTelefones;
    Contato() : quantidadeTelefones(0) {}
    void definirNome() {
        std::cout << "Digite o nome do contato: ";
        std::getline(std::cin, nome);
    }
    void definirPrimeiroTelefone() {
        std::cout << "Digite o primeiro telefone: ";
        std::getline(std::cin, telefone1);
        quantidadeTelefones = 1;
    }
    void adicionarSegundoTelefone() {
        if (quantidadeTelefones == 1) {
            std::cout << "Digite o segundo telefone: ";
            std::getline(std::cin, telefone2);
            quantidadeTelefones = 2;
        } else {
            std::cout << "Erro: ja tem um segundo telefone";
        }
    }
    void alterarSegundoTelefone() {
        if (quantidadeTelefones == 2) {
            telefone2.clear(); 
            quantidadeTelefones = 1; 
            std::cout << "O segundo telefone foi removido\n";
        } else {
            std::cerr << "Erro: o contato não possui dois telefones";
        }
    }
    int obterQuantidadeTelefones() const {
        return quantidadeTelefones;
    }
    void exibirDados() const {
        std::cout << "Nome: " << nome << std::endl;
        if (quantidadeTelefones > 0) {
            std::cout << "Telefone 1: " << telefone1 << std::endl;
        }
        if (quantidadeTelefones > 1) {
            std::cout << "Telefone 2: " << telefone2 << std::endl;
        }
    }
};
void metodo1320() {
    Contato pessoa;
    pessoa.definirNome();
    pessoa.definirPrimeiroTelefone();
    pessoa.exibirDados();
    pessoa.adicionarSegundoTelefone();
    pessoa.exibirDados();
    pessoa.alterarSegundoTelefone();
    pessoa.exibirDados(); 
}


class Contato {
public:
    std::string nome;
    std::vector<std::string> telefones;
    const int maxTelefones = 10;
    void definirNome() {
        std::cout << "Digite o nome do contato: ";
        std::getline(std::cin, nome);
    }
    void adicionarTelefone() {
        if (telefones.size() < maxTelefones) {
            std::string novoTelefone;
            std::cout << "Digite o telefone " << (telefones.size() + 1) << ": ";
            std::getline(std::cin, novoTelefone);
            telefones.push_back(novoTelefone);
        } else {
            std::cerr << "Erro: o contato já possui o número máximo de telefones";
        }
    }
    int obterQuantidadeTelefones() const {
        return telefones.size();
    }
    void exibirDados() const {
        std::cout << "Nome: " << nome << std::endl;
            for (size_t i = 0; i < telefones.size(); ++i) {
                std::cout << "Telefone " << (i + 1) << ": " << telefones[i] << std::endl;
        }
    }
};
void metodo13E1() {
    Contato pessoa;
    pessoa.definirNome();
    int quantidadeTelefones;
    std::cout << "Quantos telefones deseja adicionar (máximo " << pessoa.maxTelefones << ")? ";
    std::cin >> quantidadeTelefones;
    std::getchar();
    for (int i = 0; i < quantidadeTelefones; ++i) {
        pessoa.adicionarTelefone();
    }
    pessoa.exibirDados();
    std::cout << "Quantidade de telefones: " << pessoa.obterQuantidadeTelefones() << std::endl;
}


class Contato {
public:
    std::string nome;
    std::string enderecoResidencial;
    std::string enderecoProfissional;
    Contato() {}
    void definirNome() {
        std::cout << "Digite o nome do contato: ";
        std::getline(std::cin, nome);
    }
    void definirEnderecoResidencial() {
        std::cout << "Digite o endereço residencial: ";
        std::getline(std::cin, enderecoResidencial);
    }
    void definirEnderecoProfissional() {
        std::cout << "Digite o endereço profissional: ";
        std::getline(std::cin, enderecoProfissional);
    }
    void exibirDados() const {
        std::cout << "Nome: " << nome << std::endl;
        std::cout << "Endereço Residencial: " 
                  << enderecoResidencial << std::endl;
        std::cout << "Endereço Profissional: " 
                  << enderecoProfissional << std::endl;
    }
};
void metodo13E2() {
    Contato pessoa;
    pessoa.definirNome();
    pessoa.definirEnderecoResidencial();
    pessoa.definirEnderecoProfissional();
    pessoa.exibirDados();
}



int main(){
    int opcao;
    do{
        std::cout<< "Digite um numero entre 1-12: ";
        std::cin>> opcao;
        switch(opcao){
            case 1: metodo1311(); break;
            /*
Digite um nome: beatriz
Nome: beatriz
            */
           case 2: metodo1312(); break;
            /*
Digite um numero de telefone: 12344-7890
Telefone: 12344-7890
            */
           case 3: metodo1313(); break;
            /*
Digite o telefone: 1234-53631
Telefone válido 
Telefone: 1234-53631
            */
           case 4: metodo1314(); break;
            /*
Erro na abertura do arquivo
Erro ao ler os dados do arquivo
            */
           case 5: metodo1315(); break;
            /*
Digite o nome: Beatriz
Digite o telefone: 1234-56789
            */
           case 6: metodo1316(); break;
            /*
Digite o nome: Beatriz
Digite o telefone 1: 1234-56789
Digite o telefone 2: 9876-54321
            */
           case 7: metodo1317(); break;
            /*
Digite o nome do contato: Beatriz
Digite o número de telefone: 1234-56789
Deseja adicionar outro telefone? (sim/nao): nao
Nome: Beatriz
Quantidade de telefones: 1
Telefone 1: 1234-56789
            */
           case 8: metodo1318(); break;
            /*
Digite o nome do contato: Beatriz
Digite o primeiro telefone: 1234-56789
Nome: Beatriz
Telefone 1: 1234-56789
Deseja adicionar um segundo telefone? (sim/nao): sim
Digite o segundo telefone: 1345-84020
Nome: Beatriz
Telefone 1: 1234-56789
Telefone 2: 1345-84020
            */
           case 9: metodo1319(); break;
            /*
Digite o nome do contato: Beatriz
Digite o primeiro telefone: 1234-56789
Nome: Beatriz
Telefone 1: 1234-56789
Deseja adicionar um segundo telefone? (sim/nao): sim
Digite o segundo telefone: 3245-68494
Nome: Beatriz
Telefone 1: 1234-56789
Telefone 2: 3245-68494
Digite um novo numero para o segundo telefone: 1236-68490
Nome: Beatriz
Telefone 1: 1234-56789
Telefone 2: 1236-68490
            */
           case 10: metodo1320(); break;
            /*
Digite o nome do contato: Beatriz
Digite o primeiro telefone: 1234-58239
Nome: Beatriz
Telefone 1: 1234-58239
Digite o segundo telefone: 1334-42948
Nome: Beatriz
Telefone 1: 1234-58239
Telefone 2: 1334-42948
O segundo telefone foi removido
Nome: Beatriz
Telefone 1: 1234-58239
            */
           case 11: metodo13E1(); break;
            /*
Digite o nome do contato: Beatriz
Quantos telefones deseja adicionar (máximo 10)? 5
Digite o telefone 1: 1234-75930
Digite o telefone 2: 28490-49394
Digite o telefone 3: 2849-09180
Digite o telefone 4: 8193-90320
Digite o telefone 5: 1930-09873
Nome: Beatriz
Telefone 1: 1234-75930
Telefone 2: 28490-49394
Telefone 3: 2849-09180
Telefone 4: 8193-90320
Telefone 5: 1930-09873
Quantidade de telefones: 5
            */
           case 12: metodo13E2(); break;
            /*
Digite o nome do contato: Beatriz
Digite o endereço residencial: Carlos luz
Digite o endereço profissional: Paulista
Nome: Beatriz
Endereço Residencial: Carlos luz
Endereço Profissional: Paulista
            */
           default: std::cerr<< "Opcao invalida";break;
        }
    }while(opcao!=0);
    return 0;
}
