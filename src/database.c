
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "database.h"

void initDatabase(taskConf *tc) {
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
                    printf("Using database at %s\n", path);
                    break;
                }
                printf("\n");
                i++;
            }
            // when no database was created 
            exit(1);
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
            printf("Using database at %s\n", path);
        }
    } else {
        // if databasePath is given, check if it exists is readable and writable
        if (access(tc->databasePath, F_OK) == 0 && access(tc->databasePath, R_OK) == 0 && access(tc->databasePath, W_OK) == 0) { i = 0; } else { i = -1; }
        // open it or create it
        rc = sqlite3_open(tc->databasePath, &tc->db);
        if (rc) {
            printf("Can't open database: %s\n", sqlite3_errmsg(tc->db));
            sqlite3_close(tc->db);
            exit(1);
        }
        // if database was not found, create tables 
        if (i == -1) {
            createTables(tc);
        }
    }
}

void closeDatabase(taskConf *tc) {
    // printf("closing database\n");
    sqlite3_close(tc->db);
}

void createTables(taskConf *tc) {
    // char *sql;
    int i;

    char *tables[] = {
        // Task Table
        "CREATE TABLE task (id INTEGER PRIMARY KEY,title TEXT, description TEXT,path INTEGER, done INTEGER,createDate TEXT, expireDate TEXT,priority INTEGER);",
        // Path Table
        "CREATE TABLE path (id INTEGER PRIMARY KEY,path TEXT);",
        // Tag Table
        "CREATE TABLE tag (id INTEGER PRIMARY KEY,tag TEXT, description TEXT);",
        NULL
    };

    // create table todo
    i = 0;
    while (tables[i] != NULL) {
        executeQuery(tc, tables[i]);
        i++;
    }
}

void executeQuery(taskConf *tc, char *query) {
    int rc;
    char *errmsg;
    rc = sqlite3_exec(tc->db, query, NULL, NULL, &errmsg);
    if (rc != SQLITE_OK) {
        printf("SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(tc->db);
        exit(1);
    }
}

void printResults(taskConf *tc, char *query) {
    int rc;
    char *errmsg;
    rc = sqlite3_exec(tc->db, query, callback, NULL, &errmsg);
    if (rc != SQLITE_OK) {
        printf("SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(tc->db);
        exit(1);
    }
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
