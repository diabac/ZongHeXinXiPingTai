#include "DBInterface.h"

MySqlConn msc;
MYSQL_RES *result;
MYSQL_ROW sql_row;
MYSQL_FIELD *fd;

string dataBase="msgplatform";

/*create new tables*/
void createTable(string createTableSql){
	msc.execute(createTableSql);
	system("pause");
}

void getDataByNum(string str, int num, vector<string> &vec, int choice)
{	
	string querySql="\0";
	string c;

	if(choice==3)
	{ //convent int to string
		ostringstream oss;
		oss<<num;
		c=oss.str();
	}

	switch(choice)
	{
	case 1:	//team.team->person.name
		querySql += "select person.name from person, team where team_name='"+str+"' and person.user_id=team.user_id";
		break;
	case 2:	//person.name->person.others
		querySql += "select user_id,cellphone,phone,email,type1,type2,type3 from person where name='"+str+"'";
		break;
	case 3:	//msg.user_id->person.others but not person.name
		querySql += "select distinct cellphone,phone,email,type1,type2,type3 from person, msg where person.user_id = "+c;
		break;
	default:
		cout<<"You choose the invalid num."<<endl;
	}

	result=msc.query(querySql);
	if(result)
	{	int i=0;
	int j=mysql_num_fields(result);
	while(sql_row=mysql_fetch_row(result))
	{
		for(i=0;i<j;i++)
		{
			vec.push_back(sql_row[i]);
		}
	}
	}
	else
	{
		cout<<"query sql failed!"<<endl;
	}

}

void getDataLikeSql(char* fro, char* selec, char* constr, int num, vector<string*> &vec)
{	
	do
	{
		string from(fro);
		string afterselect(selec);
		string sconstr(constr);
		string querySql="\0";
		querySql+=("select "+afterselect+" from "+from+" where "+sconstr);
		result=msc.query(querySql);
	}
	while(!result);
	if(result)
	{	int i=0;
	int j=mysql_num_fields(result);
	int count=num;
	while(sql_row=mysql_fetch_row(result))
	{	string *row=new string[num];
	for(i=0;i<j;i++)
	{
		row[i].assign(sql_row[i]);
	}
	vec.push_back(row);
	}
	}
	else
	{
		cout<<"query sql failed!"<<endl;
	}
}

char* getByColumn(int row, int column, vector<string*> vec )
{
	vector<string*>::const_iterator iter=vec.begin()+row;
	const char* des=(*iter)[column].c_str();
	return (char*)des;
}

