package com.company.Commands.DeleteCommands;

import com.company.Group;
import com.company.Commands.Command;
import com.company.Data;

public class DeleteGroupCommand implements Command {
    public Group group = new Group();
    public boolean isOk = true;

    public DeleteGroupCommand(String line) {
        try {
            String[] data = line.split(" ");
            group.setId(Integer.parseInt(data[2]));
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

        if (data.getGroupMap().containsKey(group.getId())) {
            group = data.getGroupMap().get(group.getId());
            data.deleteGroup(group);
        } else {
            System.out.println("Selected group not exists!");
        }
    }

    @Override
    public void cancel(Data data) {
        if (!isOk) {
            return;
        }
        data.addGroup(group);
    }
}
