import java.util.List;
import java.util.ArrayList;
import java.time.LocalDate;
import java.io.BufferedReader;
import java.io.IOException;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;



class Car{
    public int govnumber;
    public String name;
    public String driver;
    public List<Flight> cases;
    public int max_len = 0;
    public int avg_mass = 0;
    public Car(int govnumber, String name, String driver){
        this.govnumber = govnumber;
        this.name = name; 
        this.driver = driver; 
        this.govnumber = govnumber;
        this.cases = new ArrayList<Flight>();
    }
    public String toString(){
        return "\nGoverment number - " + govnumber  + ". Brand -  " + name + ". Driver name - " + driver + ". Total mileage - " + max_len + ". Average mass - " + avg_mass;
    }
}

class Flight{
    public int mass;
    public LocalDate date;

    public int length;
    public int govnumber;
    public Flight(int mass,LocalDate date,int length,int govnumber){
        this.mass = mass;
        this.date = date;
        this.length = length;
        this.govnumber = govnumber;
    }
    public String toString(){
        return "\nDate: " + date.toString() + "\nLoad weight:  " + mass + "\nRoute length: " + length + "\nGov. number: " + govnumber + "\n";
    }

}

class Basic_reader{
    public String[] file_names;
    public Basic_reader(String[] file_names){
        this.file_names = file_names;
    }
    public List<Car> read_ad(){
        List<Car> l = new ArrayList<Car>();
        return l;
    }
    public List<Flight> read_dl(){
        List<Flight> l = new ArrayList<Flight>();
        return l;
    }
    public Database read_data(){
        return new Database(read_ad(), read_dl());
    }
}

class XML_reader extends Basic_reader{
    public XML_reader(String[] file_names){
        super(file_names);
    }
    public List<Car> read_ad(){
        List<Car> l = super.read_ad();
        try {
            InputStream stream = new FileInputStream(file_names[0]);
            XMLInputFactory factory = XMLInputFactory.newInstance();
            XMLStreamReader reader = factory.createXMLStreamReader(stream);
            int elementType;
            String tagName;

            int _govnumber = 0;
            String _name = "a";
            String _driver = "b";

            while(reader.hasNext()) {
                elementType = reader.next();
                switch(elementType) {
                    case XMLStreamReader.START_ELEMENT: {
                        tagName = reader.getLocalName();
                        switch(tagName) {
                            case "govnumber":
                                _govnumber = Integer.parseInt(reader.getElementText());
                                break;
                            case "name":
                                _name = reader.getElementText();
                                break;
                            case "driver":
                                _driver = reader.getElementText();
                                break;
                        }
                        break;
                    }
                    case XMLStreamReader.END_ELEMENT: {
                        tagName = reader.getLocalName();
                        switch(tagName) {
                            case "Car":
                                l.add(new Car(_govnumber, _name, _driver));
                                break;
                        }
                        break;
                    }
                }
            }
            reader.close();
        } catch(FileNotFoundException | XMLStreamException e) {}
        return l;
    }
    public List<Flight> read_dl(){
        List<Flight> l = super.read_dl();
        try {
            InputStream stream = new FileInputStream(file_names[1]);
            XMLInputFactory factory = XMLInputFactory.newInstance();
            XMLStreamReader reader = factory.createXMLStreamReader(stream);
            int elementType;
            String tagName;

            int _length = 0;
            LocalDate _date = LocalDate.now();
            int _mass = 0;
            int _govnumber = 0;
            while(reader.hasNext()) {
                elementType = reader.next();
                switch(elementType) {
                    case XMLStreamReader.START_ELEMENT: {
                        tagName = reader.getLocalName();
                        switch(tagName) {
                            case "length":
                                _length = Integer.parseInt(reader.getElementText());
                                break;
                            case "date":
                                _date = LocalDate.parse(reader.getElementText());
                                break;
                            case "mass":
                                _mass =  Integer.parseInt(reader.getElementText());
                                break;
                            case "govnumber":
                                _govnumber = Integer.parseInt(reader.getElementText());
                                break;
                        }
                        break;
                    }
                    case XMLStreamReader.END_ELEMENT: {
                        tagName = reader.getLocalName();
                        switch(tagName) {
                            case "Flight":
                                l.add(new Flight(_length, _date, _mass, _govnumber));
                                break;
                        }
                        break;
                    }
                }
            }
            reader.close();
        } catch(FileNotFoundException | XMLStreamException e) {}
        return l;
    }
}


