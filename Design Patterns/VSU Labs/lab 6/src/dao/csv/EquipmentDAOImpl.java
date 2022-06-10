package dao.csv;

import dao.EquipmentDAO;
import entity.Equipment;
import exception.PersistentException;

import java.io.File;
import java.io.IOException;
import java.util.List;

public class EquipmentDAOImpl extends BaseDAOImpl<Equipment> implements EquipmentDAO {
    public EquipmentDAOImpl(File file, File temp) {
        super(file, temp);
    }

    @Override
    protected Equipment read(CSVReader reader) throws IOException {
        if(reader != null) {
            String[] line = reader.read();
            if(line != null) {
                Equipment equipment = new Equipment();
                equipment.setIdentity(Integer.parseInt(line[0]));
                equipment.setName(line[1]);
                equipment.setPrice(Double.parseDouble(line[2]));
                equipment.setLifeTime(Integer.parseInt(line[3]));
                return equipment;
            }
        }
        return null;
    }

    @Override
    protected void write(Equipment equipment, CSVWriter writer) throws IOException {
        writer.write(new String[]{
                equipment.getIdentity().toString(),
                equipment.getName(),
                equipment.getPrice().toString(),
                equipment.getLifeTime().toString()
        });
    }

    @Override
    public List<Equipment> readAll() throws PersistentException {
        return read(new BaseDAOImpl.Filter<Equipment>() {
            @Override
            public boolean check(Equipment type) {
                return true;
            }
        });
    }
}
