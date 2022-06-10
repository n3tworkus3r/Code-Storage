package service;

import dao.EquipmentDAO;
import dao.SubdivisionDAO;
import dao.Transaction;
import dao.WorkingDAO;
import entity.Equipment;
import entity.Subdivision;
import entity.Working;
import exception.PersistentException;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class WorkingServiceImpl extends ServiceImpl implements WorkingService {
    public WorkingServiceImpl(Transaction transaction) {
        super(transaction);
    }

    private void build(List<Working> workings) throws PersistentException {
        Map<Integer, Equipment> equipments = new HashMap<Integer, Equipment>();
        EquipmentDAO equipmentDAO = getTransaction().createDao(EquipmentDAO.class);
        for(Working working : workings) {
            if(equipments.containsKey(working.getEquipment().getIdentity())) {
                working.setEquipment(equipments.get(working.getEquipment().getIdentity()));
            } else {
                Equipment equipment = equipmentDAO.read(working.getEquipment().getIdentity());
                working.setEquipment(equipment);
                equipments.put(equipment.getIdentity(), equipment);
            }
        }
        Map<Integer, Subdivision> subdivisions = new HashMap<Integer, Subdivision>();
        SubdivisionDAO subdivisionDAO = getTransaction().createDao(SubdivisionDAO.class);
        for(Working working : workings) {
            if(subdivisions.containsKey(working.getSubdivision().getIdentity())) {
                working.setSubdivision(subdivisions.get(working.getSubdivision().getIdentity()));
            } else {
                Subdivision subdivision = subdivisionDAO.read(working.getSubdivision().getIdentity());
                working.setSubdivision(subdivision);
                subdivisions.put(subdivision.getIdentity(), subdivision);
            }
        }
    }

    @Override
    public List<Working> findByEquipment(Equipment equipment) throws PersistentException {
        WorkingDAO dao = getTransaction().createDao(WorkingDAO.class);
        List<Working> workings = dao.readByEquipment(equipment);
        build(workings);
        return workings;
    }

    @Override
    public List<Working> findBySubdivision(Subdivision subdivision) throws PersistentException {
        WorkingDAO dao = getTransaction().createDao(WorkingDAO.class);
        List<Working> workings = dao.readBySubdivision(subdivision);
        build(workings);
        return workings;
    }

    @Override
    public List<Working> findAll() throws PersistentException {
        WorkingDAO workingDAO = getTransaction().createDao(WorkingDAO.class);
        List<Working> workings = workingDAO.readAll();
        build(workings);
        return workings;
    }

    @Override
    public void save(Working working) throws PersistentException {
        WorkingDAO dao = getTransaction().createDao(WorkingDAO.class);
        if(working.getIdentity() != null) {
            dao.update(working);
        } else {
            dao.create(working);
        }
    }

    @Override
    public void delete(Integer identity) throws PersistentException {
        WorkingDAO dao = getTransaction().createDao(WorkingDAO.class);
        dao.delete(identity);
    }
}
