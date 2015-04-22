import java.io.IOException;
import java.util.Arrays;
import java.util.InputMismatchException;
import java.util.HashSet;

public class BerlandLocalPositioningSystem {
    public static void main(String[] args) {
        FasterScanner sc = new FasterScanner();
        
        int N = sc.nextInt();
        
        int[] D = new int[N + 1];
        for (int i = 1; i <= N; i++) {
        	D[i] = sc.nextInt();
        }
        
        int M = sc.nextInt();
        
        int[] freq = new int[N + 1];
        int maxFreq = 0;
        for (int i = 0; i < M; i++) {
        	int B = sc.nextInt();
        	freq[B]++;
        	maxFreq = Math.max(maxFreq, freq[B]);
        }
        
        int[] endpts = new int[4];
        int idx = 0;
        boolean found = false;
        for (int i = 1; i <= N; i++) {
        	if (!found && freq[i] == maxFreq) {
        		endpts[idx++] = i;
        		found = true;
        	}
        	if (found && freq[i] != maxFreq) {
        		endpts[idx++] = i - 1;
        		found = false;
        	}
        }
        
        Long[] arr = new Long[12];
        arr[0] = check(D, freq, N, 1, 1);
        arr[1] = check(D, freq, N, N, -1);
        int cnt = 2;
        for (int pt : endpts) {
        	if (pt != 0) {
        		arr[cnt++] = check(D, freq, N, pt, -1);
        		arr[cnt++] = check(D, freq, N, pt, 1);
        	}
        }
        
        HashSet<Long> set = new HashSet<Long>();
        long val = -1;
        for (Long num : arr) {
        	if (num != null) {
        		set.add(num);
        		val = num;
        	}
        }
        
        if (set.size() == 1) {
        	System.out.println(val);
        } else {
        	System.out.println(-1);
        }
    }
    
    public static Long check(int[] D, int[] origFreq, int N, int idx, int dir) {
    	long dist = 0;
    	int[] freq = Arrays.copyOf(origFreq, origFreq.length);
    	while (freq[idx] > 0) {
    		freq[idx]--;
    		if (idx == 1) {
    			dir = 1;
    		} else if (idx == N) {
    			dir = -1;
    		}
    		int prev = idx;
    		idx += dir;
    		if (freq[idx] == 0) {
    			break;
    		}
    		dist += Math.abs(D[idx] - D[prev]);
    	}
    	for (int f : freq) {
    		if (f != 0) {
    			return null;
    		}
    	}
    	return dist;
    }
    
	public static class FasterScanner {
		private byte[] buf = new byte[1024];
		private int curChar;
		private int numChars;

		public int read() {
			if (numChars == -1)
				throw new InputMismatchException();
			if (curChar >= numChars) {
				curChar = 0;
				try {
					numChars = System.in.read(buf);
				} catch (IOException e) {
					throw new InputMismatchException();
				}
				if (numChars <= 0)
					return -1;
			}
			return buf[curChar++];
		}

		public String nextLine() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			StringBuilder res = new StringBuilder();
			do {
				res.appendCodePoint(c);
				c = read();
			} while (!isEndOfLine(c));
			return res.toString();
		}

		public String nextString() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			StringBuilder res = new StringBuilder();
			do {
				res.appendCodePoint(c);
				c = read();
			} while (!isSpaceChar(c));
			return res.toString();
		}

		public long nextLong() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = read();
			}
			long res = 0;
			do {
				if (c < '0' || c > '9')
					throw new InputMismatchException();
				res *= 10;
				res += c - '0';
				c = read();
			} while (!isSpaceChar(c));
			return res * sgn;
		}

		public int nextInt() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = read();
			}
			int res = 0;
			do {
				if (c < '0' || c > '9')
					throw new InputMismatchException();
				res *= 10;
				res += c - '0';
				c = read();
			} while (!isSpaceChar(c));
			return res * sgn;
		}
	        
	    public int[] nextIntArray(int n) {
	        int[] arr = new int[n];
	        for (int i = 0; i < n; i++) {
	            arr[i] = nextInt();
	        }
	        return arr;
	    }
        
		public long[] nextLongArray(int n) {
		    long[] arr = new long[n];
		    for (int i = 0; i < n; i++) {
		        arr[i] = nextLong();
		    }
		    return arr;
		}

	    private boolean isSpaceChar(int c) {
			return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
		}

		private boolean isEndOfLine(int c) {
			return c == '\n' || c == '\r' || c == -1;
		}
	}
}