# include <stdio.h>

void scanFilesCreateReports(int reportData[][1000], int reportLen)
{
    FILE *input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < reportLen; i++)
        {
            char line[50];
            fgets(line, sizeof(line), input);
            int count = sscanf(line, "%d %d %d %d %d %d %d %d", &reportData[i][0], &reportData[i][1], &reportData[i][2], &reportData[i][3], &reportData[i][4], &reportData[i][5], &reportData[i][6], &reportData[i][7]);
            for (int j = count; j < 8; j++)
                {
                    reportData[i][j] = -1;
                }
        }
    fclose(input);
}

int checkReports(int reportBuf[][1000], int reportLen) {
    int safeCount = 0;

    for (int report = 0; report < reportLen; report++) {
        int isIncreasing = 1; // Assume it's increasing initially
        int isDecreasing = 1; // Assume it's decreasing initially

        int lastValue = -1;

        for (int level = 0; level < 8; level++) {
            if (reportBuf[report][level] != -1) {
                if (lastValue != -1) { // Only compare if lastValue is valid
                    if (lastValue >= reportBuf[report][level]) {
                        isIncreasing = 0; // Not increasing
                    }
                    if (lastValue <= reportBuf[report][level]) {
                        isDecreasing = 0; // Not decreasing
                    }
                    // Check the difference condition
                    if ((lastValue > reportBuf[report][level] && lastValue - reportBuf[report][level] > 3) ||
                        (lastValue < reportBuf[report][level] && reportBuf[report][level] - lastValue > 3)) {
                        isIncreasing = 0;
                        isDecreasing = 0;
                    }
                }
                lastValue = reportBuf[report][level];
            }
        }

        // If either condition holds true, count it as safe
        if (isIncreasing || isDecreasing) {
            safeCount++;
        }
    }
    return safeCount;
}

int dampenCheckReports(int reportBuf[][1000], int reportLen) {
    int safeCount = 0;

    for (int report = 0; report < reportLen; report++) {
        // Create a copy of the current report to modify
        int tempReport[8];
        for (int i = 0; i < 8; i++) {
            tempReport[i] = reportBuf[report][i];
        }

        // Flag to track if we've successfully dampened the report
        int dampened = 0;

        // Try removing each number to see if it makes the report safe
        for (int problematicIndex = 0; problematicIndex < 8; problematicIndex++) {
            // Skip if the value is already -1 (unused)
            if (tempReport[problematicIndex] == -1) continue;

            // Temporarily remove the problematic number
            int removedValue = tempReport[problematicIndex];
            tempReport[problematicIndex] = -1;

            // Check if the modified report is safe
            int isIncreasing = 1;
            int isDecreasing = 1;
            int lastValue = -1;

            for (int level = 0; level < 8; level++) {
                if (tempReport[level] != -1) {
                    if (lastValue != -1) { // Only compare if lastValue is valid
                        if (lastValue >= tempReport[level]) {
                            isIncreasing = 0; // Not increasing
                        }
                        if (lastValue <= tempReport[level]) {
                            isDecreasing = 0; // Not decreasing
                        }
                        // Check the difference condition
                        if ((lastValue > tempReport[level] && lastValue - tempReport[level] > 3) ||
                            (lastValue < tempReport[level] && tempReport[level] - lastValue > 3)) {
                            isIncreasing = 0;
                            isDecreasing = 0;
                            break; // No need to continue checking
                        }
                    }
                    lastValue = tempReport[level];
                }
            }

            // If the modified report is safe, count it and move to next report
            if (isIncreasing || isDecreasing) {
                safeCount++;
                break; // We found a way to make this report safe
            }

            // Restore the removed value for next iteration
            tempReport[problematicIndex] = removedValue;
        }
    }
    return safeCount;
}

int main()
{
    int safeLevelCount = 0;
    int dampenedSafeCount = 0;
    int reportData[1000][1000];
    scanFilesCreateReports(reportData, 1000);
    printf("Safe Level Count: %d\n", checkReports(reportData, 1000));
    printf("Dampened Safe Level Count: %d\n", dampenCheckReports(reportData, 1000));
    return 0;
}
