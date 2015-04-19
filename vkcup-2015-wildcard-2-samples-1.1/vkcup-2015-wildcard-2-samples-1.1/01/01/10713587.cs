using System;
using System.Linq;
using System.Text.RegularExpressions;
using System.Collections.Generic;
using Debug = System.Diagnostics.Debug;
using StringBuilder = System.Text.StringBuilder;
using System.Numerics;
using System.Threading.Tasks;
namespace Program
{
    public class Solver
    {
        public void Solve()
        {
            var n = sc.Integer();
            var m = sc.Integer();
            var p = sc.Scan();
            var a = sc.Integer(m);
            for (int i = 0; i < m; i++)
                a[i]--;
            var len = p.Length;
            var str = new char[n];
            for (int i = 0; i < n; i++)
                str[i] = '?';
            for (int i = 0; i < m; i++)
            {
                var ptr = a[i];
                var next = Math.Min(a[i] + len, n);
                if (i < m - 1)
                    next = Math.Min(next, a[i + 1]);
                for (int j = ptr, k = 0; j < next; j++, k++)
                    str[j] = p[k];
            }
            var table = StringEx.ZAlgorithm(p + str.AsString());
            long ans = 1;
            foreach (var x in a)
            {
                if (table[len + x] >= len)
                    continue;
                else ans = 0;
            }
            var cnt = 0;
            for (int i = 0; i < n; i++)
                if (str[i] == '?') cnt++;
            ans = ans * ModPow(26, cnt, 1000000007);
            IO.Printer.Out.WriteLine(ans);
            
        }
        static public long ModPow(long x, long n, long mod)
        {
            long r = 1;
            while (n > 0)
            {
                if ((n & 1) == 1)
                    r = r * x % mod;
                x = x * x % mod;
                n >>= 1;
            }
            return r;
        }
        public IO.StreamScanner sc = new IO.StreamScanner(Console.OpenStandardInput());
        static T[] Enumerate<T>(int n, Func<int, T> f) { var a = new T[n]; for (int i = 0; i < n; ++i) a[i] = f(i); return a; }
    }
}

#region Ex
namespace Program.IO
{
    using System.IO;
    using System.Text;
    using System.Globalization;
    public class Printer : StreamWriter
    {
        static Printer() { Out = new Printer(Console.OpenStandardOutput()) { AutoFlush = false }; }
        public static Printer Out { get; set; }
        public override IFormatProvider FormatProvider { get { return CultureInfo.InvariantCulture; } }
        public Printer(System.IO.Stream stream) : base(stream, new UTF8Encoding(false, true)) { }
        public Printer(System.IO.Stream stream, Encoding encoding) : base(stream, encoding) { }
        public void Write<T>(string format, IEnumerable<T> source) { base.Write(format, source.OfType<object>().ToArray()); }
        public void WriteLine<T>(string format, IEnumerable<T> source) { base.WriteLine(format, source.OfType<object>().ToArray()); }
    }
    public class StreamScanner
    {
        public StreamScanner(Stream stream) { str = stream; }
        public readonly Stream str;
        private readonly byte[] buf = new byte[1024];
        private int len, ptr;
        public bool isEof = false;
        public bool IsEndOfStream { get { return isEof; } }
        private byte read()
        {
            if (isEof) return 0;
            if (ptr >= len) { ptr = 0; if ((len = str.Read(buf, 0, 1024)) <= 0) { isEof = true; return 0; } }
            return buf[ptr++];
        }
        public char Char() { byte b = 0; do b = read(); while (b < 33 || 126 < b); return (char)b; }

        public string Scan()
        {
            var sb = new StringBuilder();
            for (var b = Char(); b >= 33 && b <= 126; b = (char)read())
                sb.Append(b);
            return sb.ToString();
        }
        public long Long()
        {
            if (isEof) return long.MinValue;
            long ret = 0; byte b = 0; var ng = false;
            do b = read();
            while (b != '-' && (b < '0' || '9' < b));
            if (b == '-') { ng = true; b = read(); }
            for (; true; b = read())
            {
                if (b < '0' || '9' < b)
                    return ng ? -ret : ret;
                else ret = ret * 10 + b - '0';
            }
        }
        public int Integer() { return (isEof) ? int.MinValue : (int)Long(); }
        public double Double() { return double.Parse(Scan(), CultureInfo.InvariantCulture); }
        private T[] enumerate<T>(int n, Func<T> f)
        {
            var a = new T[n];
            for (int i = 0; i < n; ++i) a[i] = f();
            return a;
        }

        public char[] Char(int n) { return enumerate(n, Char); }
        public string[] Scan(int n) { return enumerate(n, Scan); }
        public double[] Double(int n) { return enumerate(n, Double); }
        public int[] Integer(int n) { return enumerate(n, Integer); }
        public long[] Long(int n) { return enumerate(n, Long); }
    }
}
static class Ex
{
    static public string AsString(this IEnumerable<char> ie) { return new string(System.Linq.Enumerable.ToArray(ie)); }
    static public string AsJoinedString<T>(this IEnumerable<T> ie, string st = " ") { return string.Join(st, ie); }
    static public void Main()
    {
        var solver = new Program.Solver();
        solver.Solve();
        Program.IO.Printer.Out.Flush();
    }
}
#endregion

#region Z Algorithm
static public partial class StringEx
{
    //接頭辞が何文字一致しているか調べる
    static public int[] ZAlgorithm(string s)
    {
        var a = new int[s.Length];
        a[0] = s.Length;
        int i = 1, j = 0;
        while (i < s.Length)
        {
            while (i + j < s.Length && s[j] == s[i + j]) ++j;
            a[i] = j;
            if (j == 0) { ++i; continue; }
            int k = 1;
            while (i + k < s.Length && k + a[k] < j) { a[i + k] = a[k]; ++k; }
            i += k; j -= k;
        }
        return a;
    }
    static public bool[] ZAlgorithm(string s, string t)
    {
        var ns = t + s;
        /*
        var ns = new int[t.Length + s.Length];
        for (int i = 0; i < t.Length; i++)
            ns[i] = t[i];
        for (int i = 0; i < s.Length; i++)
            ns[i + t.Length] = s[i];
        //*/
        var res = ZAlgorithm(ns);
        var ret = new bool[s.Length];
        for (int i = t.Length; i < res.Length; i++)
            ret[i - t.Length] = res[i] >= t.Length;
        return ret;


    }
}
#endregion