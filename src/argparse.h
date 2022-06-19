#ifndef ARGPARSE_H

#define ARGCMP(x, y, z) ((strcmp(argv[i], x) == 0 || strcmp(argv[i], y) == 0) && _tc.func == z)
#define CHECKNEXT(x, y) if (argv[i+1]) { _tc.fp.x = argv[i+1]; skip = 1; } else { _tc.err = y; return _tc; }

todoConf parseArguments(int argc, char** argv);

#endif // ARGPARSE_H
