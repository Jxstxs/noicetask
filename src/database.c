
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "main.h"
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

// void printResults(taskConf *tc, char *query) {
//     int rc;
//     char *errmsg;
//     rc = sqlite3_exec(tc->db, query, callback, NULL, &errmsg);
//     if (rc != SQLITE_OK) {
//         printf("SQL error: %s\n", errmsg);
//         sqlite3_free(errmsg);
//         sqlite3_close(tc->db);
//         exit(1);
//     }
// }
//
// int callback(void *NotUsed, int argc, char **argv, char **azColName) {
//    int i;
//    for(i = 0; i<argc; i++) {
//       printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//    }
//    printf("\n");
//    return 0;
// }

void initDbResult(DataBaseResult *dbr) {
    dbr->title = NULL;
    dbr->description = NULL;
    dbr->path = NULL;
    dbr->date = NULL;
    dbr->expireDate = NULL;
    dbr->tagName = NULL;
}

DataBaseResult *getDbResults(taskConf *tc, DataBaseQuery dbq) {
    DataBaseResult *dbr = NULL;
    int rc;
    char sql[SQL_SIZE];
    sqlite3_stmt *stmt;

    snprintf(sql, SQL_SIZE, "%sSELECT %s FROM %s%s%s;",
             (dbq.distinct ? "DISTINCT " : ""),
             dbq.columns,
             dbq.tables,
             dbq.where,
             dbq.order
    );

    printf("%s\n", sql);

    rc = sqlite3_prepare_v2(tc->db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        printf("!SQL ERROR: %s\n", sqlite3_errmsg(tc->db));
        closeDatabase(tc);
        exit(1);
    }

    int count = 0;
    int columnCount;
    char *columnName;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // realloc memory for dbr 
        DataBaseResult *dbrRealloc = realloc(dbr, sizeof(DataBaseResult) * (count + 1));
        if (dbrRealloc == NULL) {
            printf("!ERROR: realloc failed\n");
            closeDatabase(tc);
            exit(1);
        }
        dbr = dbrRealloc;

        // get data from row
        columnCount = sqlite3_column_count(stmt);
        initDbResult(&dbr[count]);
        for (int i = 0; i < columnCount; i++) {
            columnName = strdup(sqlite3_column_name(stmt, i));
            if (strcmp(columnName, "id") == 0) {
                dbr[count].id = sqlite3_column_int(stmt, i);
            } else if (strcmp(columnName, "title") == 0) {
                dbr[count].title = strdup((const char *)sqlite3_column_text(stmt, i));
            } else if (strcmp(columnName, "description") == 0) {
                dbr[count].description = strdup((const char *)sqlite3_column_text(stmt, i));
            } else if (strcmp(columnName, "path") == 0) {
                dbr[count].path = strdup((const char *)sqlite3_column_text(stmt, i));
            } else if (strcmp(columnName, "done") == 0) {
                dbr[count].done = sqlite3_column_int(stmt, i);
            } else if (strcmp(columnName, "date") == 0) {
                dbr[count].date = strdup((const char *)sqlite3_column_text(stmt, i));
            } else if (strcmp(columnName, "expireDate") == 0) {
                dbr[count].expireDate = strdup((const char *)sqlite3_column_text(stmt, i));
            } else if (strcmp(columnName, "priority") == 0) {
                dbr[count].priority = sqlite3_column_int(stmt, i);
            } else if (strcmp(columnName, "tag") == 0) {
                dbr[count].tagName = strdup((const char *)sqlite3_column_text(stmt, i));
            }
        }

        count++;
    }

    // realloc memory for dbr 
    DataBaseResult *dbrRealloc = realloc(dbr, sizeof(DataBaseResult) * (count + 1));
    if (dbrRealloc == NULL) {
        printf("!ERROR: realloc failed\n");
        closeDatabase(tc);
        exit(1);
    }
    dbr = dbrRealloc;
    dbr[count].id = -1;

    return dbr;
}

void freeDbResults(DataBaseResult *dbr) {
    if (dbr == NULL) {
        return;
    }
    for (int i = 0; dbr[i].id == -1; i++) {
        if (dbr[i].title != NULL) {
            free(dbr[i].title);
        }
        if (dbr[i].description != NULL) {
            free(dbr[i].description);
        }
        if (dbr[i].path != NULL) {
            free(dbr[i].path);
        }
        if (dbr[i].date != NULL) {
            free(dbr[i].date);
        }
        if (dbr[i].expireDate != NULL) {
            free(dbr[i].expireDate);
        }
        if (dbr[i].tagName != NULL) {
            free(dbr[i].tagName);
        }
    }
    free(dbr);
}

void printResults(DataBaseResult dbr);
