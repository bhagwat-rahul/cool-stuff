# include <stdio.h>

void scanFilesCreateReports(int reportData[][300], int levelLen, int reportLen)
{
    FILE *input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < reportLen; i++)
        {
            char line[30];
            fgets(line, sizeof(line), input);
            sscanf(line, "%d %d %d %d %d", &reportData[i][0], &reportData[i][1], &reportData[i][2], &reportData[i][3], &reportData[i][4]);
            //printf("%d %d %d %d %d\n", reportData[i][0], reportData[i][1], reportData[i][2], reportData[i][3], reportData[i][4]);
        }
    fclose(input);
}

int checkReports(int reportBuf[][300], int levelLen, int reportLen)
{
    int safeCount = 0;
    for (int report = 0; report < reportLen; report++)
        {
            int level = 0;
            if
                (
                    reportBuf[report][level] > reportBuf[report][level + 1] &&
                    reportBuf[report][level + 1] > reportBuf[report][level + 2] &&
                    reportBuf[report][level + 2] > reportBuf[report][level + 3] &&
                    reportBuf[report][level + 3] > reportBuf[report][level + 4]
                )
                {
                    safeCount++;
                }
            else if
                (
                    reportBuf[report][level] < reportBuf[report][level + 1] &&
                    reportBuf[report][level + 1] < reportBuf[report][level + 2] &&
                    reportBuf[report][level + 2] < reportBuf[report][level + 3] &&
                    reportBuf[report][level + 3] < reportBuf[report][level + 4]
                )
                {
                    safeCount++;
                }
            else
                {
                    safeCount=safeCount;
                }
        }
    return safeCount;
}

int main()
{
    int safeLevelCount = 0;
    int reportData[30][300];
    scanFilesCreateReports(reportData, 5, 6);
    safeLevelCount = checkReports(reportData, 5, 6);
    printf("Safe Level Count: %d\n", safeLevelCount);
    return 0;
}
