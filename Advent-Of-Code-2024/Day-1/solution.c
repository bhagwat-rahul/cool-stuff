# include <stdio.h>

void scanFilesCreateLists(int *listA, int *listB, int listSize)
{
    FILE *puzzleInput = fopen("input.txt", "r");
    if (puzzleInput == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < listSize; i++)
        {
            char line[14];
            fgets(line, sizeof(line), puzzleInput);
            sscanf(line, "%5d", &listA[i]);
            sscanf(line + 8, "%5d", &listB[i]);
        }
    fclose(puzzleInput);
}

// create helper func to find smallest int
void sortList(int *list, int len, int *sortedList)
{
    // sort from low to high into a new array
    int smallest = list[0];
    for (int j = 0; j < len; j++)
        {
        for (int i = j; i < len; i++)
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
    sortList(a, 999, bSorted);
    result = compareList(aSorted, bSorted, 999);
    printf("First A: %d\n", a[0]);
    printf("Last A: %d\n", a[998]);
    printf("First B: %d\n", b[0]);
    printf("Last B: %d\n", b[998]);
    printf("First Sorted A: %d\n", aSorted[0]);
    printf("Last Sorted A: %d\n", aSorted[998]);
    printf("First Sorted B: %d\n", bSorted[0]);
    printf("Last Sorted B: %d\n", bSorted[998]);
    printf("%d\n", result);
    return 0;
}
