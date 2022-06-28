
#include <time.h>
#include <stdio.h>

#include "printConf.h"

#include "../src/main.h"
#include "../src/argparse.h"
#include "../src/additional.h"

int main (int argc, char *argv[])
{
    todoConf tc;
    initTodoConf(&tc);

    // setting up arguments
    int argc_ = 12;
    char *argv_[] = {
        "./todo",
        "add",
        "-t", "test",
        "-ex", "2020/01/01/00/00",
        "-ca", "1,2,3",
        "-pr", "1",
        "-pa", "test.txt"
    };

    // parsing arguments
    tc = parseArguments(argc_, argv_);

    // printing arguments
    printTodoConfig(tc);

    // parse date
    time_t tm = convertStringToDate(tc.fp.expireDate);
    printf("%s\n", asctime(localtime(&tm)));

    return 0;
}
