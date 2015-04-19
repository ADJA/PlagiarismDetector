
import sun.security.util.BigInt;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.BigInteger;

public class Solution {
    public static void main(String[] args) throws Exception{
        new Solution().run();
    }

    BigInteger[][] z = new BigInteger[2][110];
    String s;

    BigInteger solveA(int prev, int idx){
        if(idx == s.length())
            return BigInteger.ONE;

        if(z[prev][idx] == null){
            BigInteger ans = BigInteger.ZERO;

            //put A
            {
                int cidx = idx;
                char cput = 'A';
                int cprev = prev;

                while(true){
                    if(cput == 'A'){
                        if(s.charAt(cidx) == 'A'){
                            if(cidx == s.length() - 1){
                                ans = ans.add(BigInteger.ONE);
                                break;
                            }else{
                                cidx++;
                                cput = 'A';
                                cprev = 0;
                            }
                        }else{
                            if(cidx == s.length() - 1){
                                break;
                            }else{
                                cidx++;
                                cput = 'B';
                                cprev = 0;
                            }
                        }
                    }else{
                        if(s.charAt(cidx) == 'B'){
                            if(cprev == 1){
                                ans = ans.add(solveA(1, cidx + 1));
                            }
                        }else{
                            if(cprev == 0)
                                ans = ans.add(solveA(1, cidx + 1));
                        }
                        break;
                    }
                }
            }

            if(idx != 0){
                if(s.charAt(idx) == 'B'){
                    if(prev == 1)
                        ans = ans.add(solveA(1, idx + 1));
                }else{
                    if(prev == 0)
                        ans = ans.add(solveA(1, idx + 1));
                }
            }

            z[prev][idx] = ans;
        }

        return z[prev][idx];
    }

    char inv(char c){
        if(c == 'A')
            return 'B';
        else
            return 'A';
    }

    void run() throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        s = br.readLine();

        BigInteger ans = solveA(0, 0);
        StringBuilder sb = new StringBuilder("");
        sb.append(inv(s.charAt(0)));
        for(int i = s.length() - 1; i >= 1; --i)
            sb.append(inv(s.charAt(i)));

        s = sb.toString();

        //System.err.println(s);

        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < s.length(); ++j)
                z[i][j] = null;

        System.err.println(ans);
        ans = ans.add(solveA(0, 0));
        System.err.println(ans);

        System.out.println(ans);
    }
}
