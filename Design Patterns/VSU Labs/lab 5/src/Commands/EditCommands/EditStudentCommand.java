package com.company.Commands.EditCommands;

import com.company.Student;
import com.company.Commands.Command;
import com.company.Data;

import java.util.ArrayList;
import java.util.Arrays;

public class EditStudentCommand implements Command {
    public Student student = new Student();
    public boolean isOk = true;
    public ArrayList<String> params = new ArrayList<>();

    public EditStudentCommand(String line) {
        try {
            String[] data = line.split(" ");
            student.setId(Integer.parseInt(data[2]));

            params.addAll(Arrays.asList(data).subList(3, data.length));
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
        	student = data.getStudentMap().get(student.getId());
        	student.setName(params.get(0));
            student.setSurname(params.get(1));
            student.setMiddlename(params.get(2));
            student.setSex(params.get(3));
            student.setDate(params.get(4));
        	student.setLanguageId(Integer.parseInt(params.get(5)));
            student.setGroupId(Integer.parseInt(params.get(6)));
            data.getStudentMap().put(student.getId(), student);
        } catch (Exception e) {
            isOk = false;
            System.out.println("Wrong parameters, see help! (help command)");
        }
    }

    @Override
    public void cancel(Data data) {
        if (!isOk) {
            return;
        }
        data.getStudentMap().put(student.getId(), student);
    }
}
