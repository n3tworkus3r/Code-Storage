package cards;

import javax.swing.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class CardDeck {
    private List<Card> cardDeck=new ArrayList<>();

    public void init(){
        int suitCount=4;
        int rankCount=13;
        for(int i=0; i<suitCount;i++){
            for(int j=0; j<rankCount; j++){
                ImageIcon icon=new ImageIcon("src/Image/"+i+"/"+(j+2)+".gif");
                cardDeck.add(new Card(j+2,i,icon));
            }
        }
    }

    public List<Card> getCardDeck() {
        return cardDeck;
    }

    public void shuffle(){
        Collections.shuffle(cardDeck);}

    public void remove(int index){
        cardDeck.remove(index);
    }
}
