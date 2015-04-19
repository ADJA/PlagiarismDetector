import java.io.*;
import java.util.*;

public class E {
    public static void main(String[] args) throws Exception {

        new E().solve();
    }

    int n;
    long[] min, max;
    int[] next;
    void solve() throws IOException {
        FastScanner in = new FastScanner(System.in);

        String NG = "Incorrect sequence";
        n = in.nextInt();
        int k = in.nextInt();
        boolean[] isQ = new boolean[n];
        long[] a = new long[n];
        for (int i = 0; i < n; i++) {
            String s = in.next();
            if (s.charAt(0) == '?') {
                isQ[i] = true;
            } else {
                a[i] = Integer.parseInt(s);
            }
        }

        long INF = Long.MAX_VALUE / 2;
        min = new long[n];
        max = new long[n];
        Arrays.fill(min, -INF);
        Arrays.fill(max, INF);
        next = new int[n];
        Arrays.fill(next, -1);

        for (int si = 0; si + k < n; si++) {
            int ei = si + k;
            if (!isQ[si] && !isQ[ei]) {
                if (a[si] >= a[ei]) {
                    // NG!!!
                    System.out.println(NG);
                    return;
                }

            } else if (!isQ[ei]) {
                // si
                max[si] = a[ei] - 1;

            } else if (!isQ[si]) {
                // ei
                min[ei] = a[si] + 1;

            } else {
                // si, ei
                next[si] = ei;
                min[ei] = min[si] + 1;
            }
        }

        long[] ret = new long[n];
        boolean[] done = new boolean[n];
        for (int i = 0; i < n; i++) {
            if (!isQ[i]) {
                done[i] = true;
                ret[i] = a[i];
            } else if (done[i]) {
                //
            } else if (next[i] == -1) {
                if (min[i] > max[i]) {
                    System.out.println(NG);
                    return;
                }
                if (min[i] <= 0 && 0 <= max[i]) {
                    ret[i] = 0;
                } else if (max[i] < 0) {
                    ret[i] = max[i];
                } else {
                    ret[i] = min[i];
                }
            } else {
                if (!calc(i, ret, done)) {
                    System.out.println(NG);
                    return;
                }
            }
        }

        StringBuilder sb = new StringBuilder();
        sb.append(ret[0]);
        for (int i = 1; i < n; i++) {
            sb.append(" " + ret[i]);
        }
        System.out.println(sb);

    }

    ArrayList<Integer> ilist = new ArrayList<Integer>();
    boolean calc(int i, long[] ret, boolean[] done) {
        while (ilist.size() < n) {
            ilist.add(0);
        }
        int L = 0;
        ilist.set(L++, i);
        while (next[i] != -1) {
            i = next[i];
            ilist.set(L++, i);
        }
        int iLast = ilist.get(L - 1);
        int i2L = ilist.get(L / 2);
        if (min[iLast] > max[iLast]) {
            return false;
        }

        long up = 0L;
        if (min[i2L] < 0) {
            up = Math.min(-min[i2L], max[iLast] - min[iLast]);
        }

        for (int jj = 0; jj < L; jj++) {
            int idx = ilist.get(jj);
            ret[idx] = min[idx] + up;
            done[idx] = true;
        }
        return true;
    }
    class FastScanner {

        private InputStream _stream;
        private byte[] _buf = new byte[1024];
        private int _curChar;
        private int _numChars;
        private StringBuilder _sb = new StringBuilder();

        FastScanner(InputStream stream) {
            this._stream = stream;
        }

        public int read() {
            if (_numChars == -1) throw new InputMismatchException();
            if (_curChar >= _numChars) {
                _curChar = 0;
                try {
                    _numChars = _stream.read(_buf);
                } catch (IOException e) {
                    throw new InputMismatchException();
                }
                if (_numChars <= 0) return -1;
            }
            return _buf[_curChar++];
        }

        public String next() {
            int c = read();
            while (isWhitespace(c)) {
                c = read();
            }
            _sb.setLength(0);
            do {
                _sb.appendCodePoint(c);
                c = read();
            } while (!isWhitespace(c));
            return _sb.toString();
        }

        public int nextInt() {
            return (int) nextLong();
        }
        public long nextLong() {
            int c = read();
            while (isWhitespace(c)) {
                c = read();
            }
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = read();
            }
            long res = 0;
            do {
                if (c < '0' || c > '9') throw new InputMismatchException();
                res *= 10;
                res += c - '0';
                c = read();
            } while (!isWhitespace(c));
            return res * sgn;
        }

        public boolean isWhitespace(int c) {
            return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
        }
    }

}

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
