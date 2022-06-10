package com.company.Commands.ViewCommands;

import com.company.Language;
import com.company.Commands.Command;
import com.company.Data;

public class ViewLanguageCommand implements Command {
    @Override
    public void execute(Data data) {
        if (data.getLanguageMap().size() == 0) {
            System.out.println("Languages not exists!");
        } else {
            for (Language language : data.getLanguageMap().values()) {
                System.out.println(language);
            }
        }
    }

    @Override
    public void cancel(Data data) {

    }
}
