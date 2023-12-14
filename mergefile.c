#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    unsigned char *buffer = (unsigned char *) malloc((1024 * 1024) * sizeof(unsigned char)); // 1 MiB buffer
    char mergedFileName[100] = "mergedFile";
    char splitFileName[100] = "split";
    if (argc > 3){
        strncpy(mergedFileName, argv[1], 100);
        strncpy(splitFileName, argv[2], 100);
    }
    FILE *mergedFile = fopen(mergedFileName, "wb");

    char temp[200];
    FILE *splitFileOpen = NULL;
    unsigned long long splitFileSize = 0;
    unsigned long long i = 0;
    while (1){
        sprintf(temp, "%s.%llu", splitFileName, i);
        splitFileOpen = fopen(temp, "rb");
        if(splitFileOpen == NULL){
            break;
        }
        fseeko(splitFileOpen, 0, SEEK_END);
        splitFileSize = ftello(splitFileOpen);
        printf("%llu\n", splitFileSize);
        fseeko(splitFileOpen, 0, SEEK_SET);
        fread(buffer, splitFileSize, 1, splitFileOpen);
        fwrite(buffer, splitFileSize, 1, mergedFile);
        fclose(splitFileOpen);
        i++;
    }
    free(buffer);
    fclose(mergedFile);
    return 0;
}
