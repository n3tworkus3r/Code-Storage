using System;
Console.OutputEncoding = System.Text.Encoding.UTF8;
LogicHandler.StartGame();
record Card { public Suit Suit { get; init; } public Val Val { get; init; } }
enum Suit { Clubs, Spades, Hearts, Diamonds }
enum Val { Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Queen, Jack, King, Ace }
static class Data
{
    public const int decksAm = 13, suitsAm = 4, cardsAm = 52;
    public static string infoMsg = "Отутствует";
    public static System.Collections.Generic.List<System.Collections.Generic.Stack<Card>> gameField = new();
    static Data()
    {
        var cards = new Card[cardsAm];
        for (var i = 0; i < cards.Length; i++)
            cards[i] = new() { Suit = (Suit)(i / decksAm), Val = (Val)(i % decksAm + 2) };
        var cardPicked = new bool[cardsAm];
        for (var i = 0; i < (suitsAm/2) * (decksAm/4); i++)
        {
            System.Collections.Generic.Stack<Card> stack = new();
            while (true)
            {
                var tempNum = new Random().Next(cardsAm);
                if (!cardPicked[tempNum])
                {
                    stack.Push(cards[tempNum]);
                    cardPicked[tempNum] = true;
                    break;
                }
            }
            gameField.Add(stack);
        }
    }
}
static class LogicHandler
{
    static string ChosenCard(int field) => $"{ Data.gameField[field].Peek().Suit switch { Suit.Diamonds => '♦', Suit.Clubs => '♣', Suit.Spades => '♠', Suit.Hearts => '♥', _ => throw new NotImplementedException() }}{Data.gameField[field].Peek().Val switch { Val.Two => "2", Val.Three => "3", Val.Four => "4", Val.Five => "5", Val.Six => "6", Val.Seven => "7", Val.Eight => "8", Val.Nine => "9", Val.Ten => "10", Val.Queen => "Q", Val.Jack => "J", Val.King => "K", Val.Ace => "A", _ => throw new NotImplementedException() }}";
    static void Display()
    {
        Console.Clear();
        Console.WriteLine($"Последнее действие: {Data.infoMsg}");
        for (int i = 0; i < Data.suitsAm && i <= Data.gameField.Count / Data.decksAm; Console.WriteLine(), i++)
            for (int j = 0; (i != Data.gameField.Count / Data.decksAm) ? j < Data.decksAm : Data.gameField.Count % Data.decksAm != 0 && j < Data.gameField.Count % Data.decksAm; j++)
                Console.Write($"{ChosenCard(i * Data.decksAm + j)}\t");
        Console.Write("Введите номер стопки для хода и сколько (1 или 2 карты) отступить влево\nНапр: 2 1 1\n> ");
    }
    public static void StartGame()
    {
        while (true)
        {
            if (Data.gameField.Count <= 1)
            {
                Console.WriteLine("ПОБЕДА!!!");
                return;
            }
            if (!CanMove())
            {
                Console.WriteLine("Ходов нет");
                return;
            }
            Display();
            var inputString = Console.ReadLine().Split();
            int y = 0, am = 0;
            if (int.TryParse(inputString[0], out int x) && int.TryParse(inputString.Length == 3 ? inputString[1] : Console.ReadLine(), out y) && int.TryParse(inputString.Length == 3 ? inputString[2] : Console.ReadLine(), out am) && (am is not 1 and not 2 || x < 1 || x > (Data.gameField.Count / Data.decksAm == 0 ? 1 : Data.gameField.Count / Data.decksAm) || y < 1 || y > (x <= Data.gameField.Count / Data.decksAm ? Data.decksAm : Data.gameField.Count % Data.decksAm)))
            {
                Data.infoMsg = "Невозможный ход!";
                continue;
            }
            var fieldNum = --x * Data.decksAm + --y;
            var tryFieldNum = GetTryFieldNum(fieldNum, am);
            if (!CardsMatch(fieldNum, tryFieldNum))
            {
                Data.infoMsg = $"Ни масть, ни ценность у карт {ChosenCard(fieldNum)} и {ChosenCard(tryFieldNum)} не совпадают";
                continue;
            }
            foreach (var card in Data.gameField[fieldNum])
                Data.gameField[tryFieldNum].Push(card);
            Data.infoMsg = $"Колода с верхней {ChosenCard(fieldNum)} добавлена на {ChosenCard(tryFieldNum)}";
            Data.gameField.RemoveAt(fieldNum);
        }
    }
    static bool CardsMatch(int fieldNum, int tryFieldNum) => Data.gameField[fieldNum].Peek().Val == Data.gameField[tryFieldNum].Peek().Val || Data.gameField[fieldNum].Peek().Suit == Data.gameField[tryFieldNum].Peek().Suit;
    static int GetTryFieldNum(int fieldNum, int am) => fieldNum - am + (fieldNum - am < 0 ? Data.gameField.Count : 0);
    static bool CanMove()
    {
        if (Data.gameField.Count>2)
			for (int i = 0; i < Data.gameField.Count; i++)
				if (CardsMatch(i, GetTryFieldNum(i, 1)) || CardsMatch(i, GetTryFieldNum(i, 2)))
					return true;
        return false;
    }
}
