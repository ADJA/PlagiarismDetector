import java.util.ArrayList;
import java.util.Scanner;

public class E {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		long[] a = new long[n];
		long[] l = new long[n-1];
		boolean same_l = true;
		for (int i = 0; i < n; i++) {
			a[i] = in.nextLong();
			if (i!=0) {
				l[i-1] = a[i] - a[i-1];
				if (l[i-1] != l[0]) {
					same_l = false;
				}
			}
		}
		int m = in.nextInt();
		int[] stops = new int[n];
		for (int i = 0; i < m; i++) {
			stops[in.nextInt()-1]++;
		}
		in.close();
		long full_circ = 2*(a[n-1]-a[0]);
		long re = 0;
		while(true) {
			for (int i = 0; i < n; i++) {
				stops[i] -= 2;
			}
			stops[0]++;
			stops[n-1]++;
			boolean fc = true; 
			for (int i = 0; i < n; i++) {
				if (stops[i] < 0) {
					fc = false;
					break;
				}
			}
			if (fc) {
				re +=full_circ;
			} else {
				for (int i = 0; i < n; i++) {
					stops[i] += 2;
				}
				stops[0]--;
				stops[n-1]--;
				break;
			}
		}
		boolean sp_case = true;
		for (int i = 0; i < n; i++) {
			if (stops[i]!=0) {
				sp_case = false; 
				break;
			}
		}
		if (sp_case) {
			if (same_l) {
				System.out.println(re-l[0]);
			} else {
				System.out.println(-1);
			}
		} else {
			if (stops[0] == 1) {
				stops[0]++;
			}
			if (stops[n-1] == 1) {
				stops[n-1]++;
			}
			for (int i = 0; i < n-1; i++) {
				re+=l[i]*Math.min(stops[i],stops[i+1]);
			}
			System.out.println(re);
		}
	}
}