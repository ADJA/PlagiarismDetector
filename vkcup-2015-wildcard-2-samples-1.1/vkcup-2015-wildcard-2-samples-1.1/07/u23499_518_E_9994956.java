import java.io.*;
import java.util.StringTokenizer;

public class A {

    final boolean ONLINE_JUDGE = System.getProperty("ONLINE_JUDGE") != null;
    BufferedReader in;
    PrintWriter out;
    StringTokenizer tok = new StringTokenizer("");

	void solve() throws IOException {
        int n = readInt();
        int k = readInt();

        long[] a = new long[n + k];
        boolean[] u = new boolean[n + k];
        for(int i = 0; i < n; i++) {
            String x = readString();
            if(x.equals("?")) {
                u[i] = false;
            } else {
                u[i] = true;
                a[i] = Integer.parseInt(x);
            }
        }
        for(int i = n; i < n + k; i++) {
            u[i] = true;
            a[i] = 1000 * 1000 * 1000 * 2;
        }
        for(int i = 0; i < k; i++) {
            int start = -1;
            int cnt = 0;
            long prev = -1000 * 1000 * 1000 * 2;
            for(int j = i; j < n + k; j+= k) {
                if(u[j]) {
                    if(a[j] - prev <= cnt) {
                        out.println("Incorrect sequence");
                        return;
                    }
                    if(start != -1) {
                        if(prev < 0 && a[j] < 0) {
                            int curIndex = j - k;
                            long cur = a[j]-1;
                            while (cnt > 0) {
                                a[curIndex] = cur--;
                                curIndex -= k;
                                cnt--;
                            }
                        } else if(prev < 0 && a[j] >= 0) {
                            int curIndex = j - k;
                            long cur;
                            if(cnt % 2 != 0) {
                                int opt = cnt / 2;
                                if(prev + cnt <= opt && opt <= a[j]-1) {
                                    cur = opt;
                                } else if(opt < prev + cnt) {
                                    cur = prev + cnt;
                                } else {
                                    cur = a[j] - 1;
                                }
                            } else {
                                int opt = cnt / 2;
                                int opt2 = cnt/2-1;
                                if(prev + cnt <= opt && opt <= a[j]-1) {
                                    cur = opt;
                                } else if(prev + cnt <= opt2 && opt2 <= a[j]-1) {
                                    cur = opt2;
                                }else if(opt < prev + cnt) {
                                    cur = prev + cnt;
                                } else {
                                    cur = a[j] - 1;
                                }
                            }
                            while (cnt > 0) {
                                a[curIndex] = cur--;
                                curIndex -= k;
                                cnt--;
                            }
                        } else {
                            int curIndex = j - k;
                            long cur = prev + cnt;
                            while (cnt > 0) {
                                a[curIndex] = cur--;
                                curIndex -= k;
                                cnt--;
                            }
                        }
                    }
                    start = -1;
                    cnt = 0;
                    prev = a[j];
                } else {
                    if(start == -1) {
                        start = j;
                        cnt = 0;
                    }
                    cnt++;
                }
            }
        }
        for(int i = 0; i < n; i++) {
            out.print(a[i] + " ");
        }
    }

    private int getP() throws IOException {
        String s = readString();
        if(s.charAt(0) == '1') return 100;
        return Integer.parseInt(s.substring(2));
    }


    int index(char c) {
        if('a' <= c && c <= 'z') {
            return c - 'a';
        }
        return c - 'A' + 26;
    }

    void init() throws FileNotFoundException {
        if (ONLINE_JUDGE) {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
        } else {
            in = new BufferedReader(new FileReader("input.txt"));
            out = new PrintWriter("output.txt");
        }
    }

    String readString() throws IOException {
        while (!tok.hasMoreTokens()) {
            tok = new StringTokenizer(in.readLine());
        }
        return tok.nextToken();
    }

    int readInt() throws IOException {
        return Integer.parseInt(readString());
    }

    long readLong() throws IOException {
        return Long.parseLong(readString());
    }

    double readDouble() throws IOException {
        return Double.parseDouble(readString());
    }

    int[] readArr(int n) throws IOException {
        int[] res = new int[n];
        for (int i = 0; i < n; i++) {
            res[i] = readInt();
        }
        return res;
    }

    long[] readArrL(int n) throws IOException {
        long[] res = new long[n];
        for (int i = 0; i < n; i++) {
            res[i] = readLong();
        }
        return res;
    }

    public static void main(String[] args) {
        new A().run();
    }

    public void run() {
        try {
            long t1 = System.currentTimeMillis();
            init();
            solve();
            out.close();
            long t2 = System.currentTimeMillis();
            System.err.println("Time = " + (t2 - t1));
        } catch (Exception e) {
            e.printStackTrace(System.err);
            System.exit(-1);
        }
    }
}