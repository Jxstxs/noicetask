
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "database.h"

void initDatabase(todoConf *tc) {
    int rc, i;
    char path[512];
    char answer[2];

    // check if databasePath is given
    if (strcmp(tc->databasePath, "") == 0) {
        printf("No database path given.\n");
        char upperPWD[512];
        sprintf(upperPWD, "%s/..", getenv("PWD"));

        char *paths[] = {
            getenv("PWD"),
            upperPWD,
            getenv("HOME"),
            NULL
        };

        // check paths for database
        rc = -1;
        i = 0;
        while (paths[i] != NULL) {
            sprintf(path, "%s/%s", paths[i], DATABASENAME);
            if (access(path, F_OK) == 0 && access(path, R_OK) == 0 && access(path, W_OK) == 0) {
                rc = i;
                break;
            }
            i++;
        }

        // if database was found
        if (rc == -1) {
            // loop through paths and ask to create database
            i = 0;
            while (paths[i] != NULL) {
                printf("Database not found at %s\n", paths[i]);
                printf("Do you want to create it? (y/n) ");
                scanf("%s", answer);
                if (strcmp(answer, "y") == 0) {
                    sprintf(path, "%s/%s", paths[i], DATABASENAME);
                    printf("Creating database at %s\n", path);
                    rc = sqlite3_open(path, &tc->db);
                    if (rc) {
                        printf("Can't open database: %s\n", sqlite3_errmsg(tc->db));
                        sqlite3_close(tc->db);
                        exit(1);
                    }
                    createTables(tc);
                    break;
                }
                printf("\n");
                i++;
            }
        }

    }
}

void closeDatabase(todoConf *tc) {
    // printf("closing database\n");
    // sqlite3_close(tc->db);
}
