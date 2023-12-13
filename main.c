#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t fileChunckSize = 1048576;

int main() {
    unsigned char *buffer = (unsigned char *) malloc((1024 * 1024) * sizeof(unsigned char)); // 1 MiB buffer
    FILE *inputFile = fopen("input", "rb");
    fseeko(inputFile, 0, SEEK_END);
    size_t fileSize = ftello(inputFile);
    fseeko(inputFile, 0, SEEK_SET);
    return 0;
}
