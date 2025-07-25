// A prime number is a number divisible only by 1 and itself.
// A prime sieve is an algorithm for finding prime numbers by progressively eliminating non-prime numbers.
// The Sieve of Eratosthemes is one such algorithm. It works like this:
// Create a list of numbers from 2 through n.
// Eliminate all multiples of 2, except 2 itself.
// Find the smallest number remaining in the list after 2 (in this case 3).
// Eliminate all multiples of 3, except 3 itself.
// Find the smallest number remaining in the list after 3.
// Eliminate all multiples of that number, except that number itself.
// Keep going with this process until you've worked up to n.
// Implement the Sieve of Eratosthemes using C. You don't have to do it exactly like the algorithm above, as long as it works.

// There are 168 prime numbers up to the number 1,000. There are 1,229 prime numbers up to the number 10,000. There are 9,592 prime numbers up to the number 100,000. There are 78,498 prime numbers up to the number 1,000,000.
# include <stdio.h>

void removeMultiples(int *list, int *len) {
    for (int i = 0; i < *len; i++) {
        int current = list[i];
        if (current * current > list[*len - 1]) break; // Stop if current^2 > largest number

        // Remove multiples of the current number
        for (int j = i + 1; j < *len; j++) {
            if (list[j] % current == 0) {
                // Shift the array to remove the multiple
                for (int k = j; k < *len - 1; k++) {
                    list[k] = list[k + 1];
                }
                (*len)--; // Reduce the array length
                j--; // Check the new value at position j
            }
        }
    }
}

int main()
{
    int number_list[999] = {0};
    int len = 999;
    for (int i = 2; i <= 1000; i++) {
        number_list[i-2] = i;
    }
    removeMultiples(number_list, &len);
    printf("%d\n", len);
    return 0;
}
