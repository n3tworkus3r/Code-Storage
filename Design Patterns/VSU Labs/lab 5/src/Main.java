package com.company;

import com.company.Commands.Command;
import com.company.Commands.CommandFactory;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Data data = Data.loadData();
        Scanner scan = new Scanner(System.in);

        while (true) {
            System.out.println("Enter a command: (help - for info)\n->");

            String line = scan.nextLine();

            Command command = CommandFactory.getInstance().getCommand(line);
            if (command != null) {
                command.execute(data);
            } else {
                System.out.println("Unknow command");
            }
        }
    }
}
