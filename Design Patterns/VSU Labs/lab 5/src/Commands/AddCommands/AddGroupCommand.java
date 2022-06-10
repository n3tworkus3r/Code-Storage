package com.company.Commands.AddCommands;

import com.company.Group;
import com.company.Commands.Command;
import com.company.Data;

public class AddGroupCommand implements Command {
    public Group section = new Group();
    public boolean isOk = true;

    public AddGroupCommand(String line) {
        try {
            String[] data = line.split(" ");
            section.setName(data[2]);
            section.setCourseId(data[3]);
            section.setSpeciality(data[4]);
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
        data.addGroup(section);
    }

    @Override
    public void cancel(Data data) {
        if (!isOk) {
            return;
        }
        data.deleteGroup(section);
    }
}
