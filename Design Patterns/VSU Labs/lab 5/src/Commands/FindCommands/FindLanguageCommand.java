package com.company.Commands.FindCommands;

import com.company.Language;
import com.company.Commands.Command;
import com.company.Data;

public class FindLanguageCommand implements Command {
    public Language language = new Language();
    public boolean isOk = true;

    public FindLanguageCommand(String line) {
        try {
            String[] data = line.split(" ");
            language.setLanguageId(Integer.parseInt(data[2]));
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
            System.out.println(data.getLanguageMap().get(language.getId()));
        } catch (Exception e) {
            isOk = false;
            System.out.println("Wrong parameters, see help! (help command)");
        }
    }

    @Override
    public void cancel(Data data) {

    }
}
