import java.util.Random;

public class ArrayBounds {
    public static void main(String[] args) {
        // random number generator
        Random prng = new Random();

        // make an array with 100000 elements, fill with 1's
        int[] arr = new int[100000];
        for(int i = 0; i < 100000; i++) {
            arr[i] = 1;
        }

        // overwrite the array values
        for(int i = 0; i <= 100000; i++) {
            arr[i] = prng.nextInt();

            // every so often report how we're doing
            if(i % 10000 == 0) {
                System.out.println("Overwriting element " + i);
            }
        }
    }
}