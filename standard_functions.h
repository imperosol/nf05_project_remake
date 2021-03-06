//
// Created by thgir on 27/02/2021.
//

#ifndef NF05_PROJET_REMAKE_STANDARD_FUNCTIONS_H
#define NF05_PROJET_REMAKE_STANDARD_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

void * safe_malloc(size_t n);
FILE* open_file(const char* fileName, const char* mode);
void update_tm(struct tm* time, const int year, const int month, const int m_day,
               const int hour, const int minute, const int seconds);
int input_word(char **word);
void clear_buffer(void);


#endif //NF05_PROJET_REMAKE_STANDARD_FUNCTIONS_H
