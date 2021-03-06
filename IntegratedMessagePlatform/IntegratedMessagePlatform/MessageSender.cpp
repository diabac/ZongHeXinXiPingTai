#include <afx.h>
#include <fstream>
#include "PhoneDial.h"
#include "MessageSender.h"
#include "SendMail.h"

//#define DEBUG_PRINT

//DWORD WINAPI sendthread(LPVOID lpParameter);

#ifdef DEBUG_PRINT
ofstream or_sender("out/Sender_Read.txt");
ofstream ow_sender("out/Sender_Write.txt");
#endif

MessageSender::MessageSender()
{
	h_Read = CreateEvent(NULL, FALSE, TRUE, NULL);
	h_Write = CreateEvent(NULL, TRUE, FALSE, NULL);
	h_Resend = CreateEvent(NULL, FALSE, FALSE, NULL);
	h_ResendThread = CreateThread(NULL, 0, resendthread, this, 0, NULL);
}

MessageSender::~MessageSender()
{
	CloseHandle(h_Read);
	CloseHandle(h_Write);
	CloseHandle(h_Resend);
	CloseHandle(h_ResendThread);

	#ifdef DEBUG_PRINT
	or_sender.close();
	ow_sender.close();
	#endif
}
//create send thread
HANDLE MessageSender::Send()
{
	#ifdef DEBUG_PRINT
	printf("Send Thread Create\n");
	#endif

	HANDLE handle = CreateThread(NULL, 0, sendthread, this, 0, NULL);
	return handle;
}
//call from filler and add message to queue
void MessageSender::AddMessage(const Message& message)
{
//	ResetEvent(h_Write);
	DWORD wait_result = WaitForSingleObject(h_Read, INFINITE);
	if(wait_result == WAIT_OBJECT_0) {
		sender_queue.push(message);
		#ifdef DEBUG_PRINT
		ow_sender << "Send Thread: Write Message = " << message.ID << std::endl;
		#endif
		//notify events
		SetEvent(h_Write);
		SetEvent(h_Read);
	}
}
//send thread
DWORD WINAPI sendthread(LPVOID lpParameter)
{
	MessageSender* sender = (MessageSender*) lpParameter; 
	
	HANDLE h_Events[2];
	h_Events[0] = sender->h_Read;
	h_Events[1] = sender->h_Write;
	DWORD wait_result;

	PhoneDial* dialler = new PhoneDial();
	while(true) {
		//wait events
		wait_result = WaitForMultipleObjects(2, h_Events, TRUE, INFINITE);
		if(wait_result == WAIT_OBJECT_0) {
			while(!sender->sender_queue.empty()) {
				//read message from queue
				Message message = sender->sender_queue.front();
				#ifdef DEBUG_PRINT
				or_sender << "Send Thread: Read Message = " << message.get_id() << std::endl;
				#endif
				//remove the message
				sender->sender_queue.pop();
				//send message to down layer
				//wake up resend thread
				SetEvent(sender->h_Resend);
				//add message to database


				switch(message.get_type()) {
					case MESSAGE_CHOICE : 
						sendMessage(message);
						break;
					case PHONE_CHOICE : 
						printf("phone send");
						dialler->AddPhoneMessage(message);
						break;
					case MAIL_CHOICE : 
						sendMail(message);
						break;
					default :
						printf("error");
				}
			}
			
			//queue empty then sleep itself if queue is empty
			ResetEvent(h_Events[1]);
			//notify read event
			SetEvent(h_Events[0]);
		}
	}
	//free pointer
	if(sender != NULL) {
		free(sender);
		sender = NULL;
	}
	return 0;
}

DWORD WINAPI resendthread(LPVOID lpParameter)
{
	MessageSender* sender = (MessageSender*)lpParameter;

	while(true) {
		WaitForSingleObject(sender->h_Resend, INFINITE);
		//scan database to resend

	}

	return 1;
}