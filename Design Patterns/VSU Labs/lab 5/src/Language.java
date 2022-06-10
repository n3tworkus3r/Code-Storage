package com.company;

import java.io.Serializable;

public class Language implements Serializable {
    public int LanguageId;
    public String LanguageName;

    public Language() {}

    public int getId() {
        return LanguageId;
    }

    public String getLanguageName() {
        return LanguageName;
    }


    public void setLanguageId (int LanguageId) {
        this.LanguageId = LanguageId;
    }

    public void setLanguageName(String LanguageName) {
    	this.LanguageName = LanguageName;
    }

    public String toString() {
        return "ID: " + LanguageId + ", Название: " + LanguageName;
    }
}
