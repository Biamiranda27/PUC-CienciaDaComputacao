import java.io.*;
import java.text.*;
import java.util.*;

public class ABAGames implements Cloneable {

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

    ABAGames() {
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

        for (int i = 0; i < objetos.length; i++)
            objetos[i] = (i < separar.length && !separar[i].trim().isEmpty())
                    ? separar[i].trim().replaceAll("^\"|\"$", "")
                    : "NaN";

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

    public int getEstimatedOwnersMod15() {
        try {
            String owners = Estimated_Owners.split("-")[0].replaceAll("[^0-9]", "");
            return Integer.parseInt(owners) % 15;
        } catch (Exception e) {
            return 0;
        }
    }

    public Integer getReleaseYear() {
        if (this.Release_Date == null) return null;
        Calendar cal = Calendar.getInstance();
        cal.setTime(this.Release_Date);
        return cal.get(Calendar.YEAR);
    }

    static class Node2 {
        ABAGames game;
        Node2 left, right;

        Node2(ABAGames g) {
            this.game = g;
        }
    }

    static class Tree2 {
        Node2 root;
        int comparacoes = 0;

        void insert(ABAGames g) {
            root = insertRec(root, g);
        }

        private Node2 insertRec(Node2 node, ABAGames g) {
            if (node == null) return new Node2(g);

            comparacoes++;
            int cmp = g.getName().compareTo(node.game.getName());

            if (cmp < 0)
                node.left = insertRec(node.left, g);
            else if (cmp > 0)
                node.right = insertRec(node.right, g);

            return node;
        }

        boolean search(String name) {
            Node2 node = root;

            while (node != null) {
                comparacoes++;
                int cmp = name.compareTo(node.game.getName());

                if (cmp == 0) return true;

                if (cmp < 0) {
                    System.out.print("esq ");
                    node = node.left;
                } else {
                    System.out.print("dir ");
                    node = node.right;
                }
            }
            return false;
        }
    }

    static class Node1 {
        int key;
        Node1 left, right;
        Tree2 arvoreSecundaria = new Tree2();

        Node1(int k) {
            this.key = k;
        }
    }

    static class Tree1 {
        Node1 root;

        void insert(int k) {
            root = insertRec(root, k);
        }

        private Node1 insertRec(Node1 node, int k) {
            if (node == null) return new Node1(k);
            if (k < node.key)
                node.left = insertRec(node.left, k);
            else if (k > node.key)
                node.right = insertRec(node.right, k);
            return node;
        }

        Node1 searchKey(int k) {
            Node1 node = root;
            while (node != null) {
                if (k == node.key) return node;
                if (k < node.key) node = node.left;
                else node = node.right;
            }
            return null;
        }
    }

    static void inserirJogo(Tree1 primeira, ABAGames g) {
        int chave = g.getEstimatedOwnersMod15();
        Node1 no = primeira.searchKey(chave);
        if (no != null) no.arvoreSecundaria.insert(g);
    }

    static boolean pesquisarNome(Tree1 primeira, String nome) {
        return pesquisarRec(primeira.root, nome);
    }

    static boolean pesquisarRec(Node1 node, String nome) {
        if (node == null) return false;

        boolean achou = node.arvoreSecundaria.search(nome);
        if (achou) return true;

        if (node.left != null) {
            System.out.print(" ESQ ");
            if (pesquisarRec(node.left, nome)) return true;
        }

        if (node.right != null) {
            System.out.print(" DIR ");
            if (pesquisarRec(node.right, nome)) return true;
        }

        return false;
    }

    static int somaComparacoes(Node1 node) {
        if (node == null) return 0;
        return node.arvoreSecundaria.comparacoes
                + somaComparacoes(node.left)
                + somaComparacoes(node.right);
    }

    public static void main(String[] args) throws Exception {

        long inicio = System.currentTimeMillis();

        Map<String, String> mapCSV = new HashMap<>();
        BufferedReader br = new BufferedReader(new FileReader("/tmp/games.csv"));
        br.readLine();
        String linha;

        while ((linha = br.readLine()) != null) {
            String id = linha.split(",", -1)[0];
            mapCSV.put(id, linha);
        }
        br.close();

        Tree1 primeiraArvore = new Tree1();
        int[] ordem = {7,3,11,1,5,9,13,0,2,4,6,8,10,12,14};

        for (int x : ordem) primeiraArvore.insert(x);

        Scanner sc = new Scanner(System.in);

        while (true) {
            String entrada = sc.nextLine().trim();
            if (entrada.equals("FIM")) break;

            if (mapCSV.containsKey(entrada)) {
                ABAGames g = new ABAGames();
                g.lerCSV(mapCSV.get(entrada));
                inserirJogo(primeiraArvore, g);
            }
        }

        int totalComparacoes = 0;

        while (true) {
            String nome = sc.nextLine().trim();
            if (nome.equals("FIM")) break;

            System.out.print("=> " + nome + " => raiz ");
            boolean achou = pesquisarNome(primeiraArvore, nome);
            System.out.println(achou ? " SIM" : " NAO");

            totalComparacoes = somaComparacoes(primeiraArvore.root);
        }

        sc.close();

        long fim = System.currentTimeMillis();
        double tempo = (fim - inicio) / 1000.0;

        FileWriter log = new FileWriter("845860_arvoreArvore.txt");
        log.write("845860\t" + totalComparacoes + "\t" + tempo);
        log.close();
    }
}
