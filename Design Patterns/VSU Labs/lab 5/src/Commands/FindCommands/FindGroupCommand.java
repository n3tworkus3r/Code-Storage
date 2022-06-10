package com.company.Commands.FindCommands;

import com.company.Group;
import com.company.Commands.Command;
import com.company.Data;

public class FindGroupCommand implements Command {
    public Group section = new Group();
    public boolean isOk = true;

    public FindGroupCommand(String line) {
        try {
            String[] data = line.split(" ");
            section.setId(Integer.parseInt(data[2]));
        } catch (Exception e) {
            isOk = false;
            System.out.println("Wrong parameters, see help! (help command)");
        }
    }

    @Override
    public void execute(Data data) {
        if (!isOk) {
            return;
        }

        try {
            System.out.println(data.getGroupMap().get(section.getId()));
        } catch (Exception e) {
            isOk = false;
            System.out.println("Wrong parameters, see help! (help command)");
        }
    }

    @Override
    public void cancel(Data data) {

    }
}
