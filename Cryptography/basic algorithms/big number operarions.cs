using System;
using System.Collections.Generic;
using System.Linq;



class Program
{
    static void Main()
    {
        Console.WriteLine("\n\tOPERATIONS:\n");
        
        BigNumberOperations.BigNumber U = new("11000", 2);
        BigNumberOperations.BigNumber V = new("11", 2);
        Console.WriteLine($"{U} + {V} = {U + V}");
        Console.WriteLine($"{U} - {V} = {U - V}");
        Console.WriteLine($"{U} * {V} = {U * V}");
        Console.WriteLine($"{U} / {V} = {U / V}");
        
        BigNumberOperations.BigNumber P = new("617", 10);
        BigNumberOperations.BigNumber C = new("618", 10);

        Console.WriteLine("\n\tMILLER-RABIN TEST:\n");

        if (P.MillerRabinTest(20)) 
            Console.WriteLine($"Number {P} is prime\n");
        else 
            Console.WriteLine($"Number {P} is composite\n");

        if (C.MillerRabinTest(20)) 
            Console.WriteLine($"Number {C} is prime\n");
        else
            Console.WriteLine($"Number {C} is composite\n");

        BigNumberOperations.BigNumber A = new("13", 10);
        BigNumberOperations.BigNumber B = new("8", 10); ;
        Console.WriteLine($"\n\tIDENTITY BEZU:\n{A}*u + {B}*v --> (u,v) = " + BigNumberOperations.BigNumber.IdentityBezu(A,B));
    }

}
namespace BigNumberOperations
{
    public class BigNumber : IComparable, IComparable<BigNumber>, IEquatable<BigNumber>
    {
        #region ApplicatedFields

        ////////////////////////// Properties //////////////////////////

        public int Length => numberList.Count;

        public int this[int index] => numberList[index];


        ////////////////////////// Public constructors //////////////////////////

        public BigNumber(string numberInString, int Base)
        {
            if (numberInString.Length == 0)
            {
                throw new ArgumentNullException(numberInString, "Cannot create U from empty string");
            }

            numberList = new List<int>();
            if (numberInString[0] == '-')
            {
                sign = false;
                numberInString = numberInString.TrimStart('-');
            }
            foreach (var c in numberInString)
            {
                numberList.Add(CharToInt(c));
            }
            numberList.Reverse();
            this.Base = Base;
        }

        // OVERLOADING CONSTRUCTOR (WITHOUT BASE)
        //public BigNumber(string numberInString, int Base) : this(numberInString) { }

        public BigNumber(int value)
        {
            numberList = new List<int>();
            if (value == 0)
            {
                numberList.Add(0);
            }
            else
            {
                if (value < 0)
                {
                    sign = false;
                }
                value = Math.Abs(value);
                while (value > 0)
                {
                    numberList.Add(value % 10);
                    value /= 10;
                }
            }
        }

        public BigNumber()
        {
            numberList = new List<int>();
        }


        /* ----------------- Convertations to any U systems --------------------- */

        private static char IntToChar(int c)
        {
            if (c is >= 0 and <= 9)
            {
                return (char)(c + '0');
            }

            return (char)(c + 'A' - 10);
        }

        private static int CharToInt(char c)
        {
            if (c is >= '0' and <= '9')
            {
                return c - '0';
            }

            return c - 'A' + 10;
        }

        private int NextNumber(int final)
        {
            var temp = 0;
            for (var i = numberList.Count - 1; i >= 0; i--)
            {
                temp = temp * Base + numberList[i];
                numberList[i] = temp / final;
                temp %= final;
            }
            return temp;
        }

        public BigNumber ConvertTo(int final)
        {
            BigNumber Returned = new()
            {
                Base = final
            };
            var temp = Copy();
            do
            {
                Returned.numberList.Add(temp.NextNumber(final));
            } while (!temp.EqualsToZero());
            Returned.sign = sign;
            return Returned;
        }

        /* ------------------------------- Constants --------------------------------- */

        public static readonly BigNumber Zero = 0;

        public static readonly BigNumber One = 1;

        /* ------------------------- Public operators -------------------------------- */

        public static implicit operator BigNumber(int value) => new(value);

        //public static implicit operator BigNumber(string value) => new(value);

