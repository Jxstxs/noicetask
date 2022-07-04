#ifndef ADDITIONAL_H
#define ADDITIONAL_H

#include <time.h>

#include "main.h"

void initTaskConf(taskConf *tc);
time_t convertStringToDate(char *date);
int *parseCategories(char *categories);
int parsePriority(char *priority);

#endif // ADDITIONAL_H
