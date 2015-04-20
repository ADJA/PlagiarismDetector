import java.io.*;
import java.util.StringTokenizer;

/**
 * Main entry point to app
 */
public class Main implements Runnable {


    /* Main method */
    public void solve () throws IOException {
        out.println(next());
    }

    BufferedReader bf;
    StringTokenizer st;
    PrintWriter out;

    public String next() throws IOException {
        while (st == null || !st.hasMoreTokens())
            st = new StringTokenizer(bf.readLine());
        return st.nextToken();
    }


    public Main() {

    }

    @Override
    public void run() {
        try {
            bf = new BufferedReader(new FileReader("input.txt"));
            out = new PrintWriter(new FileWriter("output.txt"));
            solve();
            bf.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(-1);
        } finally {

        }
    }
    public static void main(String args[]) {
        Main task = new Main();
        task.run();

    }
}
