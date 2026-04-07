

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>


void numeros(std::ofstream &f, int n) {
    srand(static_cast<unsigned int>(time(0))); 
    int num;

    f << n << " números irão ser gravados no arquivo\n"; 
    for (int x = 0; x < n; x++) {
        num = rand() % 100; 
        f << "Número aleatório " << x << ": " << num << "\n"; 
    }
}
void metodo1111() {
    std::ofstream f("dados.txt"); 
    if (!f) {
        std::cerr << "Erro na abertura" << std::endl; 
        exit(1);
    }
    int n;
    std::cout << "Digite quantos números você deseja que sejam gerados: ";
    std::cin >> n; 
    numeros(f, n);
     f.close();
}


int contarArray(std::ifstream &f, int *array) {
    int valor, count = 0;
    while (f >> valor) { 
        array[count++] = valor;
    }
    return count;
}
void procurarPar(int *array, int tamanho) {
    int maiorPar = -1; 
    for (int x = 0; x < tamanho; x++) {
        if (array[x] % 2 == 0) { 
            if (array[x] > maiorPar) {
                maiorPar = array[x];
            }
        }
    }
    if (maiorPar != -1) {
        std::cout << "O maior valor par é: " << maiorPar << std::endl;
    } else {
        std::cout << "Não há valores pares no array" << std::endl;
    }
}
void metodo1112() {
    std::ifstream f("dados.txt"); 
    if (!f) {
        std::cerr << "Erro na abertura " << std::endl; 
        exit(1);
    }
    int array[30], tamanho;
    tamanho = contarArray(f, array);
    f.close();
    procurarPar(array, tamanho);
}


 int contarArray(std::ifstream &f, int *array) {
    int valor, count = 0;
    while (f >> valor) { 
        array[count++] = valor;
    }
    return count;
}
void procurarPar(int *array, int tamanho) {
    int menorPar = 200; 
    for (int x = tamanho-1; x >= 0; x--) {
        if (array[x] % 2 == 0 && array[x] % 3 ==0) { 
            if (array[x] < menorPar) {
                menorPar = array[x];
            }
        }
    }
    if (menorPar != 200) {
        std::cout << "O menor valor par e multiplo de 3 é: " << menorPar << std::endl;
    } else {
        std::cout << "Não há valores pares e multiplos de 3 no array" << std::endl;
    }
}
void metodo1113() {
    std::ifstream f("dados.txt"); 
    if (!f) {
        std::cerr << "Erro na abertura " << std::endl; 
        exit(1);
    }
    int array[30], tamanho;
    tamanho = contarArray(f, array);
    f.close();
    procurarPar(array, tamanho);
}


int contarArray(std::ifstream &f, int *array) {
    int valor, count = 0;
    while (f >> valor) { 
        array[count++] = valor;
    }
    return count;
}
void posicaoArray(int *array, int posicao1, int posicao2, int tamanho) {
    int total = 0;
    for (int x = 0; x < tamanho; x++) {
        if (array[x] > posicao1 && array[x] < posicao2) {
            total += array[x];
        }
    }
    std::cout << "A soma dos valores entre as posições é: " << total << std::endl;
}
void metodo1114() {
    std::ifstream f("dados.txt");
    if (!f) {
        std::cerr << "Erro na abertura" << std::endl;
        exit(1);
    }
    int posicao1, posicao2, array[30], tamanho;
    std::cout << "Digite duas posições de um arranjo para serem o limite: ";
    std::cin >> posicao1 >> posicao2;
    tamanho = contarArray(f, array);
    f.close();
    posicaoArray(array, posicao1, posicao2, tamanho);
}


int contarArray(std::ifstream &f, int *array) {
    int valor, count = 0;
    while (f >> valor) { 
        array[count++] = valor;
    }
    return count;
}
void posicaoArray(int *array, int posicao1, int posicao2, int tamanho) {
    int total = 0, count = 0, media = 0;
    for (int x = 0; x < tamanho; x++) {
        if (array[x] > posicao1 && array[x] < posicao2) {
            count++;
            total+=array[x];
        }
    }
    media=total/count;
    std::cout << "A media dos valores entre as posições é: " << media << std::endl;
}
void metodo1115() {
    std::ifstream f("dados.txt");
    if (!f) {
        std::cerr << "Erro na abertura" << std::endl;
        exit(1);
    }
    int posicao1, posicao2, array[30], tamanho;
    std::cout << "Digite duas posições de um arranjo para serem o limite: ";
    std::cin >> posicao1 >> posicao2;
    tamanho = contarArray(f, array);
    f.close();
    posicaoArray(array, posicao1, posicao2, tamanho);
}


