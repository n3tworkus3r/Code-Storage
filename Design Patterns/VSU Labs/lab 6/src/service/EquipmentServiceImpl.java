package service;

import dao.EquipmentDAO;
import dao.Transaction;
import dao.WorkingDAO;
import entity.Equipment;
import entity.Working;
import exception.IntegrityViolationException;
import exception.PersistentException;

import java.util.List;

public class EquipmentServiceImpl extends ServiceImpl implements EquipmentService {
    public EquipmentServiceImpl(Transaction transaction) throws PersistentException {
        super(transaction);
    }

    @Override
    public List<Equipment> findAll() throws PersistentException {
        EquipmentDAO authorDAO = getTransaction().createDao(EquipmentDAO.class);
        return authorDAO.readAll();
    }

    @Override
    public void save(Equipment author) throws PersistentException {
        EquipmentDAO authorDAO = getTransaction().createDao(EquipmentDAO.class);
        if(author.getIdentity() != null) {
            authorDAO.update(author);
        } else {
            authorDAO.create(author);
        }
    }

    @Override
    public void delete(Integer identity) throws PersistentException {
        EquipmentDAO authorDAO = getTransaction().createDao(EquipmentDAO.class);
        Equipment author = authorDAO.read(identity);
        if(author != null) {
            WorkingDAO workingDAO = getTransaction().createDao(WorkingDAO.class);
            if(workingDAO.readByEquipment(author).isEmpty()) {
                authorDAO.delete(identity);
            } else {
                throw new IntegrityViolationException();
            }
        }
    }
}
