package service;

import entity.Equipment;
import entity.Subdivision;
import entity.Working;
import exception.PersistentException;

import java.util.List;

public interface WorkingService extends Service {
    List<Working> findByEquipment(Equipment equipment) throws PersistentException;

    List<Working> findBySubdivision(Subdivision subdivision) throws PersistentException;

    List<Working> findAll() throws PersistentException;

    void save(Working book) throws PersistentException;

    void delete(Integer identity) throws PersistentException;
}
