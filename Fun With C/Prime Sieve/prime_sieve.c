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
# include <stdbool.h>


bool isMultiple(int number_to_check, int divisor)
{
    if (number_to_check == divisor)
        {
            return false;
        }
        else if (number_to_check % divisor == 0)
            {
                printf("Removing %d", number_to_check);
                return true;
            }
            else
            {
                return false;
            }
}

void removeIntFromArray(int *array, size_t buflen, int index_to_remove)
{
    for (size_t counter = index_to_remove; counter < buflen - 1; counter ++)
        {
            array[counter]=array[counter + 1];
        }
}

void removeMultiples(int list[], int num, int size)
{
    for (int i = 0; i < size; i++)
        {
            int j = 13;
                    if (isMultiple(num, j))
                        {
                            removeIntFromArray(list, size, i);
                        }
        }
}

int main()
{
    int number_list[998];
    int number_list_size = sizeof(number_list) / sizeof(number_list[0]);
    // Step 1; Create list from 2 to 1000
    for (int i = 0; i < number_list_size; i++) {
        number_list[i] = i + 2;
    }
    // Step 2: Remove all multiples of a number except itself
    for (int j = 0; j < number_list_size; j++)
    {
        removeMultiples(number_list, j, number_list_size);
    }

    printf("%d", number_list_size);
    return 0;
}
