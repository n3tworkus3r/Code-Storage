package com.company.Commands.EditCommands;

import com.company.Group;
import com.company.Commands.Command;
import com.company.Data;

import java.util.ArrayList;
import java.util.Arrays;

public class EditGroupCommand implements Command {
    public Group group = new Group();
    public boolean isOk = true;
    public ArrayList<String> params = new ArrayList<>();

    public EditGroupCommand(String line) {
        try {
            String[] data = line.split(" ");
            group.setId(Integer.parseInt(data[2]));

            params.addAll(Arrays.asList(data).subList(3, data.length));
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
            group = data.getGroupMap().get(group.getId());
            group.setName(params.get(0));
            group.setCourseId(params.get(1));
            group.setSpeciality(params.get(2));
            data.getGroupMap().put(group.getId(), group);
        } catch (Exception e) {
            isOk = false;
            System.out.println("Неверные параметры, смотрите справку (команда help)");
        }
    }

    @Override
    public void cancel(Data data) {
        if (!isOk) {
            return;
        }
        data.getGroupMap().put(group.getId(), group);
    }
}
