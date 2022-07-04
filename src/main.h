#ifndef MAIN_H
#define MAIN_H

#include <sqlite3.h>
#include <stdbool.h>

enum ERRS {
    OK,
    NO_DB_PATH,
    NO_FUNC_GIVEN,
    PARAM,
    HELP
};

enum FUNCS {
    ADD_TASK,
    MOD_TASK,
    REMOVE_TASK,
    DONE_TASK,
    LIST,
    ANY,
    NONE
};

typedef struct {
    char *title;
    char *description;
    char *path;
    char *expireDate;
    char *categories;
    char *field;
    char *newValue;
    char *type;
    char *ids;
    char *priority;
    bool marked;
} funcParams;

typedef struct {
    funcParams fp;
    char *databasePath;
    sqlite3 *db;
    int noConfirm;
    int err;
    int func;
} taskConf;

#endif // MAIN_H
