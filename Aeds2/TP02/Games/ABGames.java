import java.io.*;
import java.text.*;
import java.util.*;

public class ABGames implements Cloneable {

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

    ABGames() {
        this.App_Id = "NaN";
        this.Name = "NaN";
        this.Release_Date = null;
        this.Estimated_Owners = "NaN";
        this.Price = 0.0;
        this.Supported_Languages = new String[]{"NaN"};
        this.Metacritic_Score = -1;
        this.User_Score = -1.0;
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
        } catch (Exception e) {
            this.Release_Date = null;
        }

        this.Estimated_Owners = objetos[3];
        this.Price = objetos[4].equals("NaN") ? 0.0 : Double.parseDouble(objetos[4]);
        this.Supported_Languages = objetos[5].equals("NaN") ?
                new String[]{"NaN"} : objetos[5].replaceAll("\\[|\\]|'", "").split(",\\s*");

        this.Metacritic_Score = objetos[6].equals("NaN") ? -1 : Integer.parseInt(objetos[6]);
        this.User_Score = objetos[7].equals("NaN") ? -1.0 : Double.parseDouble(objetos[7]);
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

    public Integer getReleaseYear() {
        if (this.Release_Date == null) return null;
        Calendar cal = Calendar.getInstance();
        cal.setTime(this.Release_Date);
        return cal.get(Calendar.YEAR);
    }


    static class Node {
        ABGames game;
        Node left, right;

        Node(ABGames g) {
            this.game = g;
        }
    }

    static class Tree {
        Node root;
        int comparacoes = 0;

        void insert(ABGames g) {
            root = insertRec(root, g);
        }

        private Node insertRec(Node node, ABGames g) {
            if (node == null) return new Node(g);

            comparacoes++;
            int cmp = g.getName().compareTo(node.game.getName());

            if (cmp < 0)
                node.left = insertRec(node.left, g);
            else if (cmp > 0)
                node.right = insertRec(node.right, g);
            return node;
        }

        void searchPrint(String name) {
            System.out.print("raiz  ");
            searchRec(root, name);
        }

        private void searchRec(Node node, String name) {

            if (node == null) {
                System.out.println("NAO");
                return;
            }

            comparacoes++;
            int cmp = name.compareTo(node.game.getName());

            if (cmp == 0) {
                System.out.println("SIM");
                return;
            }

            if (cmp < 0) {
                System.out.print("esq ");
                searchRec(node.left, name);
            } else {
                System.out.print("dir ");
                searchRec(node.right, name);
            }
        }
    }


    public static void main(String[] args) throws Exception {

        long inicio = System.currentTimeMillis();

        Map<String, String> mapCSV = new HashMap<>();
        BufferedReader br = new BufferedReader(new FileReader("/tmp/games.csv"));
        br.readLine();
        String linha;

        while ((linha = br.readLine()) != null) {
            String id = linha.split(",")[0];
            mapCSV.put(id, linha);
        }
        br.close();

        Scanner sc = new Scanner(System.in);
        Tree arvore = new Tree();

        Map<String, ABGames> nameMap = new HashMap<>();

        while (true) {
            String entrada = sc.nextLine();
            if (entrada.equals("FIM")) break;

            if (mapCSV.containsKey(entrada)) {
                ABGames game = new ABGames();
                game.lerCSV(mapCSV.get(entrada));
                arvore.insert(game);

                nameMap.put(game.getName(), game);
            }
        }

        while (sc.hasNextLine()) {
            String nome = sc.nextLine();
            if (nome.equals("FIM")) break;

            ABGames g = nameMap.get(nome);
            String yearStr = "NaN";
            if (g != null && g.getReleaseYear() != null) {
                yearStr = Integer.toString(g.getReleaseYear());
            }

            System.out.print(nome + " (" + yearStr + ") Edition: ");
            arvore.searchPrint(nome);
        }

        sc.close();

        long fim = System.currentTimeMillis();
        double tempo = (fim - inicio) / 1000.0;

        FileWriter log = new FileWriter("845860_arvoreBinaria.txt");
        log.write("845860\t" + arvore.comparacoes + "\t" + tempo);
        log.close();
    }
}
