package com.company.Commands.DeleteCommands;

import com.company.Student;
import com.company.Commands.Command;
import com.company.Data;

public class DeleteStudentCommand implements Command {
    public Student product = new Student();
    public boolean isOk = true;

    public DeleteStudentCommand(String line) {
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

        if (data.getLanguageMap().containsKey(product.getId())) {
        	product = data.getStudentMap().get(product.getId());
            data.deleteStudent(product);
        } else {
            System.out.println("Selected student not exists!");
        }
    }

    @Override
    public void cancel(Data data) {
        if (!isOk) {
            return;
        }
        data.addStudent(product);
    }
}