        public static BigNumber operator +(BigNumber first, BigNumber second)
        {
            return first.Add(second);
        }

        public static BigNumber operator -(BigNumber first, BigNumber second)
        {
            return first.Sub(second);
        }

        public static BigNumber operator *(BigNumber first, BigNumber second)
        {
            return first.Mul(second);
        }

        public static BigNumber operator /(BigNumber first, BigNumber second)
        {
            return first.Div(second);
        }

        public static BigNumber operator %(BigNumber first, BigNumber second)
        {
            return first.FindRemainder(second);
        }

        public static BigNumber operator ++(BigNumber first)
        {
            return first.Inc();
        }

        public static BigNumber operator --(BigNumber first)
        {
            return first.Dec();
        }

        public static BigNumber operator <<(BigNumber first, int value)
        {
            return first.ShiftL(value);
        }

        public static BigNumber operator >>(BigNumber first, int value)
        {
            return first.ShiftR(value);
        }

        public static BigNumber operator ^(BigNumber first, BigNumber second)
        {
            return first.Xor(second);
        }

        public static bool operator ==(BigNumber first, BigNumber second)
        {
            return first is not null && first.CompareTo(second) == 0;
        }

        public static bool operator !=(BigNumber first, BigNumber second)
        {
            return first is not null && first.CompareTo(second) != 0;
        }

        public static bool operator <(BigNumber first, BigNumber second)
        {
            return first.CompareTo(second) == -1;
        }

        public static bool operator >(BigNumber first, BigNumber second)
        {
            return first.CompareTo(second) == 1;
        }

        public static bool operator <=(BigNumber first, BigNumber second)
        {
            return first.CompareTo(second) != 1;
        }

        public static bool operator >=(BigNumber first, BigNumber second)
        {
            return first.CompareTo(second) != -1;
        }

        #endregion

        private readonly List<int> numberList;
        private bool sign = true;
        private int Base = 2;

        ////////////////////////// OPERATIONS //////////////////////////

        public BigNumber Add(BigNumber other)
        {
            #region  SignCheck
            switch (sign)
            {
                case true when !other.sign:
                    other.sign = true;
                    return Sub(other);
                case false when other.sign:
                    sign = true;
                    return other.Sub(this);
            }
            
            var V = Base != other.Base ? other.ConvertTo(Base) : other.Copy();
            #endregion

            #region PrepareAdd
            BigNumber addend;
            BigNumber returned;
            if (Abs(this) >= Abs(V))
            {
                returned = Copy();
                addend = V.Copy();
                returned.numberList.Add(0);
            }
            else
            {
                returned = V.Copy();
                addend = Copy();
                returned.numberList.Add(0);

            }
            if (!addend.EqualsToZero())
                addend.numberList.TrimEnd(0);

            for(int i = 0; i < addend.numberList.Count+1; i++)
                returned.numberList.Add(0);
            
            var k = returned.numberList.Count;

            #endregion

            // 1) C <--0
            var c = 0;

            // 2) FOR i = 0, ... k-1
            for (var i = addend.numberList.Count; i < k; i++)
                addend.numberList.Add(0);
            
            for (var i = 0; i < k; i++)
            {
                // 2a) Wi = (Ui + Vi +C) mod B
                var Wi = (returned.numberList[i] + addend.numberList[i] + c) % Base;

                // 2б) C <-- 0 IF Ui + Vi + C < B
                if (returned.numberList[i] + addend.numberList[i] + c >= Base)
                    c = 1;
                else
                    c = 0;
                
                returned.numberList[i] = Wi;
                
            }

            // ADD 1 IN HIGH BIT
            if (c > 0)
                    returned.numberList[k-1] = 1;

            // DELETING SPACES
            while (returned.numberList[k - 1] == 0)
            {
                returned.numberList.RemoveAt(k - 1);
                k--;
            }
               
            return returned;
        }

        ////////////////////////////////////////////////////////////////

