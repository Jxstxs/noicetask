
#include "../src/database.h"

int main (int argc, char *argv[])
{
    
    DataBaseQuery dbq;

    dbq.distinct = false;
    dbq.tables = "todos";
    dbq.columns = "*";
    dbq.where = "";
    dbq.order = "";

    DataBaseResult *dbr1 = getDbResults(NULL, dbq);

    dbq.distinct = true;
    dbq.tables = "tags as tg ";
    dbq.columns = "tg.ID as i";
    dbq.where = "WHERE ID=1 ";
    dbq.order = "DESC";

    DataBaseResult *dbr2 = getDbResults(NULL, dbq);

    return 0;
}
