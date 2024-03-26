import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class Simulator {
    public static void main(String[] args) throws IOException {
        String line = ""+args[0]+"";
        int numServer=0, numCat=0, numJob=0;
        assignCounts(line, numServer, numCat, numJob);
        List<Categoria> catList = makeCatList(line);
        List<Server> serverList = makeSerList(numServer);
        EventsPQ pq = new EventsPQ();
        catList.forEach(s->{
            s.makeLastArrivalTime();
            Event e = s.makeArrivalEvent();
            pq.getPqlist().add(e);
        });
        pq.getPqlist().forEach(System.out::println);

        /*while(numJob>0){
            EventsPQ pq = new EventsPQ();
            catList.forEach(s->{
                s.makeLastArrivalTime();
                Event e = s.makeArrivalEvent();
                pq.getPqlist().add(e);
            });*/











    }
    //Metodo che ritorna la lista che categorie desiderate

    public static List<Categoria> makeCatList(String line) throws IOException {
        FileReader file = new FileReader(line);
        Scanner scanner = new Scanner(file);
        List<Categoria> list = new LinkedList<>();
        int count=0;
        while(scanner.hasNextLine()) {
            count++;
            String s = scanner.nextLine();
            if(count!=1)
            {
                Scanner in = new Scanner(s);
                String[]str = s.split(",");
                list.add(new Categoria(Integer.parseInt(str[0]), Integer.parseInt(str[1]),
                Integer.parseInt(str[2]),Integer.parseInt(str[3]), count-1));
            }

        }
        return list;
    }
    //Metodo per assegnare a c1, c2, c3 rispettivamente i valori del numero di server, categorie e job
    public static void assignCounts(String line, int c1, int c2, int c3) throws FileNotFoundException {
        FileReader file = new FileReader(line);
        Scanner scanner = new Scanner(file);
        String s = scanner.nextLine();
        String[]str = s.split(",");
        c1=Integer.parseInt(str[0]);
        c2=Integer.parseInt(str[1]);
        c3=Integer.parseInt(str[2]);
    }
    //Metodo che ritorna una lista di Server con un numero n di elementi
    public static List<Server> makeSerList(int n){
        List<Server> list = new LinkedList<>();
        for(int i=0; i<n; i++){
            list.add(new Server());
        }
        return list;
    }






}


