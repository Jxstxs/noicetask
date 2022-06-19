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
    "Usage: todo [ARGUMENTS] <function> [PARAMETERS]\n"
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

    switch (tc.func) {
        case ADD_TODO:
            printf("adding a todo\n");
            break;
        case DONE_TODO:
            printf("done a todo\n");
            break;
        case MOD_TODO:
            printf("mod a todo\n");
            break;
        case REMOVE_TODO:
            printf("remove a todo\n");
            break;
        case LIST:
            printf("list todos\n");
            break;
    }

    return 0;
}
