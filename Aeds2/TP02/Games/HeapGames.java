/*Usando vetores, implemente o algoritmo Heapsort considerando que a chave de ordenação é o atributo Estimated_owners.
Em caso de empate, use como critério secundário o AppID do Game.

Entrada e saída padrão são iguais às da questão de Ordenação por Seleção.
Saída: os registros ordenados pelo atributo Estimated_owners (desempatando por AppID).

Além disso, crie um arquivo de log na pasta corrente com o nome suamatricula_heapsort.txt, contendo uma única linha com:

Sua matrícula
Número de comparações (entre elementos do array, incluindo as usadas na manutenção do heap)
Número de movimentações (trocas/atribuições entre elementos do array)
Tempo de execução do algoritmo de ordenação


Todas as informações do arquivo de log devem ser separadas por uma tabulação (\t). */

// int App_Id, String Name, String Release_Date, int Estimated_Owners, float Price, List<String> Supported_Languages, int Metacritic_Score, int User_Score,
// int Achievements, String Publishers, String Developers, List<String> Categories, List<String> Genres, List<String> Tags

import java.io.*;
import java.text.*;
import java.util.*;

public class HeapGames implements Cloneable { //classe principal, e faz com que os objetos/atributos sejam copiados
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

    HeapGames() {
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

    public String getAppId() {
        return this.App_Id;
    }

    public String getEstimatedOwners() {
        return this.Estimated_Owners;
    }

    public long getOwnersMinValue() {
        if (Estimated_Owners.equals("NaN")) return 0;
        try {
            String[] parts = Estimated_Owners.split(" - ");
            String num = parts[0].replaceAll("[^0-9]", "");
            return Long.parseLong(num);
        } catch (Exception e) {
            return 0;
        }
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


    public static void heapSort(HeapGames[] vetor, int n, int[] comparacoes, int[] movimentacoes) {
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(vetor, n, i, comparacoes, movimentacoes);
        }

        for (int i = n - 1; i > 0; i--) {
            HeapGames temp = vetor[0];
            vetor[0] = vetor[i];
            vetor[i] = temp;
            movimentacoes[0]++;

            heapify(vetor, i, 0, comparacoes, movimentacoes);
        }
    }

    private static void heapify(HeapGames[] vetor, int n, int i, int[] comparacoes, int[] movimentacoes) {
        int maior = i;
        int esquerda = 2 * i + 1;
        int direita = 2 * i + 2;

        if (esquerda < n) {
            comparacoes[0]++;
            if (compareGames(vetor[esquerda], vetor[maior]) > 0) {
                maior = esquerda;
            }
        }

        if (direita < n) {
            comparacoes[0]++;
            if (compareGames(vetor[direita], vetor[maior]) > 0) {
                maior = direita;
            }
        }

        if (maior != i) {
            HeapGames temp = vetor[i];
            vetor[i] = vetor[maior];
            vetor[maior] = temp;
            movimentacoes[0]++;
            heapify(vetor, n, maior, comparacoes, movimentacoes);
        }
    }

    private static int compareGames(HeapGames a, HeapGames b) {
        long ownersA = a.getOwnersMinValue();
        long ownersB = b.getOwnersMinValue();

        if (ownersA < ownersB) return -1;
        if (ownersA > ownersB) return 1;
        int idA = Integer.parseInt(a.getAppId());
        int idB = Integer.parseInt(b.getAppId());
        return Integer.compare(idA, idB);
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
        List<HeapGames> lista = new ArrayList<>();

        String entrada;
        while (!(entrada = sc.nextLine()).equals("FIM")) {
            if (ArquivoCSV.containsKey(entrada)) {
                HeapGames jogo = new HeapGames();
                jogo.lerCSV(ArquivoCSV.get(entrada));
                lista.add(jogo);
            }
        }

        sc.close();

        HeapGames[] vetor = lista.toArray(new HeapGames[0]);
        heapSort(vetor, vetor.length, comparacoes, movimentacoes);

        for (HeapGames jogo : vetor) {
            jogo.imprimirCSV();
        }

        long fim = System.currentTimeMillis();
        double tempo = (fim - inicio) / 1000.0;

        FileWriter log = new FileWriter("845860_heapsort.txt");
        log.write("845860" + "\t" + comparacoes[0] + "\t" + movimentacoes[0] + "\t" + tempo);
        log.close();
    }
}
