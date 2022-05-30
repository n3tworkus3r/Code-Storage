public class PersonIndexComparator implements java.util.Comparator<Person> {
    @Override
    public int compare(Person p1, Person p2) {
        return Integer.compare(Integer.parseInt(p1.getPostAddress().substring(p1.getPostAddress().length()-6,6)),Integer.parseInt(p2.getPostAddress().substring(p2.getPostAddress().length()-6,6)));
    }
    @Override
    public String toString(){return "По индексу";}
}
