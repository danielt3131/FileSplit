/*
 * Copyright (c) 2023 Daniel J. Thompson.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 or later.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const unsigned long long fileChunckSize = 1048576;

int main(int argc, char **argv) {
    unsigned char *buffer = (unsigned char *) malloc((1024 * 1024) * sizeof(unsigned char)); // 1 MiB buffer
    char inputFileName[100] = "input";
    char outputFileName[100] = "output";
    if (argc > 2){
        strncpy(inputFileName, argv[1], 100);
        strncpy(outputFileName, argv[2], 100);
    }
    FILE *inputFile = fopen(inputFileName, "rb");
    if (inputFile == NULL){
        return 0;
    }
    fseeko(inputFile, 0, SEEK_END);
    unsigned long long fileSize = ftello(inputFile);
    fseeko(inputFile, 0, SEEK_SET);
    unsigned long long numberOfChunks = fileSize / fileChunckSize;
    char temp[200];
    unsigned long long i;
    for (i = 0; i < numberOfChunks; i++){
        fread(buffer, fileChunckSize, 1, inputFile);
        sprintf(temp, "%s.%llu", outputFileName, i);
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
        sprintf(temp, "%s.%llu", outputFileName, i);
        FILE *output = fopen(temp, "wb");
        fwrite(buffer, remainderChunckSize, 1, output);
        fclose(output);
    }
    fclose(inputFile);
    free(buffer);
    return 0;
}
