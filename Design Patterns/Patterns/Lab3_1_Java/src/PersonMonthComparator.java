import java.util.Calendar;

public class PersonMonthComparator implements java.util.Comparator<Person> {
    @Override
    public int compare(Person p1, Person p2) {
        Calendar c1 = Calendar.getInstance(), c2 = Calendar.getInstance();
        c1.setTime(p1.getBirthday());
        c2.setTime(p2.getBirthday());
        return Integer.compare(c1.get(Calendar.MONTH), c2.get(Calendar.MONTH));
    }
    @Override
    public String toString(){return "По месяцу";}
}
