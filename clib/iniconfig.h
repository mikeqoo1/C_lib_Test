#ifndef INICONFIG_H
#define INICONFIG_H
#include <mysql.h>

#include "iniparser.h"
#include <stdio.h>
#include <string.h>

void parse_ini_file(const char *ini_file_name);

void init_DB_connection();

void close_DB_connection();

void reconnect_DB(char *ini_name);

MYSQL *getConnection();

#endif