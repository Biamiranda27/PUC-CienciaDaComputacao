import java.io.*;
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

    public void ler(String linha) {
        SimpleDateFormat sdf = new SimpleDateFormat("MMM dd, yyyy");
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

    public void imprimir() {
        SimpleDateFormat sdf = new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH);
        String dataStr = (date_added != null) ? sdf.format(date_added) : "NaN";
        String[] castOrdenado = cast.clone();
        Arrays.sort(castOrdenado, String.CASE_INSENSITIVE_ORDER);

        for (int i = 0; i < castOrdenado.length; i++) {
            castOrdenado[i] = castOrdenado[i].replaceAll("\"", "");
        }

        System.out.println("=> " + show_id + " ## " + title + " ## " + type + " ## " + director +
                " ## " + Arrays.toString(castOrdenado) + " ## " + country + " ## " + dataStr + " ## " +
                release_year + " ## " + rating + " ## " + duration + " ## " + Arrays.toString(listed_in) + " ##");
    }

    public String getTituloNormalizado() {
        return title == null ? "nan" : title.replaceAll("\"", "").trim().toLowerCase();
    }

    public String getTipoNormalizado() {
        return type == null ? "nan" : type.replaceAll("\"", "").trim().toLowerCase();
    }

    public Show clone() {
        return new Show(show_id, type, title, director, cast.clone(), country, date_added, release_year, rating, duration, listed_in.clone());
    }
}

public class DisneyInsercao {
    public static void main(String[] args) throws IOException {
        ArrayList<Show> lista = new ArrayList<>();
        Map<String, String> dadosCSV = new HashMap<>();
        Scanner sc = new Scanner(System.in);

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

        int comparacoes = 0;
        int movimentacoes = 0;

        long inicio = System.nanoTime();

        for (int i = 1; i < lista.size(); i++) {
            Show chave = lista.get(i).clone();
            int j = i - 1;
            comparacoes++;
            while (j >= 0 && (
                lista.get(j).getTipoNormalizado().compareTo(chave.getTipoNormalizado()) > 0 ||
                (lista.get(j).getTipoNormalizado().compareTo(chave.getTipoNormalizado()) == 0 &&
                 lista.get(j).getTituloNormalizado().compareTo(chave.getTituloNormalizado()) > 0)
            )) {
                comparacoes++;
                lista.set(j + 1, lista.get(j).clone());
                movimentacoes++;
                j--;
            }
            lista.set(j + 1, chave.clone());
            movimentacoes++;
        }

        long fim = System.nanoTime();
        double tempoExecucao = (fim - inicio) / 1_000_000.0;

        for (Show s : lista) {
            s.imprimir();
        }

        BufferedWriter bw = new BufferedWriter(new FileWriter("845860_insercao.txt"));
        bw.write("845860\t" + comparacoes + "\t" + movimentacoes + "\t" + String.format("%.2f", tempoExecucao));
        bw.close();
    }
}
