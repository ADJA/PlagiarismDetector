using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;

// (づ°ω°)づﾐ★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜
public class Solver
{
    int Encode(int[] a, int d)
    {
        int ret = 0;
        foreach (int aa in a) ret = ret * d + aa;
        return ret;
    }

    int[] Decode(int x, int n, int d)
    {
        var ret = new int[n];
        for (int i = 0; i < n; i++)
        {
            ret[i] = x % d;
            x /= d;
        }
        return ret;
    }

    private int n, m, d, lim;
    private int[] a, b;
    private List<int>[] opts;
    private bool[,,] mem;
    private int[] moves;
    bool Fun(int step,  int last)
    {
        if (step == m)
        {
            for (int i = 0; i < n; i++)
                if (a[i] > 0)
                    return false;
            var ans = new char[n][];
            for (int i = 0; i < n; i++)
                ans[i] = new char[m];
            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++)
                    ans[j][i] = (moves[i] >> j & 1) == 1 ? '*' : '.';
            for (int i = 0; i < n; i++)
                Write(new string(ans[i]));
            return true;
        }
        int e = Encode(a, d);
        if (mem[step, e, last])
            return false;
        for (int i = 0; i < n; i++)
            if (a[i] > (m - step) / 2 + 1)
            {
                mem[step, e, last] = true;
                return false;
            }
        
        foreach (int o in opts[b[step]])
        {
            bool ok = true;
            for (int i = 0; i < n; i++)
                if ((last >> i & 1) == 0 && (o >> i & 1) == 1)
                {
                    if (a[i] == 0)
                        ok = false;
                    a[i]--;
                }
            moves[step] = o;
            if (ok && Fun(step + 1, o))
                return true;
            for (int i = 0; i < n; i++)
                if ((last >> i & 1) == 0 && (o >> i & 1) == 1)
                    a[i]++;
        }

        mem[step, e, last] = true;
        return false;
    }

    public void Solve()
    {
        n = ReadInt();
        m = ReadInt();
        a = ReadIntArray();
        b = ReadIntArray();

        opts = Init<List<int>>(n + 1);
        for (int i = 0; i < (1 << n); i++)
        {
            int c = 0;
            for (int j = 0; j < n; j++)
                if ((i >> j & 1) == 1 && (j == 0 || (i >> j - 1 & 1) == 0))
                    c++;
            opts[c].Add(i);
        }

        d = (m + 3) / 2;
        lim = 1;
        for (int i = 0; i < n; i++)
            lim *= d;

        mem = new bool[m,lim,1 << n];
        moves = new int[m];
        Fun(0, 0);
    } 
  
    #region Main

    protected static TextReader reader;
    protected static TextWriter writer;
    static void Main()
    {
#if DEBUG
        reader = new StreamReader("..\\..\\input.txt");
        writer = Console.Out;
        //writer = new StreamWriter("..\\..\\output.txt");
#else
        reader = new StreamReader(Console.OpenStandardInput());
        writer = new StreamWriter(Console.OpenStandardOutput());
        //reader = new StreamReader("cycle.in");
        //writer = new StreamWriter("cycle.out");
#endif
        try
        {
//            var thread = new Thread(new Solver().Solve, 1024 * 1024 * 128);
//            thread.Start();
//            thread.Join();
            new Solver().Solve();
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex);
#if DEBUG
#else
            throw;
#endif
        }
        reader.Close();
        writer.Close();
    }

    #endregion

    #region Read / Write
    private static Queue<string> currentLineTokens = new Queue<string>();
    private static string[] ReadAndSplitLine() {return reader.ReadLine().Split(new[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);}
    public static string ReadToken(){while (currentLineTokens.Count == 0)currentLineTokens = new Queue<string>(ReadAndSplitLine());return currentLineTokens.Dequeue();}
    public static int ReadInt(){return int.Parse(ReadToken());}
    public static long ReadLong(){return long.Parse(ReadToken());}
    public static double ReadDouble(){return double.Parse(ReadToken(), CultureInfo.InvariantCulture);}
    public static int[] ReadIntArray(){return ReadAndSplitLine().Select(int.Parse).ToArray();}
    public static long[] ReadLongArray(){return ReadAndSplitLine().Select(long.Parse).ToArray();}
    public static double[] ReadDoubleArray(){return ReadAndSplitLine().Select(s => double.Parse(s, CultureInfo.InvariantCulture)).ToArray();}
    public static int[][] ReadIntMatrix(int numberOfRows){int[][] matrix = new int[numberOfRows][];for (int i = 0; i < numberOfRows; i++)matrix[i] = ReadIntArray();return matrix;}
    public static int[][] ReadAndTransposeIntMatrix(int numberOfRows){int[][] matrix = ReadIntMatrix(numberOfRows);int[][] ret = new int[matrix[0].Length][];
        for (int i = 0; i < ret.Length; i++){ret[i] = new int[numberOfRows];for (int j = 0; j < numberOfRows; j++)ret[i][j] = matrix[j][i];}return ret;}
    public static string[] ReadLines(int quantity){string[] lines = new string[quantity];for (int i = 0; i < quantity; i++)lines[i] = reader.ReadLine().Trim();return lines;}
    public static void WriteArray<T>(IEnumerable<T> array){writer.WriteLine(string.Join(" ", array));}
    public static void Write(params object[] array){WriteArray(array);}
    public static void WriteLines<T>(IEnumerable<T> array){foreach (var a in array)writer.WriteLine(a);}
    private class SDictionary<TKey, TValue> : Dictionary<TKey, TValue>{public new TValue this[TKey key]{
        get { return ContainsKey(key) ? base[key] : default(TValue); }set { base[key] = value; }}}
    private static T[] Init<T>(int size) where T : new(){var ret = new T[size];for (int i = 0; i < size; i++)ret[i] = new T();return ret;}
    #endregion
}