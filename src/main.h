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
    char *path;
    char *title;
    char *description;
    char *mod;
    char *newValue;
    bool done;
    int *ids;
} funcParams;

typedef struct {
    funcParams fp;
    char *databasePath;
    sqlite3 *db;
    int err;
    int func;
} todoConf;

#endif // MAIN_H
