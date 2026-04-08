import java.io.*;
import java.util.*;

class Show {

    private String showId;
    private String type;
    private String title;
    private String director;
    private String[] cast;
    private String country;
    private String dateAdded;
    private int releaseYear;
    private String rating;
    private String duration;
    private String[] listedIn;

    Show() {
        this.showId = null;
        this.type = null;
        this.title = null;
        this.director = null;
        this.cast = null;
        this.country = null;
        this.dateAdded = null;
        this.releaseYear = 0;
        this.rating = null;
        this.duration = null;
        this.listedIn = null;
    }

    Show(String showId, String type, String title, String director, String[] cast, String country,
            String dateAdded, int releaseYear, String rating, String duration, String[] listedIn) {
        this.showId = showId;
        this.type = type;
        this.title = title;
        this.director = director;
        this.cast = (cast != null) ? Arrays.copyOf(cast, cast.length) : null;
        this.country = country;
        this.dateAdded = dateAdded;
        this.releaseYear = releaseYear;
        this.rating = rating;
        this.duration = duration;
        this.listedIn = (listedIn != null) ? Arrays.copyOf(listedIn, listedIn.length) : null;
    }

    public String getShowId() {

        return showId;
    }

    public void setShowId(String x) {

        this.showId = (x == null || x.equals("")) ? "NaN" : x;
    }

    public String getType() {

        return type;
    }

    public void setType(String x) {

        this.type = (x == null || x.equals("")) ? "NaN" : x;
    }

    public String getTitle() {

        return title;
    }

    public void setTitle(String x) {
        this.title = (x == null || x.equals("")) ? "NaN" : x;
    }

    public String getDirector() {

        return director;
    }

    public void setDirector(String x) {

        this.director = (x == null || x.equals("")) ? "NaN" : x;
    }

    public String[] getCast() {

        return cast;
    }

    public void setCast(String[] x) {

        if (x == null || (x.length == 1 && x[0].equals(""))) {

            this.cast = new String[] { "NaN" };
        } else {
            this.cast = Arrays.copyOf(x, x.length);
        }
    }

    public String getCountry() {

        return country;
    }

    public void setCountry(String x) {

        this.country = (x == null || x.equals("")) ? "NaN" : x;
    }

    public String getDateAdded() {

        return dateAdded;
    }

    public void setDateAdded(String x) {

        this.dateAdded = (x == null || x.equals("")) ? "NaN" : x;
    }

    public int getReleaseYear() {

        return releaseYear;
    }

    public void setReleaseYear(int x) {

        this.releaseYear = x;
    }

    public String getRating() {

        return rating;
    }

    public void setRating(String x) {

        this.rating = (x == null || x.equals("")) ? "NaN" : x;
    }

    public String getDuration() {

        return duration;
    }

    public void setDuration(String x) {

        this.duration = (x == null || x.equals("")) ? "NaN" : x;
    }

    public String[] getListedIn() {

        return listedIn;
    }

    public void setListedIn(String[] listedIn) {

        if (listedIn == null || (listedIn.length == 1 && listedIn[0].equals(""))) {

            this.listedIn = new String[] { "NaN" };
        } else {

            this.listedIn = Arrays.copyOf(listedIn, listedIn.length);
        }
    }

    public Show Clone() {
        return new Show(this.showId, this.type, this.title, this.director, this.cast, this.country, this.dateAdded,
                this.releaseYear, this.rating, this.duration, this.listedIn);
    }

    public int StrToInt(String str) {

        int len = str.length();
        int data = 0;

        for (int i = 0; i < len; i++) {

            char c = str.charAt(i);
            data = (10 * data) + (c - '0');
        }

        return data;
    }

    public void Ler(String in) throws Exception {

        String simplify = "";
        boolean flag = true;
        int len = in.length();

        for (int i = 0; i < len; i++) {

            char c = in.charAt(i);
            if (c == '"')
                flag = !flag;
            else if (c == ',' && flag)
                simplify += '|';
            else
                simplify += c;
        }

        String[] ShowStr = simplify.split("\\|");
        
        setShowId(ShowStr[0]);
        setType(ShowStr[1]);
        setTitle(ShowStr[2]);
        setDirector(ShowStr[3]);

        String[] CastAux = ShowStr[4].split(",\\s*");
        if (CastAux.length > 0 && !CastAux[0].isEmpty()) {
            int castl = CastAux.length;
            quickSort(0, castl - 1, CastAux);
        }
        setCast(CastAux);
        setCountry(ShowStr[5]);
        setDateAdded(ShowStr[6]);

        setReleaseYear(StrToInt(ShowStr[7]));
        setRating(ShowStr[8]);
        setDuration(ShowStr[9]);

        String[] ListedInAux = ShowStr[10].split(",\\s*");
        if (ListedInAux.length > 0 && !ListedInAux[0].isEmpty()) {
            int ListedLen = ListedInAux.length;
            quickSort(0, ListedLen - 1, ListedInAux);
        }
        setListedIn(ListedInAux);

    }

