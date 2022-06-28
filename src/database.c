
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

#include "database.h"

void initDatabase(todoConf *tc) {
    char *errmsg = 0;
    int rc;

    rc = sqlite3_open(tc->databasePath, &tc->db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "ERROR: Can't open database: '%s' in initDatabase()\n", sqlite3_errmsg(tc->db));
        sqlite3_close(tc->db);
        exit(1);
    }
}

void closeDatabase(todoConf *tc);
