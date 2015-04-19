import java.util.ArrayList;
import java.util.Scanner;

public class EMain {
    static class Int{
        int value;
        boolean isKnown;

        Int(int value) {
            this.value = value;
            this.isKnown = true;
        }

        Int(boolean isKnown) {
            this.isKnown = isKnown;
        }
    }

    public void solve() {
        Parser parser = new Parser();
        int n = parser.nextInteger();
        int k = parser.nextInteger();

        ArrayList<ArrayList<Int>> seq = new ArrayList<ArrayList<Int>>();
        for(int i = 0; i < k; ++i){
            seq.add(new ArrayList<Int>());
        }

        for(int i = 0; i < n; ++i){
            String str = parser.next();
            if(str.equals("?")){
                seq.get(i % k).add(new Int(false));
            } else {
                seq.get(i % k).add(new Int(Integer.parseInt(str)));
            }
        }

        for(int i = 0; i < k; ++i){
            ArrayList<Int> ar = new ArrayList<Int>();
            ar.add(new Int(Integer.MIN_VALUE / 2 + 5));
            ar.addAll(seq.get(i));
            ar.add(new Int(Integer.MAX_VALUE / 2 - 5));
            int minIndex = 0;
            int maxIndex = 0;
            while(maxIndex + 1 < ar.size()){
                maxIndex = minIndex + 1;
                while(!ar.get(maxIndex).isKnown)++maxIndex;
                int count = maxIndex - minIndex - 1;
                int maxValue = ar.get(maxIndex).value;
                int minValue = ar.get(minIndex).value;
                if(maxValue - minValue <= count){
                    System.out.print("Incorrect sequence");
                    return;
                }
                if(maxIndex - minIndex > 1){
                    int min = - count / 2;
                    if(min <= minValue) min = minValue + 1;
                    if(min + count - 1 >= maxValue) min = maxValue - count;
                    for(int j = 0; j < count; ++j){
                        ar.get(minIndex + 1 + j).value = min + j;
                    }
                }
                minIndex = maxIndex;
            }
        }

        StringBuilder builder = new StringBuilder();

        for(int i = 0; i < n; ++i) {
            builder.append(seq.get(i % k).get(i / k).value);
            builder.append(" ");
        }

        System.out.print(builder.toString());









    }

    public static void main(String[] args) {
        new EMain().solve();
    }

    static public class Parser{
        Scanner scanner;

        public Parser() {
            scanner = new Scanner(System.in);
        }

        public Parser(String str) {
            scanner = new Scanner(str);
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
            int[][] result = new int[fields][];
            for(int i = 0; i < fields; ++i){
                result[i] = new int[count];
            }
            for(int c = 0; c < count; ++c){
                for(int i = 0; i < fields; ++i){
                    result[i][c] = nextInteger();
                }
            }
            return result;
        }

        public String next() {
            return scanner.next();
        }
    }

    static public class Matrix{
        static public final int size = 101;
        static public final long base = 1000000007;

        static public class Vector{
            long[] data = new long[size];
        }
        private long[] data;

        public Matrix() {
            data = new long[size * size];
        }

        long get(int row, int column){
            return data[row * size + column];
        }

        long set(int row, int column, long value){
            int index = row * size + column;
            long result = data[index];
            data[index] = value;
            return result;
        }

        public Matrix mul(Matrix other){
            Matrix result = new Matrix();
            for(int r = 0; r < size; ++r){
                for(int c = 0; c < size; ++c){
                    long value = 0;
                    for(int i = 0; i < size; ++i){
                        value += get(r, i) * other.get(i, c);
                        value %= base;
                    }
                    result.set(r, c, value);
                }
            }
            return result;
        }




    }
}
