
#include "../src/database.h"

int main (int argc, char *argv[])
{
    DataBaseResult dbr;
    DataBaseQuery dbq;

    dbq.distinct = false;
    dbq.tables = "todos";
    dbq.columns = "*";
    dbq.where = "";
    dbq.order = "";

     dbr = getDbResults(NULL, dbq);

    dbq.distinct = true;
    dbq.tables = "tags as tg ";
    dbq.columns = "tg.ID as i";
    dbq.where = "WHERE ID=1 ";
    dbq.order = "DESC";

     dbr = getDbResults(NULL, dbq);

    return 0;
}
