#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "main.h"
#include "argparse.h"
#include "database.h"
#include "addtask.h"

void usage() {
    printf(
    "Usage: nt [ARGUMENTS] <function> [PARAMETERS]\n"
    );
}

int main(int argc, char **argv) {
    
    // Check if enough Arguments are given
    if (argc < 2) {
        usage();
        return 0;
    }

    // Arg parsing
    taskConf tc = parseArguments(argc, argv);

    // Error and Help handling
    if (tc.err != OK) {
        switch(tc.err) {
            case NO_DB_PATH:
                printf("No Database given\n");
                printf("If you want to use the Database from current or Home Directory dont use 'db' or 'database'\n");
                break;

            case NO_FUNC_GIVEN:
                printf("No Function given\n");
                break;

            case PARAM:
                printf("Something went wrong with the Paramter for the Function: %d\n", tc.func);
        }
        usage();
        return 1;
    }

    // Initialize database
    initDatabase(&tc);

    // Execute Function
    switch (tc.func) {
        case ADD_TASK:
            addTask(&tc);
            printResults(&tc, "SELECT * FROM task");
            break;
        case DONE_TASK:
            printf("done a todo\n");
            break;
        case MOD_TASK:
            printf("mod a todo\n");
            break;
        case REMOVE_TASK:
            printf("remove a todo\n");
            break;
        case LIST:
            printf("list todos\n");
            break;
    }

    // Close database
    closeDatabase(&tc);

    return 0;
}
