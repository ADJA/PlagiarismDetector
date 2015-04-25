import java.util.ArrayList;

/**
 * Author: Adilet Zhaxybay
 * Date: 21.04.15
 * Time: 23:34
 */
public interface Preprocessor {

    public String preprocess(ArrayList <String> code, boolean keepVariables, boolean useLimitingBracketDepth);

}