    public static Show Create(String in) throws Exception {
        Show created = new Show();
        created.Ler(in);
        return created;
    }

    public static ArrayList<Show> csv(String caminho) throws Exception {
        ArrayList<Show> shows = new ArrayList<>();
        File file = new File(caminho);
        if (!file.exists()) {
            throw new FileNotFoundException("Arquivo não encontrado: " + caminho);
        }
        try (Scanner sc = new Scanner(file)) {
            sc.nextLine(); // Skip header
            while (sc.hasNextLine()) {
                String data = sc.nextLine();
                shows.add(Create(data));
            }
        }
        return shows;
    }

    public static void swap(int i, int j, String[] array) {

        String temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    public static void quickSort(int esq, int dir, String[] array) {
        if (array == null || array.length == 0 || esq >= dir)
            return;
        int i = esq, j = dir;
        String pivo = array[esq + (dir - esq) / 2];
        while (i <= j) {
            while (array[i].compareTo(pivo) < 0)
                i++;
            while (array[j].compareTo(pivo) > 0)
                j--;
            if (i <= j) {
                swap(i, j, array);
                i++;
                j--;
            }
        }
        if (esq < j)
            quickSort(esq, j, array);
        if (i < dir)
            quickSort(i, dir, array);
    }

    public void Imprimir() {

        System.out.print("=> ");
        System.out.print(showId + " ## ");
        System.out.print(title + " ## ");
        System.out.print(type + " ## ");
        System.out.print(director + " ## ");
        System.out.print("[");
        if (cast != null && cast.length > 0 && !"NaN".equals(cast[0]))
            System.out.print(String.join(", ", cast));
        System.out.print("]");
        System.out.print(" ## ");
        System.out.print(country + " ## ");
        System.out.print(dateAdded + " ## ");
        System.out.print(releaseYear + " ## ");
        System.out.print(rating + " ## ");
        System.out.print(duration + " ## ");
        System.out.print("[");
        if (listedIn != null && listedIn.length > 0 && !"NaN".equals(listedIn[0]))
            System.out.print(String.join(", ", listedIn));
        System.out.print("] ## ");
        System.out.println();
    }
}

class NoLista {
    Show show;
    NoLista prox;

    public NoLista(Show show) {
        this.show = show;
        this.prox = null;
    }
}

class HashIndireta {
    private NoLista[] tabela;
    private int tamHash = 21;

    public HashIndireta() {
        tabela = new NoLista[tamHash];
    }

    private int hash(String title) {
        int soma = 0;
        for (int i = 0; i < title.length(); i++) {
            soma += (int) title.charAt(i);
        }
        return soma % tamHash;
    }

    public void inserir(Show show) {
        int pos = hash(show.getTitle());
        NoLista atual = tabela[pos];
        while (atual != null) {
            if (atual.show.getTitle().equals(show.getTitle()))
                return;
            atual = atual.prox;
        }
        NoLista novo = new NoLista(show);
        novo.prox = tabela[pos];
        tabela[pos] = novo;
    }

    public int[] pesquisarDetalhado(String title) {
        int pos = hash(title);
        NoLista atual = tabela[pos];
        while (atual != null) {
            if (atual.show.getTitle().equals(title)) {
                return new int[] { pos, 1 };
            }
            atual = atual.prox;
        }
        return new int[] { pos, 0 };
    }
}

public class DisneyHashLista {
    public static void main(String[] args) throws Exception {
        long inicio = System.currentTimeMillis();
        Show showManager = new Show(); 
        ArrayList<Show> shows = Show.csv("/tmp/disneyplus.csv"); 

        HashIndireta tabela = new HashIndireta();

        Scanner sc = new Scanner(System.in);
        String linha = sc.nextLine();
        while (!linha.equals("FIM")) {
            for (Show s : shows) {
                if (s != null && s.getShowId().equals(linha)) {
                    tabela.inserir(s);
                    break;
                }
            }
            linha = sc.nextLine();
        }

        linha = sc.nextLine();
        while (!linha.equals("FIM")) {
            int[] resp = tabela.pesquisarDetalhado(linha);
            System.out.print(" (Posicao: " + resp[0] + ") ");
            System.out.println(resp[1] == 1 ? "SIM" : "NAO");
            linha = sc.nextLine();
        }

        long fim = System.currentTimeMillis();
        double tempo = (fim - inicio) / 1000.0;

        try (PrintWriter log = new PrintWriter("845860_hashIndireta.txt")) {
            log.printf("845860\t%.3f\n", tempo);
        } finally {
            sc.close();
        }
    }
}