        public BigNumber Sub(BigNumber other)
        {

            #region PrepareSub
            var V = Base != other.Base ? other.ConvertTo(Base) : other.Copy();

            BigNumber returned;
            BigNumber deductible;
            bool newSign;

            switch (sign)
            {
                case true when !other.sign:
                    other.sign = true;
                    return Add(other);
                case false when other.sign:
                    other.sign = false;
                    return other.Add(this);
            }


            if (Abs(this) >= Abs(V))
            {
                returned = Copy();
                deductible = V.Copy();
                newSign = sign;
            }
            else
            {
                returned = V.Copy();
                deductible = Copy();
                newSign = !sign;
            }
            #endregion

            // 1) C <-- 0
            var c = 0;

            // 2) FOR i = 0, ... k-1
            for (var i = 0; i < returned.numberList.Count; i++)
            {
                int Wi;
                if (i < deductible.numberList.Count)
                    // Wi <-- Ui - Vi - C
                    Wi = returned.numberList[i] - deductible.numberList[i] - c;
                else
                    Wi = returned.numberList[i] - c;
                // C <-- 1 IF Ui - Vi + C ?= 0
                c = (Wi >= 0) ? 0 : 1;

                returned.numberList[i] = ((Wi + Base) % Base);
            }

            #region Check

            if (!returned.EqualsToZero())
                returned.numberList.TrimEnd(0);
            returned.sign = newSign;
            #endregion

            return returned;
        }

        ////////////////////////////////////////////////////////////////

        public BigNumber Mul(BigNumber other)
        {

            #region PrepareMul
            var V = Base != other.Base ? other.ConvertTo(Base) : other.Copy();

            BigNumber Wi = new() { Base = Base };

            var length = numberList.Count + V.numberList.Count;

            #endregion
            // 1) FOR i = 0, ..., k+l-1     Wi <-- 0
            for (var i = 0; i < length; i++)
                Wi.numberList.Add(0);

            // 2) FOR i = 0, ..., l-1 
            for (var i = 0; i < V.numberList.Count; i++)
            {
                // 2a) C <-- 0
                var c = 0;
                // 2б) j = 0, ... k-1  
                for (var j = 0; j < numberList.Count; j++)
                {
                    //  xy <-- Wi+j + Uj*Vi + C 
                    var xy = Wi.numberList[i + j] + numberList[j] * V.numberList[i] + c;

                    // Wi <-- Y
                    Wi.numberList[i + j] = xy % Base;
                    // C <-- X
                    c = xy / Base;
                }

                // Wi+k <-- C
                Wi.numberList[i + numberList.Count] = c;
            }

            #region Check
            if (!Wi.EqualsToZero())
                Wi.numberList.TrimEnd(0);
            else
            {
                Wi = Zero.Copy();
            }
            Wi.sign = !(sign ^ other.sign);
            #endregion

            return Wi;
        }

        ////////////////////////////////////////////////////////////////

        public BigNumber Div(BigNumber other)
        {
            if (other.EqualsToZero())
                throw new DivideByZeroException("Cannot divide by zero");
            #region Transform
            (BigNumber U, BigNumber V) = other.numberList.Count < 2  ?
                (ConvertTo(2), other.ConvertTo(2)) :
                (Copy(), Base != other.Base ? other.ConvertTo(Base) : other.Copy());

            if (V.EqualsToOne())
                return Copy();

            var result = new BigNumber  {  Base = U.Base  };
            for (int i = 0, resultLength = U.numberList.Count - V.numberList.Count; i <= resultLength; i++)
                result.numberList.Add(0);

            var k = V.numberList.Count;
            #endregion

            // 1) D CALCULATING
            var d = U.Base / (V.numberList[^1] + 1);


            // 1a) U = U*D
            var u = U.Mul2(new BigNumber(d.ToString(), U.Base));
            // 1b) V = V*D
            var v = V.Mul(new BigNumber(d.ToString(), U.Base));

            // 2)
            for (var i = U.numberList.Count; i >= k; i--)
            {
                // 2a) TRIAL Q
                var trialQ = Math.Min((U.Base * u.numberList[i] + u.numberList[i - 1]) / v.numberList[k - 1], U.Base - 1);

                // 2б) FIXING Q
                while ((trialQ * (v.numberList[k - 1] * U.Base + v.numberList[k - 2])) > 
                    (U.Base * U.Base * u.numberList[i] + U.Base * u.numberList[i - 1] + u.numberList[i - 2]))
                    trialQ -= 1;


                // 2в)  TRANSFORM U
                u = u.Sub2(v.ShiftL(i - k).Mul(new BigNumber(IntToChar(trialQ).ToString(), Base)));

                // 2г) CORRECTIVE ADDITING
                if (!u.sign)
                {
                    u = v.ShiftL(i - k).Add(u);
                    trialQ -= 1;
                }

                result.numberList[i - k] = trialQ;
            }
            if (!result.EqualsToZero())
                result.numberList.TrimEnd(0);
            result.sign = !(sign ^ other.sign);

            return result.ConvertTo(Base);
        }

