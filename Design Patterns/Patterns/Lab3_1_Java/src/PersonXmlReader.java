import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;

public class PersonXmlReader {
    public static List<Person> readFromFile(String fileName) {
        List<Person> persons = new ArrayList<>();
        SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
        try {
            InputStream stream = new FileInputStream(fileName);
            XMLInputFactory factory = XMLInputFactory.newInstance();
            XMLStreamReader reader = factory.createXMLStreamReader(stream);
            Person person = null;
            int elementType;
            String tagName;
            while(reader.hasNext()) {
                elementType = reader.next();
                switch(elementType) {
                    case XMLStreamReader.START_ELEMENT: {
                        tagName = reader.getLocalName();
                        switch(tagName) {
                            case "person":
                                person = new Person();
                                break;
                            case "first-name":
                                person.setFirstName(reader.getElementText());
                                break;
                            case "middle-name":
                                person.setMiddleName(reader.getElementText());
                                break;
                            case "last-name":
                                person.setLastName(reader.getElementText());
                                break;
                            case "birthday":
                                String birthday = reader.getElementText();
                                person.setBirthday(format.parse(birthday));
                                break;
                            case "post_address":
                                person.setPostAddress(reader.getElementText());
                                break;
                        }
                        break;
                    }
                    case XMLStreamReader.END_ELEMENT: {
                        tagName = reader.getLocalName();
                        switch(tagName) {
                            case "person":
                                persons.add(person);
                                break;
                        }
                        break;
                    }
                }
            }
            reader.close();
        } catch(FileNotFoundException | XMLStreamException | ParseException e) {}
        return persons;
    }
}