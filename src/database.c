
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "database.h"

void initDatabase(todoConf *tc) {
    /*
        NOTE: what it should do
        - check if a database was given
            - if yes -> try open it (check if exists and read/writeable)
            - if no -> ask to create (if nc -> without asking)
    */

    // check if databasePath is given
    if (strcmp(tc->databasePath, "") == 0) {

    }
}

void closeDatabase(todoConf *tc) {
    // printf("closing database\n");
    // sqlite3_close(tc->db);
}
