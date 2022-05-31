package window.dialog;

import cards.Card;
import cards.CardDeck;
import cards.CardStorage;
import window.draw.Painter;
import window.draw.PainterStorage;

import java.util.List;

public class NewGame {
    private static int cols=13;
    private static int rows=4;

    public NewGame(){
        Painter painter = PainterStorage.getPainter();
        int size = cols * rows;
        CardDeck cardDeck = new CardDeck();
        cardDeck.init();
        cardDeck.shuffle();
        List<Card> deck = cardDeck.getCardDeck();

        for(int i = 0; i < 28; i++){
            CardStorage.addToPyramid(deck.get(0));
            deck.remove(0);
        }
        for (int i = 0; i < 24; i++) {
            CardStorage.add(deck.get(0));
            deck.remove(0);
        }
        CardStorage.flip();
        CardStorage.onField();
        painter.draw();

    }
}
