package service;

import dao.SubdivisionDAO;
import dao.Transaction;
import dao.WorkingDAO;
import entity.Subdivision;
import exception.IntegrityViolationException;
import exception.PersistentException;

import java.util.List;

public class SubdivisionServiceImpl extends ServiceImpl implements SubdivisionService {
    public SubdivisionServiceImpl(Transaction transaction) throws PersistentException {
        super(transaction);
    }

    @Override
    public List<Subdivision> findAll() throws PersistentException {
        SubdivisionDAO subdivisionDAO = getTransaction().createDao(SubdivisionDAO.class);
        return subdivisionDAO.readAll();
    }

    @Override
    public void save(Subdivision author) throws PersistentException {
        SubdivisionDAO authorDAO = getTransaction().createDao(SubdivisionDAO.class);
        if(author.getIdentity() != null) {
            authorDAO.update(author);
        } else {
            authorDAO.create(author);
        }
    }

    @Override
    public void delete(Integer identity) throws PersistentException {
        SubdivisionDAO authorDAO = getTransaction().createDao(SubdivisionDAO.class);
        Subdivision author = authorDAO.read(identity);
        if(author != null) {
            WorkingDAO workingDAO = getTransaction().createDao(WorkingDAO.class);
            if(workingDAO.readBySubdivision(author).isEmpty()) {
                authorDAO.delete(identity);
            } else {
                throw new IntegrityViolationException();
            }
        }
    }
}
