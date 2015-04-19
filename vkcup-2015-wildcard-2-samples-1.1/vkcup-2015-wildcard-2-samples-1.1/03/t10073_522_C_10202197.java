
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.math.BigDecimal;
import java.math.MathContext;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Objects;
import java.util.StringTokenizer;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Gerasimov
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    static BufferedReader inp = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter output = new PrintWriter(
            new BufferedWriter(new OutputStreamWriter(
                            System.out)));

    public static void main(String[] args) throws FileNotFoundException, IOException {

        StringTokenizer input = new StringTokenizer(inp.readLine());

        int t = Integer.parseInt(input.nextToken());

        for (int i = 0; i < t; i++) {
            inp.readLine();
            Raschet();
        }

        output.close();
    }

    public static void Raschet() throws IOException {
        StringTokenizer input = new StringTokenizer(inp.readLine());

        int m = Integer.parseInt(input.nextToken());
        int k = Integer.parseInt(input.nextToken());
        //исходный массив
        int[] mas = new int[k + 1];
        //массив в который будем сохранять при первой встречи с 1
        int[] mas2 = new int[k + 1];
        boolean[] mas3 = new boolean[k + 1];
        boolean[] mas4 = new boolean[k + 1];
        input = new StringTokenizer(inp.readLine());
        //был ли уже 0 в массиве
        boolean is0 = false;
        //колчиство нулей - количество нулей перед первой 1
        int count0 = 0;
        //колчичество нулей перед первой 1
        int count0pre1 = 0;
        //читаем массив
        for (int i = 1; i <= k; i++) {
            mas[i] = Integer.parseInt(input.nextToken());
        }
        boolean p = false;
        //читаем то что известно про первых просящих
        for (int i = 0; i < m - 1; i++) {
            input = new StringTokenizer(inp.readLine());
            //какое блюдо он выбрал
            int t = Integer.parseInt(input.nextToken());
            //был или нет феил при выборе блюда
            int r = Integer.parseInt(input.nextToken());
            //если был феил и это в первый раз
            if (r == 1 && !is0) {
                p = true;
                //копируем состояние массива на этот момент
                mas2 = Arrays.copyOf(mas, k + 1);
                //в массиве однозначно есть ноль
                is0 = true;
                //запоминаем количество нулей
                count0pre1 = count0;
                //обнуляем счетчик
                count0 = 0;
            }
            //если изветен номер блюда
            if (t > 0) {
                //уменьшаем его количество на 1
                mas[t]--;
                if (p){mas4[t]=true;}
                //если получился ноль то запоминаем это
                if (mas[t] == 0) {
                    is0 = true;
                }
            } else {
                //если неизвестно то увеличиваем счетчик нулей
                count0++;
            }

        }
        int min0 = 999999999;
        //находим минимальное значение в копированном массиве такое что в получившемся там не ноль
        if (p) {
            for (int i = 1; i <= k; i++) {
                if (!mas4[i] && min0 >= mas2[i]) {
                    min0 = mas2[i];
                }
                if (!mas4[i] &&count0pre1 >= mas2[i]) {
                    mas3[i] = true;
                }
            }
        }
        //выводим Y если в получившемся массиве число меньше чем сумарное количество нулей минус минимум в копированном
        for (int i = 1; i <= k; i++) {
            if ((mas[i] <= count0 + count0pre1 - (min0 == 999999999 ? 0 : min0)) || mas3[i]) {
                output.print("Y");
            } else {
                output.print("N");
            }
        }
        output.println();
    }

}
