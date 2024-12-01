# include <stdio.h>

void scanFilesCreateLists(int *listA, int *listB, int listSize)
{
    FILE *puzzleInput = fopen("input.txt", "r");
    fclose(puzzleInput);
}

// create helper func to find smallest int
void sortList(int *list, int len, int *sortedList)
{
    // sort from low to high into a new array
    int smallest = list[0];
    for (int j = 0; j < sizeof(sortedList); j++)
        {
        for (int i=j; i<sizeof(sortedList); i++)
            {
                if (smallest > list[i])
                    {
                        smallest = list[i];
                    }
            }
        sortedList[j]=smallest;
        }
}

int compareList(int *list1, int *list2, int listLen)
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
    int result = 0;
    int a[999];
    int b[999];
    int aSorted[999];
    int bSorted[999];
    scanFilesCreateLists(a,b, 999);
    sortList(a, 999, aSorted);
    sortList(a, 999, aSorted);
    result = compareList(aSorted, bSorted, 999);
    printf("%d", result);
    return 0;
}
