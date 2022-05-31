package cards;

import rule.Ruler;
import window.draw.Painter;
import window.draw.PainterStorage;

import javax.swing.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class CardMover extends MouseAdapter{
    public static int count=0;

    @Override
    public void mouseClicked(MouseEvent e) {
        Painter painter = PainterStorage.getPainter();
        JLabel jl = (JLabel)e.getSource();
        String str = jl.getName();
        switch (str){
            case "deck":
                CardStorage.flip();
                painter.clear();
                painter.draw();
                System.out.println("Flip " + count++);
                break;
            case "nearDeck":
                int nearRank = CardStorage.nearDeck().getRank();
                int currentRank = CardStorage.getCurrent().getRank();
                if((nearRank == (currentRank+1))
                        || (nearRank == (currentRank-1))
                )
                //|| (nearRank == (currentRank + 12))
                // || (nearRank == (currentRank - 12)))
                {
                    CardStorage.onField();
                    painter.clear();
                    painter.draw();
                    System.out.println("nearDeck ");
                }
                break;
            default:
                String[] temp = str.split(";");
                int number = Integer.parseInt(temp[0]);
                int rank = Integer.parseInt(temp[1]);
                if(move(number, rank)){
                    painter.clear();
                    painter.draw();
                    System.out.println("Click-clack");
                }
                break;
        }
        Ruler.checkMove();
        Ruler.checkWin();
    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseReleased(MouseEvent e) {

    }

    private static boolean move(int index, int rank){
        int currentRank = CardStorage.getCurrent().getRank();
        if(((rank == (currentRank+1))
                || (rank == (currentRank-1))
        )
                //  || (rank == (currentRank + 12))
                // || (rank == (currentRank - 12)))
                && canMove(index)){
            CardStorage.setCurrent(CardStorage.getFromPyramid(index));
            CardStorage.removeFromPyramid(index);
            return true;
        }
        return false;
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
