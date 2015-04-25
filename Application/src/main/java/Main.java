import java.io.*;
import java.util.*;

/**
 * Main entry point to app
 */
public class Main implements Runnable {

    /* For debug purposes let's put all input files into one folder */

    String pathToInputFolder = ""; // default for submission to CF
    //String pathToInputFolder = "src/main/resources/mock/"; //current

    int N;
    SourceCode [] sourceCodes;

    /* Main method */
    public void solve () throws IOException {
        N = Integer.parseInt(next());
        sourceCodes = new SourceCode[N];
        for (int i = 0 ; i < N ; i ++) {
            sourceCodes[i] = new SourceCode(pathToInputFolder + next());
        }
        Parameters parameters = new Parameters();

        DSU dsu = new DSU(N);
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {

                double score = process(sourceCodes[i], sourceCodes[j], parameters) + process(sourceCodes[j], sourceCodes[i], parameters);
                double scoreKeepingVariables = processKeepingVariables(sourceCodes[i], sourceCodes[j], parameters) + processKeepingVariables(sourceCodes[j], sourceCodes[i], parameters);
                double scoreWithoutBracketLimit = processWithoutBracketLimit(sourceCodes[i], sourceCodes[j], parameters) + processWithoutBracketLimit(sourceCodes[j], sourceCodes[i], parameters);

                if (score >= 2.0 * parameters.PERCENTAGE_LIMIT)
                {
                    dsu.unite(i, j);
                }

                if (scoreKeepingVariables >= 2.0 * parameters.PERCENTAGE_LIMIT)
                {
                    dsu.unite(i, j);
                }

                if ((sourceCodes[i].raw.length() < 10 || sourceCodes[j].raw.length() < 10) && scoreWithoutBracketLimit >= 2.0 * 0.70)
                {
                    dsu.unite(i, j);
                }

            }
        }
        ArrayList<ArrayList<String> > ans = new ArrayList<ArrayList<String>>();
        boolean [] used = new boolean[N];
        for (int i = 0 ; i < N ; i++) {
            if (used[i])
                continue;
            used[i] = true;

            ArrayList<String> v = new ArrayList<String>();
            v.add(sourceCodes[i].fileName);

            for (int j = i + 1; j < N; j++) {
                if (!used[j] && dsu.getSet(j) == dsu.getSet(i)) {
                    used[j] = true;
                    v.add(sourceCodes[j].fileName);
                }
            }

            if (v.size() > 1)
                ans.add(v);
        }

        out.println(ans.size());
        for (int i = 0 ; i < ans.size() ; i++) {
            for (int j = 0 ; j < ans.get(i).size() ; j ++) {
                String fileName = ans.get(i).get(j);
                // output only relative to the input folder name
                fileName = fileName.substring(pathToInputFolder.length());
                out.print(fileName + " ");
            }
            out.println();
        }
    }

    public double process(SourceCode l, SourceCode r, Parameters parameters) {
        LinkedHashMap<Long, ArrayList<Integer>> lMap = l.getFingerprints(l.raw, parameters);
        LinkedHashMap<Long, ArrayList<Integer>> rMap = r.getFingerprints(r.raw, parameters);
        int total = lMap.size();
        int matches = 0;
        for (Map.Entry<Long, ArrayList<Integer> > entry : lMap.entrySet()) {
            if (rMap.containsKey(entry.getKey())) {
                matches ++;
            }
        }

        System.out.println(l.fileName + " " + r.fileName + " " + 1.0 * matches / total);

        return 1.0 * matches / total;
    }

    public double processKeepingVariables(SourceCode l, SourceCode r, Parameters parameters) {
        LinkedHashMap<Long, ArrayList<Integer>> lMap = l.getFingerprints(l.rawKeepVariables, parameters);
        LinkedHashMap<Long, ArrayList<Integer>> rMap = r.getFingerprints(r.rawKeepVariables, parameters);
        int total = lMap.size();
        int matches = 0;
        for (Map.Entry<Long, ArrayList<Integer> > entry : lMap.entrySet()) {
            if (rMap.containsKey(entry.getKey())) {
                matches ++;
            }
        }

        System.out.println(l.fileName + " " + r.fileName + " " + 1.0 * matches / total);

        return 1.0 * matches / total;
    }

    public double processWithoutBracketLimit(SourceCode l, SourceCode r, Parameters parameters) {
        LinkedHashMap<Long, ArrayList<Integer>> lMap = l.getFingerprints(l.rawNoBracketLimit, parameters);
        LinkedHashMap<Long, ArrayList<Integer>> rMap = r.getFingerprints(r.rawNoBracketLimit, parameters);
        int total = lMap.size();
        int matches = 0;
        for (Map.Entry<Long, ArrayList<Integer> > entry : lMap.entrySet()) {
            if (rMap.containsKey(entry.getKey())) {
                matches ++;
            }
        }

        System.out.println(l.fileName + " " + r.fileName + " " + 1.0 * matches / total);

        return 1.0 * matches / total;
    }

    BufferedReader bf;
    StringTokenizer st;
    PrintWriter out;

    /**
     * Get next token from input Stream input.txt
     * @return next Token from stream
     * @throws IOException
     */
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
            bf = new BufferedReader(new FileReader(pathToInputFolder + "input.txt"));
            out = new PrintWriter(new FileWriter(pathToInputFolder + "output.txt"));
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
        // Use runnable to get more memory
        Main task = new Main();
        task.run();

    }
}
