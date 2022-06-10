package com.company;

import java.io.Serializable;

public class Group implements Serializable {
    public int id;
    public String name;
    public String courseId;
    public String speciality;
    public Group() {}

    // GROUP GETTERS
    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }
    
    public String getCourseId() {
        return courseId;
    }

    public String getSpeciality() {
        return speciality;
    }

    // GROUP SETTERS
    public void setId(int id) {
        this.id = id;
    }

    public void setName(String name) {
        this.name = name;
    }
    
    public void setCourseId(String courseId) {
        this.courseId = courseId;
    }

    public void setSpeciality(String speciality) {
        this.speciality = speciality;
    }

    public String toString() {
        return "ID: " + id + ", Group name: " + name + ", Course number: " + courseId + ", Speciality: " + speciality;
    }
}
