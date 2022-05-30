using System;
using System.Linq;
using System.IO;
using System.Collections.Generic;
using System.Reflection;
if (args.Length is not 2 || args[1][^3..] != args[0])
{
    Console.WriteLine("Wrong Console Args!");
    return;
}
var carsNTrips = (Activator.CreateInstance(Assembly.GetExecutingAssembly().GetTypes().Where(t => t.Namespace == "Lab3_2" && t.IsClass && t.Name.Substring(0, t.FullName.IndexOf("Handler") - 7).ToLower() == args[0]).First()) as Lab3_2.IReadCardNTrips).ReadData(args[1]);
carsNTrips.FreightCars.ForEach(car => Console.WriteLine(car));
carsNTrips.RoadTrips.ForEach(trip => Console.WriteLine(trip));
carsNTrips.FreightCars.Join(carsNTrips.RoadTrips,
    fCar => fCar.GovNum,
    carFromTrip => carFromTrip.GovNum,
    (fCar, carFromTrip) => new { fCar.GovNum, carFromTrip.Length, carFromTrip.Weight, carFromTrip.DateTime }
    ).GroupBy(tripsByCars => tripsByCars.GovNum)
    .Select(tripsByCars => 
    new {
        tripsByCars.First().GovNum,
        Sum = tripsByCars.Select(carNTrip => carNTrip.Length).Sum(),
        AvgWeight = Math.Truncate(
            tripsByCars.Average(carNTrip => (DateTime.Now - carNTrip.DateTime).Days < 31? carNTrip.Weight:null)??0)
    }
    ).ToList()
    .ForEach(carWithSum => OutByProps(carWithSum));
static void OutByProps(object obj)
{
    obj.GetType().GetProperties().ToList().ForEach(prop => Console.Write($"{prop.Name}: {prop.GetValue(obj)} | "));
    Console.WriteLine();
}
namespace Lab3_2
{
    interface IReadCardNTrips
    {
        public CarsNTrips ReadData(string fileName);
        public void WriteData(string fileName);
    }
    public class CsvHandler : IReadCardNTrips
    {
        static CsvHandler() { }
        public CarsNTrips ReadData(string fileName)
        {
            using Stream sr = new FileStream(fileName, FileMode.Open);
            return ServiceStack.Text.CsvSerializer.DeserializeFromStream(typeof(CarsNTrips), sr) as CarsNTrips;
        }
        public void WriteData(string fileName)
        {
            List<RoadTrip> roadTrips = new();
            List<FreightCar> freightCars = new();
            for (int i = 0; i < 100; i++)
            {
                roadTrips.Add(new());
                freightCars.Add(new());
            }
            using StreamWriter sw = new(fileName);
            var carsTrips = new CarsNTrips() { FreightCars = freightCars, RoadTrips = roadTrips };
            sw.Write(ServiceStack.Text.CsvSerializer.SerializeToCsv(new[] { carsTrips }));
        }
    }
    public class XmlHandler : IReadCardNTrips
    {
        static XmlHandler() { }
        public CarsNTrips ReadData(string fileName)
        {
            using Stream sr = new FileStream(fileName, FileMode.Open);
            return new System.Xml.Serialization.XmlSerializer(typeof(CarsNTrips)).Deserialize(sr) as CarsNTrips;
        }
        public void WriteData(string fileName)
        {
            List<RoadTrip> roadTrips = new();
            List<FreightCar> freightCars = new();
            for (int i = 0; i < 100; i++)
            {
                roadTrips.Add(new());
                freightCars.Add(new());
            }
            using StreamWriter sw = new(fileName);
            var carsTrips = new CarsNTrips() { FreightCars = freightCars, RoadTrips = roadTrips };
            new System.Xml.Serialization.XmlSerializer(typeof(CarsNTrips)).Serialize(sw, carsTrips);
        }
    }
    public class CarsNTrips
    {
        public List<RoadTrip> RoadTrips { get; set; } = new();
        public List<FreightCar> FreightCars { get; set; } = new();
    }
    public record FreightCar
    {
        public string GovNum { get; set; } = new Random().Next(10000, 10003).ToString();
        public string Model { get; set; } = new Random().Next(10).ToString();
        public string DriverName { get; set; } = new string(Enumerable.Range(5, 5).Select(num => (char)new Random().Next('a', 'z')).ToArray());
    }
    public record RoadTrip
    {
        public DateTime DateTime { get; set; } = DateTime.Now;
        public double Weight { get; set; } = new Random().Next(200, 500);
        public double Length { get; set; } = new Random().Next(5, 30);
        public string GovNum { get; set; } = new Random().Next(10000, 10003).ToString();
    }
}