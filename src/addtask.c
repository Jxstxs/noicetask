
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "addtask.h"
#include "additional.h"

void addTask(taskConf *tc) {
    // check if tc is NULL
    if (tc == NULL) {
        printf("Error: addTask() called with NULL TaskConf\n");
        return;
    }

    // check if all function parameter are valid
    if (strcmp(tc->fp.title, "") == 0) {
        printf("To add an Task you need to specify a title\n");
        return;
    }

    // check if path is given and if not it sets it to current directory
    if (strcmp(tc->fp.path, "") == 0) {
        // get current path and stores it in tc->fp.path
        char newPath[1024];
        getcwd(newPath, sizeof(newPath));
        // free(tc->fp.path);
        tc->fp.path = strdup(newPath);
        if (tc->fp.path == NULL) {
            printf("Error: addTask() could not allocate memory for path\n");
            return;
        }
    }

    // check if an expireDate is given
    time_t expireDate = 0;
    if (strcmp(tc->fp.expireDate, "") != 0) {
        // convert a string date to a time_t
        expireDate = convertStringToDate(tc->fp.expireDate);
        if (expireDate == -1) {
            printf("Error: addTask() could not convert given date to time_t struct\n");
            return;
        }
    }

    // check if categories are given
    int *categories = NULL;
    if (strcmp(tc->fp.categories, "") != 0) {
        // convert a string categories to an int array
        categories = parseCategories(tc->fp.categories);
        if (categories == NULL) {
            printf("Error: addTask() could not parse given categories\n");
            return;
        }
    }

    // check if priority is given
    int priority = 0;
    if (strcmp(tc->fp.priority, "") != 0) {
        // convert a string priority to an int
        priority = parsePriority(tc->fp.priority);
        if (priority == -1) {
            printf("Error: addTask() could not parse given priority\n");
            return;
        }
    } else {
        priority = LOW;
    }

    /* 
        NOTE: here we are
        Need to be done:
            - check if path is already in database if not add it
            - check if expireDate is valid
            - check if categories are valid
            - add data to database
    */

    

    // check if categories are given
    if (categories != NULL) {
        // free all items of categories
        for (int i = 0; categories[i]; i++) {
            free(&categories[i]);
        }
        free(categories);
    }
}
