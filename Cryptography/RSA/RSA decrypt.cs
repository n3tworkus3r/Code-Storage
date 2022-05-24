using System;
using System.Text;
using CryptRSA;
using System.Collections.Generic;
using static NumbersTheory.NumbersTheory;

Console.WriteLine("\n\t\tDECRYPT:");
Console.WriteLine($"\ta) m = {RSA.Decrypt(21, 7, 2 )}");
Console.WriteLine($"\tб) m = {RSA.Decrypt(2021, 11, 1791)}");
Console.WriteLine($"\tв) m = {RSA.Decrypt(250483, 13, 242215)}");


Console.WriteLine("\n\t\tENCRYPT:");

#region a)NFactorization
List<ulong> pq = Factorization1(21);
var p = pq[0];
var q = pq[1];
#endregion
Console.WriteLine($"\ta) c = {RSA.Encrypt(RSA.Decrypt(21, 7, 2), p, q, 7)}");

#region b)NFactorization
pq = Factorization1(2021);
//foreach (ulong i in pq) Console.WriteLine(i);
p = pq[0];
q = pq[1];
#endregion
Console.WriteLine($"\tб) c = {RSA.Encrypt(RSA.Decrypt(2021, 11, 1791), p, q, 11)}");

#region c)NFactorization
pq = Factorization1(250483);
//foreach (ulong i in pq) Console.WriteLine(i);
p = pq[0];
q = pq[1];
#endregion
Console.WriteLine($"\tб) c = {RSA.Encrypt(RSA.Decrypt(250483, 13, 242215), p, q, 13)}");
namespace CryptRSA {
    static class RSA {

        #region Values
        private static void SelectingValues(ulong c, ref ulong p, ref ulong q, ref ulong e) {
            /* Get n */
            ulong n;
            p = 2;
            q = 3;
            ulong currentPrimePoint = 1;
            do {
                while(true) {
                    if (MillerRabinTest.IsPrime(currentPrimePoint, 20)) {
                        p = currentPrimePoint;
                        currentPrimePoint++;
                        break;
                    } else {
                        currentPrimePoint++;
                    }
                }

                while (true) {
                    if (MillerRabinTest.IsPrime(currentPrimePoint, 20)) {
                        q = currentPrimePoint;
                        currentPrimePoint++;
                        break;
                    } else {
                        currentPrimePoint++;
                    }
                }

                n = p * q;
            } while (n < c || NODEuclidean(c,  n) != 1);

            /* Get e */
            ulong eulerFunkN = EilerFunction(n);
            e = 2;
            while (NODEuclidean( e,  eulerFunkN) != 1) {
                e++;
            }
        }

        #endregion

        public static ulong Encrypt(ulong m, ulong p, ulong q, ulong e) {
            // CHECK TO VALID PARAMETERS //
            /* Variables */
            ulong n = p * q;
            ulong eulerFunkN;
            /* c < n && NOD(c, n) == 1 */
            if (m >= n) {
                Console.WriteLine("Bad data! {0} < {1} (c < n)", m, n);
                return 0;
            }
            if (NODEuclidean(m, n) != 1) {
                Console.WriteLine("Bad data! NOD({0}, {1}) == 1 (NOD(c, n) == 1)", m, n);
                return 0;
            }
            /* 0 < e < n && NOD(e, f(n)) == 1 */
            if (e < 0 || e > n) {
                Console.WriteLine("Bad data! 0 < {0} < {1} (0 < e < n)", e, n);
                return 0;
            }
            eulerFunkN = EilerFunction(n);
            if (NODEuclidean(e,  eulerFunkN) != 1) {
                Console.WriteLine("Bad data! NOD({0}, {1}) == 1 (NOD(e, f(n)) == 1)", e, eulerFunkN);
                return 0;
            }
            // SHOW OPEN KEY // 
            //Console.WriteLine("\tOPEN KEY (n, e) --- ({0}, {1})", n, e);
            // CACLULATE CHIPHER //
            /* ALGORITHM */
            ulong h = DegreeRemainder2(m, e, n);
            // RETURN //
            //Console.WriteLine("\tn = {0}, e = {1}, c = {2}", n, e, h);
            return h;
        }
        public static ulong Encrypt(ulong m) {
            ulong p = 0, q = 0, e = 0;
            SelectingValues(m, ref p, ref q, ref e);
            return Encrypt(m, p, q, e);
        }
        public static ulong Decrypt(ulong n, ulong e, ulong h) {
            // VARIABLES //
            ulong eulerFunkN = EilerFunction(n);
            ulong u = 0, v = 0;
            ulong d; // Secret key 'd'
            // ALGORITHM //
            /* Find Secrey key 'd' */
            IdentityBezu(eulerFunkN, e, ref u, ref v);
            //d = v + eulerFunkN;
            var f = EilerFunction(n);
            d = InverseClass(f, e);//+ EilerFunction(n);
            /* Decrypting */
            ulong c = DegreeRemainder1(h, d, n);
            // RETURN //
            return c;
        }

        public static String ToText(string chipher) {
            String alphanet = " abcdefghijklmnopqrstuvwxyz";
            //String chipher = c.ToString();
            StringBuilder text = new StringBuilder();
            
            if (chipher.Length % 2 == 0 ) {
                chipher = chipher.Insert(0, "0");
            }

            for (int i = 0; i < chipher.Length; i += 2) {
                int index = Convert.ToInt32(chipher.Substring(i, 2)) % 26;
                text.Append(alphanet[index]);
            }

            return text.ToString();
        }
    }
}
