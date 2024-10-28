#include <stdio.h>

void fizzbuzz(char result[]) {
    int n = 60;
    char FIZZ[5]="Fizz";
    char BUZZ[5]="Buzz";
    int fizz = 3;
    int buzz = 5;
    int i = 0;
    for (i = 0; i<= n; i++)
        {
            if (i % fizz == 0 && i % buzz ==0)
            {
                // TODO: Looks like we are overwriting on same memory here
                snprintf(result, 100000, "%s%s", FIZZ, BUZZ );
                //printf("FizzBuzz\n");
            }
            if (i % buzz == 0)
                {
                    //printf("Fizz\n");
                }
            if (i % buzz == 0)
                {
                    //printf("Buzz\n");
                }
            else
            {
                //printf("%d\n", i);
            }
        }
}


int main()
{
    char output[100000];
    fizzbuzz(output);
    printf("%s", output);
    return 0;
}
