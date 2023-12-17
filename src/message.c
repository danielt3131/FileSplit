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
#include <ncurses.h>
#include <stdlib.h>
#include "message.h"
#define MAX_FILENAME_LENGTH 100
#define DEFAULT_CHUNK_SIZE 1048576
#define ERROR_OUTPUT 1
#define SPLIT_FILE 1
#define MERGE_FILE 2

void completedMergeMsg(char *inputFileName, char *outputFileName){
    clear();
    printw("The file(s) of %s have been merged into %s\n", inputFileName, outputFileName);
    refresh();
    free(inputFileName);
    free(outputFileName);
    sleep(5);
    endwin();
}

void completedSplitMsg(char *inputFileName, char *outputFileName){
    clear();
    printw("The file of %s have been splited into %s\n", inputFileName, outputFileName);
    refresh();
    free(inputFileName);
    free(outputFileName);
    sleep(5);
    endwin();
}

void errorMsg(short type, char *inputFileName, char *outputFileName){
    switch (type){
    case SPLIT_FILE:
        attron(COLOR_PAIR(ERROR_OUTPUT));
        printw("There was an error in splitFile\n");
        refresh();
        sleep(5);
        free(inputFileName);
        free(outputFileName);
        endwin();
        break;
    case MERGE_FILE:
        attron(COLOR_PAIR(ERROR_OUTPUT));
        printw("There was an error in mergeFile\n");
        refresh();
        sleep(5);
        free(inputFileName);
        free(outputFileName);
        endwin();
        break;
    default:
        break;
    }
}