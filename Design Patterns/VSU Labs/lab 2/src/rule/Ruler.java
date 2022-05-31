package rule;

import cards.Card;
import cards.CardStorage;
import window.Window;
import window.dialog.EndGame;
import window.dialog.Winner;

import javax.swing.*;
import java.util.List;

public class Ruler {
    public static void checkWin(){
        List<Card> pyramid = CardStorage.getPyramid();
        for(int i = 0; i < 28; i++)
            if(pyramid.get(i)!=null)
                return;
        JDialog jDialog = new Winner(Window.getjFrame());
        jDialog.setVisible(true);
    }

    public static void checkMove(){
        List<Card> pyramid = CardStorage.getPyramid();
        List<Card> deck = CardStorage.getCardList();
        List<Card> onField = CardStorage.getOnField();
        int deckSize = deck.size();
        int currentRank = CardStorage.getCurrent().getRank();
        for(int i = 0; i < deckSize; i++) {
            int rank = deck.get(i).getRank();
            if ((rank == (currentRank + 1))
                    || (rank == (currentRank - 1))
            )
                //  || (rank == (currentRank + 12))
                //    || (rank == (currentRank - 12)))
                return;
        }

        int onFieldSize = onField.size();
        for(int i = 0; i < onFieldSize; i++) {
            int rank = onField.get(i).getRank();
            if ((rank == (currentRank + 1))
                    || (rank == (currentRank - 1))
            )
                // || (rank == (currentRank + 12))
                // || (rank == (currentRank - 12)))
                return;
        }

        int pyramidSize = pyramid.size();
        for (int i = 0; i < pyramidSize; i++){
            if(pyramid.get(i)==null) continue;
            int rank = pyramid.get(i).getRank();
            if(((rank == (currentRank+1))
                    || (rank == (currentRank-1))
                    // || (rank == (currentRank + 12))
                    // || (rank == (currentRank - 12)))
            )
                    && canMove(i)) return;
        }
        JDialog jDialog = new EndGame(Window.getjFrame());
        jDialog.setVisible(true);
    }

    private static boolean canMove(int index){
        int layerNumber = 0;
        if(index==0){
            layerNumber = 1;
            if(CardStorage.getPyramid().get(index+layerNumber)==null && CardStorage.getPyramid().get(index+layerNumber+1)==null)return true;
            else return false;
        }
        if(index>=1 && index<=2){
            layerNumber = 2;
            if(CardStorage.getPyramid().get(index+layerNumber)==null && CardStorage.getPyramid().get(index+layerNumber+1)==null)return true;
            else return false;
        }
        if(index>=3 && index<=5){
            layerNumber = 3;
            if(CardStorage.getPyramid().get(index+layerNumber)==null && CardStorage.getPyramid().get(index+layerNumber+1)==null)return true;
            else return false;
        }
        if(index>=6 && index<=9){
            layerNumber = 4;
            if(CardStorage.getPyramid().get(index+layerNumber)==null && CardStorage.getPyramid().get(index+layerNumber+1)==null)return true;
            else return false;
        }
        if(index>=10 && index<=14){
            layerNumber = 5;
            if(CardStorage.getPyramid().get(index+layerNumber)==null && CardStorage.getPyramid().get(index+layerNumber+1)==null)return true;
            else return false;
        }
        if(index>=15 && index<=20){
            layerNumber = 6;
            if(CardStorage.getPyramid().get(index+layerNumber)==null && CardStorage.getPyramid().get(index+layerNumber+1)==null)return true;
            else return false;
        }
        if(index>=21 && index<=27){
            return true;
        }
        return false;
    }
}
