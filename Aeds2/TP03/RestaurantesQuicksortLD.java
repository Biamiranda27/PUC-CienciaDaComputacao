import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Scanner;

class Restaurante {
    private int id;
    private String nome;
    private String cidade;
    private int capacidade;
    private double avaliacao;
    private List<String> tipos_cozinha;
    private int faixa_preco;
    private String horario_abertura;
    private String horario_fechamento;
    private String data_abertura;
    private boolean aberto;

    public Restaurante() {
        this.tipos_cozinha = new ArrayList<>();
    }

    public int getId() { 
        return id;
     }
    public double getAvaliacao() { 
        return avaliacao;
     }
    public String getNome() { 
        return nome;
     }

    private String trimField(String s) {
        if (s == null) return "";
        int inicio = 0;
        int fim = s.length() - 1;
        while (inicio <= fim && (s.charAt(inicio) == ' ' || s.charAt(inicio) == '"' || s.charAt(inicio) == '\n' || s.charAt(inicio) == '\r')) {
            inicio++;
        }
        while (fim >= inicio && (s.charAt(fim) == ' ' || s.charAt(fim) == '"' || s.charAt(fim) == '\n' || s.charAt(fim) == '\r')) {
            fim--;
        }
        if (inicio > fim) return "";
        return s.substring(inicio, fim + 1).replace("\n", "").replace("\r", "");
    }

    private String formatHora(String hora) {
        if (hora == null || hora.isEmpty() || hora.equals("NaN")) return "NaN";
        String[] partes = hora.split(":");
        if (partes.length >= 2) {
            return String.format("%02d:%02d", Integer.parseInt(partes[0].trim()), Integer.parseInt(partes[1].trim()));
        }
        return "NaN";
    }

    public void ler(String linha) {
        List<String> campos = new ArrayList<>();
        StringBuilder sb = new StringBuilder();
        boolean inQuotes = false;
        
        for (int i = 0; i < linha.length(); i++) {
            char c = linha.charAt(i);
            if (c == '"') {
                inQuotes = !inQuotes;
                sb.append(c);
            } else if (c == ',' && !inQuotes) {
                campos.add(sb.toString());
                sb.setLength(0);
            } else {
                sb.append(c);
            }
        }
        campos.add(sb.toString());

        while (campos.size() < 15) campos.add(""); 

        this.id = Integer.parseInt(trimField(campos.get(0)));
        this.nome = trimField(campos.get(1));
        this.cidade = trimField(campos.get(2));
        
        String capStr = trimField(campos.get(3));
        this.capacidade = capStr.isEmpty() ? 0 : Integer.parseInt(capStr);
        
        String avaStr = trimField(campos.get(4));
        this.avaliacao = avaStr.isEmpty() ? 0.0 : Double.parseDouble(avaStr);

        String cozinhasStr = campos.get(5);
        cozinhasStr = cozinhasStr.replace("[", "").replace("]", "").replace("'", "");
        this.tipos_cozinha = new ArrayList<>();
        if (!cozinhasStr.trim().isEmpty()) {
            String[] tokens = cozinhasStr.split("[,;]");
            for (String token : tokens) {
                this.tipos_cozinha.add(trimField(token));
            }
        }

        String precoStr = trimField(campos.get(6));
        this.faixa_preco = precoStr.length();

        String horariosStr = trimField(campos.get(7));
        if (!horariosStr.isEmpty() && horariosStr.contains("-")) {
            String[] partes = horariosStr.split("-");
            this.horario_abertura = formatHora(trimField(partes[0]));
            this.horario_fechamento = formatHora(trimField(partes[1]));
        } else {
            this.horario_abertura = "NaN";
            this.horario_fechamento = "NaN";
        }

        String dataStr = trimField(campos.get(8));
        if (!dataStr.isEmpty() && !dataStr.equals("NaN")) {
            String[] dataParts = dataStr.split("-");
            if (dataParts.length == 3) {
                this.data_abertura = String.format("%02d/%02d/%04d", 
                    Integer.parseInt(dataParts[2]), 
                    Integer.parseInt(dataParts[1]), 
                    Integer.parseInt(dataParts[0]));
            } else {
                this.data_abertura = "NaN";
            }
        } else {
            this.data_abertura = "NaN";
        }

        String abertoStr = trimField(campos.get(9)).toLowerCase();
        this.aberto = abertoStr.equals("true") || abertoStr.equals("1");
    }

