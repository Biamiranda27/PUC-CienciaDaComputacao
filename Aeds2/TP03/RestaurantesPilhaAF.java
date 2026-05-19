import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

class Data {
    private int ano, mes, dia;

    public Data(int ano, int mes, int dia) {
        this.ano = ano;
        this.mes = mes;
        this.dia = dia;
    }

    public int getAno() { return ano; }
    public int getMes() { return mes; }
    public int getDia() { return dia; }

    public static Data parseData(String s) {
        if (s == null || s.trim().isEmpty() || s.equalsIgnoreCase("NaN")) return null;
        return new Data(Integer.parseInt(s.substring(0, 4)), Integer.parseInt(s.substring(5, 7)),
                Integer.parseInt(s.substring(8, 10)));
    }

    public String formatar() {
        return String.format("%02d/%02d/%04d", dia, mes, ano);
    }
}

class Hora {
    private int hora, minuto;

    public Hora(int hora, int minuto) {
        this.hora = hora;
        this.minuto = minuto;
    }

    public int getHora() { return hora; }
    public int getMinuto() { return minuto; }

    public static Hora parseHora(String s) {
        if (s == null || s.trim().isEmpty() || s.equalsIgnoreCase("NaN")) return null;
        return new Hora(Integer.parseInt(s.substring(0, 2)), Integer.parseInt(s.substring(3, 5)));
    }

    public String formatar() {
        return String.format("%02d:%02d", hora, minuto);
    }
}

class Restaurante {
    private int id;
    private String nome, cidade;
    private int capacidade;
    private double avaliacao;
    private String[] tiposCozinha;
    private int faixaPreco;
    private Hora horarioAbertura, horarioFechamento;
    private Data dataAbertura;
    private boolean aberto;

    public Restaurante(int id, String nome, String cidade, int capacidade, double avaliacao,
            String[] tiposCozinha, int faixaPreco, Hora horarioAbertura,
            Hora horarioFechamento, Data dataAbertura, boolean aberto) {
        this.id = id;
        this.nome = nome;
        this.cidade = cidade;
        this.capacidade = capacidade;
        this.avaliacao = avaliacao;
        this.tiposCozinha = tiposCozinha;
        this.faixaPreco = faixaPreco;
        this.horarioAbertura = horarioAbertura;
        this.horarioFechamento = horarioFechamento;
        this.dataAbertura = dataAbertura;
        this.aberto = aberto;
    }

    public int getId() { return id; }
    public String getNome() { return nome; }

    public static Restaurante parseRestaurante(String s) {
        String[] c = s.split(",");
        String[] tipos = c[5].trim().replace("[", "").replace("]", "").replace("'", "").split("[,;]\\s*");
        
        Hora abertura = null;
        Hora fechamento = null;
        if (!c[7].trim().isEmpty() && c[7].contains("-")) {
            String[] hor = c[7].trim().split("-");
            abertura = Hora.parseHora(hor[0]);
            fechamento = Hora.parseHora(hor[1]);
        }

        return new Restaurante(
                Integer.parseInt(c[0].trim()), 
                c[1].trim(), 
                c[2].trim(),
                c[3].trim().isEmpty() ? 0 : Integer.parseInt(c[3].trim()), 
                c[4].trim().isEmpty() ? 0.0 : Double.parseDouble(c[4].trim()), 
                tipos,
                c[6].trim().length(), 
                abertura, 
                fechamento,
                Data.parseData(c[8].trim()), 
                Boolean.parseBoolean(c[9].trim()) || c[9].trim().equals("1")
        );
    }

    public String formatar() {
        StringBuilder fp = new StringBuilder();
        for (int i = 0; i < faixaPreco; i++) fp.append("$");
        
        StringBuilder tc = new StringBuilder("[");
        if (tiposCozinha != null) {
            for (int i = 0; i < tiposCozinha.length; i++) {
                if (i > 0) tc.append(",");
                tc.append(tiposCozinha[i]);
            }
        }
        tc.append("]");

        String horaAberta = (horarioAbertura != null) ? horarioAbertura.formatar() : "NaN";
        String horaFechada = (horarioFechamento != null) ? horarioFechamento.formatar() : "NaN";
        String dataFormatada = (dataAbertura != null) ? dataAbertura.formatar() : "NaN";

        return String.format(java.util.Locale.US, "[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %s]",
                id, nome, cidade, capacidade, avaliacao, tc, fp,
                horaAberta, horaFechada, dataFormatada, aberto);
    }
}

