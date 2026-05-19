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

    public Data() {
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

    public static Data parseData(String data) {
        if (data == null || data.trim().isEmpty() || data.equalsIgnoreCase("NaN")) {
            return null;
        }
        String[] partes = data.split("-");
        return new Data(Integer.parseInt(partes[0]), Integer.parseInt(partes[1]), Integer.parseInt(partes[2]));
    }

    public int getAno() { 
        return ano; 
    }
    public int getMes() { 
        return mes;
     }
    public int getDia() {
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
        if (hora == null || hora.trim().isEmpty() || hora.equalsIgnoreCase("NaN")) {
            return null;
        }
        String[] partes = hora.split(":");
        return new Hora(Integer.parseInt(partes[0]), Integer.parseInt(partes[1]));
    }

    public int getHora() { 
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
        for (int i = 0; i < faixaPreco; i++) {
            precoString += "$";
        }

        String dataFormatada = (dataAbertura != null) ? dataAbertura.formatar() : "NaN";
        String horaAberta = (horarioAbertura != null) ? horarioAbertura.formatar() : "NaN";
        String horaFechada = (horarioFechamento != null) ? horarioFechamento.formatar() : "NaN";

        return String.format(Locale.US, "[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %b]",
                id, nome, cidade, capacidade, avaliacao, cozinhaString.toString(), precoString,
                horaAberta, horaFechada, dataFormatada, aberto);
    }

    public static Restaurante parseRestaurante(String dividirLinha) {
        Restaurante restaurante = new Restaurante();
        String[] campos = dividirLinha.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);

        for (int i = 0; i < campos.length; i++) {
            campos[i] = campos[i].trim().replaceAll("^\"|\"$", "");
        }

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
}

class ColecaoRestaurantes {
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
                if (tamanho < restaurantes.length) {
                    restaurantes[tamanho++] = Restaurante.parseRestaurante(linha);
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
 
class No {
    public Restaurante elemento;
    public No esq, dir;

    public No(Restaurante elemento) {
        this(elemento, null, null);
    }

    public No(Restaurante elemento, No esq, No dir) {
        this.elemento = elemento;
        this.esq = esq;
        this.dir = dir;
    }
}
 
class ArvoreBinaria {
    private No raiz;
    public int comparacoes;

    public ArvoreBinaria() {
        raiz = null;
        comparacoes = 0;
    }

    public void inserir(Restaurante x) {
        raiz = inserir(x, raiz);
    }

    private No inserir(Restaurante x, No i) {
        if (i == null) {
            i = new No(x);
        } else if (x.getNome().compareTo(i.elemento.getNome()) < 0) {
            i.esq = inserir(x, i.esq);
        } else if (x.getNome().compareTo(i.elemento.getNome()) > 0) {
            i.dir = inserir(x, i.dir);
        } else { 
        }
        return i;
    }

    public void pesquisar(String nome) {
        System.out.print("raiz ");
        pesquisar(nome, raiz);
    }

    private void pesquisar(String nome, No i) {
        if (i == null) {
            System.out.println("NAO");
        } else {
            comparacoes++;
            if (nome.equals(i.elemento.getNome())) {
                System.out.println("SIM");
            } else {
                comparacoes++;
                if (nome.compareTo(i.elemento.getNome()) < 0) {
                    System.out.print("esq ");
                    pesquisar(nome, i.esq);
                } else {
                    System.out.print("dir ");
                    pesquisar(nome, i.dir);
                }
            }
        }
    }

    public void mostrarEmOrdem() {
        mostrarEmOrdem(raiz);
    }

    private void mostrarEmOrdem(No i) {
        if (i != null) {
            mostrarEmOrdem(i.esq);
            System.out.println(i.elemento.formatar());
            mostrarEmOrdem(i.dir);
        }
    }
}

public class RestaurantesAB {
    public static void main(String[] args) {
        ColecaoRestaurantes colecao = ColecaoRestaurantes.lerCsv();
        Scanner scanner = new Scanner(System.in);
        ArvoreBinaria arvore = new ArvoreBinaria();
         
        while (scanner.hasNextLine()) {
            String input = scanner.nextLine().trim();
            if (input.equals("-1")) {
                break;
            }
            if (input.isEmpty()) continue;
            
            int idBusca = Integer.parseInt(input);
            for (int i = 0; i < colecao.getTamanho(); i++) {
                Restaurante r = colecao.getRestaurantes()[i];
                if (r != null && r.getId() == idBusca) {
                    arvore.inserir(r);
                    break;
                }
            }
        }

        long tempoInicio = System.currentTimeMillis();
 
        while (scanner.hasNextLine()) {
            String nomeBusca = scanner.nextLine().trim();
            if (nomeBusca.equals("FIM")) {
                break;
            }
            if (nomeBusca.isEmpty()) continue;

            arvore.pesquisar(nomeBusca);
        }

        long tempoFim = System.currentTimeMillis();
 
        arvore.mostrarEmOrdem();
 
        try (PrintWriter out = new PrintWriter(new FileWriter("882406_arvoreBinaria.txt"))) {
             
            out.printf("882406\t%d\t%d\n", arvore.comparacoes, (tempoFim - tempoInicio));
        } catch (IOException e) {
            System.err.println("Erro ao escrever o log: " + e.getMessage());
        }

        scanner.close();
    }
}