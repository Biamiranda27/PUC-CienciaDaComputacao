import java.io.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

// int App_Id, String Name, String Release_Date, int Estimated_Owners, float Price, List<String> Supported_Languages, int Metacritic_Score, int User_Score,
// int Achievements, String Publishers, String Developers, List<String> Categories, List<String> Genres, List<String> Tags


public class LASGames implements Cloneable { //classe principal, e faz com que os objetos/atributos sejam copiados
    String App_Id;
    String Name;
    Date Release_Date;
    String Estimated_Owners;
    double Price;
    String[] Supported_Languages;
    int Metacritic_Score;
    double User_Score;
    int Achievements;
    String Publishers;
    String Developers;
    String[] Categories;
    String[] Genres;
    String[] Tags;

    LASGames() {
        this.App_Id = "NaN";
        this.Name = "NaN";
        this.Release_Date = null;
        this.Estimated_Owners = "NaN";
        this.Price = 0.0f;
        this.Supported_Languages = new String[]{"NaN"};
        this.Metacritic_Score = -1;
        this.User_Score = -1.0f;
        this.Achievements = 0;
        this.Publishers = "NaN";
        this.Developers = "NaN";
        this.Categories = new String[]{"NaN"};
        this.Genres = new String[]{"NaN"};
        this.Tags = new String[]{"NaN"};
    }

    LASGames(String App_Id, String Name, Date Release_Date, String Estimated_Owners, double Price, String[] Supported_Languages, int Metacritic_Score, double User_Score,
             int Achievements, String Publishers, String Developers, String[] Categories, String[] Genres, String[] Tags) {
        this.App_Id = App_Id;
        this.Name = Name;
        this.Release_Date = Release_Date;
        this.Estimated_Owners = Estimated_Owners;
        this.Price = Price;
        this.Supported_Languages = Supported_Languages;
        this.Metacritic_Score = Metacritic_Score;
        this.User_Score = User_Score;
        this.Achievements = Achievements;
        this.Publishers = Publishers;
        this.Developers = Developers;
        this.Categories = Categories;
        this.Genres = Genres;
        this.Tags = Tags;
    }

    @Override
    public LASGames clone() {
        return new LASGames(App_Id, Name, Release_Date, Estimated_Owners, Price, Supported_Languages.clone(), Metacritic_Score, User_Score, Achievements, Publishers,
                Developers, Categories.clone(), Genres.clone(), Tags.clone());
    }

