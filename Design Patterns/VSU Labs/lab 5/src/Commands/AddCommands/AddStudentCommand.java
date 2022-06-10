package com.company.Commands.AddCommands;

import com.company.Student;
import com.company.Commands.Command;
import com.company.Data;

public class AddStudentCommand implements Command {
    public Student student = new Student();
    public boolean isOk = true;

    public AddStudentCommand(String line) {
        try {
            String[] data = line.split(" ");
            student.setName(data[2]);
            student.setSurname(data[3]);
            student.setMiddlename(data[4]);
            student.setSex(data[5]);
            student.setDate(data[6]);
            student.setLanguageId(Integer.parseInt(data[7]));
            student.setGroupId(Integer.parseInt(data[8]));
            System.out.println("Complete!");
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
        data.addStudent(student);
    }

    @Override
    public void cancel(Data data) {
        if (!isOk) {
            return;
        }
        data.deleteStudent(student);
    }
}
