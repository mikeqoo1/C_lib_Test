#include "iniconfig.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <ini.file>\n", argv[0]);
        return 1;
    }
    const char *file = argv[1];
    parse_ini_file(file);
    init_DB_connection();
    getConnection();
    return 0;
}