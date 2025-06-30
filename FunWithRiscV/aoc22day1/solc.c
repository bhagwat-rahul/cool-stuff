#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("sample.txt", "r");
    if (!file) {
        perror("open failed");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file); 
    char *data = malloc(filesize + 1);
    if (!data) {
        fclose(file);
        return 1;
    }
    fread(data, 1, filesize, file);
    data[filesize] = '\0'; 
    fclose(file);
    int elfcount = 0;
    int has_data = 0;
    for (long i = 0; i < filesize; i++) {
        if (data[i] == '\n' && data[i + 1] == '\n') {
            if (has_data) {
                elfcount++;
                has_data = 0;
            }
        } else if (data[i] != '\n') {
            has_data = 1;
        }
    }
    if (has_data) elfcount++;
    printf("Elf count: %d\n", elfcount);
    free(data);
    return 0;
}