int contarArray(std::ifstream &f, int *array) {
    int valor, count = 0;
    while (f >> valor) { 
        array[count++] = valor;
    }
    return count;
}
void positivos(int *array, int tamanho) {
    int count = 0;
    for (int x = 0; x < tamanho; x++) {
        if (array[x] > 0) {
            count++;
        }
    }
    if(count==tamanho-1){
    std::cout << "Todos os valores são positivos " << std::endl;
    }else{
        std::cout << "Não são todos os valores que são positivos " << std::endl;
    }
}
void metodo1116() {
    std::ifstream f("dados.txt");
    if (!f) {
        std::cerr << "Erro na abertura" << std::endl;
        exit(1);
    }
    int array[30], tamanho;
    tamanho = contarArray(f, array);
    f.close();
    positivos(array, tamanho);
}


int contarArray(std::ifstream &f, int *array) {
    int valor, count = 0;
    while (f >> valor) { 
        array[count++] = valor;
    }
    return count;
}
void array_ordenado(int *array, int tamanho) {
    bool ordenado = true;
    for (int x = 0; x < tamanho-1; x++) {
        if (array[x] < array[x+1]) {
            ordenado = false;
        }
    }
    if(ordenado){
    std::cout << "Os valores estão ordenados em ordem decrescente" << std::endl;
    }else{
        std::cout << "Os valores não estão ordenados em ordem decrescente" << std::endl;
    }
}
void metodo1117() {
    std::ifstream f("dados.txt");
    if (!f) {
        std::cerr << "Erro na abertura" << std::endl;
        exit(1);
    }
    int array[30], tamanho;
    tamanho = contarArray(f, array);
    f.close();
    array_ordenado(array, tamanho);
}


int contarArray(std::ifstream &f, int *array) {
    int valor, count = 0;
    while (f >> valor) { 
        array[count++] = valor;
    }
    return count;
}
void procurar_numero(int *array, int posicao1, int posicao2, int tamanho, int num) {
    int count = 0;
    for (int x = 0; x < tamanho; x++) {
        if(array[x]>posicao1 && array[x]<posicao2){
        if (array[x] == num) {
            count++;
        }
        }
    }if(count>0){
    std::cout << "O numero digitado esta presente no array" << std::endl;
    }else{
        std::cout << "O numero digitado não esta no array" << std::endl;
    }
}
void metodo1118() {
    std::ifstream f("dados.txt");
    if (!f) {
        std::cerr << "Erro na abertura" << std::endl;
        exit(1);
    }
    int posicao1, posicao2, array[30], tamanho, num;
    std::cout << "Digite duas posições de um arranjo para serem o limite: ";
    std::cin >> posicao1 >> posicao2;
    std::cout << "Digite um numero para verificar se ele existe no array: ";
    std::cin >> num;
    tamanho = contarArray(f, array);
    f.close();
    procurar_numero(array, posicao1, posicao2, tamanho, num);
}


int contarArray(std::ifstream &f, int *array) {
    int valor, count = 0;
    while (f >> valor) { 
        array[count++] = valor;
    }
    return count;
}
void escalarDados(int *array, int tamanho, int constante, int posicao1, int posicao2) {
    for (int x = 0; x < tamanho; x++) {
        if (array[x] > posicao1 && array[x] < posicao2) {
            array[x] *= constante;
        }
    }
    std::cout << "Valores escalados: ";
    for (int x = 0; x < tamanho; x++) {
        std::cout << array[x] << " ";
    }
    std::cout << std::endl;
}
void metodo1119() {
    std::ifstream f("dados.txt");
    if (!f) {
        std::cerr << "Erro na abertura " << std::endl;
        exit(1);
    }
    int array[30], tamanho;
    tamanho = contarArray(f, array);
    f.close();
    int constante, posicao1, posicao2;
    std::cout << "Digite duas posições de um arranjo para serem o limite: ";
    std::cin >> posicao1 >> posicao2;
    std::cout << "Digite a constante para multiplicar os valores: ";
    std::cin >> constante;
    escalarDados(array, tamanho, constante, posicao1, posicao2);
}


int contarArray(std::ifstream &f, int *array) {
    int valor, count = 0;
    while (f >> valor) { 
        array[count++] = valor;
    }
    return count;
}
void ordenarDecrescente(int *array, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            if (array[i] < array[j]) {
                std::swap(array[i], array[j]);
            }
        }
    }
}
void metodo1120() {
    std::ifstream f("dados.txt");
    if (!f) {
        std::cerr << "Erro na abertura " << std::endl;
        exit(1);
    }
    int array[30], tamanho;
    tamanho = contarArray(f, array);
    f.close();
    ordenarDecrescente(array, tamanho);
    std::cout << "Valores ordenados em ordem decrescente: ";
    for (int x = 0; x < tamanho; x++) {
        std::cout << array[x] << " ";
    }
    std::cout << std::endl;
}


