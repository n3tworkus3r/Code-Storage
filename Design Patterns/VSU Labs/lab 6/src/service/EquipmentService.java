package service;

import entity.Equipment;
import exception.PersistentException;

import java.util.List;

public interface EquipmentService extends Service {
    List<Equipment> findAll() throws PersistentException;

    void save(Equipment author) throws PersistentException;

    void delete(Integer identity) throws PersistentException;
}
