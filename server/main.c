/* this is a server in c, relying on a bunch of abstractions
   (kernel , driver, tcp ip) to start with. rm 1 by 1 as makes sense. */

# include <stdio.h>

int main()
{
    while (1) 
    {
        puts("running");
    }
    return 0;
}
