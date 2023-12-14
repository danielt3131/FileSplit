#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const unsigned long long fileChunckSize = 1048576;

int main() {
    unsigned char *buffer = (unsigned char *) malloc((1024 * 1024) * sizeof(unsigned char)); // 1 MiB buffer
    FILE *inputFile = fopen("input", "rb");
    fseeko(inputFile, 0, SEEK_END);
    unsigned long long fileSize = ftello(inputFile);
    fseeko(inputFile, 0, SEEK_SET);
    unsigned long long numberOfChunks = fileSize / fileChunckSize;
    char outputFile[100] = "split";
    char temp[100];
    unsigned long long i;
    for (i = 0; i < numberOfChunks; i++){
        fread(buffer, fileChunckSize, 1, inputFile);
        sprintf(temp, "%s.%llu", outputFile, i);
        FILE *output = fopen(temp, "wb");
        fwrite(buffer, fileChunckSize, 1, output);
        fclose(output);
        printf("%llu\n", i);
    }
    printf("%llu\n", (fileSize % fileChunckSize));
    printf("%llu\n", (fileSize - (numberOfChunks * fileChunckSize)));
    if (fileSize % fileChunckSize != 0){
        unsigned long long remainderChunckSize = fileSize - (numberOfChunks * fileChunckSize);
        fread(buffer, remainderChunckSize, 1, inputFile);
        sprintf(temp, "%s.%llu", outputFile, i);
        FILE *output = fopen(temp, "wb");
        fwrite(buffer, remainderChunckSize, 1, output);
        fclose(output);
    }
    fclose(inputFile);
    free(buffer);
    return 0;
}
