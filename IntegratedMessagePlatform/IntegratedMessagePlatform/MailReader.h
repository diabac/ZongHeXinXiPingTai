#ifndef _MAIL_READER_H_
#define _MAIL_READER_H_

/***********************Class MaileReader****************************
* Description: The Interface for Mail Module
* Use:			Convert Mail message to standard message
Add to MessageFiller queue
******************************************************************/

#include "MessageFiller.h"
#include "StdAfx.h"
#include "DBInterface.h"
#include "pop3.h" 
#include <conio.h>
#include <iostream>
using namespace std;

class MailReader{
	//Mail Module Listening Thread
	friend DWORD WINAPI read_message_from_mail(LPVOID lpParameter);
public:
	MailReader(MessageFiller* filler);
	~MailReader();

	HANDLE Start();
	void initPop3(CPop3 pop, const char* username, const char* userpwd, const char* svraddr, 
		int& sum,unsigned short port = 110);
	void getPart(char *whole, char *txt,int i,CPop3 pop);	//get part and you can fetch info from it
	void getFrom(char* part,char* from);					//get source email address, part is part or whole
	void MailReader::checkFrom(char*from,char* twe);		//check if it is from sjtu
	void getSubject(char* part, char* subject);				//get subject like XXX:YYY
	bool checkSubject(char* subject);						//judge whether the subject could be used
	void getRealSubject(char* subject, char* realSub);		//get YYY
	void getReceiver(char* subject,char *receiver);			//get XXX
	void getmoreContent(char* part, char * cont);			//a function help to getContent
	void getContent(char* part, char* content);				//use getmoreContent together and get the mail content
	void convertToSimplemessage(char *content,char* receiver);

private:
	MessageFiller* m_filler;
};

#endif