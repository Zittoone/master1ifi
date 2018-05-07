import java.util.*;

public class EmploiDuTemps {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String line = sc.nextLine();

        int N = Integer.parseInt(line);

        List<Interval> intervals = new ArrayList<Interval>();

        for (int i = 0; i < N; i++) {
            String[] lineSplit = sc.nextLine().split(" ");
            int i1 = Integer.parseInt(lineSplit[0]);
            int i2 = Integer.parseInt(lineSplit[1]);
            intervals.add(new Interval(i1, i2));
        }

        // intervals.sort(Comparator.comparingInt(interval -> interval.start));
        Collections.sort(intervals, Comparator.comparingInt(i -> i.start));

        List<Classroom> classrooms = new ArrayList<>();
        classrooms.add(new Classroom());

        for (Interval current : intervals) {
            addInterval(current, classrooms);
        }

        System.out.println(classrooms.size());
    }

    public static Interval earliest(List<Interval> list){
        return list.stream().min(Comparator.comparingInt(interval -> interval.start)).get();
    }

    public static void addInterval(Interval interval, List<Classroom> classrooms) {
        for(Classroom classroom : classrooms) {
            if(classroom.addInterval(interval))
                return;
        }

        Classroom classroomNew = new Classroom();
        classroomNew.addInterval(interval);
        classrooms.add(classroomNew);
    }

    private static class Interval {
        public int start;
        public int end;

        public Interval(int start, int end) {
            this.start = start;
            this.end = end;
        }

        public boolean intersectWith(Interval interval) {
            return this.start < interval.end && (this.start > interval.start || interval.start < this.end);
        }
    }

    private static class Classroom {
        public List<Interval> intervals;

        public Classroom() {
            intervals = new ArrayList<>();
        }

        public boolean addInterval(Interval interval) {
            for(Interval i : intervals) {
                if(interval.intersectWith(i))
                    return false;
            }

            intervals.add(interval);
            return true;
        }

    }
}
