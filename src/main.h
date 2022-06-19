#ifndef MAIN_H

#include <sqlite3.h>
#include <stdbool.h>

enum ERRS {
    OK,
    NO_DB_PATH,
    NO_FUNC_GIVEN,
    HELP
};

enum FUNCS {
    ADD_TODO,
    MOD_TODO,
    REMOVE_TODO,
    DONE_TODO,
    LIST,
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
    int *ids;
    int priority;
    int marked;
} funcParams;

typedef struct {
    funcParams fp;
    char *databasePath;
    sqlite3 *db;
    int noConfirm;
    int err;
    int func;
} todoConf;

#endif // MAIN_H
