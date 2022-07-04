
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "main.h"
#include "additional.h"

void initTaskConf(taskConf *tc) {
    tc->databasePath = "";
    tc->noConfirm = 0;
    tc->err = OK;
    tc->func = NONE;

    tc->fp.title = "";
    tc->fp.description = "";
    tc->fp.path = "";
    tc->fp.expireDate = "";
    tc->fp.categories = "";
    tc->fp.field = "";
    tc->fp.newValue = "";
    tc->fp.type = "";
    tc->fp.ids = "";
    tc->fp.priority = "";
    tc->fp.marked = false;
}

time_t convertStringToDate(char *date) {
    struct tm tm;
    char *delim = "/";

    char buf[17];
    strcpy(buf, date);
    char *token = strtok(buf, delim);

    int i = 0;
    while (token != NULL) {
        if (i == 0) {
            tm.tm_year = atoi(token) - 1900;
        } else if (i == 1) {
            tm.tm_mon = atoi(token) - 1;
        } else if (i == 2) {
            tm.tm_mday = atoi(token);
        } else if (i == 3) {
            tm.tm_hour = atoi(token);
        } else if (i == 4) {
            tm.tm_min = atoi(token);
        }
        token = strtok(NULL, delim);
        i++;
    }
    if (i < 4 || i > 5) {
        return -1;
    }
    if (i == 4) tm.tm_min = 0;
    tm.tm_sec = 0;
    return mktime(&tm);
}

int *parseCategories(char *categories) {
    int *result = NULL; // malloc(sizeof(int));
    // if (result == NULL) {
    //     return NULL;
    // }
    char *delim = ",";

    char buf[50];
    strcpy(buf, categories);
    char *token = strtok(buf, delim);

    int i = 0;
    while (token != NULL) {
        // reallocate result
        int *_result = realloc(result, sizeof(int) * (i + 1));
        if (_result == NULL) {
            free(result);
            return NULL;
        }
        result = _result;

        int newResult = atoi(token);
        // check if newResult is in already in result
        for (int j = 0; j < i; j++) {
            if (result[j] == newResult) {
                newResult = 0;
                break;
            }
        }
        if (newResult != 0) {
            result[i] = newResult;
            i++;
        } 

        token = strtok(NULL, delim);
    }
    result[i] = 0;
    return result;
}

int parsePriority(char *priority) {
    if ((strcmp(priority, "low") == 0) || (strcmp(priority, "l") == 0)) {
        return LOW;
    } else if ((strcmp(priority, "medium") == 0) || (strcmp(priority, "m") == 0)) {
        return MEDIUM;
    } else if ((strcmp(priority, "high") == 0) || (strcmp(priority, "h") == 0)) {
        return HIGH;
    } else {
        return -1;
    }
}
