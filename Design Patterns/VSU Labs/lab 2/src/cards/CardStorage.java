package cards;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class CardStorage {
    private static List<Card> cardList=new ArrayList<>();
    private static List<Card> onField = new ArrayList<>();
    private static Card current;

    public static Card getCurrent() {
        return current;
    }

    public static void setCurrent(Card current) {
        CardStorage.current = current;
    }

    public static void onField(){
        current=nearDeck();
        onField.remove(nearDeck());
    }

    public static void flip(){
        if(cardList.isEmpty() && !onField.isEmpty()){
            Collections.reverse(onField);
            cardList=new ArrayList<>(onField);
            onField=new ArrayList<>();
        }
        else if(!cardList.isEmpty()){
            onField.add(cardList.get(cardList.size()-1));
            cardList.remove(cardList.size()-1);
        }
    }

    public static Card nearDeck(){
        if(onField.isEmpty()) return null;
        else return onField.get(onField.size()-1);
    }

    public static List<Card> getCardList() {
        return cardList;
    }

    public static List<Card> getOnField() {
        return onField;
    }

    public static void add(Card card){
        cardList.add(card);
    }

    public static Card get(int index){
        return cardList.get(index);
    }

    public static void set(int index, Card card){
        cardList.set(index, card);
    }

    public static void remove(int index){
        cardList.remove(index);
    }

    private static List<Card> pyramid = new ArrayList<>();

    public static Card getFromPyramid(int index){
        return pyramid.get(index);
    }

    public static List<Card> getPyramid(){
        return pyramid;
    }

    public static void addToPyramid(Card card) {
        pyramid.add(card);
    }

    public static void removeFromPyramid(int index){
        pyramid.set(index, null);
    }
}