int contarArray(std::ifstream &f, int *array) {
    int valor, count = 0;
    while (f >> valor) { 
        array[count++] = valor;
    }
    return count;
}
bool diferentes(int *array1, int *array2, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (array1[i] != array2[i]) {
            return true; 
        }
    }
    return false; 
}
void metodo11E1() {
    std::ifstream f1("dados1.txt");
    std::ifstream f2("dados2.txt");
    if (!f1 || !f2) {
        std::cerr << "Erro na abertura " << std::endl;
        exit(1);
    }
    int array1[30], array2[30], tamanho1, tamanho2;
    tamanho1 = contarArray(f1, array1);
    tamanho2 = contarArray(f2, array2);
    f1.close();
    f2.close();
    if (tamanho1 != tamanho2) {
        std::cout << "Os arrays são diferentes\n" << std::endl;
        return;
    }
    if (diferentes(array1, array2, tamanho1)) {
        std::cout << "Os arrays são diferentes em pelo menos uma posição" << std::endl;
    } else {
        std::cout << "Os arrays são iguais" << std::endl;
    }
}


int contarArray(std::ifstream &f, int *array) {
    int valor, count = 0;
    while (f >> valor) { 
        array[count++] = valor;
    }
    return count;
}
void calcularDiferencas(int *array1, int *array2, int tamanho) {
    int diferencas[30]; 
    for (int i = 0; i < tamanho; i++) {
        diferencas[i] = array1[i] - array2[i];
    }
    std::cout << "Diferenças entre os arrays: " << std::endl;
    for (int i = 0; i < tamanho; i++) {
        std::cout << "Posição " << i << ": " << diferencas[i] << std::endl;
    }
}
void metodo11E2() {
    std::ifstream f1("dados1.txt");
    std::ifstream f2("dados2.txt");
    if (!f1 || !f2) {
        std::cerr << "Erro na abertura" << std::endl;
        exit(1);
    }
    int array1[30], array2[30], tamanho1, tamanho2;
    tamanho1 = contarArray(f1, array1);
    tamanho2 = contarArray(f2, array2);
    f1.close();
    f2.close();
    if (tamanho1 != tamanho2) {
        std::cout << "Os arrays têm tamanhos diferentes" << std::endl;
        return;
    }
    calcularDiferencas(array1, array2, tamanho1);
}



int main() {
    int opcao;
    do {
        cout << "Digite um número entre 1-12 (ou 0 para sair): ";
        cin >> opcao;
        switch(opcao) {
            case 1: metodo1111(); break;
            /*
Digite quantos números você deseja que sejam gerados: 5
5 números irão ser gravados no arquivo
Número aleatório 0: 42
Número aleatório 1: 87
Número aleatório 2: 15
Número aleatório 3: 63
Número aleatório 4: 29
            */
            case 2: metodo1112(); break;
            /*
5 9 12 18 7 20 24
O maior valor par é: 24
            */
            case 3: metodo1113(); break;
            /*
5 9 12 18 7 20 24
O menor valor par e múltiplo de 3 é: 12
            */
            case 4: metodo1114(); break;
            /*
5 12 3 18 7 20 15 9 4
Digite duas posições de um arranjo para serem o limite: 10 17
A soma dos valores entre as posições é: 27
            */
            case 5: metodo1115(); break;
            /*
5 12 3 18 7 20 15 9 4
Digite duas posições de um arranjo para serem o limite: 10 17
A média dos valores entre as posições é: 13
            */
            case 6: metodo1116(); break;
            /*
5 -3 8 6 -2 0 7
Não são todos os valores que são positivos
            */
            case 7: metodo1117(); break;
            /*
5 4 3 2 1
Os valores estão ordenados em ordem decrescente
            */
            case 8: metodo1118(); break;
            /*
1 2 3 4 5 6 7 8 9 10
Digite duas posições de um arranjo para serem o limite: 2 8
Digite um número para verificar se ele existe no array: 5
O número digitado está presente no array.
            */
            case 9: metodo1119(); break;
            /*
10
20
30
40
50
Digite duas posições de um arranjo para serem o limite: 20 40
Digite a constante para multiplicar os valores: 2
Valores escalados: 10 40 60 80 50
            */
            case 10: metodo1120(); break;
            /*
10
20
30
40
50
Valores ordenados em ordem decrescente: 50 40 30 20 10 
            */
            case 11: metodo11E1(); break;
            /*
10
20
30

10
21
30

Os arrays são diferentes em pelo menos uma posição.
            */
            case 12: metodo11E2(); break;
            /*
10
20
30

5
15
25

Diferenças entre os arrays:
Posição 0: 5
Posição 1: 5
Posição 2: 5
            */
            default: cout << "Opção inválida" << endl; break;
        }
    } while (opcao != 0); 
    return 0;
}
