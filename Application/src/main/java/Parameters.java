/**
 * Created by nurlan on 4/20/15.
 */
public class Parameters {
    int K = 5;
    int W = 1;
    double PERCENTAGE_LIMIT = 0.65;
    int p = 257;
    public Parameters() {

    }
    Parameters withK(int K) {
        this.K = K;
        return this;
    }
    Parameters withW(int W) {
        this.W = W;
        return this;
    }
    Parameters withPercentageLimit(double percentage) {
        this.PERCENTAGE_LIMIT = percentage;
        return this;
    }
    Parameters withPrimeP(int prime) {
        this.p = prime;
        return this;
    }
}
