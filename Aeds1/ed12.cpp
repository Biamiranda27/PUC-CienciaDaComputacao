

#include <iostream> //serve para output e input (cout e cin)
#include<string>
#include<ctime>
#include<fstream> //manipular arquivo
#include<vector> //armazenar dados de forma dinamica
#include<sstream> //manipular cada linha de texto
#include<cstdlib>


void numeros(std::ofstream &f, int matriz[][30], int linha, int coluna){
    srand(time(NULL));
    int x,y;
    for(x = 0; x < linha; x++){
        for(y = 0; y < coluna; y++){
            matriz[x][y]= rand() % 100;
            std::cout<< "O numero gerado para a matriz[" <<x<< "][" <<y<< "] é: " <<matriz[x][y]<< " " << "\n";
            f<< matriz[x][y] <<" "; //imprime no arquivo
        }
        f<<"\n";
    }
}
void metodo1211(){
    std::ofstream f("dados.txt"); //abri arquivo para escrita
    if(!f){ //se der erro na abertura do arquivo
        std::cerr<< "Erro na abertura" <<std::endl; //cerr é para mensagens de erro
        exit (1);
    }
    int matriz[30][30], linha, coluna, tamanho;
    std::cout<< "Digite o numero de linhas e colunas da matriz: "; //printa
    std::cin>> linha;
    std::cin>> coluna; //ler e armazenar
    tamanho = linha*coluna;
    //f<<tamanho<< "\n" <<std::endl;
    numeros(f, matriz, linha, coluna);
    f.close(); //fecha o arquivo
}


void novaMatriz(int linhas, int colunas, int constante, int matriz[][30]) {
    for (int x = 0; x < linhas; x++) {
        for (int y = 0; y < colunas; y++) {
            std::cout << "O valor da matriz [" << x << "][" << y << "] multiplicado pela constante é: "
                      << matriz[x][y] * constante << std::endl;
        }
    }
}

