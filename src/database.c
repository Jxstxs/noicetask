
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

        // if database was not found
        if (rc == -1) {

            // loop through paths and ask to create database
            i = 0;
            while (paths[i] != NULL) {
                printf("Create database in %s? (y/n) ", paths[i]);

                // get input and check if it is yes
                scanf("%s", answer);
                if (strcmp(answer, "y") == 0) {
                    sprintf(path, "%s/%s", paths[i], DATABASENAME);
                    // printf("Creating database at %s\n", path);

                    // Create database
                    rc = sqlite3_open(path, &tc->db);
                    if (rc) {
                        printf("Can't open database: %s\n", sqlite3_errmsg(tc->db));
                        sqlite3_close(tc->db);
                        exit(1);
                    }
                    // Create Tables
                    createTables(tc);
                    break;
                }
                printf("\n");
                i++;
            }
        } else {

            // if database was found, open it
            sprintf(path, "%s/%s", paths[rc], DATABASENAME);
            // printf("Database found at %s\n", path);
            rc = sqlite3_open(path, &tc->db);
            if (rc) {
                printf("Can't open database: %s\n", sqlite3_errmsg(tc->db));
                sqlite3_close(tc->db);
                exit(1);
            }
        }
    } else {
        // if databasePath is given, open it
        rc = sqlite3_open(tc->databasePath, &tc->db);
        if (rc) {
            printf("Can't open database: %s\n", sqlite3_errmsg(tc->db));
            sqlite3_close(tc->db);
            exit(1);
        }
    }
}

void closeDatabase(todoConf *tc) {
    // printf("closing database\n");
    // sqlite3_close(tc->db);
}
