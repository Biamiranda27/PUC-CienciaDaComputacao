import java.io.File;
import java.io.FileNotFoundException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

class Show {
    private String show_id;
    private String type;
    private String title;
    private String director;
    private String[] cast;
    private String country;
    private Date date_added;
    private int release_year;
    private String rating;
    private String duration;
    private String[] listed_in;

    public Show() {
        this.show_id = "NaN";
        this.type = "NaN";
        this.title = "NaN";
        this.director = "NaN";
        this.cast = new String[]{"NaN"};
        this.country = "NaN";
        this.date_added = null;
        this.release_year = -1;
        this.rating = "NaN";
        this.duration = "NaN";
        this.listed_in = new String[]{"NaN"};
    }

    public void ler(String linha) {
        SimpleDateFormat sdf = new SimpleDateFormat("MMM dd, yyyy", Locale.ENGLISH);
        String[] campos = new String[12];

        String[] partes = linha.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);
        for (int i = 0; i < campos.length; i++) {
            campos[i] = (i < partes.length && !partes[i].trim().isEmpty()) ? partes[i].trim().replaceAll("^\"|\"$", "") : "NaN";
        }

        this.show_id = campos[0];
        this.type = campos[1];
        this.title = campos[2];
        this.director = campos[3];
        this.cast = campos[4].equals("NaN") ? new String[]{"NaN"} : campos[4].split(", ");
        this.country = campos[5];
        try {
            this.date_added = campos[6].equals("NaN") ? null : sdf.parse(campos[6]);
        } catch (ParseException e) {
            this.date_added = null;
        }
        this.release_year = campos[7].equals("NaN") ? -1 : Integer.parseInt(campos[7]);
        this.rating = campos[8];
        this.duration = campos[9];
        this.listed_in = campos[10].equals("NaN") ? new String[]{"NaN"} : campos[10].split(", ");
    }

    public Show clone() {
        return new Show(show_id, type, title, director, cast.clone(), country, date_added, release_year, rating, duration, listed_in.clone());
    }

    public Show(String show_id, String type, String title, String director, String[] cast, String country,
                Date date_added, int release_year, String rating, String duration, String[] listed_in) {
        this.show_id = show_id;
        this.type = type;
        this.title = title;
        this.director = director;
        this.cast = cast;
        this.country = country;
        this.date_added = date_added;
        this.release_year = release_year;
        this.rating = rating;
        this.duration = duration;
        this.listed_in = listed_in;
    }

    public void imprimir() {
        SimpleDateFormat sdf = new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH);
        String data = (date_added != null) ? sdf.format(date_added) : "NaN";

        String[] castOrdenado = cast.clone();
        Arrays.sort(castOrdenado, String.CASE_INSENSITIVE_ORDER);
        for (int i = 0; i < castOrdenado.length; i++) {
            castOrdenado[i] = castOrdenado[i].replaceAll("\"", "");
        }

        String tituloLimpo = title.replaceAll("\"", "");

        System.out.println("=> " + show_id + " ## " + tituloLimpo + " ## " + type + " ## " + director +
                " ## " + Arrays.toString(castOrdenado) + " ## " + country + " ## " + data + " ## " +
                release_year + " ## " + rating + " ## " + duration + " ## " + Arrays.toString(listed_in) + " ##");
    }

    public String getTitle() { return title; }
    public String getDuration() { return duration; }
}

public class DisneyMerge {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        ArrayList<Show> lista = new ArrayList<>();
        HashMap<String, String> base = new HashMap<>();

        //BufferedReader br = new BufferedReader(new FileReader("./disneyplus.csv")); // local
        BufferedReader br = new BufferedReader(new FileReader("/tmp/disneyplus.csv")); // verde
        br.readLine(); // ignorar cabeçalho
        String linha;
        while ((linha = br.readLine()) != null) {
            String id = linha.split(",")[0];
            base.put(id, linha);
        }
        br.close();

        String entrada;
        while (!(entrada = sc.nextLine()).equals("FIM")) {
            if (base.containsKey(entrada)) {
                Show s = new Show();
                s.ler(base.get(entrada));
                lista.add(s);
            }
        }
        sc.close();

        int[] comp = {0}, mov = {0};
        long start = System.nanoTime();

        ordenar(lista, comp, mov);

        long end = System.nanoTime();
        double tempo = (end - start) / 1_000_000.0;

        for (Show s : lista) {
            s.imprimir();
        }

        BufferedWriter writer = new BufferedWriter(new FileWriter("846431_mergesort.txt"));
        writer.write("846431\t" + comp[0] + "\t" + mov[0] + "\t" + String.format("%.2f", tempo));
        writer.close();
    }

    public static void ordenar(ArrayList<Show> lista, int[] comp, int[] mov) {
        if (lista.size() <= 1) return;
        mergeSort(lista, 0, lista.size() - 1, comp, mov);
    }

    private static void mergeSort(ArrayList<Show> lista, int esq, int dir, int[] comp, int[] mov) {
        if (esq < dir) {
            int meio = (esq + dir) / 2;
            mergeSort(lista, esq, meio, comp, mov);
            mergeSort(lista, meio + 1, dir, comp, mov);
            intercalar(lista, esq, meio, dir, comp, mov);
        }
    }

    private static void intercalar(ArrayList<Show> lista, int esq, int meio, int dir, int[] comp, int[] mov) {
        ArrayList<Show> esqLista = new ArrayList<>();
        ArrayList<Show> dirLista = new ArrayList<>();

        for (int i = esq; i <= meio; i++) esqLista.add(lista.get(i).clone());
        for (int i = meio + 1; i <= dir; i++) dirLista.add(lista.get(i).clone());

        int i = 0, j = 0, k = esq;
        while (i < esqLista.size() && j < dirLista.size()) {
            comp[0]++;
            if (comparar(esqLista.get(i), dirLista.get(j)) <= 0) {
                lista.set(k++, esqLista.get(i++).clone());
            } else {
                lista.set(k++, dirLista.get(j++).clone());
            }
            mov[0]++;
        }

        while (i < esqLista.size()) {
            lista.set(k++, esqLista.get(i++).clone());
            mov[0]++;
        }

        while (j < dirLista.size()) {
            lista.set(k++, dirLista.get(j++).clone());
            mov[0]++;
        }
    }

    private static int comparar(Show a, Show b) {
        int durA = extrairDuracao(a.getDuration());
        int durB = extrairDuracao(b.getDuration());
        int cmp = Integer.compare(durA, durB);
        if (cmp != 0) return cmp;
        return a.getTitle().compareTo(b.getTitle());
    }

    private static int extrairDuracao(String dur) {
        try {
            if (dur.contains("min")) {
                return Integer.parseInt(dur.replaceAll("[^0-9]", ""));
            } else if (dur.contains("Season")) {
                return Integer.parseInt(dur.replaceAll("[^0-9]", "")) * 1000;
            }
        } catch (Exception e) {
            return 0;
        }
        return 0;
    }
}
 
    

