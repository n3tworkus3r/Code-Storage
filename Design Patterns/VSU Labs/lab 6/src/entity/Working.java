package entity;

import java.util.Date;

public class Working extends Entity{
    private Equipment equipment;

    private Subdivision subdivision;

    private Date dateOfInput;

    public Equipment getEquipment() {
        return equipment;
    }

    public void setEquipment(Equipment equipment) {
        this.equipment = equipment;
    }

    public Subdivision getSubdivision() {
        return subdivision;
    }

    public void setSubdivision(Subdivision subdivision) {
        this.subdivision = subdivision;
    }

    public Date getDateOfInput() {
        return dateOfInput;
    }

    public void setDateOfInput(Date dateOfInput) {
        this.dateOfInput = dateOfInput;
    }
}
