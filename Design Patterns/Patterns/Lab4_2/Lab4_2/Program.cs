using System;
using System.Linq;
using System.Collections.Generic;
const int n = 10000, nDisplay = 10;
System.Diagnostics.Stopwatch sw = new();
new SeqGenerator[] 
{
    new FibonSeqGen(n),
    new FactorSeqGen(n),
    new PrimeSeqGen(n)
}
.ToList().ForEach(alg =>
{
    sw.Start();
    alg.Generate(n).Take(nDisplay).ToList().ForEach(el => Console.Write($"{el} "));
    Console.WriteLine($"\n{sw.Elapsed.Milliseconds}ms ellapsed");
    sw.Stop();
});
abstract class SeqGenerator
{
    public int N { get; init; }
    public SeqGenerator(int n) => N = n;
    public abstract IEnumerable<long> Generate(int n); 
}
class FibonSeqGen : SeqGenerator
{
    public FibonSeqGen(int n) : base(n) { }
    public override long[] Generate(int n)
    {
        var fibon = new long[n];
        fibon[0] = 1;
        fibon[1] = 1;
        for (long i = 2; i < fibon.Length; i++)
            fibon[i] = fibon[i - 1] + fibon[i - 2];
        return fibon;
    }
}
class FactorSeqGen : SeqGenerator
{
    public FactorSeqGen(int n) : base(n) { }
    public override long[] Generate(int n)
    {
        var factors = new long[n];
        factors[0] = 1;
        for (long i = 1; i < n; i++)
            factors[i] = factors[i - 1] * i;
        return factors;
    }

}
class PrimeSeqGen : SeqGenerator
{
    public PrimeSeqGen(int n) : base(n) { }
    public override IEnumerable<long> Generate(int n)
    {
        static bool IsPrime(long a)
        {
            if (a < 2) return false;
            if (a == 2) return true;
            var sq = (long)Math.Sqrt(a);
            for (long i = 2; i < a; i++)
                if (a % i == 0)
                    return false;
            return true;
        }
        for (long i = 0; i < n; i++)
            if (IsPrime(i))
                yield return i;
    }
}
abstract class SeqGenDecorator : SeqGenerator
{
    protected SeqGenerator Component { get; set; }
    public SeqGenDecorator(int n) : base(n) { }
    public void SetComponent(SeqGenerator component) => Component = component;
    public override IEnumerable<long> Generate(int n) => Component?.Generate(n);
}
#region ConcrDec
class ConcreteDecoratorA : SeqGenDecorator
{
    public ConcreteDecoratorA(int n) : base(n) { }
    public override IEnumerable<long> Generate(int n) => base.Generate(n);
}
#endregion ConcrDec
