/* Usando vetores, implemente o algoritmo Mergesort considerando que a chave de ordenação é o atributo Price.
Em caso de empate, utilize o AppID do Game como critério secundário.

Entrada e saída padrão são iguais às da questão de Ordenação por Seleção.
Saída: os registros ordenados pelo atributo Price (desempatando por AppID).
Ao final, imprima os 5 preços mais caros e os 5 mais baratos.

 Além disso, crie um arquivo de log na pasta corrente com o nome suamatricula_mergesort.txt, contendo uma única linha com:
Sua matrícula
Número de comparações (entre elementos do array)
Número de movimentações (entre elementos do array)
Tempo de execução do algoritmo de ordenação

 Todas as informações do arquivo de log devem ser separadas por uma tabulação (\t). */


import java.io.*;
import java.text.*;
import java.util.*;

// int App_Id, String Name, String Release_Date, int Estimated_Owners, float Price, List<String> Supported_Languages, int Metacritic_Score, int User_Score,
// int Achievements, String Publishers, String Developers, List<String> Categories, List<String> Genres, List<String> Tags


public class MergeGames implements Cloneable { //classe principal, e faz com que os objetos/atributos sejam copiados
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

    MergeGames() {
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
        this.Price = objetos[4].equals("NaN") ? 0.0 : Double.parseDouble(objetos[4]);
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

    public String getAppId() { return this.App_Id; }
    public double getPrice() { return this.Price; }

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


    public static void mergeSort(List<MergeGames> lista, int esquerda, int direita, int[] comparacoes, int[] movimentacoes) {
        if (esquerda < direita) {
            int meio = (esquerda + direita) / 2;
            mergeSort(lista, esquerda, meio, comparacoes, movimentacoes);
            mergeSort(lista, meio + 1, direita, comparacoes, movimentacoes);
            merge(lista, esquerda, meio, direita, comparacoes, movimentacoes);
        }
    }

    private static void merge(List<MergeGames> lista, int esquerda, int meio, int direita, int[] comparacoes, int[] movimentacoes) {
        int n1 = meio - esquerda + 1;
        int n2 = direita - meio;

        List<MergeGames> L = new ArrayList<>();
        List<MergeGames> R = new ArrayList<>();

        for (int i = 0; i < n1; i++) L.add(lista.get(esquerda + i));
        for (int j = 0; j < n2; j++) R.add(lista.get(meio + 1 + j));

        int i = 0, j = 0, k = esquerda;

        while (i < n1 && j < n2) {
            comparacoes[0]++;
            MergeGames left = L.get(i);
            MergeGames right = R.get(j);

            if (left.getPrice() < right.getPrice() ||
                    (left.getPrice() == right.getPrice() && Integer.parseInt(left.getAppId()) <= Integer.parseInt(right.getAppId()))) {
                lista.set(k, left);
                i++;
            } else {
                lista.set(k, right);
                j++;
            }
            movimentacoes[0]++;
            k++;
        }

        while (i < n1) {
            lista.set(k, L.get(i));
            i++; k++; movimentacoes[0]++;
        }

        while (j < n2) {
            lista.set(k, R.get(j));
            j++; k++; movimentacoes[0]++;
        }
    }

    public static void main(String[] args) throws IOException {
        long inicio = System.currentTimeMillis();
        int[] comparacoes = {0};
        int[] movimentacoes = {0};

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
        List<MergeGames> vetor = new ArrayList<>();

        String entrada;
        while (!(entrada = sc.nextLine()).equals("FIM")) {
            if (ArquivoCSV.containsKey(entrada)) {
                MergeGames jogo = new MergeGames();
                jogo.lerCSV(ArquivoCSV.get(entrada));
                vetor.add(jogo);
            }
        }

        mergeSort(vetor, 0, vetor.size() - 1, comparacoes, movimentacoes);

        System.out.println("| 5 preços mais caros | ");
        for (int i = vetor.size() - 1; i >= Math.max(0, vetor.size() - 5); i--) {
            vetor.get(i).imprimirCSV();
        }
        System.out.print("\n");

        System.out.println("| 5 preços mais baratos | ");
        for (int i = 0; i < Math.min(5, vetor.size()); i++) {
            vetor.get(i).imprimirCSV();
        }

        sc.close();

        long fim = System.currentTimeMillis();
        double tempo = (fim - inicio) / 1000.0;

        FileWriter log = new FileWriter("845860_mergesort.txt");
        log.write("845860" + "\t" + comparacoes[0] + "\t" + movimentacoes[0] + "\t" + tempo);
        log.close();
    }
} 