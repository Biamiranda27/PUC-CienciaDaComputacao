import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

class Data {
    private int ano, mes, dia;
    public Data(int ano, int mes, int dia) { this.ano = ano; this.mes = mes; this.dia = dia; }
    public int getAno() { return ano; }
    public int getMes() { return mes; }
    public int getDia() { return dia; }
    public static Data parseData(String s) {
        return new Data(Integer.parseInt(s.substring(0, 4)), Integer.parseInt(s.substring(5, 7)), Integer.parseInt(s.substring(8, 10)));
    }
    public String formatar() { return String.format("%02d/%02d/%04d", dia, mes, ano); }
}

class Hora {
    private int hora, minuto;
    public Hora(int hora, int minuto) { this.hora = hora; this.minuto = minuto; }
    public int getHora() { return hora; }
    public int getMinuto() { return minuto; }
    public static Hora parseHora(String s) {
        return new Hora(Integer.parseInt(s.substring(0, 2)), Integer.parseInt(s.substring(3, 5)));
    }
    public String formatar() { return String.format("%02d:%02d", hora, minuto); }
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
        this.id = id; this.nome = nome; this.cidade = cidade; this.capacidade = capacidade;
        this.avaliacao = avaliacao; this.tiposCozinha = tiposCozinha; this.faixaPreco = faixaPreco;
        this.horarioAbertura = horarioAbertura; this.horarioFechamento = horarioFechamento;
        this.dataAbertura = dataAbertura; this.aberto = aberto;
    }

    public int getId() { return id; }
    public String getNome() { return nome; }
    public String getCidade() { return cidade; }
    public int getCapacidade() { return capacidade; }
    public double getAvaliacao() { return avaliacao; }
    public String[] getTiposCozinha() { return tiposCozinha; }
    public int getFaixaPreco() { return faixaPreco; }
    public Hora getHorarioAbertura() { return horarioAbertura; }
    public Hora getHorarioFechamento() { return horarioFechamento; }
    public Data getDataAbertura() { return dataAbertura; }
    public boolean isAberto() { return aberto; }

    public static Restaurante parseRestaurante(String s) {
        String[] c = s.split(",");
        String[] tipos = c[5].trim().split(";");
        String[] hor = c[7].trim().split("-");
        return new Restaurante(Integer.parseInt(c[0].trim()), c[1].trim(), c[2].trim(),
                Integer.parseInt(c[3].trim()), Double.parseDouble(c[4].trim()), tipos,
                c[6].trim().length(), Hora.parseHora(hor[0]), Hora.parseHora(hor[1]),
                Data.parseData(c[8].trim()), Boolean.parseBoolean(c[9].trim()));
    }

    public String formatar() {
        StringBuilder fp = new StringBuilder();
        for (int i = 0; i < faixaPreco; i++) fp.append("$");
        StringBuilder tc = new StringBuilder("[");
        for (int i = 0; i < tiposCozinha.length; i++) {
            if (i > 0) tc.append(",");
            tc.append(tiposCozinha[i]);
        }
        tc.append("]");
        return String.format("[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %s]",
                id, nome, cidade, capacidade, avaliacao, tc, fp,
                horarioAbertura.formatar(), horarioFechamento.formatar(), dataAbertura.formatar(), aberto);
    }
}

class ColecaoRestaurantes {
    private int tamanho;
    private Restaurante[] restaurantes;

    public ColecaoRestaurantes() { tamanho = 0; restaurantes = new Restaurante[0]; }
    public int getTamanho() { return tamanho; }
    public Restaurante[] getRestaurantes() { return restaurantes; }

    public void lerCsv(String path) {
        try {
            BufferedReader br = new BufferedReader(new FileReader(path));
            int count = 0;
            br.readLine();
            String linha;
            while ((linha = br.readLine()) != null)
                if (!linha.trim().isEmpty()) count++;
            br.close();
            restaurantes = new Restaurante[count];
            tamanho = 0;
            br = new BufferedReader(new FileReader(path));
            br.readLine();
            while ((linha = br.readLine()) != null) {
                linha = linha.trim();
                if (!linha.isEmpty()) restaurantes[tamanho++] = Restaurante.parseRestaurante(linha);
            }
            br.close();
        } catch (IOException e) { System.err.println("Erro: " + e.getMessage()); }
    }

    public static ColecaoRestaurantes lerCsv() {
        ColecaoRestaurantes c = new ColecaoRestaurantes();
        c.lerCsv("/tmp/restaurantes.csv");
        return c;
    }
}

public class RestaurantesSelecaoP {
    static long comparacoes = 0;
    static long movimentacoes = 0;

    static void selecaoParcial(Restaurante[] v, int n, int k) {
        for (int i = 0; i < k && i < n; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                comparacoes++;
                if (v[j].getNome().compareTo(v[minIdx].getNome()) < 0) {
                    minIdx = j;
                }
            }
            if (minIdx != i) {
                Restaurante tmp = v[i];
                v[i] = v[minIdx];
                v[minIdx] = tmp;
                movimentacoes += 3;
            }
        }
    }

    public static void main(String[] args) throws Exception {
        ColecaoRestaurantes colecao = ColecaoRestaurantes.lerCsv();
        Restaurante[] todos = colecao.getRestaurantes();
        int n = colecao.getTamanho();
        int k = 10;
        Scanner sc = new Scanner(System.in);
        java.util.List<Integer> idList = new java.util.ArrayList<>();
        while (sc.hasNextInt()) {
            int v = sc.nextInt();
            if (v == -1) break;
            idList.add(v);
        }
        sc.close();
        int qtd = idList.size();
        Restaurante[] selecionados = new Restaurante[qtd];
        int count = 0;
        for (int id : idList) {
            for (int j = 0; j < n; j++) {
                if (todos[j].getId() == id) {
                    selecionados[count++] = todos[j];
                    break;
                }
            }
        }
        long inicio = System.nanoTime();
        selecaoParcial(selecionados, count, k);
        long tempo = System.nanoTime() - inicio;
        for (int i = 0; i < count; i++)
            System.out.println(selecionados[i].formatar());
        String matricula = "845860";
        try (FileWriter fw = new FileWriter(matricula + "_selecao_parcial.txt")) {
            fw.write(matricula + "\t" + comparacoes + "\t" + movimentacoes + "\t" + tempo + "\n");
        }
    }
}