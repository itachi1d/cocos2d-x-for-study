# ���Ե���cocoStudio�����Ķ��������������Լ��������

## ����
1.������룺`	ArmatureDataManager::getInstance()->addArmatureFileInfo("NewAnimation/NewAnimation.ExportJson");    
		Armature *armatureBird = Armature::create("Animation1");  
		armatureBird->setPosition(Point(visibleSize.width/2, visibleSize.height/2));  
		this->addChild(armatureBird);  
		armatureBird->getAnimation()->playByIndex(0);`���к����

## �������
1.���г�����ΪArmature *armatureBird = Armature::create("NewAnimation"); ��" "���������cocostduio����Ŀ���֣�������ȡ���ֻ�����д������