#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const unsigned long long fileChunckSize = 1048576;

int main() {
    unsigned char *buffer = (unsigned char *) malloc((1024 * 1024) * sizeof(unsigned char)); // 1 MiB buffer
    FILE *mergedFile = fopen("mergedFile", "wb");
    char splitFile[100] = "split";
    char temp[100];
    FILE *splitFileOpen = NULL;
    unsigned long long splitFileSize = 0;
    unsigned long long i = 0;
    do  {
        sprintf(temp, "%s.%llu", splitFile, i);
        fopen(temp, "rb");
        fseeko(splitFileOpen, 0, SEEK_END);
        splitFileSize = ftello(splitFileOpen);
        fseeko(splitFileOpen, 0, SEEK_SET);
        fread(buffer, splitFileSize, 1, splitFileOpen);
        fwrite(buffer, splitFileSize, 1, mergedFile);
        fclose(splitFileOpen);
        i++;
    } while (!feof(splitFileOpen));
    free(buffer);
    fclose(mergedFile);
    return 0;
}
