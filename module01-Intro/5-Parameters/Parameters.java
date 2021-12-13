public class Parameters {

    private static void bar(double d) {
        d = 13;
        System.out.println("in bar, d = " + d);
    }

    public static void main(String[] args) {
        double md = 0;

        System.out.println("before bar, md = " + md);
        bar(md);
        System.out.println("after bar, md = " + md);
    }
}