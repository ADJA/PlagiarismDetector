import java.io.*;
import java.util.*;

public class cf293E {
	static InputReader in = new InputReader();
	static String str = "";
	static String[] arr;
	static boolean works = true;
	static int[] a;
	
	public static void main(String[] args) throws Exception {
		str = in.readLine();
		int n = Integer.parseInt(str.substring(0, str.indexOf(" ")));
		int k = Integer.parseInt(str.substring(str.indexOf(" ") + 1));
		boolean[] det = new boolean[n];
		a = new int[n];
		arr = in.readLine().split(" ");
		for(int i = 0; i < n; i++) {
			if(arr[i].equals("?")) {
				det[i] = false;
			} else {
				det[i] = true;
				a[i] = Integer.parseInt(arr[i]);
			}
		}
		long tot = 0;
		for(int i = 0; i < k; i++) {
			int lowerbound = -1500000000;
			int upperbound = 1500000000;
			int count = 0;
			int ind = i;
			for(int j = i; j < n; j += k) {
				if(det[j]) {
					upperbound = Math.min(upperbound, a[j] - 1);
					comp(lowerbound, upperbound, count, ind, k);
					lowerbound = Math.max(lowerbound, a[j] + 1);
					upperbound = 1500000000;
					ind = j + k;
					count = 0;
				} else {
					count++;
				}
			}
			comp(lowerbound, upperbound, count, ind, k);
		}
		if(works) {
			for(int i = 0; i < n; i++) {
				System.out.print(a[i] + (i == n - 1 ? "\n" : " "));
			}
		} else {
			System.out.println("Incorrect sequence");
		}
	}

	public static void comp(int l, int r, int c, int s, int k) {
		if(s >= a.length) {
			return;
		}
		if((long) r - l + 1 < c) {
			works = false;
			return;
		}
		if(c % 2 == 1) {
			if(l <= -(c - 1) / 2 && (c - 1) / 2 <= r) {
				fill(s, s + (c - 1) * k, k, -(c - 1) / 2);
				return;
			}
			if((c - 1) / 2 <= r) {
				fill(s, s + (c - 1) * k, k, l);
				return;
			}
			fill(s, s + (c - 1) * k, k, r - c + 1);
			return;
		}
		if(l <= -c / 2 && c / 2 - 1 <= r) {
			fill(s, s + (c - 1) * k, k, -c / 2);
			return;
		}
		if(l <= -c / 2 + 1 && c / 2 <= r) {
			fill(s, s + (c - 1) * k, k, -c / 2 + 1);
			return;
		}
		if(c / 2 <= r) {
			fill(s, s + (c - 1) * k, k, l);
			return;
		}
		fill(s, s + (c - 1) * k, k, r - c + 1);
	}

	public static void fill(int s, int e, int k, int start) {
		int count = 0;
		for(int i = s; i <= e; i += k) {
			a[i] = start + count++;
		}
	}

	static class InputReader {
		BufferedReader br;
		public InputReader() {
			try {
				br = new BufferedReader(new FileReader("cf293E.in"));
			} catch(Exception e) {
				br = new BufferedReader(new InputStreamReader(System.in));
			}
		}

		public String readLine() throws Exception {
			return br.readLine();
		}
	}
}