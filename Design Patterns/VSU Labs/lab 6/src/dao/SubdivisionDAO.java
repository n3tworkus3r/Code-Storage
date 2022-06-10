package dao;

import entity.Subdivision;
import exception.PersistentException;

import java.util.List;

public interface SubdivisionDAO extends DAO<Subdivision> {
    List<Subdivision> readAll() throws PersistentException;
}
