package com.company.Commands.ViewCommands;

import com.company.Group;
import com.company.Commands.Command;
import com.company.Data;

public class ViewGroupCommand implements Command {
    @Override
    public void execute(Data data) {
        if (data.getGroupMap().size() == 0) {
            System.out.println("Groups not exists!");
        } else {
            for (Group section : data.getGroupMap().values()) {
                System.out.println(section);
            }
        }
    }

    @Override
    public void cancel(Data data) {

    }
}
