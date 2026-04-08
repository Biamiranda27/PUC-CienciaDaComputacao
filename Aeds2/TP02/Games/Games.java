import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

// int App_Id, String Name, String Release_Date, int Estimated_Owners, float Price, List<String> Supported_Languages, int Metacritic_Score, int User_Score,
// int Achievements, String Publishers, String Developers, List<String> Categories, List<String> Genres, List<String> Tags

public class Games implements Cloneable{ //classe principal, e faz com que os objetos/atributos sejam copiados
    String App_Id;
    private String Name;
    private Date Release_Date;
    String Estimated_Owners;
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

    Games(){
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

    Games(String App_Id, String Name, Date Release_Date, String Estimated_Owners, double Price, String[] Supported_Languages, int Metacritic_Score, double User_Score,
         int Achievements, String Publishers, String Developers, String[] Categories, String[] Genres, String[] Tags){
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
    public Games clone(){ //copia o construtor, e as mudancas feitas nao afetam o objeto original
        return new Games(App_Id, Name, Release_Date, Estimated_Owners, Price, Supported_Languages.clone(), Metacritic_Score, User_Score, Achievements, Publishers,
                        Developers, Categories.clone(), Genres.clone(), Tags.clone());                                       
    }


    public void lerCSV(String linha){
        String[] objetos = new String[14];
        String[] separar = linha.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);
        for(int i = 0; i < objetos.length; i++){
        objetos[i] = (i < separar.length && !separar[i].trim().isEmpty()) ? separar[i].trim().replaceAll("^\"|\"$", "") : "NaN";
    }
    SimpleDateFormat sdfOriginDateFormat = new SimpleDateFormat ("MMM dd, yyyy", Locale.ENGLISH);
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

public void imprimirCSV(){
    SimpleDateFormat sdfOriginDateFormat  = new SimpleDateFormat("dd/MM/yyyy");
        String New_Data = (Release_Date != null) ? sdfOriginDateFormat.format(Release_Date) : "NaN";
        System.out.println(
            "=> " + App_Id + " ## " + Name + " ## " + New_Data + " ## " +
            Estimated_Owners + " ## " + Price + " ## " + Arrays.toString(Supported_Languages) + " ## " +
            Metacritic_Score + " ## " + User_Score + " ## " + Achievements + " ## [" +
            Publishers + "] ## [" + Developers + "] ## " + Arrays.toString(Categories) + " ## " +
            Arrays.toString(Genres) + " ## " + Arrays.toString(Tags) + " ##"
        );
}

 public static void main(String[] args) throws IOException {
        Map<String, String> ArquivoCSV = new HashMap<>();
        BufferedReader ler = new BufferedReader(new FileReader("/tmp/games.csv")); 
        ler.readLine();
        String linha;
        while ((linha = ler.readLine()) != null) {
            String id = linha.split(",")[0];
            ArquivoCSV.put(id, linha);
        }
        ler.close();
        Scanner scanner = new Scanner(System.in);
        String input;
        while (!(input = scanner.nextLine()).equals("FIM")) {
            if (ArquivoCSV.containsKey(input)) {
                Games games = new Games();
                games.lerCSV(ArquivoCSV.get(input));
                games.imprimirCSV();
            } else {
                System.out.println("=> NaN ## NaN ## null ## NaN ## 0.0f ## [NaN] ## -1 ## -1.0f ## 0 ## [NaN] ## [NaN] ## [NaN] ## [NaN] ## [NaN] ##");
            }
        }
          scanner.close();
    }

}


