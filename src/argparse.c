
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
//      // CREATE ARG
//      else if (ARGCMP("-cr", "--create") && _tc.func == NONE) {
//          // HERE 
//      }

        // FUNCTIONS
        else if (ARGCMP("a", "add", NONE)) _tc.func = ADD_TODO;
        else if (ARGCMP("d", "done", NONE)) _tc.func = DONE_TODO;
        else if (ARGCMP("r", "remove", NONE)) _tc.func = REMOVE_TODO;
        else if (ARGCMP("m", "modify", NONE)) _tc.func = MOD_TODO;
        else if (ARGCMP("p", "print", NONE)) _tc.func = LIST;
        
        // FUNCTION PARAMETERS
        // ADD
        else if (ARGCMP("-t", "--title", ADD_TODO))         {CHECKNEXT(title, PARAM)}
        else if (ARGCMP("-d", "--description", ADD_TODO))   {CHECKNEXT(description, PARAM)}
        else if (ARGCMP("-pa", "--path", ADD_TODO))         {CHECKNEXT(title, PARAM)}
        else if (ARGCMP("-ex", "--expire", ADD_TODO))       {CHECKNEXT(title, PARAM)}
        else if (ARGCMP("-ca", "--category", ADD_TODO))     {CHECKNEXT(title, PARAM)}
        else if (ARGCMP("-pr", "--priority", ADD_TODO))     {CHECKNEXT(title, PARAM)}

        // DONE
        else if (ARGCMP("-id", "-id", DONE_TODO)) {CHECKNEXT(ids, PARAM)}

        // MOD
        else if (ARGCMP("-f", "--field", MOD_TODO)) {CHECKNEXT(field, PARAM)}
        else if (ARGCMP("-nv", "--newvalue", MOD_TODO)) {CHECKNEXT(newValue, PARAM)}

        // REMOVE
        else if (ARGCMP("-m", "--marked", REMOVE_TODO)) {_tc.fp.marked = True;}

    }

    if (_tc.func == NONE) _tc.err = NO_FUNC_GIVEN;

    return _tc;
}
