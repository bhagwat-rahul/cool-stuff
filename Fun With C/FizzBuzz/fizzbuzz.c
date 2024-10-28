#include <stdio.h>

void fizzbuzz(char *result, size_t maxsize) {
    int n = 60;
    char FIZZ[5]="Fizz";
    char BUZZ[5]="Buzz";
    int fizz = 3;
    int buzz = 5;
    size_t written = 0;
    size_t remaining = maxsize;
    int ret;
    for (int i = 0; i<= n; i++)
        {
            if (i % fizz == 0 && i % buzz ==0)
            {
                ret = snprintf(result + written, remaining, "%s%s", FIZZ, BUZZ );
            }
            else if (i % buzz == 0)
                {
                    ret = snprintf(result + written, remaining, "%s", BUZZ );
                }
                else if (i % fizz == 0)
                {
                    ret = snprintf(result + written, remaining, "%s", FIZZ );
                }
            else
            {
                ret = snprintf(result + written, remaining, "%d", i );
            }
            written += ret;
            remaining -= ret;
            if (i == n)
                {
                    int period = snprintf(result + written, remaining, ".");
                    written += period;
                    remaining -= period;
                }
            else
            {
                int comma = snprintf(result + written, remaining, ", ");
                written += comma;
                remaining -= comma;
            }
        }
}


int main()
{
    char output[100000] = {0};
    fizzbuzz(output, sizeof(output));
     // TODO: Add unit test instead of print statement
    printf("%s", output);
    return 0;
}
