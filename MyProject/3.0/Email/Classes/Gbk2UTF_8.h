#include "cocos2d.h"
#include "iconv.h"
class Gbk2UTF_8
{
public:
	static int convert(char *from_charset, char *to_charset, char *inbuf, size_t inlen, char *outbuf, size_t outlen)
	{
		iconv_t iconvH;
		iconvH = iconv_open(to_charset, from_charset);
		if( !iconvH ) return NULL;
		memset(outbuf, 0, outlen);
 
	 #if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		const char *temp = inbuf;
		const char **pin = &temp;
		char **pout = &outbuf;
		if( !iconv(iconvH, pin, &inlen, pout, &outlen) )
		{
			iconv_close(iconvH);
			return NULL;
		}
	#else
		if( !iconv(iconvH, &inbuf, &inlen, &outbuf, &outlen) )
		{
			iconv_close(iconvH);
			return NULL;
		}
	#endif
		iconv_close(iconvH);
		return NULL;
	}
	static int gbk2utf8(char *inbuf, size_t inlen, char *outbuf, size_t outlen)
	{
		return convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
	}
	static void ConvertStringToUTF8(std::string& src){
		//return;
		char* inBuf = (char *)src.c_str();
		size_t inLen = strlen(inBuf);
		size_t outLen = inLen << 1;
		char* outBuf = (char *)malloc(outLen); 
		gbk2utf8(inBuf,inLen,outBuf,outLen);
		src = outBuf;
	}
};