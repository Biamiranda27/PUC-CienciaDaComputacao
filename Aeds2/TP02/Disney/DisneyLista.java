import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

class ListaShow {
    private Show[] array;
    private int n;

    public ListaShow(int tamanho) {
        array = new Show[tamanho];
        n = 0;
    }

    public void inserirInicio(Show show) throws Exception {
        if (n >= array.length) throw new Exception("Erro ao inserir!");
        for (int i = n; i > 0; i--) {
            array[i] = array[i - 1];
        }
        array[0] = show;
        n++;
    }

    public void inserirFim(Show show) throws Exception {
        if (n >= array.length) throw new Exception("Erro ao inserir!");
        array[n++] = show;
    }

    public void inserir(Show show, int pos) throws Exception {
        if (n >= array.length || pos < 0 || pos > n) throw new Exception("Erro ao inserir!");
        for (int i = n; i > pos; i--) {
            array[i] = array[i - 1];
        }
        array[pos] = show;
        n++;
    }

    public Show removerInicio() throws Exception {
        if (n == 0) throw new Exception("Erro ao remover!");
        Show resp = array[0];
        for (int i = 0; i < n - 1; i++) {
            array[i] = array[i + 1];
        }
        n--;
        return resp;
    }

    public Show removerFim() throws Exception {
        if (n == 0) throw new Exception("Erro ao remover!");
        return array[--n];
    }

    public Show remover(int pos) throws Exception {
        if (n == 0 || pos < 0 || pos >= n) throw new Exception("Erro ao remover!");
        Show resp = array[pos];
        for (int i = pos; i < n - 1; i++) {
            array[i] = array[i + 1];
        }
        n--;
        return resp;
    }

    public void mostrar() {
        for (int i = 0; i < n; i++) {
            System.out.print("[" + i + "] ");
            array[i].mostrar();
        }
    }
}

class Show implements Cloneable {
    private String show_id;
    private String type;
    private String title;
    private String director;
    private List<String> cast = new ArrayList<>();
    private String country;
    private Date date_added;
    private int release_year;
    private String rating;
    private String duration;
    private List<String> listed_in = new ArrayList<>();

