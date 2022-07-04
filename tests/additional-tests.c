
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include "../src/additional.h"

int main (int argc, char *argv[])
{

    // parse date
    time_t tm = convertStringToDate("20220/12/1/6");
    printf("%s", asctime(localtime(&tm)));

    // parse categories
    char *categories = "32,1234,13,4,12,67,32,432";
    int *categoriesArr = parseCategories(categories);
    for (int i = 0; categoriesArr[i] != 0; i++) {
        printf("%d ", categoriesArr[i]);
    }
    printf("\n");
    free(categoriesArr);

    // parse priority
    char *priority = "h";
    int priorityInt = parsePriority(priority);
    printf("%d\n", priorityInt);

    return 0;
}
