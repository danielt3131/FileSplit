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
#ifndef FILE_H
#define FILE_H

/*
 * Merges back n slices back into the original file
 * @param *inputFileName The name of the splitted file
 * @param *outputFileName The name of the merged file
 * @return Nothing
 */
int mergeFile(char *inputFileName, char *outputFileName);

/*
 * Splits a file into n slices
 * @param *inputFileName The name of the file to split
 * @param *outputFileName The name.* of splitted files where * is the integer extension
 */

int splitFile(char *inputFileName, char *outputFileName);

/*
 * Computes the size of a file
 * @param *file The file pointer 
 * @return The size of the file
 */
unsigned long long fileSize(FILE *file);

#endif FILE_H
