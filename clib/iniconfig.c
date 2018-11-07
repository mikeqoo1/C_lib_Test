#include "iniconfig.h"
#include "iniparser.h"
#include <stdio.h>
#include <string.h>

static const char *db_host;
static int db_port;
static const char *db_user;
static const char *db_pass;
static const char *db_db;
static const char *ipc_host;
static int ipc_port;

dictionary *ini = NULL;

void parse_ini_file(const char *ini_file_name)
{
    ini = iniparser_load(ini_file_name);

    if(ini==NULL){
        printf("找不到ini設定檔\n");
        exit(-1);
    }

    db_host = iniparser_getstring(ini, "DataBase:host", NULL);
    db_port = iniparser_getint(ini, "DataBase:port", 3306);
    db_user = iniparser_getstring(ini, "DataBase:user", NULL);
    db_pass = iniparser_getstring(ini, "DataBase:pass", NULL);
    db_db= iniparser_getstring(ini, "DataBase:db", NULL);

    ipc_host = iniparser_getstring(ini, "Ipc:host", NULL);
    ipc_port = iniparser_getint(ini, "Ipc:port", 3306);
    printf("%s, %d, %s, %s, %s\n", db_host, db_port, db_user, db_pass, db_db);
    printf("%s, %d\n", ipc_host, ipc_port);

    iniparser_freedict(ini);
}