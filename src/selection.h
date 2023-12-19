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
#ifndef SELECTION_H
#define SELECTION_H

/*
 * File selection
 * @param *inputFileName The filepath of the input file
 * @param *outputFileName The filepath of the output file
 * @return Nothing
 */
void fileSelection(char *inputFileName, char *outputFileName);

/*
 * Asks the user if they want to set the chunk/slice size 
 * @param *chunkSize the pointer to the chunkSize
 * @return Nothing
 */
void chunkSelection(unsigned long long *chunkSize);

/*
 * Handles the cli arguments
 * @param argc The number of cli arguments
 * @param **argv The array of cli argument strings
 * @param *inputFileName The filepath of the input file
 * @param *outputFileName The filepath of the output file
 * @param *fileChunkSize The pointer to the fileChunkSize
 * @return the exit status 
 */
int selectionCLI(int argc, char **argv, char *inputFileName, char *outputFileName, int *fileChunkSize);

#endif //SELECTION_H
