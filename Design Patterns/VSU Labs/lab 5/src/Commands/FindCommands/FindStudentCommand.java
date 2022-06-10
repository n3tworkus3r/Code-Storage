package com.company.Commands.FindCommands;

import com.company.Student;
import com.company.Commands.Command;
import com.company.Data;

public class FindStudentCommand implements Command {
    public Student product = new Student();
    public boolean isOk = true;

    public FindStudentCommand(String line) {
        try {
            String[] data = line.split(" ");
            product.setId(Integer.parseInt(data[2]));
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
            System.out.println(data.getStudentMap().get(product.getId()));
        } catch (Exception e) {
            isOk = false;
            System.out.println("Wrong parameters, see help! (help command)");
        }
    }

    @Override
    public void cancel(Data data) {

    }
}
