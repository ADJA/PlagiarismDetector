import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Random;

/**
 * Author: Adilet Zhaxybay
 * Date: 21.04.15
 * Time: 23:39
 */
public class CppPreprocessor implements Preprocessor {

    final String[] badLineBeginnings = {"#include", "#define", "//", "using", "template"};
    final String[] keywords = {"struct", "class", "const", "for", "if", "int", "long", "string", "printf", "scanf",
            "double", "char", "byte", "short", "while", "cin", "cout", "gets", "puts", "getline", "return", "max",
            "min", "vector", "map", "set", "assert", "freopen", "stdin", "stdout", "pair", "bool", "memset", "queue",
            "priority_queue", "queue", "stack", "cerr", "iterator", "void", "switch", "case", "do", "break",
            "continue", "else", "true", "false", "float", "push_back", "make_pair", "sort", "unique", "reverse",
            "next_permutation", "strlen", "count", "insert", "append", "length", "size", "ceil", "floor"};

    ArrayList <String> defines;

    final char badChars[] = {' ' /*, ';', '{', '}'*/ };

    final String opening = "{", closing = "}";
    final int openingLimit = 2;

    final String commentStart = "/*", commentEnd = "*/";
    final char stringStart = '"', stringEnd = '"';

    final int p = 257;
    final int mod = 10000000;

    public boolean startsBadly(String s) {
        for (String bad : badLineBeginnings)
            if (s.startsWith(bad))
                return true;
        return false;
    }

    public boolean isKeyword(String s) {
        for (String keyword : keywords)
            if (s.equals(keyword))
                return true;
        return false;
    }

    public boolean isDelimeter(char c) {
        if (Character.isAlphabetic(c) || Character.isDigit(c))
            return false;
        return true;
    }

    public boolean isBadChar(char c) {
        for (char badChar : badChars)
            if (c == badChar)
                return true;
        return false;
    }

    public String preprocess(ArrayList <String> code, boolean keepVariables) {

        //System.out.println(code);

        StringBuilder raw = new StringBuilder();
        int variableNum = 0;
        defines = new ArrayList<String>(); // TODO: do something with it
        ArrayList <String> variables = new ArrayList<String>();
        ArrayList <Integer> variablePositions = new ArrayList<Integer>();

        boolean inComment = false;
        boolean inString = false;
        int opened = 0;
        int charNum = 0;

        for (String line : code) {

            line = line.trim();

            if (!inComment) {
                if (startsBadly(line))
                    continue;
            }

            StringBuilder curWord = new StringBuilder();
            for (int i = 0; i < line.length(); i++) {
                char curChar = line.charAt(i);
                if (inString) {
                    if (curChar == stringEnd) {
                        inString = false;
                    }
                    continue;
                }
                if (inComment) {
                    if (line.regionMatches(i, commentEnd, 0, commentEnd.length())) {
                        inComment = false;
                        i += commentEnd.length() - 1;
                    }
                    continue;
                }
                if (curChar == stringStart) {
                    inString = true;
                    curWord.setLength(0);
                    continue;
                }
                if (line.regionMatches(i, commentStart, 0, commentStart.length())) {
                    inComment = true;
                    curWord.setLength(0);
                    i += commentStart.length() - 1;
                    continue;
                }

                if (line.regionMatches(i, opening, 0, opening.length())) {
                    opened++;
                    //curWord.setLength(0);
                    //i += opening.length() - 1;
                    //continue;
                }
                if (line.regionMatches(i, closing, 0, closing.length())) {
                    opened--;
                    //curWord.setLength(0);
                    //i += closing.length() - 1;
                    //continue;
                }

                char lastChar = 0;
                if (i > 0)
                    lastChar = line.charAt(i - 1);

                if (isDelimeter(curChar) || isDelimeter(lastChar)) {
                    String word = curWord.toString();
                    if (word.length() != 0) {
                        //System.out.println(word);
                        if (!Character.isDigit(word.charAt(0)) && (!Character.isAlphabetic(word.charAt(0))) || isKeyword(word)) {
                            raw.append(word);
                        }
                        else {
                            if (!keepVariables) {
                                long hash = 0;
                                long pp = 1L;
                                int curLen = raw.length();
                                for (int j = 0; j < Math.min(5, curLen); j++) {
                                    hash = (hash + (long) (raw.charAt(curLen - 1 - j)) * pp) % mod;
                                    while (hash < 0)
                                        hash += mod;
                                    pp *= 1L * p;
                                }

                                word = Long.toString(hash);
                            }
                            variables.add(word);
                            variablePositions.add(raw.length());
                            //raw.append(word);
                        }
                    }
                    curWord.setLength(0);
                }

                if (opened < openingLimit)
                    continue;

                if (isBadChar(curChar))
                    continue;

                curWord.append(curChar);
            }
            raw.append(curWord.toString());
        }

        //System.out.println(raw.toString());

        StringBuilder rawString = new StringBuilder();

        System.out.println(variables.size());
        System.out.println(variables);
        System.out.println(variablePositions);

        int pos = 0;
        for (int i = 0; i <= raw.length(); i++) {
            while (pos < variablePositions.size() && i == variablePositions.get(pos)) {
                rawString.append(variables.get(pos));
                pos++;
            }
            if (i < raw.length())
                rawString.append(raw.charAt(i));
        }

        return rawString.toString();
    }
}
