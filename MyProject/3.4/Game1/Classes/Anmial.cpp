#include "Anmial.h"
#include "ResourceManager.h"

Anmial::Anmial():type(1)
{
	
}
Anmial* Anmial::create(int type)
{
	std::string fileName;
	switch (type)
	{
	case 1:
		fileName = "daxiang0.png";
		break;
	case 2:
		fileName = "houzi0.png";
		break;
	case 3:
		fileName = "tuoniao0.png";
		break;
	case 4:
		fileName = "banma0.png";
		break;
	case 5:
		fileName = "luotuo0.png";
		break;
	case 6:
		fileName = "shizi0.png";
		break;
	case 7:
		fileName = "yezhu0.png";
		break;
	case 8:
		fileName = "xiniu0.png";
		break;
	case 9:
		fileName = "xiongmao0.png";
		break;
	case 10:
		fileName = "kongong0.png";
		break;
	case 11:
		fileName = "wugui0.png";
		break;
	default:
		break;
	}
	return Anmial::createWithSpriteFrameName(fileName, type);
}
Anmial* Anmial::createWithSpriteFrameName(const std::string& spriteFrameName, int type)
{
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
    CCASSERT(frame != nullptr, msg);
#endif
    
    return createWithSpriteFrame(frame, type);
}
Anmial* Anmial::createWithSpriteFrame(SpriteFrame *spriteFrame, int type)
{
    Anmial *sprite = new (std::nothrow) Anmial();
    if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
    {
		sprite->type = type;
		sprite->initBuRu();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Anmial::playerRunAnimation()
{
	Vector<SpriteFrame*> vector;
	switch (type)
	{
	case 1:
		vector = ResourceManager::vector_daxiang;
		break;
	case 2:
		vector = ResourceManager::vector_houzi;
		break;
	case 3:
		vector = ResourceManager::vector_tuoniao;
		break;
	case 4:
		vector = ResourceManager::vector_banma;
		break;
	case 5:
		vector = ResourceManager::vector_luotuo;
		break;
	case 6:
		vector = ResourceManager::vector_shizi;
		break;
	case 7:
		vector = ResourceManager::vector_yezhu;
		break;
	case 8:
		vector = ResourceManager::vector_xiniu;
		break;
	case 9:
		vector = ResourceManager::vector_xiongmao;
		break;
	case 10:
		vector = ResourceManager::vector_kongong;
		break;
	case 11:
		vector = ResourceManager::vector_wugui;
		break;
	default:
		break;
	}
	Animation *animation = Animation::createWithSpriteFrames(vector, 0.07f, -1);
	animation->setDelayPerUnit((float)(5+rand()%3)/100);
	Animate *anima = Animate::create(animation);	
	this->runAction(anima);
}

void Anmial::initBuRu()
{
	switch (type)
	{
	case 1:
		buRu = true;
		break;
	case 2:
		buRu = true;
		break;
	case 3:
		buRu = false;
		break;
	case 4:
		buRu = true;
		break;
	case 5:
		buRu = true;
		break;
	case 6:
		buRu = true;
		break;
	case 7:
		buRu = true;
		break;
	case 8:
		buRu = true;
		break;
	case 9:
		buRu = true;
		break;
	case 10:
		buRu = false;
		break;
	case 11:
		buRu = false;
		break;
	default:
		break;
	}
}
int Anmial::getSpeed()
{
	return speed;
}
void Anmial::setSpeed(int _speed)
{
	this->speed = _speed;
}

void Anmial::AnimalsContact(Anmial* animal)
{
	if(this->getPositionY() < animal->getPositionY())
	{
		if(this->getZOrder() <= animal->getZOrder())
			this->setZOrder(animal->getZOrder()+1);
	}else
	{
		if(this->getZOrder() >= animal->getZOrder())
			animal->setZOrder(this->getZOrder()+1);
	}
}

int Anmial::getType()
{
	return type;
}
bool Anmial::isbuRu()
{
	return buRu;
}