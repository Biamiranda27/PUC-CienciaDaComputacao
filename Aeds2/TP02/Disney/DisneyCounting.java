import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

class Show {
    private String id;
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
        this.id = "NaN";
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

    public Show(String id, String tipo, String titulo, String diretor, String[] elenco, String pais,
                Date dataAdicionada, int anoLancamento, String classificacao, String duracao, String[] categorias) {
        this.id = id;
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

    public String getId() { return id; }
    public void setId(String id) { this.id = id; }

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

    // Clone
    public Show clone() {
        return new Show(id, tipo, titulo, diretor, elenco.clone(), pais, dataAdicionada, anoLancamento, classificacao, duracao, categorias.clone());
    }

    // Imprimir
    public void imprimir() {
        SimpleDateFormat sdf = new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH);
        String dataStr = (dataAdicionada != null) ? sdf.format(dataAdicionada) : "NaN";
    
        String[] elencoOrdenado = elenco.clone();
        Arrays.sort(elencoOrdenado, String.CASE_INSENSITIVE_ORDER);
    
        String tituloLimpo = titulo.replaceAll("\"", "");

        for (int i = 0; i < elencoOrdenado.length; i++) {
            elencoOrdenado[i] = elencoOrdenado[i].replaceAll("\"", "");
        } 
    
        System.out.println("=> " + id + " ## " + tituloLimpo + " ## " + tipo + " ## " + diretor +
                " ## " + Arrays.toString(elencoOrdenado) + " ## " + pais + " ## " + dataStr + " ## " +
                anoLancamento + " ## " + classificacao + " ## " + duracao + " ## " + Arrays.toString(categorias) + " ##");
    }

    // Ler CSV
    public void ler(String linha) {
        SimpleDateFormat sdf = new SimpleDateFormat("MMM dd, yyyy");
        String[] campos = new String[12];

        String[] partes = linha.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);
        for (int i = 0; i < campos.length; i++) {
            campos[i] = (i < partes.length && !partes[i].trim().isEmpty()) ? partes[i].trim().replaceAll("^\"|\"$", "") : "NaN";
        }

        this.id = campos[0];
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
}

public class DisneyCounting {
    private static void countingSort(ArrayList<Show> lista, int comparacoes[], int movimentacoes[]) {
        if (lista.isEmpty()) return;
    
        int minAno = lista.get(0).getAnoLancamento();
        int maxAno = lista.get(0).getAnoLancamento();
    
        for (Show s : lista) {
            if (s.getAnoLancamento() < minAno) minAno = s.getAnoLancamento();
            if (s.getAnoLancamento() > maxAno) maxAno = s.getAnoLancamento();
        }
    
        int range = maxAno - minAno + 1;
    
        ArrayList<ArrayList<Show>> baldes = new ArrayList<>(range);
        for (int i = 0; i < range; i++) {
            baldes.add(new ArrayList<>());
        }
    
        for (Show s : lista) {
            baldes.get(s.getAnoLancamento() - minAno).add(s.clone());
            movimentacoes[0]++;
        }
    
        lista.clear();
        for (ArrayList<Show> balde : baldes) {
            if (!balde.isEmpty()) {
                balde.sort((a, b) -> {
                    comparacoes[0]++;
                    return a.getTituloNormalizado().compareTo(b.getTituloNormalizado());
                });

                for (Show s : balde) {
                    lista.add(s);
                    movimentacoes[0]++;
                }
            }
        }
    }

    public static void main(String[] args) throws IOException {
        ArrayList<Show> lista = new ArrayList<>();
        Map<String, String> dadosCSV = new HashMap<>();
        Scanner sc = new Scanner(System.in);

        // Leitura do CSV
        BufferedReader br = new BufferedReader(new FileReader("/tmp/disneyplus.csv")); 
        br.readLine();
        String linha;
        
        while ((linha = br.readLine()) != null) {
            String id = linha.split(",")[0];
            dadosCSV.put(id, linha);
        }
        br.close();

        String entrada;
        while (!(entrada = sc.nextLine()).equals("FIM")) {
            if (dadosCSV.containsKey(entrada)) {
                Show show = new Show();
                show.ler(dadosCSV.get(entrada));
                lista.add(show);
            }
        }
        sc.close();

        int[] comparacoes = {0};
        int[] movimentacoes = {0};

        long inicio = System.nanoTime();

        countingSort(lista, comparacoes, movimentacoes);

        long fim = System.nanoTime();
        double tempoExecucao = (fim - inicio) / 1_000_000.0;

        for (Show s : lista) {
            s.imprimir();
        }

        BufferedWriter bw = new BufferedWriter(new FileWriter("845860_countingsort.txt"));
        bw.write("845860\t" + comparacoes[0] + "\t" + movimentacoes[0] + "\t" + String.format("%.2f", tempoExecucao));
        bw.close();
    }
}
