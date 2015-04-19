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
    public void Solve()
    {
        int n = ReadInt();
        int m = ReadInt();

        var a = new int[n];
        var f = new bool[n];
        for (int i = 0; i < n; i++)
        {
            string s = ReadToken();
            if (s == "?")
                f[i] = true;
            else
                a[i] = int.Parse(s);
        }

        for (int i = 0; i < m; i++)
        {
            var q = new List<int>();
            int low = int.MinValue;
            for (int j = i; j < n; j += m)
            {
                if (f[j])
                    q.Add(j);
                else
                {
                    if (q.Count > 0)
                    {
                        if (low == int.MinValue)
                            low = -1001000000;

                        if (a[j] - low - 1 < q.Count)
                        {
                            Write("Incorrect sequence");
                            return;
                        }
                        int p = (q.Count + 1) / -2 + 1;
                        if (p <= low)
                            p = low + 1;
                        if (p + q.Count > a[j])
                            p = a[j] - q.Count;

                        for (int k = 0; k < q.Count; k++)
                            a[q[k]] = p + k;
                        q.Clear();
                    }
                    else if (a[j] <= low)
                    {
                        Write("Incorrect sequence");
                        return;
                    }
                    low = a[j];
                }
            }

            if (q.Count > 0)
            {
                if (low == int.MinValue)
                    low = -1001000000;
                int high = 1001000000;

                if (high - low - 1 < q.Count)
                {
                    Write("Incorrect sequence");
                    return;
                }
                int p = (q.Count + 1) / -2 + 1;
                if (p <= low)
                    p = low + 1;
                if (p + q.Count > high)
                    p = high - q.Count;

                for (int k = 0; k < q.Count; k++)
                    a[q[k]] = p + k;
                q.Clear();
            }
        }

        WriteArray(a);
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
        //reader = new StreamReader("game.in");
        //writer = new StreamWriter("game.out");
#endif
        try
        {
//            var thread = new Thread(new Solver().Solve, 1024 * 1024 * 256);
//            thread.Start();
//            thread.Join();
            new Solver().Solve();    
        }
        catch (Exception ex)
        {
#if DEBUG
            Console.WriteLine(ex);
#else
            Console.WriteLine(ex);
            throw;
#endif
        }
        reader.Close();
        writer.Close();
    }

    #endregion

    #region Read / Write

    private static Queue<string> currentLineTokens = new Queue<string>();

    private static string[] ReadAndSplitLine()
    {
        return reader.ReadLine().Split(new[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);
    }

    public static string ReadToken()
    {
        while (currentLineTokens.Count == 0)
            currentLineTokens = new Queue<string>(ReadAndSplitLine());
        return currentLineTokens.Dequeue();
    }

    public static int ReadInt()
    {
        return int.Parse(ReadToken());
    }

    public static long ReadLong()
    {
        return long.Parse(ReadToken());
    }

    public static double ReadDouble()
    {
        return double.Parse(ReadToken(), CultureInfo.InvariantCulture);
    }

    public static int[] ReadIntArray()
    {
        return ReadAndSplitLine().Select(int.Parse).ToArray();
    }

    public static long[] ReadLongArray()
    {
        return ReadAndSplitLine().Select(long.Parse).ToArray();
    }

    public static double[] ReadDoubleArray()
    {
        return ReadAndSplitLine().Select(s => double.Parse(s, CultureInfo.InvariantCulture)).ToArray();
    }

    public static int[][] ReadIntMatrix(int numberOfRows)
    {
        int[][] matrix = new int[numberOfRows][];
        for (int i = 0; i < numberOfRows; i++)
            matrix[i] = ReadIntArray();
        return matrix;
    }

    public static int[][] ReadAndTransposeIntMatrix(int numberOfRows)
    {
        int[][] matrix = ReadIntMatrix(numberOfRows);
        int[][] ret = new int[matrix[0].Length][];
        for (int i = 0; i < ret.Length; i++)
        {
            ret[i] = new int[numberOfRows];
            for (int j = 0; j < numberOfRows; j++)
                ret[i][j] = matrix[j][i];
        }
        return ret;
    }

    public static string[] ReadLines(int quantity)
    {
        string[] lines = new string[quantity];
        for (int i = 0; i < quantity; i++)
            lines[i] = reader.ReadLine().Trim();
        return lines;
    }

    public static void WriteArray<T>(IEnumerable<T> array)
    {
        writer.WriteLine(string.Join(" ", array));
    }

    public static void Write(params object[] array)
    {
        WriteArray(array);
    }

    public static void WriteLines<T>(IEnumerable<T> array)
    {
        foreach (var a in array)
            writer.WriteLine(a);
    }

    #endregion
}