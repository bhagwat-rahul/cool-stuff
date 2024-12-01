# include <stdio.h>


// create helper func to find smallest int
void sortList(int *list, int len, int *sortedList)
{
    // sort from low to high into a new array
}

int listCompare(int *list1, int *list2, int listLen)
{
    int result = 0;
    // compare indexes and subtract larger from smaller
    for (int i = 0; i <listLen; i++)
        {
            if (list1[i]<list2[i])
                {
                    result+=list2[i]-list1[i];
                }
            else if (list1[i]>list2[i])
                {
                    result+=list1[i]-list2[i];
                }
            else {
                    result+=0;
                }
        }
    return result;
}

int main()
{
    // initialise both arrays
    int a[999];
    int b[999];
    int aSorted[999];
    int bSorted[999];
    int result = 0;

    result = listCompare(aSorted, bSorted, 999);
    printf("%d", result);
    return 0;
}
