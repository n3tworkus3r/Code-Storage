package dao.csv;


import dao.SubdivisionDAO;
import entity.Subdivision;
import exception.PersistentException;

import java.io.File;
import java.io.IOException;
import java.util.List;

public class SubdivisionDAOImpl extends BaseDAOImpl<Subdivision> implements SubdivisionDAO {
    public SubdivisionDAOImpl(File file, File temp) {
        super(file, temp);
    }

    @Override
    protected Subdivision read(CSVReader reader) throws IOException {
        if(reader != null) {
            String[] line = reader.read();
            if(line != null) {
                Subdivision subdivision = new Subdivision();
                subdivision.setIdentity(Integer.parseInt(line[0]));
                subdivision.setName(line[1]);
                return subdivision;
            }
        }
        return null;
    }

    @Override
    protected void write(Subdivision subdivision, CSVWriter writer) throws IOException {
        writer.write(new String[]{
                subdivision.getIdentity().toString(),
                subdivision.getName()
        });
    }

    @Override
    public List<Subdivision> readAll() throws PersistentException {
        return read(new BaseDAOImpl.Filter<Subdivision>() {
            @Override
            public boolean check(Subdivision type) {
                return true;
            }
        });
    }
}
