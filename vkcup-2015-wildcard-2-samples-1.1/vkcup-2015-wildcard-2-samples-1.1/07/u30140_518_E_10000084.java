import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;


public class E {

    static StringTokenizer st;
    static BufferedReader br;
    static PrintWriter pw;
    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        int n = nextInt();
        int k = nextInt();
        int[]a = new int[n+1];
        int INF = (int) 2e9;
        Arrays.fill(a, INF);
        for (int i = 1; i <= n; i++) {
            String s = next();
            if (!s.equals("?"))
                a[i] = Integer.parseInt(s);
        }
        int[]b = new int[n+2];
        int max = (int) (1e9+1e8);
        for (int i = 1; i <= k; i++) {
            int size = 0;
            for (int j = i; j <= n; j += k) {
                b[++size] = a[j];
            }
            b[0] = -max;
            b[size+1] = max;
            int last = 0;
            for (int j = 1; j <= size+1; j++) {
                if (b[j] != INF) {
                    if (b[last] >= 0 && b[j] >= 0) {
                        for (int j2 = last+1; j2 <= j-1; j2++) {
                            b[j2] = b[j2-1]+1;
                        }
                        if (b[j-1] >= b[j]) {
                            System.out.println("Incorrect sequence");
                            return;
                        }
                    }
                    else if (b[last] <= 0 && b[j] <= 0) {
                        for (int j2 = j-1; j2 > last; j2--) {
                            b[j2] = b[j2+1]-1;
                        }
                        if (b[last] >= b[last+1]) {
                            System.out.println("Incorrect sequence");
                            return;
                        }
                    }
                    else {
                        int need = j-last-1;
                        if (need > 0) {
                            need--;
                        }
                        int left = -1, right = 1;
                        for (int j2 = 1; j2 <= need; j2++) {
                            if (Math.abs(left) < Math.abs(right)) {
                                if (left > b[last])
                                    left--;
                                else
                                    right++;
                            }
                            else {
                                if (right < b[j])
                                    right++;
                                else
                                    left--;
                            }
                        }
                        left++;
                        for (int j2 = last+1; j2 < j; j2++) {
                            b[j2] = left++;
                        }
                        if (b[last] >= b[last+1] || b[j-1] >= b[j]) {
                            System.out.println("Incorrect sequence");
                            return;
                        }
                    }
                    last = j;
                }
            }
            size = 0;
            for (int j = i; j <= n; j += k) {
                a[j] = b[++size];
            }
        }
        for (int i = 1; i <= n; i++) {
            pw.print(a[i]+" ");
        }
        pw.close();
    }
    private static int nextInt() throws IOException {
        return Integer.parseInt(next());
    }
    private static long nextLong() throws IOException {
        return Long.parseLong(next());
    }
    private static double nextDouble() throws IOException {
        return Double.parseDouble(next());
    }
    private static String next() throws IOException {
        while (st==null || !st.hasMoreTokens())
            st = new StringTokenizer(br.readLine());
        return st.nextToken();
    }
}
