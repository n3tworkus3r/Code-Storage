package com.company.Commands.AddCommands;

import com.company.Language;
import com.company.Commands.Command;
import com.company.Data;

public class AddLanguageCommand implements Command {
    public Language maker = new Language();
    public boolean isOk = true;

    public AddLanguageCommand(String line) {
        try {
            String[] data = line.split(" ");
            maker.setLanguageName(data[2]);
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
        data.addLanguage(maker);
    }

    @Override
    public void cancel(Data data) {
        if (!isOk) {
            return;
        }
        data.deleteLanguage(maker);
    }
}
