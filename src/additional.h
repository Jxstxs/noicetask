#ifndef ADDITIONAL_H
#define ADDITIONAL_H

#include <time.h>

#include "main.h"

void initTaskConf(taskConf *tc);
time_t convertStringToDate(char *date);
int *parseCategories(char *categories);
int parsePriority(char *priority);

// checks for database data
// https://stackoverflow.com/questions/23176734/sqlite-c-query-rows-how-to-handle-multiple-columns
int checkTagsExists(taskConf *tc, int *tags);
int checkPathExists(taskConf *tc, char *path);

#endif // ADDITIONAL_H
