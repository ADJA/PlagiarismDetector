import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;


public class E {	
	BufferedReader reader;
    StringTokenizer tokenizer;
    PrintWriter out;

    long UNDEF = Long.MAX_VALUE;
	public void solve() throws IOException {				
		int N = nextInt();
        int K = nextInt();
        String[] SS = reader.readLine().split(" ");
        long[] A = new long[N];
        for (int i = 0; i < N; i++) {
            if (SS[i].equals("?")) {
                A[i] = UNDEF;
            } else {
                A[i] = Integer.parseInt(SS[i]);
            }
        }

        for (int i = 0; i < K; i++) {
            ArrayList<Long> ns = new ArrayList<Long>();
            for (int j = i; j < N; j+=K) {
                ns.add(A[j]);
            }
            long[] B = new long[ns.size()];
            for (int j = 0; j < ns.size(); j++) {
                B[j] = ns.get(j);
            }
            boolean result = build(B);
            if (!result) {
                out.println("Incorrect sequence");
                return;
            } else {
                int k = 0;
                for (int j = i; j < N; j+=K) {
                    A[j] = B[k++];
                }
            }
        }

        for (int i = 0; i < N; i++) {
            out.print(A[i] + " ");
        }
        out.println();
	}

    public boolean build(long[] A) {
        int N = A.length;
        int cur1 = 0;

//        System.out.println(Arrays.toString(A));
        while (cur1 < N) {
            while (cur1 < N && A[cur1] != UNDEF) {
                cur1++;
            }

            if (cur1 == N) break;

            int cur2 = cur1;
            while (cur2 < N-1 && A[cur2+1] == UNDEF) {
                cur2++;
            }

//            System.out.println(cur1 + ", " + cur2);

            int cnt = cur2 - cur1 + 1;
            long min = cur1 > 0? A[cur1-1]+1: Long.MIN_VALUE/3;
            long max = cur2 < N-1? A[cur2+1]-1: Long.MAX_VALUE/3;

            if (max - min + 1 < cnt) {
                return false;
            }

            if (min >= 0) {
                for (int j = cur1; j <= cur2; j++) {
                    A[j] = min + (j - cur1);
                }
            } else if (max <= 0) {
                for (int j = cur2; j >= cur1; j--) {
                    A[j] = max + (j - cur2);
                }
            } else {
                if (min >= -cnt/2) {
                    for (int j = cur1; j <= cur2; j++) {
                        A[j] = min + (j - cur1);
                    }
                } else if (max <= cnt/2) {
                    for (int j = cur2; j >= cur1; j--) {
                        A[j] = max + (j - cur2);
                    }
                } else {
                    for (int j = cur1; j <= cur2; j++) {
                        A[j] = -cnt/2 + (j - cur1);
                    }
                }
            }

            cur1 = cur2 + 1;
        }

        for (int i = 0; i < N-1; i++) {
            if (A[i] >= A[i+1]) return false;
        }

        return true;
    }
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new E().run();
	}
	
	public void run() {
        try {
            reader = new BufferedReader(new InputStreamReader(System.in));
            tokenizer = null;
            out = new PrintWriter(System.out);
            solve();
            reader.close();
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }

    String nextToken() throws IOException {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(reader.readLine());
        }
        return tokenizer.nextToken();
    }

}
