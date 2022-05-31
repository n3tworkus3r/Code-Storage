package window.draw;

import cards.Card;
import cards.CardMover;
import cards.CardStorage;
import window.Field;
import window.Window;

import javax.swing.*;
import java.awt.*;
import java.util.List;

public class Painter extends Window implements Draw {

    @Override
    public void draw() {
        List<JLabel> field = Field.getField();
        List<Card> pyramid = CardStorage.getPyramid();
        List<Card> deck = CardStorage.getCardList();
        Card nearDeck = CardStorage.nearDeck();
        Card current = CardStorage.getCurrent();
        CardMover mover = new CardMover();
        int size = pyramid.size();
        field.clear();
        jPanel.setBackground(new Color(127,250, 84));
        int i = 0;
        int j = 0;
        int counter = 0;
        int startX = 280;
        int startY = 50;
        while(counter<28){
            field.add(new JLabel());
            if (pyramid.get(counter) != null)
            {
                field.get(counter).setIcon(pyramid.get(counter).getIcon());
                field.get(counter).setName(counter + ";" + pyramid.get(counter).getRank());
                field.get(counter).setBounds(startX + j * 73, startY, 73, 97);
                field.get(counter).addMouseListener(mover);
            } else {
                field.get(counter).setBounds(startX + j * 97, startY, 73, 97);
            }
            jPanel.add(field.get(counter));
            if(i == j){
                startX-=36.5;
                startY+=97;
                i++;
                j = 0;
                counter++;
                continue;
            }
            counter++;
            j++;
        }
        //Print deck
        field.add(new JLabel("Карта",JLabel.CENTER));
        field.get(counter).setName("deck");
        field.get(counter).setBounds(500, 50, 50, 50);
        field.get(counter).setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.RED));
        field.get(counter).addMouseListener(mover);
        jPanel.add(field.get(counter++));

        if(CardStorage.nearDeck()==null){
            field.add(new JLabel("X",JLabel.CENTER));
            field.get(counter).setName("nearDeck");
            field.get(counter).setBounds(555, 50, 73, 97);
            field.get(counter).setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.WHITE));
            jPanel.add(field.get(counter++));
        } else {
            field.add(new JLabel());
            field.get(counter).setName("nearDeck");
            field.get(counter).setIcon(nearDeck.getIcon());
            field.get(counter).setBounds(555, 50, 73, 97);
            field.get(counter).setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.WHITE));
            field.get(counter).addMouseListener(mover);
            jPanel.add(field.get(counter++));
        }

        field.add(new JLabel());
        field.get(counter).setName("current");
        field.get(counter).setIcon(current.getIcon());
        field.get(counter).setBounds(523, 180, 73, 97);
        field.get(counter).setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.WHITE));

        jPanel.add(field.get(counter++));

        jPanel.repaint();
    }

    public void clear(){
        List<JLabel> field= Field.getField();
        int size=field.size();
        for(int i=0; i<size; i++){
            jPanel.remove(field.get(i));
            jPanel.repaint();
        }
    }
}
