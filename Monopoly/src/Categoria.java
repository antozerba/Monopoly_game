import java.util.Random;

public class Categoria{
    float arrivalL, serviceL;
    int seedA, seedL;
    int count;
    double lastArrivalTime, lastServiceTime;
    Random randomA;
    Random randomS;

    public Categoria() {
    }

    public Categoria(int arrivalL, int serviceL, int seedA, int seedL, int count) {
        this.arrivalL = arrivalL;
        this.serviceL = serviceL;
        this.seedA = seedA;
        this.seedL = seedL;
        this.count = count;
        this.lastArrivalTime=0;
        this.lastServiceTime=0;
        this.randomA = new Random(this.seedA);
        this.randomS = new Random(this.seedL);

    }

    @Override
    public String toString() {
        return "Categoria{" +
                "arrivalL=" + arrivalL +
                ", serviceL=" + serviceL +
                ", seedA=" + seedA +
                ", seedL=" + seedL +
                ", count=" + count +
                ", lastArrivalTime=" + lastArrivalTime +
                ", lastServiceTime=" + lastServiceTime +
                '}';
    }
    public void makeLastArrivalTime(){
        float a = randomA.nextFloat();
        double x= (-Math.log(1.0-a)*(1.0/arrivalL));
        System.out.println("X="+x);
        lastArrivalTime = lastArrivalTime + x;
        System.out.println("LA="+lastArrivalTime);
    }
    public Event makeArrivalEvent(){
        return new Event(this, "A", lastArrivalTime);
    }
}
