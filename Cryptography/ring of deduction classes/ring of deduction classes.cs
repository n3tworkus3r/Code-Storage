using System;
using System.Collections.Generic;

Console.ForegroundColor = ConsoleColor.White;
PrintMultiplicationAddictionTable(9);
int n = 8, m = 9;
if(InverseClass(m, n) > 0)
    Console.WriteLine($"\nReverse element in the ring of the residue class mod {m} for {n} is " + InverseClass(m, n) + " (InverseClass)\n");
if(InverseBezu(m, n) > 0)
    Console.WriteLine($"\nReverse element in the ring of the residue class mod {m} for {n} is " + InverseBezu(m, n) + " (InverseBezu)\n");
Console.WriteLine($"Eiler function for {31} is " + EilerFunction(31));

#region ClassTable
static void PrintMultiplicationAddictionTable(int n)
{
    #region FormatView
    Console.WriteLine("\n");
    for (int i = 0; i < n*2-2; i++)
        Console.Write(" ");

    Console.WriteLine("ADDITION TABLE".PadLeft(15));

    Console.Write("   ");

    for (int i = 0; i < n; i++)
        Console.Write("----");

    Console.Write("\n    ");

    for (int i = 0; i < n; i++)
        Console.Write(" {0,-2} ", i);
    
    Console.WriteLine();
    Console.Write("   ");
    for (int i = 0; i < n; i++)
        Console.Write("----");

    Console.WriteLine();
    #endregion

    // ADDITION TABLE
    for (int i = 0; i < n; i++)
    {
        Console.Write("{0,-3}|".PadLeft(3), i);
        for (int j = 0; j < n; j++)
        {
            if ((j + i) % n == 1)
                Console.ForegroundColor = ConsoleColor.Red;

            Console.Write(" {0,-2} ", (j + i) % n);
            Console.ForegroundColor = ConsoleColor.White;
        }
        Console.WriteLine();
    }

    #region FormatView
    Console.WriteLine("\n");
    for (int i = 0; i < n * 2-2; i++)
        Console.Write(" ");

    Console.WriteLine("MULTIPLICATION TABLE");
    Console.Write("   ");

    for (int i = 0; i < n; i++)
        Console.Write("----");
    
    Console.WriteLine();
    Console.Write("    ");

    for (int i = 0; i < n; i++)
        Console.Write(" {0,-2} ", i);
    Console.WriteLine();
    Console.Write("   ");

    for (int i = 0; i < n; i++)
        Console.Write("----");
    
    Console.WriteLine();
    #endregion

    // MULTIPLICATION TABLE
    for (int i = 0; i < n; i++)
    {
        Console.Write("{0,-3}|", i);
        for (int j = 0; j < n; j++)
        {
            if ((j * i) % n == 1)
                Console.ForegroundColor = ConsoleColor.Red;
          
            Console.Write(" {0,-2} ", (j * i) % n);
            Console.ForegroundColor = ConsoleColor.White;
        }
        Console.WriteLine();
    }

    #region FormatView
    Console.Write("   ");
    for (int i = 0; i < n; i++)
    {
        Console.Write("----");
    }
    #endregion
}
#endregion

#region EilerFunction
static int EilerFunction(int n)
{
    var factorization = Factorization(n);
    int result = 1;

    foreach (var value in factorization)
        result *= value.Item2 - (value.Item2 / value.Item1);

    return result;
}
#endregion

#region InverseClass
static int InverseClass(int m, int n)
{
    n %= m;

    if (NODEuclidean(m, n) != 1)
    {
        Console.WriteLine("\n\nN not invertible in the ring of the residue class mod M (InverseClass)");
        return -1;
    } 
        
    for (int i = 0; i < m; i++)
    {
        if ((i * n) % m == 1)
        {
            return i;
        }
    }
    return 0;
}
#endregion

#region InverseBezu
static int InverseBezu(int m, int n)
{
    n %= m;

    if (NODEuclidean(m, n) != 1)
    {
        Console.WriteLine("\nN not invertible in the ring of the residue class mod M (InverseBezu)");
        return -1;
    }

    var temp = IdentityBezu(m, n);
    return (temp.Item2 + m) % m;
}
#endregion

#region Factorization2.0
static List<(int, int)> Factorization(int n) // v. 2.0
{// Factorization 2.0 - returns list of prime multipliers
    List<(int, int)> factorizationList = new List<(int, int)>();
    int div = 2;
    while (n > 1)
    {
        if (n % div == 0)
        {
            var temp = (div, 1);
            while (n % div == 0)
            {
                temp.Item2 *= div;
                n = n / div;
            }
            factorizationList.Add(temp);
        }
        div++;
    }
    return factorizationList;
}
#endregion

#region IdentityBezu
static (int, int) IdentityBezu(int a, int b)
{
    int temp;

    // SIGN CHECK
    var key = false;
    if (a < b)
    {
        (a, b) = (b, a);
        key = true;
    }

    // CREATE Q-COEFFICIENT LIST
    List<int> q = new();

    // RUN DOWN (EUCLIDEAN ALGORITHM)
    while ((temp = a % b) > 0)
    {
        q.Add(a / b);
        a = b;
        b = temp;
    }

    var result = (u: 0, v: 1);

    // RUN UP
    for (var i = q.Count - 1; i >= 0; i--)
    {
        temp = result.u;
        result.u = result.v;
        result.v = temp - result.v * q[i];
    }

    if (key)
    {
        (result.u, result.v) = (result.v, result.u);
    }

    return result;
}
#endregion

#region NODEuclidian
static int NODEuclidean(int a, int b)
{
    while (a != b)
    {
        if (a > b)
            a -= b;
        else
            b -= a;
    }
    return a;
}
#endregion


