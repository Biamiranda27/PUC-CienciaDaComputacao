import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.Locale;

class Data {
    private int ano;
    private int mes;
    private int dia;

    public Data(){
        this.ano = 0;
        this.mes = 0;
        this.dia = 0;
    }

    public Data(int ano, int mes, int dia) { 
        this.ano = ano;
        this.mes = mes;
        this.dia = dia;
    }

    public String formatar() {
        return String.format("%02d/%02d/%04d", dia, mes, ano);
    }

    public static Data parseData(String data) { //converte a string data de ano-mes-dia para um objeto Data
        if (data == null || data.trim().isEmpty() || data.equalsIgnoreCase("NaN")) {
            return null;
        }
        String[] partes = data.split("-");
        return new Data(Integer.parseInt(partes[0]), Integer.parseInt(partes[1]), Integer.parseInt(partes[2])); //retorna dia-mes-ano
    }

    public int getAno(){ 
        return ano; 
    }
    public int getMes(){ 
        return mes; 
    }
    public int getDia(){ 
        return dia; 
    }
}

class Hora {
    private int hora;
    private int minuto;

    public Hora(){
        this.hora = 0;
        this.minuto = 0;
    }

    public Hora(int hora, int minuto) {
        this.hora = hora;
        this.minuto = minuto;
    }

    public String formatar() {
        return String.format("%02d:%02d", hora, minuto);
    }

    public static Hora parseHora(String hora) { //converte a string hora:minuto para um objeto Hora
        if (hora == null || hora.trim().isEmpty() || hora.equalsIgnoreCase("NaN")) {
            return null;
        }
        String[] partes = hora.split(":");
        return new Hora(Integer.parseInt(partes[0]), Integer.parseInt(partes[1])); //retorna hora e minuto com dois digitos
    }

    public int getHora(){ 
        return hora; 
    }
    public int getMinuto(){ 
        return minuto; 
    }
}

class Restaurante {
    private int id;
    private String nome;
    private String cidade;
    private int capacidade;
    private double avaliacao;
    private String[] tiposCozinha; 
    private int faixaPreco;      
    private Hora horarioAbertura; 
    private Hora horarioFechamento;
    private Data dataAbertura;    
    private boolean aberto;

    public Restaurante() {
        this.id = 0;
        this.nome = "";
        this.cidade = "";
        this.capacidade = 0;
        this.avaliacao = 0.0;
        this.tiposCozinha = new String[0];
        this.faixaPreco = 0;
        this.horarioAbertura = null;
        this.horarioFechamento = null;
        this.dataAbertura = null;
        this.aberto = false;
    }

    public String formatar() { //faz os objetos de restaurante ficarem em uma linha
        StringBuilder cozinhaString = new StringBuilder("[");
        if (tiposCozinha != null) {
            for (int i = 0; i < tiposCozinha.length; i++) {
                cozinhaString.append(tiposCozinha[i]);
                if (i < tiposCozinha.length - 1) cozinhaString.append(","); //poe virgula entre os nomes
            }
        }
        cozinhaString.append("]");

        String precoString = "";
        for (int i = 0; i < faixaPreco; i++) {
            precoString += "$"; //mostra quantos $ o restaurante é, 2 == $$
        }

        //se os atributos abaixo existirem é para formatar, se nao escrever NaN
        String dataFormatada = (dataAbertura != null) ? dataAbertura.formatar() : "NaN";
        String horaAberta = (horarioAbertura != null) ? horarioAbertura.formatar() : "NaN";
        String horaFechada = (horarioFechamento != null) ? horarioFechamento.formatar() : "NaN";

        return String.format(Locale.US, "[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %b]",
                id, nome, cidade, capacidade, avaliacao, cozinhaString.toString(), precoString,
                horaAberta, horaFechada, dataFormatada, aberto);
    }

    public static Restaurante parseRestaurante(String dividirLinha) { //pega a linha e tranforma em um objeto de Restaurantes
        Restaurante restaurante = new Restaurante();
        String[] campos = dividirLinha.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);
        
        for (int i = 0; i < campos.length; i++) {
            campos[i] = campos[i].trim().replaceAll("^\"|\"$", ""); //tira as ""
        }

        //coloca cada atributo na sua posicao
        restaurante.id = Integer.parseInt(campos[0]);
        restaurante.nome = campos[1];
        restaurante.cidade = campos[2];
        restaurante.capacidade = campos[3].isEmpty() ? 0 : Integer.parseInt(campos[3]);
        restaurante.avaliacao = campos[4].isEmpty() ? 0.0 : Double.parseDouble(campos[4]);

        String tipos = campos[5].replace("[", "").replace("]", "").replace("'", "");
        restaurante.tiposCozinha = tipos.split("[,;]\\s*"); 

        restaurante.faixaPreco = campos[6].isEmpty() ? 0 : campos[6].length(); 

        if (!campos[7].isEmpty() && campos[7].contains("-")) {
            String[] horas = campos[7].split("-"); 
            restaurante.horarioAbertura = Hora.parseHora(horas[0]);
            restaurante.horarioFechamento = Hora.parseHora(horas[1]);
        }

