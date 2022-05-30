using System;
using Lab5;
const string namespaceName = "Lab5.LabListsClasses";
CommandsHandler commandsHandler = new(namespaceName);
while (true)
{
    Console.WriteLine(commandsHandler.MenuText);
    var pars = Console.ReadLine().Split(' ');
    if (pars[0] is "")
        break;
    Console.Clear();
    var binCmd = CreateCommand(commandsHandler.Coms[pars[0]]);
    SetCommand(out Reciever reciever, binCmd);
    Invoker.Run(reciever, pars[1..]);
    Console.ReadKey();
}

ICommand CreateCommand(Action<string[]> cmd) => new BinCommand(cmd);
void SetCommand(out Reciever rcvr, ICommand binCommand) => rcvr = new(binCommand);
class Reciever
{
    public ICommand BinCommand { get; set; }
    public Reciever(ICommand binCommand) => BinCommand = binCommand;
}
interface ICommand { public void Execute(string[] pars); }
class BinCommand : ICommand
{
    public BinCommand(Action<string[]> cmd) => Cmd += cmd;
    public event Action<string[]> Cmd;
    public void Execute(string[] pars) => Cmd.Invoke(pars);
}
class Invoker { public static void Run(Reciever reciever, string[] pars) => reciever.BinCommand.Execute(pars); }
