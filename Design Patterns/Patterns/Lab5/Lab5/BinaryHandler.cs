using System;
using System.Linq;
using System.Collections.Generic;
using System.IO;

namespace Lab5
{
    static class BinaryHandler
    {
        static public void WriteToFile<T>(string fileName, T obj) where T : class
        {
            IEnumerable<T> finalContent;
            using (FileStream fs = new(fileName, FileMode.Open, FileAccess.Read)) 
            {
                using BinaryReader br = new(fs);
                finalContent = ReadFromFile<T>(br).Append(obj).ToList();
            }
            using BinaryWriter bw = new(File.Open(fileName, FileMode.OpenOrCreate));
            foreach (var el in finalContent)
            {
                var props = el.GetType().GetProperties();
                foreach (var prop in props)
                {
                    var val = prop.GetValue(el);
                    if (val is string) bw.Write(val as string);
                    else if (val is int) bw.Write(Convert.ToInt32(val));
                    else if (val is double) bw.Write(Convert.ToDouble(val));
                    else if (val is bool) bw.Write(Convert.ToBoolean(val));
                    else if (val is DateTime)
                    {
                        var dt = (val as DateTime?).Value;
                        bw.Write(dt.Year);
                        bw.Write(dt.Month);
                        bw.Write(dt.Day);
                    };
                }
            }
        }

        static public IEnumerable<T> ReadFromFile<T>(BinaryReader br) where T : class
        {
            while (br.PeekChar() is not -1)
            {
                var obj = Activator.CreateInstance(typeof(T)) as T;
                var props = typeof(T).GetProperties();
                foreach (var prop in props)
                {
                    var a = prop.PropertyType.Name;
                    prop.SetValue(obj, a switch
                    {
                        "String" => br.ReadString(),
                        "Int32" => br.ReadInt32(),
                        "Double" => br.ReadDouble(),
                        "Boolean" => br.ReadBoolean(),
                        "DateTime" => new DateTime(br.ReadInt32(), br.ReadInt32(), br.ReadInt32()),
                        _ => throw new NotImplementedException()
                    });
                }
                yield return obj;
            }
        }
    }
}
