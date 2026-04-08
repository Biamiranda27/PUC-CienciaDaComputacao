import java.io.*;
import java.text.*;
import java.util.*;

public class AVLGames implements Cloneable {

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

    AVLGames() {
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
        AVLGames game;
        Node left, right, parent;
        boolean color;

        Node(AVLGames g) {
            this.game = g;
            this.color = true; 
        }
    }
    static class RBT {
        Node root;
        int comparacoes = 0;

        private void rotateLeft(Node x) {
            if (x == null || x.right == null) return;

            Node y = x.right;
            x.right = y.left;
            if (y.left != null) {
                y.left.parent = x;
            }

            y.parent = x.parent;
            if (x.parent == null) {
                root = y;
            } else if (x == x.parent.left) {
                x.parent.left = y;
            } else {
                x.parent.right = y;
            }

            y.left = x;
            x.parent = y;
        }

        private void rotateRight(Node x) {
            if (x == null || x.left == null) return;

            Node y = x.left;
            x.left = y.right;
            if (y.right != null) {
                y.right.parent = x;
            }

            y.parent = x.parent;
            if (x.parent == null) {
                root = y;
            } else if (x == x.parent.right) {
                x.parent.right = y;
            } else {
                x.parent.left = y;
            }

            y.right = x;
            x.parent = y;
        }

        void insert(AVLGames g) {
            Node novo = new Node(g);
            if (root == null) {
                root = novo;
                root.color = false; 
                return;
            }

            Node current = root;
            Node parent = null;

            while (current != null) {
                parent = current;
                comparacoes++;
                int cmp = novo.game.getName().compareTo(current.game.getName());
                if (cmp < 0) {
                    current = current.left;
                } else if (cmp > 0) {
                    current = current.right;
                } else {
                    return;
                }
            }

            novo.parent = parent;
            comparacoes++;
            if (novo.game.getName().compareTo(parent.game.getName()) < 0)
                parent.left = novo;
            else
                parent.right = novo;

            fixInsert(novo);
        }

        private void fixInsert(Node z) {
            while (z.parent != null && z.parent.color == true) {
                Node gp = z.parent.parent;
                if (gp == null) break; 

                if (z.parent == gp.left) {
                    Node y = gp.right; 
                    if (y != null && y.color == true) {
                        z.parent.color = false;
                        y.color = false;
                        gp.color = true;
                        z = gp;
                    } else {
                        if (z == z.parent.right) {
                            z = z.parent;
                            rotateLeft(z);
                        }
                        z.parent.color = false;
                        gp.color = true;
                        rotateRight(gp);
                    }
                } else {
                    Node y = gp.left; 
                    if (y != null && y.color == true) {
                        z.parent.color = false;
                        y.color = false;
                        gp.color = true;
                        z = gp;
                    } else {
                        if (z == z.parent.left) {
                            z = z.parent;
                            rotateRight(z);
                        }
                        z.parent.color = false;
                        gp.color = true;
                        rotateLeft(gp);
                    }
                }
            }
            if (root != null) root.color = false; 
        }

        void searchPrint(String name) {
            System.out.print("=>raiz  ");
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
        RBT arvore = new RBT();

        while (true) {
            String entrada = sc.nextLine();
            if (entrada.equals("FIM")) break;

            if (mapCSV.containsKey(entrada)) {
                AVLGames game = new AVLGames();
                game.lerCSV(mapCSV.get(entrada));
                arvore.insert(game);
            }
        }

        while (sc.hasNextLine()) {
            String nome = sc.nextLine();
            if (nome.equals("FIM")) break;

            System.out.print(nome + ": ");
            arvore.searchPrint(nome);
        }

        sc.close();

        long fim = System.currentTimeMillis();
        double tempo = (fim - inicio) / 1000.0;

        FileWriter log = new FileWriter("845860_arvoreAlvinegra.txt");
        log.write("845860\t" + arvore.comparacoes + "\t" + tempo);
        log.close();
    }
}
