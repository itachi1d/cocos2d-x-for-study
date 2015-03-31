#include "cocos2d.h"
#include "EMail.h"
USING_NS_CC;
class EMailXmlReader : public SAXDelegator
{
public:
	void Init(std::string path); 
	~EMailXmlReader(){}
	void startElement(void *ctx, const char *name, const char **atts);
	void endElement(void *ctx, const char *name);
	void textHandler(void *ctx, const char *ch, int len);
private:
	EMail *mail;
	std::string preTag;
};