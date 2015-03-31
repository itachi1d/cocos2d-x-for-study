
#include "EMail.h"
#include "TSingleton.h"

class EmailManager : public TSingleton<EmailManager>
{
public:
	static EmailManager* Instance()
	{	
		if(emailManager == NULL)
			emailManager = new EmailManager();
		return emailManager;
	}
	void addEMail(EMail* mail);
	EMail *find(int);
	void destory();

	std::map<int, EMail*> mails;
private:
	EmailManager();
	~EmailManager();
	static EmailManager* EmailManager::emailManager;	
};