        restaurante.dataAbertura = Data.parseData(campos[8]);
        restaurante.aberto = campos[9].equalsIgnoreCase("true") || campos[9].equals("1");

        return restaurante;
    }

    public int getId(){
         return id; 
        }
    public String getNome(){ 
        return nome; 
    }
    public String getCidade(){
         return cidade; 
        }
    public Data getDataAbertura(){ 
        return dataAbertura; 
    }
}

class ColecaoRestaurantes { //parte que armazena varios restaurantes
    private int tamanho;
    private Restaurante[] restaurantes;

    public ColecaoRestaurantes(int capacidadeMax) {
        restaurantes = new Restaurante[capacidadeMax];
        tamanho = 0;
    }

    public int getTamanho() { return tamanho; } 
    public Restaurante[] getRestaurantes() { return restaurantes; } 

    public void lerCsv(String leitura) { 
        try (BufferedReader buffer = new BufferedReader(new FileReader(leitura))) {
            String linha = buffer.readLine(); 
            while ((linha = buffer.readLine()) != null) {
                if(tamanho < restaurantes.length) {
                    restaurantes[tamanho++] = Restaurante.parseRestaurante(linha); //transforma o csv, a linha em objeto
                }
            }
        } catch (IOException e) {
            System.err.println("Erro ao ler o arquivo: " + e.getMessage());
        }
    }

    public static ColecaoRestaurantes lerCsv() { 
        ColecaoRestaurantes colecao = new ColecaoRestaurantes(2000); 
        colecao.lerCsv("/tmp/restaurantes.csv"); 
        return colecao;
    }
}

public class RestaurantesHeapsort {
    
    static int comparacoes = 0;
    static int movimentacoes = 0;

    public static int compareRestaurantes(Restaurante r1, Restaurante r2) { //compara ano, mes e dia. e é ordenado do mais antigo ao mais novo
        Data d1 = r1.getDataAbertura();
        Data d2 = r2.getDataAbertura();
        int comparacao = 0;

        comparacoes++;
        if (d1 == null && d2 != null) comparacao = -1;
        else if (d1 != null && d2 == null) comparacao = 1;
        else if (d1 != null && d2 != null) {
            if (d1.getAno() != d2.getAno()) {
                comparacao = Integer.compare(d1.getAno(), d2.getAno());
            } else if (d1.getMes() != d2.getMes()) {
                comparacao = Integer.compare(d1.getMes(), d2.getMes());
            } else {
                comparacao = Integer.compare(d1.getDia(), d2.getDia());
            }
        }

        if (comparacao == 0) {
            comparacoes++;
            comparacao = r1.getNome().compareTo(r2.getNome()); //se os restaurantes abrirem na mesma data, testa o nome, ordema alfabetica
        }
        
        return comparacao;
    }

    public static void refazer(Restaurante[] a, int i, int n) { //logica da ab
        int maior = i;
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;

        if (esq < n && compareRestaurantes(a[esq], a[maior]) > 0) {
            maior = esq;
        }

        if (dir < n && compareRestaurantes(a[dir], a[maior]) > 0) {
            maior = dir;
        }

        if (maior != i) {
            Restaurante tmp = a[i];
            a[i] = a[maior];
            a[maior] = tmp;
            movimentacoes += 3;
            refazer(a, maior, n);
        }
    }

    public static void heapsort(Restaurante[] a, int n) {
        for (int i = (n / 2) - 1; i >= 0; i--) {
            refazer(a, i, n);
        }

        for (int i = n - 1; i > 0; i--) {
            Restaurante tmp = a[0];
            a[0] = a[i];
            a[i] = tmp;
            movimentacoes += 3;
            refazer(a, 0, i);
        }
    }

    public static void main(String[] args) {
        ColecaoRestaurantes colecao = ColecaoRestaurantes.lerCsv();
        Scanner scanner = new Scanner(System.in);
        
        Restaurante[] selecionados = new Restaurante[2000];
        int numSelecionados = 0;
        
        while (scanner.hasNextInt()) {
            int idBusca = scanner.nextInt();
            
            if (idBusca == -1) {
                break;
            }
            
            for (int i = 0; i < colecao.getTamanho(); i++) {
                Restaurante r = colecao.getRestaurantes()[i];
                if (r != null && r.getId() == idBusca) {
                    selecionados[numSelecionados++] = r;
                    break;
                }
            }
        }
        scanner.close();

        long tempoInicio = System.currentTimeMillis();

        if (numSelecionados > 0) {
            heapsort(selecionados, numSelecionados);
        }

        long tempoFim = System.currentTimeMillis();

        for (int i = 0; i < numSelecionados; i++) {
            System.out.println(selecionados[i].formatar());
        }

        try (PrintWriter out = new PrintWriter(new FileWriter("882406_heapsort.txt"))) {
            out.printf("882406\t%d\t%d\t%d\n", comparacoes, movimentacoes, (tempoFim - tempoInicio));
        } catch (IOException e) {
            System.err.println("Erro ao escrever o arquivo de log: " + e.getMessage());
        }
    }
}