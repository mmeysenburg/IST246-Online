public class ParamCheck {
    private static void foo(int x) {
        System.out.println("Foo says: You sent me: " + x);
    }

    public static void main(String[] args) {
        foo(13);
        foo(13.13);
    }
}