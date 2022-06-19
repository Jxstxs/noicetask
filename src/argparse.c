
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "argparse.h"

todoConf parseArguments(int argc, char** argv){
    todoConf _tc;

    // setting defaults
    _tc.err = OK;
    _tc.func = NONE;

    int skip = 0; // skip indicator

    // looping through Arguments
    for (int i=0; i<argc; i++) {

        // skiping values for arguments
        if (skip != 0) {
            i = i + skip;
            skip = 0;
        }

        if (!argv[i]) break;

        // debuging
//      printf("%s\n", argv[i]);

        // ARGUMENTS
        // DATABASE ARG
        if (ARGCMP("-db", "--database") && _tc.func == NONE) {
            // checks if database is given
            if (argv[i+1]) {
                _tc.databasePath = argv[i+1];
                skip = 1;
            } else {
                _tc.err = NO_DB_PATH;
                return _tc;
            }
        }
        // HELP ARG
        else if (ARGCMP("-h", "--help") && _tc.func == NONE) {
            _tc.err = HELP;
            return _tc;
        }
        // CREATE ARG
        else if (ARGCMP("-cr", "--create") && _tc.func == NONE) {
            // HERE 
        }

        // FUNCTIONS
        else if (ARGCMP("a", "add") && _tc.func == NONE) _tc.func = ADD;
        else if (ARGCMP("d", "done") && _tc.func == NONE) _tc.func = DONE;
        else if (ARGCMP("r", "remove") && _tc.func == NONE) _tc.func = REMOVE;
        else if (ARGCMP("m", "modify") && _tc.func == NONE) _tc.func = MOD;
        else if (ARGCMP("p", "print") && _tc.func == NONE) _tc.func = PRINT;
    }

    if (_tc.func == NONE) _tc.err = NO_FUNC_GIVEN;

    return _tc;
}
