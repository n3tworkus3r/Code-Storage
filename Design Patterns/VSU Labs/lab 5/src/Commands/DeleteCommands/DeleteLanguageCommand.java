package com.company.Commands.DeleteCommands;

import com.company.Language;
import com.company.Commands.Command;
import com.company.Data;

public class DeleteLanguageCommand implements Command {
    public Language language = new Language();
    public boolean isOk = true;

    public DeleteLanguageCommand(String line) {
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

        if (data.getLanguageMap().containsKey(language.getId())) {
            language = data.getLanguageMap().get(language.getId());
            data.deleteLanguage(language);
        } else {
            System.out.println("Language not exists!");
        }
    }

    @Override
    public void cancel(Data data) {
        if (!isOk) {
            return;
        }
        data.addLanguage(language);
    }
}
