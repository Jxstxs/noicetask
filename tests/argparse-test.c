
#include <stdio.h>

#include "../src/main.h"
#include "../src/argparse.h"

#include "printConf.h"

int main(void){

    printf("Testing Argparse\n");

    char *argsTest2[] = {
        "m",
        "-f",
        "path",
        "-nv",
        "$HOME/gits/noicetask/README.md"
    };
    todoConf tcTest2 = parseArguments(4, argsTest2);
    printTodoConfig(tcTest2);
    
    return 0;
}
