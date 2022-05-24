using System;
using System.Collections.Generic;
using static NumbersTheory.NumbersTheory;

namespace NumbersTheory
{
    class NumbersTheory
    {
        #region Factorization1.0
        public static List<ulong> Factorization1(ulong number)
        {
            List<ulong> ListOfMultipliers = new();
            ulong multiplier = 2; // Первый множитель в списке простых чисел -- 2
            while (number > 1) // Пока введённое число больше 1
            {
                if (number % multiplier == 0) // Если делится на простой множитель
                {
                    number /= multiplier; // Делим
                    ListOfMultipliers.Add(multiplier); // Множитель добавляем в список
                }
                else
                    multiplier++; // Или увеличиваем множитель на 1
            }
            return ListOfMultipliers;
        }
        #endregion

        #region Factorization2.0
        public static List<(ulong, ulong)> Factorization(ulong n) // v. 2.0
        {// Factorization 2.0 - returns list of prime multipliers
            List<(ulong, ulong)> factorizationList = new List<(ulong, ulong)>();
            ulong div = 2;
            while (n > 1)
            {
                if (n % div == 0)
                {
                    var temp = ((ulong)div,(ulong) 1);
                    while (n % div == 0)
                    {
                        temp.Item2 *= (ulong) div;
                        n = n / div;
                    }
                    factorizationList.Add(temp);
                }
                div++;
            }
            return factorizationList;
        }
        #endregion

        #region NODEuclidean
        public static ulong NODEuclidean( ulong a,  ulong b)
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

        #region EilerFunction
        public static ulong EilerFunction(ulong n)
        {
            var factorization = Factorization(n);
            ulong result = 1;

            foreach (var value in factorization)
                result *= value.Item2 - (value.Item2 / value.Item1);

            return result;
        }
        #endregion

        #region DegreeRemainder1
        public static ulong DegreeRemainder1(ulong a, ulong s, ulong m)
        { // a^s mod m
            char[] degreeBinaryCode = Convert.ToString((uint)s, 2).ToCharArray();
            Array.Reverse(degreeBinaryCode);

            ulong[] remainders = new ulong[degreeBinaryCode.Length];

            remainders[0] = a % m;

            for (int i = 1; i < degreeBinaryCode.Length; i++)
                remainders[i] = (remainders[i - 1] * remainders[i - 1]) % m;

            ulong res = 1;
            for (int i = 0; i < degreeBinaryCode.Length; i++)
            {
                if (degreeBinaryCode[i] == '1')
                {
                    res *= remainders[i];
                    res %= m;
                }
            }

            return res % m;
        }
        #endregion

        #region DegreeRemainder2
        public static ulong DegreeRemainder2(ulong a, ulong m, ulong n)
        {
            if (m == 0)
            {
                return 1;
            }

            ulong y = DegreeRemainder2(a, m / 2, n);
            ulong ret = (y * y) % n;
            return (m % 2 == 0) ? ret : (ret * (a % n)) % n;
        }
        #endregion

        #region IdentityBezu.v.2.0
        public static void IdentityBezu(ulong a, ulong b, ref ulong u, ref ulong v)
        {
            List<ulong> r = new List<ulong>() { (ulong)a, (ulong)b };
            List<ulong> s = new List<ulong>() { 1, 0 };
            List<ulong> t = new List<ulong>() { 0, 1 };
            for (int i = 1; r[i] != 0; i++)
            {
                ulong q = r[i - 1] / r[i];
                r.Add(r[i - 1] - (ulong)q * r[i]);
                s.Add(s[i - 1] - (ulong)q * s[i]);
                t.Add(t[i - 1] - (ulong)q * t[i]);
            }
            u = s[s.Count - 2];
            v = t[t.Count - 2];
        }
        #endregion

        #region IdentityBezu
        static (ulong, ulong) IdentityBezu(ulong a, ulong b)
        {
            ulong temp;

            // SIGN CHECK
            var key = false;
            if (a < b)
            {
                (a, b) = (b, a);
                key = true;
            }

            // CREATE Q-COEFFICIENT LIST
            List<ulong> q = new();

            // RUN DOWN (EUCLIDEAN ALGORITHM)
            while ((temp = a % b) > 0)
            {
                q.Add(a / b);
                a = b;
                b = temp;
            }

            var result = (u: (ulong)0, v: (ulong)1);

            // RUN UP
            for (var i = q.Count - 1; i >= 0; i--)
            {
                temp = (ulong) result.u;
                result.u = result.v;
                result.v = (temp - result.v * q[i]);
            }

            if (key)
            {
                (result.u, result.v) = (result.v, result.u);
            }

            return result;
        }
        #endregion

        #region MillerRabinTest
        public class MillerRabinTest
        {
            private static ulong ModPow(ulong a, ulong n, ulong m)
            {
                ulong res = 1;
                while (n != 0)
                {
                    if (n % 2 != 0)
                    {
                        res *= a;
                        res %= m;
                    }
                    a *= (a % m);
                    a %= m;
                    n >>= 1;
                }
                return res % m;
            }

            public static bool IsPrime(ulong n, ulong k)
            {
                if (n is 1 or 2 or 3) return true;
                // представим n − 1 в виде (2^s)·t, где t нечётно, это можно сделать последовательным делением n - 1 на 2
                ulong t = n - 1;
                ulong s = 0;
                while (t % 2 == 0)
                {
                    t = t / 2;
                    s += 1;
                }
                // повторить k раз
                for (int i = 0; i < (uint)k; i++)
                {
                    // выберем случайное целое число a в отрезке [2, n − 2]
                    Random rnd = new Random();
                    int a = rnd.Next(2, (int) (n - 2));
                    // x ← a^t mod n, вычислим с помощью возведения в степень по модулю
                    ulong x = ModPow((ulong)a, t, n);

                    // если x == 1 или x == n − 1, то перейти на следующую итерацию цикла
                    if (x == 1 || x == n - 1)
                    {
                        continue;
                    }
                    // повторить s − 1 раз
                    for (ulong r = 1; r < s; r++)
                    {
                        // x ← x^2 mod n
                        x = ModPow(x, 2, n);

                        // если x == 1, то вернуть "составное"
                        if (x == 1)
                            return false;

                        // если x == n − 1, то перейти на следующую итерацию внешнего цикла
                        if (x == n - 1)
                            break;
                    }
                    if (x != n - 1)
                        return false;


                }
                return true;
            }

        }

        #endregion

        #region InverseClass
        public static ulong InverseClass(ulong m, ulong n)
        {
            n %= m;

            if (NODEuclidean(m, n) != 1)
            {
                Console.WriteLine("\n\nN not invertible in the ring of the residue class mod M (InverseClass)");
                return 404;
            }

            for (ulong i = 0; i < m; i++)
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
        public static ulong InverseBezu(ulong m, ulong n)
        {
            n %= m;

            if (NODEuclidean(m, n) != 1)
            {
                Console.WriteLine("\nN not invertible in the ring of the residue class mod M (InverseBezu)");
                return 404;
            }

            var temp = IdentityBezu((ulong)m, (ulong) n);
            return (temp.Item2 + m) % m;
        }
        #endregion

    }
}