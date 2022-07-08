#ifndef DATABASE_H
#define DATABASE_H

#include "main.h"

#define DATABASENAME "TODO"

void initDatabase(taskConf *tc);
void closeDatabase(taskConf *tc);
void createTables(taskConf *tc);
void executeQuery(taskConf *tc, char *query);
void printResults(taskConf *tc, char *query);
int callback(void *NotUsed, int argc, char **argv, char **azColName);

#endif // !DATABASE_H
