import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
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

    public int getId() { return id; }
    public String getNome() { return nome; }
    public String getCidade() { return cidade; }
    public Data getDataAbertura() { return dataAbertura; }
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

class FilaCircular {
    private Restaurante[] array;
    private int primeiro;
    private int ultimo;

    public FilaCircular(int tamanho) {
        array = new Restaurante[tamanho + 1];
        primeiro = 0;
        ultimo = 0;
    }

    public void inserir(Restaurante r) {
        if (((ultimo + 1) % array.length) == primeiro) {
            remover();
        }

        array[ultimo] = r;
        ultimo = (ultimo + 1) % array.length;

        int soma = 0;
        int count = 0;

        //calcula a media dos anos de abertura dos restaurantes
        for (int i = primeiro; i != ultimo; i = (i + 1) % array.length) {
            if (array[i] != null && array[i].getDataAbertura() != null) {
                soma += array[i].getDataAbertura().getAno();
            }
            count++;
        }

        int media = 0;
        if (count > 0) {
            media = (int) Math.round((double) soma / count);
        }

        System.out.println("(I)" + media);
    }

    public Restaurante remover() {
        if (primeiro == ultimo) {
            return null;
        }
        
        Restaurante resp = array[primeiro];
        primeiro = (primeiro + 1) % array.length;
        System.out.println("(R)" + resp.getNome());
        return resp;
    }

    public void mostrar() {
        int pos = 0;
        for (int i = primeiro; i != ultimo; i = (i + 1) % array.length) {
            System.out.println("[" + pos + "] " + array[i].formatar());
            pos++;
        }
    }
}

public class RestaurantesFilaCircular {

    public static Restaurante buscarPorId(ColecaoRestaurantes colecao, int id) {
        for (int i = 0; i < colecao.getTamanho(); i++) {
            if (colecao.getRestaurantes()[i] != null && colecao.getRestaurantes()[i].getId() == id) {
                return colecao.getRestaurantes()[i];
            }
        }
        return null;
    }

    public static void main(String[] args) {
        ColecaoRestaurantes colecao = ColecaoRestaurantes.lerCsv();
        FilaCircular fila = new FilaCircular(5);
        Scanner scanner = new Scanner(System.in);
        
        while (scanner.hasNext()) {
            String input = scanner.next();
            if (input.equals("-1")) {
                break;
            }
            try {
                int idBusca = Integer.parseInt(input);
                Restaurante r = buscarPorId(colecao, idBusca);
                if (r != null) {
                    fila.inserir(r);
                }
            } catch (NumberFormatException e) {}
        }

        if (scanner.hasNextInt()) {
            int numComandos = scanner.nextInt();
            
            for (int i = 0; i < numComandos; i++) {
                String comando = scanner.next();
                
                if (comando.equals("I")) {
                    int id = scanner.nextInt();
                    Restaurante restaurantes = buscarPorId(colecao, id);
                    if (restaurantes != null) {
                        fila.inserir(restaurantes);
                    }
                } else if (comando.equals("R")) {
                    fila.remover();
                }
            }
        }
        scanner.close();

        fila.mostrar();
    }
}