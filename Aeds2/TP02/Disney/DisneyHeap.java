import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.HashMap;
import java.util.Locale;
import java.util.Map;
import java.util.Scanner;

class Show {
    private String idShow;
    private String tipo;
    private String titulo;
    private String diretor;
    private String[] elenco;
    private String pais;
    private Date dataAdicionada;
    private int anoLancamento;
    private String classificacao;
    private String duracao;
    private String[] categorias;

    public Show() {
        this.idShow = "NaN";
        this.tipo = "NaN";
        this.titulo = "NaN";
        this.diretor = "NaN";
        this.elenco = new String[]{"NaN"};
        this.pais = "NaN";
        this.dataAdicionada = null;
        this.anoLancamento = -1;
        this.classificacao = "NaN";
        this.duracao = "NaN";
        this.categorias = new String[]{"NaN"};
    }

    public Show(String idShow, String tipo, String titulo, String diretor, String[] elenco, String pais,
                Date dataAdicionada, int anoLancamento, String classificacao, String duracao, String[] categorias) {
        this.idShow = idShow;
        this.tipo = tipo;
        this.titulo = titulo;
        this.diretor = diretor;
        this.elenco = elenco;
        this.pais = pais;
        this.dataAdicionada = dataAdicionada;
        this.anoLancamento = anoLancamento;
        this.classificacao = classificacao;
        this.duracao = duracao;
        this.categorias = categorias;
    }

    public String getIdShow() { return idShow; }
    public void setIdShow(String idShow) { this.idShow = idShow; }

    public String getTipo() { return tipo; }
    public void setTipo(String tipo) { this.tipo = tipo; }

    public String getTitulo() { return titulo; }
    public void setTitulo(String titulo) { this.titulo = titulo; }

    public String getDiretor() { return diretor; }
    public void setDiretor(String diretor) { this.diretor = diretor; }

    public String[] getElenco() { return elenco; }
    public void setElenco(String[] elenco) { this.elenco = elenco; }

    public String getPais() { return pais; }
    public void setPais(String pais) { this.pais = pais; }

    public Date getDataAdicionada() { return dataAdicionada; }
    public void setDataAdicionada(Date dataAdicionada) { this.dataAdicionada = dataAdicionada; }

    public int getAnoLancamento() { return anoLancamento; }
    public void setAnoLancamento(int anoLancamento) { this.anoLancamento = anoLancamento; }

    public String getClassificacao() { return classificacao; }
    public void setClassificacao(String classificacao) { this.classificacao = classificacao; }

    public String getDuracao() { return duracao; }
    public void setDuracao(String duracao) { this.duracao = duracao; }

    public String[] getCategorias() { return categorias; }
    public void setCategorias(String[] categorias) { this.categorias = categorias; }

    // clone
    public Show clonar() {
        return new Show(idShow, tipo, titulo, diretor, elenco.clone(), pais, dataAdicionada, anoLancamento, classificacao, duracao, categorias.clone());
    }

    // imprimir
    public void imprimir() {
        SimpleDateFormat sdf = new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH);
        String dataStr = (dataAdicionada != null) ? sdf.format(dataAdicionada) : "NaN";

        String[] elencoOrdenado = elenco.clone();
        Arrays.sort(elencoOrdenado, String.CASE_INSENSITIVE_ORDER);

        String tituloLimpo = titulo.replaceAll("\"", "");

        for (int i = 0; i < elencoOrdenado.length; i++) {
            elencoOrdenado[i] = elencoOrdenado[i].replaceAll("\"", "");
        }