void lerMatriz(std::ifstream &arquivo, int &linhas, int &colunas, int matriz[][30]) {
    linhas = 0;
    colunas = 0;
    int valor, colunaTemp = 0;
    char linha[256];

    // Lê cada linha do arquivo
    while (arquivo.getline(linha, 256)) {
        colunaTemp = 0;
        char *ptr = linha;
        
        // Lê cada número inteiro da linha
        while (*ptr != '\0') {
            if (std::isdigit(*ptr) || (*ptr == '-' && std::isdigit(*(ptr + 1)))) {
                matriz[linhas][colunaTemp++] = std::atoi(ptr);
                while (std::isdigit(*ptr) || *ptr == '-') ptr++;
            }
            if (*ptr) ptr++;
        }

        if (colunas == 0) {
            colunas = colunaTemp;
        } else if (colunaTemp != colunas) {
            std::cerr << "Erro: As linhas do arquivo não têm o mesmo número de colunas." << std::endl;
            return;
        }
        linhas++;
    }

    if (linhas == 0 || colunas == 0) {
        std::cerr << "Erro: Matriz vazia ou formato inválido no arquivo." << std::endl;
        return;
    }

    std::cout << "Dimensões da matriz: " << linhas << "x" << colunas << std::endl;
    std::cout << "Matriz lida do arquivo:" << std::endl;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void metodo1212() {
    std::ifstream arquivo("dados.txt"); // abre o arquivo para leitura
    if (!arquivo.is_open()) {
        std::cerr << "Erro na abertura do arquivo." << std::endl;
        exit(1);
    }

    int linhas, colunas, matriz[30][30];
    const int CONSTANTE = 3;

    lerMatriz(arquivo, linhas, colunas, matriz);
    arquivo.close();

    if (linhas > 0 && colunas > 0) {
        novaMatriz(linhas, colunas, CONSTANTE, matriz);
    } else {
        std::cerr << "Erro: Não foi possível processar a matriz." << std::endl;
    }
}


void matrizIdentidade(int linhas, int colunas, int matriz[][30]){
    int x, y, count1 = 0, count2 = 0, a;
    a = (linhas*colunas)-linhas;
    for(x = 0; x < linhas; x++){
        for(y = 0; y < colunas; y++){
            if(x==y){
                if(matriz[x][y]==1){
                count1++;
                }
            } else if(x!=y){
                if(matriz[x][y]==0){
                    count2++;
                }
            }
        }
    }
    if(count1 == linhas && count2 == a){
        std::cout<< "A matriz lida é identidade";
    }else{
        std::cout<< "A matriz lida não é identidade";
    }
}
void ler_matriz(std::ifstream &arquivo, int &linhas, int &colunas, int matriz[][30]) {
    linhas = 0;
    colunas = 0;
    int valor, colunaTemp = 0;
    char linha[256];
    while (arquivo.getline(linha, 256)) {
        colunaTemp = 0;
        char *ptr = linha;
        while (*ptr != '\0') {
            if (std::isdigit(*ptr) || (*ptr == '-' && std::isdigit(*(ptr + 1)))) {
                matriz[linhas][colunaTemp++] = std::atoi(ptr);
                while (std::isdigit(*ptr) || *ptr == '-') ptr++;
            }
            if (*ptr) ptr++;
        }
        if (colunas == 0) {
            colunas = colunaTemp;
        } else if (colunaTemp != colunas) {
            std::cerr << "Erro: As linhas do arquivo não têm o mesmo número de colunas." << std::endl;
            return;
        }
        linhas++;
    }
    if (linhas == 0 || colunas == 0) {
        std::cerr << "Erro: Matriz vazia ou formato inválido no arquivo." << std::endl;
        return;
    }
    std::cout << "Dimensões da matriz: " << linhas << "x" << colunas << std::endl;
    std::cout << "Matriz lida do arquivo:" << std::endl;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void metodo1213(){
    std::ifstream f("dados.txt"); //abre o arquivo para leitura
    if(!f.is_open()){
        std::cerr<< "Erro na abertura" <<std::endl;
        exit(1);
    }
    int linhas, colunas, matriz[30][30];
    ler_matriz(f,linhas,colunas,matriz);
    if(linhas == colunas){
        matrizIdentidade(linhas, colunas, matriz);
    }else{
        std::cout<< "A matriz lida não tem o numero de linhas igual ao de colunas, então não é uma matriz identidade ";
    }
    f.close();
}


void numeros1(std::ofstream &a, int matriz1[][30], int linhas1, int colunas1){
    srand(time(NULL));
    int x,y;
    for(x = 0; x < linhas1; x++){
        for(y = 0; y < colunas1; y++){
            matriz1[x][y]= rand() % 100;
            std::cout<< "O numero gerado para a matriz1[" <<x<< "][" <<y<< "] é: " <<matriz1[x][y]<< " " << "\n";
            a<< matriz1[x][y]<< " "; //imprime no arquivo
        }
        a<<"\n";
    }
}
void numeros2(std::ofstream &b, int matriz2[][30], int linhas2, int colunas2){
    srand(time(NULL));
    int x,y;
    for(x = 0; x < linhas2; x++){
        for(y = 0; y < colunas2; y++){
            matriz2[x][y]= rand() % 100;
            std::cout<< "O numero gerado para a matriz2[" <<x<< "][" <<y<< "] é: " <<matriz2[x][y]<< " " << "\n";
            b<< matriz2[x][y]<< " "; //imprime no arquivo
        }
        b<<"\n";
    }
}
void igualdade(int matriz1[][30], int linhas1, int colunas1, int matriz2[][30]){
    int x, y, count = 0, a;
    a = linhas1 * colunas1;
    for(x = 0; x < linhas1; x++){
        for(y = 0; y < colunas1; y++){
            if(matriz1[x][y] == matriz2[x][y]){
                count++;
            }
        }
    }if(count == a){
        std::cout<< "As matrizes tem igualdade";
    }else{
        std::cout<< "As matrizes não tem igualdade";
    }
}
void metodo1214(){
    std::ofstream a("dados1.txt");
    if(!a){
        std::cerr<< "Erro na abertura" <<std::endl;
        exit(1);
    }
    std::ofstream b("dados2.txt");
    if(!b){
        std::cerr<< "Erro na abertura" <<std::endl;
        exit(1);
    }
    int linhas1, colunas1, linhas2, colunas2, matriz1[30][30], matriz2[30][30];
    std::cout<< "Digite o numero de linhas e colunas para a matriz1: ";
    std::cin>> linhas1 >> colunas1;
    std::cout<< "Digite o numero de linhas e colunas para a matriz2: ";
    std::cin>> linhas2 >> colunas2;
    if(linhas1 == linhas2 && colunas1 == colunas2){
        numeros1(a, matriz1, linhas1, colunas1);
    numeros2(b, matriz2, linhas2, colunas2);
        igualdade(matriz1, linhas1, colunas1, matriz2);
    }else{
        std::cout<< "As duas matrizes não tem o tamanho de linhas e/ou colunas da primeira matriz igual a segunda";
    }
    a.close();
    b.close();
}


void ler_matriz1(std::ifstream &a, int &linhas1, int &colunas1, int matriz1[][30]) {
    linhas1 = 0;
    colunas1 = 0;
    int valor, colunaTemp = 0;
    char linha[256];
    while (a.getline(linha, 256)) {
        colunaTemp = 0;
        char *ptr = linha;
        while (*ptr != '\0') {
            if (std::isdigit(*ptr) || (*ptr == '-' && std::isdigit(*(ptr + 1)))) {
                matriz1[linhas1][colunaTemp++] = std::atoi(ptr);
                while (std::isdigit(*ptr) || *ptr == '-') ptr++;
            }
            if (*ptr) ptr++;
        }
        if (colunas1 == 0) {
            colunas1 = colunaTemp;
        } else if (colunaTemp != colunas1) {
            std::cerr << "Erro: As linhas do arquivo não têm o mesmo número de colunas." << std::endl;
            return;
        }
        linhas1++;
    }
    if (linhas1 == 0 || colunas1 == 0) {
        std::cerr << "Erro: Matriz vazia ou formato inválido no arquivo." << std::endl;
        return;
    }
    std::cout << "Dimensões da matriz1: " << linhas1 << "x" << colunas1 << std::endl;
    std::cout << "Matriz lida do arquivo:" << std::endl;
    for (int i = 0; i < linhas1; i++) {
        for (int j = 0; j < colunas1; j++) {
            std::cout << matriz1[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void ler_matriz2(std::ifstream &b, int &linhas2, int &colunas2, int matriz2[][30]) {
    linhas2 = 0;
    colunas2 = 0;
    int valor, colunaTemp = 0;
    char linha[256];
    while (b.getline(linha, 256)) {
        colunaTemp = 0;
        char *ptr = linha;
        while (*ptr != '\0') {
            if (std::isdigit(*ptr) || (*ptr == '-' && std::isdigit(*(ptr + 1)))) {
                matriz2[linhas2][colunaTemp++] = std::atoi(ptr);
                while (std::isdigit(*ptr) || *ptr == '-') ptr++;
            }
            if (*ptr) ptr++;
        }
        if (colunas2 == 0) {
            colunas2 = colunaTemp;
        } else if (colunaTemp != colunas2) {
            std::cerr << "Erro: As linhas do arquivo não têm o mesmo número de colunas." << std::endl;
            return;
        }
        linhas2++;
    }
    if (linhas2 == 0 || colunas2 == 0) {
        std::cerr << "Erro: Matriz vazia ou formato inválido no arquivo." << std::endl;
        return;
    }
    std::cout << "Dimensões da matriz2: " << linhas2 << "x" << colunas2 << std::endl;
    std::cout << "Matriz lida do arquivo:" << std::endl;
    for (int i = 0; i < linhas2; i++) {
        for (int j = 0; j < colunas2; j++) {
            std::cout << matriz2[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void soma(int matriz1[][30], int linhas, int colunas, int matriz2[][30], int matriz3[][30]){
    int x, y;
    for(x = 0; x < linhas; x++){
        for(y = 0; y < colunas; y++){
            matriz3[x][y] = matriz1[x][y] + matriz2[x][y];
            std::cout<< "O numero gerado para a matriz3[" <<x<< "][" <<y<< "] é: " <<matriz3[x][y]<< " " << "\n";
            //std::cin>> matriz3[x][y];
        }
    }
}
void metodo1215(){
std::ifstream a("dados1.txt"); 
    if(!a.is_open()){
        std::cerr<< "Erro na abertura" <<std::endl;
        exit(1);
    }
    std::ifstream b("dados2.txt"); 
    if(!b.is_open()){
        std::cerr<< "Erro na abertura" <<std::endl;
        exit(1);
    }
    int linhas1, colunas1, linhas2, colunas2, matriz1[30][30], matriz2[30][30], matriz3[30][30];
    ler_matriz1(a, linhas1, colunas1, matriz1);
    ler_matriz2(b, linhas2, colunas2, matriz2);
    if(linhas1 == linhas2 && colunas1 == colunas2){
        soma(matriz1,linhas1,colunas1,matriz2,matriz3);
    }
    a.close();
    b.close();
}


void finalMatriz(int linhas, int colunas, int matriz[][30], int MULTI){
    int x, y, z;
        for(y = 0; y < colunas; y++){
                z = matriz[0][y]+matriz[1][y]*MULTI;
                std::cout<< z << " ";
        }
   std::cout<< "\n" ;
    for(x = 1; x < linhas; x++){
        for(y = 0; y < colunas; y++){
            std::cout<<" "<<matriz[x][y]<<" ";
        }
    }
}
void lerMatriz1(std::ifstream &f, int &linhas, int &colunas, int matriz[][30]) {
    linhas = 0;
    colunas = 0;
    int valor, colunaTemp = 0;
    char linha[256];
    while (f.getline(linha, 256)) {
        colunaTemp = 0;
        char *ptr = linha;
        while (*ptr != '\0') {
            if (std::isdigit(*ptr) || (*ptr == '-' && std::isdigit(*(ptr + 1)))) {
                matriz[linhas][colunaTemp++] = std::atoi(ptr);
                while (std::isdigit(*ptr) || *ptr == '-') ptr++;
            }
            if (*ptr) ptr++;
        }
        if (colunas == 0) {
            colunas = colunaTemp;
        } else if (colunaTemp != colunas) {
            std::cerr << "Erro: As linhas do arquivo não têm o mesmo número de colunas." << std::endl;
            return;
        }
        linhas++;
    }
    if (linhas == 0 || colunas == 0) {
        std::cerr << "Erro: Matriz vazia ou formato inválido no arquivo." << std::endl;
        return;
    }
    std::cout << "Dimensões da matriz: " << linhas << "x" << colunas << std::endl;
    std::cout << "Matriz lida do arquivo:" << std::endl;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void metodo1216(){
    std::ifstream f("dados1.txt");
    if(!f.is_open()){
        std::cerr<< "Erro na abertura" <<std::endl;
        exit(1);
    }
    int linhas,colunas,matriz[30][30];
    const int MULTI = 2;
    lerMatriz1(f,linhas,colunas,matriz);
    finalMatriz(linhas,colunas,matriz,MULTI);
    f.close();
}


void finalMatriz(int linhas, int colunas, int matriz[][30], int MULTI){
    if(linhas<2){
        std::cerr<<"Erro: a matriz deve ter pelo menos duas linhas"<<std::endl;
        return;
    }
    int x, y, z;
        for(y = 0; y < colunas; y++){
                z = (matriz[1][y]*MULTI) - (matriz[0][y]);
                std::cout<< z << " ";
        }
    std::cout<< "\n" ;
    for(x = 1; x < linhas; x++){
        for(y = 0; y < colunas; y++){
            std::cout<<matriz[x][y]<<" ";
        }
    }
}
void lerMatriz1(std::ifstream &f, int &linhas, int &colunas, int matriz[][30]) {
    linhas = 0;
    colunas = 0;
    int valor, colunaTemp = 0;
    char linha[256];
    while (f.getline(linha, 256)) {
        colunaTemp = 0;
        char *ptr = linha;
        while (*ptr != '\0') {
            if (std::isdigit(*ptr) || (*ptr == '-' && std::isdigit(*(ptr + 1)))) {
                matriz[linhas][colunaTemp++] = std::atoi(ptr);
                while (std::isdigit(*ptr) || *ptr == '-') ptr++;
            }
            if (*ptr) ptr++;
        }
        if (colunas == 0) {
            colunas = colunaTemp;
        } else if (colunaTemp != colunas) {
            std::cerr << "Erro: As linhas do arquivo não têm o mesmo número de colunas." << std::endl;
            return;
        }
        linhas++;
    }
    if (linhas == 0 || colunas == 0) {
        std::cerr << "Erro: Matriz vazia ou formato inválido no arquivo." << std::endl;
        return;
    }
    std::cout << "Dimensões da matriz: " << linhas << "x" << colunas << std::endl;
    std::cout << "Matriz lida do arquivo:" << std::endl;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void metodo1217(){
    std::ifstream f("dados1.txt");
    if(!f.is_open()){
        std::cerr<< "Erro na abertura" <<std::endl;
        exit(1);
    }
    int linhas,colunas,matriz[30][30];
    const int MULTI = 2;
    lerMatriz1(f,linhas,colunas,matriz);
    finalMatriz(linhas,colunas,matriz,MULTI);
    f.close();
}


void procurar(int matriz[][30], int linhas, int colunas, int num){
    int x, y, count = 0, a = 0;
    for(x = 0; x < linhas; x++){
        for(y = 0; y < colunas; y++){
            if(matriz[x][y] == num){
                count++;
                a = x;
            } 
        }
    } if(count > 0){
        std::cout<< "O numero digitado existe na matriz e esta na linha "<<a;
    } else{
        std::cout<< "O numero digitado não existe na matriz";
    }
}
void lerMatriz1(std::ifstream &f, int &linhas, int &colunas, int matriz[][30]) {
    linhas = 0;
    colunas = 0;
    int valor, colunaTemp = 0;
    char linha[256];
    while (f.getline(linha, 256)) {
        colunaTemp = 0;
        char *ptr = linha;
        while (*ptr != '\0') {
            if (std::isdigit(*ptr) || (*ptr == '-' && std::isdigit(*(ptr + 1)))) {
                matriz[linhas][colunaTemp++] = std::atoi(ptr);
                while (std::isdigit(*ptr) || *ptr == '-') ptr++;
            }
            if (*ptr) ptr++;
        }
        if (colunas == 0) {
            colunas = colunaTemp;
        } else if (colunaTemp != colunas) {
            std::cerr << "Erro: As linhas do arquivo não têm o mesmo número de colunas." << std::endl;
            return;
        }
        linhas++;
    }
    if (linhas == 0 || colunas == 0) {
        std::cerr << "Erro: Matriz vazia ou formato inválido no arquivo." << std::endl;
        return;
    }
    std::cout << "Dimensões da matriz: " << linhas << "x" << colunas << std::endl;
    std::cout << "Matriz lida do arquivo:" << std::endl;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void metodo1218(){
  std::ifstream f("dados1.txt");
    if(!f.is_open()){
        std::cerr<< "Erro na abertura" <<std::endl;
        exit(1);
    }
    int num, linhas, colunas, matriz[30][30];
    std::cout<< "Digite um numero para ver se esta na matriz: ";
    std::cin>> num;  
    lerMatriz1(f,linhas,colunas,matriz);
    procurar(matriz,linhas,colunas,num);
}


void procurar(int matriz[][30], int linhas, int colunas, int num){
    int x, y, count = 0, a = 0;
    for(x = 0; x < linhas; x++){
        for(y = 0; y < colunas; y++){
            if(matriz[x][y] == num){
                count++;
                a = y;
            } 
        }
    } if(count > 0){
        std::cout<< "O numero digitado existe na matriz e esta na coluna "<<a;
    } else{
        std::cout<< "O numero digitado não existe na matriz";
    }
}
void lerMatriz1(std::ifstream &f, int &linhas, int &colunas, int matriz[][30]) {
    linhas = 0;
    colunas = 0;
    int valor, colunaTemp = 0;
    char linha[256];
    while (f.getline(linha, 256)) {
        colunaTemp = 0;
        char *ptr = linha;
        while (*ptr != '\0') {
            if (std::isdigit(*ptr) || (*ptr == '-' && std::isdigit(*(ptr + 1)))) {
                matriz[linhas][colunaTemp++] = std::atoi(ptr);
                while (std::isdigit(*ptr) || *ptr == '-') ptr++;
            }
            if (*ptr) ptr++;
        }
        if (colunas == 0) {
            colunas = colunaTemp;
        } else if (colunaTemp != colunas) {
            std::cerr << "Erro: As linhas do arquivo não têm o mesmo número de colunas." << std::endl;
            return;
        }
        linhas++;
    }
    if (linhas == 0 || colunas == 0) {
        std::cerr << "Erro: Matriz vazia ou formato inválido no arquivo." << std::endl;
        return;
    }
    std::cout << "Dimensões da matriz: " << linhas << "x" << colunas << std::endl;
    std::cout << "Matriz lida do arquivo:" << std::endl;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void metodo1219(){
  std::ifstream f("dados1.txt");
    if(!f.is_open()){
        std::cerr<< "Erro na abertura" <<std::endl;
        exit(1);
    }
    int num, linhas, colunas, matriz[30][30];
    std::cout<< "Digite um numero para ver se esta na matriz: ";
    std::cin>> num;  
    lerMatriz1(f,linhas,colunas,matriz);
    procurar(matriz,linhas,colunas,num);
}


void transpor(int matriz[][30], int linhas, int colunas){
    int x, y;
    std::cout<< "A matriz transposta é: \n";
    for(x = 0; x < colunas; x++){
        for(y = 0; y < linhas; y++){
            std::cout<< matriz[y][x] <<" ";
        }
          std::cout<<" \n ";
    } 
}
void lerMatriz1(std::ifstream &f, int &linhas, int &colunas, int matriz[][30]) {
    linhas = 0;
    colunas = 0;
    int valor, colunaTemp = 0;
    char linha[256];
    while (f.getline(linha, 256)) {
        colunaTemp = 0;
        char *ptr = linha;
        while (*ptr != '\0') {
            if (std::isdigit(*ptr) || (*ptr == '-' && std::isdigit(*(ptr + 1)))) {
                matriz[linhas][colunaTemp++] = std::atoi(ptr);
                while (std::isdigit(*ptr) || *ptr == '-') ptr++;
            }
            if (*ptr) ptr++;
        }
        if (colunas == 0) {
            colunas = colunaTemp;
        } else if (colunaTemp != colunas) {
            std::cerr << "Erro: As linhas do arquivo não têm o mesmo número de colunas." << std::endl;
            return;
        }
        linhas++;
    }
    if (linhas == 0 || colunas == 0) {
        std::cerr << "Erro: Matriz vazia ou formato inválido no arquivo." << std::endl;
        return;
    }
    std::cout << "Dimensões da matriz: " << linhas << "x" << colunas << std::endl;
    std::cout << "Matriz lida do arquivo:" << std::endl;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void metodo1220(){
  std::ifstream f("dados1.txt");
    if(!f.is_open()){
        std::cerr<< "Erro na abertura" <<std::endl;
        exit(1);
    }
    int linhas, colunas, matriz[30][30]; 
    lerMatriz1(f,linhas,colunas,matriz);
    transpor(matriz,linhas,colunas);
}


void preencherMatriz(int matriz[][30], int linhas, int colunas) {
    int numero = 1;
    int i, j;
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            matriz[i][j] = numero++;
        }
    }
}
void exibirMatriz(int matriz[][30], int linhas, int colunas) {
    int i, j;
    std::cout << "Matriz preenchida:\n";
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void metodo12E1() {
    int linhas, colunas, matriz[30][30];
    std::cout << "Digite o número de linhas e colunas da matriz (2 ou mais): ";
    std::cin >> linhas >> colunas;
    if (linhas < 2 || colunas < 2) {
        std::cerr << "Erro: A matriz deve ter pelo menos 2 linhas e 2 colunas" << std::endl;
        exit (1);
    }
    preencherMatriz(matriz, linhas, colunas);
    exibirMatriz(matriz, linhas, colunas);
}


void preencherMatriz(int matriz[][30], int linhas, int colunas) {
    int numero = 1;
    int i, j, novaMatriz[30][30];
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            matriz[i][j] = numero++;
        }
    }
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            novaMatriz[i][j] = matriz[(linhas - 1 - i)][j]; 
        }
    }
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            matriz[i][j] = novaMatriz[i][j];
        }
    }
}
void exibirMatriz(int matriz[][30], int linhas, int colunas) {
    int i, j;
    std::cout << "Matriz preenchida:\n";
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void metodo12E2() {
    int linhas, colunas, matriz[30][30];
    std::cout << "Digite o número de linhas e colunas da matriz (2 ou mais): ";
    std::cin >> linhas >> colunas;
    if (linhas < 2 || colunas < 2) {
        std::cerr << "Erro: A matriz deve ter pelo menos 2 linhas e 2 colunas" << std::endl;
        exit (1);
    }
    preencherMatriz(matriz, linhas, colunas);
    exibirMatriz(matriz, linhas, colunas);
}



int main(){
    int opcao;
    do{
       std::cout<< "Digite um numero entre 1-12: ";
       std::cin>> opcao;
       switch(opcao){
        case 1: metodo1211();break;
        /*
Terminal:
Digite o numero de linhas e colunas da matriz: 3 3
O numero gerado para a matriz[0][0] é: 37 
O numero gerado para a matriz[0][1] é: 97 
O numero gerado para a matriz[0][2] é: 7 
O numero gerado para a matriz[1][0] é: 18 
O numero gerado para a matriz[1][1] é: 96 
O numero gerado para a matriz[1][2] é: 97 
O numero gerado para a matriz[2][0] é: 28 
O numero gerado para a matriz[2][1] é: 27 
O numero gerado para a matriz[2][2] é: 88

dados.txt:
9

37      97      7
18      96      97
28      27      88
        */
       case 2: metodo1212();break;
        /*
Dimensões da matriz: 3x3
Matriz lida do arquivo:
76 61 82 
17 6 24 
80 55 34 
O valor da matriz [0][0] multiplicado pela constante é: 228
O valor da matriz [0][1] multiplicado pela constante é: 183
O valor da matriz [0][2] multiplicado pela constante é: 246
O valor da matriz [1][0] multiplicado pela constante é: 51
O valor da matriz [1][1] multiplicado pela constante é: 18
O valor da matriz [1][2] multiplicado pela constante é: 72
O valor da matriz [2][0] multiplicado pela constante é: 240
O valor da matriz [2][1] multiplicado pela constante é: 165
O valor da matriz [2][2] multiplicado pela constante é: 102
        */
       case 3: metodo1213();break;
        /*
Dimensões da matriz: 3x3
Matriz lida do arquivo:
76 61 82 
17 6 24 
80 55 34 
A matriz lida não é identidade
        */
       case 4: metodo1214();break;
        /*
Terminal:
Digite o numero de linhas e colunas para a matriz1: 2 3
Digite o numero de linhas e colunas para a matriz2: 2 3
O numero gerado para a matriz1[0][0] é: 95 
O numero gerado para a matriz1[0][1] é: 65 
O numero gerado para a matriz1[0][2] é: 77 
O numero gerado para a matriz1[1][0] é: 78 
O numero gerado para a matriz1[1][1] é: 71 
O numero gerado para a matriz1[1][2] é: 35 
O numero gerado para a matriz2[0][0] é: 95 
O numero gerado para a matriz2[0][1] é: 65 
O numero gerado para a matriz2[0][2] é: 77 
O numero gerado para a matriz2[1][0] é: 78 
O numero gerado para a matriz2[1][1] é: 71 
O numero gerado para a matriz2[1][2] é: 35 
As matrizes tem igualdade

dados1.txt:
95 65 77 
78 71 35 

dados2.txt:
95 65 77 
78 71 35
        */
       case 5: metodo1215();break;
        /*
Dimensões da matriz1: 2x3
Matriz lida do arquivo:
95 65 77 
78 71 35 
Dimensões da matriz2: 2x3
Matriz lida do arquivo:
95 65 77 
78 71 35 
O numero gerado para a matriz3[0][0] é: 190 
O numero gerado para a matriz3[0][1] é: 130 
O numero gerado para a matriz3[0][2] é: 154 
O numero gerado para a matriz3[1][0] é: 156 
O numero gerado para a matriz3[1][1] é: 142 
O numero gerado para a matriz3[1][2] é: 70
        */
       case 6: metodo1216();break;
        /*
Dimensões da matriz: 2x3
Matriz lida do arquivo:
95 65 77 
78 71 35 
251 207 147 
 78  71  35
        */
       case 7: metodo1217();break;
        /*
Dimensões da matriz: 2x3
Matriz lida do arquivo:
95 65 77 
78 71 35 
61 77 -7 
78 71 35
        */
       case 8: metodo1218();break;
        /*
Digite um numero para ver se esta na matriz: 35
Dimensões da matriz: 2x3
Matriz lida do arquivo:
95 65 77 
78 71 35 
O numero digitado existe na matriz e esta na linha 1
        */
       case 9: metodo1219();break;
        /*
Digite um numero para ver se esta na matriz: 35
Dimensões da matriz: 2x3
Matriz lida do arquivo:
95 65 77 
78 71 35 
O numero digitado existe na matriz e esta na coluna 2
        */
       case 10: metodo1220();break;
        /*
Dimensões da matriz: 2x3
Matriz lida do arquivo:
95 65 77 
78 71 35 
A matriz transposta é: 
95 78  
 65 71  
 77 35
        */
       case 11: metodo12E1();break;
        /*
Digite o número de linhas e colunas da matriz (2 ou mais): 2 2
Matriz preenchida:
1 2 
3 4 
        */
       case 12: metodo12E2();break;
        /*
Digite o número de linhas e colunas da matriz (2 ou mais): 3 3
Matriz preenchida:
7 8 9 
4 5 6 
1 2 3 
        */
       default: std::cout<< "Opção invalida"; break;
       }
    }while(opcao!=0);
}
