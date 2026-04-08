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
            String dateAdded, int releaseYear, String rating, String duration, String[] listedIn){
        this.showId = showId;
        this.type = type;
        this.title = title;
        this.director = director;
        this.cast = new String[cast.length];
        System.arraycopy(cast, 0, this.cast, 0, cast.length); 
        this.country = country;
        this.dateAdded = dateAdded;
        this.releaseYear = releaseYear;
        this.rating = rating;
        this.duration = duration;
        this.listedIn = new String[listedIn.length];
        System.arraycopy(listedIn, 0, this.listedIn, 0, listedIn.length);
    }

   
    public String getShowId(){
        return showId;
    }

   
    public void setShowId(String x){
        this.showId = (x.equals("")) ? "NaN" : x;
    }

   
    public String getType(){
        return type;
    }

   
    public void setType(String x){
        this.type = (x.equals("")) ? "NaN" : x;
    }

   
    public String getTitle(){
        return title;
    }

   
    public void setTitle(String x){
        this.title = (x.equals("")) ? "NaN" : x;
    }

  
    public String getDirector(){
        return director;
    }

  
    public void setDirector(String x){
        this.director = (x.equals("")) ? "NaN" : x;
    }

  
    public String[] getCast(){
        return cast;
    }

   
    public void setCast(String[] x){
        if(x.length == 1 && x[0].equals("")){
            this.cast = new String[] { "NaN" };
        } else {
            this.cast = x;
        }
    }

  
    public String getCountry(){
        return country;
    }

    
    public void setCountry(String x){
        this.country = (x.equals("")) ? "NaN" : x;
    }

   
    public String getDateAdded(){
        return dateAdded;
    }

  
    public void setDateAdded(String x){
        this.dateAdded = (x.equals("")) ? "NaN" : x;
    }

  
    public int getReleaseYear(){
        return releaseYear;
    }

    
    public void setReleaseYear(int x){
        this.releaseYear = x;
    }

   
    public String getRating(){
        return rating;
    }

   
    public void setRating(String x){
        this.rating = (x.equals("")) ? "NaN" : x;
    }

   
    public String getDuration(){
        return duration;
    }

  
    public void setDuration(String x){
        this.duration = (x.equals("")) ? "NaN" : x;
    }

  
    public String[] getListedIn(){
        return listedIn;
    }

  
    public void setListedIn(String[] listedIn){
        if(listedIn.length == 1 && listedIn[0].equals("")){
            this.listedIn = new String[] { "NaN" };
        } else {
            this.listedIn = listedIn;
        }
    }

  
    public Show Clone(){
        return new Show(this.showId,this.type,this.title,this.director,this.cast,this.country,this.dateAdded,this.releaseYear,this.rating,this.duration,this.listedIn);
    }

   
    public int StrToInt(String str){
        
        int len = str.length();
        int data = 0;
        for(int i = 0; i < len; i++){
            char c = str.charAt(i);
            data = (10 * data) + (c - '0');
        }
        return data;
    }

  
    public void Ler(String in) throws Exception{
       
        String simplify = "";
        boolean flag = true;
        int len = in.length();

        for(int i = 0; i < len; i++){
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
        int castl = CastAux.length;
        quickSort(0, castl - 1, CastAux);
        setCast(CastAux);
        setCountry(ShowStr[5]);
        setDateAdded(ShowStr[6]);

        setReleaseYear(StrToInt(ShowStr[7]));
        setRating(ShowStr[8]);
        setDuration(ShowStr[9]);

        String[] ListedInAux = ShowStr[10].split(",\\s*");
        int ListedLen = ListedInAux.length;
        quickSort(0, ListedLen - 1, ListedInAux);
        setListedIn(ListedInAux);
    }

 
    public static Show Create(String in) throws Exception{
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
            if (sc.hasNextLine()) {
                sc.nextLine(); 
            }
            while (sc.hasNext()) {
                String data = sc.nextLine();
                shows.add(Create(data));
            }
        }
        return shows;
    }

  
    public static void swap(int i, int j, String[] array){
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
            while (array[i].compareTo(pivo) < 0) i++;
            while (array[j].compareTo(pivo) > 0) j--;
            if (i <= j) {
                swap(i, j, array);
                i++;
                j--;
            }
        }
        if (esq < j) quickSort(esq, j, array);
        if (i < dir) quickSort(i, dir, array);
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


