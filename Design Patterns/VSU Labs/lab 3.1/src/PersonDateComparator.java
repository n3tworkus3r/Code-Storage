public class PersonDateComparator implements java.util.Comparator<Person> {
    @Override
    public int compare(Person p1, Person p2) {
        java.util.Calendar c1 = java.util.Calendar.getInstance(), c2 = java.util.Calendar.getInstance();
        c1.setTime(p1.getBirthday());
        c2.setTime(p2.getBirthday());
        return c1.compareTo(c2);
    }
    @Override
    public String toString(){return "По дате";}
}
