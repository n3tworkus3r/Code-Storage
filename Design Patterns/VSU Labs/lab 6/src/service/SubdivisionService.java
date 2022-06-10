package service;

import entity.Subdivision;
import exception.PersistentException;

import java.util.List;

public interface SubdivisionService extends Service {
    List<Subdivision> findAll() throws PersistentException;

    void save(Subdivision author) throws PersistentException;

    void delete(Integer identity) throws PersistentException;
}
