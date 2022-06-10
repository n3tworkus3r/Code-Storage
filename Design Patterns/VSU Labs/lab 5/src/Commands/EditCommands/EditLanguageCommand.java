package com.company.Commands.EditCommands;

import com.company.Language;
import com.company.Commands.Command;
import com.company.Data;

import java.util.ArrayList;
import java.util.Arrays;

public class EditLanguageCommand implements Command {
    public Language maker = new Language();
    public boolean isOk = true;
    public ArrayList<String> params = new ArrayList<>();

    public EditLanguageCommand(String line) {
        try {
            String[] data = line.split(" ");
            maker.setLanguageId(Integer.parseInt(data[2]));

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
            maker = data.getLanguageMap().get(maker.getId());
            maker.setLanguageName(params.get(0));
            data.getLanguageMap().put(maker.getId(), maker);
        } catch (Exception e) {
            isOk = false;
            System.out.println("Wrong parameters, see help! (help command)");
        }
    }

    @Override
    public void cancel(Data data) {
        if (!isOk) {
            return;
        }
        data.getLanguageMap().put(maker.getId(), maker);
    }
}
