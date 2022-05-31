import java.util.Calendar;

public class PersonDoWComparator implements java.util.Comparator<Person> {
    @Override
    public int compare(Person p1, Person p2) {
        Calendar c1 = Calendar.getInstance(), c2 = Calendar.getInstance();
        c1.setTime(p1.getBirthday());
        c2.setTime(p2.getBirthday());
        return Integer.compare(c1.get(Calendar.DAY_OF_WEEK), c2.get(Calendar.DAY_OF_WEEK));
    }
    @Override
    public String toString(){return "По дню недели";}
}
