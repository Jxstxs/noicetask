
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"
#include "argparse.h"
#include "additional.h"

taskConf parseArguments(int argc, char** argv){
    taskConf _tc;

    // setting defaults
    initTaskConf(&_tc);

    int skip = 0; // skip indicator

    // looping through Arguments
    for (int i=0; i<argc; i++) {

        // skiping values for arguments
        if (skip != 0) {
            i = i + skip;
            skip = 0;
        }
        if (!argv[i]) break;
        
        // ARGUMENTS
        // DATABASE ARG
        if (ARGCMP("-db", "--database", NONE)){
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
        else if (ARGCMP("-h", "--help", NONE)) {
            _tc.err = HELP;
            return _tc;
        }
        // NO CONFIRM ARG
        else if (ARGCMP("-nc", "--noconfirm", NONE)) {_tc.noConfirm = 1;}

        // FUNCTIONS
        else if (ARGCMP("a", "add", NONE)) _tc.func = ADD_TASK;
        else if (ARGCMP("d", "done", NONE)) _tc.func = DONE_TASK;
        else if (ARGCMP("r", "remove", NONE)) _tc.func = REMOVE_TASK;
        else if (ARGCMP("m", "modify", NONE)) _tc.func = MOD_TASK;
        else if (ARGCMP("l", "list", NONE)) _tc.func = LIST;
        
        // FUNCTION PARAMETERS
        // FOR MULTIPLE FUNCTIONS
        else if (ARGCMP("-id", "-id", ANY)) {CHECKNEXT(ids, PARAM)}
        else if (ARGCMP("-t", "--title", ANY)) {CHECKNEXT(title, PARAM)}
        else if (ARGCMP("-d", "--description", ANY)) {CHECKNEXT(description, PARAM)}

        // ADD
        else if (ARGCMP("-pa", "--path", ADD_TASK)) {CHECKNEXT(path, PARAM)}
        else if (ARGCMP("-ex", "--expire", ADD_TASK)) {CHECKNEXT(expireDate, PARAM)}
        else if (ARGCMP("-ca", "--category", ADD_TASK)) {CHECKNEXT(categories, PARAM)}
        else if (ARGCMP("-pr", "--priority", ADD_TASK)) {CHECKNEXT(priority, PARAM)}

        // MOD
        else if (ARGCMP("-f", "--field", MOD_TASK)) {CHECKNEXT(field, PARAM)}
        else if (ARGCMP("-nv", "--newvalue", MOD_TASK)) {CHECKNEXT(newValue, PARAM)}

        // REMOVE
        else if (ARGCMP("-m", "--marked", REMOVE_TASK)) {_tc.fp.marked = true;}

        // LIST
        else if (ARGCMP("--type", "--type", LIST)) {CHECKNEXT(type, PARAM)}
    }

    if (_tc.func == NONE) _tc.err = NO_FUNC_GIVEN;

    return _tc;
}
