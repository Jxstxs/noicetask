
#include <stdio.h>

#include "../src/main.h"

void printTodoConfig(todoConf tc) {
    printf(
    "\tdatabasePath: '%s'\n"
    "\tnoConfirm: %d\n"
    "\terr: %d\n"
    "\tfunc: %d\n"
    "\ttitle: '%s'\n"
    "\tdescription: '%s'\n"
    "\tpath: '%s'\n"
    "\texpireDate: '%s'\n"
    "\tcategories: '%s'\n"
    "\tfield: '%s'\n"
    "\tnewValue: '%s'\n"
    "\ttype: '%s'\n"
    "\tids: '%s'\n"
    "\tpriority: '%s'\n"
    "\tmarked: %d\n",
    tc.databasePath,
    tc.noConfirm,
    tc.err,
    tc.func,
    tc.fp.title,
    tc.fp.description,
    tc.fp.path,
    tc.fp.expireDate,
    tc.fp.categories,
    tc.fp.field,
    tc.fp.newValue,
    tc.fp.type,
    tc.fp.ids,
    tc.fp.priority,
    tc.fp.marked
    );
}
