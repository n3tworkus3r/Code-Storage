using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace Lab5
{
    class BinListHandler
    {
        public Type ClassType { get; init; }
        string FileName { get; init; }
        public BinListHandler(Type classType)
        {
            ClassType = classType;
            FileName = $"{ClassType.Name.ToLower()}s.dat";
        }
        object CreateObject(string[] pars)
        {
            var obj = Activator.CreateInstance(ClassType);
            var props = obj.GetType().GetProperties();
            for (int i = 0; i < pars.Length; i++)
                props[i].SetValue(obj, props[i].PropertyType.Name switch
                {
                    "String" => pars[i],
                    "Int32" => int.Parse(pars[i]),
                    "Double" => double.Parse(pars[i]),
                    "Boolean" => bool.Parse(pars[i]),
                    "DateTime" => new DateTime(int.Parse(pars[i]), int.Parse(pars[++i]), int.Parse(pars[++i])),
                    _ => throw new NotImplementedException()
                });
            return obj;
        }
        void WriteElements(IEnumerable<object> elements) => 
            elements.ToList()
            .ForEach(el => typeof(BinaryHandler)
                .GetMethod("WriteToFile")
                .MakeGenericMethod(ClassType)
                .Invoke(null, new object[] { FileName, el }));
        List<object> GetElements(BinaryReader br) => (typeof(BinaryHandler).GetMethod("ReadFromFile")
                .MakeGenericMethod(ClassType).Invoke(null, new object[] { br })
                as IEnumerable<object>)
                .ToList();
        public void BinAdd(string[] pars) =>
            typeof(BinaryHandler).GetMethod("WriteToFile")
                    .MakeGenericMethod(ClassType)
                    .Invoke(null, new object[] { FileName, CreateObject(pars) });
        public void BinDel(string[] pars)
        {
            List<object> elements;
            using (BinaryReader br = new(File.Open(FileName, FileMode.OpenOrCreate)))
                elements = GetElements(br);
            using (FileStream fs = new(FileName, FileMode.Create))
                fs.Close();
            elements.RemoveAt(int.Parse(pars[0]));
            WriteElements(elements);
        }
        public void BinEdit(string[] pars)
        {
            BinDel(new string[] { pars[0] });
            List<object> elements;
            using (BinaryReader br = new(File.Open(FileName, FileMode.OpenOrCreate)))
                elements = GetElements(br);
            elements.Insert(int.Parse(pars[0]), CreateObject(pars[1..]));
            using (FileStream fs = new(FileName, FileMode.Create))
                fs.Close();
            WriteElements(elements);
        }
        public void BinShow(string[] pars)
        {
            using BinaryReader br = new(File.Open(FileName, FileMode.OpenOrCreate));
            var elements = GetElements(br);
            for (int i = 0; i < elements.Count; i++)
                Console.WriteLine($"{i} - {elements[i]}");
        }
        public void BinSearch(string[] pars)
        {
            List<object> elements;
            using (BinaryReader br = new(File.Open(FileName, FileMode.OpenOrCreate)))
                elements = GetElements(br);
            elements.Where(el =>
                    el.GetType()
                    .GetProperties()
                    .First(prop =>
                    prop.Name == pars[0]
                )
                .GetValue(el).ToString() == pars[1]
            )
            .ToList()
            .ForEach(Console.WriteLine);
        }
    }
}
