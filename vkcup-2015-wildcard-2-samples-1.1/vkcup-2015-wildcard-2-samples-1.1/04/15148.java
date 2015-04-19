import java.util.*;
import static java.lang.Math.*;
import java.io.*;

public class E {
	static void p(Object ...o) {System.out.println(Arrays.deepToString(o));}; 
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		N = in.nextInt();
		G = new ArrayList[N];
		for (int i = 0; i < N; i++)
			G[i] = new ArrayList<Integer>();
		for (int i = 0; i < N-1; i++) {
			int a = in.nextInt()-1;
			int b = in.nextInt()-1;
			G[a].add(b);
			G[b].add(a);
		}

		pos = new boolean[N];
		DP = new int[N+1][N+1];
		size(0, -1);
		
		int numans = 0;
		for (int i = 1; i < N - 1;i++)
			if(pos[i])
				numans++;
		System.out.println(numans);
		for (int i = 1; i < N-1; i++) {
			if (pos[i]) {
				System.out.println(i+" "+(N-i-1));
			}
		}
	}
	private static int size(int at, int p) {
		ArrayList<Integer> sizes = new ArrayList<Integer>();
		for (int e:G[at]) {
			if (e == p)
				continue;
			sizes.add(size(e, at));
		}
		int total = 0;
		for (int s:sizes)
			total += s;
		sizes.add(N-total-1);
		
		
		for (int i = 0; i <= sizes.size(); i++) {
			Arrays.fill(DP[i], 0);
		}
		DP[0][0] = 1;
		for (int i = 0; i < sizes.size(); i++) {
			for (int j = 0; j <= N ;j++) {
				if (DP[i][j] == 1) {
					DP[i+1][j] = 1;
					DP[i+1][j+sizes.get(i)] = 1;
				}
			}
		}
		for (int j = 0; j <= N; j++)
			if (DP[sizes.size()][j] == 1)
				pos[j] = true;
		return total + 1;
	}
	static int[][] DP;
	static int N;
	static boolean[] pos;
	static ArrayList<Integer>[] G;
}
