import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;

class Celula {
    public int elemento;
    public Celula inf, sup, esq, dir;

    public Celula() {
        this(0);
    }

    public Celula(int elemento) {
        this.elemento = elemento;
        this.inf = null;
        this.sup = null;
        this.esq = null;
        this.dir = null;
    }
}

class Matriz {
    private int linhas;
    private int colunas;
    private Celula inicio;

    public Matriz(int linhas, int colunas) {
        this.linhas = linhas;
        this.colunas = colunas;

        if (linhas > 0 && colunas > 0) {
            inicio = new Celula();
            Celula atual = inicio;
            for (int j = 1; j < colunas; j++) {
                Celula nova = new Celula();
                atual.dir = nova;
                nova.esq = atual;
                atual = nova;
            }

            Celula linhaAnterior = inicio;
            for (int i = 1; i < linhas; i++) {
                Celula novaLinha = new Celula();
                linhaAnterior.inf = novaLinha;
                novaLinha.sup = linhaAnterior;

                Celula celulaCima = linhaAnterior;
                Celula celulaAtual = novaLinha;

                for (int j = 1; j < colunas; j++) {
                    Celula nova = new Celula();

                    celulaAtual.dir = nova;
                    nova.esq = celulaAtual;

                    celulaCima = celulaCima.dir;
                    celulaCima.inf = nova;
                    nova.sup = celulaCima;

                    celulaAtual = nova;
                }
                linhaAnterior = novaLinha;
            }
        }
    }

    public void ler(LeitorRapido sc) {
        for (Celula i = inicio; i != null; i = i.inf) {
            for (Celula j = i; j != null; j = j.dir) {
                j.elemento = sc.nextInt();
            }
        }
    }

    public Matriz somar(Matriz m) {
        Matriz resultado = new Matriz(this.linhas, this.colunas);
        Celula aLinha = this.inicio;
        Celula bLinha = m.inicio;
        Celula resLinha = resultado.inicio;

        while (aLinha != null && bLinha != null) {
            Celula a = aLinha, b = bLinha, r = resLinha;
            while (a != null && b != null) {
                r.elemento = a.elemento + b.elemento;
                a = a.dir;
                b = b.dir;
                r = r.dir;
            }
            aLinha = aLinha.inf;
            bLinha = bLinha.inf;
            resLinha = resLinha.inf;
        }
        return resultado;
    }

    public Matriz multiplicar(Matriz m) {
        Matriz resultado = new Matriz(this.linhas, m.colunas);
        Celula aLinha = this.inicio;
        Celula resLinha = resultado.inicio;

        while (aLinha != null) {
            Celula bColuna = m.inicio;
            Celula r = resLinha;

            while (bColuna != null) {
                int soma = 0;
                Celula a = aLinha;
                Celula b = bColuna;

                while (a != null && b != null) {
                    soma += a.elemento * b.elemento;
                    a = a.dir;
                    b = b.inf;
                }
                r.elemento = soma;

                bColuna = bColuna.dir;
                r = r.dir;
            }
            aLinha = aLinha.inf;
            resLinha = resLinha.inf;
        }
        return resultado;
    }

    public void mostrarDiagonalPrincipal() {
        if (inicio == null) {
            System.out.println();
            return;
        }
        StringBuilder sb = new StringBuilder();
        Celula atual = inicio;
        boolean primeiro = true;

        while (atual != null) {
            if (!primeiro) sb.append(" ");
            sb.append(atual.elemento);
            primeiro = false;

            // Avança diagonal: desce uma linha e vai para direita uma coluna
            Celula prox = atual.inf;
            if (prox != null) prox = prox.dir;
            atual = prox;
        }
        System.out.println(sb.toString());
    }

    public void mostrarDiagonalSecundaria() {
        if (inicio == null) {
            System.out.println();
            return;
        }
        StringBuilder sb = new StringBuilder();

        // Começa no canto superior direito
        Celula atual = inicio;
        while (atual.dir != null) atual = atual.dir;

        boolean primeiro = true;
        while (atual != null) {
            if (!primeiro) sb.append(" ");
            sb.append(atual.elemento);
            primeiro = false;

            // Avança diagonal secundária: desce uma linha e vai para esquerda uma coluna
            Celula prox = atual.inf;
            if (prox != null) prox = prox.esq;
            atual = prox;
        }
        System.out.println(sb.toString());
    }

    public void mostrar() {
        if (inicio == null) return;
        for (Celula i = inicio; i != null; i = i.inf) {
            StringBuilder sb = new StringBuilder();
            boolean primeiro = true;
            for (Celula j = i; j != null; j = j.dir) {
                if (!primeiro) sb.append(" ");
                sb.append(j.elemento);
                primeiro = false;
            }
            System.out.println(sb.toString());
        }
    }
}

class LeitorRapido {
    BufferedReader br;
    StringTokenizer st;

    public LeitorRapido() {
        br = new BufferedReader(new InputStreamReader(System.in));
    }

    String next() {
        while (st == null || !st.hasMoreElements()) {
            try {
                String line = br.readLine();
                if (line == null) return null;
                st = new StringTokenizer(line);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return st.nextToken();
    }

    Integer nextIntOrNull() {
        String n = next();
        if (n == null) return null;
        return Integer.parseInt(n);
    }

    int nextInt() {
        return Integer.parseInt(next());
    }
}

public class RestaurantesMatriz {
    public static void main(String[] args) {
        LeitorRapido sc = new LeitorRapido();

        Integer casos = sc.nextIntOrNull();
        if (casos == null) return;

        for (int c = 0; c < casos; c++) {
            // Lê dimensões e elementos da primeira matriz
            int l1 = sc.nextInt();
            int c1 = sc.nextInt();
            Matriz m1 = new Matriz(l1, c1);
            m1.ler(sc);

            // Lê dimensões e elementos da segunda matriz (podem ser diferentes!)
            int l2 = sc.nextInt();
            int c2 = sc.nextInt();
            Matriz m2 = new Matriz(l2, c2);
            m2.ler(sc);

            // Diagonal principal da primeira, diagonal secundária da segunda
            m1.mostrarDiagonalPrincipal();
            m2.mostrarDiagonalSecundaria();

            // Soma e multiplicação
            m1.somar(m2).mostrar();
            m1.multiplicar(m2).mostrar();
        }
    }
}