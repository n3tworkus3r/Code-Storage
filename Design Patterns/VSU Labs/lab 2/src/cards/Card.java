package cards;

import javax.swing.*;

public class Card {
    private int suit;
    private int rank;
    private ImageIcon icon;

    public Card(int rank, int suit, ImageIcon icon) {
        this.rank = rank;
        this.suit = suit;
        this.icon = icon;
    }

    public int getSuit() {
        return suit;
    }

    public void setSuit(int suit) {
        this.suit = suit;
    }

    public ImageIcon getIcon() {
        return icon;
    }


    public void setIcon(ImageIcon icon) {
        this.icon = icon;
    }

    public int getRank() {
        return rank;
    }

    public void setRank(int rank) {
        this.rank = rank;
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder= new StringBuilder();
        switch (this.rank){
            case 11:
                stringBuilder.append("Валет ");
                break;
            case 12:
                stringBuilder.append("Дама ");
                break;
            case 13:
                stringBuilder.append("Король ");
                break;
            case 14:
                stringBuilder.append("Туз ");
                break;
            default:
                stringBuilder.append(rank).append(" ");
                break;
        }
        switch (this.suit){
            case 0:
                stringBuilder.append("Червей ");
                break;
            case 1:
                stringBuilder.append("Пик ");
                break;
            case 2:
                stringBuilder.append("Бубн ");
                break;
            case 3:
                stringBuilder.append("Треф ");
                break;
        }
        return stringBuilder.toString();
    }

}