    public void imprimir() {
        StringBuilder precoStr = new StringBuilder();
        for (int i = 0; i < this.faixa_preco; i++) precoStr.append("$");
        
        StringBuilder cozinhaStr = new StringBuilder("[");
        for (int i = 0; i < this.tipos_cozinha.size(); i++) {
            cozinhaStr.append(this.tipos_cozinha.get(i));
            if (i < this.tipos_cozinha.size() - 1) cozinhaStr.append(",");
        }
        cozinhaStr.append("]");
        
        System.out.printf(Locale.US, "[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %s]\n",
            this.id, this.nome, this.cidade, this.capacidade, this.avaliacao, 
            cozinhaStr.toString(), precoStr.toString(), 
            this.horario_abertura, this.horario_fechamento, 
            this.data_abertura, this.aberto ? "true" : "false");
    }
}

class CelulaDupla {
    Restaurante elemento;
    CelulaDupla ant, prox;

    public CelulaDupla(Restaurante elemento) {
        this.elemento = elemento;
        this.ant = this.prox = null;
    }

    public CelulaDupla() {
        this(null);
    }
}

class ListaDupla {
    CelulaDupla primeiro, ultimo;
    int n;
    
    public static int comp = 0;
    public static int mov = 0;

    public ListaDupla() {
        primeiro = new CelulaDupla();
        ultimo = primeiro;
        n = 0;
    }

    public void inserirFim(Restaurante x) {
        ultimo.prox = new CelulaDupla(x);
        ultimo.prox.ant = ultimo;
        ultimo = ultimo.prox;
        n++;
    }

    public void sort() {
        if (n > 1) {
            quicksort(0, n - 1, primeiro.prox, ultimo);
        }
    }

    private void quicksort(int esq, int dir, CelulaDupla nodeEsq, CelulaDupla nodeDir) {
        int i = esq, j = dir;
        CelulaDupla nodeI = nodeEsq, nodeJ = nodeDir;
         
        int meio = (esq + dir) / 2;
        CelulaDupla nodePivo = nodeEsq;
        for (int k = esq; k < meio; k++) {
            nodePivo = nodePivo.prox;
        }
        Restaurante pivo = nodePivo.elemento;
        
        while (i <= j) {
            while (compare(nodeI.elemento, pivo) < 0) {
                nodeI = nodeI.prox;
                i++;
            }
            while (compare(nodeJ.elemento, pivo) > 0) {
                nodeJ = nodeJ.ant;
                j--;
            }
            
            if (i <= j) { 
                Restaurante temp = nodeI.elemento;
                nodeI.elemento = nodeJ.elemento;
                nodeJ.elemento = temp;
                mov += 3;
                
                nodeI = nodeI.prox;
                i++;
                nodeJ = nodeJ.ant;
                j--;
            }
        }
        
        if (esq < j) quicksort(esq, j, nodeEsq, nodeJ);
        if (i < dir) quicksort(i, dir, nodeI, nodeDir);
    }

    private int compare(Restaurante a, Restaurante b) {
        comp++;
        if (a.getAvaliacao() < b.getAvaliacao()) return -1;
        if (a.getAvaliacao() > b.getAvaliacao()) return 1;
        comp++;
        return a.getNome().compareTo(b.getNome());
    }
}

public class RestaurantesQuicksortLD {
    public static void main(String[] args) throws Exception {
        Map<Integer, Restaurante> todosRestaurantes = new HashMap<>();
         
        try (BufferedReader br = new BufferedReader(new FileReader("/tmp/restaurantes.csv"))) {
            String linha = br.readLine();  
            while ((linha = br.readLine()) != null) {
                Restaurante r = new Restaurante();
                r.ler(linha);
                todosRestaurantes.put(r.getId(), r);
            }
        }
        
        ListaDupla lista = new ListaDupla();
        Scanner sc = new Scanner(System.in);
         
        while (sc.hasNext()) {
            String entrada = sc.next();
            if (entrada.equals("FIM") || entrada.equals("-1")) break;
            
            int idBusca;
            try {
                idBusca = Integer.parseInt(entrada);
            } catch (NumberFormatException e) {
                continue;
            }
            
            Restaurante r = todosRestaurantes.get(idBusca);
            if (r != null) {
                lista.inserirFim(r);
            }
        }
        
        long inicio = System.currentTimeMillis();
        lista.sort();
        long fim = System.currentTimeMillis();
         
        CelulaDupla i = lista.primeiro.prox;
        while (i != null) {
            i.elemento.imprimir();
            i = i.prox;
        }
         
        double tempoMilisegundos = (fim - inicio);
        try (FileWriter fw = new FileWriter("882406_quicksort_flexivel.txt")) {
            fw.write("882406\t" + ListaDupla.comp + "\t" + ListaDupla.mov + "\t" + tempoMilisegundos / 1000.0 + "\n");
        }
        
        sc.close();
    }
}