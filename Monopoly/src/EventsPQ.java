import java.util.LinkedList;
import java.util.List;

public class EventsPQ {
    private List<Event> pqlist;

    public EventsPQ() {
        this.pqlist = new LinkedList<>();
    }

    public List<Event> getPqlist() {
        return pqlist;
    }
}
