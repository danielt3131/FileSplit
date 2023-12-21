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
#ifndef MESSAGE_H
#define MESSAGE_H
/**
 * Prints the summary of what happened
 * @param *inputFileName The name of the input file
 * @param *outputFileName The name of the output file
 * @return Nothing
 */
void completedMergeMsg(char *inputFileName, char *outputFileName);
/**
 * Prints the summary of what happened
 * @param *inputFileName The name of the input file
 * @param *outputFileName The name of the output file
 * @return Nothing
 */
void completedSplitMsg(char *inputFileName, char *outputFileName);
/**
 * Prints error message
 * @param type The error type
 * @param *inputFileName The name of the input file
 * @param *outputFileName The name of the output file
 * @return Nothing
 */
void errorMsg(short type, char *inputFileName, char *outputFileName);

#endif //MESSAGE_H