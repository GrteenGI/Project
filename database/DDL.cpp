#include "DDL.h"

FILE * io_logfp;
std::string CUR_DB;         // current database
char * CUR_DIR;         // current dir

/* 
    databases DDL
*/

std::string * show_databases(int * size) {
    DIR             *dp;
    struct dirent   *dirp;
    struct stat     statbuf;
    int i = 0;
    std::string * res = new std::string[DBMAX];
    
    if ((dp = opendir(DTATBASEL)) == NULL) {      // can't read directory
        fprintf(io_logfp , "show_databases : can't read dir" DTATBASEL "\n");
        return NULL;
    }
    while ((dirp = readdir(dp)) != NULL) {
        if (strcmp(dirp->d_name , ".") == 0 || strcmp(dirp->d_name , "..") == 0)
            continue;           // ignore dot and dot-dot
        res[i++].assign(dirp->d_name);
    }
    *size = i;
    return res;
}

std::string show_cur_db(void) {
    return CUR_DB;
}

int create_db(std::string db_name , int CDB_flags) {
    int size = 0;
    std::string * all_db_name = show_databases(&size);       // get all the db name
    if (all_db_name == NULL)
        return -1;      // error
    for (int i = 0 ; i < size ; i++){
        if (all_db_name[i] == db_name){
            if (CDB_flags & IF_NOT_EXIST)       // have the IF_NOT_EXIST flags
                return 0;           // suceess
            else {            // no IF_NOT_EXIST and find a db'name as same as target db
                fprintf(io_logfp , "create_db : db exists name : %s\n" , (char*)db_name.data());
                return 1;           // db exists
            }
        }
    }
    char fullpath[PATH_MAX];
    strcpy(fullpath , "./" DTATBASEL); 
    strcpy(&fullpath[strlen(fullpath)] , "/");
    strcpy(&fullpath[strlen(fullpath)] , (char *)db_name.data());

    if (mkdir(fullpath , O_RDWR | 0777) == -1) {
        fprintf(io_logfp , "create_db : mkdir error\n");
        return -1;      // error
    }
    fprintf(io_logfp , "create_db : create db success name : %s" , (char *)db_name.data());
    return 0;       // success
}

int delete_db(std::string db_name , int DDB_flags) {
    FILE * fp;
    int size = 0;
    std::string * all_db_name = show_databases(&size);       // get all the db name
    if (all_db_name == NULL)
        return -1;      // error
    for (int i = 0 ; i < size ; i++){
        if (all_db_name[i] == db_name){             // find the target
            char cmdstr[PATH_MAX];
            strcpy(cmdstr , "rm -rf ./");
            strcpy(&cmdstr[strlen(cmdstr)] , DTATBASEL "/");
            strcpy(&cmdstr[strlen(cmdstr)] , (char *)db_name.data());
            if ((fp = popen(cmdstr , "r")) == NULL) {
                fprintf(io_logfp , "delete db : popen error\n");
                return -1;      // error
            }
            fprintf(io_logfp , "delete_db success name : %s\n" , (char *)db_name.data());
            return 0;       // success
        }
    }
    // not find target db
    if (DDB_flags & IF_EXIST)
        return 0;       // success
    fprintf(io_logfp , "delete db : not find target db\n");
    return 1;       // not found
}

int use_db(std::string db_name) {
    int size = 0;
    std::string * all_db_name = show_databases(&size);       // get all the db name
    if (all_db_name == NULL)
        return -1;      // error
    for (int i = 0 ; i < size ; i++){
        if (all_db_name[i] == db_name){     // find the target db
            CUR_DB = db_name;           // change the current db
            fprintf(io_logfp , "use_db : use db success name : %s\n" , (char *)db_name.data());
            return 0;           // success
        }
    }
    fprintf(io_logfp , "use_db : use db failed not find target db name : %s\n" , (char *)db_name.data());
    return 1;       // target db not find
}

int main(void) {
    io_logfp = fopen(IOLOG , "w+");        // open the IO log
    use_db("777");
    create_db("777" , 0);
    use_db("777");
    std::cout << CUR_DB << std::endl;
    delete_db("777" , 0);
    use_db("777");
}