class ColecaoRestaurantes {
    private int tamanho;
    private Restaurante[] restaurantes;

    public ColecaoRestaurantes() {
        tamanho = 0;
        restaurantes = new Restaurante[0];
    }

    public int getTamanho() { return tamanho; }
    public Restaurante[] getRestaurantes() { return restaurantes; }

    public void lerCsv(String path) {
        try {
            BufferedReader br = new BufferedReader(new FileReader(path));
            int count = 0;
            br.readLine();
            String linha;
            while ((linha = br.readLine()) != null) {
                if (!linha.trim().isEmpty()) count++;
            }
            br.close();

            restaurantes = new Restaurante[count];
            tamanho = 0;
            br = new BufferedReader(new FileReader(path));
            br.readLine();
            while ((linha = br.readLine()) != null) {
                linha = linha.trim();
                linha = linha.replaceAll("^\"|\"$", ""); 
                if (!linha.isEmpty()) {
                    restaurantes[tamanho++] = Restaurante.parseRestaurante(linha);
                }
            }
            br.close();
        } catch (IOException e) {
            System.err.println("Erro: " + e.getMessage());
        }
    }

    public static ColecaoRestaurantes lerCsv() {
        ColecaoRestaurantes c = new ColecaoRestaurantes();
        c.lerCsv("/tmp/restaurantes.csv");
        return c;
    }
}

class Celula {
    public Restaurante elemento;
    public Celula prox;

    public Celula(Restaurante elemento) {
        this.elemento = elemento;
        this.prox = null;
    }
}

class Pilha {
    private Celula topo;

    public Pilha() {
        topo = null;
    }

    public void empilhar(Restaurante r) {
        Celula tmp = new Celula(r);
        tmp.prox = topo;
        topo = tmp;
    }

    public Restaurante desempilhar() throws Exception {
        if (topo == null) throw new Exception("Erro: Pilha vazia!");
        Restaurante r = topo.elemento;
        topo = topo.prox;
        return r;
    }

    private void mostrarRec(Celula i) {
        if (i != null) {
            System.out.println(i.elemento.formatar());
            mostrarRec(i.prox);
        }
    }

    public void mostrar() {
        mostrarRec(topo);
    }
}

public class RestaurantesPilhaAF {
    public static void main(String[] args) {
        ColecaoRestaurantes colecao = ColecaoRestaurantes.lerCsv();
        Restaurante[] todos = colecao.getRestaurantes();
        Scanner sc = new Scanner(System.in);
        Pilha pilha = new Pilha();

        while (sc.hasNextInt()) {
            int id = sc.nextInt();
            if (id == -1) break;
            
            for (int j = 0; j < colecao.getTamanho(); j++) {
                if (todos[j] != null && todos[j].getId() == id) {
                    pilha.empilhar(todos[j]);
                    break;
                }
            }
        }

        if (sc.hasNextInt()) {
            int n = sc.nextInt();
            sc.nextLine(); 
            for (int i = 0; i < n; i++) {
                String linha = sc.nextLine().trim();
                String[] p = linha.split(" ");
                String cmd = p[0];

                try {
                    if (cmd.equals("I")) {
                        int id = Integer.parseInt(p[1]);
                        for (int j = 0; j < colecao.getTamanho(); j++) {
                            if (todos[j] != null && todos[j].getId() == id) {
                                pilha.empilhar(todos[j]);
                                break;
                            }
                        }
                    } else if (cmd.equals("R")) {
                        Restaurante r = pilha.desempilhar();
                        if (r != null) {
                            System.out.println("(R)" + r.getNome());
                        }
                    }
                } catch (Exception e) {
                    System.err.println(e.getMessage());
                }
            }
        }

        sc.close();
        pilha.mostrar();
    }
}