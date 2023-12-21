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

#ifndef CONSTANTS_H
#define CONSTANTS_H
/**
 * @def Types of errors
 */
#define ALLOCATION_ERROR 2
#define FILE_READ_ERROR 3
#define FILE_WRITE_ERROR 4
#define INTEGER_OVERFLOW_ERROR 5
#define COLOR_SUPPORT_ERROR 6

/**
 * @def Constant values
 */
#define MAX_FILENAME_LENGTH 512
#define DEFAULT_CHUNK_SIZE 1048576
#define ERROR_OUTPUT 1
#define SPLIT_FILE 1
#define MERGE_FILE 2
#endif //CONSTANTS_H
