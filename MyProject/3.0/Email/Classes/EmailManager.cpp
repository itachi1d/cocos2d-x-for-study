#include "EmailManager.h"

EmailManager::EmailManager()
{
	
}
EmailManager::~EmailManager()
{
	destory();
}

void EmailManager::addEMail(EMail* mail)
{
	//this->mails[mail->ID] = mail;
	this->mails.insert(std::map<int,EMail*>::value_type(mail->ID,mail));
}
void EmailManager::destory()
{
	std::map<int, EMail*>::iterator iterMap = mails.begin();
    for (;iterMap != mails.end();iterMap++)
    {
		delete iterMap->second;
    }
	mails.clear();
	this->~EmailManager();
}

EMail *EmailManager::find(int _id)
{
	return mails.find(_id)->second;
}
EmailManager* EmailManager::emailManager = NULL;