#ifndef DATABASE_H
#define DATABASE_H

#include <time.h>

#include "main.h"

#define DATABASENAME "TODO"
#define SQL_SIZE 1024

typedef struct {
    char *title;
    char *description;
    char *path;
    char *tagName;
    char *date;
    char *expireDate;
    int tagId;
    int id;
    int done;
    int priority;
} DataBaseResult;

typedef struct {
    char *tables;
    char *columns;
    char *where;
    char *order;
    bool distinct;
} DataBaseQuery;

void initDatabase(taskConf *tc);
void closeDatabase(taskConf *tc);
void createTables(taskConf *tc);
void executeQuery(taskConf *tc, char *query);
void printResults(DataBaseResult dbr);
void initDbResult(DataBaseResult *dbr);
DataBaseResult *getDbResults(taskConf *tc, DataBaseQuery dbq);
void freeDbResults(DataBaseResult *dbr);

#endif // !DATABASE_H
