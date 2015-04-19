import java.io.BufferedReader;
import java.io.FileReader;
import java.io.*;
import java.io.IOException;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.StringTokenizer;

/**
 * Created with IntelliJ IDEA.
 * User: contest
 * Date: 7/14/12
 * Time: 11:36 AM
 * To change this template use File | Settings | File Templates.
 */
public class problemC {
    final String prefix = "c";
    final String problem_input = prefix + ".in";
    final String problem_output = prefix + ".out";
    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;
    String s;
    BigInteger dp[][];
    void load() throws IOException
    {
        s = nextToken();
    }
    int first;

    BigInteger f(int i, int m)
    {
        if (i == s.length())
        {
            if (m == first)
                return BigInteger.ONE;
            else return BigInteger.ZERO;
        }
        if (dp[i][m] != null) return dp[i][m];
        dp[i][m] = BigInteger.ZERO;
        if (s.charAt(i) == 'A')
        {
            if ((m & 1) == 0) // _A
            {
                dp[i][m] = dp[i][m].add(f(i + 1, ((m << 1) | 0) & 3));
            }
            else //_B
            {
                if ((m & 2) == 0)                
                    for (int j = 0; j < 2; j++)
                        dp[i][m] = dp[i][m].add(f(i + 1, ((m << 1) | j) & 3));
            }
        }
        else if (s.charAt(i) == 'B')
        {
            if ((m & 1) == 1) // _B
            {                    //BB
                if ((m & 2) > 0) // B 
                {
                    for (int j = 0; j < 2; j++)
                        dp[i][m] = dp[i][m].add(f(i + 1, ((m << 1) | j) & 3));
                }
            }
            else // _A
            {
                dp[i][m] = f(i + 1, ((m << 1) | 1) & 3);
            }
        }
        return dp[i][m];
    }
    void solve()
    {
        dp = new BigInteger[s.length() + 2][4];
        BigInteger res = BigInteger.ZERO;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < s.length() + 1; j++)
                dp[j][0] = dp[j][1] = dp[j][2] = dp[j][3] = null;
            first = i;
            res = res.add(f(0, i));
        } 
        out.println(res);
    }
    void run()
    {
        try
        {
            br = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(new OutputStreamWriter(System.out));
            load();
            solve();
            out.close();
        }
        catch(Exception e)
        {
            e.printStackTrace();
            System.exit(42);
        }
    }
    public String nextToken() throws IOException {
        while (st == null || !st.hasMoreTokens())
        {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }
    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }
    public long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }
    public double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }
    public void readIntArray(int []a, int n) throws IOException 
    {
        for (int i = 0; i < n; i++)
            a[i] = nextInt();
    }
    public static void main(String args[])
    {
        new problemC().run();
    }
}
