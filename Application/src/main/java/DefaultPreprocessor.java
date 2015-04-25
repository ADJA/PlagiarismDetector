/**
 * Author: Adilet Zhaxybay
 * Date: 24.04.15
 * Time: 0:51
 */
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Random;

public class DefaultPreprocessor implements Preprocessor {

    final int p = 257;
    final int mod = 10000000;

    public String preprocess(ArrayList <String> code, boolean keepVariables, boolean useLimitingBracketDepth) {

        //System.out.println(code);

        StringBuilder raw = new StringBuilder();

        for (String line : code) {

            line = line.trim();

            StringBuilder curWord = new StringBuilder();
            for (int i = 0; i < line.length(); i++) {
                char curChar = line.charAt(i);

                if (curChar != ' ')
                    curWord.append(curChar);
            }
            raw.append(curWord.toString());
        }

        //System.out.println(raw.toString());
        return raw.toString();
    }
}