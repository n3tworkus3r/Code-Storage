package dao;

import entity.Equipment;
import exception.PersistentException;

import java.util.List;

public interface EquipmentDAO extends DAO<Equipment> {
    List<Equipment> readAll() throws PersistentException;
}
