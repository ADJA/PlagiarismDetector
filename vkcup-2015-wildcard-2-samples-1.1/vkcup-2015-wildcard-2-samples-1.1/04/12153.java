import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Solution {
    static int[][] r;
    static int N;
    static boolean[] positions;
    static ArrayList<Integer>[] g;

    static void p(Object... o) {
        System.out.println(Arrays.deepToString(o));
    }

    ;

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        N = in.nextInt();
        g = new ArrayList[N];
        for (int i = 0; i < N; i++)
            g[i] = new ArrayList<>();
        
        for (int i = 0; i < N - 1; i++) {
            int a = in.nextInt() - 1;
            int b = in.nextInt() - 1;
            g[a].add(b);
            g[b].add(a);
        }

        positions = new boolean[N];
        r = new int[N + 1][N + 1];
        size(0, -1);

        int tmp = 0;
        for (int i = 1; i < N - 1; i++)
            if (positions[i])
                tmp++;
        System.out.println(tmp);
        for (int i = 1; i < N - 1; i++) {
            if (positions[i]) {
                System.out.println(i + " " + (N - i - 1));
            }
        }
    }

    private static int size(int at, int p) {
        ArrayList<Integer> sizes = new ArrayList<>();

        for (int e : g[at]) {
            if (e == p)
                continue;
            sizes.add(size(e, at));
        }
        
        int total = 0;
        for (int s : sizes)
            total += s;
        sizes.add(N - total - 1);

        for (int i = 0; i <= sizes.size(); i++) {
            Arrays.fill(r[i], 0);
        }
        r[0][0] = 1;
        for (int i = 0; i < sizes.size(); i++) {
            for (int j = 0; j <= N; j++) {
                if (r[i][j] == 1) {
                    r[i + 1][j] = 1;
                    r[i + 1][j + sizes.get(i)] = 1;
                }
            }
        }
        for (int j = 0; j <= N; j++)
            if (r[sizes.size()][j] == 1)
                positions[j] = true;
        
        return total + 1;
    }
}
