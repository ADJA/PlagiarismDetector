import std.algorithm;
import std.array;
import std.container;
import std.conv;
import std.exception;
import std.functional;
import std.math;
import std.numeric;
import std.range;
import std.stdio;
import std.string;
import std.typecons;
import core.bitop;

immutable int TODO = 1_234_567_890;

void main ()
{
	int n, k;
	while (readf (" %s %s ", &n, &k) > 0)
	{
		auto a = readln ().split ()
		    .map !(x => x == "?" ? TODO : x.to !(int)).array;
		foreach (s; 0..k)
		{
			a ~= TODO - 1;
		}

		void go (int lo, int hi)
		{
			if (lo >= hi)
			{
				return;
			}
			int blo = lo >= k ? a[lo - k] : -TODO + 1;
			int bhi = a[hi];
			int len = (hi - lo) / k;
			int vlo = -len / 2;
			int vhi = vlo + len - 1;
			if (vlo <= blo)
			{
				vlo = blo + 1;
				vhi = vlo + len - 1;
			}
			if (vhi >= bhi)
			{
				vhi = bhi - 1;
				vlo = vhi - len + 1;
			}
			for (int i = lo; i < hi; i += k)
			{
				a[i] = vlo;
				vlo++;
			}
		}

		foreach (s; 0..k)
		{
			int lo = s;
			int hi = s;
			for (int i = s; i < n + k; i += k)
			{
				if (a[i] == TODO)
				{
					hi = i + k;
				}
				else
				{
					go (lo, hi);
					lo = hi = i + k;
				}
			}
		}

		bool ok = true;
		foreach (i; 0..n)
		{
			ok &= (a[i] < a[i + k]);
		}

		if (ok)
		{
			writefln ("%(%s %)", a[0..n]);
		}
		else
		{
			writeln ("Incorrect sequence");
		}
	}
}
