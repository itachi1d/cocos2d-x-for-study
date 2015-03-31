#include "EMailXmlReader.h"
#include "platform/CCSAXParser.h"
#include "EmailManager.h"
#include "Gbk2UTF_8.h"

void EMailXmlReader::Init(std::string path){
	mail = NULL;
	preTag = "";
	SAXParser parser;
	CCASSERT(parser.init("UTF-8"), "The file format isn't UTF-8");
	parser.setDelegator(this);
	parser.parse(path);
}

void EMailXmlReader::startElement(void *ctx, const char *name, const char **atts)
{//atts[0] : HeroLevel,atts[1] attribute
	CC_UNUSED_PARAM(ctx);
	CC_UNUSED_PARAM(atts);

	const std::string sName(name);
	preTag = sName;  
	if(preTag.compare("info") == 0){	
		mail = new EMail(); 
		int number;    
		std::stringstream ss;
		ss << atts[1];
		ss >> number; 
		mail->type = number;
		mail->ID = number;	
	}  
	//while(atts && *atts)
	//{
	//	GameLog("attribute = %s=======%s",atts[0],atts[1]); 
	//	++ atts;
	//}
}

void EMailXmlReader::endElement(void *ctx, const char *name)
{ 
	CC_UNUSED_PARAM(ctx);
	const std::string sName((char*)name);
	preTag = "";
	if(sName.compare("info") == 0 && mail != NULL){
		EmailManager::Instance()->addEMail(mail);
		mail = NULL;
	} 
}

void EMailXmlReader::textHandler(void *ctx, const char *ch, int len)
{ 
	CC_UNUSED_PARAM(ctx);
	std::string data = std::string((char*)ch,0,len); 
	if(mail != NULL) {  
		if(preTag.compare("name") == 0){ 
			//Gbk2UTF_8::ConvertStringToUTF8(data);
			mail->name = data;
		}
		else if(preTag.compare("type") == 0){
			int number;    
			std::stringstream ss;
			ss << data;
			ss >> number; 
			mail->type = number;
		}
		else if(preTag.compare("icon") == 0){
			//Gbk2UTF_8::ConvertStringToUTF8(data);
			mail->icon = data;
		}
		else if(preTag.compare("content") == 0){
			//Gbk2UTF_8::ConvertStringToUTF8(data);
			mail->content = data;
		}
		else if(preTag.compare("addresser") == 0){
			//Gbk2UTF_8::ConvertStringToUTF8(data);
			mail->addresser = data;
		}
		else if(preTag.compare("rewardID") == 0){
			//Gbk2UTF_8::ConvertStringToUTF8(data);
			mail->rewardID = data;
		}
	} 
}