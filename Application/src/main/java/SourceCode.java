import java.io.*;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.StringTokenizer;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by nurlan on 4/20/15.
 */
public class SourceCode {
    String fileName;
    String extension;
    String raw, rawKeepVariables;
    ArrayList <String> code;
    public SourceCode(String fileName) {
        try {
            this.fileName = fileName;
            File file = new File(fileName);

            int i = fileName.lastIndexOf('.');
            if (i > 0)
                extension = fileName.substring(i + 1);
            else
                extension = "";

            BufferedReader in = new BufferedReader(
                    new InputStreamReader(
                            new FileInputStream(file), "UTF8"));

            code = new ArrayList<String>();
            String str;
            while ((str = in.readLine()) != null) {
                code.add(str.toLowerCase());
            }

            in.close();

            preprocess();
        }
        catch (UnsupportedEncodingException e)
        {
            System.out.println(e.getMessage());
            System.exit(-1);
        }
        catch (IOException e)
        {
            System.out.println(e.getMessage());
            System.exit(-1);
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
            System.exit(-1);
        }
    }

    public void preprocess() {

        Preprocessor preprocessor;

        if (extension.equals("cpp") || extension.equals("c") || extension.equals("d"))
            preprocessor = new CppPreprocessor();
        else if (extension.equals("java") || extension.equals("cs"))
            preprocessor = new JavaPreprocessor();
        else if (extension.equals("pas") || extension.equals("dpr"))
            preprocessor = new PascalPreprocessor();
        else if (extension.equals("py"))
            preprocessor = new PythonPreprocessor();
        else
            preprocessor = new DefaultPreprocessor();

        raw = preprocessor.preprocess(code, false);
        rawKeepVariables = preprocessor.preprocess(code, true);
        System.out.println("PREPROCESSED " + fileName);
        System.out.println(raw);

    }

    public LinkedHashMap<Long, ArrayList<Integer> > getFingerprints(String raw, Parameters parameters) {
        int K = parameters.K;
        LinkedHashMap<Long, ArrayList<Integer> > map = new LinkedHashMap<Long, ArrayList<Integer>>();

        // Rolling hashes of length K
        // of the form ( s[i] * p^(k-1) + s[i+1] * p^(k-2) + ... + s[i + K - 2] * p + s[i-K+1] )
        long currentHash = 0;
        int p = parameters.p;
        long pp = 1L; // will be p^(k-1)
        for (int i = 0 ; i < K - 1 ; i ++) {
            pp *= p;
        }
        for (int i = 0 ; i < raw.length() ; i ++) {
            if (i < K) {
                currentHash = currentHash * p + raw.charAt(i);
            } else {
                currentHash -= raw.charAt(i - K) * pp;
                currentHash = currentHash * p + raw.charAt(i);
            }
            if (i >= K - 1) {
                if (!map.containsKey(currentHash)) {
                    map.put(currentHash, new ArrayList<Integer>());
                }
                map.get(currentHash).add(i);
            }
        }
        return map;
    }
}
