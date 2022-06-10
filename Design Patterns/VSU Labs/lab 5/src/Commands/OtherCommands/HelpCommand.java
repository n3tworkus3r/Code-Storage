package com.company.Commands.OtherCommands;

import com.company.Commands.Command;
import com.company.Data;

public class HelpCommand implements Command {
    @Override
    public void execute(Data data) {
        System.out.println("*************\n" +
                "\n" +
                "## View collection student/language/group:\n" +
                "view student/language/group\n" +
                "\n" +
                "*************\n" +
                "\n" +
                "## Add student:\n" +
                "add student name surname middle sex date languageId groupId\n" +
                "\n" +
                "## Add language:\n" +
                "add language name\n" +
                "\n" +
                "## Add group:\n" +
                "add group name courseId speciality\n" +
                "\n" +
                "*************\n" +
                "\n" +
                "## Edit student:\n" +
                "edit student studentId name surname middle sex date languageId groupId\n" +
                "\n" +
                "## Edit language:\n" +
                "edit language languageId newLanguageName\n" +
                "\n" +
                "## Edit group:\n" +
                "edit group groupId newName newCourseId newSpeciality\n" +
                "\n" +
                "*************\n" +
                "\n" +
                "## Remove student:\n" +
                "delete student studentId\n" +
                "\n" +
                "## Remove language:\n" +
                "delete language languageId\n" +
                "\n" +
                "## Remove group:\n" +
                "delete group groupId\n" +
                "\n" +
                "*************\n" +
                "\n" +
                "## Find student:\n" +
                "find student studentId\n" +
                "\n" +
                "## Find language:\n" +
                "find language languageId\n" +
                "\n" +
                "## Find group:\n" +
                "find group groupId\n" +
                "\n" +
                "*************\n" +
                "\n" +
                "## Information:\n" +
                "help\n" +
                "\n" +
                "## Cancel last operation:\n" +
                "cancel\n" +
                "\n" +
                "## Close program:\n" +
                "exit\n" +
                "\n" +
                "*************");
    }

    @Override
    public void cancel(Data data) {

    }
}
