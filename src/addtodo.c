
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "addtodo.h"
#include "additional.h"

void addTodo(todoConf *tc) {
    // check if tc is NULL
    if (tc == NULL) {
        printf("Error: addTodo() called with NULL todoConf\n");
        return;
    }

    // check if all function parameter are valid
    if (strcmp(tc->fp.title, "") == 0) {
        printf("To add an Todo you need to specify a title\n");
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
            printf("Error: addTodo() could not allocate memory for path\n");
            return;
        }
    }

    // check if an expire date is given
    time_t expireDate = 0;
    if (strcmp(tc->fp.expireDate, "") != 0) {
        // convert a string date to a time_t
        time_t expireDate = convertStringToDate(tc->fp.expireDate);
        if (expireDate == -1) {
            printf("Error: addTodo() could not convert given date to time_t struct\n");
            return;
        }
    }

    // check if categories are given
    int *categories = NULL;
    if (strcmp(tc->fp.categories, "") != 0) {
        // convert a string categories to an int array
        int *categories = parseCategories(tc->fp.categories);
        if (categories == NULL) {
            printf("Error: addTodo() could not parse given categories\n");
            return;
        }
    }

    // check if priority is given
    int priority = 0;
    if (strcmp(tc->fp.priority, "") != 0) {
        // convert a string priority to an int
        int priority = parsePriority(tc->fp.priority);
        if (priority == -1) {
            printf("Error: addTodo() could not parse given priority\n");
            return;
        }
    } else {
        priority = LOW;
    }

    // print all function parameters
    printf("Title: %s\n", tc->fp.title);
    printf("Description: %s\n", tc->fp.description);
    printf("Path: %s\n", tc->fp.path);
    printf("Expire Date: %s\n", tc->fp.expireDate);
    printf("Categories: %s\n", tc->fp.categories);
    printf("Priority: %s\n", tc->fp.priority);
    printf("\n");

    // print all information todoConf
    printf("Title: %s\n", tc->fp.title);
    printf("Description: %s\n", tc->fp.description);
    printf("Path: %s\n", tc->fp.path);
    printf("Expire Date: %s", asctime(localtime(&expireDate)));
    printf("Categories: ");
    // check if categories is not NULL
    if (categories != NULL) {
        for (int i = 0; i < MAX_CATEGORIES; i++) {
            if (categories[i]) {
                printf("%d ", categories[i]);
            }
        }
    }
    printf("\n");
    printf("Priority: %d\n", priority);
    printf("\n");


    // frees allocated vars
    // free(tc->fp.path);

    // check if categories are given
    if (categories != NULL) {
        free(categories);
    }
}
