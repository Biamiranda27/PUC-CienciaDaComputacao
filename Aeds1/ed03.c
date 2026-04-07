

 #include <stdio.h>
 #include <string.h>

 void metodo0311(char palavra[]){
   int i;
  printf("Digite uma palavra: ");
  scanf("%s", &palavra[0]);
  for(i=0;i<=strlen(palavra); i++){
    if(palavra[i]>='A' && palavra[i]<='Z'){
      printf("A letra %d da palavra é maiúscula\n", i+1);
    }
    else if(palavra[i]>='a' && palavra[i]<='z'){
      printf("A letra %d da palavra é minuscula\n",i+1);
    }
  }
 }


 void metodo0312(char palavra[]){
    int i, count=0;
    printf("Digite uma palavra: ");
    scanf("%s", &palavra[i]);
    for(i=0;i<=strlen(palavra); i++){
        if(palavra[i]>='a' && palavra[i]<='z'){
            count++;
            printf("A letra %d da palavra é minuscula\n", i+1);
        }
    }
  printf("A palavra digitada tem %d letras minúsculas", count);
 }


 void metodo0313(char palavra[]){
    int i, count=0;
    printf("Digite uma palavra: ");
    scanf("%s", &palavra[i]);
    for(i=strlen(palavra);i>=0; i--){
        if(palavra[i]>='a' && palavra[i]<='z'){
            count++;
            printf("A letra %d da palavra é minuscula\n", i+1);
        }
    }
  printf("A palavra digitada tem %d letras minúsculas", count);
 }


void metodo0314(char caracter[]){
    int i, count=0;
    printf("Digite uma cadeia de caracteres: ");
    scanf("%s", &caracter[i]);
    for(i=0;i<=strlen(caracter); i++){
        if(caracter[i]>=97 && caracter[i]<=122 || caracter[i]>=65 && caracter[i]<=90){
            count++;
            printf("O caracter na posição %d é uma letra\n", i+1);
        }
        }
    printf("A cadeia de caracteres digitado tem %d letras", count);
}


void metodo0315(char caracter[]){
    int i, count=0;
    printf("Digite uma cadeia de carateres: ");
    scanf("%s", &caracter[i]);
    for(i=strlen(caracter);i>=0;i--){
        if(caracter[i]>=48 && caracter[i]<=57){
            count++;
            printf("O caracter na posição %d é um dígito \n", i+1);
        }
    }
    printf("A cadeia de caracteres digitado tem %d dígitos", count);
}


void metodo0316(char caracter[]){
    int i, count=0;
    printf("Digite uma cadeia de caracteres: ");
    scanf("%s", &caracter[i]);
    for(i=0;i<strlen(caracter); i++){
        if(!(caracter[i]>='a' && caracter[i]<='z' || caracter[i]>='A' && caracter[i]<='Z'|| caracter[i]>='0'&& caracter[i]<='9')){
            count++;
            printf("O caracter na posição %d é um caractere especial\n", i+1);
        }
        }
    printf("A cadeia de caracteres digitado tem %d caractere especial", count);
}


void metodo0317(int a, int b){
    int n=0, i=0, count=0;
    printf("Digite dois numeros inteiros: ");
    scanf("%d %d", &a, &b);
    printf("Digite a quantidade de numeros a serem testados: ");
    scanf("%d", &n);
    int numeros[n];
    printf("Digite %d numeros: ", n);
    for(i=0;i<n;i++){
    scanf("%d", &numeros[i]);
        if(numeros[i]>=a && numeros[i]<=b && numeros[i]%5==0){
            count++;
            printf("O número %d esta dentro do limite e é divisivel por 5\n", numeros[i]);
        }
    }
    printf("Tem %d numeros dentro do intervalo e divisiveis por 5", count);
}


void metodo0318(int a, int b){
    int n=0, i=0, count=0;
    printf("Digite dois valores inteiros: ");
    scanf("%d %d", &a, &b);
    printf("Digite a quantidade de numeros a serem testados: ");
    scanf("%d", &n);
    printf("Digite %d numeros: ", n);
    int numeros[n];
    for(i=0;i<n;i++){
        scanf("%d", &numeros[i]);
        if(numeros[i]>=a && numeros[i]<=b && numeros[i]%3==0 && numeros[i]%5!=0){
            count++;
            printf("O número %d está dentro do limite e é divisivel por 3 mas não por 5\n", numeros[i]);
        }
    }
    printf("Tem %d numeros dentro do intervalo divisivel por 3 mas não por 5", count);
}


void metodo0319(double A, double B){
    int n=0, i=0, count=0;
    printf("Digite dois valores reais, sendo o primeiro menor que o segundo: ");
    scanf("%lf %lf", &A, &B);
    printf("Digite a quantidade de numeros a serem testados: ");
    scanf("%d", &n);
    double numeros[n];
    printf("Digite %d numeros: ", n);
    for(i=0;i<n;i++){
        scanf("%lf", &numeros[i]);
        if(numeros[i]>A && numeros[i]<B && (int)numeros[i]%2!=0){
            count++;
            printf("O numeros %lf esta dentro do limite e é impar\n", numeros[i]);
        }
    }
    printf("Tem %d numeros dentro do intervalo e impar", count);
}


void metodo0320(double A, double B){
    int n=0, i=0, count=0;
    printf("Digite dois valores reais, maiores que 0 e menores que 1: ");
    scanf("%lf %lf", &A, &B);
    printf("Digite a quantidade de numeros a serem testados: ");
    scanf("%d", &n);
    printf("Digite %d numeros: ", n);
    double numeros[n];
    double novo[n];
    for(i=0;i<n;i++){
        scanf("%lf", &numeros[i]);
        novo[i]=(numeros[i]-(int)numeros[i]);
        if(novo[i]<A || novo[i]>B){
            count++;
            printf("O numeros %lf esta fora do limite\n", novo[i]);
        }
    }
    printf("Tem %d numeros fora do intervalo", count);
}