        ////////////////////////////////////////////////////////////////


        #region ApplecatedOpreations
        public BigNumber ShiftL(int value)
        {
            var Returned = Copy();
            Returned.numberList.Reverse();
            for (var i = 0; i < value; i++)
                Returned.numberList.Add(0);
            Returned.numberList.Reverse();
            return Returned;
        }

        public BigNumber ShiftR(int value)
        {
            var Returned = Copy();
            Returned.numberList.RemoveRange(0, value);
            return Returned;
        }

        public BigNumber Xor(BigNumber other)
        {
            bool wasConverted = false;
            BigNumber tempThis;
            if (this.Base != 2)
            {
                tempThis = this.ConvertTo(2);
                wasConverted = true;
            }
            else
            {
                tempThis = this.Copy();
            }

            var V = tempThis.Base != other.Base ? other.ConvertTo(tempThis.Base) : other.Copy();
            BigNumber Returned;
            if (tempThis.Length > V.Length)
            {
                Returned = tempThis.Copy();
            }
            else
            {
                Returned = V.Copy();
                V = tempThis.Copy();
            }
            var size = V.Length;
            for (var i = 0; i < size; i++)
            {
                Returned.numberList[i] ^= V[i];
            }

            if (!Returned.EqualsToZero())
            {
                Returned.numberList.TrimEnd(0);
            }

            if (wasConverted)
            {
                Returned = Returned.ConvertTo(this.Base);
            }
            return Returned;
        }

        public BigNumber Dec()
        {
            return this.Sub(One);
        }

        public BigNumber Inc()
        {
            return this.Add(One);
        }

        public BigNumber FindRemainder(BigNumber other)
        {
            var V = Base != other.Base ? other.ConvertTo(Base) : other.Copy();

            var temp = Div(V).Mul(V);
            var Returned = Sub(temp);

            return Returned.EqualsToZero() ? 0 : Returned;
        }

        public static BigNumber Abs(BigNumber U)
        {
            var Returned = U.Copy();
            Returned.sign = true;
            return Returned;
        }

        public BigNumber Pow(BigNumber power)
        {
            if (!power.sign)
            {
                throw new ArgumentException("Power must be positive or zero", nameof(power));
            }

            var binaryM = power.ConvertTo(2);

            List<BigNumber> binaryDegrees = new()
            {
                Copy()
            };

            for (var i = 1; i < binaryM.Length; i++)
            {
                binaryDegrees.Add(binaryDegrees[i - 1] * binaryDegrees[i - 1]);
            }
            BigNumber Returned = 1;
            for (var i = 0; i < binaryM.Length; i++)
            {
                if (binaryM[i] == 1)
                {
                    Returned *= binaryDegrees[i];
                }
            }
            return Returned;
        }

        public static BigNumber Random(BigNumber min, BigNumber max)
        {
            Random rand = new();
            var tempMin = !min.sign ? Zero.Copy() : min.Copy();

            var size = rand.Next(tempMin.numberList.Count, max.numberList.Count);
            BigNumber Returned;
            do
            {
                Returned = new BigNumber()
                {
                    Base = min.Base
                };

                for (var i = 0; i < size; i++)
                {
                    Returned.numberList.Add(rand.Next(0, min.Base));
                }
                if (!Returned.EqualsToZero())
                    Returned.numberList.TrimEnd(0);
            } while (Returned > max || Returned < tempMin);

            return Returned;
        }

        public BigNumber DegreeRemainder(BigNumber power, BigNumber m)
        {
            var binaryM = power.ConvertTo(2);

            List<BigNumber> binaryDegrees = new()
            {
                this % m
            };

            for (var i = 1; i < binaryM.Length; i++)
            {
                binaryDegrees.Add((binaryDegrees[i - 1] * binaryDegrees[i - 1]) % m);
            }
            BigNumber ret = 1;
            for (var i = 0; i < binaryM.Length; i++)
            {
                if (binaryM[i] != 1) continue;
                ret *= binaryDegrees[i];
                ret %= m;
            }
            return ret;
        }

