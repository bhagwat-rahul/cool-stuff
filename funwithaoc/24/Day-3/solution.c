# include <stdio.h>

void scanFilesCreateMemory(char *list, int lineCount)
{
    FILE *puzzleInput = fopen("input.txt", "r");
    if (puzzleInput == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < lineCount; i++)
        {
            char line[5000];
            fgets(line, sizeof(line), puzzleInput);
            sscanf(line, "%s", &list[i]);
        }
    fclose(puzzleInput);
}

void createUncorruptedList(char *validSequence, char *corruptedList, char *uncorruptedList, int corruptedListLen, int uncorruptedListLen)
{

}

int multiplyAndSumList(char *uncorruptedList, int uncorruptedListLen)
{
    return 0;
}

int main()
{
    char initialMemory[20000];
    char uncorruptedMemory[20000];
    char validSequence[20] = "mul(xxx,xxx)";
    scanFilesCreateMemory(initialMemory, 6);
    createUncorruptedList(validSequence, initialMemory, uncorruptedMemory, 20000, 20000);
    printf("Sum of Multiplications: %d\n", multiplyAndSumList(uncorruptedMemory, 20000));
    return 0;
}
