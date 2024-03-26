
public class Event {
    private static int count=0;
    Categoria categoria;
    String type;
    double time;
    int index;

    public Event(Categoria categoria, String type, double time) {
        this.categoria = categoria;
        this.type = type;
        this.time = time;
        this.index = count;
        count++;
    }

    @Override
    public String toString() {
        return "Event{" +
                "categoria=" + categoria +
                ", type='" + type + '\'' +
                ", time=" + time +
                ", index=" + index +
                '}';
    }
}
