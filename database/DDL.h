#include "common.h"
#include <string>
#include <iostream>

#define DTATBASEL "data"        // the dir of databases
#define DBMAX   64      // the maxnum of databases.

#define IOLOG   "./log/IO.log"

// flag of create database
#define IF_NOT_EXIST    1   

// flag of delete database
#define IF_EXIST    1

/* 
    databases DDL
*/

// show all the databases
std::string * show_databases(int * size);       

// show current database
std::string show_cur_db(void);

// create a database   return -1 means error 1 means db exists (no IF_NOT_EXIST) 0 means success
int create_db(std::string db_name , int CDB_flags);

// delete a database   return -1 means error 1 means db not exists (no IF_EXIST) 0 means success
int delete_db(std::string db_name , int DDB_flags);

// change the current database    return -1 means error 1 means db not exists 0 means success
int use_db(std::string db_name);
