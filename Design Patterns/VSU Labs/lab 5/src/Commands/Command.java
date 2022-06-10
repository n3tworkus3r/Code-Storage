package com.company.Commands;

import com.company.Data;

public interface Command {
    public void execute(Data data);
    public void cancel(Data data);
}
