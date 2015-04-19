import java.util.Scanner;


public class CFD {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		String s = in.next();
		long [] numb = new long[2];
		long [] numa = new long[2];
		for(int i=0;i<s.length();i++) {
			if(s.charAt(i)=='a') {
				numa[i%2]++;
			}
			else {
				numb[i%2]++;
			}
		}
		long numo=0;
		long nume=0;
		for(int i=0;i<2;i++) {
			numo+=numb[i]*(numb[i]+1)/2;
			numo+=numa[i]*(numa[i]+1)/2;
		}
		nume+=numb[0]*numb[1];
		nume+=numa[0]*numa[1];
		System.out.println(nume+" "+numo);
	}

}
