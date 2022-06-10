package com.company.Commands;

import com.company.Commands.AddCommands.*;
import com.company.Commands.DeleteCommands.*;
import com.company.Commands.EditCommands.*;
import com.company.Commands.FindCommands.*;
import com.company.Commands.OtherCommands.*;
import com.company.Commands.ViewCommands.*;

public class CommandFactory {
    public Command lastCommand = null;

    public static CommandFactory instance;

    public CommandFactory() {}

    public static CommandFactory getInstance() {
        if (instance == null) {
            instance = new CommandFactory();
        }

        return instance;
    }

    public Command getCommand(String line) {
        if (line.startsWith("view student")) {
            lastCommand = new ViewStudentCommand();
        } else if (line.startsWith("view language")) {
            lastCommand = new ViewLanguageCommand();
        } else if (line.startsWith("view group")) {
            lastCommand = new ViewGroupCommand();
        } else if (line.startsWith("add student")) {
            lastCommand = new AddStudentCommand(line);
        } else if (line.startsWith("add language")) {
            lastCommand = new AddLanguageCommand(line);
        } else if (line.startsWith("add group")) {
            lastCommand = new AddGroupCommand(line);
        } else if (line.startsWith("edit student")) {
            lastCommand = new EditStudentCommand(line);
        } else if (line.startsWith("edit language")) {
            lastCommand = new EditLanguageCommand(line);
        } else if (line.startsWith("edit group")) {
            lastCommand = new EditGroupCommand(line);
        } else if (line.startsWith("delete student")) {
            lastCommand = new DeleteStudentCommand(line);
        } else if (line.startsWith("delete language")) {
            lastCommand = new DeleteLanguageCommand(line);
        } else if (line.startsWith("delete group")) {
            lastCommand = new DeleteGroupCommand(line);
        } else if (line.startsWith("find student")) {
            lastCommand = new FindStudentCommand(line);
        } else if (line.startsWith("find language")) {
            lastCommand = new FindLanguageCommand(line);
        } else if (line.startsWith("find group")) {
            lastCommand = new FindGroupCommand(line);
        } else if (line.startsWith("help")) {
            lastCommand = new HelpCommand();
        } else if (line.startsWith("cancel")) {
            lastCommand = new CancelCommand(lastCommand);
        } else if (line.startsWith("exit")) {
            lastCommand = new SaveAndExitCommand();
        } else {
            return null;
        }

        return lastCommand;
    }
}
