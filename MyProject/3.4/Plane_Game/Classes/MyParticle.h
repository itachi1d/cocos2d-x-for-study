#ifndef _MYPARTICLE_
#define _MYPARTICLE_
#include "cocos2d.h"
using namespace cocos2d;

//粒子效果优化类
class MyParticle : public ParticleSystemQuad
{
public:
	static ParticleSystem* create(ValueMap& dictionary, const std::string& plistFile)
	{
		MyParticle *particleSystemQuad = new MyParticle();
		if (particleSystemQuad && particleSystemQuad->initWithFile(dictionary, plistFile))
		{
			particleSystemQuad->autorelease();
			return particleSystemQuad;
		}
		CC_SAFE_DELETE(particleSystemQuad);
		return nullptr;
	}
	bool initWithFile(ValueMap& dictionary, const std::string& plistFile);
	bool initWithDictionary(ValueMap& dictionary, const std::string& dirname);
};
#endif