
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "main.h"
#include "additional.h"

void initTodoConf(todoConf *tc) {
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
    printf("convertStringToDate() called\n");
    struct tm tm;
    char *delim = "/";
    char *token = strtok(date, delim);
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
    printf("parseCategories() called\n");
    int *result = malloc(sizeof(int) * MAX_CATEGORIES);
    if (result == NULL) {
        return NULL;
    }
    char *delim = ",";
    char *token = strtok(categories, delim);
    int i = 0;
    while (token != NULL) {
        printf("%s\n", token);
        result[i] = atoi(token);
        token = strtok(NULL, delim);
        i++;
    }
    return result;
}

int parsePriority(char *priority) {
    printf("parsePriority() called\n");
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
