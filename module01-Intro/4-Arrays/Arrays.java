import java.util.Random;

public class Arrays {
    private static int sum(int[] arr) {
        int s = 0;
        for(int i : arr) {
            s += i;
        }

        return s;
    }
    public static void main(String[] args) {
        // random number generator
        Random prng = new Random();

        // make an array with 100000 elements, fill with random values
        int[] arr = new int[100000];
        for(int i = 0; i < 100000; i++) {
            arr[i] = prng.nextInt(100);
        }

        // output the sum
        System.out.println("The sum of the array is: " + sum(arr));
    }
}