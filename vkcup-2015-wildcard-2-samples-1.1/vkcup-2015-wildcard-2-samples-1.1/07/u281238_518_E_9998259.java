import java.io.IOException;
import java.io.InputStreamReader;
import java.util.InputMismatchException;
import java.io.PrintStream;
import java.io.BufferedReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.Reader;
import java.io.Writer;
import java.util.StringTokenizer;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 * @author Nipuna Samarasekara
 */
public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        FastScanner in = new FastScanner(inputStream);
        FastPrinter out = new FastPrinter(outputStream);
        TaskE solver = new TaskE();
        solver.solve(1, in, out);
        out.close();
    }
}

class TaskE {
    // 689^*(
    public void solve(int testNumber, FastScanner in, FastPrinter out) {
    int n=in.nextInt(),k=in.nextInt();
    String s=in.readLine();
    s=in.readLine();
        StringTokenizer st= new StringTokenizer(s);
    int nnil= 1000000007;
    int[] a= new int[n];
        for (int i = 0; i < n; i++) {
          String ss=st.nextToken();
            if (ss.equals("?"))a[i]=nnil;
            else a[i]=Integer.parseInt(ss);
        }
        int ccc=1;
        for (int i = 0; i < n; i++) {
             if (a[i]==nnil){
                
                 int pos=i,ct=0;
                 while (pos<n&&a[pos]==nnil){
                  ct++;
                  pos+=k;
                 }
                if (pos>=n){
                 int cc=-ct/2;
                    if (i>=k)cc=Math.max(a[i-k]+1,cc);
                 pos=i;
                    for (int j = 0; j < ct; j++) {
                    a[pos]=cc;
                    pos+=k;
                    cc++;
                    }
                }
                else{
                 int res=a[pos];
                 int cc=Math.min(-ct/2,res-ct);
                    if (i>=k)cc=Math.max(a[i-k]+1,cc);
                    pos=i;
                    for (int j = 0; j < ct; j++) {
                        a[pos]=cc;
                        pos+=k;
                        cc++;
                    }
                }
             }
        }
        for (int i = 0; i+k < n; i++) {
            if (a[i]>=a[i+k])ccc=0;
        }
//        long ans=0;
//        for (int i = 0; i < n; i++) {
//            ans+=(long)Math.abs(a[i]);
//        }
        if (ccc==0) out.println("Incorrect sequence");
       else {
            for (int i = 0; i < n; i++) {
                out.print(a[i] + " ");
            }
            out.println();
        }
    }
}

class FastScanner extends BufferedReader {

    public FastScanner(InputStream is) {
        super(new InputStreamReader(is));
    }

    public int read() {
        try {
            int ret = super.read();
//            if (isEOF && ret < 0) {
//                throw new InputMismatchException();
//            }
//            isEOF = ret == -1;
            return ret;
        } catch (IOException e) {
            throw new InputMismatchException();
        }
    }

    static boolean isWhiteSpace(int c) {
        return c >= 0 && c <= 32;
    }

    public int nextInt() {
        int c = read();
        while (isWhiteSpace(c)) {
            c = read();
        }
        int sgn = 1;
        if (c == '-') {
            sgn = -1;
            c = read();
        }
        int ret = 0;
        while (c >= 0 && !isWhiteSpace(c)) {
            if (c < '0' || c > '9') {
                throw new NumberFormatException("digit expected " + (char) c
                        + " found");
            }
            ret = ret * 10 + c - '0';
            c = read();
        }
        return ret * sgn;
    }

    public String readLine() {
        try {
            return super.readLine();
        } catch (IOException e) {
            return null;
        }
    }

}

class FastPrinter extends PrintWriter {

    public FastPrinter(OutputStream out) {
        super(out);
    }


}