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
#include "file.h"

int main (int argc, char **argv){
    char *inputFileName = NULL;
    char *outputFileName = NULL;
    if (argc > 2){
        inputFileName = (char *) malloc(strlen(argv[1]) + 1);
        outputFileName = (char *) malloc(strlen(argv[2]) + 1);
        strcpy(inputFileName, argv[1]);
        strcpy(outputFileName, argv[2]);
    }
    return 0;
}