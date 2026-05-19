import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;
import java.util.Locale;

class Data {
    private int ano;
    private int mes;
    private int dia;

    public Data() { this.ano = 0; this.mes = 0; this.dia = 0; }

    public Data(int ano, int mes, int dia) {
        this.ano = ano; this.mes = mes; this.dia = dia;
    }

    public String formatar() {
        return String.format("%02d/%02d/%04d", dia, mes, ano);
    }

    public static Data parseData(String data) {
        if (data == null || data.trim().isEmpty() || data.equalsIgnoreCase("NaN")) return null;
        String[] partes = data.split("-");
        return new Data(Integer.parseInt(partes[0]), Integer.parseInt(partes[1]), Integer.parseInt(partes[2]));
    }

    public int getAno()  { 
        return ano; 
    }
    public int getMes()  { 
        return mes;
     }
    public int getDia()  { 
        return dia;
     }
}

class Hora {
    private int hora;
    private int minuto;

    public Hora() { 
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

    public static Hora parseHora(String hora) {
        if (hora == null || hora.trim().isEmpty() || hora.equalsIgnoreCase("NaN")) return null;
        String[] partes = hora.split(":");
        return new Hora(Integer.parseInt(partes[0]), Integer.parseInt(partes[1]));
    }

    public int getHora()   { 
        return hora; 
    }
    public int getMinuto() { 
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
        this.id = 0; this.nome = ""; this.cidade = ""; this.capacidade = 0;
        this.avaliacao = 0.0; this.tiposCozinha = new String[0]; this.faixaPreco = 0;
        this.horarioAbertura = null; this.horarioFechamento = null;
        this.dataAbertura = null; this.aberto = false;
    }

    public String formatar() {
        StringBuilder cozinhaString = new StringBuilder("[");
        if (tiposCozinha != null) {
            for (int i = 0; i < tiposCozinha.length; i++) {
                cozinhaString.append(tiposCozinha[i]);
                if (i < tiposCozinha.length - 1) cozinhaString.append(",");
            }
        }
        cozinhaString.append("]");

        String precoString = "";
        for (int i = 0; i < faixaPreco; i++) precoString += "$";

        String dataFormatada = (dataAbertura    != null) ? dataAbertura.formatar()       : "NaN";
        String horaAberta    = (horarioAbertura != null) ? horarioAbertura.formatar()    : "NaN";
        String horaFechada   = (horarioFechamento != null) ? horarioFechamento.formatar() : "NaN";

        return String.format(Locale.US,
                "[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %b]",
                id, nome, cidade, capacidade, avaliacao,
                cozinhaString.toString(), precoString,
                horaAberta, horaFechada, dataFormatada, aberto);
    }

    public static Restaurante parseRestaurante(String dividirLinha) {
        Restaurante restaurante = new Restaurante();
        String[] campos = dividirLinha.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);

        for (int i = 0; i < campos.length; i++)
            campos[i] = campos[i].trim().replaceAll("^\"|\"$", "");

        restaurante.id         = Integer.parseInt(campos[0]);
        restaurante.nome       = campos[1];
        restaurante.cidade     = campos[2];
        restaurante.capacidade = campos[3].isEmpty() ? 0 : Integer.parseInt(campos[3]);
        restaurante.avaliacao  = campos[4].isEmpty() ? 0.0 : Double.parseDouble(campos[4]);

        String tipos = campos[5].replace("[", "").replace("]", "").replace("'", "");
        restaurante.tiposCozinha = tipos.split("[,;]\\s*");

        restaurante.faixaPreco = campos[6].isEmpty() ? 0 : campos[6].length();

        if (!campos[7].isEmpty() && campos[7].contains("-")) {
            String[] horas = campos[7].split("-");
            restaurante.horarioAbertura   = Hora.parseHora(horas[0]);
            restaurante.horarioFechamento = Hora.parseHora(horas[1]);
        }

        restaurante.dataAbertura = Data.parseData(campos[8]);
        restaurante.aberto = campos[9].equalsIgnoreCase("true") || campos[9].equals("1");
        return restaurante;
    }

    public int    getId(){ 
        return id; 
    }
    public String getNome(){ 
        return nome; 
    }
    public String getCidade(){ 
        return cidade; 
    }
    public Data   getDataAbertura(){ 
        return dataAbertura; 
    }
}

class ColecaoRestaurantes {
    private int tamanho;
    private Restaurante[] restaurantes;

    public ColecaoRestaurantes(int capacidadeMax) {
        restaurantes = new Restaurante[capacidadeMax];
        tamanho = 0;
    }

    public int getTamanho(){ 
        return tamanho; 
    }
    public Restaurante[] getRestaurantes() { 
        return restaurantes; 
    }

