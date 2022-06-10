package com.company.Commands.ViewCommands;

import com.company.Student;
import com.company.Commands.Command;
import com.company.Data;

public class ViewStudentCommand implements Command {
    @Override
    public void execute(Data data) {
        if (data.getStudentMap().size() == 0) {
            System.out.println("Students not added");
        } else {
            for (Student student : data.getStudentMap().values()) {
                System.out.println(student);
            }
        }
    }

    @Override
    public void cancel(Data data) {

    }
}
