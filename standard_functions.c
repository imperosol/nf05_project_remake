//
// Created by thgir on 27/02/2021.
//

#include <errno.h>
#include <string.h>
#include <time.h>
#include "standard_functions.h"

void *safe_malloc(size_t n) {
    void *p = malloc(n);
    if (p == NULL) {
        fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", n);
        exit(1);
    }
    return p;
}

FILE *open_file(const char *fileName, const char *mode) {
    errno_t err;
    FILE *toOpen = NULL;
    if ((err = fopen_s(&toOpen, fileName, mode))) {
        fprintf(stderr, "cannot open file '%s': %s\n", fileName, strerror(err));
        exit(1);
    } else {
        return toOpen;
    }
}


void update_tm(struct tm* time, const int year, const int month, const int m_day,
               const int hour, const int minute, const int seconds)
{
    time->tm_year += year;
    time->tm_mon += month;
    time->tm_mday += m_day;
    time->tm_hour += hour;
    time->tm_min += minute;
    time->tm_sec += seconds;

    mktime(time);
}

int input_word(char **word) {
    char temp[40];
    fgets(temp, 40, stdin);
    *word = safe_malloc(sizeof(char) * strlen(temp) + 1);
    strcpy(*word, temp);
    printf("%s\n", *word);
    return 0;
}

void clear_buffer(void) {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}