class NoTitulo {
    String title;
    Show show;
    NoTitulo esq, dir;

  
    public NoTitulo(Show show) {
        this.title = show.getTitle();
        this.show = show;
        this.esq = this.dir = null;
    }
}


class ArvoreTitulo {
    private NoTitulo raiz;

   
    public void inserir(Show show) {
        raiz = inserir(raiz, show);
    }

  
    private NoTitulo inserir(NoTitulo no, Show show) {
        if (no == null) return new NoTitulo(show);
        int cmp = show.getTitle().compareTo(no.title);
        if (cmp < 0) no.esq = inserir(no.esq, show);
        else if (cmp > 0) no.dir = inserir(no.dir, show);
        return no;
    }

    public boolean pesquisar(String title, StringBuilder caminho) {
        return pesquisar(raiz, title, caminho);
    }

   
    private boolean pesquisar(NoTitulo no, String title, StringBuilder caminho) {
        if (no == null) return false;
        int cmp = title.compareTo(no.title);
        if (cmp == 0) return true;
        else if (cmp < 0) {
            caminho.append("esq ");
            return pesquisar(no.esq, title, caminho);
        } else {
            caminho.append("dir ");
            return pesquisar(no.dir, title, caminho);
        }
    }
}


class NoAno {
    int chave; 
    NoAno esq, dir;
    ArvoreTitulo titulos;

   
    public NoAno(int chave) {
        this.chave = chave;
        this.esq = this.dir = null;
        this.titulos = new ArvoreTitulo();
    }
}


class ArvoreAno {
    private NoAno raiz;

  
    public void inserir(Show show) {
        int chave = show.getReleaseYear() % 15;
        raiz = inserir(raiz, chave, show);
    }

   
    private NoAno inserir(NoAno no, int chave, Show show) {
        if (no == null) {
            NoAno novo = new NoAno(chave);
            novo.titulos.inserir(show);
            return novo;
        }
        if (chave < no.chave) no.esq = inserir(no.esq, chave, show);
        else if (chave > no.chave) no.dir = inserir(no.dir, chave, show);
        else no.titulos.inserir(show); 
        return no;
    }

   
    public boolean pesquisar(String title, int releaseYear, StringBuilder caminho) {
        int chave = releaseYear % 15;
        caminho.append("raiz ");
        return pesquisar(raiz, chave, title, caminho);
    }


    private boolean pesquisar(NoAno no, int chave, String title, StringBuilder caminho) {
        if (no == null) return false;

        StringBuilder caminhoTitulo = new StringBuilder();
        boolean achou = no.titulos.pesquisar(title, caminhoTitulo);
        caminho.append(caminhoTitulo); 
        if (achou) return true;

        if (chave < no.chave) {
            caminho.append("ESQ ");
            return pesquisar(no.esq, chave, title, caminho);
        } else if (chave > no.chave) {
            caminho.append("DIR ");
            return pesquisar(no.dir, chave, title, caminho);
        }
        return false;
    }
}


public class DisneyArvoreArvore {
    public static void main(String[] args) throws Exception {
        long inicio = System.currentTimeMillis();
        Show showManager = new Show();
        // Carrega os dados do CSV
        ArrayList<Show> shows = showManager.csv("/tmp/disneyplus.csv");

        ArvoreAno arvore = new ArvoreAno();

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
            Show encontrado = null;
            for (Show s : shows) {
                if (s != null && s.getTitle().equals(linha)) {
                    encontrado = s;
                    break;
                }
            }
            StringBuilder caminho = new StringBuilder();
            boolean achou = false;
            if (encontrado != null) {
                achou = arvore.pesquisar(encontrado.getTitle(), encontrado.getReleaseYear(), caminho);
            }
            System.out.print(caminho);
            System.out.println(achou ? "SIM" : "NAO");
            linha = sc.nextLine();
        }

        long fim = System.currentTimeMillis();
        double tempo = (fim - inicio) / 1000.0;

        try (PrintWriter log = new PrintWriter("845860_arvoreArvore.txt")) {
            log.printf("845860\t%.3f\t%d\n", tempo, 0); 
        } finally {
            sc.close(); 
        }
    }
}
