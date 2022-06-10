package com.company.Commands.OtherCommands;

import com.company.Commands.Command;
import com.company.Data;

import java.io.IOException;

public class SaveAndExitCommand implements Command {
    public SaveAndExitCommand() {}

    @Override
    public void execute(Data data) {
        try {
            data.saveData();
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.exit(0);
    }

    @Override
    public void cancel(Data data) {

    }
}
