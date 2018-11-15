#include "iniconfig.h"
#include "iniparser.h"
#include <stdio.h>
#include <string.h>

static const char *db_host = NULL;
static int db_port = 3306;
static const char *db_user = NULL;
static const char *db_pass = NULL;
static const char *db_db = NULL;
static const char *ipc_host = NULL;
static int ipc_port;

dictionary *ini = NULL;

MYSQL *Conn = NULL;

void parse_ini_file(const char *ini_file_name)
{
    ini = iniparser_load(ini_file_name);

    if (ini == NULL) {
        printf("找不到ini設定檔\n");
        exit(-1);
    }

    db_host = iniparser_getstring(ini, "DataBase:host", NULL);
    db_port = iniparser_getint(ini, "DataBase:port", 3306);
    db_user = iniparser_getstring(ini, "DataBase:user", NULL);
    db_pass = iniparser_getstring(ini, "DataBase:pass", NULL);
    db_db = iniparser_getstring(ini, "DataBase:db", NULL);

    printf("%s, %d, %s, %s, %s\n", db_host, db_port, db_user, db_pass, db_db);

    iniparser_freedict(ini);
}

void init_DB_connection()
{
    Conn = mysql_init(NULL);

    if (Conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(Conn));
        exit(-1);
    }

    printf("%s, %d, %s, %s, %s\n", db_host, db_port, db_user, db_pass, db_db);

    if (NULL == mysql_real_connect(Conn, db_host, db_user, db_pass, db_db, db_port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(Conn));
        exit(-1);
    }
}

void close_DB_connection()
{
    if (Conn != NULL) {
        mysql_close(Conn);
        Conn = NULL;
    }
}

void reconnect_DB(char *ini_name)
{
    if (Conn != NULL) mysql_close(Conn);

    init_DB_connection(ini_name);
}

MYSQL *getConnection() { return Conn; }