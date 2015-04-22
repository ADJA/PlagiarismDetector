import java.io.*;
import java.util.*;

public class E {
    private InputStream is;
    private PrintWriter out;

    private void run() throws Exception {
        is = System.in;
        out = new PrintWriter(System.out);

        solve();
        out.flush();
    }

    public static void main(String[] args) throws Exception {
        new E().run();
    }

    private void solve() {
        int n = nextInt();
        long[] x = new long[n + 1];
        for (int i = 1; i <= n; i++) x[i] = nextInt();
        int m = nextInt();
        int[] f = new int[n + 1];
        for (int i = 0; i < m; i++) f[nextInt()]++;

        if (f[n] != f[1] + 1) {
            if (f[1] != f[n] + 1) {
                if (f[1] == f[n]) {
                    long cy = f[n];
                    f[1] -= cy;
                    f[n] -= cy;
                    for (int i = 2; i <= n - 1; i++) {
                        f[i] -= 2 * cy;
                    }
        
                    boolean flag = false;
                    long ret = cy * 2L * (x[n] - x[1]);
                    for (int i = 1; i <= n - 1; i++) {
                        if (f[i] < f[i + 1]) {
                            ret -= x[i + 1];
                            flag = true;
                        } else if (f[i] > f[i + 1]) {
                            ret += x[i];
                            flag = true;
                        }
                    }
                    if (flag) {
                        out.println(ret);
                    } else {
                        long del = x[2] - x[1];
                        for (int i = 1; i <= n - 1; i++) {
                            if (del != x[i + 1] - x[i]) {
                                out.println(-1);
                                return;
                            }
                        }
                        out.println(ret - del);
                    }
                }
            } else {
                long cy = f[n];
                f[1] -= cy;
                f[n] -= cy;
                for (int i = 2; i <= n - 1; i++) {
                    f[i] -= 2 * cy;
                }
    
                long ret = cy * 2L * (x[n] - x[1]);
                for (int i = 1; i <= n - 1; i++) {
                    if (f[i + 1] == 0 && f[i] >= 1) {
                        ret += x[i] - x[1];
                    }
                    if (f[i + 1] <= 1 && f[i] == 2) {
                        ret += x[i] - x[1];
                    }
                }
                out.println(ret);
            }
        } else {
            long cy = f[1];
            f[1] -= cy;
            f[n] -= cy;
            for (int i = 2; i <= n - 1; i++) {
                f[i] -= 2 * cy;
            }

            long ret = cy * 2L * (x[n] - x[1]);
            for (int i = 1; i <= n - 1; i++) {
                if (f[i] == 0 && f[i + 1] >= 1) {
                    ret += x[n] - x[i + 1];
                }
                if (f[i] <= 1 && f[i + 1] == 2) {
                    ret += x[n] - x[i + 1];
                }
            }
            out.println(ret);
        }
    }

    private byte[] inbuf = new byte[1024];
    private int lenbuf = 0, ptrbuf = 0;

    private int readByte() {
        if (lenbuf == -1) throw new InputMismatchException();
        if (ptrbuf >= lenbuf) {
            ptrbuf = 0;
            try {
                lenbuf = is.read(inbuf);
            } catch (IOException e) {
                throw new InputMismatchException();
            }
            if (lenbuf <= 0) return -1;
        }
        return inbuf[ptrbuf++];
    }

    private boolean isSpaceChar(int c) {
        return !(c >= 33 && c <= 126);
    }

    private int skip() {
        int b;
        while ((b = readByte()) != -1 && isSpaceChar(b)) {
        };
        return b;
    }

    private int nextInt() {
        int num = 0, b;
        boolean minus = false;
        while ((b = readByte()) != -1 && !((b >= '0' && b <= '9') || b == '-'))  {
            
        }
        if (b == '-') {
            minus = true;
            b = readByte();
        }

        while (true) {
            if (b >= '0' && b <= '9') {
                num = num * 10 + (b - '0');
            } else {
                return minus ? -num : num;
            }
            b = readByte();
        }
    }
}
