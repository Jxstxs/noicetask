#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "main.h"
#include "argparse.h"

void usage() {
    printf(
    "Usage: todo [ARGUMENTS] <function> [PARAMETERS]"
    // ARGUMENTS
    // DATABASE HELP
    "\n\t-db <path> or --database <path> to specify which Todo Database should be used, if its not found it would create a new one in the given Path."
    "\n\t\tDefaults: it first looks in the current working Directory and then into the $HOME Directory."
    // HELP HELP
    "\n\t-h <function> or --help <function> prints this or a specific Help text for a Function"
    "\n\t\tDefaults: it prints all Help texts"

    // FUNCTIONS
    // ADD HELP
    "\n\n\tadd:"
    "\n\t\t-t 'TITLE' or --title 'TITLE' specify the Title of the Todo. The Title is always needed."
    "\n\t\t-d 'DESCRIPTION' or --description 'DESCRIPTION' specify the Description for the Todo. The Description is optional."
    "\n\t\tWeiter Machen !!!!!!!!!!!!!!!!!"
    );
}

int main(int argc, char **argv) {
    
    // Check if enough Arguments are given
    if (argc < 2) {
        usage();
        return 0;
    }

    // Arg parsing
    todoConf tc;
    tc = parseArguments(argc, argv);

    // Error and Help handling
    if (tc.err != OK) {
        switch(tc.err) {
            case NO_DB_PATH:
                printf("No Database given\n");
                printf("If you want to use the Database from current or Home Directory dont use 'db' or 'database'\n");
                usage();
                break;

            case HELP:
                usage();
                break;
            
            case NO_FUNC_GIVEN:
                printf("No Function given\n");
                usage();
                break;
        }
        return 1;
    }

    setupTConf(&tc);

    printf("%s\n", tc.databasePath);

    char *errMsg = 0;
    sqlite3_exec(tc.db, "SELECT * FROM todos;", callback, 0, &errMsg);

    switch (tc.func) {
        case ADD:
            printf("adding a todo\n");
            break;
        case DONE:
            printf("done a todo\n");
            break;
        case MOD:
            printf("mod a todo\n");
            break;
        case REMOVE:
            printf("remove a todo\n");
            break;
        case PRINT:
            printf("list todos\n");
            break;
    }

    return 0;
}
