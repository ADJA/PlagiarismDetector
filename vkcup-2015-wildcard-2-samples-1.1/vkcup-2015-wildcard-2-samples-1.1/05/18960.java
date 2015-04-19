import java.io.*;
import java.math.BigInteger;
import java.util.StringTokenizer;

/**
 * Author: homo_sapiens
 * Date: 7/14/12
 * Time: 11:54 AM
 */
public class Solution {
    public static void main(String[] args) throws IOException {
        Solution solution = new Solution();
        solution.run();
    }

    private int n;
    private int[] a;
    private BigInteger[][][] z;

    private void run() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out));

        String s = in.readLine();

        a = new int[s.length()];
        for (int i = 0; i < s.length(); i++) {
            a[i] = s.charAt(i) == 'A' ? 0 : 1;
        }

        z = new BigInteger[s.length() + 1][4][4];

        for (int i = 0; i <= s.length(); i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    z[i][j][k] = BigInteger.valueOf(-1);
                }
            }
        }

        BigInteger result = BigInteger.ZERO;

        for (int mask = 0; mask < 4; mask++) {
            result = result.add(solve(2, mask, mask));
        }

        out.write(result.toString());
        out.newLine();

        out.close();
        in.close();
    }

    private BigInteger solve(int idx, int mask1, int mask2) {
        if (!z[idx][mask1][mask2].equals(BigInteger.valueOf(-1))) {
            return z[idx][mask1][mask2];
        }

        int f1 = mask1 & 1, f2 = (mask1 >> 1) & 1;
        int s1 = mask2 & 1, s2 = (mask2 >> 1) & 1;

        BigInteger result = BigInteger.ZERO;

        if (idx == a.length) {
            if (correct(s1, s2, f1, a[idx - 2], a[idx - 1], a[0])
                    && correct(s2, f1, f2, a[idx - 1], a[0], a[1])) {
                result = BigInteger.ONE;
            }
        } else {
            for (int cur = 0; cur < 2; cur++) {
                if (correct(s1, s2, cur, a[idx - 2], a[idx - 1], a[idx])) {
                    result = result.add(solve(idx + 1, mask1, (cur << 1) | s2));
                }
            }
        }

        return z[idx][mask1][mask2] = result;
    }

    private boolean correct(int a1, int a2, int a3, int b1, int b2, int b3) {
        if (a1 == 0 && a2 == 1) {
            return b1 == 1 && b2 == 0;
        } else if (a2 == 0 && a3 == 1) {
            return b2 == 1 && b3 == 0;
        } else {
            return a2 == b2;
        }
    }
}
