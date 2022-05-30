using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;

namespace Lab5
{
    class CommandsHandler
    {
        public Dictionary<string, Action<string[]>> Coms { get; set; } = new(){ ["exit"] = (string[] pars) => Environment.Exit(0) };
        public string MenuText { get; set; } = "Введите команду и параметры к ней из списка:";
        public CommandsHandler(string namespaceName)
        {
            var handlers = Assembly.GetExecutingAssembly()
                .GetTypes()
                .Where(type => type.FullName.StartsWith(namespaceName))
                .Select(classType => new BinListHandler(classType))
                .ToList();
            foreach (var handler in handlers)
            {
                var methodInfos = handler.GetType()
                    .GetMethods()
                    .Where(methodInfo => methodInfo.Name.StartsWith("Bin"))
                    .ToList();
                foreach (var methodInfo in methodInfos)
                {
                    var comText = $"{methodInfo.Name[3..].ToLower()}-{handler.ClassType.Name.ToLower()}";
                    Coms.Add(comText, methodInfo.CreateDelegate(typeof(Action<string[]>), handler) as Action<string[]>);
                    MenuText += $"\n{comText}";
                }
            }
        }
    }
}
