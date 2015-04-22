import java.io.*;
import java.util.*;

public class EMain {
    String noResultMessage = "NoResult";
    Parser in = new Parser();
    PrintWriter out;

    int n = in.nextInteger();
    int q = in.nextInteger();
    int[] as = in.nextIntegers(n);
    long[] bs = in.nextLongs(q);

    static class Level{
        final int index;
        final long b;

        Level(int index, long b) {
            this.index = index;
            this.b = b;
        }
    }

    public void solve() {
        Level[] levels = new Level[q];
        for(int i = 0; i < q; ++i){
            levels[i] = new Level(i, bs[i]);
        }
        int[] counts = new int[n];
        for(Level level : levels){
            long b = level.b;
            long sum = 0;
            int curr;
            for(curr = 0; curr < n; ++curr) {
                if (sum + as[curr] > b) break;
                sum += as[curr];
            }
            if(curr == n){
                out.println(1);
                continue;
            }
            int minPos = 0;
            int minCount = curr;

            counts[0] = curr;
            for(int i = 1; i < n; ++i){
                sum -= as[i - 1];
                while(sum + as[curr%n] <= b){
                    sum += as[curr%n];
                    ++curr;
                }
                if(curr - i < minCount){
                    minCount = curr - i;
                    minPos = i;
                }
                counts[i] = curr%n;
            }
            int min = Integer.MAX_VALUE;
            for(int i = 0; i <= minCount; ++i){
                int start = minPos + i;
                int count = 0;
                int pos = start;
                while(pos - start < n){
                    int next = counts[pos%n];
                    pos = next < pos ? next + n : next;
                    ++count;
                }
                min = Math.min(min, count);
            }
            out.println(min);
        }
    }

    static public class Parser{
        Scanner scanner;

        public Parser() {
            scanner = new Scanner(System.in).useLocale(Locale.ENGLISH);
        }

        public Parser(String str) {
            scanner = new Scanner(str).useLocale(Locale.ENGLISH);
        }

        long nextLong(){
            return scanner.nextLong();
        }

        int nextInteger(){
            return scanner.nextInt();
        }

        double nextDouble(){
            return scanner.nextDouble();
        }

        String nextLine(){
            return scanner.nextLine();
        }

        String next(){
            return scanner.next();
        }

        int[] nextIntegers(int count){
            int[] result = new int[count];
            for(int i = 0; i < count; ++i){
                result[i] = nextInteger();
            }
            return result;
        }

        long[] nextLongs(int count){
            long[] result = new long[count];
            for(int i = 0; i < count; ++i){
                result[i] = nextLong();
            }
            return result;
        }

        int[][] nextIntegers(int fields, int count){
            int[][] result = new int[fields][count];
            for(int c = 0; c < count; ++c){
                for(int i = 0; i < fields; ++i){
                    result[i][c] = nextInteger();
                }
            }
            return result;
        }
    }

    void noResult(){
        throw new NoResultException();
    }

    void noResult(String str){
        throw new NoResultException(str);
    }

    void run(){
        try{
            ByteArrayOutputStream outStream = new ByteArrayOutputStream();
            out = new PrintWriter(outStream);
            solve();
            out.close();
            System.out.print(outStream.toString());
        } catch (NoResultException exc){
            System.out.print(null == exc.response ? noResultMessage : exc.response);
        }
    }

    public static void main(String[] args) {
        new EMain().run();
    }

    public static class NoResultException extends RuntimeException{
        private String response;

        public NoResultException(String response) {
            this.response = response;
        }

        public NoResultException() {
        }
    }
}