        #endregion

        #region HelpForDivision

        private BigNumber Mul2(BigNumber other)
        {
            var V = Base != other.Base ? other.ConvertTo(Base) : other.Copy();
            var Returned = new BigNumber { Base = Base };

            var length = numberList.Count + V.numberList.Count;
            for (var i = 0; i < length; i++)
            {
                Returned.numberList.Add(0);
            }
            for (var i = 0; i < V.numberList.Count; i++)
            {
                var c = 0;
                for (var j = 0; j < numberList.Count; j++)
                {
                    var temp = Returned.numberList[i + j] + numberList[j] * V.numberList[i] + c;
                    Returned.numberList[i + j] = temp % Base;
                    c = temp / Base;
                }
                Returned.numberList[i + numberList.Count] = c;
            }
            return Returned;
        }

        private BigNumber Sub2(BigNumber other)
        {
            var V = Base != other.Base ? other.ConvertTo(Base) : other.Copy();

            BigNumber Returned;
            BigNumber deductible;
            var newSign = true;
            if (this >= V)
            {
                Returned = Copy();
                deductible = V.Copy();
            }
            else
            {
                Returned = V.Copy();
                Returned.numberList.TrimEnd(0);
                deductible = Copy();
                newSign = false;
            }
            var c = 0;
            for (var i = 0; i < Returned.numberList.Count; i++)
            {
                int sum;
                if (i < deductible.numberList.Count)
                    sum = Returned.numberList[i] - deductible.numberList[i] - c;
                else
                    sum = Returned.numberList[i] - c;
                c = sum >= 0 ? 0 : 1;
                Returned.numberList[i] = ((sum + Base) % Base);
            }
            Returned.sign = newSign;
            return Returned;
        }

        #endregion

        //////////////////////////////// MILLER-RABIN TEST ////////////////////////////////

        public bool MillerRabinTest(int T)
        {
            var decN = Dec();
            var two = Base > 2 ? new BigNumber("2", Base) : new BigNumber("10", Base);
            var s = 0;
            var r = decN.Copy();


            // 1) 2^s * R + 1
            while (r.IsDivisibleByTwo())
            {
                r /= two;
                s++;
            }

            // 2) 
            for (var t = 1; t <= T; t++)
            {
                // 2.1)
                var u = Random(two, decN.Dec());

                // 2.2)
                var v = u.DegreeRemainder(r, this);

                // 2.3)
                if (v.EqualsToOne() || v.Equals(decN)) continue;
                var key = true;

                // 2.4) FOR i = 1,2 ... S-1
                for (var i = 1; i <= s - 1 && key; i++)
                {
                    // 2.4a) V <-- V^2 mod N
                    v = v.Mul(v).FindRemainder(this);

                    // 2.4b) IF V = 1
                    if (v.EqualsToOne())
                        return false;
                    
                    // 2.4c) IF V = N - 1
                    if (v.Equals(decN))
                        key = false;
                }
               
                if (key) // 2.6) CONTINUE
                    return false; // 2.5) NUMBER IS COMPOSITE
            }
            return true; // 3) NUMBER IS PRIME
        }

        ///////////////////////////////////////////////////////////////////////////////////


