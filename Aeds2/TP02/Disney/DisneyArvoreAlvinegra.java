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

    public String getShowId() {
        return showId;
    }

    public void setShowId(String x) {
        this.showId = (x.equals("")) ? "NaN" : x;
    }

    public String getType() {
        return type;
    }

    public void setType(String x) {
        this.type = (x.equals("")) ? "NaN" : x;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String x) {
        this.title = (x.equals("")) ? "NaN" : x;
    }

    public String getDirector() {
        return director;
    }

    public void setDirector(String x) {
        this.director = (x.equals("")) ? "NaN" : x;
    }

    public String[] getCast() {
        return cast;
    }

    public void setCast(String[] x) {
        if (x.length == 1 && x[0].equals("")) {
            this.cast = new String[] { "NaN" };
        } else {
            this.cast = x;
        }
    }

    public String getCountry() {
        return country;
    }

    public void setCountry(String x) {
        this.country = (x.equals("")) ? "NaN" : x;
    }

    public String getDateAdded() {
        return dateAdded;
    }

    public void setDateAdded(String x) {
        this.dateAdded = (x.equals("")) ? "NaN" : x;
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
        this.rating = (x.equals("")) ? "NaN" : x;
    }

    public String getDuration() {
        return duration;
    }

    public void setDuration(String x) {
        this.duration = (x.equals("")) ? "NaN" : x;
    }

    public String[] getListedIn() {
        return listedIn;
    }

    public void setListedIn(String[] listedIn) {
        if (listedIn.length == 1 && listedIn[0].equals("")) {
            this.listedIn = new String[] { "NaN" };
        } else {
            this.listedIn = listedIn;
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
        quickSort(0, CastAux.length - 1, CastAux);
        setCast(CastAux);
        setCountry(ShowStr[5]);
        setDateAdded(ShowStr[6]);
        setReleaseYear(StrToInt(ShowStr[7]));
        setRating(ShowStr[8]);
        setDuration(ShowStr[9]);
        String[] ListedInAux = ShowStr[10].split(",\\s*");
        quickSort(0, ListedInAux.length - 1, ListedInAux);
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
            while (sc.hasNext()) {
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

    public Show(String showId, String type, String title, String director, String[] cast, String country,
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

    public void Imprimir() {
        System.out.print("=> ");
        System.out.print(showId + " ## ");
        System.out.print(title + " ## ");
        System.out.print(type + " ## ");
        System.out.print(director + " ## ");
        System.out.print("[");
        if(cast != null && cast.length > 0)
            System.out.print(String.join(", ", cast));
        System.out.print("]");
        System.out.print(" ## ");
        System.out.print(country + " ## ");
        System.out.print(dateAdded + " ## ");
        System.out.print(releaseYear + " ## ");
        System.out.print(rating + " ## ");
        System.out.print(duration + " ## ");
        System.out.print("[");
        if(listedIn != null && listedIn.length > 0)
            System.out.print(String.join(", ", listedIn));
        System.out.print("] ## ");
        System.out.println();
    }
}

class No {
    Show show;
    No esq, dir;
    int altura;

    public No(Show show) {
        this.show = show;
        this.esq = this.dir = null;
        this.altura = 1;
    }
}

class ArvoreAVL {
    private No raiz;
    public int comparacoes = 0;

    private int altura(No no) {
        return (no == null) ? 0 : no.altura;
    }

    private void setAltura(No no) {
        no.altura = 1 + Math.max(altura(no.esq), altura(no.dir));
    }

    private int balanceamento(No no) {
        return (no == null) ? 0 : altura(no.dir) - altura(no.esq);
    }

    private No rotacaoDir(No y) {
        No x = y.esq;
        No T2 = x.dir;

        x.dir = y;
        y.esq = T2;

        setAltura(y);
        setAltura(x);

        return x;
    }

    private No rotacaoEsq(No x) {
        No y = x.dir;
        No T2 = y.esq;

        y.esq = x;
        x.dir = T2;

        setAltura(x);
        setAltura(y);

        return y;
    }

    public void inserir(Show show) {
        raiz = inserir(raiz, show);
    }

    private No inserir(No no, Show show) {
        if (no == null) {
            return new No(show);
        }
        comparacoes++;
        int cmp = show.getTitle().compareTo(no.show.getTitle());
        if (cmp < 0) {
            no.esq = inserir(no.esq, show);
        } else if (cmp > 0) {
            no.dir = inserir(no.dir, show);
        } else {
            return no;
        }

        setAltura(no);

        int balance = balanceamento(no);

        if (balance > 1 && show.getTitle().compareTo(no.dir.show.getTitle()) > 0) {
            return rotacaoEsq(no);
        }

        if (balance < -1 && show.getTitle().compareTo(no.esq.show.getTitle()) < 0) {
            return rotacaoDir(no);
        }

        if (balance > 1 && show.getTitle().compareTo(no.dir.show.getTitle()) < 0) {
            no.dir = rotacaoDir(no.dir);
            return rotacaoEsq(no);
        }

        if (balance < -1 && show.getTitle().compareTo(no.esq.show.getTitle()) > 0) {
            no.esq = rotacaoEsq(no.esq);
            return rotacaoDir(no);
        }

        return no;
    }

    public boolean pesquisar(String nome) {
        System.out.print("=>raiz ");
        return pesquisar(raiz, nome);
    }

    private boolean pesquisar(No no, String nome) {
        if (no == null) {
            System.out.println("NAO");
            return false;
        }
        comparacoes++;
        int cmp = nome.compareTo(no.show.getTitle());
        if (cmp == 0) {
            System.out.println("SIM");
            return true;
        } else if (cmp < 0) {
            System.out.print("esq ");
            if (no.esq == null) {
                System.out.println("NAO");
                return false;
            }
            return pesquisar(no.esq, nome);
        } else {
            System.out.print("dir ");
            if (no.dir == null) {
                System.out.println("NAO");
                return false;
            }
            return pesquisar(no.dir, nome);
        }
    }
}

public class DisneyArvoreAlvinegra {
    public static void main(String[] args) throws Exception {
        long inicio = System.currentTimeMillis();

        Show showManager = new Show();
        ArrayList<Show> shows = showManager.csv("/tmp/disneyplus.csv");

        ArvoreAVL arvore = new ArvoreAVL();
        Scanner sc = new Scanner(System.in);

        String linha = sc.nextLine();
        while (!linha.equals("FIM")) {
            for (Show s : shows) {
                if (s != null && s.getShowId().equals(linha)) {
                    arvore.inserir(s);
                    break;
                }
            }
            linha = sc.nextLine();
        }

        linha = sc.nextLine();
        while (!linha.equals("FIM")) {
            arvore.pesquisar(linha);
            linha = sc.nextLine();
        }

        long fim = System.currentTimeMillis();
        double tempo = (fim - inicio) / 1000.0;

        try (PrintWriter log = new PrintWriter("845860_avinegra.txt")) {
            log.printf("845860\t%.3f\t%d\n", tempo, arvore.comparacoes);
        }
    }
}
