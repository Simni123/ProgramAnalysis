package deps.normal;

// -> import java.util.ArrayList
// -> import java.util.Iterator
// -> import java.util.List
// -> import java.lang.Integer
// -> import java.lang.String

import java.util.ArrayList; //an actual import
import java.util.Iterator;
import java.util.List;

// A class to compute primes
public class Primes implements Iterable<Integer> {
    private final List<Integer> primes = new ArrayList<>();

    @Override
    public Iterator<Integer> iterator() {
        String testString = "Maybe an Example";
        return new PrimesIterator(); /* this should be Removed */
    }

    public class PrimesIterator implements Iterator<Integer> {
        private int current = 2;

        @Override
        public boolean hasNext() {
            return true;
        }

        @Override
        public Integer next() {
            while (true) {
                boolean isPrime = true;
                for (int i : primes) {
                    if (current % i == 0) {
                        isPrime = false;
                        break;
                    }
                }
                if (isPrime) {
                    if (current > primes.get(primes.size() - 1)) {
                        primes.add(current);
                    }
                    current += 1;
                    return current - 1;
                } else {
                    current += 1;
                }
            }
        }
    }

    public static void main(String[] args) {
        for (int i : new Primes()){/* dang
            this is Anoyung
           yep */System.out.println(i);
        }
        
    }

/* 
 * not 
 * part
 * of 
 * The
*/

}
