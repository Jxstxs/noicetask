#ifndef ARGPARSE_H
#define ARGPARSE_H

#include "main.h"

#define ARGCMP(x, y, z) ((strcmp(argv[i], x) == 0 || strcmp(argv[i], y) == 0) && (_tc.func == z || z == ANY))
#define CHECKNEXT(x, y) if (argv[i+1]) { _tc.fp.x = argv[i+1]; skip = 1; } else { _tc.err = y; return _tc; }

taskConf parseArguments(int argc, char** argv);

#endif // ARGPARSE_H
