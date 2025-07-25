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
            char line[15];
            fgets(line, sizeof(line), puzzleInput);
            sscanf(line, "%d %d", &listA[i], &listB[i]);
        }
    fclose(puzzleInput);
}

// create helper func to find smallest int
void sortList(int *list, int len, int *sortedList)
{
    for (int i = 0; i < len; i++)
        sortedList[i] = list[i];

    for (int i = 0; i < len - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < len; j++)
        {
            if (sortedList[j] < sortedList[minIndex])
            {
                minIndex = j;
            }
        }
        int temp = sortedList[i];
        sortedList[i] = sortedList[minIndex];
        sortedList[minIndex] = temp;
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

int getSimilarityScore(int *listA, int *listB)
{
    int score = 0;
    for (int i = 0; i < 999; i++)
        {
            int temp = listA[i];
            for (int j = 0; j < 999; j++)
                {
                    if (temp == listB[j])
                        {
                            score+=temp;
                        }
                }
        }
    return score;
}

int main()
{
    // initialise both arrays
    int a[1000];
    int b[1000];
    int aSorted[1000] = {0};
    int bSorted[1000] = {0};
    scanFilesCreateLists(a,b, 1000);
    sortList(a, 1000, aSorted);
    sortList(b, 1000, bSorted);
    int totalDistance = compareList(aSorted, bSorted, 1000);;
    int similarityScore = getSimilarityScore(aSorted, bSorted);
    printf("Result: %d\n", totalDistance);
    printf("Similarity Score: %d\n", similarityScore);
    return 0;
}
