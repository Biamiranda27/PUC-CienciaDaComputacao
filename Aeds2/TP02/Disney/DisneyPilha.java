import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Locale;
import java.util.Date;

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
        this.country = country;
        this.date_added = date_added;
        this.release_year = release_year;
        this.rating = rating;
        this.duration = duration;
        this.listed_in = new ArrayList<>(Arrays.asList(listed_in));
    }

    public void ler(String linha) {
        String[] partes = new String[12];
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

        this.cast = new ArrayList<>();
        if (!partes[4].equals("NaN")) {
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

        this.listed_in = new ArrayList<>();
        if (!partes[10].equals("NaN")) {
            this.listed_in = new ArrayList<>(Arrays.asList(partes[10].split(", ")));
            Collections.sort(this.listed_in);
        }
    }

    public void imprimir() {
        String castStr = (cast.isEmpty()) ? "[NaN]" : cast.toString();
        String listedInStr = (listed_in.isEmpty()) ? "[NaN]" : listed_in.toString();
    
        System.out.println("=> " + show_id + " ## " + title + " ## " + type + " ## " + director + " ## " + castStr + " ## " +
                country + " ## " + sdf.format(date_added) + " ## " + release_year + " ## " + rating + " ## " +
                duration + " ## " + listedInStr + " ##");
    }
    

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

    public String getTitle() {
        return title;
    }
}

class No {
    public Show elemento;
    public No proximo;

    public No(Show elemento) {
        this.elemento = elemento;
        this.proximo = null;
    }
}

class PilhaShow {
    private No topo;

    public PilhaShow() {
        topo = null;
    }

    public void inserir(Show show) {
        No novo = new No(show);
        novo.proximo = topo;
        topo = novo;
    }

    public Show remover() {
        if (topo == null) {
            return null;
        }
        Show removido = topo.elemento;
        topo = topo.proximo;
        return removido;
    }

    public int tamanhoPilha() {
        int tamanho = 0;
        No aux = topo;
        while (aux != null) {
            tamanho++;
            aux = aux.proximo;
        }
        return tamanho;
    }

    public void imprimirPilhaComIndice() {
        int tamanho = tamanhoPilha();
        imprimirRecursivo(topo, tamanho - 1);
    }

    private void imprimirRecursivo(No no, int indice) {
        if (no != null) {
            System.out.print("[" + indice + "] ");
            no.elemento.imprimir();
            imprimirRecursivo(no.proximo, indice - 1);
        }
    }
}

public class DisneyPilha {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        List<String> idsProcurados = new ArrayList<>();
        String entrada;

        while (!(entrada = scanner.nextLine()).equals("FIM")) {
            idsProcurados.add(entrada.trim());
        }

        PilhaShow pilha = new PilhaShow();

        Map<String, String> mapaLinhaPorId = new HashMap<>();
        try {
            Scanner arquivo = new Scanner(new File("/tmp/disneyplus.csv"));
            arquivo.nextLine(); 

            while (arquivo.hasNextLine()) {
                String linha = arquivo.nextLine();
                String id = linha.split(",")[0];
                mapaLinhaPorId.put(id, linha);
            }
            arquivo.close();
        } catch (FileNotFoundException e) {
            System.out.println("Arquivo não encontrado");
            
        }

        for (String id : idsProcurados) {
            if (mapaLinhaPorId.containsKey(id)) {
                Show s = new Show();
                s.ler(mapaLinhaPorId.get(id));
                pilha.inserir(s);
            }
        }

        int n = Integer.parseInt(scanner.nextLine());

        for (int i = 0; i < n; i++) {
            String comando = scanner.nextLine();
            String[] partes = comando.split(" ");

            switch (partes[0]) {
                case "I":  
                    if (mapaLinhaPorId.containsKey(partes[1])) {
                        Show s = new Show();
                        s.ler(mapaLinhaPorId.get(partes[1]));
                        pilha.inserir(s);
                    }
                    break;

                case "R":  
                    Show removido = pilha.remover();
                    if (removido != null) {
                        System.out.println("(R) " + removido.getTitle());
                    }
                    break;
            }
        }

        pilha.imprimirPilhaComIndice();

        scanner.close();
    }
}
