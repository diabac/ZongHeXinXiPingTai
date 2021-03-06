#ifndef _PHONE_DIAL_H_
#define _PHONE_DIAL_H_

#include "afx.h"
#include "MessageQueue.h"
#include "Message.h"
#include <list>

#define CH_NUM 4

class PhoneDial
{
	friend DWORD WINAPI dial(LPVOID lpParameter);
public:
	PhoneDial();
	~PhoneDial();
	void AddPhoneMessage(const Message& message);
private:
	HANDLE h_Message;
	HANDLE h_Dial;
	MessageQueue<Message> m_list;

	BOOL InitBoard();
	BOOL CloseBoard();
	BOOL PickUp(int ch);
	BOOL Dial(int ch, const char* buf);
	
	BOOL ChAllFree();
	int SearchFreeCh();
};

#endif