void metodo03E1(char palavra[40]){
    int i=0;
    getchar();
    printf("Digite uma sequência: ");
    fgets(palavra,40,stdin);
    printf("A sequência sem os simbolos alfanuméricos é: ");
    for(i=0;i<strlen(palavra);i++){
        if(!(palavra[i]>='a' && palavra[i]<='z' || palavra[i]>='A' && palavra[i]<='Z' || palavra[i]>='0' && palavra[i]<='9')){
            printf("%c", palavra[i]);
        }
    }
}


void metodo03E2(char palavra[40]){
    int i=0;
    char nova_palavra[40];
    getchar();
    printf("Digite uma sequência: ");
    fgets(palavra,40,stdin);
    for(i=0;i<strlen(palavra);i++){
        if(!(palavra[i]>='a' && palavra[i]<='z' || palavra[i]>='A' && palavra[i]<='Z')){
            nova_palavra[i]=palavra[i];
        }
    }
    if(strcmp(nova_palavra, palavra)==0){
    printf("A sequência não tem letras e é: %s", nova_palavra);
    }
}

int main(){
    char palavra[40], caracter[40];
    int a, b, opcao;
    double A, B;
    do{
        printf("\nDigite um número entre 1 a 12: ");
        scanf("%d", &opcao);
    switch(opcao){
        case 1: metodo0311(palavra);break;
            /*
              Digite uma palavra: PaLaVrA
              A letra 1 da palavra é maiúscula
              A letra 2 da palavra é minuscula
              A letra 3 da palavra é maiúscula
              A letra 4 da palavra é minuscula
              A letra 5 da palavra é maiúscula
              A letra 6 da palavra é minuscula
              A letra 7 da palavra é maiúscula
            */
        case 2: metodo0312(palavra);break;
        /*
           Digite uma palavra: PaLaVrA
           A letra 2 da palavra é minuscula
           A letra 4 da palavra é minuscula
           A letra 6 da palavra é minuscula
           A palavra digitada tem 3 letras minúsculas
        */
        case 3: metodo0313(palavra);break;
        /*
           Digite uma palavra: PaLaVrA
           A letra 6 da palavra é minuscula
           A letra 4 da palavra é minuscula
           A letra 2 da palavra é minuscula
           A palavra digitada tem 3 letras minúsculas
        */
        case 4: metodo0314(caracter);break;
        /*
           Digite uma cadeia de caracteres: P4LaVr@
           O caracter na posição 1 é uma letra
           O caracter na posição 3 é uma letra
           O caracter na posição 4 é uma letra
           O caracter na posição 5 é uma letra
           O caracter na posição 6 é uma letra
           A cadeia de caracteres digitado tem 5 letras
        */
        case 5: metodo0315(caracter);break;
        /*
           Digite uma cadeia de carateres: P4LaVr@1
           O caracter na posição 8 é um dígito 
           O caracter na posição 2 é um dígito 
           A cadeia de caracteres digitado tem 2 dígitos
        */
        case 6: metodo0316(caracter);break;
        /*
          Digite uma cadeia de caracteres: P4LaVr@O!
          O caracter na posição 7 é um caractere especial
          O caracter na posição 9 é um caractere especial
          A cadeia de caracteres digitado tem 2 caractere especia
        */
        case 7: metodo0317(a,b);break;
        /*
           Digite dois numeros inteiros: 15 60
           Digite a quantidade de numeros a serem testados: 7
           Digite 7 numeros: 10 20 30 42 54 60 84
           O número 20 esta dentro do limite e é divisivel por 5
           O número 30 esta dentro do limite e é divisivel por 5
           O número 60 esta dentro do limite e é divisivel por 5
           Tem 3 numeros dentro do intervalo e divisiveis por 5
        */
        case 8: metodo0318(a,b);break;
        /*
          Digite dois valores inteiros: 20 60
          Digite a quantidade de numeros a serem testados: 7
          Digite 7 numeros: 10 20 30 48 52 60 84
          O número 48 está dentro do limite e é divisivel por 3 mas não por 5
          Tem 1 numeros dentro do intervalo divisivel por 3 mas não por 5
        */
        case 9: metodo0319(a,b);break;
        /*
           Digite a quantidade de numeros a serem testados: 7
           Digite 7 numeros: 1.0 2.4 3.3 4.1 5.5 6.3 8.4
           O numeros 3.300000 esta dentro do limite e é impar
           O numeros 5.500000 esta dentro do limite e é impar
           Tem 2 numeros dentro do intervalo e impar
        */
        case 10: metodo0320(a,b);break;
        /* 
           Digite dois valores reais, maiores que 0 e menores que 1: 0.25 0.50
           Digite a quantidade de numeros a serem testados: 7
           Digite 7 numeros: 1.0 2.8 3.3 4.1 5.5 6.9 8.4
           O numeros 0.000000 esta fora do limite
           O numeros 0.800000 esta fora do limite
           O numeros 0.100000 esta fora do limite
           O numeros 0.900000 esta fora do limite
           Tem 4 numeros fora do intervalo
        */
        case 11: metodo03E1(palavra);break;
        /*
          Digite um número entre 1 a 12: 11
          Digite uma sequência: P4LaVr@O! & pAl4vR1n#a
          A sequência sem os simbolos alfanuméricos é: @! & #
        */
        case 12: metodo03E2(palavra);break;
        /*
           Digite uma sequência: 4@0!1#
           A sequência não tem letras e é: 4@0!1#
        */
        default: printf("Opção invalida");
    }
    } while(opcao!=0);
    return (0);
}
