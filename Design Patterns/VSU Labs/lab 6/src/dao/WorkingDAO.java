package dao;

import entity.Equipment;
import entity.Subdivision;
import entity.Working;
import exception.PersistentException;

import java.util.List;

public interface WorkingDAO extends DAO<Working> {
    List<Working> readByEquipment(Equipment equipment) throws PersistentException;

    List<Working> readBySubdivision(Subdivision subdivision) throws  PersistentException;

    List<Working> readAll() throws PersistentException;
}
