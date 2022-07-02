#ifndef DATABASE_H
#define DATABASE_H

#include "main.h"

#define DATABASENAME "TODO"

void initDatabase(todoConf *tc);
void closeDatabase(todoConf *tc);
void createTables(todoConf *tc);

#endif // !DATABASE_H
