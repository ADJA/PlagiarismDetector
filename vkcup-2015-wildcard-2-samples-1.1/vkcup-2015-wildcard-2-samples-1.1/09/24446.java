import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Scanner;

public class F {
    private Scanner scanner;
    private PrintWriter out;

    void solve() {
        int n = scanner.nextInt(), m = scanner.nextInt();
        int[] row = new int[n];
        for (int i = 0; i < n; i++) {
            row[i] = scanner.nextInt();
        }
        int[] col = new int[m];
        for (int i = 0; i < m; i++) {
            col[i] = scanner.nextInt();
        }
        char[][] map = new char[n][m];
        for (int i = 0; i < n; i++) {
            Arrays.fill(map[i], '?');
        }
        rec(0, 0, 0, new int[n], map, row, col);

        check(map, row, col);

        for (int i = 0; i < n; i++) {
            out.println(new String(map[i]));
        }
//		tr(ved);
    }

    void check(char[][] map, int[] row, int[] col) {
        int n = map.length, m = map[0].length;

        for (int i = 0; i < n; i++) {
            int lrow = 0;
            for (int j = 0; j < m; j++) {
                if (map[i][j] == '*' && (j == 0 || map[i][j - 1] == '.')) lrow++;
            }
            if (lrow != row[i]) throw new RuntimeException();
        }
        for (int i = 0; i < m; i++) {
            int lcol = 0;
            for (int j = 0; j < n; j++) {
                if (map[j][i] == '*' && (j == 0 || map[j - 1][i] == '.')) lcol++;
            }
            if (lcol != col[i]) throw new RuntimeException();
        }
    }

    boolean rec(int r, int c, int rdis, int[] rc, char[][] map, int[] row, int[] col) {
        if (c == map[0].length) {
            for (int i = 0; i < map.length; i++) {
                if (rc[i] != row[i]) {
                    return false;
                }
            }
            return true;
        }
        if (r == map.length) {
            if (rdis != col[c]) return false;
            return rec(0, c + 1, 0, rc, map, row, col);
        }

//		ved++;

        int n = map.length, m = map[0].length;

        {
            map[r][c] = '.';
            boolean go = true;
            if ((n - 1 - r + 1) / 2 + rdis < col[c]) {
                go = false;
            }

            if (go) {
                int vir = rc[r];
                int prev = 0, xx = 0;
                for (int i = c + 1; i < m; i++) {
                    if (col[i] == 0) {
                        xx = 0;
                    } else if (col[i] == 3) {
                        if ((r & 1) == 0) {
                            xx = 1;
                        } else {
                            xx = 0;
                        }
                    } else {
                        xx = prev ^ 1;
                    }
                    if (prev == 0 && xx == 1) vir++;
                    prev = xx;
                }
                if (vir < row[r]) {
                    go = false;
                }
            }
            if (go) {
                int vir = rc[r];
                int prev = 0, xx = 0;
                for (int i = c + 1; i < m; i++) {
                    if (col[i] == 0) {
                        xx = 0;
                    } else if (col[i] == 3) {
                        if ((r & 1) == 0) {
                            xx = 1;
                        } else {
                            xx = 0;
                        }
                    } else {
                        xx = prev;
                    }
                    if (prev == 0 && xx == 1) vir++;
                    prev = xx;
                }
                if (vir > row[r]) {
                    go = false;
                }
            }
//			if((m-1-c+1)/2 + rc[r] < row[r]){
//				go = false;
//			}
            if (go && rec(r + 1, c, rdis, rc, map, row, col)) return true;
        }

        {
            map[r][c] = '*';
            boolean go = true;
            int nrdis = rdis;
            if (r == 0 || map[r - 1][c] == '.') {
                if (rdis + 1 > col[c]) {
                    go = false;
                } else {
                    nrdis++;
                }
            }
            boolean pl = false;
            if (c == 0 || map[r][c - 1] == '.') {
                if (rc[r] + 1 > row[r]) {
                    go = false;
                } else {
                    rc[r]++;
                    pl = true;
                }
            }
            if ((n - 1 - r) / 2 + nrdis < col[c]) {
                go = false;
            }

            if (go) {
                int vir = rc[r];
                int prev = 1, xx = 0;
                for (int i = c + 1; i < m; i++) {
                    if (col[i] == 0) {
                        xx = 0;
                    } else if (col[i] == 3) {
                        if ((r & 1) == 0) {
                            xx = 1;
                        } else {
                            xx = 0;
                        }
                    } else {
                        xx = prev ^ 1;
                    }
                    if (prev == 0 && xx == 1) vir++;
                    prev = xx;
                }
                if (vir < row[r]) {
                    go = false;
                }
            }
            if (go) {
                int vir = rc[r];
                int prev = 1, xx = 0;
                for (int i = c + 1; i < m; i++) {
                    if (col[i] == 0) {
                        xx = 0;
                    } else if (col[i] == 3) {
                        if ((r & 1) == 0) {
                            xx = 1;
                        } else {
                            xx = 0;
                        }
                    } else {
                        xx = prev;
                    }
                    if (prev == 0 && xx == 1) vir++;
                    prev = xx;
                }
                if (vir > row[r]) {
                    go = false;
                }
            }
//			if((m-1-c)/2 + rc[r] < row[r]){
//				go = false;
//			}
            if (go && rec(r + 1, c, nrdis, rc, map, row, col)) return true;
            if (pl) {
                rc[r]--;
            }
        }


        map[r][c] = '?';
        return false;
    }

    void run() throws Exception {
        scanner = new Scanner(System.in);
        out = new PrintWriter(System.out);

        solve();
        out.flush();
    }

    public static void main(String[] args) throws Exception {
        new F().run();
    }
}