    private static final SimpleDateFormat sdf = new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH);

    public Show() {
        this.show_id = "NaN";
        this.type = "NaN";
        this.title = "NaN";
        this.director = "NaN";
        this.cast = new ArrayList<>();
        this.country = "NaN";
        try {
            this.date_added = sdf.parse("March 1, 1900");
        } catch (ParseException e) {
            this.date_added = new Date();
        }
        this.release_year = 0;
        this.rating = "NaN";
        this.duration = "NaN";
        this.listed_in = new ArrayList<>();
    }

    public Show(String show_id, String type, String title, String director, String[] cast, String country,
                Date date_added, int release_year, String rating, String duration, String[] listed_in) {
        this.show_id = show_id;
        this.type = type;
        this.title = title;
        this.director = director;
        this.cast = new ArrayList<>(Arrays.asList(cast));
        Collections.sort(this.cast);
        this.country = country;
        this.date_added = date_added;
        this.release_year = release_year;
        this.rating = rating;
        this.duration = duration;
        this.listed_in = new ArrayList<>(Arrays.asList(listed_in));
        Collections.sort(this.listed_in);
    }

    public void ler(String linha) {
        List<String> campos = new ArrayList<>();
        boolean aspas = false;
        StringBuilder campo = new StringBuilder();

        for (int i = 0; i < linha.length(); i++) {
            char c = linha.charAt(i);
            if (c == '"') {
                aspas = !aspas;
            } else if (c == ',' && !aspas) {
                campos.add(campo.toString().trim());
                campo.setLength(0);
            } else {
                campo.append(c);
            }
        }
        campos.add(campo.toString().trim());

        String[] partes = new String[12];
        for (int i = 0; i < partes.length; i++) {
            if (i < campos.size()) {
                partes[i] = campos.get(i).isEmpty() ? "NaN" : campos.get(i);
            } else {
                partes[i] = "NaN";
            }
        }

        this.show_id = partes[0];
        this.type = partes[1];
        this.title = partes[2];
        this.director = partes[3];

        if (partes[4].equals("NaN")) {
            this.cast = new ArrayList<>();
        } else {
            this.cast = new ArrayList<>(Arrays.asList(partes[4].split(", ")));
            Collections.sort(this.cast);
        }

        this.country = partes[5];

        try {
            this.date_added = partes[6].equals("NaN") ? sdf.parse("March 1, 1900") : sdf.parse(partes[6]);
        } catch (ParseException e) {
            try {
                this.date_added = sdf.parse("March 1, 1900");
            } catch (ParseException ex) {
                this.date_added = new Date();
            }
        }

        try {
            this.release_year = Integer.parseInt(partes[7]);
        } catch (NumberFormatException e) {
            this.release_year = 0;
        }

        this.rating = partes[8];
        this.duration = partes[9];

        if (partes[10].equals("NaN")) {
            this.listed_in = new ArrayList<>();
        } else {
            this.listed_in = new ArrayList<>(Arrays.asList(partes[10].split(", ")));
            Collections.sort(this.listed_in);
        }
    }

    public void imprimir() {
        System.out.println("=> " + show_id + " ## " + title + " ## " + type + " ## " + director + " ## " + cast + " ## " +
                country + " ## " + sdf.format(date_added) + " ## " + release_year + " ## " + rating + " ## " +
                duration + " ## " + listed_in + " ##");
    }

    public void mostrar() {
        System.out.println(this.show_id + " " +
                this.type + " " +
                this.title + " " +
                this.director + " " +
                this.cast + " " +
                this.country + " " +
                sdf.format(this.date_added) + " " +
                this.release_year + " " +
                this.rating + " " +
                this.duration + " " +
                this.listed_in);
    }

    @Override
    public Show clone() {
        try {
            Show clone = (Show) super.clone();
            clone.cast = new ArrayList<>(this.cast);
            clone.listed_in = new ArrayList<>(this.listed_in);
            clone.date_added = (Date) this.date_added.clone();
            return clone;
        } catch (CloneNotSupportedException e) {
            return null;
        }
    }

    public String getShow_id() { return show_id; }
    public void setShow_id(String show_id) { this.show_id = show_id; }

    public String getType() { return type; }
    public void setType(String type) { this.type = type; }

    public String getTitle() { return title; }
    public void setTitle(String title) { this.title = title; }

    public String getDirector() { return director; }
    public void setDirector(String director) { this.director = director; }

    public String[] getCast() { return cast.toArray(new String[0]); }
    public void setCast(String[] cast) {
        this.cast = new ArrayList<>(Arrays.asList(cast));
        Collections.sort(this.cast);
    }

    public String getCountry() { return country; }
    public void setCountry(String country) { this.country = country; }

    public Date getDate_added() { return date_added; }
    public void setDate_added(Date date_added) { this.date_added = date_added; }

    public int getRelease_year() { return release_year; }
    public void setRelease_year(int release_year) { this.release_year = release_year; }

    public String getRating() { return rating; }
    public void setRating(String rating) { this.rating = rating; }

    public String getDuration() { return duration; }
    public void setDuration(String duration) { this.duration = duration; }

    public String[] getListed_in() { return listed_in.toArray(new String[0]); }
    public void setListed_in(String[] listed_in) {
        this.listed_in = new ArrayList<>(Arrays.asList(listed_in));
        Collections.sort(this.listed_in);
    }
}

public class DisneyLista {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        List<String> idsProcurados = new ArrayList<>();
        String entrada;

        while (true) {
            entrada = scanner.nextLine();
            if (entrada.equals("FIM")) break;
            idsProcurados.add(entrada.trim());
        }

        try {
            Scanner arquivo = new Scanner(new File("/tmp/disneyplus.csv"));
            arquivo.nextLine();

            while (arquivo.hasNextLine()) {
                String linha = arquivo.nextLine();
                String idLinha = linha.split(",")[0];
                if (idsProcurados.contains(idLinha)) {
                    Show s = new Show();
                    s.ler(linha);
                    s.imprimir();
                }
            }

            arquivo.close();
        } catch (FileNotFoundException e) {
            System.out.println("Arquivo não encontrado");
        }

        scanner.close();
    }
}