    public void lerCSV(String linha) {
        String[] objetos = new String[14];
        String[] separar = linha.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);
        for (int i = 0; i < objetos.length; i++) {
            objetos[i] = (i < separar.length && !separar[i].trim().isEmpty()) ? separar[i].trim().replaceAll("^\"|\"$", "") : "NaN";
        }
        SimpleDateFormat sdfOriginDateFormat = new SimpleDateFormat("MMM dd, yyyy", Locale.ENGLISH);
        this.App_Id = objetos[0];
        this.Name = objetos[1];
        try {
            this.Release_Date = objetos[2].equals("NaN") ? null : sdfOriginDateFormat.parse(objetos[2]);
        } catch (ParseException e) {
            this.Release_Date = null;
        }
        this.Estimated_Owners = objetos[3];
        this.Price = objetos[4].equals("NaN") ? 0.0f : Double.parseDouble(objetos[4]);
        this.Supported_Languages = objetos[5].equals("NaN") ? new String[]{"NaN"} : objetos[5]
                .replaceAll("\\[|\\]|'", "")
                .split(",\\s*");
        this.Metacritic_Score = objetos[6].equals("NaN") ? -1 : Integer.parseInt(objetos[6]);
        this.User_Score = objetos[7].equals("NaN") ? -1.0f : Double.parseDouble(objetos[7]);
        this.Achievements = objetos[8].equals("NaN") ? 0 : Integer.parseInt(objetos[8]);
        this.Publishers = objetos[9];
        this.Developers = objetos[10];
        this.Categories = objetos[11].equals("NaN") ? new String[]{"NaN"} : objetos[11].split(",");
        this.Genres = objetos[12].equals("NaN") ? new String[]{"NaN"} : objetos[12].split(",");
        this.Tags = objetos[13].equals("NaN") ? new String[]{"NaN"} : objetos[13].split(",");
    }

    public void imprimirCSV() {
        SimpleDateFormat sdfOriginDateFormat = new SimpleDateFormat("dd/MM/yyyy");
        String New_Data = (Release_Date != null) ? sdfOriginDateFormat.format(Release_Date) : "NaN";
        System.out.println(
                "=> " + App_Id + " ## " + Name + " ## " + New_Data + " ## " +
                        Estimated_Owners + " ## " + Price + " ## " + Arrays.toString(Supported_Languages) + " ## " +
                        Metacritic_Score + " ## " + User_Score + " ## " + Achievements + " ## [" +
                        Publishers + "] ## [" + Developers + "] ## " + Arrays.toString(Categories) + " ## " +
                        Arrays.toString(Genres) + " ## " + Arrays.toString(Tags) + " ##"
        );
    }

    public static void main(String[] args) throws Exception {
        Map<String, String> ArquivoCSV = new HashMap<>();
        BufferedReader ler = new BufferedReader(new FileReader("/tmp/games.csv"));
        ler.readLine();
        String linha;
        while ((linha = ler.readLine()) != null) {
            String id = linha.split(",")[0];
            ArquivoCSV.put(id, linha);
        }
        ler.close();
        Scanner sc = new Scanner(System.in);
        ListaGames lista = new ListaGames(1000);
        String input;
        while (!(input = sc.nextLine()).equals("FIM")) {
            if (ArquivoCSV.containsKey(input)) {
                LASGames g = new LASGames();
                g.lerCSV(ArquivoCSV.get(input));
                lista.inserirFim(g);
            }
        }
        int nComandos = Integer.parseInt(sc.nextLine());
        for (int i = 0; i < nComandos; i++) {
            String comando = sc.nextLine();
            String[] partes = comando.split(" ");
            String tipo = partes[0];
            switch (tipo) {
                case "II": {
                    LASGames g = new LASGames();
                    g.lerCSV(ArquivoCSV.get(partes[1]));
                    lista.inserirInicio(g);
                    break;
                }
                case "IF": {
                    LASGames g = new LASGames();
                    g.lerCSV(ArquivoCSV.get(partes[1]));
                    lista.inserirFim(g);
                    break;
                }
                case "I*": {
                    int pos = Integer.parseInt(partes[1]);
                    LASGames g = new LASGames();
                    g.lerCSV(ArquivoCSV.get(partes[2]));
                    lista.inserir(g, pos);
                    break;
                }
                case "RI": {
                    LASGames removido = lista.removerInicio();
                    System.out.println("(R) " + removido.Name);
                    break;
                }
                case "RF": {
                    LASGames removido = lista.removerFim();
                    System.out.println("(R) " + removido.Name);
                    break;
                }
                case "R*": {
                    int pos = Integer.parseInt(partes[1]);
                    LASGames removido = lista.remover(pos);
                    System.out.println("(R) " + removido.Name);
                    break;
                }
            }
        }
        lista.mostrar();
        sc.close();
    }
}

class ListaGames {
    private LASGames[] array;
    private int n;

    public ListaGames(int tamanho) {
        array = new LASGames[tamanho];
        n = 0;
    }

    public void inserirInicio(LASGames game) throws Exception {
        if (n >= array.length) throw new Exception("Erro");
        for (int i = n; i > 0; i--) array[i] = array[i - 1];
        array[0] = game.clone();
        n++;
    }

    public void inserir(LASGames game, int pos) throws Exception {
        if (n >= array.length) throw new Exception("Erro");
        if (pos < 0 || pos > n) throw new Exception("Erro");
        for (int i = n; i > pos; i--) array[i] = array[i - 1];
        array[pos] = game.clone();
        n++;
    }

    public void inserirFim(LASGames g) throws Exception {
        if (n >= array.length) throw new Exception("Erro");
        array[n++] = g.clone();
    }

    public LASGames removerInicio() throws Exception {
        if (n == 0) throw new Exception("Erro");
        LASGames resp = array[0];
        for (int i = 0; i < n - 1; i++) array[i] = array[i + 1];
        n--;
        return resp;
    }

    public LASGames remover(int pos) throws Exception {
        if (n == 0) throw new Exception("Erro");
        if (pos < 0 || pos >= n) throw new Exception("Erro");
        LASGames resp = array[pos];
        for (int i = pos; i < n - 1; i++) array[i] = array[i + 1];
        n--;
        return resp;
    }

    public LASGames removerFim() throws Exception {
        if (n == 0) throw new Exception("Erro");
        return array[--n];
    }

    public void mostrar() {
        for (int i = 0; i < n; i++) {
            System.out.print("[" + i + "] ");
            array[i].imprimirCSV();
        }
    }
}
