package com.company.Commands.OtherCommands;

import com.company.Commands.Command;
import com.company.Data;

public class CancelCommand implements Command {
    Command command;

    public CancelCommand(Command lastCommand) {
        command = lastCommand;
    }

    @Override
    public void execute(Data data) {
        if (command != null) {
            command.cancel(data);
        }
    }

    @Override
    public void cancel(Data data) {
        if (command != null) {
            command.execute(data);
        }
    }
}