        System.out.println("=> " + idShow + " ## " + tituloLimpo + " ## " + tipo + " ## " + diretor +
                " ## " + Arrays.toString(elencoOrdenado) + " ## " + pais + " ## " + dataStr + " ## " +
                anoLancamento + " ## " + classificacao + " ## " + duracao + " ## " + Arrays.toString(categorias) + " ##");
    }

    public void ler(String linha) {
        SimpleDateFormat sdf = new SimpleDateFormat("MMM dd, yyyy");
        String[] campos = new String[12];

        String[] partes = linha.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);
        for (int i = 0; i < campos.length; i++) {
            campos[i] = (i < partes.length && !partes[i].trim().isEmpty()) ? partes[i].trim().replaceAll("^\"|\"$", "") : "NaN";
        }

        this.idShow = campos[0];
        this.tipo = campos[1];
        this.titulo = campos[2];
        this.diretor = campos[3];
        this.elenco = campos[4].equals("NaN") ? new String[]{"NaN"} : campos[4].split(", ");
        this.pais = campos[5];
        try {
            this.dataAdicionada = campos[6].equals("NaN") ? null : sdf.parse(campos[6]);
        } catch (ParseException e) {
            this.dataAdicionada = null;
        }
        this.anoLancamento = campos[7].equals("NaN") ? -1 : Integer.parseInt(campos[7]);
        this.classificacao = campos[8];
        this.duracao = campos[9];
        this.categorias = campos[10].equals("NaN") ? new String[]{"NaN"} : campos[10].split(", ");
    }

    public String getTituloNormalizado() {
        return titulo.replaceAll("\"", "").trim().toLowerCase();
    }

    public String getDiretorNormalizado() {
        return diretor.replaceAll("\"", "").trim().toLowerCase();
    }
}

public class DisneyHeap {
    private static void heapSort(ArrayList<Show> lista, int contComparacoes[], int contMovimentacoes[]) {
        int n = lista.size();

        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(lista, n, i, contComparacoes, contMovimentacoes);
        }

        for (int i = n - 1; i > 0; i--) {
            Show temp = lista.get(0).clonar();
            lista.set(0, lista.get(i).clonar());
            lista.set(i, temp.clonar());
            contMovimentacoes[0] += 3;

            heapify(lista, i, 0, contComparacoes, contMovimentacoes);
        }
    }

    private static void heapify(ArrayList<Show> lista, int n, int i, int contComparacoes[], int contMovimentacoes[]) {
        int maior = i;
        int esquerda = 2 * i + 1;
        int direita = 2 * i + 2;

        if (esquerda < n) {
            contComparacoes[0]++;
            if (compare(lista.get(esquerda), lista.get(maior)) > 0) {
                maior = esquerda;
            }
        }

        if (direita < n) {
            contComparacoes[0]++;
            if (compare(lista.get(direita), lista.get(maior)) > 0) {
                maior = direita;
            }
        }

        if (maior != i) {
            Show troca = lista.get(i).clonar();
            lista.set(i, lista.get(maior).clonar());
            lista.set(maior, troca.clonar());
            contMovimentacoes[0] += 3;

            heapify(lista, n, maior, contComparacoes, contMovimentacoes);
        }
    }

    private static int compare(Show a, Show b) {
        int cmp = a.getDiretorNormalizado().compareTo(b.getDiretorNormalizado());
        if (cmp != 0) {
            return cmp;
        }
        return a.getTituloNormalizado().compareTo(b.getTituloNormalizado());
    }

    public static void main(String[] args) throws IOException {
        ArrayList<Show> listaShows = new ArrayList<>();
        Map<String, String> dadosCSV = new HashMap<>();
        Scanner scanner = new Scanner(System.in);

        BufferedReader br = new BufferedReader(new FileReader("/tmp/disneyplus.csv")); 

        br.readLine();
        String linha;

        while ((linha = br.readLine()) != null) {
            String id = linha.split(",")[0];
            dadosCSV.put(id, linha);
        }
        br.close();

        String entrada;
        while (!(entrada = scanner.nextLine()).equals("FIM")) {
            if (dadosCSV.containsKey(entrada)) {
                Show show = new Show();
                show.ler(dadosCSV.get(entrada));
                listaShows.add(show);
            }
        }
        scanner.close();

        int[] contComparacoes = {0};
        int[] contMovimentacoes = {0};

        long inicio = System.nanoTime();

        heapSort(listaShows, contComparacoes, contMovimentacoes);

        long fim = System.nanoTime();
        double tempoExecucao = (fim - inicio) / 1_000_000.0;

        for (Show s : listaShows) {
            s.imprimir();
        }

        BufferedWriter bw = new BufferedWriter(new FileWriter("845860_heapsort.txt"));
        bw.write("845860\t" + contComparacoes[0] + "\t" + contMovimentacoes[0] + "\t" + String.format("%.2f", tempoExecucao));
        bw.close();
    }
}
