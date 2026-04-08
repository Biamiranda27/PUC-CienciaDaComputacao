import java.io.*;
import java.text.*;
import java.util.*;

class Show {
    String id, tipo, titulo, diretor, elenco, pais;
    String data_adicionada, classificacao, duracao, categorias;
    int ano_lancamento;

    public Show(String linha) {
        String[] campos = parseCSVLine(linha);
        this.id = getOrDefault(campos[0]);
        this.tipo = getOrDefault(campos[1]);
        this.titulo = getOrDefault(campos[2]);
        this.diretor = getOrDefault(campos[3]);
        this.elenco = getOrDefault(campos[4]);
        this.pais = getOrDefault(campos[5]);
        this.data_adicionada = getOrDefault(campos[6]);
        this.ano_lancamento = campos[7].isEmpty() ? -1 : Integer.parseInt(campos[7]);
        this.classificacao = getOrDefault(campos[8]);
        this.duracao = getOrDefault(campos[9]);
        this.categorias = getOrDefault(campos[10]);
    }

    private String getOrDefault(String campo) {
        return campo.isEmpty() ? "NaN" : campo;
    }

    private String[] parseCSVLine(String linha) {
        List<String> campos = new ArrayList<>();
        boolean dentroDeAspas = false;
        StringBuilder sb = new StringBuilder();

        for (char c : linha.toCharArray()) {
            if (c == '"') {
                dentroDeAspas = !dentroDeAspas;
            } else if (c == ',' && !dentroDeAspas) {
                campos.add(sb.toString());
                sb.setLength(0);
            } else {
                sb.append(c);
            }
        }
        campos.add(sb.toString());
        return campos.toArray(new String[0]);
    }

    public void imprimir() {
        String elencoOrdenado = ordenarElenco();
        System.out.printf("=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##\n",
                id, titulo, tipo, diretor, elencoOrdenado, pais, data_adicionada, ano_lancamento,
                classificacao, duracao, categorias);
    }

    private String ordenarElenco() {
        if (elenco.equals("NaN")) return elenco;
        String[] nomes = elenco.split(",");
        for (int i = 0; i < nomes.length; i++) nomes[i] = nomes[i].trim();
        Arrays.sort(nomes);
        return String.join(", ", nomes);
    }

    public static int comparar(Show a, Show b) {
        Date da = parseData(a.data_adicionada);
        Date db = parseData(b.data_adicionada);

        if (!da.equals(db)) return da.compareTo(db);
        return a.titulo.compareToIgnoreCase(b.titulo);
    }

    private static Date parseData(String data) {
        if (data.equals("NaN")) return new Date(0);
        try {
            SimpleDateFormat sdf = new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH);
            return sdf.parse(data);
        } catch (ParseException e) {
            return new Date(0);
        }
    }
}

class Node {
    Show show;
    Node prev, next;

    Node(Show show) {
        this.show = show;
    }
}

class ListaDupla {
    Node head, tail;

    void inserirFim(Show show) {
        Node novo = new Node(show);
        if (head == null) {
            head = tail = novo;
        } else {
            tail.next = novo;
            novo.prev = tail;
            tail = novo;
        }
    }

    void quickSort() {
        quickSort(head, tail);
    }

    private void quickSort(Node esq, Node dir) {
        if (esq != null && dir != null && esq != dir && esq != dir.next) {
            Node pivo = particionar(esq, dir);
            quickSort(esq, pivo.prev);
            quickSort(pivo.next, dir);
        }
    }

    private Node particionar(Node esq, Node dir) {
        Show pivo = dir.show;
        Node i = esq.prev;

        for (Node j = esq; j != dir; j = j.next) {
            if (Show.comparar(j.show, pivo) <= 0) {
                i = (i == null) ? esq : i.next;
                Show tmp = i.show;
                i.show = j.show;
                j.show = tmp;
            }
        }

        i = (i == null) ? esq : i.next;
        Show tmp = i.show;
        i.show = dir.show;
        dir.show = tmp;
        return i;
    }

    void imprimir() {
        for (Node atual = head; atual != null; atual = atual.next) {
            atual.show.imprimir();
        }
    }
}

public class DisneyQuickD {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        BufferedReader br = new BufferedReader(new FileReader("/tmp/disneyplus.csv"));

        Map<String, Show> mapa = new HashMap<>();
        String linha;
        br.readLine(); // pular cabeçalho

        while ((linha = br.readLine()) != null) {
            Show s = new Show(linha);
            mapa.put(s.id, s);
        }
        br.close();

        ListaDupla lista = new ListaDupla();
        while (true) {
            String entrada = sc.nextLine();
            if (entrada.equals("FIM")) break;
            if (mapa.containsKey(entrada)) {
                lista.inserirFim(mapa.get(entrada));
            }
        }

        long inicio = System.currentTimeMillis();
        lista.quickSort();
        long fim = System.currentTimeMillis();

        lista.imprimir();

        PrintWriter log = new PrintWriter("845860_quicksort3.txt");
        log.printf("845860\t%s\t%s\t%.2f\n", "-", "-", (fim - inicio) * 1.0);
        log.close();
        sc.close();
    }
}