    public void lerCsv(String leitura) {
        try (BufferedReader buffer = new BufferedReader(new FileReader(leitura))) {
            buffer.readLine(); 
            String linha;
            while ((linha = buffer.readLine()) != null) {
                if (tamanho < restaurantes.length)
                    restaurantes[tamanho++] = Restaurante.parseRestaurante(linha);
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

class No {
    Restaurante restaurante;
    No anterior;
    No proximo;

    public No(Restaurante restaurante) {
        this.restaurante = restaurante;
        this.anterior    = null;
        this.proximo     = null;
    }
}

class ListaDupla {
    private No cabeca;   
    private No cauda;   
    private int n;     

    public ListaDupla() {
        cabeca = null;
        cauda  = null;
        n      = 0;
    }

    public void inserirInicio(Restaurante restaurante) {
        No novo = new No(restaurante);
        if (cabeca == null) {
            cabeca = cauda = novo;
        } else {
            novo.proximo   = cabeca;
            cabeca.anterior = novo;
            cabeca          = novo;
        }
        n++;
    }

    public void inserir(Restaurante restaurante, int posicao) {
        if (posicao <= 0) {
            inserirInicio(restaurante);
            return;
        }
        if (posicao >= n) {
            inserirFim(restaurante);
            return;
        }

        No novo   = new No(restaurante);
        No atual  = getNo(posicao);          
        No antes  = atual.anterior;

        antes.proximo  = novo;
        novo.anterior  = antes;
        novo.proximo   = atual;
        atual.anterior = novo;
        n++;
    }

    public void inserirFim(Restaurante restaurante) {
        No novo = new No(restaurante);
        if (cauda == null) {
            cabeca = cauda = novo;
        } else {
            novo.anterior = cauda;
            cauda.proximo = novo;
            cauda         = novo;
        }
        n++;
    }

    public Restaurante removerInicio() {
        if (cabeca == null) return null;
        Restaurante resp = cabeca.restaurante;
        cabeca = cabeca.proximo;
        if (cabeca != null) cabeca.anterior = null;
        else cauda = null;
        n--;
        return resp;
    }

    public Restaurante remover(int posicao) {
        if (posicao <= 0)   return removerInicio();
        if (posicao >= n-1) return removerFim();

        No alvo = getNo(posicao);
        alvo.anterior.proximo = alvo.proximo;
        alvo.proximo.anterior = alvo.anterior;
        n--;
        return alvo.restaurante;
    }

    public Restaurante removerFim() {
        if (cauda == null) return null;
        Restaurante resp = cauda.restaurante;
        cauda = cauda.anterior;
        if (cauda != null) cauda.proximo = null;
        else cabeca = null;
        n--;
        return resp;
    }

    public void mostrar() {
        No atual = cabeca;
        //int i = 0;
        while (atual != null) {
            System.out.println( atual.restaurante.formatar());
            atual = atual.proximo;
           // i++;
        }
    }

    private No getNo(int posicao) {
        No atual;
        if (posicao < n / 2) {
            atual = cabeca;
            for (int i = 0; i < posicao; i++) atual = atual.proximo;
        } else {
            atual = cauda;
            for (int i = n - 1; i > posicao; i--) atual = atual.anterior;
        }
        return atual;
    }
}

public class RestaurantesListaDAF {

    public static Restaurante buscarPorId(ColecaoRestaurantes colecao, int id) {
        for (int i = 0; i < colecao.getTamanho(); i++) {
            if (colecao.getRestaurantes()[i] != null &&
                colecao.getRestaurantes()[i].getId() == id)
                return colecao.getRestaurantes()[i];
        }
        return null;
    }

    public static void main(String[] args) {
        ColecaoRestaurantes colecao = ColecaoRestaurantes.lerCsv();
        ListaDupla lista = new ListaDupla();
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNext()) {
            String input = scanner.next();
            if (input.equals("-1")) break;
            int idBusca = Integer.parseInt(input);
            Restaurante restaurante = buscarPorId(colecao, idBusca);
            if (restaurante != null) lista.inserirFim(restaurante);
        }

        if (scanner.hasNextInt()) {
            int numComandos = scanner.nextInt();

            for (int i = 0; i < numComandos; i++) {
                String cmd = scanner.next();

                if (cmd.equals("II")) {
                    int id = scanner.nextInt();
                    Restaurante r = buscarPorId(colecao, id);
                    if (r != null) lista.inserirInicio(r);

                } else if (cmd.equals("I*")) {
                    int pos = scanner.nextInt();
                    int id  = scanner.nextInt();
                    Restaurante r = buscarPorId(colecao, id);
                    if (r != null) lista.inserir(r, pos);

                } else if (cmd.equals("IF")) {
                    int id = scanner.nextInt();
                    Restaurante r = buscarPorId(colecao, id);
                    if (r != null) lista.inserirFim(r);

                } else if (cmd.equals("RI")) {
                    Restaurante r = lista.removerInicio();
                    if (r != null) System.out.println("(R)" + r.getNome());

                } else if (cmd.equals("R*")) {
                    int posicao = scanner.nextInt();
                    Restaurante r = lista.remover(posicao);
                    if (r != null) System.out.println("(R)" + r.getNome());

                } else if (cmd.equals("RF")) {
                    Restaurante r = lista.removerFim();
                    if (r != null) System.out.println("(R)" + r.getNome());
                }
            }
        }

        scanner.close();
        lista.mostrar();
    }
}