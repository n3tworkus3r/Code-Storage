package com.company;

import java.io.*;
import java.util.HashMap;
import java.util.Map;

public class Data implements Serializable {
    //public static final String path = ".;
    public static final String path = "D:\\Projects\\Java\\DP5\\DP5\\src\\Data\\data.txt";
    public int makerId = 0;
    public int studentId = 0;
    public int sectionId = 0;

    public Map<Integer, Language> makerMap = new HashMap<>();
    public Map<Integer, Student> studentMap = new HashMap<>();
    public Map<Integer, Group> sectionMap = new HashMap<>();

    public void addLanguage(Language maker) {
        maker.setLanguageId(makerId++);
        makerMap.put(maker.getId(), maker);
    }

    public void deleteLanguage(Language maker) {
        makerMap.remove(maker.getId());
    }

    public Map<Integer, Language> getLanguageMap() {
        return makerMap;
    }

    public void addStudent(Student student) {
        student.setId(studentId++);
        studentMap.put(student.getId(), student);
    }

    public void deleteStudent(Student student) {
    	studentMap.remove(student.getId());
    }

    public Map<Integer, Student> getStudentMap() {
        return studentMap;
    }

    public void addGroup(Group section) {
        section.setId(sectionId++);
        sectionMap.put(section.getId(), section);
    }

    public void deleteGroup(Group section) {
        sectionMap.remove(section.getId());
    }

    public Map<Integer, Group> getGroupMap() {
        return sectionMap;
    }

    public void saveData() throws IOException {
        FileOutputStream fos = new FileOutputStream(path, false);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        oos.writeObject(this);
    }

    public static Data loadData() {
        try {
            FileInputStream fis = new FileInputStream(path);
            ObjectInputStream ois = new ObjectInputStream(fis);
            System.out.println("Completed!");
            return (Data)ois.readObject();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        return new Data();
    }
}