        public static (BigNumber, BigNumber) IdentityBezu(BigNumber a, BigNumber b)
        {
            BigNumber temp;

            // SIGN CHECK
            var key = false;
            if (a < b)
            {
                (a, b) = (b, a);
                key = true;
            }

            // CREATE Q-COEFFICIENT LIST
            List<BigNumber> q = new();

            // RUN DOWN (EUCLIDEAN ALGORITHM)
            while ((temp = a % b) > 0)
            {
                q.Add(a / b);
                a = b;
                b = temp;
            }

            var result = ( u : new BigNumber(0), v : new BigNumber(1));

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

        ///////////////////////////////////////////////////////////////////////////////////
        
        #region OtherOperations 

        public bool IsDivisibleByTwo()
        {
            if (Base % 2 == 0)
                return (numberList[0] % 2) == 0;
            var sum = numberList.Sum();
            return (sum % 2) == 0;
        }

        public static BigNumber NodEuclidean(BigNumber a, BigNumber Base)
        {
            BigNumber temp;
            if (a < Base)
            {
                (a, Base) = (Base, a);
            }
            while (!(temp = a % Base).EqualsToZero())
            {
                a = Base.Copy();
                Base = temp.Copy();
            }
            return Base;
        }

        public static BigNumber InverseBezu(BigNumber n, BigNumber m)
        {
            n %= m;

            if (NodEuclidean(m, n) != 1)
            {
                return -1;
            }

            var temp = IdentityBezu(m, n);
            return (temp.Item2 + m) % m;
        }

        /* ------------------------------ Compare methods ---------------------------- */

        public bool EqualsToZero()
        {
            var Returned = true;
            var i = 0;
            while (Returned && i < numberList.Count)
            {
                Returned = numberList[i] == 0;
                i++;
            }
            return Returned;
        }

        public bool EqualsToOne()
        {
            return (numberList.Count == 1 && numberList[0] == 1);
        }

        public bool Equals(BigNumber other)
        {
            if (other is null)
            {
                throw new NullReferenceException("Parameter cannot be null");
            }

            if (sign != other.sign)
            {
                return false;
            }

            var V = Base != other.Base ? other.ConvertTo(Base) : other.Copy();

            var Returned = true;
            if (numberList.Count == V.numberList.Count)
            {
                for (var i = 0; i < numberList.Count && Returned; i++)
                {
                    Returned = numberList[i] == V.numberList[i];
                }
            }
            else
            {
                return false;
            }

            return Returned;
        }

        public override bool Equals(object obj)
        {
            if (ReferenceEquals(this, obj))
            {
                return true;
            }

            if (obj is null)
            {
                return false;
            }

            var temp = obj as BigNumber;

            return temp != null && Equals(temp);
        }

        public int CompareTo(BigNumber other)
        {
            if (other is null)
            {
                return 1;
            }

            switch (this.sign)
            {
                case true when !other.sign:
                    return 1;
                case false when other.sign:
                    return -1;
            }

            var returnSign = (this.sign) ? 1 : -1;


            var V = Base != other.Base ? other.ConvertTo(Base) : other.Copy();

            var tempThis = Copy();
            if (!tempThis.EqualsToZero())
                tempThis.numberList.TrimEnd(0);
            else
                tempThis = Zero.Copy();
            if (!V.EqualsToZero())
                V.numberList.TrimEnd(0);
            else
                V = Zero.Copy();

            if (tempThis.numberList.Count < V.numberList.Count)
            {
                return -1 * returnSign;
            }

            if (tempThis.numberList.Count > V.numberList.Count)
            {
                return 1 * returnSign;
            }


            for (var i = tempThis.numberList.Count - 1; i >= 0; i--)
            {
                if (tempThis.numberList[i] > V.numberList[i])
                {
                    return 1 * returnSign;
                }
                if (tempThis.numberList[i] < V.numberList[i])
                {
                    return -1 * returnSign;
                }
            }

            return 0;
        }

        public int CompareTo(object obj)
        {
            if (obj is not BigNumber other)
            {
                throw new ArgumentException("Cannot compare objects");
            }
            return CompareTo(other);
        }


        /* ------------------------------- Other methods ----------------------------- */

        public override int GetHashCode()
        {
            return numberList.Aggregate(0, (current, val) => current ^ val);
        }

        public override string ToString()
        {
            var Returned = "";
            if (!sign)
                Returned += '-';
            for (var i = numberList.Count - 1; i >= 0; i--)
            {
                Returned += IntToChar(numberList[i]);
            }
            return Returned;
        }

        public BigNumber Copy()
        {
            BigNumber Returned = new() { Base = Base };
            foreach (var d in numberList)
            {
                Returned.numberList.Add(d);
            }
            Returned.sign = sign;
            return Returned;
        }


    }

    internal static class ListExtension
    {
        public static void TrimEnd(this List<int> list, int d)
        {
            var count = 0;
            var iterator = list.Count;
            while (list[iterator - 1] == d)
            {
                count++;
                iterator--;
            }
            list.RemoveRange(iterator, count);
        }
    }
}
#endregion


