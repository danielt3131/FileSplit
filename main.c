#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
const uint64_t fileChunckSize = 1048576;

int main() {
    unsigned char *buffer = (unsigned char *) malloc((1024 * 1024) * sizeof(unsigned char)); // 1 MiB buffer
    FILE *inputFile = fopen("input", "rb");
    fseeko(inputFile, 0, SEEK_END);
    uint64_t fileSize = ftello(inputFile);
    fseeko(inputFile, 0, SEEK_SET);
    uint64_t numberOfChunks = fileSize / fileChunckSize;
    char outputFile[100] = "output";
    char temp[100];
    uint64_t i;
    for (i = 0; i < numberOfChunks; i++){
        fread(buffer, fileChunckSize, 1, inputFile);
        sprintf(temp, "%s.%lu", outputFile, i);
        FILE *output = fopen(temp, "wb");
        fwrite(buffer, fileChunckSize, 1, output);
        fclose(output);
    }
    i++;
    if (fileSize % fileChunckSize != 0){
        uint64_t remainderChunckSize = fileSize - (numberOfChunks * fileChunckSize);
        fread(buffer, remainderChunckSize, 1, inputFile);
        sprintf(temp, "%s.%lu", outputFile, i);
        FILE *output = fopen(temp, "wb");
        fwrite(buffer, fileChunckSize, 1, output);
        fclose(output);
    }
    fclose(inputFile);
    free(buffer);
    return 0;
}