class CSV_reader extends Basic_reader{
    public CSV_reader(String[] file_names){
        super(file_names);
    }
    public List<Car> read_ad(){
        List<Car> l = super.read_ad();
        Path pathToFile = Paths.get(file_names[0]);
        try (BufferedReader br = Files.newBufferedReader(pathToFile)) { 
            String line = br.readLine();
            while (line != null) {
            String[] attributes = line.split(",");
            if (line == "") { break; }
            int _govnumber = Integer.parseInt(attributes[0]);
            String _name = attributes[1];
            String _driver = attributes[2];

            l.add(new Car(_govnumber, _name, _driver));
            line = br.readLine(); } } 
        catch (IOException ioe) { ioe.printStackTrace(); }

        return l;
    }
    public List<Flight> read_dl(){
        List<Flight> l = super.read_dl();
        Path pathToFile = Paths.get(file_names[1]);
        try (BufferedReader br = Files.newBufferedReader(pathToFile)) { 
            String line = br.readLine();
            while (line != null) {
            String[] attributes = line.split(",");

            LocalDate _date = LocalDate.parse(attributes[0]);
            int _mass = Integer.parseInt(attributes[1]);
            int _length = Integer.parseInt(attributes[2]);
            int _govnumber = Integer.parseInt(attributes[3]);;
            l.add(new Flight(_length, _date, _mass, _govnumber));
            line = br.readLine(); } } 
        catch (IOException ioe) { ioe.printStackTrace(); }
        return l;
    }
}

class Reader_fact{
    static Reader_fact instance=null;
    static String ext;
    static String[] file_names;
    static Basic_reader reader;
    public Reader_fact(){}
    public static Reader_fact get_instance(String ext, String[] file_names){
        if(instance==null){
            ext = ext;
            file_names = file_names;
            if(ext.equals("csv"))
                reader = new CSV_reader(file_names);
            else
                reader = new XML_reader(file_names);
            instance = new Reader_fact();
        }
        return instance;
    }
    public Basic_reader get_reader(){
        return this.reader;
    } 
}

class Database{
    public List<Car> ad;
    public List<Flight> dl;
    public Database(List<Car> ad, List<Flight> dl){
        this.ad = ad;
        this.dl = dl;
        bind_cases();
    }
    
    public void bind_cases() {
        for (Car a : ad) {
            int max_length = 0;
            int mass_sum = 0;
            int counter = 0;
            for (Flight d : dl) {
                if (a.govnumber == d.govnumber) {
                    a.cases.add(d);
                    max_length += d.length;
                    mass_sum += d.mass;
                    counter++;
                }
            }
            a.max_len = max_length;
            a.avg_mass = mass_sum/counter;
        }
    }
    public void print_all(){
        System.out.println("Машины:");
        for(Car a : ad)
            System.out.println(a.toString());
        System.out.println("Рейсы:");
        for(Flight d : dl){
            System.out.println(d.toString());
            System.out.println();}
    }

    public void print_profiles(){
        for(Car a : ad){
            System.out.println("#########################");
            System.out.println(a.toString());
        System.out.println();
        for(Flight d : a.cases){
            System.out.println("-------------------------");
            System.out.println(d.toString());
            System.out.println("-------------------------");
            System.out.println();}
        System.out.println("#########################");
            }       
    }
}



public class Cars {
    public static Database db;
    public static Reader_fact factory;
    public static void main(String[] args) throws ClassNotFoundException{
        //factory = new Reader_fact().get_instance(args[0], new String[]{args[1],args[2]});
        factory = new Reader_fact().get_instance("csv", new String[] {"drivers.csv","flights.csv"});
        //System.out.println("xxxxxxxx");
        db = factory.get_reader().read_data();
        db.print_profiles();
    }
}