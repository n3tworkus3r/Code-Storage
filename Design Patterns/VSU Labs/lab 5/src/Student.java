package com.company;

import java.io.Serializable;

public class Student implements Serializable {
    public int id;
    public String surname;
    public String name;
    public String middlename;
    public String sex;
    public String date;
    public int languageId;
    public int groupId;

    public Student() {}

    //STUDENT GETTERS
    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getSurname() {
        return surname;
    }

    public String getMiddlename() {
        return middlename;
    }

    public String getSex() {
        return sex;
    }

    public String getDate() {
        return date;
    }

    public int getLanguageId() {
        return languageId;
    }

    public int getGroupId() {
        return groupId;
    }


    //STUDENT SETTERS
    public void setId(int id) {
        this.id = id;
    }

    public void setName(String newName) {
        this.name = newName;
    }

    public void setSurname(String newSurname) {
        this.surname = newSurname;
    }

    public void setMiddlename(String newMiddlename) {
        this.middlename = newMiddlename;
    }

    public void setSex(String newSex) {
        this.sex = newSex;
    }

    public void setDate(String newDate) {
        this.date = newDate;
    }

    public void setLanguageId(int languageId) {
        this.languageId = languageId;
    }

    public void setGroupId(int groupId) {
        this.groupId = groupId;
    }

    public String toString() {
        return "ID: " + this.id + ", Name: " + this.name + ", Surname: " + this.surname + ", Middlename: " + this.middlename +  ", Sex: " + this.sex +", Date: " + this.date + ", Language id: " + this.languageId + ", Group number: " + this.groupId;
    }
}
