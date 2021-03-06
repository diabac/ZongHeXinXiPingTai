#ifndef _DB_INTERFACE_H_
#define _DB_INTERFACE_H_

#include "MysqlI.h"
#include <sstream> 
#include <vector>

extern MySqlConn msc;
extern MYSQL_RES *result;
extern MYSQL_ROW sql_row;
extern MYSQL_FIELD *fd;
extern string dataBase;

/* create tables */
void createTable(string createTableSql);  
/* Tool Functions */
void getDataByNum(string str, int num, vector<string> &vec, int choice); 
void getDataLikeSql(char* fro, char* selec, char* constr,int num,vector<string*> &vec);
char* getByColumn(int row,int column, vector<string*>vec);
#endif 

