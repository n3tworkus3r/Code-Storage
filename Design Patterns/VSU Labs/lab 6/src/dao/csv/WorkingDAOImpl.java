package dao.csv;

import dao.WorkingDAO;
import entity.Equipment;
import entity.Subdivision;
import entity.Working;
import exception.PersistentException;

import java.io.File;
import java.io.IOException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.List;
import java.util.Locale;

public class WorkingDAOImpl extends BaseDAOImpl<Working> implements WorkingDAO {
    public WorkingDAOImpl(File file, File temp) {
        super(file, temp);
    }

    @Override
    protected Working read(CSVReader reader) throws IOException, ParseException {
        DateFormat format = DateFormat.getDateInstance(DateFormat.MEDIUM, Locale.GERMANY);
        if(reader != null) {
            String[] line = reader.read();
            if(line != null) {
                Working working = new Working();
                working.setIdentity(Integer.parseInt(line[0]));
                Equipment equipment = new Equipment();
                equipment.setIdentity(Integer.parseInt(line[1]));
                working.setEquipment(equipment);
                Subdivision subdivision = new Subdivision();
                subdivision.setIdentity(Integer.parseInt(line[2]));
                working.setSubdivision(subdivision);
                working.setDateOfInput(format.parse(line[3]));
                return working;
            }
        }
        return null;
    }

    @Override
    protected void write(Working working, CSVWriter writer) throws IOException {
        DateFormat format = DateFormat.getDateInstance(DateFormat.MEDIUM);
        writer.write(new String[]{
                working.getIdentity().toString(),
                working.getEquipment().getIdentity().toString(),
                working.getSubdivision().getIdentity().toString(),
                format.format(working.getDateOfInput())
        });
    }

    @Override
    public List<Working> readBySubdivision(final Subdivision subdivision) throws PersistentException {
        return read(new BaseDAOImpl.Filter<Working>() {
            @Override
            public boolean check(Working working) {
                return working.getSubdivision().equals(subdivision);
            };
        });
    }

    @Override
    public List<Working> readByEquipment(final Equipment equipment) throws PersistentException {
        return read(new BaseDAOImpl.Filter<Working>() {
            @Override
            public boolean check(Working working) {
                return working.getEquipment().equals(equipment);
            }
            ;
        });
    }

    public List<Working> readAll() throws PersistentException {
        return read(new BaseDAOImpl.Filter<Working>() {
            @Override
            public boolean check(Working type) {
                return true;
            }
        });
    }
}
