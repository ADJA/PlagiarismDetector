import java.util.Random;

/**
 * Created by nurlan on 4/20/15.
 */
public class DSU {
    int N;
    int [] st;
    int currentSize = 0;
    Random random;
    public DSU(int N) {
        this.N = N;
        st = new int[N];
        for (int i = 0 ; i < N ; i ++) {
            st[i] = i;
        }
        currentSize = N;
        random = new Random();
    }
    public int getSet(int x) {
        while (st[x] != x) {
            st[x] = st[st[x]];
            x = st[x];
        }
        return x;
    }
    public void unite(int u, int v) {
        u = getSet(u); v = getSet(v);
        if (u != v) {
            currentSize --;
            if (random.nextBoolean())
                st[u] = v;
            else
                st[v] = u;
        }
    }
}
