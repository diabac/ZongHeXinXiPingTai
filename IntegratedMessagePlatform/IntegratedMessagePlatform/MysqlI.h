#ifndef _MY_SQLI_H_
#define _MY_SQLI_H_
#include<winsock2.h>
#include<windows.h>
#include<mysql.h>
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;
#pragma comment(lib,"libmysql.lib")

class MySqlConn
{
private:
	MYSQL *mysql;           //sturcture
	MYSQL_RES *res;         //result
	MYSQL_ROW  row;         //row point
	MYSQL_FIELD *field;     

	string host;            
	string username;          
	string password;          
	string database;        //name of database  
	int port;           
	string socket;
	int client_flag; 
public:
	bool connect(string UserName,string Password,string DataBase); //connect database

	MYSQL_RES* query(string queryStr);				//return MYSQL_RES point(res)
	bool execute(string execuStr);					//execute SQL
	int affectedRows();    //the rows the lattest time excute insert delete update
	void close();          //disconnect
};
#endif