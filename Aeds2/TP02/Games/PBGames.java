import java.io.*;
import java.text.*;
import java.util.*;


// int App_Id, String Name, String Release_Date, int Estimated_Owners, float Price, List<String> Supported_Languages, int Metacritic_Score, int User_Score,
// int Achievements, String Publishers, String Developers, List<String> Categories, List<String> Genres, List<String> Tags

public class PBGames implements Cloneable { //classe principal, e faz com que os objetos/atributos sejam copiados
    private String App_Id; 
    private String Name;
    private Date Release_Date;
    private String Estimated_Owners;
    private double Price;
    private String[] Supported_Languages;
    private int Metacritic_Score;
    private double User_Score;
    private int Achievements;
    private String Publishers;
    private String Developers;
    private String[] Categories;
    private String[] Genres;
    private String[] Tags;

    PBGames() {
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

    public void lerCSV(String linha) {
        String[] objetos = new String[14];
        String[] separar = linha.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);
        for (int i = 0; i < objetos.length; i++) {
            objetos[i] = (i < separar.length && !separar[i].trim().isEmpty())
                    ? separar[i].trim().replaceAll("^\"|\"$", "")
                    : "NaN";
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
        this.Supported_Languages = objetos[5].equals("NaN") ? new String[]{"NaN"}
                : objetos[5].replaceAll("\\[|\\]|'", "").split(",\\s*");
        this.Metacritic_Score = objetos[6].equals("NaN") ? -1 : Integer.parseInt(objetos[6]);
        this.User_Score = objetos[7].equals("NaN") ? -1.0f : Double.parseDouble(objetos[7]);
        this.Achievements = objetos[8].equals("NaN") ? 0 : Integer.parseInt(objetos[8]);
        this.Publishers = objetos[9];
        this.Developers = objetos[10];
        this.Categories = objetos[11].equals("NaN") ? new String[]{"NaN"} : objetos[11].split(",");
        this.Genres = objetos[12].equals("NaN") ? new String[]{"NaN"} : objetos[12].split(",");
        this.Tags = objetos[13].equals("NaN") ? new String[]{"NaN"} : objetos[13].split(",");
    }

    public String getName() {
        return this.Name;
    }

    public static boolean buscaBinaria(List<PBGames> lista, String nome, int[] comparacoes) {
        int esq = 0, dir = lista.size() - 1;

        while (esq <= dir) {
            int meio = (esq + dir) / 2;
            comparacoes[0]++;

            int testa = lista.get(meio).getName().compareToIgnoreCase(nome);

            if (testa == 0) {
                return true;
            } else if (testa < 0) {
                esq = meio + 1;
            } else {
                dir = meio - 1;
            }
        }
        return false;
    }

    public static void main(String[] args) throws IOException {
        long startTime = System.currentTimeMillis();
        int[] comparacoes = {0};

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
        List<PBGames> vetor = new ArrayList<>();

        String entrada;
        while (!(entrada = sc.nextLine()).equals("FIM")) {
            if (ArquivoCSV.containsKey(entrada)) {
                PBGames jogo = new PBGames();
                jogo.lerCSV(ArquivoCSV.get(entrada));
                vetor.add(jogo);
            }
        }

        vetor.sort(Comparator.comparing(PBGames::getName, String.CASE_INSENSITIVE_ORDER));

        while (!(entrada = sc.nextLine()).equals("FIM")) {
            boolean achou = buscaBinaria(vetor, entrada, comparacoes);
            if(achou == true){
                System.out.println("\t SIM");
            } else{
                System.out.println("\t NAO");
            }
        }

        sc.close();

        long endTime = System.currentTimeMillis();
        double tempo = (endTime - startTime) / 1000.0;

        FileWriter log = new FileWriter("845860_binaria.txt");
        log.write("845860" + "\t" + tempo + "\t" + comparacoes[0]);
        log.close();
    }
}
