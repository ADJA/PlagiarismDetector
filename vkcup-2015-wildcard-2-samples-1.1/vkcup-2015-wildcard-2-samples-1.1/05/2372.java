import java.io.*;
import java.math.*;

public class SuperCleverReshenie {
    public static void main(String[] args) throws IOException {
        SuperCleverReshenie superCleverReshenie = new SuperCleverReshenie();
        superCleverReshenie.run();
    }

    private int NN;
    private int[] massive;
    private BigInteger[][][] dp;

    private void run() throws IOException {
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter output = new BufferedWriter(new OutputStreamWriter(System.out));

        String line = input.readLine();

        massive = new int[line.length()];
        for (int i = 0; i < line.length(); i++) {
            massive[i] = line.charAt(i) == 'A' ? 0 : 1;
        }

        dp = new BigInteger[line.length() + 1][4][4];

        for (int x = 0; x <= line.length(); x++) {
            for (int y = 0; y < 4; y++) {
                for (int rr = 0; rr < 4; rr++) {
                    dp[x][y][rr] = BigInteger.valueOf(-1);
                }
            }
        }

        BigInteger ans = BigInteger.ZERO;

        for (int maska = 0; maska < 4; maska++) {
            ans = ans.add(resh(2, maska, maska));
        }

        output.write(ans.toString());
        output.newLine();

        output.close();
        input.close();
    }

    private BigInteger resh(int index, int mskA, int mskB) {
        if (!dp[index][mskA][mskB].equals(BigInteger.valueOf(-1))) {
            return dp[index][mskA][mskB];
        }

        int flag1 = mskA & 1, flag2 = (mskA >> 1) & 1;
        int s1 = mskB & 1, s2 = (mskB >> 1) & 1;

        BigInteger result = BigInteger.ZERO;

        if (index == massive.length) {
            if (ok(s1, s2, flag1, massive[index - 2], massive[index - 1], massive[0])
                    && ok(s2, flag1, flag2, massive[index - 1], massive[0], massive[1])) {
                result = BigInteger.ONE;
            }
        } else {
            for (int cc = 0; cc < 2; cc++) {
                if (ok(s1, s2, cc, massive[index - 2], massive[index - 1], massive[index])) {
                    result = result.add(resh(index + 1, mskA, (cc << 1) | s2));
                }
            }
        }

        return dp[index][mskA][mskB] = result;
    }

    private boolean ok(int aa, int ab, int ac, int ba, int bb, int bc) {
        if (aa == 0 && ab == 1) {
            return ba == 1 && bb == 0;
        } else if (ab == 0 && ac == 1) {
            return bb == 1 && bc == 0;
        } else {
            return ab == bb;
        }
    }
}
